#ifndef __FROLIC_ARCADE_H__
#define __FROLIC_ARCADE_H__

#include "cocos2d.h"
#include "Player.h"
#include "BackgroundLayer.h"
#include "StoneLayer.h"
#include "PhysEngine.h"
#include "TopGUI.h"
#include "ForegroundLayer.h"
#include "MenuLayer.h"
#include "GameOver.h"
#include "ArcadeUI.h"

using namespace cocos2d;

class FrolicArcade : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
	void update(float dt);
	bool onTouchStart(Touch *touch, Event *event);
	bool onTouchMove(Touch *touch, Event *event);
	bool onTouchEnd(Touch *touch, Event *event);
	void getPauseMenu();
	void resumeGame();
	void pauseGame();
	void gameOver();
	void updateAllSounds();
	void pauseAllSounds();

private:
	Player *player;
	BackgroundLayer *backgroundLayer;
	StoneLayer *stoneLayer;
	ForegroundLayer *foregroundLayer;
	MenuLayer *menuLayer;
	TopGUI *topGUI;
	GameOver *gameOverLayer;
	ArcadeUI *arcadeUI;
	Size visibleSize;
	float touchX;
	float touchY;
	bool isAllMoving;
	bool isPause;
	bool isGameOver;
	bool isItPlayer(Vec2 _pos);
	bool isTouchedPlayer;
	bool isHighScore;
    
    // implement the "static create()" method manually
    CREATE_FUNC(FrolicArcade);
};

#endif // __!FROLIC_ARCADE_H__
