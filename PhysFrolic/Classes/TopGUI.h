#ifndef __TOPGUI_H__
#define __TOPGUI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class TopGUI: public Layer {
    public:
		TopGUI();
		void setScore(int _s);
		int getScore();
		void showHighScore();

	private:
		Size visibleSize;
		int score;
		Label *gold_label;
};

#endif // __!TOPGUI_H__
