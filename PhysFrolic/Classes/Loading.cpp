#include "Loading.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"
//#include "PublicVariables.h"

// Create Loading scene
Scene* Loading::scene() {
    return Loading::create();
}

// Initialize scene
bool Loading::init() {
    // Screen size
    visibleSize = Director::getInstance()->getVisibleSize();

	alfa = 0.0f;

	// Sky layer
	Color4B tColor(90, 182, 255, 255);
	Color4B bColor(255, 255, 255, 255);
	auto sky = LayerGradient::create(bColor, tColor);
	sky->setVector(Point(0, 1));
	this->addChild(sky, 0);

	for (int a = 0; a < 2; a++)
	{
		auto tail = Sprite::create("menu_tail.png");
		l_tail = visibleSize.height * 0.13f;
		a % 2 ? tail->setFlippedY(false) : tail->setFlippedY(true);
		a % 2 ? tail->setFlippedX(false) : tail->setFlippedX(true);

		tail->setPosition(visibleSize.width / 2, visibleSize.height / 2 + l_tail);

		this->addChild(tail);

		tails.pushBack(tail);
	}

    // Percent label
    percLabel = Label::createWithBMFont("font.fnt", "0");
    percLabel->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    percLabel->setScale(0.3f);
    this->addChild(percLabel);

    // Get load
    this->schedule(schedule_selector(Loading::loadSources), 0.5f);
	this->scheduleUpdate();

    return true;
}

void Loading::loadSources(float dt) {
    // Unschedule
    this->unschedule(schedule_selector(Loading::loadSources));

    // Loading sprites
    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("sprites-0.plist");
	spritecache->addSpriteFramesWithFile("sprites-1.plist");
	spritecache->addSpriteFramesWithFile("sprites-2.plist");
	spritecache->addSpriteFramesWithFile("sprites-3.plist");
	spritecache->addSpriteFramesWithFile("sprites-4.plist");
    
    percLabel->setString("20");

    // Get audio engine instance
    auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

    // Loading music
    audioEngine->preloadBackgroundMusic("music.mp3");
	
    // Loading missile sound
    audioEngine->preloadEffect("click.mp3");
	audioEngine->preloadEffect("gameover.mp3");
	audioEngine->preloadEffect("highscore.mp3");
	audioEngine->preloadEffect("jump.mp3");
	audioEngine->preloadEffect("pickup.mp3");
	audioEngine->preloadEffect("land.mp3");
	audioEngine->preloadEffect("obstacle.mp3");

    percLabel->setString("100");

    // Go to main menu scene
    Scene *myScene = TitleScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, myScene, Color3B(255, 255, 255)));
}

void Loading::update(float dt)
{
	int ct = 0;
	for (auto &tail : tails)
	{
		int delta = 1;

		(ct % 2) ? delta = 1 : delta = -1;

		tail->setPosition(Vec2(visibleSize.width / 2 + delta * l_tail * cos(alfa), visibleSize.height / 2 + delta * l_tail * sin(alfa)));

		tail->setRotation(90 - (alfa * 180.0f / 3.14f));

		ct++;
	}

	alfa += 0.1f;

	if (alfa >= 6.28f)
		alfa = 0.0f;		
}