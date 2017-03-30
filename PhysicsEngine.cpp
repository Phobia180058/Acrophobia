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
		std::ostringstream stringStream;   //调用ostringstream来拼接int和字符串
		stringStream << "key_" << i;
		std::string s = stringStream.str();     //将stringstream中字符串取出
		std::pair<std::string, Value> pair1(s, Value("ball.png"));    //构造一个键值对，注意值得类型需要是Value
		map.insert(pair1);     //insert只能如此添加

		map[s] = "ball.png";
	}
 
	return true;
}

void SecondScene::menuGoCallback(Ref*pSender) {
	PhysicsMaterial pm;
	pm.density = 0;
	pm.friction = 1;
	pm.restitution = 1;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int tag = 0;  //sprite标签
	for (auto &pair : map) {       //按键值对遍历
		float x = CCRANDOM_0_1() * visibleSize.width;
		float y = CCRANDOM_0_1() * visibleSize.height;
		this->removeChildByTag(tag);
		Sprite* sprite = Sprite::create(pair.second.asString());      //按键值对值来设置
		auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2,pm);
		sprite->setPhysicsBody(body);
		sprite->setPosition(Vec2(x, y));
		this->addChild(sprite, 0, tag++);
	}
}
