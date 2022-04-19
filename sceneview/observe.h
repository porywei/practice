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
		printf("%s ������ %s\n", player->getName().c_str(), e->getName().c_str());
		watchlist.emplace(e->getid(), e);
	}

	void eraseWatch(Player* e) {
		printf("%s ������ %s\n", player->getName().c_str(), e->getName().c_str());
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
	std::unordered_map<EntityId, Player*> bewatchlist; // �������б��п���ɾȥ��ʹ��ʱ��ʱ��ȡ
};
