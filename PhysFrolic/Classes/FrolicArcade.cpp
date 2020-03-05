#include "FrolicArcade.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* FrolicArcade::createScene()
{
    return FrolicArcade::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool FrolicArcade::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
			
	isPause = false;
	isGameOver = false;
	isAllMoving = false;
	isTouchedPlayer = false;
	isHighScore = false;
		
	backgroundLayer = new BackgroundLayer();
	this->addChild(backgroundLayer, 0);
		
	stoneLayer = new StoneLayer();
	this->addChild(stoneLayer, 4);
		
	player = Player::create();	
	this->addChild(player, 5);

	// Get start stone and set player position
	for (auto &nextStone : stoneLayer->getPebbles())
	{
		if (nextStone->isTopStone() && nextStone->isStartStone())
		{
			player->setPosition(Vec2(nextStone->getPosition().x, nextStone->getPosition().y + nextStone->getContentSize().height *0.9));
		}
	}

	arcadeUI = new ArcadeUI();
	this->addChild(arcadeUI, 9);
	arcadeUI->setVisible(false);

	foregroundLayer = new ForegroundLayer();
	this->addChild(foregroundLayer, 11);

	topGUI = new TopGUI();
	this->addChild(topGUI, 12);

	this->scheduleUpdate();

	// listener
	auto listenerT = EventListenerTouchOneByOne::create();
	listenerT->setSwallowTouches(true);
	listenerT->onTouchBegan = CC_CALLBACK_2(FrolicArcade::onTouchStart, this);
	listenerT->onTouchMoved = CC_CALLBACK_2(FrolicArcade::onTouchMove, this);
	listenerT->onTouchEnded = CC_CALLBACK_2(FrolicArcade::onTouchEnd, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerT, this);

	// Music
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3", true);

	updateAllSounds();
	
    return true;
}


bool FrolicArcade::onTouchStart(Touch *touch, Event *event)
{
	isTouchedPlayer = isItPlayer(Vec2(touch->getLocation().x, touch->getLocation().y));
	if (!isPause && !isGameOver && isTouchedPlayer)
	{
		touchX = player->getPosition().x + player->getContentSize().width * 0.06f;
		touchY = player->getPosition().y + player->getContentSize().height * 0.31f;

		PhysEngine::getInstance()->setVelocity(0);
		PhysEngine::getInstance()->setAngle(0);
	}

	return true;
}


bool FrolicArcade::onTouchMove(Touch *touch, Event *event)
{
	if (!isPause && !isGameOver && isTouchedPlayer)
	{
		arcadeUI->setVisible(true);

		auto x = (touchX - touch->getLocation().x) / (visibleSize.height * 0.003f);
		auto y = (touchY - touch->getLocation().y) / (visibleSize.height * 0.003f);

		if (x < 0)
			x = 0;

		if (y < 0)
			y = 0;		
		
		PhysEngine::getInstance()->setVelocity(PhysEngine::getInstance()->calcVelocityWithArrow(x, y));
		PhysEngine::getInstance()->setAngle(PhysEngine::getInstance()->calcAngleWithArrow(x, y));

		arcadeUI->setArrowPosition(Vec2(player->getPosition().x + player->getContentSize().width * 0.06f, player->getPosition().y + player->getContentSize().height * 0.31f),
			PhysEngine::getInstance()->getAngle(), PhysEngine::getInstance()->getVelocity());		
	}

	return true;
}


bool FrolicArcade::onTouchEnd(Touch *touch, Event *event)
{
	if (!isPause && !isGameOver && isTouchedPlayer)
	{
		// Jump sound
		if (UserDefault::getInstance()->getBoolForKey("SFX", true))
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.mp3");

		arcadeUI->setVisible(false);

		if (PhysEngine::getInstance()->getVelocity() > 0)
			player->startForce(PhysEngine::getInstance()->getVelocity(), PhysEngine::getInstance()->getAngle());		
	}
			
	return true;
}


