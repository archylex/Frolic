#include "EduUI.h"
#include "FrolicEdu.h"


EduUI::EduUI()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	info_vec = false;
	lock_start = false;

	firstParamPic = Sprite::create();
	firstParamPic->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.21f));
	firstParamPic->setScale(0.73f);	
	this->addChild(firstParamPic, 1);
	
	secondParamPic = Sprite::create();
	secondParamPic->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.14f));
	secondParamPic->setScale(0.73f);
	secondParamPic->setColor(Color3B(242, 206, 0));
	this->addChild(secondParamPic, 1);
	
	firstParamValue = Label::createWithBMFont("font.fnt", "0");
	firstParamValue->setAnchorPoint(Vec2(0.0f, 0.5f));
	firstParamValue->setPosition(Vec2(visibleSize.width * 0.14f, visibleSize.height * 0.2f));
	firstParamValue->setScale(0.3f);
	firstParamValue->setHorizontalAlignment(TextHAlignment::LEFT);
	this->addChild(firstParamValue, 1);
	
	secondParamValue = Label::createWithBMFont("font.fnt", "0");
	secondParamValue->setAnchorPoint(Vec2(0.0f, 0.5f));
	secondParamValue->setPosition(Vec2(visibleSize.width * 0.14f, visibleSize.height * 0.14f));
	secondParamValue->setScale(0.3f);
	secondParamValue->setHorizontalAlignment(TextHAlignment::LEFT);
	this->addChild(secondParamValue, 1);
		
	auto editFieldPic = Sprite::createWithSpriteFrameName("edit.png");
	editFieldPic->setPosition(Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.2f));
	this->addChild(editFieldPic, 1);

	answerPic = Sprite::create();
	answerPic->setPosition(Vec2(editFieldPic->getContentSize().width * 0.23f, editFieldPic->getContentSize().height * 0.5f));
	answerPic->setScale(0.7f);
	editFieldPic->addChild(answerPic, 1);

	tf = TextField::create();
	tf->setAnchorPoint(Vec2(1.0f, 0.5f));
	tf->setPosition(Vec2(editFieldPic->getContentSize().width * 0.83f, editFieldPic->getContentSize().height * 0.5f));
	tf->setFontSize(32);
	tf->setMaxLength(5);
	tf->setMaxLengthEnabled(true);
	tf->setColor(Color3B(255, 255, 255));
	tf->setPlaceHolder("0");
	tf->setString("0");
	tf->setTextHorizontalAlignment(TextHAlignment::RIGHT);
	editFieldPic->addChild(tf, 2);

	tf->addEventListenerTextField(this, textfieldeventselector(EduUI::checkString));

	auto checkbox = CheckBox::create("check_box_normal.png",
			"check_box_normal.png",
			"check_box_active.png",
			"check_box_normal.png",
			"check_box_normal.png", Widget::TextureResType::PLIST);

	checkbox->setPosition(Vec2(visibleSize.width * 0.1f, visibleSize.height * 0.08f));

	checkbox->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				info_vec ? info_vec = false : info_vec = true;

				FrolicEdu *game = (FrolicEdu*)this->getParent();
				game->vec_info();
				break;
		}
	});

	this->addChild(checkbox, 3);

	auto checkboxTitle = Label::createWithBMFont("font.fnt", "INFO");
	checkboxTitle->setAnchorPoint(Vec2(0.0f, 0.5f));
	checkboxTitle->setPosition(Vec2(visibleSize.width * 0.12f, visibleSize.height * 0.075f));
	checkboxTitle->setScale(0.3f);
	this->addChild(checkboxTitle, 1);	

	auto button = Button::create("menu_play.png", "menu_play.png", "menu_play.png", Widget::TextureResType::PLIST);	
	button->setPosition(Vec2(editFieldPic->getPosition().x + (editFieldPic->getContentSize().width - button->getContentSize().width) / 2, visibleSize.height * 0.08f));
	button->setScale(0.8f);

	button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (!lock_start)
			{
				float number;
				istringstream iss(tf->getString());
				iss >> number;

				if (answerPic->getResourceName() == "v.png")
					number *= 10;

				FrolicEdu *game = (FrolicEdu*)this->getParent();
				game->startJump(abs(number));

				tf->setString("0");

				lock_start = true;
			}
			break;
		}
	});

	this->addChild(button, 1);
}


