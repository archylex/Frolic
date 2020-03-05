#include "CloudLayer.h"
#include "FrolicUtils.h"

#define CLOUD_VELOCITY 20

CloudLayer::CloudLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	last_pos = 0.0f;

	for (int a = 0; a < 12; a++)
	{
		createCloud();
	}
}


void CloudLayer::update(float dt)
{
	last_pos -= CLOUD_VELOCITY * dt;

	if (clouds.size() > 0) {
		for (auto &nextCloud : clouds) 
		{
			nextCloud->setPosition(nextCloud->getPosition().x - CLOUD_VELOCITY * dt, nextCloud->getPosition().y);

			// Check screen border
			if (nextCloud->getPosition().x < -nextCloud->getContentSize().width)
				del_clouds.pushBack(nextCloud);
		}
	}

	if (del_clouds.size() > 0)
	{
		for (auto &nextCloud : del_clouds)
		{
			clouds.eraseObject(nextCloud);
			this->removeChild(nextCloud, true);
			createCloud();
		}

		del_clouds.clear();
	}
}


void CloudLayer::createCloud()
{
	string name[] = { "c001.png", "c002.png", "c003.png" };
	int rn = rand() % int(sizeof(name) / sizeof(*name));
	float sc = FrolicUtils::randomF(75, 105) / 100.0f;

	auto cloud = Sprite::createWithSpriteFrameName(name[rn]);
	cloud->setScale(sc);
	cloud->setPosition(Vec2(last_pos, FrolicUtils::randomF(visibleSize.height * 0.76f, visibleSize.height)));
	this->addChild(cloud, 1);

	clouds.pushBack(cloud);

	last_pos += cloud->getContentSize().width / 2 + FrolicUtils::randomF(visibleSize.width / 10,  visibleSize.width / 4);
}