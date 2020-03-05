#ifndef __STONE_H__
#define __STONE_H__

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

class Stone : public Sprite 
{
public:
	static Stone *create(string _name);
	bool isTopStone();
	bool isStartStone();
	void setStartStone(bool _is);
	void setTopStone(bool _is);
		
private:
	bool initialize(string _name);		
	bool isTop;
	bool isStart;
};

#endif // __!STONE_H__
