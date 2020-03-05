#ifndef __ARCADE_UI_H__
#define __ARCADE_UI_H__

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class ArcadeUI: public Layer {
    public:
		ArcadeUI();
		void setArrowPosition(Vec2 _pos, float _angle, float _velocity);

    private:            
		Sprite *arrow;
		Sprite *arrow_base;
		Sprite *arrow_line;
		Vec2 cur_pos;
};

#endif // __!ARCADE_UI_H__
