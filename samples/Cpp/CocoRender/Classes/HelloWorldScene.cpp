#include "HelloWorldScene.h"
#include "Render.h"
#include "FileInfo.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "../cocos2dx/platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(HelloWorld::menuCloseCallback));
    pCloseItem->setScale(2.0);
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width,
                                origin.y + pCloseItem->getContentSize().height));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 3);
    
    std::string path = std::string(FileInfo::sharedFileInfo()->getSavePath());
    if(path.empty())
    {
    	CCLabelTTF *pLabel = CCLabelTTF::create("File Error! File unzip error or null",
    	                                            "Arial",30);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pLabel->setPosition(ccp(size.width/2, size.height/2));

		addChild(pLabel);
    }
    else
    {
		//save file path
		std::vector<std::string> searchPaths = CCFileUtils::sharedFileUtils()->getSearchPaths();
		searchPaths.insert(searchPaths.begin(), path);
		CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

		Render* scene = new Render(FileInfo::sharedFileInfo()->getFilename());
		this->addChild(scene,2);
    }
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CloseScene(true);
}

void CloseScene(bool autonomous)
{
if(autonomous)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	#define  LOG_TAG    "JniHelper"
	#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
		JniMethodInfo minfo;
		jobject jobj;
		bool b = JniHelper::getStaticMethodInfo(minfo,
												"cn/cocostudio/render/CocoRender",
												"exitRenderScene",
												"()V");
		if (!b) {
			LOGD("JniHelper::getStaticMethodInfo error...");
		}else{
			jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		}
	#endif
}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
