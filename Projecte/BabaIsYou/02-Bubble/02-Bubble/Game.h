#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Scene.h"
#include "Menu.h"
#include "Instructions.h"
#include "LevelsMap.h"
#include "SoundManager.h"
#include "Text.h"

#define SCREEN_WIDTH 528
#define SCREEN_HEIGHT 480

// Game is a singleton (a class with a single instance) that represents our whole application

class Game {

public:
	Game() {};
	~Game();
	static Game& instance() {
		static Game G;
		return G;
	}

	void init();
	void nextLevel();
	bool update(int deltaTime);
	void render();

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	Text text;
	ISoundEngine* engine;
	Menu* menu;
	Instructions* instr;
	LevelsMap* lvlMap;
	Scene* scene;                      // Scene to render
	int numLevel, numView, posIndex;
	bool bPlay, start, songPlaying, isMap; // Continue to play game?
	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time
};

#endif // _GAME_INCLUDE