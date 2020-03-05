#include "MenuLayer.h"
#include "FrolicArcade.h"
#include "TitleScene.h"
#include "FrolicUtils.h"
#include "FrolicEdu.h"


MenuLayer::MenuLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	auto fadeBGNode = DrawNode::create();
	Vec2 fadeBG[] = { Vec2(0, 0), Vec2(0, visibleSize.height), Vec2(visibleSize.width, visibleSize.height), Vec2(visibleSize.width, 0) };
	Color4F aBlack(0.0f, 0.0f, 0.0f, 0.5f);
	fadeBGNode->drawPolygon(fadeBG, 4, aBlack, 0, aBlack);
	this->addChild(fadeBGNode);

	movingButtons = new MovingButton();
	movingButtons->setStartAngle(0);
	movingButtons->setBetaAngle(90);
	movingButtons->setSpiralRadius(visibleSize.height * 0.07f);
	movingButtons->setStartPosition(Vec2(0, visibleSize.height / 2));

	movingButtons->addButton("menu_home.png", true, [&]() {
		auto scale_anim = ScaleTo::create(1.5f, 0.0f);
		pic_logo->runAction(scale_anim);
	}, [&]() {
		auto scene = TitleScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(255, 255, 255)));
	});

	string my_name;
	UserDefault::getInstance()->getBoolForKey("MUSIC", true) ? my_name = "menu_music_on.png" : my_name = "menu_music_off.png";

	movingButtons->addButton(my_name, false, [&]() {
		if (UserDefault::getInstance()->getBoolForKey("MUSIC", true))
		{
			UserDefault::getInstance()->setBoolForKey("MUSIC", false);
			UserDefault::getInstance()->flush();
			movingButtons->setChangePicName("menu_music_off.png");
		}
		else {
			UserDefault::getInstance()->setBoolForKey("MUSIC", true);
			UserDefault::getInstance()->flush();
			movingButtons->setChangePicName("menu_music_on.png");
		}
	}, nullptr);

	movingButtons->addButton("menu_play.png", true, [&]() {
		auto scale_anim = ScaleTo::create(1.5f, 0.0f);
		pic_logo->runAction(scale_anim);
	}, [&]() {
		if (UserDefault::getInstance()->getBoolForKey("ARCADE", true))
		{
			FrolicArcade *game = (FrolicArcade*)this->getParent();
			game->resumeGame();
		}
		else {
			FrolicEdu *game = (FrolicEdu*)this->getParent();
			game->resumeGame();
		}

		this->removeFromParentAndCleanup(true);
	});
	
	UserDefault::getInstance()->getBoolForKey("SFX", true) ? my_name = "menu_sound_on.png" : my_name = "menu_sound_off.png";

	movingButtons->addButton(my_name, false, [&]() {
		if (UserDefault::getInstance()->getBoolForKey("SFX", true))
		{
			UserDefault::getInstance()->setBoolForKey("SFX", false);
			UserDefault::getInstance()->flush();
			movingButtons->setChangePicName("menu_sound_off.png");
		}
		else {
			UserDefault::getInstance()->setBoolForKey("SFX", true);
			UserDefault::getInstance()->flush();
			movingButtons->setChangePicName("menu_sound_on.png");
		}
	}, nullptr);

	this->addChild(movingButtons, 5);

	movingButtons->start();	

	// center pic
	pic_logo = Sprite::createWithSpriteFrameName("menu_pause.png");
	pic_logo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));	
	pic_logo->setScale(0);
	this->addChild(pic_logo, 5);
	
	auto scale_anim = ScaleTo::create(1.5f, 1.0f);
	pic_logo->runAction(scale_anim);
}


void MenuLayer::update(float dt)
{
	movingButtons->update(dt);
}