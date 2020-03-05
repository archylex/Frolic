#include "FrolicEdu.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;


Scene* FrolicEdu::createScene()
{
    return FrolicEdu::create();
}

// on "init" you need to initialize your instance
bool FrolicEdu::init()
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
	isHighScore = false;
	score = 0;
	  
	// Add background layer
	backgroundLayer = new BackgroundLayer();
	this->addChild(backgroundLayer);
	
	// pebbles
	pl = new StoneLayer();
	this->addChild(pl, 4);
		
	player = Player::create();
	player->setPosition(Vec2(visibleSize.width * 0.2, 300));
	this->addChild(player, 5);

	for (auto &nextStone : pl->getPebbles())
	{
		if (nextStone->isTopStone() && nextStone->isStartStone())
		{
			player->setPosition(Vec2(nextStone->getPosition().x, nextStone->getPosition().y + nextStone->getContentSize().height *0.9));
		}
	}
	
	// Foreground layer
	foregroundLayer = new ForegroundLayer();
	this->addChild(foregroundLayer, 10);

	// shader testa
	topGUI = new TopGUI();
	this->addChild(topGUI, 11);

	// Edu UI
	eduUI = new EduUI();
	this->addChild(eduUI, 12);
	   
	answer = getQuest();

	vec_info();
	
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music.mp3", true);

	updateAllSounds();

	this->scheduleUpdate();

    return true;
}


