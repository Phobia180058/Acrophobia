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
	//创建世界边框对象
	PhysicsBody *body = PhysicsBody::createEdgeBox(visibleSize, pm,1.0f);
	auto edgeBody = Node::create();
	edgeBody->setPosition(Vec2(visibleSize.width / 2+origin.x, visibleSize.height / 2+origin.y));

	edgeBody->setPhysicsBody(body);
	this->addChild(edgeBody);
	//创建按钮
	auto goItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(SecondScene::menuGoCallback, this));
	goItem->setPosition(Vec2(visibleSize.width / 5, visibleSize.height / 5));
	auto menu = Menu::create(goItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	//定义Map对象并且循环创建Map中键值对
	this->map = Map<int, cocos2d::Sprite*>();
	for (int i = 0; i < 50; i++) {
		Sprite* sprite = Sprite::create("ball.png");
		PhysicsBody *body = PhysicsBody::createCircle(sprite->getContentSize().width / 2,pm);
		sprite->setPhysicsBody(body);
		map.insert(i, sprite);   //添加元素
	}
	return true;
}

void SecondScene::menuGoCallback(Ref*pSender) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::vector<int> vec = this->map.keys();      //创建vector对象来存储map中的key方便遍历
for (int key : vec) {                           //循环
Sprite* sprite = map.at(key);
		float x = CCRANDOM_0_1() * visibleSize.width;
		float y = CCRANDOM_0_1() * visibleSize.height;
		sprite->setPosition(Vec2(x, y));
		this->removeChild(sprite);
		this->addChild(sprite);
	}
}
