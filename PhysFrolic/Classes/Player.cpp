#include "Player.h"
#include "AnimationTools.h"


Player *Player::create() {
	Player *_player = new Player();

	if (_player && _player->initialize()) {
		_player->autorelease();
		return _player;
	}

	CC_SAFE_DELETE(_player);

	return nullptr;
}

bool Player::initialize() 
{
	visibleSize = Director::getInstance()->getVisibleSize();

	isPause = false;
	isMoveScreen = false;
	isFalling = false;
				
	// Idle - Wagging tail
	auto wt_frames = AnimationTools::getAnimation("%03d.png", 1, 8); 
	auto wt_animation = Animation::createWithSpriteFrames(wt_frames, 0.8f / 8);
	idle_tail = RepeatForever::create(Animate::create(wt_animation));	
	idle_tail->retain();	
		
	// Idle - Catch tail
	auto ct_frames = AnimationTools::getAnimation("%03d.png", 21, 29);
	auto ct_animation = Animation::createWithSpriteFrames(ct_frames, 0.36f / 9);
	idle_roll = Animate::create(ct_animation);
	idle_roll->retain();

	// Jump animation
	auto j_frames = AnimationTools::getAnimation("%03d.png", 17, 20); 
	auto j_animation = Animation::createWithSpriteFrames(j_frames, 0.2f / 4);
	jump = Animate::create(j_animation);
	jump->retain();
	
	this->setSpriteFrame(wt_frames.front());
	this->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));

	calledWaggingTail(this);	

	return true;
}

void Player::calledWaggingTail(Ref* _sender) {
	this->stopAllActions();

	this->runAction(idle_tail);

	if (!catching_tail)
	{
		this->schedule(schedule_selector(Player::CatchTail), 7.0f);
		catching_tail = true;
	}
}


void Player::JumpAnimation()
{
	this->unschedule(schedule_selector(Player::CatchTail));
	catching_tail = false;

	this->stopAllActions();
	
	FiniteTimeAction *callAct = CallFuncN::create(CC_CALLBACK_1(Player::calledWaggingTail, this));

	auto seq = Sequence::create(jump, callAct, nullptr);
		
	this->runAction(seq);
}

void Player::CatchTail(float dt)
{
	this->stopAllActions();	

	FiniteTimeAction *callAct = CallFuncN::create(CC_CALLBACK_1(Player::calledWaggingTail, this));
	
	auto seq = Sequence::create(idle_roll, idle_roll, callAct, nullptr);
	
	this->runAction(seq);
}

void Player::startForce(float _v, float _a)
{
	vel = _v;
	alfa = _a;
	time = 0.0f;
	start_position = this->getPosition().y;
	started_force = true;

	startedJump = this->getPosition();

	// Jump animation
	auto j_frames = AnimationTools::getAnimation("%03d.png", 9, 11);
	auto j_animation = Animation::createWithSpriteFrames(j_frames, 0.125f / 3);
	startJumpAnimation = Animate::create(j_animation);
	startJumpAnimation->retain();

	this->unschedule(schedule_selector(Player::CatchTail));
	catching_tail = false;

	this->stopAllActions();
	this->runAction(startJumpAnimation);
}

void Player::stopForce()
{
	vel = 0.0f;
	alfa = 0.0f;
	time = 0.0f;
	started_force = false;	
}

bool Player::isStartedForce()
{
	return started_force;
}


void Player::setIsMove(bool _is)
{
	isMoveScreen = _is;
}


void Player::setJumpPhase(float t)
{		
	int num_frame = 0;

	for (int tx = 4; tx <= 8; tx++)
	{
		float c_time = tx / 10.0f;
		if (time / t >= c_time)
		{
			num_frame = tx + 8;
		}
	}

	if (num_frame != 0)
	{
		auto filename = "0" + to_string(num_frame) + ".png";
		this->stopAllActions();
		this->setSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName(filename));
				
	}	
}

void Player::update(float dt)
{
	if (!isPause)
	{
		if (started_force)
		{
			auto t = time;
			auto x = vel * cos(alfa) * t;
			auto y = vel * sin(alfa) * t - (10 * pow(t, 2) / 2);
			
			this->setPosition(startedJump.x + x, startedJump.y + y);

			time += 0.3f;
		}
		else {
			stopForce();
		}

		// falling down
		if (isFalling)
			this->setPosition(this->getPosition().x, this->getPosition().y - visibleSize.height * 0.02f);

		if (isMoveScreen)
			this->setPosition(Vec2(this->getPosition().x - 10, this->getPosition().y));
	}
}


void Player::startLeftFall()
{
	auto a_frames = AnimationTools::getAnimation("%03d.png", 17, 19);
	auto a_animation = Animation::createWithSpriteFrames(a_frames, 0.12f / 3);
	auto land_animation = Animate::create(a_animation);
	land_animation->retain();

	auto f_frames = AnimationTools::getAnimation("%03d.png", 30, 30);
	auto f_animation = Animation::createWithSpriteFrames(f_frames, 0.125f);
	auto fall_animation = Animate::create(f_animation);
	land_animation->retain();

	auto mv = MoveBy::create(0, Vec2(0, -this->getContentSize().height * 0.3f));

	auto seq = Sequence::create(land_animation, mv, fall_animation, nullptr);
	
	stopForce();

	isFalling = true;

	this->stopAllActions();
	this->runAction(seq);
}


void Player::stopLeftFall()
{
	isFalling = false;
}


void Player::resumeMe()
{
	isPause = false;
	this->resume();
}


void Player::pauseMe()
{
	isPause = true;
	this->pause();
}


float Player::getTime()
{
	return time;
}