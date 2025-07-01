#include "../common/database.h"
#include "../common/eqemu_logsys.h"
#include "../common/strings.h"

#include "zonelist.h"
#include "zoneserver.h"
#include "worlddb.h"
#include "resource_hunter.h"
#include "resource_hunter_zones.h"

#include <ctime>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

// Use shared externs
extern WorldDatabase database;
extern WorldDatabase content_db;
extern ZSList zoneserver_list;

ResourceHunterZones ez;

bool HasRotatedToday() {
	auto results = database.QueryDatabase(
		"SELECT value FROM variables WHERE varname = 'rh_last_rotated';"
	);

	if (!results.Success() || results.RowCount() == 0)
		return false;

	auto row_iter = results.begin();
	if (row_iter == results.end()) {
		return false;
	}

	std::string last_date_str = row_iter[0];

	// Get today's date string (YYYY-MM-DD)
	time_t now = time(nullptr);
	char today[11];
	strftime(today, sizeof(today), "%Y-%m-%d", localtime(&now));

	return last_date_str == today;
}

void RotateResourceHunterZones() {
	if (!ez.Load()) {
		LogError("Failed to load expansion zones for Resource Hunter rotation.");
		return;
	}

	// Weight brackets
	std::map<LevelBracket, int> bracket_weights = {
		{ LevelBracket::Bracket_1_10,    2 },
		{ LevelBracket::Bracket_11_20,  2 },
		{ LevelBracket::Bracket_21_30,  2 },
		{ LevelBracket::Bracket_31_40,  3 },
		{ LevelBracket::Bracket_41_50,  3 },
		{ LevelBracket::Bracket_51_60,  4 },
		{ LevelBracket::Bracket_61_65,  1 }
	};

	// Create weighted zone pool
	std::vector<std::string> weighted_zone_pool;
	for (const auto& [bracket, zones] : ez.GetZonesByBracket()) {
		int weight = bracket_weights[bracket];
		for (const auto& zone : zones) {
			for (int i = 0; i < weight; ++i) {
				weighted_zone_pool.push_back(zone.short_name);
			}
		}
	}

	// Shuffle and draw zones
	std::shuffle(weighted_zone_pool.begin(), weighted_zone_pool.end(), std::default_random_engine(static_cast<unsigned>(time(nullptr))));
	std::unordered_set<std::string> used_zones;

	// Bonus types and how many zones to assign per type
	std::map<std::string, std::pair<int, int>> bonus_ranges = {
		{ "exp", {10, 14} },
		{ "coin", {8, 11} },
		{ "loot", {1, 5} },
		{ "respawn", {3, 5} },
		{ "empowered", {2, 5} }
	};

	// Clear previous day's bonuses
	database.QueryDatabase("DELETE FROM resource_hunter_zones;");

	LogInfo("Selected zones for bonuses:");
	auto zone_iter = weighted_zone_pool.begin();
	std::default_random_engine rng(static_cast<unsigned>(time(nullptr)));

	for (const auto& [bonus, range] : bonus_ranges) {
		int min_count = range.first;
		int max_count = range.second;
		std::uniform_int_distribution<int> dist(min_count, max_count);
		int count = dist(rng); // pick a number within the range

		int assigned = 0;
		while (assigned < count && zone_iter != weighted_zone_pool.end()) {
			std::string z = *zone_iter++;
			if (used_zones.count(z)) continue;

			used_zones.insert(z);
			assigned++;

			// TODO: Report these to discord webhook
			//LogInfo("  - Bonus: {} | Zone: {}", bonus, z);
			auto query = StringFormat(
				"INSERT INTO resource_hunter_zones (zone_short_name, bonus_type) VALUES ('%s', '%s');",
				z.c_str(), bonus.c_str()
			);
			database.QueryDatabase(query);
		}
	}


	// Store today's date
	time_t now = time(nullptr);
	char today[11];
	strftime(today, sizeof(today), "%Y-%m-%d", localtime(&now));

	auto update_query = StringFormat(
		"REPLACE INTO variables (varname, value, information, ts) VALUES ('rh_last_rotated', '%s', 'Last date Resource Hunter zones rotated', NOW());",
		today
	);
	database.QueryDatabase(update_query);

	zoneserver_list.SendEmoteMessage(
		0,
		0,
		0,
		Chat::Yellow,
		"Resource Hunter zones have rotated!"
	);

	LogInfo("Resource Hunter zones rotated.");
}
