#include "pch.h"
#include "File.h"

Scene* File::createScene() {
	auto scene = Scene::create();
	auto layer = File::create();
	scene->addChild(layer);
	return scene;
}

bool File::init() {
	if (!Layer::create()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	MenuItemFont::setFontSize(40);
	//创建label1
	MenuItemFont* label1 = MenuItemFont::create("TestResourseDirInfo",CC_CALLBACK_1(File::OnClickMenu1, this));
	label1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height*9 / 12));
	Menu *menu1 = Menu::create(label1, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1);
	//创建label2
	auto label2 = MenuItemFont::create("Test WritablePath Info", CC_CALLBACK_1(File::OnClickMenu2, this));
	label2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height*7/ 12));
	Menu *menu2 = Menu::create(label2, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2);
	//创建label3
	auto label3 = MenuItemFont::create("Test Read File", CC_CALLBACK_1(File::OnClickMenu3, this));
	label3->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 5 / 12));
	Menu *menu3 = Menu::create(label3, NULL);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3);
	//创建label4
	auto label4 = MenuItemFont::create("Test Write File", CC_CALLBACK_1(File::OnClickMenu4, this));
	label4->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 3 / 12));
	Menu *menu4 = Menu::create(label4, NULL);
	menu4->setPosition(Vec2::ZERO);
	this->addChild(menu4);


	return true;
}
//读取资源目录
void File::OnClickMenu1(Ref* pSender) {
	auto sharedFileUtils = FileUtils::getInstance();
	std::string fileName = sharedFileUtils->fullPathForFilename("text.txt");
	log("fullPathForFileName = %s", fileName.c_str());   //log只能接受constchar*
}
//读取可写入的目录
void File::OnClickMenu2(Ref* pSender) {
	FileUtils *sharedFileUtils = FileUtils::getInstance();   //初始化时就判断调用哪个平台的子类
	sharedFileUtils->setWritablePath("E:\cocos2d-x\Project\HelloWorld\proj");
	std::string writablePath = sharedFileUtils->getWritablePath();
	log("Writable path is %s", writablePath.c_str());   //把STRING转换为constchar*

}

//读取资源文件
void File::OnClickMenu3(Ref* pSender) {
	auto sharedFileUtils = FileUtils::getInstance();
	std::string fullFileName = sharedFileUtils->fullPathForFilename("text.txt");
	Data data = sharedFileUtils->getDataFromFile(fullFileName);
	std::string content = std::string((const char*)data.getBytes(), 0, data.getSize());
	log("content:%s", content.c_str());
}
//写入文件
void File::OnClickMenu4(Ref* pSender) {
	auto sharedFileUtils = FileUtils::getInstance();
	sharedFileUtils->setWritablePath("E:\cocos2d-x\Project\HelloWorld\Resources");
	std::string writablePath = sharedFileUtils->getWritablePath();
	std::string fileName = writablePath + "text.txt";
	char szBuf[100] = "Testing write to file.";
	FILE *fp = fopen(fileName.c_str(), "wb");
	if (fp) {
		int ret = fprintf(fp, szBuf);
		fclose(fp);
		if (ret != 0) {
			log("write succeeds");
		}
	}
}
File::File()
{
}
