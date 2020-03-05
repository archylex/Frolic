#include "GameOver.h"
#include "SimpleAudioEngine.h"
#include "FrolicArcade.h"
#include "TitleScene.h"
#include "FrolicUtils.h"
#include "FrolicEdu.h"
#include "AdvMob.h"


GameOver::GameOver()
{
	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		AdvMob::showInterstitial();
	#endif

	visibleSize = Director::getInstance()->getVisibleSize();
	alfa = 0.0f;

	auto fadeBGNode = DrawNode::create();
	Vec2 fadeBG[] = { Vec2(0, 0), Vec2(0, visibleSize.height), Vec2(visibleSize.width, visibleSize.height), Vec2(visibleSize.width, 0) };
	Color4F aBlack(0.0f, 0.0f, 0.0f, 0.55f);
	fadeBGNode->drawPolygon(fadeBG, 4, aBlack, 0, aBlack);
	this->addChild(fadeBGNode);

	const char *score_key = "EDU_SCORE";
	if (UserDefault::getInstance()->getBoolForKey("ARCADE", true))
		score_key = "ARCADE_SCORE";

	// Highscore picture
	highscore_bg = Sprite::createWithSpriteFrameName("game_over_highscore.png");
	highscore_bg->setAnchorPoint(Vec2(0.0f, 0.5f));
	highscore_bg->setPosition(Vec2(-highscore_bg->getContentSize().width, visibleSize.height * 0.873f));
	this->addChild(highscore_bg, 5);

	// Highscore value
	highscore_value = Label::createWithBMFont("font.fnt", to_string(UserDefault::getInstance()->getIntegerForKey(score_key, 0)));
	highscore_value->setAnchorPoint(Vec2(0.0f, 0.5f));
	highscore_value->setPosition(Vec2(highscore_bg->getContentSize().width * 0.54f, highscore_bg->getContentSize().height * 0.43f));
	highscore_value->setScale(0.25f);
	highscore_value->setHorizontalAlignment(TextHAlignment::LEFT);
	highscore_bg->addChild(highscore_value, 6);
		
	// Score picture
	score_bg = Sprite::createWithSpriteFrameName("game_over_score.png");
	score_bg->setAnchorPoint(Vec2(1.0f, 0.5f));
	score_bg->setPosition(Vec2(visibleSize.width + score_bg->getContentSize().width, visibleSize.height * 0.88f));
	this->addChild(score_bg, 5);

	// Score value
	score_value = Label::createWithBMFont("font.fnt", "0");
	score_value->setAnchorPoint(Vec2(1.0f, 0.5f));
	score_value->setPosition(Vec2(score_bg->getContentSize().width * 0.534f, score_bg->getContentSize().height * 0.37f));
	score_value->setScale(0.25f);
	score_value->setHorizontalAlignment(TextHAlignment::RIGHT);
	score_bg->addChild(score_value, 6);

	// Game Over Logo
	pic_logo = Sprite::createWithSpriteFrameName("game_over.png");	
	pic_logo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	pic_logo->setScale(0);
	this->addChild(pic_logo);

	// Buttons
	movingButtons = new MovingButton();
	movingButtons->setStartAngle(-90);
	movingButtons->setBetaAngle(180);
	movingButtons->setSpiralRadius(visibleSize.height * 0.097f);
	movingButtons->setStartPosition(Vec2(0, visibleSize.height / 2));
		
	movingButtons->addButton("menu_home.png", true, [&]() {
		hideMe();
	}, [&]() {
		auto scene = TitleScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(255, 255, 255)));
	});

	movingButtons->addButton("menu_play.png", true, [&]() {
		hideMe();
	}, [&]() {
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

	this->addChild(movingButtons, 5);

	movingButtons->start();

	auto hiscoreBGMoveIn = MoveTo::create(0.5f, Vec2(visibleSize.width * 0.02f, highscore_bg->getPosition().y));
	highscore_bg->runAction(hiscoreBGMoveIn);

	auto scoreBGMoveIn = MoveTo::create(0.5f, Vec2(visibleSize.width * 0.98f, score_bg->getPosition().y));
	score_bg->runAction(scoreBGMoveIn);

	auto scale_anim = ScaleTo::create(1.5f, 1.0f);
	pic_logo->runAction(scale_anim);

	//
	for (int a = 0; a < 2; a++)
	{
		auto star = Sprite::createWithSpriteFrameName("star.png");		
		this->addChild(star);
		star->setScale(0);
		stars.pushBack(star);

		auto delay = DelayTime::create(1.5f);
		auto scale_anim = ScaleTo::create(0.01f, 1.0f);
		auto seq = Sequence::create(delay, scale_anim, nullptr);
		star->runAction(seq);
	}

	// Music
	if (UserDefault::getInstance()->getBoolForKey("SFX", true))
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gameover.mp3");
}


void GameOver::setScore(int _s)
{
	score_value->setString(to_string(_s));	
}


void GameOver::update(float dt)
{
	movingButtons->update(dt);

	// stars update
	float sx = pic_logo->getPosition().x + pic_logo->getContentSize().width * 0.2f;
	float sy = pic_logo->getPosition().y + pic_logo->getContentSize().height * 0.12f;	
	int a = 0;

	for (auto &star : stars)
	{
		float delta;
		(a % 2) ? delta = 1 : delta = -1;
		star->setPosition(Vec2(sx + pic_logo->getContentSize().width * 0.2f * delta * cos(alfa), sy + pic_logo->getContentSize().height * 0.05f * delta * sin(alfa)));		
		a++;
	}

	alfa += 0.1f;

	if (alfa >= 6.28f)
		alfa = 0.0f;
}


void GameOver::hideMe()
{
	auto scale_anim = ScaleTo::create(1.5f, 0.0f);
	pic_logo->runAction(scale_anim);

	auto hiscoreBGMoveOut = MoveTo::create(0.5f, Vec2(-highscore_bg->getContentSize().width, highscore_bg->getPosition().y));
	highscore_bg->runAction(hiscoreBGMoveOut);

	auto scoreBGMoveOut = MoveTo::create(0.5f, Vec2(visibleSize.width + score_bg->getContentSize().width, score_bg->getPosition().y));
	score_bg->runAction(scoreBGMoveOut);

	for (auto &star : stars)
	{		
		star->setVisible(false);
	}
}