#ifndef __HERB_LAYER_H__
#define __HERB_LAYER_H__

#include <iostream>
#include "cocos2d.h"
#include "AnimationTools.h"

using namespace std;
using namespace cocos2d;

class HerbLayer: public Layer {
    public:
		HerbLayer();
        void update(float dt);		
		void createHerbs();
		void setIsMove(bool _is);
		void pauseMe();
		void resumeMe();
		void setScaleRange(float _min, float _max);
		void setStartY(float _y);
		void setVelocity(float _v);

    private:            
		Vector<Sprite*> herbs;
		Vector<Sprite*> del_herbs;
		Size visibleSize;
		bool isMove;
		bool isPause;
		float last_pos;
		float min_scale;
		float max_scale;
		float startY;
		float velocity;

		void createHerb();
};

#endif // __!HERB_LAYER_H__