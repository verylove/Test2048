/*
 * GameOverScene.h
 *
 *  Created on: 2014年11月10日
 *      Author: Yang
 */

#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(GameOverScene);

	//重新开始游戏的回调函数
	void menuRestartCallback(Ref* pObject);
	//退出的回调函数
	void menuExitCallback(Ref* pObject);

	void setScore(int score);

};




#endif /* GAMEOVERSCENE_H_ */
