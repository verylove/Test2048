/*
 * GameOverScene.cpp
 *
 *  Created on: 2014年11月10日
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

void GameOverScene::setScore(int score)
{
	Label* scoreLabel = (Label*)this->getChildByTag(100);
	scoreLabel->setString(StringUtils::format("%d",score));
}

bool GameOverScene::init()
{
	if( !Layer::init())
	{
		return false;
	}

	Sprite* bg = Sprite::create("end.png");
	bg->ignoreAnchorPointForPosition(false);
	bg->setAnchorPoint(Point(0,0));
	bg->setPosition(0,0);
	this->addChild(bg);


	//成绩
	TTFConfig config("HelloKitty.ttf",80);
	Label* scoreLabel = Label::createWithTTF(config,StringUtils::format("%d",0));
	scoreLabel->setPosition(Point(GAME_SCREEN_WIDTH/2,GAME_SCREEN_HEIGHT - 420));
	scoreLabel->setTag(100);
	this->addChild(scoreLabel);

	//重新开始游戏
	//auto restartItem = MenuItemFont::create("Restart",CC_CALLBACK_1(GameOverScene::menuRestartCallback,this));
	auto restartItem = MenuItemImage::create(
											"restart.png",
											"restart_dark.png",
											CC_CALLBACK_1(GameOverScene::menuRestartCallback,this));
	restartItem -> setPosition(Point(GAME_SCREEN_WIDTH/2-100,GAME_SCREEN_HEIGHT/2));

	//退出游戏
	//auto exit = MenuItemFont::create("Exit",CC_CALLBACK_1(GameOverScene::menuExitCallback,this));;
	auto exit = MenuItemImage::create(
									  "exit.png",
									  "exit_dark.png",
									  CC_CALLBACK_1(GameOverScene::menuExitCallback,this));
	exit -> setPosition(Point(GAME_SCREEN_WIDTH/2+100,GAME_SCREEN_HEIGHT/2));

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


















