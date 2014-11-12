/*
 * AboutScene.h
 *
 *  Created on: 2014Äê11ÔÂ12ÈÕ
 *      Author: Yang
 */

#ifndef ABOUTSCENE_H_
#define ABOUTSCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class AboutScene : public Layer
{
public:
	virtual bool init();

	static Scene* createScene();

	CREATE_FUNC(AboutScene);

	void returnCallback(Ref* ref);
};



#endif /* ABOUTSCENE_H_ */
