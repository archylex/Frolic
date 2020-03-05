#include "ForegroundLayer.h"

#define HERB_VELOCITY 20

ForegroundLayer::ForegroundLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	Color4B tbColor(0, 0, 0, 128);
	Color4B tColor(0, 0, 0, 0);
	Color4B bColor(0, 0, 0, 255);

	// Herbs
	herbLayer = new HerbLayer();
	herbLayer->setScaleRange(100, 125);
	herbLayer->setVelocity(HERB_VELOCITY);
	herbLayer->setStartY(visibleSize.height * -0.2f);
	herbLayer->createHerbs();
	this->addChild(herbLayer, 1);

	// top
	auto top = LayerGradient::create(tColor, tbColor);
	top->setAnchorPoint(Vec2(0.0f, 1.0f));
	top->setPosition(Vec2(0, 0));
	top->setVector(Point(0, 1));
	top->setScaleY(0.07f);
	this->addChild(top, 2);

	// bottom	
	auto bottom = LayerGradient::create(bColor, tColor);
	bottom->setAnchorPoint(Vec2(0.0f, 0.0f));
	bottom->setPosition(Vec2(0, 0));
	bottom->setVector(Point(0, 1));
	bottom->setScaleY(0.25f);
	this->addChild(bottom, 2);	
}


void ForegroundLayer::update(float dt)
{
	herbLayer->update(dt);
}


void ForegroundLayer::setIsMove(bool _is)
{
	herbLayer->setIsMove(_is);
}


void ForegroundLayer::pauseMe()
{
	herbLayer->pauseMe();
}

void ForegroundLayer::resumeMe()
{
	herbLayer->resumeMe();
}