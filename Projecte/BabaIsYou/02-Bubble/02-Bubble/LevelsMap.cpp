#include "LevelsMap.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

LevelsMap::LevelsMap() {
	pos = 0;
	currentTime = 0.0f;

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(528.f, 480.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, ShaderProgramManager::instance().getShaderProgram());

	spritesheet.loadFromFile("images/baba-is-you.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(24, 24), glm::vec2(float(1.f / 64.f), float(1.f / 16.f)), &spritesheet, &ShaderProgramManager::instance().getShaderProgram());
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE_LEFT, 5);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((494 - 1) % 64) * float(1.f / 64.f), ((494 - 1) / 64) * float(1.f / 16.f)));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((494 - 1) % 64) * float(1.f / 64.f), (1 + (494 - 1) / 64) * float(1.f / 16.f)));  
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(((494 - 1) % 64) * float(1.f / 64.f), (2 + (494 - 1) / 64) * float(1.f / 16.f)));  
	sprite->changeAnimation(2);

	scene.loadFromFile("images/baba-is-map.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

LevelsMap::~LevelsMap() {
	if (sprite != NULL) delete sprite;
	if (bground != NULL) delete bground;
}

void LevelsMap::init() {
	sprite->setColor({ 1.f, 1.f, 1.f, 1.f });
	pos = 1;
	sprite->setPosition(glm::vec2(float(166), float(364)));

	scene.setWrapS(GL_CLAMP_TO_EDGE);
	scene.setWrapT(GL_CLAMP_TO_EDGE);
	scene.setMinFilter(GL_NEAREST);
	scene.setMagFilter(GL_NEAREST);
}

void LevelsMap::setPosIndex(int posI) {
	if (posI > 0 && posI < 7) {
		pos = posI;
		if (pos == 1) sprite->setPosition(glm::vec2(float(166), float(364)));
		else if (pos == 2) sprite->setPosition(glm::vec2(float(194), float(326)));
		else if (pos == 3) sprite->setPosition(glm::vec2(float(284), float(344)));
		else if (pos == 4) sprite->setPosition(glm::vec2(float(249), float(304)));
		else if (pos == 5) sprite->setPosition(glm::vec2(float(349), float(288)));
		else if (pos == 6) sprite->setPosition(glm::vec2(float(366), float(264)));
	}
}

void LevelsMap::update(int deltaTime) {
	currentTime += deltaTime;
	sprite->update(deltaTime);
}

void LevelsMap::render() {
	ShaderProgramManager::instance().useShaderProgram();
	bground->render(scene);
	sprite->render();
}