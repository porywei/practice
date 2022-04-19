#pragma once

#include <unordered_map>
#include "entity.h"

class Player;
class OBServe {
public:
	OBServe(Player* me) {player = me;}

	void clear() {
		clearWatch();
		clearBeWatch();
	}
	void clearWatch() {
		watchlist.clear();
	}
	void clearBeWatch() {
		bewatchlist.clear();
	}

	std::unordered_map<EntityId, Player*>&
	getWatchList() {
		return watchlist;
	}

	std::unordered_map<EntityId, Player*>&
		getBeWatchList() {
		return bewatchlist;
	}

	void addWatch(Player* e) {
		printf("%s 看见了 %s\n", player->getName().c_str(), e->getName().c_str());
		watchlist.emplace(e->getid(), e);
	}

	void eraseWatch(Player* e) {
		printf("%s 看不见 %s\n", player->getName().c_str(), e->getName().c_str());
		watchlist.erase(e->getid());
	}

	void addBeWatch(Player* e) {
		bewatchlist.emplace(e->getid(), e);
	}

	void eraseBeWatch(Player* e) {
		bewatchlist.erase(e->getid());
	}

private:
	Player* player;
	std::unordered_map<EntityId, Player*> watchlist;
	std::unordered_map<EntityId, Player*> bewatchlist; // 被看见列表，有考虑删去，使用时候及时获取
};
