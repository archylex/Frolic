#include "BackgroundLayer.h"
#include "FrolicUtils.h"

#define NEAR_FIELD_VELOCITY 5
#define FAR_FIELD_VELOCITY 2
#define HERB_VELOCITY 8
#define BUTTERFLY_VELOCITY 70


// Create background layer
BackgroundLayer::BackgroundLayer() 
{
	visibleSize = Director::getInstance()->getVisibleSize();
	isMove = false;
			
	// Sky layer
	Color4B tColor(90, 182, 255, 255);
	Color4B bColor(255, 255, 255, 255);
	auto sky = LayerGradient::create(bColor, tColor);
	sky->setAnchorPoint(Vec2(0.0f, 0.0f));
	sky->setPosition(Vec2(0, visibleSize.height/2));
	sky->setVector(Point(0, 1));
	sky->setScaleY(0.5f);
	this->addChild(sky, 1);
	
	// Mountain	
	auto mountain = Sprite::createWithSpriteFrameName("mountain.png");
	mountain->setAnchorPoint(Vec2(0.5f, 0.0f));
	mountain->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.426f));
	this->addChild(mountain, 3);

	// far field filenames
	string far_field_filename[] = { "far_field_0.png", "far_field_1.png", "far_field_2.png", "far_field_3.png", "far_field_4.png" };
	createField(far_field_filename, x_far_field, 5, 0.214f, far_field, 5);

	// near field filenames
	string near_field_filename[] = { "near_field_0.png", "near_field_1.png", "near_field_2.png", "near_field_3.png", "near_field_4.png" };
	createField(near_field_filename, x_near_field, 5, 0, near_field, 6);

	cloudLayer = new CloudLayer();
	this->addChild(cloudLayer, 2);

	herbLayer = new HerbLayer();
	herbLayer->setScaleRange(75, 110);
	herbLayer->setVelocity(HERB_VELOCITY);
	herbLayer->setStartY(0);
	herbLayer->createHerbs();
	this->addChild(herbLayer, 7);

	// start butterflies
	this->schedule(schedule_selector(BackgroundLayer::createButterfly), 14);
}


void BackgroundLayer::createField(string _f[], float &_x, int _c, float _h, Vector<Sprite*> &_v, int _z)
{
	_x = 0.0f;
	
	for (int x = 0; x < _c; x++)
	{
		auto f1 = Sprite::createWithSpriteFrameName(_f[x]);
		f1->setAnchorPoint(Vec2(0, 0));
		f1->setPosition(Vec2(_x, visibleSize.height * _h));
		this->addChild(f1, _z);

		_v.pushBack(f1);

		_x += f1->getContentSize().width;
	}
}


void BackgroundLayer::setIsMove(bool _is)
{
	isMove = _is;
	herbLayer->setIsMove(_is);
}


void BackgroundLayer::updateFieldPosition(Vector<Sprite*> &_field, float &_x, float _vel)
{
	_x -= _vel;

	for (auto &nf : _field)
	{
		nf->setPosition(Vec2(nf->getPosition().x - _vel, nf->getPosition().y));

		if (nf->getPosition().x + nf->getContentSize().width <= 0)
		{
			nf->setPosition(Vec2(_x, nf->getPosition().y));
			_x += nf->getContentSize().width;
		}
	}
}


void BackgroundLayer::update(float dt) 
{
	if (isMove)
	{
		updateFieldPosition(far_field, x_far_field, FAR_FIELD_VELOCITY);
		updateFieldPosition(near_field, x_near_field, NEAR_FIELD_VELOCITY);
	}

	herbLayer->update(dt);

	cloudLayer->update(dt);

	// butterfly
	if (butterflies.size() > 0)
	{
		for (auto &nextButterfly : butterflies) {
			auto vel_y = rand() % 2;
			vel_y == 0 ? vel_y = -2 : vel_y = 2;
			nextButterfly->setPosition(Vec2(nextButterfly->getPosition().x - BUTTERFLY_VELOCITY * dt, nextButterfly->getPosition().y + vel_y * BUTTERFLY_VELOCITY * dt));

			if (isMove)
				nextButterfly->setPosition(Vec2(nextButterfly->getPosition().x - HERB_VELOCITY, nextButterfly->getPosition().y));

			// Check screen border
			if (nextButterfly->getPosition().x < -nextButterfly->getContentSize().width)
				deleteButterflies.pushBack(nextButterfly);
		}
	}
	
	if (deleteButterflies.size() > 0)
	{
		for (auto &bf : deleteButterflies)
		{
			butterflies.eraseObject(bf);
			this->removeChild(bf);
		}

		deleteButterflies.clear();
	}
}


void BackgroundLayer::pauseAll() {    
	this->unschedule(schedule_selector(BackgroundLayer::createButterfly));
	
	herbLayer->pauseMe();

	for (auto &nextButterfly : butterflies)
	{
		nextButterfly->pause();
	}
}


void BackgroundLayer::resumeAll() {
	this->schedule(schedule_selector(BackgroundLayer::createButterfly), 14);
	
	herbLayer->resumeMe();

	for (auto &nextButterfly : butterflies)
	{
		nextButterfly->resume();
	}
}


void BackgroundLayer::createButterfly(float dt)
{
	auto dframes = AnimationTools::getAnimation("b%03d.png", 1, 6);
	auto danimation = Animation::createWithSpriteFrames(dframes, 0.15f / 6);
	auto fly_d = Animate::create(danimation);

	auto uframes = AnimationTools::getAnimation("b%03d.png", 6, 1);
	auto uanimation = Animation::createWithSpriteFrames(uframes, 0.15f / 6);
	auto fly_u = Animate::create(uanimation);

	auto butterfly = Sprite::createWithSpriteFrame(dframes.front());
	butterfly->setPosition(Vec2(visibleSize.width + butterfly->getContentSize().width, visibleSize.height / 2 + rand() % int(visibleSize.height / 2)));
	auto seq = Sequence::create(fly_d, fly_u, nullptr);
	auto repeat = RepeatForever::create(seq);
	butterfly->runAction(repeat);
	this->addChild(butterfly, 8);

	butterflies.pushBack(butterfly);
}