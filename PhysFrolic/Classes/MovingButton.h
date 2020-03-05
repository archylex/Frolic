#ifndef __MOVING_BUTTON_H__
#define __MOVING_BUTTON_H__

#pragma once;

#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"


using namespace std;
using namespace cocos2d;
using namespace ui;

struct MyButton
{
	Button* btn;
	function<void()> func;
	function<void()> callback_func;
	bool isHide;
};

class MovingButton: public Layer {
    public:
		MovingButton();
		void update(float dt);
		void addButton(const string _b, bool _hidden, const std::function<void()> &func, const std::function<void()> &cb_func);
		void setStartAngle(float _out);
		void setBetaAngle(float _out);
		void setSpiralRadius(float _out);
		void setStartPosition(Vec2 _out);
		void setChangePicName(string _out);
		void start();
		void stop();

    private:            
		Size visibleSize;
		Vector<Sprite*> tails;
		Vector<ParticleSystem*> stars;
		string change_pic_name;
		bool change_pic_button;
		function<void()> callfunc_button;
		bool isMove;
		float spiral_radius;
		float fi;
		float fi_step;
		float alfa;
		float start_angle;
		float beta_angle;
		Vec2 start_pos;
		vector<MyButton> myfunctions;

		void createParticleTails();

};

#endif // __!MOVING_BUTTON_H__