void EduUI::horizontalLine(Vec2 _startPos, Vec2 _endPos, string _t)
{
	Color3B yellow(242, 206, 0);

	auto vec_base = Sprite::createWithSpriteFrameName("arrow-head.png");
	vec_base->setAnchorPoint(Vec2(0.5f, 1.0f));
	vec_base->setFlippedX(true);
	vec_base->setScale(0.5f);
	vec_base->setRotation(-90);
	vec_base->setPosition(_startPos);
	vec_base->setColor(yellow);
	this->addChild(vec_base, 1);
	arrow_array.pushBack(vec_base);
	
	auto rectNode = DrawNode::create();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(_startPos.x + vec_base->getContentSize().height*0.5f, _startPos.y - vec_base->getContentSize().height*0.09f);
	rectangle[1] = Vec2(_startPos.x + vec_base->getContentSize().height*0.5f, _startPos.y + vec_base->getContentSize().height*0.09f);
	rectangle[2] = Vec2(_endPos.x - vec_base->getContentSize().height*0.5f, _endPos.y + vec_base->getContentSize().height*0.09f);
	rectangle[3] = Vec2(_endPos.x - vec_base->getContentSize().height*0.5f, _endPos.y - vec_base->getContentSize().height*0.09f);
		
	Color4F white(0.95f, 0.81f, 0.0f, 1.0f);
	rectNode->drawPolygon(rectangle, 4, white, 1, white);
	this->addChild(rectNode, 1);
	rects.pushBack(rectNode);
	
	auto vec_head = Sprite::createWithSpriteFrameName("arrow-head.png");
	vec_head->setAnchorPoint(Vec2(0.5f, 1.0f));
	vec_head->setRotation(90);
	vec_head->setScale(0.5f);
	vec_head->setPosition(_endPos);
	vec_head->setColor(yellow);
	this->addChild(vec_head, 1);
	arrow_array.pushBack(vec_head);
	
	auto h_sprite = Sprite::createWithSpriteFrameName(_t);
	h_sprite->setPosition(Vec2((_startPos.x + _endPos.x) / 2, _startPos.y - h_sprite->getContentSize().height*0.5f));
	h_sprite->setScale(0.5f);	
	this->addChild(h_sprite, 1);
	arrow_array.pushBack(h_sprite);
}


void EduUI::verticalLine(Vec2 _startPos, Vec2 _endPos)
{
	Color3B yellow(242, 206, 0);
	auto vec_base = Sprite::createWithSpriteFrameName("arrow-head.png");
	vec_base->setAnchorPoint(Vec2(0.5f, 1.0f));
	vec_base->setScale(0.5f);
	vec_base->setPosition(_endPos);
	vec_base->setColor(yellow);
	this->addChild(vec_base, 1);
	arrow_array.pushBack(vec_base);

	auto rectNode = DrawNode::create();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(_endPos.x - vec_base->getContentSize().width*0.1f, _endPos.y - vec_base->getContentSize().height*0.5f);
	rectangle[1] = Vec2(_endPos.x + vec_base->getContentSize().width*0.1f, _endPos.y - vec_base->getContentSize().height*0.5f);
	rectangle[2] = Vec2(_startPos.x + vec_base->getContentSize().width*0.1f, _startPos.y + vec_base->getContentSize().height*0.5f);
	rectangle[3] = Vec2(_startPos.x - vec_base->getContentSize().width*0.1f, _startPos.y + vec_base->getContentSize().height*0.5f);

	Color4F white(0.95f, 0.81f, 0.0f, 1.0f);
	rectNode->drawPolygon(rectangle, 4, white, 1, white);
	this->addChild(rectNode, 1);
	rects.pushBack(rectNode);
	
	auto h_sprite = Sprite::createWithSpriteFrameName("h.png");
	h_sprite->setPosition(Vec2(_startPos.x + h_sprite->getContentSize().width*0.3f, (_startPos.y + _endPos.y) / 2));
	h_sprite->setRotation(-90);
	h_sprite->setScale(0.5f);
	this->addChild(h_sprite, 1);
	arrow_array.pushBack(h_sprite);
	
	auto vec_head = Sprite::createWithSpriteFrameName("arrow-head.png");
	vec_head->setAnchorPoint(Vec2(0.5f, 1.0f));
	vec_head->setFlippedY(true);
	vec_head->setScale(0.5f);
	vec_head->setPosition(Vec2(_startPos.x, _startPos.y + vec_base->getContentSize().height*0.5f));
	vec_head->setColor(yellow);
	this->addChild(vec_head, 1);
	arrow_array.pushBack(vec_head);
}



