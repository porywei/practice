#pragma once

#include <iostream>
#include <chrono>


class Scene;
class OBServe;
typedef uint64_t EntityId;



class Entity {
public:
	virtual ~Entity(){};
	virtual EntityId getid() {return _id;}
	virtual EntityId createId() = 0;
	virtual std::string getType() = 0;
	virtual void setid(EntityId id) {_id = id;}
	virtual int getX() {return x;}
	virtual int getY() {return y;}
	virtual void setX(int _x) {x = _x;}
	virtual void setY(int _y) { y = _y;}
	virtual std::string& getName() {return name;}
	virtual void setName(std::string& n) {name = n;}
private:
	EntityId _id;
	int x = 0;
	int y = 0;
	std::string name;
};


class Player : public Entity {
public:
	Player();
	virtual ~Player();
	EntityId createId() override;
	std::string getType() override {
		return "Player";
	}
	OBServe* getOblist() {
		return oblist;
	}
	void setScene(Scene* s) {scene = s;}
	void initPlayerWatch();
	void onLeaveScene();
	void onMove(int tx, int ty);

private:
	void moveX(int tx);
	void moveY(int ty);

private:
	OBServe* oblist;
	Scene* scene = nullptr;
};

//class Monster : public Entity {
//public:
//	EntityId createId() override {
//		return createMonsterId();
//	};
//	std::string getType() override {
//		return "Monster";
//	}
//};




