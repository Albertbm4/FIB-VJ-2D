#include "Menu.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Menu::Menu() {
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
	sprite->setPosition(glm::vec2(float(45), float(180)));
	sprite->setColor(glm::vec4(1.f, 1.f, 1.f, 1.f));

	scene1.loadFromFile("images/baba-is-bground.png", TEXTURE_PIXEL_FORMAT_RGB);
	scene2.loadFromFile("images/baba-is-credits.png", TEXTURE_PIXEL_FORMAT_RGB);
}

Menu::~Menu() {
	if (sprite != NULL) delete sprite;
	if (bground != NULL) delete bground;
}

void Menu::init(const int& idScene) {
	id = idScene;
	
	if (id == 0) {
		scene = scene1;
	}
	else if (id == 2) {
		scene = scene2;
	}

	scene.setWrapS(GL_CLAMP_TO_EDGE);
	scene.setWrapT(GL_CLAMP_TO_EDGE);
	scene.setMinFilter(GL_NEAREST);
	scene.setMagFilter(GL_NEAREST);
}

void Menu::update(int deltaTime) {
	currentTime += deltaTime;
	if (id == 0) sprite->update(deltaTime);
}

void Menu::setPosIndex(int pos) {
	if (pos == 0) sprite->setPosition(glm::vec2(float(45), float(180)));
	else if (pos == 1) sprite->setPosition(glm::vec2(float(45), float(250)));
	else if (pos == 2) sprite->setPosition(glm::vec2(float(45), float(320)));
	else if (pos == 3) sprite->setPosition(glm::vec2(float(28), float(385)));
}

void Menu::render() {
	ShaderProgramManager::instance().useShaderProgram();
	bground->render(scene);
	if (id == 0) sprite->render();
}