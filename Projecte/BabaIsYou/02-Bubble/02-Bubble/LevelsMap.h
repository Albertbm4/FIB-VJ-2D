#ifndef _LEVELS_MAP_INCLUDE
#define _LEVELS_MAP_INCLUDE

#include "ShaderProgramManager.h"
#include <vector>
#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"

class LevelsMap {
public:
	LevelsMap();
	~LevelsMap();

	void init();
	void render();
	void update(int deltaTime);
	void setPosIndex(int posI);

	int getPos() const { return pos; }

private:
	int pos;
	Sprite* sprite;
	float currentTime;
	Texture spritesheet;
	TexturedQuad* bground;
	glm::mat4 projection;
	Texture scene;
};

#endif // _LEVELS_MAP_INCLUDE
