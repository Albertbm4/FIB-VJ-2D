#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"

Player::Player() {
	map = NULL;
	sprite = NULL;
	bMoving = bStop = false;
}

Player::~Player() {
	if (map != NULL) delete map;
	if (sprite != NULL) delete sprite;
}

void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Texture& spritesheet) {
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(offsetH, offsetV), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(20);

	sprite->setAnimationSpeed(STAND_LEFT, 10);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(10 * offsetH, 9 * offsetV));

	sprite->setAnimationSpeed(STAND_RIGHT, 10);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0 * offsetH, 9 * offsetV));

	sprite->setAnimationSpeed(STAND_UP, 10);
	sprite->addKeyframe(STAND_UP, glm::vec2(5 * offsetH, 9 * offsetV));

	sprite->setAnimationSpeed(STAND_DOWN, 10);
	sprite->addKeyframe(STAND_DOWN, glm::vec2(15 * offsetH, 9 * offsetV));

	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(11 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(12 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(13 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(14 * offsetH, 9 * offsetV));

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(1 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(4 * offsetH, 9 * offsetV));

	sprite->setAnimationSpeed(MOVE_UP, 10);
	sprite->addKeyframe(MOVE_UP, glm::vec2(6 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_UP, glm::vec2(7 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_UP, glm::vec2(8 * offsetH, 9 * offsetV));
	sprite->addKeyframe(MOVE_UP, glm::vec2(9 * offsetH, 9 * offsetV));

	sprite->setAnimationSpeed(MOVE_DOWN, 10);
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(16 * offsetH, 10 * offsetV));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(17 * offsetH, 10 * offsetV));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(18 * offsetH, 10 * offsetV));
	sprite->addKeyframe(MOVE_DOWN, glm::vec2(19 * offsetH, 9 * offsetV));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

string Player::returnDir() {
	if (!bStop && !bMoving) {
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) return "MOVE_LEFT";
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) return "MOVE_RIGHT";
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) return "MOVE_UP";
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) return "MOVE_DOWN";
		else {
			if (sprite->animation() == MOVE_LEFT)
				return "STAND_LEFT";
			else if (sprite->animation() == MOVE_RIGHT)
				return "STAND_RIGHT";
			else if (sprite->animation() == MOVE_UP)
				return "STAND_UP";
			else if (sprite->animation() == MOVE_DOWN)
				return "STAND_DOWN";
		}
	}
	return "STOP";
}

void Player::update(int deltaTime, const string& dir) {
	sprite->update(deltaTime);
	if (!bMoving) {
		if (!bStop) {
			if (dir == "MOVE_LEFT") {
				if (sprite->animation() != MOVE_LEFT) sprite->changeAnimation(MOVE_LEFT);
				posPlayer.x -= 2;
				bMoving = true;
			}
			else if (dir == "MOVE_RIGHT") {
				if (sprite->animation() != MOVE_RIGHT) sprite->changeAnimation(MOVE_RIGHT);
				posPlayer.x += 2;
				bMoving = true;
			}
			else if (dir == "MOVE_UP") {
				if (sprite->animation() != MOVE_UP)	sprite->changeAnimation(MOVE_UP);
				posPlayer.y -= 2;
				bMoving = true;
			}
			else if (dir == "MOVE_DOWN") {
				if (sprite->animation() != MOVE_DOWN) sprite->changeAnimation(MOVE_DOWN);
				posPlayer.y += 2;
				bMoving = true;
			}
			else {
				bMoving = false;
				if (dir == "STAND_LEFT")
					sprite->changeAnimation(STAND_LEFT);
				else if (dir == "STAND_RIGHT")
					sprite->changeAnimation(STAND_RIGHT);
				else if (dir == "STAND_UP")
					sprite->changeAnimation(STAND_UP);
				else if (dir == "STAND_DOWN")
					sprite->changeAnimation(STAND_DOWN);
			}
		}
		else {
			bMoving = true;
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
			else if (sprite->animation() == MOVE_UP)
				sprite->changeAnimation(STAND_UP);
			else if (sprite->animation() == MOVE_DOWN)
				sprite->changeAnimation(STAND_DOWN);
		}
	}
	else {
		if (sprite->animation() == MOVE_UP) {
			if (posPlayer.y % 24 != 0) posPlayer.y -= 2;
			else bMoving = false;
		}
		else if (sprite->animation() == MOVE_DOWN) {
			if (posPlayer.y % 24 != 0) posPlayer.y += 2;
			else bMoving = false;
		}
		else if (sprite->animation() == MOVE_LEFT) {
			if (posPlayer.x % 24 != 0) posPlayer.x -= 2;
			else bMoving = false;
		}
		else if (sprite->animation() == MOVE_RIGHT) {
			if (posPlayer.x % 24 != 0) posPlayer.x += 2;
			else bMoving = false;
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render() {
	sprite->render();
}

void Player::setTileMap(TileMap* tileMap) {
	map = tileMap;
}

void Player::setPosition(const glm::vec2& pos) {
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::setStop(const bool& b) {
	bStop = b;
}

void Player::setColor(const glm::vec4& color) {
	sprite->setColor(color);
}