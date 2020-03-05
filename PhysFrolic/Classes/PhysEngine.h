#ifndef __PHYSENGINE_H__
#define __PHYSENGINE_H__

#include <iostream>
#include "FrolicUtils.h"

using namespace std;

class PhysEngine {
    public:		
		static PhysEngine* getInstance();
		float getVelocity();
		float getAngle();
		float getHmax();
		float getLmax();
		float getTime();
		float getThmax();
		float getLhalf();
		void setVelocity(float _s);
		void setAngle(float _s);
		void setDelta(float _d);
		float calcVelocity(float _x, float _y);
		float calcAngleWithArrow(float _x, float _y);
		float calcVelocityWithArrow(float _x, float _y);

    private:           
		PhysEngine();
		float velocity;
		float angle;
		float delta;
		static PhysEngine *m_instance;
};

#endif // __!PHYSENGINE_H__
