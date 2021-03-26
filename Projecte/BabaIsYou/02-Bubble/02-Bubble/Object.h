#ifndef _OBJECT_INCLUDE
#define _OBJECT_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Blocks.h"

// Object is basically a Sprite that represents an object. 

class Object {

public:
	Object();
	~Object();

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Texture& spritesheet, const int& id);
	void update(int deltaTime);
	void move(const string& dir);
	void render();

	string Object::getTileType() const { return tileType; }
	string Object::getBlockType() const { return blockType; }
	pair<int, int> Object::getPos() const { return { posObj.x, posObj.y }; }

	void setTileType(const string& p);
	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setColor(const glm::vec4& color);

private:
	string objDir;
	glm::ivec2 tileMapDispl, posObj;
	Sprite* sprite;
	TileMap* map;
	string tileType, blockType;
};

#endif // _OBJECT_INCLUDE