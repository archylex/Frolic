#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Player : public Sprite
{
public:
	static Player *create();
	virtual void update(float dt);
	void JumpAnimation();
	void CatchTail(float dt);
	void calledWaggingTail(Ref* _sender);
	void startForce(float _v, float _a);
	void stopForce();
	bool isStartedForce();
	void setJumpPhase(float t);
	void setIsMove(bool _is);
	void pauseMe();
	void resumeMe();
	void startLeftFall();
	void stopLeftFall();
	float getTime();

private:
	bool initialize();
	Size visibleSize;
	Animate *idle_roll;
	Action *idle_tail;
	Animate *jump;
	Animate *startJumpAnimation;
	bool catching_tail;
	float time;
	float vel;
	float alfa;
	bool started_force;
	float start_position;
	Vec2 startedJump;
	bool isMoveScreen;
	bool isPause;
	bool isFalling;
};

#endif // !PLAYER_H