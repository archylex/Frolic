
#ifndef __FROLIC_EDU_SCENE_H__
#define __FROLIC_EDU_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "BackgroundLayer.h"
#include "StoneLayer.h"
#include "PhysEngine.h"
#include "TopGUI.h"
#include "MenuLayer.h"
#include "GameOver.h"
#include "EduUI.h"
#include "ForegroundLayer.h"
#include "FrolicUtils.h"

class FrolicEdu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	void update(float dt);    
	void getPauseMenu();
	void resumeGame();
	void pauseGame();
	void gameOver();
	int getQuest();
	void vec_info();
	void startJump(float _n);
	void updateAllSounds();
	void pauseAllSounds();

private:
	Player *player;
	BackgroundLayer *backgroundLayer;
	StoneLayer *pl;
	MenuLayer *menuLayer;
	TopGUI *topGUI;
	GameOver *gameOverLayer;
	EduUI *eduUI;
	ForegroundLayer *foregroundLayer;
	Size visibleSize;
	float touchX;
	float touchY;
	Vec2 cur_pos;
	bool isAllMoving;
	bool isPause;
	bool isHighScore;
	int score;
	bool isGameOver;
	bool isTouchedPlayer;
	int answer;	
   
    // implement the "static create()" method manually
    CREATE_FUNC(FrolicEdu);
};

#endif // __!FROLIC_EDU_SCENE_H__
