#ifndef __GOLD_LAYER_H__
#define __GOLD_LAYER_H__

#include "cocos2d.h"
#include "AnimationTools.h"

using namespace std;
using namespace cocos2d;

class GoldLayer: public Layer {
    public:
		GoldLayer();
		void createGold(Vec2 _pos);
		void update(float dt);
		Vector<Sprite*> getGolds();
		void deleteGold(Sprite* _s);
		void setisMove(bool _s);
		void pauseMe();
		void resumeMe();

	private:
		Size visibleSize;
		Animate *gold_animation;
		Vector<Sprite*> golds;
		Vector<Sprite*> del_golds;
		float x_length;
		bool isPause;
		bool isMove;

};

#endif // __!GOLD_LAYER_H__
