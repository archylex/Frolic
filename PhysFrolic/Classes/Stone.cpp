#include "Stone.h"

Stone *Stone::create(string _name)
{
	Stone *_pebble = new Stone();

	if (_pebble && _pebble->initialize(_name)) 
	{
		_pebble->autorelease();
		return _pebble;
	}

	CC_SAFE_DELETE(_pebble);

	return nullptr;
}

bool Stone::initialize(string _name)
{	
	auto spritecache = SpriteFrameCache::getInstance();

	this->setSpriteFrame(spritecache->getSpriteFrameByName(_name));

	this->setAnchorPoint(Vec2(0.5f, 0.0f));

	isTop = false;

	isStart = false;

	return true;
}

void Stone::setTopStone(bool _is)
{
	isTop = _is;
}

void Stone::setStartStone(bool _is)
{
	isStart = _is;
}

bool Stone::isTopStone()
{
	return isTop;
}

bool Stone::isStartStone()
{
	return isStart;
}

