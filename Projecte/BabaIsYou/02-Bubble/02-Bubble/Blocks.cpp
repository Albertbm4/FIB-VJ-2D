#include "Blocks.h"

Blocks::~Blocks() {
	blocksRef.clear();
}

void Blocks::init() { // second-> NormalBackground, NormalForeground, OP, Verb, Name
	for (int i = 1; i <= 16; ++i) blocksRef.emplace(i, make_pair("BRICK", "NORMALB"));
	for (int i = 17; i <= 32; ++i) blocksRef.emplace(i, make_pair("RUBBLE", "NORMALB"));
	for (int i = 33; i <= 48; ++i) blocksRef.emplace(i, make_pair("WATER", "NORMALB"));
	for (int i = 49; i <= 64; ++i) blocksRef.emplace(i, make_pair("WALL", "NORMALB"));
	for (int i = 193; i <= 208; ++i) blocksRef.emplace(i, make_pair("ICE", "NORMALB"));
	for (int i = 209; i <= 224; ++i) blocksRef.emplace(i, make_pair("GRASS", "NORMALB"));
	for (int i = 225; i <= 240; ++i) blocksRef.emplace(i, make_pair("LEAVES", "NORMALB"));
	blocksRef.emplace(385, make_pair("AND", "OP")); blocksRef.emplace(386, make_pair("IS", "OP"));
	blocksRef.emplace(387, make_pair("DEFEAT", "VERB")); blocksRef.emplace(388, make_pair("PUSH", "VERB"));
	blocksRef.emplace(389, make_pair("SINK", "VERB")); blocksRef.emplace(390, make_pair("STOP", "VERB"));
	blocksRef.emplace(391, make_pair("WIN", "VERB")); blocksRef.emplace(392, make_pair("YOU", "VERB"));
	blocksRef.emplace(393, make_pair("HOT", "VERB")); blocksRef.emplace(394, make_pair("OPEN", "VERB"));
	blocksRef.emplace(395, make_pair("MOVE", "VERB")); blocksRef.emplace(396, make_pair("ROCKW", "NAME"));
	blocksRef.emplace(397, make_pair("SKULLW", "NAME")); blocksRef.emplace(398, make_pair("SUNW", "NAME"));
	blocksRef.emplace(399, make_pair("WALLW", "NAME")); blocksRef.emplace(400, make_pair("RUBBLEW", "NAME"));
	blocksRef.emplace(401, make_pair("STARW", "NAME")); blocksRef.emplace(402, make_pair("WATERW", "NAME"));
	blocksRef.emplace(403, make_pair("PILARW", "NAME")); blocksRef.emplace(404, make_pair("ROCKETW", "NAME"));
	blocksRef.emplace(405, make_pair("JELLY", "NORMALF")); blocksRef.emplace(406, make_pair("STARFISH", "NORMALF"));
	blocksRef.emplace(407, make_pair("SUN", "NORMALF")); blocksRef.emplace(408, make_pair("ALGAEW", "NAME"));
	blocksRef.emplace(409, make_pair("BAW", "NAME")); blocksRef.emplace(410, make_pair("BABAW", "NAME"));
	blocksRef.emplace(411, make_pair("BOLTW", "NAME")); blocksRef.emplace(412, make_pair("BRICKW", "NAME"));
	blocksRef.emplace(413, make_pair("COGW", "NAME")); blocksRef.emplace(414, make_pair("CRABW", "NAME"));
	blocksRef.emplace(415, make_pair("DOORW", "NAME")); blocksRef.emplace(416, make_pair("SHUT", "VERB"));
	for (int i = 417; i <= 420; ++i) blocksRef.emplace(i, make_pair("SKULL", "NORMALF"));
	for (int i = 425; i <= 428; ++i) blocksRef.emplace(i, make_pair("BOLT", "NORMALF"));
	for (int i = 432; i <= 447; ++i) blocksRef.emplace(i, make_pair("LAVA", "NORMALB"));
	blocksRef.emplace(486, make_pair("BLACK", "NORMALB"));
	blocksRef.emplace(494, make_pair("WHITE", "NORMALB"));
	for (int i = 577; i <= 596; ++i) blocksRef.emplace(i, make_pair("BABA", "NORMALF"));
	blocksRef.emplace(597, make_pair("ALGAE", "NORMALF")); blocksRef.emplace(598, make_pair("DOOR", "NORMALF"));
	blocksRef.emplace(599, make_pair("FLAG", "NORMALF")); blocksRef.emplace(600, make_pair("BFLY", "NORMALB"));
	blocksRef.emplace(601, make_pair("KEY", "NORMALF")); blocksRef.emplace(602, make_pair("LOVE", "NORMALF"));
	blocksRef.emplace(603, make_pair("MOON", "NORMALF")); blocksRef.emplace(604, make_pair("PILAR", "NORMALB"));
	blocksRef.emplace(605, make_pair("ROCK", "NORMALF")); blocksRef.emplace(606, make_pair("STAR", "NORMALF"));
	blocksRef.emplace(607, make_pair("STONE", "NORMALB")); blocksRef.emplace(608, make_pair("FLAGW", "NAME"));
	blocksRef.emplace(609, make_pair("GRASSW", "NAME")); blocksRef.emplace(610, make_pair("ICEW", "NAME"));
	blocksRef.emplace(611, make_pair("MELT", "VERB")); blocksRef.emplace(612, make_pair("JELLYW", "NAME"));
	blocksRef.emplace(613, make_pair("KEKEW", "NAME")); blocksRef.emplace(614, make_pair("KEYW", "NAME"));
	blocksRef.emplace(615, make_pair("LAVAW", "NAME")); blocksRef.emplace(616, make_pair("LOVEW", "NAME"));
	for (int i = 617; i <= 631; ++i) blocksRef.emplace(i, make_pair("CONGRATS", "NAME"));
	for (int i = 769; i <= 788; ++i) blocksRef.emplace(i, make_pair("KEKE", "NORMALF"));
	for (int i = 789; i <= 792; ++i) blocksRef.emplace(i, make_pair("COG", "NORMALF"));
	for (int i = 793; i <= 796; ++i) blocksRef.emplace(i, make_pair("CRAB", "NORMALF"));
	for (int i = 797; i <= 800; ++i) blocksRef.emplace(i, make_pair("ROCKET", "NORMALF"));
	blocksRef.emplace(802, make_pair("GHOST", "VERB"));
	blocksRef.emplace(804, make_pair("GREY", "NORMALB"));
}

pair<string, string> Blocks::getRef(const int& id) {
	//pre: id always exists in the map 
	map<int, pair<string, string>>::iterator it = blocksRef.find(id);
	return it->second;
}

int Blocks::getId(const string& type) {
	map<int, pair<string, string>, int>::iterator it = blocksRef.begin();
	while (it != blocksRef.end()) {
		if (it->second.first == type) return it->first;
		++it;
	}
}