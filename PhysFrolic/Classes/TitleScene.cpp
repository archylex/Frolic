#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "FrolicArcade.h"
#include "FrolicUtils.h"
#include "FrolicEdu.h"

USING_NS_CC;

#define CLOUD_VELOCITY 50

Scene* TitleScene::createScene()
{
    return TitleScene::create();
}


bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// Sky layer
	Color4B tColor(90, 182, 255, 255);
	Color4B bColor(255, 255, 255, 255);
	auto sky = LayerGradient::create(bColor, tColor);
	sky->setVector(Point(0, 1));
	this->addChild(sky, 0);

	// Cloud layer
	cloudLayer = new CloudLayer();
	this->addChild(cloudLayer, 1);

	// Game mode picture
	mode_sprite = Sprite::createWithSpriteFrameName("arcade_logo.png");
	mode_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	mode_sprite->setPosition(Vec2(-mode_sprite->getContentSize().width, visibleSize.height * 0.9f));
	this->addChild(mode_sprite, 3);

	// Score picture
	score_bg = Sprite::createWithSpriteFrameName("title_score_bg.png");
	score_bg->setAnchorPoint(Vec2(1.0f, 0.5f));
	score_bg->setPosition(Vec2(visibleSize.width + score_bg->getContentSize().width, visibleSize.height * 0.885f));
	this->addChild(score_bg, 5);

	// Score value
	score_value = Label::createWithBMFont("font.fnt", "0");
	score_value->setAnchorPoint(Vec2(1.0f, 0.5f));
	score_value->setPosition(Vec2(score_bg->getContentSize().width * 0.51f, score_bg->getContentSize().height * 0.45f));
	score_value->setScale(0.25f);
	score_value->setHorizontalAlignment(TextHAlignment::RIGHT);
	score_bg->addChild(score_value, 6);

	updateMode();

	// Title
	logo = Sprite::createWithSpriteFrameName("logo.png");
	logo->setAnchorPoint(Vec2(0.49f, 0.5f));
	logo->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.6f));
	this->addChild(logo, 3);

	// Buttons
	movingButtons = new MovingButton();	
	movingButtons->setStartAngle(-90);
	movingButtons->setBetaAngle(180);
	movingButtons->setSpiralRadius(visibleSize.height * 0.07f);
	movingButtons->setStartPosition(Vec2(0, visibleSize.height * 0.29f));
		
	movingButtons->addButton("menu_quit.png", true, [&]() {hideStart();playButton->stop();}, [&]() {Director::getInstance()->end();});

	movingButtons->addButton("menu_settings.png", true, [&]() {
		hideStart();
		playButton->stop();
	}, [&]() {
		settings = new Settings();
		this->addChild(settings, 5);
	});

	this->addChild(movingButtons, 5);

	movingButtons->start();
		
	// PLAY BUTTON
	playButton = new MovingButton();
	playButton->setStartAngle(0);
	playButton->setBetaAngle(0);
	playButton->setSpiralRadius(0);
	playButton->setStartPosition(Vec2(0, visibleSize.height * 0.29f));
		
	playButton->addButton("start_play.png", true, [&]() {hideStart();movingButtons->stop();}, [&]() {
		if (UserDefault::getInstance()->getBoolForKey("ARCADE", true))
		{
			auto scene = FrolicArcade::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(255, 255, 255)));
		}
		else {
			auto scene = FrolicEdu::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(255, 255, 255)));
		}
	});

	this->addChild(playButton, 5);

	playButton->start();
	
	// my logo
	logo_author = Sprite::createWithSpriteFrameName("logocube.png");	
	logo_author->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.05f));
	logo_author->setScale(0.6f);
	this->addChild(logo_author, 3);
	
	showStart();
		
	this->scheduleUpdate();
				
    return true;
}


void TitleScene::update(float dt)
{
	movingButtons->update(dt);
	playButton->update(dt);
	cloudLayer->update(dt);
}


void TitleScene::hideStart()
{
	auto fadeout = FadeOut::create(1.5f);	
	logo->runAction(fadeout);

	auto afadeout = FadeOut::create(1.5f);
	logo_author->runAction(afadeout);

	auto modeMoveOut = MoveTo::create(0.5f, Vec2(-mode_sprite->getContentSize().width, mode_sprite->getPosition().y));
	mode_sprite->runAction(modeMoveOut);

	auto scoreBGMoveOut = MoveTo::create(0.5f, Vec2(visibleSize.width + score_bg->getContentSize().width, score_bg->getPosition().y));
	score_bg->runAction(scoreBGMoveOut);
}


void TitleScene::showStart()
{
	movingButtons->start();

	playButton->start();

	auto fadein = FadeIn::create(1.5f);
	logo->runAction(fadein);

	auto afadein = FadeIn::create(1.5f);
	logo_author->runAction(afadein);

	auto modeMoveIn = MoveTo::create(0.5f, Vec2(visibleSize.width * 0.02f, mode_sprite->getPosition().y));
	mode_sprite->runAction(modeMoveIn);
	
	auto scoreBGMoveIn = MoveTo::create(0.5f, Vec2(visibleSize.width * 0.9775f, score_bg->getPosition().y));
	score_bg->runAction(scoreBGMoveIn);
}


void TitleScene::updateMode()
{
	if (UserDefault::getInstance()->getBoolForKey("ARCADE", true))
	{		
		score_value->setString(to_string(UserDefault::getInstance()->getIntegerForKey("ARCADE_SCORE", 0)));
		mode_sprite->initWithSpriteFrameName("arcade_logo.png");
	} else {
		score_value->setString(to_string(UserDefault::getInstance()->getIntegerForKey("EDU_SCORE", 0)));
		mode_sprite->initWithSpriteFrameName("edu_logo.png");
	}	

	mode_sprite->setAnchorPoint(Vec2(0.0f, 0.5f));
}