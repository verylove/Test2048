/*
 * AboutScene.cpp
 *
 *  Created on: 2014Äê11ÔÂ12ÈÕ
 *      Author: Yang
 */


#include "GameDefine.h"
#include "AboutScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* AboutScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AboutScene::create();
	scene->addChild(layer);

	return scene;
}


bool AboutScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Sprite* bg = Sprite::create("about.png");
	bg->ignoreAnchorPointForPosition(false);
	bg->setAnchorPoint(Point(0,0));

	TTFConfig config("HelloKitty.ttf",90);

	int score  = UserDefault::sharedUserDefault()->getIntegerForKey("TopScore");
	Label* scoreLabel = Label::createWithTTF(config,StringUtils::format("TOP %d",score));
	scoreLabel->setPosition(500,300);
	scoreLabel->setColor(Color3B::BLUE);
	this->addChild(bg);
	this->addChild(scoreLabel);

	auto returnItem = MenuItemImage::create("return.png",
											"return_dark.png",
											CC_CALLBACK_1(AboutScene::returnCallback,this));
	returnItem->setPosition(Point(100,GAME_SCREEN_HEIGHT-returnItem->getContentSize().height));

	Menu* menu = Menu::create(returnItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	return true;
}

void AboutScene::returnCallback(Ref* ref)
{
	auto mainScene = MainScene::createScene();
	Director::sharedDirector()->replaceScene(CCTransitionProgressRadialCW::create(1,mainScene));
}
