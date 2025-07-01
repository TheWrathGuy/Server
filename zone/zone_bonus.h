#pragma once
#include <unordered_map>
#include <unordered_set>
#include <string>

extern std::unordered_map<std::string, std::unordered_set<std::string>> g_zone_bonuses;

void LoadZoneBonuses();
bool ZoneHasBonusType(const std::string& short_name, const std::string& bonus_type);
