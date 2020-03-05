#ifndef __FROLIC_UTILS_H__
#define __FROLIC_UTILS_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;
using namespace ui;

class FrolicUtils {
    public:
		static float degree_to_rad(float _degree);
		static float rad_to_degree(float _rad);
		static Vec2 rotate_coordinates(Vec2 _point, float _beta, Vec2 _null_point);
		static float round2f(float _v);
		static string float2ToString(float _f);
		static bool isDigits(const string &str);
		static float randomF(float min, float max);
		static bool checkEquilibrium(Sprite *_a, Sprite *_b);
		static bool checkFalling(Sprite *_a, Sprite *_b);
		static bool checkCollision(Sprite *_a, Sprite *_b);
		static bool checkGoldCollision(Sprite *_a, Sprite *_b);
		
	private:
		Size visibleSize;
		
};

#endif // __!FROLIC_UTILS_H__
