#ifndef __FOREGROUND_LAYER_H__
#define __FOREGROUND_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HerbLayer.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class ForegroundLayer: public Layer {
    public:
		ForegroundLayer();
		void update(float dt);
		void setIsMove(bool _is);
		void pauseMe();
		void resumeMe();

	private:
		Size visibleSize;
		HerbLayer *herbLayer;
};

#endif // __!FOREGROUND_LAYER_H__
