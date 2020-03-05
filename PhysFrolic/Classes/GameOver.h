#ifndef __GAME_OVER__
#define __GAME_OVER__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MovingButton.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class GameOver: public Layer {
    public:
		GameOver();
		void update(float dt);
		void hideMe();
		void setScore(int _s);

	private:
		Size visibleSize;
		Sprite *score_bg;
		Sprite *highscore_bg;
		Label *score_value;
		Label *highscore_value;
		Sprite *pic_logo;
		MovingButton *movingButtons;
		Vector<Sprite*> stars;
		float alfa;

};

#endif // __!GAME_OVER__
