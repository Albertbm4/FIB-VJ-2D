#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <iostream>

Game::~Game() {
	if (menu != NULL) delete menu;
	if (instr != NULL) delete instr;
}

void Game::init() {
	SoundManager::instance().init();
	engine = SoundManager::instance().getSoundEngine();

	ShaderProgramManager::instance().init();

	if (!text.init("fonts/Fishfingers.ttf"))
		cout << "Could not load font!" << endl;

	numView = 0, posIndex = 0, numLevel = 1;
	bPlay = true, start = false, songPlaying = false, isMap = true;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	menu = new Menu();
	menu->init(numView);

	scene = new Scene();
	scene->init(numLevel);

	instr = new Instructions();
	instr->init(0);
	lvlMap = new LevelsMap();
	lvlMap->init();

	irrklang::ISound* sound = engine->play2D("sounds/baba-is-chill.mp3", true, false, true);
	sound->setVolume(0.5f);
}

void Game::nextLevel() {
	delete scene;
	if (numLevel == 6) {
		engine->removeAllSoundSources();
		engine->play2D("sounds/baba-is-galaxy.mp3");
		songPlaying = false;
		numView = 2;
		start = false;
		isMap = false;
		menu->init(numView);
	}
	else isMap = true;
}

bool Game::update(int deltaTime) {
	if (start) {
		if (isMap) lvlMap->update(deltaTime);
		else scene->update(deltaTime);
	}
	else {
		if (numView == 1) instr->update(deltaTime);
		else menu->update(deltaTime);
	}
	return bPlay;
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (start) {
		if (isMap) lvlMap->render();
		else {
			scene->render();
			if (numLevel == 1) text.render("LEVEL 1 - WHERE DO I GO?", glm::vec2(0, 22), 24, glm::vec4(1, 1, 1, 1));
			else if (numLevel == 2) text.render("LEVEL 2 - OUT OF REACH", glm::vec2(0, 22), 24, glm::vec4(1, 1, 1, 1));
			else if (numLevel == 3) text.render("LEVEL 3 - STILL OUT OF REACH", glm::vec2(0, 22), 24, glm::vec4(1, 1, 1, 1));
			else if (numLevel == 4) text.render("LEVEL 4 - ICY WATERS", glm::vec2(0, 22), 24, glm::vec4(1, 1, 1, 1));
			else if (numLevel == 5) text.render("LEVEL 5 - GHOSTS HATE LOVE", glm::vec2(0, 22), 24, glm::vec4(1, 1, 1, 1));
			else if (numLevel == 6) text.render("LEVEL 6 - GHOSTLY OUT OF REACH", glm::vec2(0, 22), 24, glm::vec4(1, 1, 1, 1));
		}
	}
	else {
		if (numView == 1) instr->render();
		else menu->render();
	}
}

void Game::keyPressed(int key) {
	if (key == 27) { // Escape code
		if (numView == 0) bPlay = false;
		else {
			numView = 0;
			start = false;
			isMap = true;
			menu->init(numView);
			menu->setPosIndex(posIndex);
		}
	}

	if (key == 80 || key == 112) engine->setAllSoundsPaused(true); //'P' or 'p' codes to pause songs
	if (key == 85 || key == 117) engine->setAllSoundsPaused(false); //'U' or 'u' codes to unpause songs

	if ((key == 82 || key == 114) && start) { //'R' or 'r' codes to reset level
		delete scene;
		scene = new Scene();
		scene->init(numLevel);
	}

	if ((key == 13 || key == 10) && numView == 1) instr->change(); // CR / LF codes

	if ((key == 13 || key == 10) && start && isMap) {
		numLevel = lvlMap->getPos();
		isMap = false;
		scene = new Scene();
		if (numLevel == 4) glClearColor(0.06f, 0.08f, 0.17f, 1.0f);
		else if (numLevel == 5 || numLevel == 6) glClearColor(0.6f, 0.1f, 0.1f, 1.0f);
		else glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		scene->init(numLevel);
	}

	if ((key == 13 || key == 10) && numView == 0) { // CR/LF codes
		if (posIndex == 0) {
			numView = -1;
			start = true;
			isMap = true;
			if (!songPlaying) {
				engine->removeSoundSource("sounds/baba-is-galaxy.mp3");
				engine->removeSoundSource("sounds/baba-is-chill.mp3");
				irrklang::ISound* sound = engine->play2D("sounds/baba-is-theme.mp3", true, false, true);
				sound->setVolume(0.2f);
				songPlaying = true;
			}
		}
		else if (posIndex == 3) bPlay = false;
		else {
			numView = posIndex;
			if (numView != 1) menu->init(posIndex);
		}
	}
	keys[key] = true;
}

void Game::keyReleased(int key) {
	keys[key] = false;
}

void Game::specialKeyPressed(int key) {
	if (key == GLUT_KEY_DOWN && numView == 0) { //scroll menu down
		++posIndex;
		posIndex = (posIndex) % 4;
		menu->setPosIndex(posIndex);
	}
	if (key == GLUT_KEY_UP && numView == 0) { //scroll menu up
		--posIndex;
		if (posIndex < 0) posIndex = -3 * posIndex;
		posIndex = (posIndex) % 4;
		menu->setPosIndex(posIndex);
	}
	if (key == GLUT_KEY_RIGHT && numView == 1) 
		if (instr->getInstrId() == 1 || instr->getInstrId() == 2) instr->setPosIndex(1);

	if (key == GLUT_KEY_RIGHT && start && isMap) {
		if (lvlMap->getPos() != 0 && lvlMap->getPos() != 7) lvlMap->setPosIndex((lvlMap->getPos()) + 1);
	}
	if (key == GLUT_KEY_LEFT && numView == 1) 
		if (instr->getInstrId() == 1 || instr->getInstrId() == 2) instr->setPosIndex(0);

	if (key == GLUT_KEY_LEFT && start && isMap) {
		if (lvlMap->getPos() != 0 && lvlMap->getPos() != 7) lvlMap->setPosIndex((lvlMap->getPos()) - 1);
	}

	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key) {
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y) {
}

void Game::mousePress(int button) {
}

void Game::mouseRelease(int button) {
}

bool Game::getKey(int key) const {
	return keys[key];
}

bool Game::getSpecialKey(int key) const {
	return specialKeys[key];
}