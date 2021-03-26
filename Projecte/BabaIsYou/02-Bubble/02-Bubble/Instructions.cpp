#include "Instructions.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Instructions::Instructions() {
	thirdSprites = vector<Sprite*>(8);
	id = 0;
	pos = 1;
	currentTime = 0.0f;
	
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(528.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, ShaderProgramManager::instance().getShaderProgram());
	
	spritesheet.loadFromFile("images/baba-is-you.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(float(1.f / 64.f), float(1.f / 16.f)), &spritesheet, &ShaderProgramManager::instance().getShaderProgram());
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE_LEFT, 6);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((577 - 1) % 64) * float(1.f / 64.f), ((577 - 1) / 64) * float(1.f / 16.f)));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((577 - 1) % 64) * float(1.f / 64.f), (1 + (577 - 1) / 64) * float(1.f / 16.f)));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((577 - 1) % 64) * float(1.f / 64.f), (2 + (577 - 1) / 64) * float(1.f / 16.f)));
	sprite->changeAnimation(2);

	scene1.loadFromFile("images/baba-is-instr1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scene2.loadFromFile("images/baba-is-instr2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scene3.loadFromFile("images/baba-is-instr3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scene4.loadFromFile("images/baba-is-instr4.png", TEXTURE_PIXEL_FORMAT_RGBA);

	for (int i = 0; i < 8; ++i) {
		thirdSprites[i] = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(float(1.f / 64.f), float(1.f / 16.f)), &spritesheet, &ShaderProgramManager::instance().getShaderProgram());
		thirdSprites[i]->setNumberAnimations(3);

		thirdSprites[i]->setAnimationSpeed(MOVE_LEFT, 6);
		thirdSprites[i]->addKeyframe(MOVE_LEFT, glm::vec2(((385 + i - 1) % 64) * float(1.f / 64.f), ((385 + i - 1) / 64) * float(1.f / 16.f)));
		thirdSprites[i]->addKeyframe(MOVE_LEFT, glm::vec2(((385 + i - 1) % 64) * float(1.f / 64.f), (1 + (385 + i - 1) / 64) * float(1.f / 16.f)));
		thirdSprites[i]->addKeyframe(MOVE_LEFT, glm::vec2(((385 + i - 1) % 64) * float(1.f / 64.f), (2 + (385 + i - 1) / 64) * float(1.f / 16.f)));
		thirdSprites[i]->changeAnimation(2);
	}

	ghost = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(float(1.f / 64.f), float(1.f / 16.f)), &spritesheet, &ShaderProgramManager::instance().getShaderProgram());
	ghost->setNumberAnimations(3);

	ghost->setAnimationSpeed(MOVE_LEFT, 6);
	ghost->addKeyframe(MOVE_LEFT, glm::vec2(((802 - 1) % 64) * float(1.f / 64.f), ((802 - 1) / 64) * float(1.f / 16.f)));
	ghost->addKeyframe(MOVE_LEFT, glm::vec2(((802 - 1) % 64) * float(1.f / 64.f), (1 + (802 - 1) / 64) * float(1.f / 16.f)));
	ghost->addKeyframe(MOVE_LEFT, glm::vec2(((802 - 1) % 64) * float(1.f / 64.f), (2 + (802 - 1) / 64) * float(1.f / 16.f)));
	ghost->changeAnimation(2);
}

Instructions::~Instructions() {
	if (sprite != NULL) delete sprite;
	if (bground != NULL) delete bground;
}

void Instructions::init(const int& idScene) {
	id = idScene;
	sprite->setColor({1.f, 1.f, 1.f, 1.f});
	if (id == 0) {
		pos = 1;
		sprite->setPosition(glm::vec2(float(245), float(455)));
		scene = scene1;
	}
	else if (id == 1) {
		pos = 0;
		sprite->setPosition(glm::vec2(float(128), float(455)));
		scene = scene2;
	}
	else if (id == 2) {
		pos = 0;
		sprite->setPosition(glm::vec2(float(128), float(455)));
		for (int i = 0; i < 8; ++i) {
			if (i == 0) thirdSprites[i]->setPosition(glm::vec2(float(20), float(93)));
			else if (i == 1) thirdSprites[i]->setPosition(glm::vec2(float(20), float(135)));
			else if (i == 2) thirdSprites[i]->setPosition(glm::vec2(float(20), float(185)));
			else if (i == 3) thirdSprites[i]->setPosition(glm::vec2(float(20), float(227)));
			else if (i == 4) thirdSprites[i]->setPosition(glm::vec2(float(20), float(280)));
			else if (i == 5) thirdSprites[i]->setPosition(glm::vec2(float(20), float(325)));
			else if (i == 6) thirdSprites[i]->setPosition(glm::vec2(float(20), float(367)));
			else if (i == 7) thirdSprites[i]->setPosition(glm::vec2(float(20), float(407)));
			thirdSprites[i]->setColor({ 1.f, 1.f, 1.f, 1.f });
		}
		scene = scene3;
	}
	else if (id == 3) {
		pos = 0;
		sprite->setPosition(glm::vec2(float(128), float(455)));
		ghost->setPosition(glm::vec2(float(20), float(153)));
		ghost->setColor({ 1.f, 1.f, 1.f, 1.f });
		scene = scene4;
	}

	scene.setWrapS(GL_CLAMP_TO_EDGE);
	scene.setWrapT(GL_CLAMP_TO_EDGE);
	scene.setMinFilter(GL_NEAREST);
	scene.setMagFilter(GL_NEAREST);
}

void Instructions::change() {
	if (id == 0) init(1);
	else if (id == 1 && pos == 0) init(0);
	else if (id == 1 && pos == 1) init(2);
	else if (id == 2 && pos == 0) init(1);
	else if (id == 2 && pos == 1) init(3);
	else if (id == 3) init(2);
}

void Instructions::update(int deltaTime) {
	currentTime += deltaTime;
	sprite->update(deltaTime);
	if (id == 2) for (int i = 0; i < 8; ++i) thirdSprites[i]->update(deltaTime);
	if (id == 3) ghost->update(deltaTime);
}

void Instructions::setPosIndex(int posI) {
	if (id == 1 || id == 2) {
		pos = posI;
		if (pos == 0) sprite->setPosition(glm::vec2(float(128), float(455)));
		else sprite->setPosition(glm::vec2(float(245), float(455)));
	}
}

void Instructions::render() {
	ShaderProgramManager::instance().useShaderProgram();
	bground->render(scene);
	sprite->render();
	if (id == 2) for (int i = 0; i < 8; ++i) thirdSprites[i]->render();
	if (id == 3) ghost->render();
}
