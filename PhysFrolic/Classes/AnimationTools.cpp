#include "AnimationTools.h"
#include "FrolicUtils.h"

Vector<SpriteFrame*> AnimationTools::getAnimation(const char *format, int start, int count) 
{
	auto spritecache = SpriteFrameCache::getInstance();

	Vector<SpriteFrame*> animFrames;
	char str[100];
	int delta = 1;

	(count - start > 0) ? delta = 1 : delta = -1;
	
	for (int i = delta * start; i <= delta * count; i++)
	{
		sprintf(str, format, abs(i));
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}

RepeatForever* AnimationTools::getRotateAnimation()
{
	auto tm = FrolicUtils::randomF(60, 80) / 60.0f;
	auto rotateToOne = RotateBy::create(tm/2, 5.0f);
	auto rotateToTwo = RotateBy::create(tm, -5.0f);
	auto delay = DelayTime::create(0.15f);
	auto e1 = EaseIn::create(rotateToOne, tm / 2);
	auto e2 = EaseOut::create(rotateToTwo, tm);
	auto seq = Sequence::create(e1, delay, e2, nullptr);

	auto rotate_action = RepeatForever::create(seq);

	return rotate_action;
}
