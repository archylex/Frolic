#include "TopGUI.h"
#include "FrolicArcade.h"
#include "FrolicEdu.h"


TopGUI::TopGUI()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	score = 0;

	auto gold_gui = Sprite::createWithSpriteFrameName("gui_gold.png");
	gold_gui->setPosition(visibleSize.width * 0.1f, visibleSize.height * 0.9f);
	this->addChild(gold_gui);

	auto b1 = Button::create("button_pause.png", "button_pause.png", "button_pause.png", Widget::TextureResType::PLIST);
	b1->setPosition(Vec2(visibleSize.width * 0.9f, visibleSize.height * 0.9f));

	b1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (UserDefault::getInstance()->getBoolForKey("ARCADE", true))
			{
				FrolicArcade *game = (FrolicArcade*)this->getParent();
				game->getPauseMenu();
			} else {
				FrolicEdu *game = (FrolicEdu*)this->getParent();
				game->getPauseMenu();
			}
			break;		
		}
	});

	this->addChild(b1);
	
	gold_label = Label::createWithBMFont("font.fnt", "0");
	gold_label->setAnchorPoint(Vec2(0.0f, 0.5f));
	gold_label->setPosition(Vec2(visibleSize.width * 0.1f + gold_gui->getContentSize().width / 12, visibleSize.height * 0.9f));
	this->addChild(gold_label, 2);
	gold_label->setScale(0.3f);
}


void TopGUI::setScore(int _s)
{
	score = _s;
	gold_label->setString(to_string(score));
}


int TopGUI::getScore()
{
	return score;
}


void TopGUI::showHighScore()
{
	auto hgold = Sprite::createWithSpriteFrameName("hs.png");
	hgold->setPosition(visibleSize.width * 0.08f, visibleSize.height * 0.9f);
	this->addChild(hgold);

	gold_label->setPosition(Vec2(visibleSize.width * 0.13f, visibleSize.height * 0.9f));

	auto scaleIn = ScaleTo::create(0.2f, 1.25f);
	auto scaleOut = ScaleTo::create(0.2f, 1.0f);
	auto seq = Sequence::create(scaleIn, scaleOut, nullptr);
	hgold->runAction(seq);
}