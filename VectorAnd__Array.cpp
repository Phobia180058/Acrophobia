#include "pch.h"
#include "SecondScene.h"

Scene* SecondScene::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);   //可以删除，用来测试
	auto layer = SecondScene::create();
	scene->addChild(layer);
	return scene;
}

bool SecondScene::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	PhysicsMaterial pm;
	pm.restitution = 1;
	pm.friction = 0;
	pm.density = 0;
	auto body = PhysicsBody::createEdgeBox(visibleSize,pm,5.0f);   //创建物体对象
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(body);   //节点对象和物体相关联
	this->addChild(edgeNode);

	//添加GO按钮
	auto closeItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png", CC_CALLBACK_1(SecondScene::menuGoCallback, this));
	closeItem->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 5));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	this->vector = Vector<cocos2d::Sprite*>(50);//不需要内存管理
	
	for (int i = 0; i < 50; i++) {
		auto sprite = Sprite::create("ball.png");
		auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2,pm);
		sprite->setPhysicsBody(body);
		this->vector.pushBack(sprite);
	}

    /*this->arraylist = __Array::createWithCapacity(50);        
    this->arraylist->retain();

	for (int i = 0; i < 50; i++) {
		Sprite *sprite = Sprite::create("BALL.png");
		auto body = PhysicsBody::createCircle(sprite->getContentSize().width/2,pm);
		sprite->setPhysicsBody(body);
		this->arraylist->addObject(sprite);

	}
	*/
	return true;

}

void SecondScene::menuGoCallback(Ref *pSender) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*
	Ref *obj = NULL;
	CCARRAY_FOREACH(this->arraylist, obj) {
		Sprite *sprite = (Sprite*)obj;
		int x = CCRANDOM_0_1() * visibleSize.width;
		int y = CCRANDOM_0_1() * visibleSize.height;
		sprite->setPosition(Vec2(x, y));
		this->removeChild(sprite);
		this->addChild(sprite);
    } */
	for (int i = 0; i < this->vector.size(); i++) {
		float x = CCRANDOM_0_1() * visibleSize.width;
		float y = CCRANDOM_0_1() * visibleSize.height;
		Sprite* sprite = vector.at(i);
		sprite->setPosition(Vec2(x, y));
		this->removeChild(sprite);
		this->addChild(sprite);
	}
}


/*

SecondScene::~SecondScene() {
	this->arraylist->removeAllObjects();
	CC_SAFE_RELEASE_NULL(this->arraylist);
}
*/
