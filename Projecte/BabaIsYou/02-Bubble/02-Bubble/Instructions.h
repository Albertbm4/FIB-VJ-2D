#ifndef _INSTRUCTIONS_INCLUDE
#define _INSTRUCTIONS_INCLUDE

#include "ShaderProgramManager.h"
#include <vector>
#include <glm/glm.hpp>
#include "TexturedQuad.h"
#include "Sprite.h"

class Instructions {
public:
	Instructions();
	~Instructions();

	void init(const int& idScene);
	void change();
	void render();
	void update(int deltaTime);
	void setPosIndex(int pos);
	int getInstrId() const { return id; }

private:
	int pos, id;
	Sprite* sprite, *ghost;
	vector<Sprite*> thirdSprites;
	float currentTime;
	Texture spritesheet;
	TexturedQuad* bground;
	glm::mat4 projection;
	Texture scene, scene1, scene2, scene3, scene4;
};

#endif // _INSTRUCTIONS_INCLUDE