#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include "TileMap.h"
#include "Player.h"
#include "Object.h"
#include "Properties.h"
#include <irrKlang.h>
using namespace irrklang;

// Scene contains all the entities of our game.
// It is responsible for updating and render them.

class Scene {
public:
	Scene();
	~Scene();

	void init(const int& numLvl);
	void update(int deltaTime);

	void endGame();
	void exeDefeat();
	void exeWin();

	void lookProperties();
	bool findIs(pair<int, int> posIni, const pair<int, int>& dir, pair<int, int>& posIs);
	bool checkVerb(pair<int, int> posIs, const pair<int, int>& dir, const string& nameType);
	void addPropertie(const string& verb, const string& name);
	string checkName(pair<int, int> posIni, const pair<int, int>& dir);
	void changeSprite(const string& preSprite, const string& postSprite);
	bool canIMove(pair<int, int> ini, const string& dir, const int& posAnt, const bool& iamPlayer, const bool& isGhost);
	void removeVector(const string& blockType, const int& pos);
	void stopMove(string& dir);

	void render();
	void createOBJ();

	bool getVictory() const { return victory; }

private:
	TileMap* map;
	Player* player;
	Texture spritesheet;
	float currentTime;
	glm::mat4 projection;
	ISoundEngine* engine;

	vector<Object> obj;
	Properties props;

	vector<int> name, op, verb, foreground, background;

	bool disconnected, victory, defeat;
};

#endif // _SCENE_INCLUDE