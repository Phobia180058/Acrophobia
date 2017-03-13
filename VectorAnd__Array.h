#pragma once
#ifndef _SECONDSCENE_H_
#define _SECONDSCENE_H_
#include "cocos2d.h"
USING_NS_CC;

class SecondScene :public cocos2d::Layer
{
	//__Array *arraylist;   采用__Array容器，需要析构函数来进行内存管理和内存释放
	Vector<cocos2d::Sprite*> vector;
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	CREATE_FUNC(SecondScene);
	void menuGoCallback(Ref* pSender);
	//~SecondScene();
};

#endif // !_SECONDSCENE_H_