void EduUI::trajectoryLine(Vec2 _startPos, Vec2 _endPos, float _vel, float _angle)
{
	float mt = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	
	while (x < _endPos.x)
	{
		mt += 0.2f;

		auto point = Sprite::createWithSpriteFrameName("point.png");

		x = _vel * cos(_angle) * mt;
		y = _vel * sin(_angle) * mt - (10 * pow(mt, 2) / 2);

		point->setPosition(_startPos.x + x, _startPos.y + y);

		point->setColor(Color3B(242, 206, 0));

		this->addChild(point, 1);

		arrow_array.pushBack(point);
	}
}


void EduUI::angleLine(Vec2 _startPos)
{
	auto angle_pic = Sprite::createWithSpriteFrameName("a.png");
	angle_pic->setAnchorPoint(Vec2(0.0f, 0.0f));
	angle_pic->setScale(0.5f);
	angle_pic->setPosition(_startPos + Vec2(visibleSize.width / 20, visibleSize.height / 32));
	this->addChild(angle_pic, 1);
	arrow_array.pushBack(angle_pic);
}


void EduUI::eraseLines()
{
	if (arrow_array.size() > 0) {
		for (auto &l : arrow_array)
		{
			l->removeFromParentAndCleanup(true);
		}
		arrow_array.clear();
	}

	if (rects.size() > 0) {
		for (auto &l : rects)
		{
			l->removeFromParentAndCleanup(true);
		}
		rects.clear();
	}	
}


void EduUI::showInfoVec(Vec2 _pl, Vec2 _np, float  _vel, float _angle)
{
	if (info_vec)
	{
		eraseLines();

		if (firstParamPic->getResourceName() != "h.png")
			horizontalLine(_pl, Vec2(_np.x + _pl.x, _pl.y), firstParamPic->getResourceName());

		verticalLine(Vec2(_pl.x + _np.x, _pl.y), Vec2(_pl.x + _np.x, _pl.y + _np.y));

		trajectoryLine(_pl, _np, _vel, _angle);

		angleLine(_pl);
	}
	else {
		eraseLines();
	}
}


void EduUI::setFirstParamName(string _s)
{
	firstParamPic->initWithSpriteFrameName(_s);
}


void EduUI::setSecondParamName(string _s)
{
	secondParamPic->initWithSpriteFrameName(_s);
}


void EduUI::setFirstParamValue(float _s, string _m)
{

	firstParamValue->setString(FrolicUtils::float2ToString(_s) + _m);
}


void EduUI::setSecondParamValue(float _s, string _m)
{
	secondParamValue->setString(FrolicUtils::float2ToString(_s) + _m);
}


void EduUI::setAnswerPic(string _m)
{
	answerPic->initWithSpriteFrameName(_m);
}


void EduUI::setLockStart(bool _m)
{
	lock_start = _m;
}


void EduUI::checkString(Ref *ref, TextFiledEventType type)
{
	switch (type)
	{
	case TEXTFIELD_EVENT_ATTACH_WITH_IME: break;
	case TEXTFIELD_EVENT_DETACH_WITH_IME: break;
	case TEXTFIELD_EVENT_INSERT_TEXT: 
		if (!FrolicUtils::isDigits(tf->getString()))
			tf->setString("");		
		break;
	case TEXTFIELD_EVENT_DELETE_BACKWARD: break;
	default: break;
	}
	
}