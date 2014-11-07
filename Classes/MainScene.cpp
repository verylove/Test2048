/*
 * MainScene.cpp
 *
 *  Created on: 2014Äê11ÔÂ6ÈÕ
 *      Author: Yang
 */


#include "MainScene.h"
#include "GameDefine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	 auto scene = Scene::create();

	 auto layer = MainScene::create();

	 scene->addChild(layer);

	 return scene;
}


bool MainScene::init()
{
	if(!Layer::init()){
		return false;
	}

	TTFConfig config("HelloKitty.ttf",60);

	auto labelGame = Label::createWithTTF(config,"2048");
	labelGame->setPosition(GAME_SCREEN_WIDTH/2,(GAME_SCREEN_HEIGHT*2)/3);
	this->addChild(labelGame);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto gameScene = GameScene::createScene();
	this->addChild(gameScene);


	return true;
}

void MainScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

