#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include <iostream>
#include "cocos2d.h"
#include "AnimationTools.h"
#include "HerbLayer.h"
#include "CloudLayer.h"


using namespace std;
using namespace cocos2d;

class BackgroundLayer: public Layer {
    public:
        BackgroundLayer();
        void update(float dt);
        void pauseAll();
        void resumeAll();
		void setIsMove(bool _is);

    private:            
		Vector<Sprite*> butterflies;
		Vector<Sprite*> deleteButterflies;
		Vector<Sprite*> far_field;
		Vector<Sprite*> near_field;
		Size visibleSize;		
		bool isMove;
		float x_far_field;
		float x_near_field;
		HerbLayer *herbLayer;
		CloudLayer *cloudLayer;
				
		void createField(string _f[], float &_x, int _c, float _h, Vector<Sprite*> &_v, int _z);
		void createButterfly(float dt);
		void updateFieldPosition(Vector<Sprite*> &_field, float &_x, float _vel);
};

#endif 
