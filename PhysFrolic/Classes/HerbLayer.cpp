#include "HerbLayer.h"
#include "FrolicUtils.h"

#define MUSHROOM 7

HerbLayer::HerbLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	isMove = false;
	isPause = false;
	last_pos = 0.0f;
	velocity = 0.0f;
	min_scale = 0.0f;
	max_scale = 0.0f;
	startY = 0.0f;	
}


void HerbLayer::update(float dt)
{
	if (isMove)
	{
		last_pos -= velocity;

		for (auto &nextHerb : herbs)
		{
			nextHerb->setPosition(Vec2(nextHerb->getPosition().x - velocity, nextHerb->getPosition().y));

			if (nextHerb->getPosition().x + nextHerb->getContentSize().width / 2 <= 0)
				del_herbs.pushBack(nextHerb);
		}
	}
	
	if (del_herbs.size() > 0)
	{
		for (auto &herb : del_herbs)
		{
			herbs.eraseObject(herb);
			this->removeChild(herb);
			createHerb();
		}

		del_herbs.clear();
	}
}


void HerbLayer::setIsMove(bool _is)
{
	isMove = _is;
}


void HerbLayer::pauseMe()
{
	isPause = true;

	for (auto &nextHerb : herbs)
	{
		nextHerb->pause();
	}
}

void HerbLayer::resumeMe()
{
	isPause = false;

	for (auto &nextHerb : herbs)
	{
		nextHerb->resume();
	}
}

void HerbLayer::createHerb()
{
	string name[] = { "i000.png", "i001.png", "i002.png", "i003.png", "i004.png", "i005.png", "i006.png", "i007.png", "i008.png", "i009.png" };
	int rn = rand() % int(sizeof(name) / sizeof(*name));
	float sc = FrolicUtils::randomF(min_scale, max_scale) / 100.0f;
	auto *herb = Sprite::createWithSpriteFrameName(name[rn]);
	herb->setAnchorPoint(Vec2(0.5f, 0.0f));
	herb->setPosition(Vec2(last_pos, startY));
	herb->setScale(sc);
	this->addChild(herb, 1);
	herbs.pushBack(herb);

	last_pos += herb->getContentSize().width/2;

	if (rn != MUSHROOM)
	{
		auto rotate_action = AnimationTools::getRotateAnimation();
		herb->runAction(rotate_action);
	}
}


void HerbLayer::createHerbs()
{
	for (int a = 0; a < 12; a++)
	{
		createHerb();
	}
}


void HerbLayer::setScaleRange(float _min, float _max)
{
	min_scale = _min;
	max_scale = _max;
}


void HerbLayer::setStartY(float _y)
{
	startY = _y;
}


void HerbLayer::setVelocity(float _v)
{
	velocity = _v;
}



