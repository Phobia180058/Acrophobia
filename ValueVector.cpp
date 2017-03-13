#include "pch.h"
#include "SecondScene.h"

Scene* SecondScene::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = SecondScene::create();
	scene->addChild(layer);
	return scene;

}

bool SecondScene::init() {
	if (!Layer::create()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//创建PhysicsMaterial对象
	PhysicsMaterial pm;
	pm.density = 0;
	pm.friction = 1;
	pm.restitution = 1;

	//创建世界边框
	PhysicsBody* body = PhysicsBody::createEdgeBox(visibleSize, pm);
	Node* edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	auto goItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(SecondScene::menuGoCallback, this));
	goItem->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 2));
	auto menu = Menu::create(goItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	for (int i = 0; i < 50; i++) {
		Value name("ball.png");      //ValueVector添加元素前需要先把数据类型转化为Value
		list.push_back(name);        //添加元素

	}
 
	return true;
}

void SecondScene::menuGoCallback(Ref*pSender) {
	PhysicsMaterial pm;
	pm.density = 0;
	pm.friction = 1;
	pm.restitution = 1;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int tag = 0;                //Sprite的标签
	for (auto &v : list) {
		int x = CCRANDOM_0_1() * visibleSize.width;
		int y = CCRANDOM_0_1() * visibleSize.height;
		//this->removeChildByTag(tag);          //上次所标识的精灵去除，否则上次出现精灵不会消除
		Sprite* sprite = Sprite::create(v.asString());    //ValueVector中元素使用时需要先把类型转化为所需的数据类型
		auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2, pm);
		sprite->setPhysicsBody(body);

		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite, 0, tag++);     //按照tag来添加Sprite
	}
}
