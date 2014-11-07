/*
 * MainScene.h
 *
 *  Created on: 2014年11月6日
 *      Author: Yang
 */

#ifndef MAINSCENE_H_
#define MAINSCENE_H_

#include "cocos2d.h"
USING_NS_CC;

class MainScene : public Layer
{

public:
	//初始化场景
	virtual bool init();

	static Scene* createScene();

	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(MainScene);

};


#endif /* MAINSCENE_H_ */
