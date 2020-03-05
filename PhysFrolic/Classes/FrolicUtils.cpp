#include "FrolicUtils.h"


float FrolicUtils::degree_to_rad(float _degree)
{
	return _degree * 3.14159f / 180.0f;
}


float FrolicUtils::rad_to_degree(float _rad)
{
	return _rad * 180.0f / 3.14159f;
}


Vec2 FrolicUtils::rotate_coordinates(Vec2 _point, float _beta, Vec2 _null_point)
{
	float x = _point.x * cos(_beta) - _point.y * sin(_beta) + _null_point.x;
	float y = _point.x * sin(_beta) + _point.y * cos(_beta) + _null_point.y;

	return Vec2(x, y);
}


float FrolicUtils::round2f(float _v)
{
	float v = (int)(_v * 100 + 0.5f);
	return (float)v / 100;
}


string FrolicUtils::float2ToString(float _f)
{
	ostringstream ss;
	ss << round2f(_f);
	string s(ss.str());
	return s;
}


bool FrolicUtils::isDigits(const string &str)
{
	return str.find_first_not_of("0123456789.") == std::string::npos;
}


float FrolicUtils::randomF(float min, float max)
{
	return rand() % int(max - min) + min;
}


bool FrolicUtils::checkEquilibrium(Sprite *_a, Sprite *_b)
{
	if ((_a->getPosition().x - _a->getContentSize().width * 0.16f >= _b->getPosition().x - _b->getContentSize().width / 2) &&
		(_a->getPosition().x + _a->getContentSize().width * 0.23f <= _b->getPosition().x + _b->getContentSize().width / 2))
	{
		return true;
	}	

	return false;
}

bool FrolicUtils::checkFalling(Sprite *_a, Sprite *_b)
{
	if ((_a->getPosition().x - _a->getContentSize().width * 0.16f < _b->getPosition().x - _b->getContentSize().width / 2) &&
		(_a->getPosition().x + _a->getContentSize().width * 0.23f >= _b->getPosition().x - _b->getContentSize().width / 2))
	{
		return true;
	}

	return false;
}


bool FrolicUtils::checkCollision(Sprite *_a, Sprite *_b)
{
	if ((_a->getPosition().x + _a->getContentSize().width * 0.23f > _b->getPosition().x - _b->getContentSize().width / 2) &&
		(_a->getPosition().x - _a->getContentSize().width * 0.16f < _b->getPosition().x + _b->getContentSize().width / 2) &&
		(_a->getPosition().y > _b->getPosition().y) &&
		(_a->getPosition().y < _b->getPosition().y + _b->getContentSize().height))
	{
		return true;
	}
	return false;
}


bool FrolicUtils::checkGoldCollision(Sprite *_a, Sprite *_b)
{
	if ((_a->getPosition().x + _a->getContentSize().width * 0.5f >= _b->getPosition().x - _b->getContentSize().width / 2) &&
		(_a->getPosition().x - _a->getContentSize().width * 0.5f <= _b->getPosition().x + _b->getContentSize().width / 2) &&
		(_a->getPosition().y <= _b->getPosition().y + _b->getContentSize().height) &&
		(_a->getPosition().y + _a->getContentSize().height / 2 >= _b->getPosition().y))
	{
		return true;
	}
	return false;
}