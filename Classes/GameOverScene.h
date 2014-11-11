/*
 * GameOverScene.h
 *
 *  Created on: 2014��11��10��
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

	//���¿�ʼ��Ϸ�Ļص�����
	void menuRestartCallback(Ref* pObject);
	//�˳��Ļص�����
	void menuExitCallback(Ref* pObject);

	void setScore(int score);

};




#endif /* GAMEOVERSCENE_H_ */
