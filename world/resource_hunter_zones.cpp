#include "resource_hunter_zones.h"
#include "../common/eqemu_logsys.h"
#include "worlddb.h" // for content_db

#include <unordered_map>

extern WorldDatabase content_db;

namespace {
	std::unordered_map<std::string, LevelBracket> zone_to_bracket = {
		// 1-10
		{ "akanon", LevelBracket::Bracket_1_10 },
		{ "butcher", LevelBracket::Bracket_1_10 },
		{ "commons", LevelBracket::Bracket_1_10 },
		{ "ecommons", LevelBracket::Bracket_1_10 },
		{ "erudnext", LevelBracket::Bracket_1_10 },
		{ "erudnint", LevelBracket::Bracket_1_10 },
		{ "erudsxing", LevelBracket::Bracket_1_10 },
		{ "everfrost", LevelBracket::Bracket_1_10 },
		{ "feerrott", LevelBracket::Bracket_1_10 },
		{ "felwithea", LevelBracket::Bracket_1_10 },
		{ "felwitheb", LevelBracket::Bracket_1_10 },
		{ "fieldofbone", LevelBracket::Bracket_1_10 },
		{ "gfaydark", LevelBracket::Bracket_1_10 },
		{ "grobb", LevelBracket::Bracket_1_10 },
		{ "halas", LevelBracket::Bracket_1_10 },
		{ "innothule", LevelBracket::Bracket_1_10 },
		{ "kaladima", LevelBracket::Bracket_1_10 },
		{ "kaladimb", LevelBracket::Bracket_1_10 },
		{ "kerraridge", LevelBracket::Bracket_1_10 },
		{ "misty", LevelBracket::Bracket_1_10 },
		{ "nektulos", LevelBracket::Bracket_1_10 },
		{ "neriaka", LevelBracket::Bracket_1_10 },
		{ "neriakb", LevelBracket::Bracket_1_10 },
		{ "neriakc", LevelBracket::Bracket_1_10 },
		{ "nro", LevelBracket::Bracket_1_10 },
		{ "oggok", LevelBracket::Bracket_1_10 },
		{ "paineel", LevelBracket::Bracket_1_10 },
		{ "qcat", LevelBracket::Bracket_1_10 },
		{ "qey2hh1", LevelBracket::Bracket_1_10 },
		{ "qeynos", LevelBracket::Bracket_1_10 },
		{ "qeynos2", LevelBracket::Bracket_1_10 },
		{ "qeytoqrg", LevelBracket::Bracket_1_10 },
		{ "qrg", LevelBracket::Bracket_1_10 },
		{ "rivervale", LevelBracket::Bracket_1_10 },
		{ "shadeweaver", LevelBracket::Bracket_1_10 },
		{ "sharvahl", LevelBracket::Bracket_1_10 },
		{ "sro", LevelBracket::Bracket_1_10 },
		{ "steamfont", LevelBracket::Bracket_1_10 },
		{ "tox", LevelBracket::Bracket_1_10 },
		{ "warslikswood", LevelBracket::Bracket_1_10 },

		// 11-20
		{ "arena", LevelBracket::Bracket_11_20 },
		{ "befallen", LevelBracket::Bracket_11_20 },
		{ "beholder", LevelBracket::Bracket_11_20 },
		{ "blackburrow", LevelBracket::Bracket_11_20 },
		{ "cauldron", LevelBracket::Bracket_11_20 },
		{ "cazicthule", LevelBracket::Bracket_11_20 },
		{ "crushbone", LevelBracket::Bracket_11_20 },
		{ "freporte", LevelBracket::Bracket_11_20 },
		{ "freportn", LevelBracket::Bracket_11_20 },
		{ "freportw", LevelBracket::Bracket_11_20 },
		{ "highkeep", LevelBracket::Bracket_11_20 },
		{ "highpass", LevelBracket::Bracket_11_20 },
		{ "jaggedpine", LevelBracket::Bracket_11_20 },
		{ "kurn", LevelBracket::Bracket_11_20 },
		{ "lakerathe", LevelBracket::Bracket_11_20 },
		{ "lavastorm", LevelBracket::Bracket_11_20 },
		{ "lfaydark", LevelBracket::Bracket_11_20 },
		{ "najena", LevelBracket::Bracket_11_20 },
		{ "northkarana", LevelBracket::Bracket_11_20 },
		{ "oasis", LevelBracket::Bracket_11_20 },
		{ "oot", LevelBracket::Bracket_11_20 },
		{ "runnyeye", LevelBracket::Bracket_11_20 },
		{ "soldunga", LevelBracket::Bracket_11_20 },
		{ "soldungb", LevelBracket::Bracket_11_20 },
		{ "swampofnohope", LevelBracket::Bracket_11_20 },

		// 21-30
		{ "dalnir", LevelBracket::Bracket_21_30 },
		{ "eastkarana", LevelBracket::Bracket_21_30 },
		{ "guktop", LevelBracket::Bracket_21_30 },
		{ "kaesora", LevelBracket::Bracket_21_30 },
		{ "lakeofillomen", LevelBracket::Bracket_21_30 },
		{ "mistmoore", LevelBracket::Bracket_21_30 },
		{ "netherbian", LevelBracket::Bracket_21_30 },
		{ "permafrost", LevelBracket::Bracket_21_30 },
		{ "rathemtn", LevelBracket::Bracket_21_30 },
		{ "scarlet", LevelBracket::Bracket_21_30 },
		{ "shadowhaven", LevelBracket::Bracket_21_30 },
		{ "southkarana", LevelBracket::Bracket_21_30 },
		{ "stonebrunt", LevelBracket::Bracket_21_30 },
		{ "thedeep", LevelBracket::Bracket_21_30 },
		{ "thegrey", LevelBracket::Bracket_21_30 },
		{ "twilight", LevelBracket::Bracket_21_30 },
		{ "unrest", LevelBracket::Bracket_21_30 },
		{ "warrens", LevelBracket::Bracket_21_30 },
		{ "westkarana", LevelBracket::Bracket_21_30 },

		// 31-40
		{ "burningwood", LevelBracket::Bracket_31_40 },
		{ "citymist", LevelBracket::Bracket_31_40 },
		{ "dawnshroud", LevelBracket::Bracket_31_40 },
		{ "echo", LevelBracket::Bracket_31_40 },
		{ "emeraldjungle", LevelBracket::Bracket_31_40 },
		{ "frontiermtns", LevelBracket::Bracket_31_40 },
		{ "greatdivide", LevelBracket::Bracket_31_40 },
		{ "grimling", LevelBracket::Bracket_31_40 },
		{ "iceclad", LevelBracket::Bracket_31_40 },
		{ "mseru", LevelBracket::Bracket_31_40 },
		{ "nexus", LevelBracket::Bracket_31_40 },
		{ "overthere", LevelBracket::Bracket_31_40 },
		{ "paw", LevelBracket::Bracket_31_40 },
		{ "sseru", LevelBracket::Bracket_31_40 },
		{ "tenebrous", LevelBracket::Bracket_31_40 },
		{ "timorous", LevelBracket::Bracket_31_40 },

		// 41-50
		{ "acrylia", LevelBracket::Bracket_41_50 },
		{ "bazaar", LevelBracket::Bracket_41_50 },
		{ "charasis", LevelBracket::Bracket_41_50 },
		{ "chardok", LevelBracket::Bracket_41_50 },
		{ "cobaltscar", LevelBracket::Bracket_41_50 },
		{ "crystal", LevelBracket::Bracket_41_50 },
		{ "dreadlands", LevelBracket::Bracket_41_50 },
		{ "droga", LevelBracket::Bracket_41_50 },
		{ "eastwastes", LevelBracket::Bracket_41_50 },
		{ "firiona", LevelBracket::Bracket_41_50 },
		{ "fungusgrove", LevelBracket::Bracket_41_50 },
		{ "karnor", LevelBracket::Bracket_41_50 },
		{ "katta", LevelBracket::Bracket_41_50 },
		{ "maiden", LevelBracket::Bracket_41_50 },
		{ "mischiefplane", LevelBracket::Bracket_41_50 },
		{ "nurga", LevelBracket::Bracket_41_50 },
		{ "poair", LevelBracket::Bracket_41_50 },
		{ "poinnovation", LevelBracket::Bracket_41_50 },
		{ "pojustice", LevelBracket::Bracket_41_50 },
		{ "ponightmare", LevelBracket::Bracket_41_50 },
		{ "postorms", LevelBracket::Bracket_41_50 },
		{ "scarlet", LevelBracket::Bracket_41_50 },
		{ "sebilis", LevelBracket::Bracket_41_50 },
		{ "shadowrest", LevelBracket::Bracket_41_50 },
		{ "sirens", LevelBracket::Bracket_41_50 },
		{ "skyfire", LevelBracket::Bracket_41_50 },
		{ "skyshrine", LevelBracket::Bracket_41_50 },
		{ "ssratemple", LevelBracket::Bracket_41_50 },
		{ "templeveeshan", LevelBracket::Bracket_41_50 },
		{ "trakanon", LevelBracket::Bracket_41_50 },
		{ "umbral", LevelBracket::Bracket_41_50 },
		{ "unrest", LevelBracket::Bracket_41_50 },
		{ "velketor", LevelBracket::Bracket_41_50 },
		{ "wakening", LevelBracket::Bracket_41_50 },
		{ "warrens", LevelBracket::Bracket_41_50 },
		{ "westwastes", LevelBracket::Bracket_41_50 },

		// 51-60
		{ "airplane", LevelBracket::Bracket_51_60 },
		{ "akheva", LevelBracket::Bracket_51_60 },
		{ "codecay", LevelBracket::Bracket_51_60 },
		{ "dragonnecropolis", LevelBracket::Bracket_51_60 },
		{ "fearplane", LevelBracket::Bracket_51_60 },
		{ "griegsend", LevelBracket::Bracket_51_60 },
		{ "growthplane", LevelBracket::Bracket_51_60 },
		{ "kael", LevelBracket::Bracket_51_60 },
		{ "maiden", LevelBracket::Bracket_51_60 },
		{ "povalor", LevelBracket::Bracket_51_60 },
		{ "powar", LevelBracket::Bracket_51_60 },
		{ "powater", LevelBracket::Bracket_51_60 },
		{ "sirens", LevelBracket::Bracket_51_60 },
		{ "skyshrine", LevelBracket::Bracket_51_60 },
		{ "ssratemple", LevelBracket::Bracket_51_60 },
		{ "templeveeshan", LevelBracket::Bracket_51_60 },
		{ "umbral", LevelBracket::Bracket_51_60 },
		{ "velketor", LevelBracket::Bracket_51_60 },
		{ "vexthal", LevelBracket::Bracket_51_60 },
		{ "westwastes", LevelBracket::Bracket_51_60 },

		// 61-65
		{ "bothunder", LevelBracket::Bracket_61_65 },
		{ "hohonora", LevelBracket::Bracket_61_65 },
		{ "hohonorb", LevelBracket::Bracket_61_65 },
		{ "nightmareb", LevelBracket::Bracket_61_65 },
		{ "poeartha", LevelBracket::Bracket_61_65 },
		{ "poearthb", LevelBracket::Bracket_61_65 },
		{ "pofire", LevelBracket::Bracket_61_65 },
		{ "potimea", LevelBracket::Bracket_61_65 },
		{ "potimeb", LevelBracket::Bracket_61_65 },
		{ "solrotower", LevelBracket::Bracket_61_65 },
	};
}

bool ResourceHunterZones::Load() {
	zones_by_bracket_.clear();

	for (const auto& [short_name, bracket] : zone_to_bracket) {
		ZoneInfo zone;
		zone.short_name = short_name;
		zone.bracket = bracket;

		zones_by_bracket_[bracket].push_back(zone);
	}

	LogInfo("Loaded {} level brackets with zones.", zones_by_bracket_.size());
	for (const auto& [bracket, zones] : zones_by_bracket_) {
		LogInfo("Bracket {} contains {} zones.", static_cast<int>(bracket), zones.size());
	}

	return true;
}


const std::map<LevelBracket, std::vector<ZoneInfo>>& ResourceHunterZones::GetZonesByBracket() const {
	return zones_by_bracket_;
}
