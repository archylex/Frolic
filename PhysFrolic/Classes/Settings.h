#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MovingButton.h"


using namespace cocos2d;
using namespace ui;
using namespace std;

class Settings : public Layer {
    public:
        Settings();
		void update(float dt);
    		
    private:         
        Size visibleSize;
        MovingButton *movingButtons;
		Sprite *pic_logo;
};

#endif 
