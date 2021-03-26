#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE

#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include <vector>

// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format. With this information it builds a single VBO that contains all tiles. 
// As a result the render method draws the whole map independently of what is visible.

struct Entity {
	int id;
	glm::ivec2 pos;
};

#define offsetH 1.f / 64.f
#define offsetV 1.f / 16.f

class TileMap {
public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap* createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

	TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);
	~TileMap();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }
	glm::ivec2 getPosPlayer() const { return posPlayer; }
	vector<Entity> TileMap::getEntities() const { return entColl; }

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collisionMove(const glm::ivec2& pos, const glm::ivec2& size, const string& dir) const;

private:
	bool loadLevel(const string& levelFile);
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize, posPlayer;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int* map;
	vector<Entity> entColl;
};

#endif // _TILE_MAP_INCLUDE