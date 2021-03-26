#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"

Scene::Scene() {
	map = NULL;
	player = NULL;
	currentTime = 0.f;
	engine = SoundManager::instance().getSoundEngine();
	victory = disconnected = defeat = false;
	Blocks::instance().init();
}

Scene::~Scene() {
	if (map != NULL) delete map;
	if (player != NULL) delete player;
	obj.clear();
	name.clear(); op.clear(); verb.clear(); foreground.clear(); background.clear();
}

void Scene::createOBJ() {
	vector<Entity> ent = map->getEntities();
	obj = vector<Object>(ent.size());
	for (int i = 0; i < int(obj.size()); ++i) {
		obj[i].init(glm::ivec2(0, 0), ShaderProgramManager::instance().getShaderProgram(), spritesheet, ent[i].id);
		obj[i].setPosition(glm::vec2(ent[i].pos[0], ent[i].pos[1]));
		if (obj[i].getBlockType() == "OP") op.push_back(i);
		else if (obj[i].getBlockType() == "NAME") name.push_back(i);
		else if (obj[i].getBlockType() == "VERB") verb.push_back(i);
		else if (obj[i].getBlockType() == "NORMALB") background.push_back(i);
		else foreground.push_back(i);
	}
}

void Scene::init(const int& numLvl) {
	map = TileMap::createTileMap("levels/lvl" + to_string(numLvl) + ".txt", glm::vec2(0, 0), ShaderProgramManager::instance().getShaderProgram());

	spritesheet.loadFromFile("images/baba-is-you.png", TEXTURE_PIXEL_FORMAT_RGBA);

	player = new Player();
	player->init(glm::ivec2(0, 0), ShaderProgramManager::instance().getShaderProgram(), spritesheet);
	player->setPosition(glm::vec2(map->getPosPlayer().x * map->getTileSize(), map->getPosPlayer().y * map->getTileSize()));
	player->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));

	props = Properties::Properties();

	createOBJ();
	currentTime = 0.0f;
}

void Scene::update(int deltaTime) {
	currentTime += deltaTime;

	if (!victory && !defeat) {
		pair<int, int> posP = player->getPos();
		string dir = player->returnDir();
		lookProperties();

		if (!props.can("YOU", "BABA")) {
			if (!disconnected) {
				disconnected = true;
				player->setStop(true);
			}
		}
		else if (disconnected) {
			disconnected = false;
			player->setStop(false);
		}

		for (int i = 0; i < int(obj.size()); ++i) {
			if (props.can("GHOST", obj[i].getTileType())) {
				obj[i].setColor(glm::vec4(0.f, 0.f, 1.f, 1.f));
			}
			else obj[i].setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
		}

		if (props.can("GHOST", "BABA")) player->setColor(glm::vec4(0.f, 0.f, 1.f, 1.f));
		else player->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));

		if (!canIMove(posP, dir, 300000, true, props.can("GHOST", "BABA"))) stopMove(dir);
		player->update(deltaTime, dir);
		for (int i = 0; i < int(obj.size()); ++i) obj[i].update(deltaTime);

		endGame();
		props.deleteProperties();
	}
}

void Scene::endGame() {
	pair<int, int> posP = player->getPos();
	for (int i = 0; i < int(obj.size()); ++i) {
		if (obj[i].getPos() == posP && props.can("GHOST", "BABA") == props.can("GHOST", obj[i].getTileType())) {
			if (props.can("WIN", obj[i].getTileType())) exeWin();
			if (props.can("SINK", obj[i].getTileType()) || props.can("SINK", "BABA")) {
				exeDefeat();
				removeVector(obj[i].getBlockType(), i);
				obj[i].setTileType("none");
			}
			if (props.can("DEFEAT", obj[i].getTileType())) exeDefeat();
		}
	}
}

void Scene::exeDefeat() {
	engine->play2D("sounds/defeat.ogg");
	player->setStop(true);
	defeat = true;
}

void Scene::exeWin() {
	engine->play2D("sounds/victory.ogg");
	player->setStop(true);
	victory = true;
}

void Scene::lookProperties() {
	for (int i = 0; i < int(name.size()); ++i) {
		pair<int, int> posName = obj[name[i]].getPos();

		pair<int, int> posIs;

		//VERTICAL
		bool foundV = findIs({ posName.first, posName.second + 24 }, { 0, 24 }, posIs);
		if (foundV) {
			if (!checkVerb({ posIs.first, posIs.second + 24 }, { 0, 24 }, obj[name[i]].getTileType())) {
				string trans = checkName({ posIs.first, posIs.second + 24 }, { 0, 24 });
				if (trans != "NULL") changeSprite(obj[name[i]].getTileType(), trans);
			}
		}

		//HORIZONTAL
		bool foundH = findIs({ posName.first + 24, posName.second }, { 24, 0 }, posIs);
		if (foundH) {
			if (!checkVerb({ posIs.first + 24, posIs.second }, { 24, 0 }, obj[name[i]].getTileType())) {
				string trans = checkName({ posIs.first + 24, posIs.second }, { 24, 0 });
				if (trans != "NULL") changeSprite(obj[name[i]].getTileType(), trans);
			}
		}
	}
}

bool Scene::findIs(pair<int, int> posIni, const pair<int, int>& dir, pair<int, int>& posIs) {
	for (int i = 0; i < int(op.size()); ++i) {
		pair<int, int> posOp = obj[op[i]].getPos();
		if (posOp == posIni) {
			if (obj[op[i]].getTileType() == "AND") {
				for (int j = 0; j < int(name.size()); ++j) {
					pair<int, int> posName = obj[name[j]].getPos();
					if (posOp.first + dir.first == posName.first && posOp.second + dir.second == posName.second) {
						return findIs({ posName.first + dir.first, posName.second + dir.second }, dir, posIs);
					}
				}
			}
			else if (obj[op[i]].getTileType() == "IS") {
				posIs = posOp;
				return true;
			}
		}
	}
	return false;
}

