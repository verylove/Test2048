/*
 * GameScene.h
 *
 *  Created on: 2014年11月7日
 *      Author: Yang
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "cocos2d.h"
#include "GameDefine.h"
#include "NumberTiled.h"

USING_NS_CC;

class GameScene : public Layer
{


public :

	Vector<NumberTiled *> m_allTiled;//一个Vector（集合）来保存所有的块
	int map[GAME_ROWS][GAME_COLS];//添加一个二维数组,map	用来保存每个格子的状况哟~

	void newNumberTiled();//添加一个方法，产生一个新块

	LayerColor* colorBack;//LayerColor指针

	int m_x,m_y;//记录屏幕开始触摸时的坐标
	int score;

	bool m_startMove;//判断是否开始触摸，并且在一个滑动结束前，不允许再次获取触摸
	void moveAllTiled( MOVE_DIR dir );//就是根据滑动的方向，对相应方向的数字块 进行合并或者移动

	void judgeMove();

	// 播放哪个音乐
	bool m_sound_clear;

	bool isMoveUp = false;
	bool isMoveDown = false;
	bool isMoveRight = false;
	bool isMoveLeft = false;

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool init();

	static Scene* createScene();

	CREATE_FUNC(GameScene);


};


#endif /* GAMESCENE_H_ */
