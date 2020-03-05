#include "StoneLayer.h"
#include "FrolicUtils.h"

#define STONE_VELOCITY 10


float rand_num(float _min, float _max)
{
	return float(rand() % int(_max - _min + 1) + int(_min));
}


int rand_num(int _min, int _max)
{
	return rand() % (_max - _min + 1) + _min;
}


StoneLayer::StoneLayer()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	isMove = false;

	isPause = false;

	goldLayer = new GoldLayer();
	this->addChild(goldLayer);

	x_length = visibleSize.width / 5; 

	
	for (auto a = 0; a < 4; a++)
	{
		createRow();

		if (a == 0)
		{
			for (auto &nextStone : pebbles)
			{
				nextStone->setStartStone(true);
			}
		}		
	}	    
}


void StoneLayer::update(float dt)
{
	goldLayer->update(dt);

	if (!isPause)
	{
		if (isMove)
		{
			x_length -= STONE_VELOCITY; 

			for (auto &nextPebble : pebbles)
			{
				nextPebble->setPosition(Vec2(nextPebble->getPosition().x - STONE_VELOCITY, nextPebble->getPosition().y));

				if (nextPebble->getPosition().x + nextPebble->getContentSize().width / 2 <= 0)
					del_stones.pushBack(nextPebble);
			}			
		}
	}

	if (del_stones.size() > 0)
	{
		bool isStart = false;

		for (auto &peb : del_stones)
		{
			if (peb->isStartStone())
				isStart = true;

			this->removeChild(peb, true);
			pebbles.eraseObject(peb);		
			
		}

		if (isStart)
		{
			isStart = false;
			createRow();
		}

		del_stones.clear();		
	}
}

void StoneLayer::setIsMove(bool _is)
{
	isMove = _is;
	goldLayer->setisMove(_is);
}


void StoneLayer::pauseMe()
{
	isPause = true;
	goldLayer->pauseMe();
}

void StoneLayer::resumeMe()
{
	isPause = false;
	goldLayer->resumeMe();
}


Vector<Stone*> StoneLayer::getPebbles()
{
	return pebbles;
}


void StoneLayer::deleteGold(Sprite* _s)
{
	goldLayer->deleteGold(_s);
}


void StoneLayer::createRow()
{    
	vector<string> nfn;
	vector<string> tfn;

	Vec2 top_stone_pos;
	bool isStartStone = false;

	for (int a = 1; a <= 5; a++)
	{
		string n = "s00" + to_string(a) + ".png";
		nfn.push_back(n);
	}

	for (int a = 6; a <= 9; a++)
	{
		string n = "s00" + to_string(a) + ".png";
		tfn.push_back(n);
	}
	
	int count = rand_num(2, 5);

	float h = 0.0f;

	for (auto a = 1; a <= count; a++)
	{
		Stone *stone;
		int rn = 0;

		float scale = rand_num(60, 95) / 100.0f;
		
		if (a == count) {
			rn = rand_num(0, tfn.size() - 1);
			stone = Stone::create(tfn[rn]);			
			stone->setTopStone(true);
			scale = 1.0f;
			top_stone_pos = Vec2(x_length, h + stone->getContentSize().height*1.3f);
			isStartStone = stone->isStartStone();
		} else {
			rn = rand_num(0, nfn.size() - 1);
			stone = Stone::create(nfn[rn]);
			nfn.erase(nfn.begin() + rn);					
		}

		stone->setAnchorPoint(Vec2(0.5f, 0.0f));

		stone->setScale(scale);

		Size new_size;
		new_size.height = stone->getContentSize().height * scale;
		new_size.width = stone->getContentSize().width * scale;
		stone->setContentSize(new_size);
							
		stone->setPosition(Vec2(x_length, h));		
									
		this->addChild(stone);

		pebbles.pushBack(stone);

		h += stone->getContentSize().height * 0.97f;							
	}

	// distance
	x_length += rand_num(visibleSize.width * 0.28f, visibleSize.width * 0.6f);

	// create gold
	if (!isStartStone)
	{
		if (UserDefault::getInstance()->getBoolForKey("ARCADE", true))
		{
			if (rand() % 2)
			{
				goldLayer->createGold(top_stone_pos);
			}
			else {
				auto np = getLeftNearStone(top_stone_pos);
				goldLayer->createGold(top_stone_pos - np / 2);
			}
		} else {
			goldLayer->createGold(top_stone_pos);
		}
	}
}


Vec2 StoneLayer::getNearStone(Vec2 _p)
{
	Vec2 res;

	res.x = visibleSize.width;

	for (auto &nextStone : pebbles)
	{
		if (nextStone->isTopStone())
		{
			if (!nextStone->isStartStone() && nextStone->getPosition().x - _p.x < res.x)
			{
				res.x = nextStone->getPosition().x - _p.x;
				res.y = nextStone->getPosition().y + nextStone->getContentSize().height - _p.y;
			}
		}
	}

	return res;
}


Vec2 StoneLayer::getLeftNearStone(Vec2 _p)
{
	Vec2 res;

	res.x = visibleSize.width;

	for (auto &nextStone : pebbles)
	{
		if (nextStone->isTopStone())
		{
			if ((_p.x - nextStone->getPosition().x > 0) && (_p.x - nextStone->getPosition().x < res.x))
			{
				res.x = _p.x - nextStone->getPosition().x;
				res.y = -abs(nextStone->getPosition().y + nextStone->getContentSize().height - _p.y);
			}
		}
	}

	return res;
}


Vector<Sprite*> StoneLayer::getGolds()
{
	return goldLayer->getGolds();
}