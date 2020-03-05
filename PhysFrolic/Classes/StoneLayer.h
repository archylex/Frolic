#ifndef __STONE_LAYER_H__
#define __STONE_LAYER_H__

#include <iostream>
#include "cocos2d.h"
#include "Stone.h"
#include "GoldLayer.h"


using namespace std;
using namespace cocos2d;

class StoneLayer: public Layer {
    public:
		StoneLayer();
        void update(float dt);
		void createRow();
		Vec2 getNearStone(Vec2 _p);
		Vec2 getLeftNearStone(Vec2 _p);
		Vector<Sprite*> getGolds();
		void deleteGold(Sprite* _s);
		Vector<Stone*> getPebbles();
		void setIsMove(bool _is);
		void pauseMe();
		void resumeMe();

    private:            
		Vector<Stone*> pebbles;
		Vector<Stone*> del_stones;
		GoldLayer *goldLayer;
		Size visibleSize;
		float x_length;
		bool isMove;
		bool isPause;
};

#endif // __!STONE_LAYER_H__
