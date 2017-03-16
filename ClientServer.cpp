#include "ODSocketDemo.h"

Scene* ODSocketDemo::createScene() {
	auto scene = Scene::create();
	auto layer = ODSocketDemo::create();
	scene->addChild(layer);
	return scene;
}

bool ODSocketDemo::init() {
	if (!Layer::create()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//连接的按钮
	auto label1 = MenuItemFont::create("Connection", CC_CALLBACK_1(ODSocketDemo::connectServer, this));
	label1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height* 3 / 4 + origin.y));
	auto menu1 = Menu::create(label1, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1);
	//发送数据按钮
	auto label2 = MenuItemFont::create("Sending", CC_CALLBACK_1(ODSocketDemo::sendData, this));
	label2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));
	auto menu2 = Menu::create(label2, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2);
	//断开连接按钮
	auto shiftItem = MenuItemImage::create("CloseNormal.png", "CloseNormal.png", CC_CALLBACK_1(ODSocketDemo::menuShiftCallBack, this));
	shiftItem->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	auto menu3 = Menu::create(shiftItem, NULL);   //绑定menu和Item
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 1);

	return true;

}

void ODSocketDemo::connectServer(Ref* pSender) {
	//初始化socket，包括启动DLL库和配置版本
	socket.Init();
	//将（协议，socket形式）和socket绑定创建clientsocket
	socket.Create(AF_INET, SOCK_STREAM, 0);	
	//要连接的ip地址
	const char* ip = "127.0.0.1";
	//发送的端口号
	int port = 9090;
	//连接服务器
	bool result = socket.Connect(ip, port);
	
	//判断连接状况
	if (result) {
		log("Connecting succeeds");
		//连接完成后开启一个新线程来接受服务器传输的数据
		std::thread recvThread = std::thread(&ODSocketDemo::receiveData, this);
		//从主线程剥离
		recvThread.detach();

	}
	else {
		log("Connecting fails");
		return;
	}

}
//发送数据
void ODSocketDemo::sendData(Ref* pSender) {
	
	socket.Send("Hello",6);
}
//接受数据
void ODSocketDemo::receiveData() {
	char buf[512] = "";
	socket.Recv(buf, 512, 0);
	log("receive: %s", buf);

}
//关闭socket连接
void ODSocketDemo::menuShiftCallBack(Ref* pSender) {
	socket.Close();
}
