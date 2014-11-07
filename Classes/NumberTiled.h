/*
 * NumberTiled.h
 *
 *  Created on: 2014年11月7日
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

	//存储行列位置 该位置的数字值
	int m_row,m_col;
	int m_number;

	//揿动到r,c 这表位置
	void moveTo(int r,int c);
	void doubleNumber();

	CREATE_FUNC(NumberTiled);

};


#endif /* NUMBERTILED_H_ */
