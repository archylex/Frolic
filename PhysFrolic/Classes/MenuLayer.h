#ifndef __MENU_LAYER__
#define __MENU_LAYER__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MovingButton.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class MenuLayer: public Layer {
    public:
		MenuLayer();
		void update(float dt);

	private:
		Size visibleSize;
		MovingButton *movingButtons;
		Sprite *pic_logo;

};

#endif // __!MENU_LAYER__
