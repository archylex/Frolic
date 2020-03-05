#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#pragma once;

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Settings.h"
#include "CloudLayer.h"
#include "MovingButton.h"

using namespace cocos2d;
using namespace ui;

class TitleScene : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
	void update(float dt);
	void hideStart();
	void showStart();
	void updateMode();
	
private:	
	Size visibleSize;
	Label *score_value;
	Sprite *mode_sprite;
	Sprite *score_bg;
	Sprite *logo;
	Sprite *logo_author;
	Settings *settings;
	CloudLayer *cloudLayer;
	MovingButton *movingButtons;
	MovingButton *playButton;
	    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);
};

#endif // __!TITLE_SCENE_H__
