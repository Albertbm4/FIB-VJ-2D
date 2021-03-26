#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Object.h"

static Blocks blocks;

Object::Object() {
	map = NULL;
	sprite = NULL;
}

Object::~Object() {
	if (map != NULL) delete map;
	if (sprite != NULL) delete sprite;
}

void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Texture& spritesheet, const int& id) {
	pair<string, string> b = Blocks::instance().getRef(id);
	tileType = b.first;
	blockType = b.second;

	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(offsetH, offsetV), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((id - 1) % 64) * offsetH, ((id - 1) / 64) * offsetV));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((id - 1) % 64) * offsetH, (1 + (id - 1) / 64) * offsetV));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((id - 1) % 64) * offsetH, (2 + (id - 1) / 64) * offsetV));

	sprite->changeAnimation(2);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x), float(tileMapDispl.y + posObj.y)));
	sprite->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
}

void Object::update(int deltaTime) {
	sprite->update(deltaTime);
	if (objDir == "MOVE_UP") {
		if (posObj.y % 24 != 0) posObj.y -= 2;
		else objDir = "STOP";
	}
	else if (objDir == "MOVE_DOWN") {
		if (posObj.y % 24 != 0) posObj.y += 2;
		else objDir = "STOP";
	}
	else if (objDir == "MOVE_LEFT") {
		if (posObj.x % 24 != 0) posObj.x -= 2;
		else objDir = "STOP";
	}
	else if (objDir == "MOVE_RIGHT") {
		if (posObj.x % 24 != 0) posObj.x += 2;
		else objDir = "STOP";
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x), float(tileMapDispl.y + posObj.y)));
}

void Object::move(const string& dir) {
	if (dir == "MOVE_LEFT") {
		objDir = "MOVE_LEFT";
		posObj.x -= 2;
	}
	else if (dir == "MOVE_RIGHT") {
		objDir = "MOVE_RIGHT";
		posObj.x += 2;
	}
	else if (dir == "MOVE_UP") {
		objDir = "MOVE_UP";
		posObj.y -= 2;
	}
	else if (dir == "MOVE_DOWN") {
		objDir = "MOVE_DOWN";
		posObj.y += 2;
	}
}

void Object::render() {
	sprite->render();
}

void Object::setTileType(const string& p) {
	tileType = p;
}

void Object::setTileMap(TileMap* tileMap) {
	map = tileMap;
}

void Object::setPosition(const glm::vec2& pos) {
	posObj = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObj.x), float(tileMapDispl.y + posObj.y)));
}

void Object::setColor(const glm::vec4& color) {
	sprite->setColor(color);
}