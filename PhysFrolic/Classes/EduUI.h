#ifndef __EDU_UI_H__
#define __EDU_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "FrolicUtils.h"

using namespace std;
using namespace cocos2d;
using namespace ui;


class EduUI: public Layer {
    public:
		EduUI();
		void setFirstParamName(string _s);
		void setSecondParamName(string _s);
		void setFirstParamValue(float _s, string _m);
		void setSecondParamValue(float _s, string _m);
		void setAnswerPic(string _m);
		void horizontalLine(Vec2 _startPos, Vec2 _endPos, string _t);
		void verticalLine(Vec2 _startPos, Vec2 _endPos);
		void trajectoryLine(Vec2 _startPos, Vec2 _endPos, float _vel, float _angle);
		void angleLine(Vec2 _startPos);
		void eraseLines();
		void showInfoVec(Vec2 _pl, Vec2 _np, float  _vel, float _angle);
		void checkString(Ref *ref, TextFiledEventType type);
		void setLockStart(bool _m);

	private:
		Size visibleSize;
		Sprite *firstParamPic;
		Sprite *secondParamPic;
		Sprite *answerPic;
		Label *firstParamValue;
		Label *secondParamValue;
		TextField *tf;
		Vector<Sprite*> arrow_array;		
		Vector<DrawNode*> rects;
		bool info_vec;
		bool lock_start;
};

#endif // __!EDU_UI_H__
