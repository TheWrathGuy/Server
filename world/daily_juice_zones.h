#ifndef DAILY_JUICE_ZONES_H
#define DAILY_JUICE_ZONES_H

#include <map>
#include <vector>
#include <string>

enum class LevelBracket {
	Bracket_1_10,
	Bracket_11_20,
	Bracket_21_30,
	Bracket_31_40,
	Bracket_41_50,
	Bracket_51_60,
	Bracket_61_65,
	Unknown
};

struct ZoneInfo {
	int zone_id;
	std::string short_name;
	LevelBracket bracket;
};

class DailyJuiceZones {
public:
	bool Load();
	const std::map<LevelBracket, std::vector<ZoneInfo>>& GetZonesByBracket() const;

private:
	std::map<LevelBracket, std::vector<ZoneInfo>> zones_by_bracket_;
};

#endif
