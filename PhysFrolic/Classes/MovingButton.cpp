#include "MovingButton.h"
#include "SimpleAudioEngine.h"
#include "FrolicUtils.h"
#include "TitleScene.h"


MovingButton::MovingButton()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	spiral_radius = 0.0f;
	fi = 0.0f;
	fi_step = 0.05f;
	alfa = 0.0f;
	start_angle = 0.0f;
	beta_angle = 0.0f;
	start_pos = Vec2(0.0f, 0.0f);
	isMove = true;	
	change_pic_button = false;
	callfunc_button = nullptr;
}


void MovingButton::update(float dt)
{
	float scale = fi / 4.712385f; // 1.5 * PI
	int a = 0;

	if (isMove)
	{		
		float x = spiral_radius * fi * cos(fi);
		float y = spiral_radius * fi * sin(fi);

		a = 0;
		for (auto &btn : myfunctions)
		{
			btn.btn->setScale(scale);
			btn.btn->setPosition(FrolicUtils::rotate_coordinates(Vec2(x, y), FrolicUtils::degree_to_rad(start_angle + beta_angle * a), Vec2(visibleSize.width / 2, start_pos.y)));
			a++;
		}

		// particle tail
		a = 0;
		for (auto &star : stars)
		{
			star->setScale(scale);
			star->setPosition(FrolicUtils::rotate_coordinates(Vec2(x, y), FrolicUtils::degree_to_rad(start_angle + beta_angle * a), Vec2(visibleSize.width / 2, start_pos.y)));
			a++;
		}

		fi += fi_step;

		if (FrolicUtils::rad_to_degree(fi) >= 270 || FrolicUtils::rad_to_degree(fi) < 0)
			isMove = false;

		if (FrolicUtils::rad_to_degree(fi) < 0 && callfunc_button != nullptr)
		{
			callfunc_button();
			callfunc_button = nullptr;
		}
	}	

	//
	a = 0;
	for (auto &tail : tails)
	{
		int delta = 1;

		(a % 2) ? delta = 1 : delta = -1;

		auto parent_size = tail->getParent()->getContentSize();
		auto radius = parent_size.width * 0.6f;
		
		tail->setPosition(Vec2(parent_size.width/2 + delta * radius * cos(alfa), parent_size.height/2 + delta * radius * sin(alfa)));
		
		tail->setRotation(90 - (FrolicUtils::rad_to_degree(alfa)));

		tail->setScale(scale);

		a++;
	}
	
	if (!isMove)
	{
		if (stars.size() > 0)
		{
			for (auto &star : stars)
			{
				star->removeFromParentAndCleanup(true);
			}

			stars.clear();
		}		
	}

	alfa += 0.1f;

	if (alfa >= 6.28f)
		alfa = 0.0f;
}


void MovingButton::addButton(const string _b, bool _hidden, const std::function<void()> &func, const std::function<void()> &cb_func)
{
	MyButton mybtn;

	mybtn.func = nullptr;
	mybtn.callback_func = nullptr;

	mybtn.btn = Button::create(_b, _b, _b, Widget::TextureResType::PLIST);
	mybtn.btn->setTag(myfunctions.size());
	
	mybtn.func = func;

	mybtn.callback_func = cb_func;

	mybtn.isHide = _hidden;
		
	mybtn.btn->addTouchEventListener([&](Object* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (UserDefault::getInstance()->getBoolForKey("SFX", true))
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("click.mp3");

			auto obj = sender;
			int num = (int)((Button *)obj)->getTag();
			
			if (myfunctions[num].isHide)
				stop();
			else
				callfunc_button = nullptr;

			if (myfunctions[num].callback_func != nullptr)
				callfunc_button = myfunctions[num].callback_func;
			
			if (myfunctions[num].func != nullptr)
				myfunctions[num].func();

			if (change_pic_button)
			{
				myfunctions[num].btn->loadTextures(change_pic_name, change_pic_name, change_pic_name, TextureResType::PLIST);
				change_pic_button = false;
			}
			
			break;
		}
	});

	myfunctions.push_back(mybtn);

	this->addChild(mybtn.btn, 5);

	// moving elements
	for (int a = 0; a < 2; a++)
	{
		auto tail = Sprite::createWithSpriteFrameName("menu_tail.png");

		a % 2 ? tail->setFlippedY(false) : tail->setFlippedY(true);
		a % 2 ? tail->setFlippedX(false) : tail->setFlippedX(true);

		mybtn.btn->addChild(tail, 1);

		tails.pushBack(tail);
	}		
}


void MovingButton::createParticleTails()
{
	for (int a = 0; a < myfunctions.size(); a++)
	{
		auto particleSystem = ParticleSystemQuad::create("particle_texture.plist");
		particleSystem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		this->addChild(particleSystem, 1);
		particleSystem->setAutoRemoveOnFinish(true);
		stars.pushBack(particleSystem);
	}
}


void MovingButton::setStartAngle(float _out)
{
	start_angle = _out;
}


void MovingButton::setBetaAngle(float _out)
{
	beta_angle = _out;
}


void MovingButton::setStartPosition(Vec2 _out)
{
	start_pos = _out;
}


void MovingButton::setSpiralRadius(float _out)
{
	spiral_radius = _out;
}


void MovingButton::setChangePicName(string _out)
{
	change_pic_name = _out;
	change_pic_button = true;
}


void MovingButton::start()
{
	fi_step = 1 * 0.05f;
	isMove = true;
	createParticleTails();
}


void MovingButton::stop()
{
	fi_step = -1 * 0.05f;
	isMove = true;
	createParticleTails();
}