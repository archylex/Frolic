#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Loading : public Scene {
    public:
        virtual bool init();  
    	static Scene *scene();
		virtual void update(float dt);
    	
    private:
		Size visibleSize;
        Label *percLabel;
        void loadSources(float dt);
		Vector<Sprite*> tails;
		float l_tail;
		float alfa;
        	
    CREATE_FUNC(Loading)
};

#endif 
