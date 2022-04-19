
#include "scene.h"
#include "observe.h"

Scene::Scene() {
	for (int y = 0; y < map.max_size(); ++y) {
		auto& row = map.at(y);
		for (int x = 0; x < row.max_size(); ++x) {
			map[y][x] = new Grid(x, y);
		}
	}
}

void Scene::addEntity(Entity* e, int x, int y) {
	map[y][x]->addEntity(e);

	if (e->getType() == "Player") {
		auto player = static_cast<Player*>(e);
		player->setX(x);
		player->setY(y);
		playerlist.emplace(e->getid(), player);
		player->setScene(this);
		player->initPlayerWatch();
	}
}

void Scene::removeEntity(Entity* e) {
	getGrid(e->getX(), e->getY())->removeEntity(e);
	if (e->getType() == "Player") {
		auto player = static_cast<Player*>(e);
		player->onLeaveScene();
		player->setScene(nullptr);
		playerlist.erase(e->getid());
	}
}

void Scene::clearPlayer() {
	doAllGrid([](Grid* g) {
		auto& list = g->getEntityList();
		if (!list.empty()) {
			std::vector<EntityId> eraseIds;
			for (auto& iter : list) {
				eraseIds.emplace_back(iter.first);
				printf("clear:%s\n", iter.second->getName().c_str());
			}
			for (auto& iter : eraseIds) {
				list.erase(iter);
			}
		}
		});
	for (auto& iter : playerlist) {
		delete iter.second;
	}
	playerlist.clear();
}

void Scene::doAllGrid(void(*f)(Grid*)) {
	for (int y = 0; y < map.max_size(); ++y) {
		auto& row = map.at(y);
		for (int x = 0; x < row.max_size(); ++x) {
			f(row.at(x));
		}
	}
}

void Scene::showEntity() {
	printf("showing========\n");
	doAllGrid([](Grid* g) {
		auto& list = g->getEntityList();
		if (!list.empty()) {
			printf("Grid(%d,%d):", g->getx(), g->gety());
			for (auto iter = list.begin(); iter != list.end(); ++iter) {
				printf("%s ", iter->second->getName().c_str());
			}
			printf("\n");
		}
		});
}

Player* Scene::findPlayer(EntityId playerid) {
	auto iter = playerlist.find(playerid);
	if (iter == playerlist.end()) {
		return nullptr;
	}
	return iter->second;
}


