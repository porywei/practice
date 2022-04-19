
// 此demo用作练习场景进出和场景内移动时候的视野同步策略,仅个人练习测试用
// author: wei
// ide:vs2019


#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <utility>
#include <string>
#include "entity.h"
#include "scene.h"

int main() {
	auto scene = new Scene();

// 测试数据
typedef std::pair<int, int> pp;
	std::vector<pp > v{
		pp(0, 0),
		pp(2, 2),
		pp(1, 4),
		pp(4, 2),
		pp(5, 3)
	};

	Player* me = nullptr;

	static int c = 0;
	for (auto iter = v.begin(); iter != v.end(); ++iter) {
		Entity*e = new Player();
		std::string name = "wei" + std::to_string(++c);
		e->setid(e->createId());
		e->setName(name);
		e->setX(iter->first);
		e->setY(iter->second);
		scene->addEntity(e, iter->first, iter->second);

		if (!me) {
			me = static_cast<Player*>(e);
		}
	}
	scene->showEntity();
	printf("=======================================\n");
	std::vector<pp > step{
		pp(1, 0),
		pp(0, 1),
		pp(1, 0),
		pp(1, 0),
		pp(1, 0),
		pp(1, 0),
		pp(1, 0),
		pp(0, 1),
		pp(0, 1),
		pp(-1, 0),
	};

	for (auto& iter : step) {
		int x = me->getX();
		int y = me->getY();
		printf("moving:(%d,%d)->(%d,%d)\n", x, y, x + iter.first, y + iter.second);
		me->onMove(x + iter.first, y + iter.second);
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	printf("leaving\n");
	scene->removeEntity(me);
	std::this_thread::sleep_for(std::chrono::seconds(5));

	printf("add to 1,1\n");
	scene->addEntity(me, 1, 1);
	printf("leaving\n");
	scene->removeEntity(me);

	std::this_thread::sleep_for(std::chrono::seconds(5));
	printf("add to 2,3\n");
	scene->addEntity(me, 2, 3);

	printf("clear|\n");
	scene->clearPlayer();
	me = nullptr;
	return 0;
}
