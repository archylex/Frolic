#include "GoldLayer.h"

#define GOLD_VELOCITY 10

GoldLayer::GoldLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	x_length = 0.0f;

	isMove = false;
	isPause = false;
}


void GoldLayer::createGold(Vec2 _pos)
{
	auto frames = AnimationTools::getAnimation("m%03d.png", 1, 8);
	auto animation = Animation::createWithSpriteFrames(frames, 0.36f / 8);
	gold_animation = Animate::create(animation);
	gold_animation->retain();

	auto gold_item = Sprite::create();
	gold_item->setSpriteFrame(frames.front());
	gold_item->setAnchorPoint(Vec2(0.5f, 0.0f));
	gold_item->setPosition(_pos);
	gold_item->runAction(RepeatForever::create(gold_animation));
	this->addChild(gold_item);

	golds.pushBack(gold_item);
}


void GoldLayer::update(float dt)
{
	if (!isPause)
	{
		if (isMove)
		{
			for (auto &nextGold : golds)
			{
				nextGold->setPosition(Vec2(nextGold->getPosition().x - GOLD_VELOCITY, nextGold->getPosition().y));

				if (nextGold->getPosition().x + nextGold->getContentSize().width < 0)
					del_golds.pushBack(nextGold);
			}

			x_length -= GOLD_VELOCITY;
		}
	}

	if (del_golds.size() > 0)
	{
		for (auto &gold : del_golds)
		{
			auto g = gold;
			golds.eraseObject(g);
			this->removeChild(g, true);
		}

		del_golds.clear();
	}
}


void GoldLayer::deleteGold(Sprite* _s)
{
	del_golds.pushBack(_s);
}


Vector<Sprite*> GoldLayer::getGolds()
{
	return golds;
}


void GoldLayer::setisMove(bool _s)
{
	isMove = _s;
}


void GoldLayer::pauseMe()
{
	isPause = true;

	if (golds.size() > 0)
	{
		for (auto &gold : golds)
		{
			gold->pause();	
		}
	}
}


void GoldLayer::resumeMe()
{
	isPause = false;

	if (golds.size() > 0)
	{
		for (auto &gold : golds)
		{
			gold->resume();
		}
	}
}