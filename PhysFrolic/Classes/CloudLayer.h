#ifndef __CLOUD_LAYER_H__
#define __CLOUD_LAYER_H__

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class CloudLayer: public Layer {
    public:
		CloudLayer();
        void update(float dt);		

    private:            
		Vector<Sprite*> clouds;
		Vector<Sprite*> del_clouds;
		Size visibleSize;
		float last_pos;

		void createCloud();
};

#endif // __!CLOUD_LAYER_H__