/*
 * MainScene.cpp
 *
 *  Created on: 2014Äê11ÔÂ6ÈÕ
 *      Author: Yang
 */


#include "MainScene.h"

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
	labelGame->setPosition(100,300);
	this->addChild(labelGame);


	return true;
}

