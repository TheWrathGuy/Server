#include "zone_bonus.h"
#include "zone.h"

extern ZoneDatabase database;
extern ZoneDatabase content_db;

std::unordered_map<std::string, std::unordered_set<std::string>> g_zone_bonuses;

void LoadZoneBonuses() {
	auto db = database.QueryDatabase("SELECT zone_short_name, bonus_type FROM resource_hunter_zones");
	if (!db.Success()) return;

	for (auto row = db.begin(); row != db.end(); ++row) {
		std::string zone = Strings::ToLower(row[0]);
		std::string bonus = Strings::ToLower(row[1]);
		g_zone_bonuses[zone].insert(bonus);
	}
}

bool ZoneHasBonusType(const std::string& short_name, const std::string& bonus_type) {
	auto it = g_zone_bonuses.find(Strings::ToLower(short_name));
	if (it == g_zone_bonuses.end()) return false;
	return it->second.count(Strings::ToLower(bonus_type)) > 0;
}
