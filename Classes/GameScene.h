/*
 * GameScene.h
 *
 *  Created on: 2014��11��7��
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

	Vector<NumberTiled *> m_allTiled;//һ��Vector�����ϣ����������еĿ�
	int map[GAME_ROWS][GAME_COLS];//���һ����ά����,map	��������ÿ�����ӵ�״��Ӵ~

	void newNumberTiled();//���һ������������һ���¿�

	LayerColor* colorBack;//LayerColorָ��

	int m_x,m_y;//��¼��Ļ��ʼ����ʱ������
	int score;

	bool m_startMove;//�ж��Ƿ�ʼ������������һ����������ǰ���������ٴλ�ȡ����
	void moveAllTiled( MOVE_DIR dir );//���Ǹ��ݻ����ķ��򣬶���Ӧ��������ֿ� ���кϲ������ƶ�

	void judgeMove();

	// �����ĸ�����
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
