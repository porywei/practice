#pragma once

#include <iostream>
#include <unordered_map>
#include <array>
#include <algorithm>
#include "entity.h"

// 地图宽高
#define WIDTH 10
#define HEIGHT 10

// 视野范围 以自己为中心
#define VIEW_WIDTH 1
#define VIEW_HEIGH 1


class Grid {
public:
	Grid(int _x, int _y) {
		x = _x;
		y = _y;
	}

	std::unordered_map<EntityId, Entity*>&
		getEntityList() { return entityList; }

	void addEntity(Entity* e) {
		entityList.emplace(e->getid(), e);
	}

	void removeEntity(Entity* e) {
		entityList.erase(e->getid());
	}

	int getx() { return x; }
	int gety() { return y; }

private:
	std::unordered_map<EntityId, Entity*> entityList;
	int x = 0;
	int y = 0;
};


class Scene {
public:
	Scene();

	void addEntity(Entity* e, int x, int y);
	void removeEntity(Entity* e);

	void clearPlayer();
	void doAllGrid(void(*f)(Grid*));

	void showEntity();

	Grid* getGrid(int x, int y){ return map[y][x]; }
	Player* findPlayer(EntityId);

private:
	std::array<std::array<class Grid*, WIDTH>, HEIGHT> map;
	std::unordered_map<EntityId, Player*> playerlist;
};

