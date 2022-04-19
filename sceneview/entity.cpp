
#include "entity.h"
#include "observe.h"
#include "scene.h"

static EntityId createPlayerId() {
	static EntityId a = 1;
	return a++;
}

static EntityId createMonsterId() {
	static EntityId a = 101;
	return a++;
}

Player::Player() {
	oblist = new OBServe(this);
}

Player::~Player() {
	delete oblist;
}

EntityId Player::createId() {
	return createPlayerId();
};

void Player::initPlayerWatch() {
	oblist->clear();

	int x = getX();
	int y = getY();

	int xmin = std::max(0, x - VIEW_WIDTH);
	int xmax = std::min(WIDTH - 1, x + VIEW_WIDTH);
	int ymin = std::max(0, y - VIEW_HEIGH);
	int ymax = std::min(HEIGHT - 1, y + VIEW_HEIGH);

	for (int pointx = xmin; pointx <= xmax; ++pointx) {
		for (int pointy = ymin; pointy <= ymax; ++pointy) {
			auto grid = scene->getGrid(pointx, pointy);
			auto& list = grid->getEntityList();
			for (auto& iter : list) {
				if (iter.second->getType() == "Player" && iter.first != getid()) {
					auto otherplayer = static_cast<Player*>(iter.second);
					oblist->addWatch(otherplayer);
					oblist->addBeWatch(otherplayer);
					otherplayer->getOblist()->addWatch(this);
					otherplayer->getOblist()->addBeWatch(this);
				}
			}
		}
	}
}

void Player::onLeaveScene() {
	auto& list = oblist->getBeWatchList();
	for (auto& iter : list) {
		auto otherplayer = scene->findPlayer(iter.first);
		if (otherplayer) {
			otherplayer->getOblist()->eraseWatch(this);
			otherplayer->getOblist()->eraseWatch(this);
		}
	}
}

void Player::onMove(int tx, int ty) {
	int x = getX();
	int y = getY();

	if (x == tx && y == ty) {
		return;
	}
	if (tx < 0 || tx >= WIDTH || ty < 0 || ty >= HEIGHT){
		return;
	}

	// 一次只能移动一格 四方向
	if (tx == x && abs(ty - y) == 1) {
		moveY(ty);
	}
	else if (ty == y && abs(tx - x) == 1) {
		moveX(tx);
	}
	else{
		printf("error move:(%d %d)-> (%d %d)\n", x, y, tx, ty);
		return;
	}
}

void Player::moveX(int tx) {
	int x = getX();
	int y = getY();

	{
	// 移除旧视野
		int w = tx > x ? x - VIEW_WIDTH : x + VIEW_WIDTH;
		if (w >= 0 && w < WIDTH) {
			for (int h = y - VIEW_HEIGH; h <= y + VIEW_HEIGH; ++h) {
				if (h < 0 || h >= HEIGHT) {
					continue;
				}
				auto grid = scene->getGrid(w, h);
				auto& list = grid->getEntityList();
				for (auto& iter : list) {
					if (iter.second->getType() == "Player") {
						auto otherplayer = static_cast<Player*>(iter.second);
						otherplayer->getOblist()->eraseWatch(this);
						otherplayer->getOblist()->eraseBeWatch(this);

						oblist->eraseWatch(otherplayer);
						oblist->eraseBeWatch(otherplayer);
					}
				}
			}
		}
	}
	{
	// 添加新视野
		int w = tx > x? tx + VIEW_WIDTH : tx - VIEW_WIDTH;
		if (w >= 0 && w < WIDTH) {
			for (int h = y - VIEW_HEIGH; h <= y + VIEW_HEIGH; ++h) {
				if (h < 0 || h >= HEIGHT) {
					continue;
				}
				auto grid = scene->getGrid(w, h);
				auto& list = grid->getEntityList();
				for (auto& iter : list) {
					if (iter.second->getType() == "Player") {
						auto otherplayer = static_cast<Player*>(iter.second);
						otherplayer->getOblist()->addBeWatch(this);
						otherplayer->getOblist()->addWatch(this);

						oblist->addBeWatch(otherplayer);
						oblist->addWatch(otherplayer);
					}
				}
			}
		}
	}

	auto grid = scene->getGrid(x, y);
	grid->removeEntity(this);

	auto newgrid = scene->getGrid(tx, y);
	newgrid->addEntity(this);

	this->setX(tx);
}

void Player::moveY(int ty) {
	int x = getX();
	int y = getY();

	{
		// 移除旧视野
		int h = ty > y ? y - VIEW_HEIGH : y + VIEW_HEIGH;
		if (h >= 0 && h < HEIGHT) {
			for (int w = x - VIEW_WIDTH; w <= x + VIEW_WIDTH; ++w) {
				if (w < 0 || w >= WIDTH) {
					continue;
				}
				auto grid = scene->getGrid(w, h);
				auto& list = grid->getEntityList();
				for (auto& iter : list) {
					if (iter.second->getType() == "Player") {
						auto otherplayer = static_cast<Player*>(iter.second);
						otherplayer->getOblist()->eraseWatch(this);
						otherplayer->getOblist()->eraseBeWatch(this);

						oblist->eraseWatch(otherplayer);
						oblist->eraseBeWatch(otherplayer);
					}
				}
			}
		}
	}
	{
		// 添加新视野
		int h = ty > y ? ty + VIEW_HEIGH : ty - VIEW_HEIGH;
		if (h >= 0 && h < HEIGHT) {
			for (int w = x - VIEW_WIDTH; w <= x + VIEW_WIDTH; ++w) {
				if (w < 0 || w >= WIDTH) {
					continue;
				}
				auto grid = scene->getGrid(w, h);
				auto& list = grid->getEntityList();
				for (auto& iter : list) {
					if (iter.second->getType() == "Player") {
						auto otherplayer = static_cast<Player*>(iter.second);
						otherplayer->getOblist()->addBeWatch(this);
						otherplayer->getOblist()->addWatch(this);

						oblist->addBeWatch(otherplayer);
						oblist->addWatch(otherplayer);
					}
				}
			}
		}
	}

	auto grid = scene->getGrid(x, y);
	grid->removeEntity(this);

	auto newgrid = scene->getGrid(x, ty);
	newgrid->addEntity(this);

	this->setY(ty);
}

