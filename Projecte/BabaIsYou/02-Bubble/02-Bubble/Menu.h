#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "ShaderProgramManager.h"
#include <vector>
#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"

class Menu {
public:
	Menu();
	~Menu();

	void init(const int& idScene);
	void render();
	void update(int deltaTime);
	void setPosIndex(int pos);

private:
	int id;
	Sprite* sprite;
	float currentTime;
	Texture spritesheet;
	TexturedQuad* bground;
	glm::mat4 projection;
	Texture scene, scene1, scene2;
};

#endif // _MENU_INCLUDE