bool Scene::checkVerb(pair<int, int> posIni, const pair<int, int>& dir, const string& nameType) {
	for (int i = 0; i < int(verb.size()); ++i) {
		pair<int, int> posVerb = obj[verb[i]].getPos();
		if (posIni == posVerb) {
			addPropertie(obj[verb[i]].getTileType(), nameType);
			for (int j = 0; j < int(op.size()); ++j) {
				pair<int, int> posOp = obj[op[j]].getPos();
				if (obj[op[j]].getTileType() == "AND" && posVerb.first + dir.first == posOp.first && posVerb.second + dir.second == posOp.second) {
					checkVerb({ posOp.first + dir.first , posOp.second + dir.second }, dir, nameType);
				}
			}
			return true;
		}
	}
	return false;
}

void Scene::addPropertie(const string& verb, const string& name) {
	string nonWname = name;
	nonWname.pop_back();
	props.setPropertie(verb, nonWname);
}

string Scene::checkName(pair<int, int> posIni, const pair<int, int>& dir) {

	for (int i = 0; i < int(name.size()); ++i) {
		pair<int, int> posName = obj[name[i]].getPos();
		if (posIni == posName) {
			for (int j = 0; j < int(op.size()); ++j) {
				pair<int, int> posOp = obj[op[j]].getPos();
				if (obj[op[j]].getTileType() == "IS" && posName.first + dir.first == posOp.first && posName.second + dir.second == posOp.second) {
					string next = checkName({ posOp.first + dir.first, posOp.second + dir.second }, dir);
					if (next != "NULL") return next;
				}
			}
			return obj[name[i]].getTileType();
		}
	}
	return "NULL";
}

void Scene::changeSprite(const string& preSprite, const string& postSprite) { //change the sprite of a selected block to a desired one
	string nonWnamePre = preSprite;
	nonWnamePre.pop_back();
	for (int i = 0; i < int(obj.size()); ++i) {
		if (obj[i].getTileType() == nonWnamePre) {
			pair<int, int> postPos = obj[i].getPos();
			string nonWnamePost = postSprite;
			nonWnamePost.pop_back();
			int blockId = Blocks::instance().getId(nonWnamePost);
			obj[i].init(glm::ivec2(0, 0), ShaderProgramManager::instance().getShaderProgram(), spritesheet, blockId);
			obj[i].setPosition(glm::vec2(postPos.first, postPos.second));
		}
	}
}

bool Scene::canIMove(pair<int, int> ini, const string& dir, const int& posAnt, const bool& iamPlayer, const bool& isGhost) {
	if (dir == "MOVE_RIGHT") ini.first += 24;
	else if (dir == "MOVE_LEFT") ini.first -= 24;
	else if (dir == "MOVE_UP") ini.second -= 24;
	else if (dir == "MOVE_DOWN") ini.second += 24;
	else return false;

	if (map->collisionMove({ ini.first, ini.second }, glm::ivec2(24, 24), dir)) return false;
	for (int i = 0; i < int(obj.size()); ++i) {
		if (obj[i].getPos() == ini && (props.can("GHOST", obj[i].getTileType()) == isGhost || obj[i].getBlockType() == "VERB"
			|| obj[i].getBlockType() == "NAME"
			|| obj[i].getBlockType() == "OP")) {
			if (props.can("STOP", obj[i].getTileType())) return false;

			if (!iamPlayer && props.can("SINK", obj[i].getTileType())) {
				engine->play2D("sounds/defeat.ogg");
				removeVector(obj[i].getBlockType(), i);
				obj[i].setTileType("none");
				removeVector(obj[posAnt].getBlockType(), posAnt);
				obj[posAnt].setTileType("none");
			}

			if (props.can("PUSH", obj[i].getTileType())) {
				if (!canIMove(ini, dir, i, false, isGhost)) return false;
				else {
					engine->play2D("sounds/move.ogg");
					obj[i].move(dir);
				}
			}
		}
	}
	return true;
}

void Scene::removeVector(const string& blockType, const int& pos) {
	if (blockType == "NORMALB") background.erase(remove(background.begin(), background.end(), pos), background.end());
	else if (blockType == "NORMALF") foreground.erase(remove(foreground.begin(), foreground.end(), pos), foreground.end());
	else if (blockType == "VERB") verb.erase(remove(verb.begin(), verb.end(), pos), verb.end());
	else name.erase(remove(name.begin(), name.end(), pos), name.end());
}

void Scene::stopMove(string& dir) {
	if (dir == "MOVE_RIGHT") dir = "STAND_RIGHT";
	else if (dir == "MOVE_LEFT")  dir = "STAND_LEFT";
	else if (dir == "MOVE_UP")  dir = "STAND_UP";
	else if (dir == "MOVE_DOWN") dir = "STAND_DOWN";
}

void Scene::render() {
	ShaderProgramManager::instance().useShaderProgram();

	map->render();
	for (int i = 0; i < int(background.size()); ++i) obj[background[i]].render();
	for (int i = 0; i < int(foreground.size()); ++i) obj[foreground[i]].render();
	for (int i = 0; i < int(name.size()); ++i) obj[name[i]].render();
	for (int i = 0; i < int(verb.size()); ++i) obj[verb[i]].render();
	for (int i = 0; i < int(op.size()); ++i) obj[op[i]].render();
	if (!defeat) player->render();

	if (victory) Game::instance().nextLevel();
}