/*
 * GameOverScene.cpp
 *
 *  Created on: 2014��11��10��
 *      Author: Yang
 */



#include "GameOverScene.h"
#include "GameDefine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init()
{
	if( !Layer::init())
	{
		return false;
	}


	//���¿�ʼ��Ϸ
	auto restartItem = MenuItemFont::create("Restart",CC_CALLBACK_1(GameOverScene::menuRestartCallback,this));
	restartItem -> setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/2));

	//�˳���Ϸ
	auto exit = MenuItemFont::create("Exit",CC_CALLBACK_1(GameOverScene::menuExitCallback,this));;
	exit -> setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT/3));

	auto menu = Menu::create(restartItem,exit,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	return true;
}

void GameOverScene::menuRestartCallback(Ref* pObject)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(CCTransitionProgressRadialCCW::create(1,scene));
}

void GameOverScene::menuExitCallback(Ref* pObject)
{
	Director::getInstance()->end();
}


















