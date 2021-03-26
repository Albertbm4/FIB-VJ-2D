#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement and collisions.

class Player {

public:
	Player();
	~Player();

	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Texture& spritesheet);
	void update(int deltaTime, const string& dir);
	string returnDir();
	void render();

	pair<int, int> Player::getPos() const { return { posPlayer.x, posPlayer.y }; }

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	void setStop(const bool& b);
	void setColor(const glm::vec4& color);

private:
	bool bMoving, bStop;
	glm::ivec2 tileMapDispl, posPlayer;
	Sprite* sprite;
	TileMap* map;
};

#endif // _PLAYER_INCLUDE