void FrolicEdu::update(float dt)
{
	player->update(dt);

	if (!isPause)
	{
		backgroundLayer->update(dt);
		foregroundLayer->update(dt);
	}

	if (isPause && !isGameOver)
		menuLayer->update(dt);

	if (isGameOver)
		gameOverLayer->update(dt);
	
	pl->update(dt);

	if (player->isStartedForce())
	{
		player->setJumpPhase(PhysEngine::getInstance()->getTime());

		for (auto &nextPebble : pl->getPebbles())
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

							player->setPosition(Vec2(player->getPosition().x, nextPebble->getPosition().y + nextPebble->getContentSize().height *0.88f));
							player->JumpAnimation();
							nextPebble->setStartStone(true);							
							player->setIsMove(true);
							pl->setIsMove(true);
							foregroundLayer->setIsMove(true);							
							backgroundLayer->setIsMove(true);
							isAllMoving = true;

							eduUI->eraseLines();
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
		for (auto &nextGold : pl->getGolds())
		{
			if (FrolicUtils::checkGoldCollision(player, nextGold))
			{
				if (UserDefault::getInstance()->getBoolForKey("SFX", true))
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pickup.mp3");

				topGUI->setScore(topGUI->getScore() + 1);

				if (UserDefault::getInstance()->getIntegerForKey("EDU_SCORE", 0) < topGUI->getScore())
				{
					if (!isHighScore)
					{
						isHighScore = true;

						if (UserDefault::getInstance()->getBoolForKey("SFX", true))
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("highscore.mp3");

						topGUI->showHighScore();
					}

					UserDefault::getInstance()->setIntegerForKey("EDU_SCORE", topGUI->getScore());
					UserDefault::getInstance()->flush();					
				}

				pl->deleteGold(nextGold);
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
			pl->setIsMove(false);
			foregroundLayer->setIsMove(false);
			backgroundLayer->setIsMove(false);
			isAllMoving = false;			

			answer = getQuest();

			vec_info();
		}
	}
}


void FrolicEdu::getPauseMenu()
{
	menuLayer = new MenuLayer();
	this->addChild(menuLayer, 69);

	pauseGame();

	isPause = true;
}


void FrolicEdu::resumeGame()
{
	player->resumeMe();
	backgroundLayer->resumeAll();
	pl->resumeMe();
	foregroundLayer->resumeMe();
	foregroundLayer->resumeMe();
	topGUI->setVisible(true);
	eduUI->setVisible(true);
	isPause = false;
	updateAllSounds();
}


void FrolicEdu::pauseGame()
{
	player->pauseMe();
	backgroundLayer->pauseAll();
	pl->pauseMe();
	foregroundLayer->pauseMe();	
	topGUI->setVisible(false);
	eduUI->setVisible(false);
	pauseAllSounds();
}


void FrolicEdu::gameOver()
{
	pauseAllSounds();

	gameOverLayer = new GameOver();
	this->addChild(gameOverLayer, 69);

	pauseGame();

	isPause = true;

	isGameOver = true;
}


int FrolicEdu::getQuest()
{
	Vec2 ps = pl->getNearStone(player->getPosition());
	float ang = FrolicUtils::rad_to_degree(atan(abs(ps.y) / (ps.x / 2)));
	log("ANGLE s: %f", ang);
	if (ang <= 45)
		ang = 45;

	ang += rand() % 7;

	PhysEngine::getInstance()->setAngle(ang);
	float v = PhysEngine::getInstance()->calcVelocity(ps.x, ps.y);
	PhysEngine::getInstance()->setVelocity(v);

	eduUI->setLockStart(false);
	
	int res = 0; // 0 - velocity; 1 - angle

	srand(time(NULL));
	int q = (rand() % 6) + 1;

	switch (q)
	{
	case 1: // v -> l, a
	{
		eduUI->setFirstParamName("s.png");
		eduUI->setSecondParamName("a.png");		
		eduUI->setFirstParamValue(PhysEngine::getInstance()->getLhalf() / 100, "m");
		eduUI->setSecondParamValue(FrolicUtils::rad_to_degree(PhysEngine::getInstance()->getAngle()), "");
		eduUI->setAnswerPic("v.png");
		res = 0;
		break;
	}
	case 2: // v -> h, a
	{
		eduUI->setFirstParamName("h.png");
		eduUI->setSecondParamName("a.png");
		eduUI->setFirstParamValue(PhysEngine::getInstance()->getHmax() / 100, "m");
		eduUI->setSecondParamValue(FrolicUtils::rad_to_degree(PhysEngine::getInstance()->getAngle()), "");
		eduUI->setAnswerPic("v.png");
		res = 0;
		break;
	}
	case 3: // v -> t, a
	{
		eduUI->setFirstParamName("t.png");
		eduUI->setSecondParamName("a.png");
		eduUI->setFirstParamValue(PhysEngine::getInstance()->getThmax() / 10, "s");
		eduUI->setSecondParamValue(FrolicUtils::rad_to_degree(PhysEngine::getInstance()->getAngle()), "");
		eduUI->setAnswerPic("v.png");
		res = 0;
		break;
	}

	case 4: // a -> l, v
	{				
		eduUI->setFirstParamName("s.png");
		eduUI->setSecondParamName("v.png");
		eduUI->setFirstParamValue(PhysEngine::getInstance()->getLhalf() / 100, "m");
		eduUI->setSecondParamValue(PhysEngine::getInstance()->getVelocity() / 10, "m/s");
		eduUI->setAnswerPic("a.png");		
		res = 1;
		break;
	}
	case 5: // a -> h, v
	{
		eduUI->setFirstParamName("h.png");
		eduUI->setSecondParamName("v.png");
		eduUI->setFirstParamValue(PhysEngine::getInstance()->getHmax() / 100, "m");
		eduUI->setSecondParamValue(PhysEngine::getInstance()->getVelocity() / 10, "m/s");
		eduUI->setAnswerPic("a.png");
		res = 1;
		break;
	}
	case 6: // a -> t, v
	{
		eduUI->setFirstParamName("t.png");
		eduUI->setSecondParamName("v.png");
		eduUI->setFirstParamValue(PhysEngine::getInstance()->getThmax() / 10, "s");
		eduUI->setSecondParamValue(PhysEngine::getInstance()->getVelocity() / 10, "m/s");
		eduUI->setAnswerPic("a.png");
		res = 1;
		break;
	}
	default:
		break;
	}

	return res;
}


void FrolicEdu::vec_info()
{
	eduUI->showInfoVec(player->getPosition(), Vec2(PhysEngine::getInstance()->getLhalf(), PhysEngine::getInstance()->getHmax()), PhysEngine::getInstance()->getVelocity(), PhysEngine::getInstance()->getAngle());
}


void FrolicEdu::startJump(float _n)
{
	if (UserDefault::getInstance()->getBoolForKey("SFX", true))
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump.mp3");

	if (answer == 0)
		PhysEngine::getInstance()->setVelocity(_n);
	else
		PhysEngine::getInstance()->setAngle(_n);

	player->startForce(PhysEngine::getInstance()->getVelocity(), PhysEngine::getInstance()->getAngle());
}


void FrolicEdu::updateAllSounds()
{
	if (UserDefault::getInstance()->getBoolForKey("MUSIC", true))
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	else
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}


void FrolicEdu::pauseAllSounds()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}