void FrolicArcade::update(float dt)
{
	player->update(dt);
	stoneLayer->update(dt);

	if (!isPause)
	{
		backgroundLayer->update(dt);
		foregroundLayer->update(dt);
	}

	if (isPause && !isGameOver)
		menuLayer->update(dt);

	if (isGameOver)
		gameOverLayer->update(dt);
	
	if (player->isStartedForce())
	{
		player->setJumpPhase(PhysEngine::getInstance()->getTime());

		for (auto &nextPebble : stoneLayer->getPebbles())
		{
			if (FrolicUtils::checkCollision(player, nextPebble) && !nextPebble->isStartStone())
			{
				if (nextPebble->isTopStone())
				{
					if (PhysEngine::getInstance()->getThmax() < player->getTime())
					{
						if (FrolicUtils::checkEquilibrium(player, nextPebble))
						{
							if (UserDefault::getInstance()->getBoolForKey("SFX", true))
								CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("land.mp3");

							player->stopForce();
							player->setPosition(Vec2(player->getPosition().x, nextPebble->getPosition().y + nextPebble->getContentSize().height *0.9));
							player->JumpAnimation();
							nextPebble->setStartStone(true);

							player->setIsMove(true);
							stoneLayer->setIsMove(true);
							foregroundLayer->setIsMove(true);
							backgroundLayer->setIsMove(true);
							isAllMoving = true;
						}

						if (FrolicUtils::checkFalling(player, nextPebble))
							player->startLeftFall();
					}
				} else {
					if (UserDefault::getInstance()->getBoolForKey("SFX", true))
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("obstacle.mp3");
					player->startLeftFall();
				}
			}
		}	

		// Gold
		for (auto &nextGold : stoneLayer->getGolds())
		{
			if (FrolicUtils::checkGoldCollision(player, nextGold))
			{
				topGUI->setScore(topGUI->getScore() + 1);

				if (UserDefault::getInstance()->getBoolForKey("SFX", true))
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pickup.mp3");
				
				if (UserDefault::getInstance()->getIntegerForKey("ARCADE_SCORE", 0) < topGUI->getScore())
				{
					UserDefault::getInstance()->setIntegerForKey("ARCADE_SCORE", topGUI->getScore());
					UserDefault::getInstance()->flush();

					if (!isHighScore)
					{
						isHighScore = true;

						// Highscore sound					
						if (UserDefault::getInstance()->getBoolForKey("SFX", true))
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("highscore.mp3");

						// Show highscore
						topGUI->showHighScore();
					}
				}
				
				stoneLayer->deleteGold(nextGold);
			}
		}
	}

	if (player->getPosition().y + player->getContentSize().height < 0 && !isGameOver)
	{
		player->stopForce();
		player->stopLeftFall();

		gameOver();
	}

	if (isAllMoving)
	{
		if (player->getPosition().x <= visibleSize.width * 0.2)
		{
			player->setIsMove(false);
			stoneLayer->setIsMove(false);
			foregroundLayer->setIsMove(false);
			backgroundLayer->setIsMove(false);
			isAllMoving = false;						
		}
	}
}


void FrolicArcade::getPauseMenu()
{
	menuLayer = new MenuLayer();
	this->addChild(menuLayer, 69);

	pauseGame();

	isPause = true;
}


void FrolicArcade::resumeGame()
{
	player->resumeMe();
	backgroundLayer->resumeAll();
	stoneLayer->resumeMe();
	foregroundLayer->resumeMe();
	topGUI->setVisible(true);
	isPause = false;
	updateAllSounds();
}


void FrolicArcade::pauseGame()
{
	player->pauseMe();
	backgroundLayer->pauseAll();
	foregroundLayer->pauseMe();
	stoneLayer->pauseMe();
	topGUI->setVisible(false);
	pauseAllSounds();
}


bool FrolicArcade::isItPlayer(Vec2 _pos)
{
	if ((_pos.x > player->getPosition().x - player->getContentSize().width / 2) &&
		(_pos.x < player->getPosition().x + player->getContentSize().width / 2) &&
		(_pos.y < player->getPosition().y + player->getContentSize().height) &&
		(_pos.y > player->getPosition().y))
	{
		return true;
	}

	return false;
}


void FrolicArcade::gameOver()
{
	pauseAllSounds();

	gameOverLayer = new GameOver();
	gameOverLayer->setScore(topGUI->getScore());
	this->addChild(gameOverLayer, 69);

	pauseGame();

	isPause = true;

	isGameOver = true;	
}


void FrolicArcade::updateAllSounds()
{
	if (UserDefault::getInstance()->getBoolForKey("MUSIC", true))
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	else
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}


void FrolicArcade::pauseAllSounds()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}