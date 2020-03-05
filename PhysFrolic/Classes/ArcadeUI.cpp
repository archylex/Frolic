#include "ArcadeUI.h"
#include "FrolicUtils.h"


ArcadeUI::ArcadeUI()
{
	arrow_base = Sprite::createWithSpriteFrameName("arrow-start.png");	
	arrow_base->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->addChild(arrow_base, 5);

	arrow_line = Sprite::createWithSpriteFrameName("arrow-line.png");	
	arrow_line->setAnchorPoint(Vec2(0.5f, 0.0f));
	arrow_line->setPosition(Vec2(arrow_base->getContentSize().width * 0.485f, arrow_base->getContentSize().height * 0.97f));
	arrow_base->addChild(arrow_line, 5);
		
	arrow = Sprite::createWithSpriteFrameName("arrow-head.png");
	arrow->setAnchorPoint(Vec2(0.5f, 0.0f));
	arrow->setPosition(Vec2(arrow_line->getContentSize().width * 0.49f, arrow_line->getContentSize().height * 0.98f));
	arrow_line->addChild(arrow, 5);
}


void ArcadeUI::setArrowPosition(Vec2 _pos, float _angle, float _velocity)
{
	float arrow_angle = 90 - FrolicUtils::rad_to_degree(_angle);
	float arrow_x = _pos.x + sin(FrolicUtils::degree_to_rad(arrow_angle)) * 2.1f * arrow->getContentSize().width;
	float arrow_y = _pos.y + cos(FrolicUtils::degree_to_rad(arrow_angle)) * 2.1f * arrow->getContentSize().width;
	arrow_base->setPosition(Vec2(arrow_x, arrow_y));	
	arrow_base->setRotation(arrow_angle);		
	arrow_line->setScaleY(_velocity / 100);
	arrow->setScaleY(100 / _velocity);
}