#include "PhysEngine.h"


PhysEngine * PhysEngine::m_instance = nullptr;

PhysEngine* PhysEngine::getInstance()
{
	if (!m_instance)
		m_instance = new PhysEngine;

	return m_instance;
}

PhysEngine::PhysEngine()
{
	velocity = 0.0f;
	angle = 0.0f;
	delta = 1.0f;
}


float PhysEngine::getVelocity()
{
	return velocity;
}


void PhysEngine::setVelocity(float _s)
{
	velocity = _s;
}


void PhysEngine::setAngle(float _s)
{
	angle = FrolicUtils::degree_to_rad(_s);
}


float PhysEngine::getLmax()
{
	return pow(velocity, 2) * sin(2 * angle) / 10;
}


float PhysEngine::getLhalf()
{
	return getLmax() / 2.0f;
}


float PhysEngine::getThmax()
{	
	return getTime() / 2.0f;
}


float PhysEngine::getHmax()
{
	return (pow(velocity, 2) * pow(sin(angle), 2) / (2.0f * 10.0f));
}


float PhysEngine::getAngle()
{
	return angle;
}


float PhysEngine::getTime()
{
	return 2 * velocity * sin(angle) / 10;
}


float PhysEngine::calcVelocity(float _x, float _y)
{		
	return sqrt((pow(_x, 2)*10.0f) / (2 * pow(cos(angle), 2)*(_x*tan(angle) - _y)));
}


float PhysEngine::calcVelocityWithArrow(float _x, float _y)
{
	return sqrt(pow(_x, 2) + pow(_y, 2)) / delta;
}


float PhysEngine::calcAngleWithArrow(float _x, float _y)
{	
	return FrolicUtils::rad_to_degree(atan(_y / _x));
}


void PhysEngine::setDelta(float _d)
{
	delta = _d;
}