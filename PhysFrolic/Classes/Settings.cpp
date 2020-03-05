#include "Settings.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "FrolicUtils.h"


Settings::Settings() {
    // Screen size
    visibleSize = Director::getInstance()->getVisibleSize();

	// Buttons
	movingButtons = new MovingButton();
	movingButtons->setStartAngle(0);
	movingButtons->setBetaAngle(90);
	movingButtons->setSpiralRadius(visibleSize.height * 0.07f);
	movingButtons->setStartPosition(Vec2(0, visibleSize.height / 2));

	movingButtons->addButton("menu_home.png", true, [&]() {
		auto scale_anim = ScaleTo::create(1.5f, 0.0f);
		pic_logo->runAction(scale_anim);
	}, [&]() {
		TitleScene *title = (TitleScene*)this->getParent();
		title->updateMode();
		title->showStart();
		this->removeFromParentAndCleanup(true);
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

	UserDefault::getInstance()->getBoolForKey("ARCADE", true) ? my_name = "menu_arcade.png" : my_name = "menu_education.png";

	movingButtons->addButton(my_name, false, [&]() {
		if (UserDefault::getInstance()->getBoolForKey("ARCADE", true))
		{
			UserDefault::getInstance()->setBoolForKey("ARCADE", false);
			UserDefault::getInstance()->flush();
			movingButtons->setChangePicName("menu_education.png");
		}
		else {
			UserDefault::getInstance()->setBoolForKey("ARCADE", true);
			UserDefault::getInstance()->flush();
			movingButtons->setChangePicName("menu_arcade.png");
		}
	}, nullptr);

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
	pic_logo = Sprite::createWithSpriteFrameName("settings_logo.png");
	pic_logo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	pic_logo->setScale(0);
	this->addChild(pic_logo, 5);

	auto scale_anim = ScaleTo::create(1.5f, 1.0f);
	pic_logo->runAction(scale_anim);
	
	this->scheduleUpdate();
}


void Settings::update(float dt)
{
	movingButtons->update(dt);
}