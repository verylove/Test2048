/*
 * NumberTiled.h
 *
 *  Created on: 2014��11��7��
 *      Author: Yang
 */

#ifndef NUMBERTILED_H_
#define NUMBERTILED_H_

#include "cocos2d.h"

USING_NS_CC;

class NumberTiled : public Node
{
public:

	bool init();

	//�洢����λ�� ��λ�õ�����ֵ
	int m_row,m_col;
	int m_number;

	//�춯��r,c ���λ��
	void moveTo(int r,int c);
	void doubleNumber();

	CREATE_FUNC(NumberTiled);

};


#endif /* NUMBERTILED_H_ */
