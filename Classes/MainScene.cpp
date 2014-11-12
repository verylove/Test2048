/*
 * MainScene.cpp
 *
 *  Created on: 2014Äê11ÔÂ6ÈÕ
 *      Author: Yang
 */


#include "MainScene.h"
#include "GameDefine.h"
#include "GameScene.h"
#include "AboutScene.h"

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

	Sprite*  bg = Sprite::create("start.png");
	bg -> ignoreAnchorPointForPosition(false);
	bg -> setAnchorPoint(Point(0,0));
	this->addChild(bg);

	TTFConfig config("HelloKitty.ttf",60);

	auto labelGame = Label::createWithTTF(config,"2048");
	labelGame->setPosition(GAME_SCREEN_WIDTH/2,(GAME_SCREEN_HEIGHT*2)/3);
	this->addChild(labelGame);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto startItem = MenuItemImage::create(
										"start_btn.png",
										"start_dark.png",
										CC_CALLBACK_1(MainScene::menuStartCallback,this));
	startItem->setPosition(Vec2(origin.x + visibleSize.width/2,
								origin.y + visibleSize.height/2));


	auto closeItem = MenuItemImage::create(
										   "exit_btn.png",
										   "exit_sdark.png",
										   CC_CALLBACK_1(MainScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
								origin.y + closeItem->getContentSize().height/2+50));

	auto infoItem = MenuItemImage::create("about_btn.png",
										  "about_dark.png",
										  CC_CALLBACK_1(MainScene::menuItemCallback,this));

	infoItem->setPosition(Vec2(origin.x + visibleSize.width - infoItem->getContentSize().width/2 ,
							   origin.y + infoItem->getContentSize().height/2+200));


	auto menu = Menu::create(startItem,infoItem,closeItem,NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}


void MainScene::menuItemCallback(Ref* pSender)
{
	auto aboutScene = AboutScene::createScene();
	Director::getInstance()->replaceScene(CCTransitionProgressRadialCCW::create(1,aboutScene));
}


void MainScene::menuStartCallback(Ref* pSender)
{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(CCTransitionProgressRadialCCW::create(1,gameScene));

}

void MainScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

