
#include "cocos-ext.h"
#include "../ExtensionsTest.h"
#include "TriggerTest.h"
#include "EventDef.h"

using namespace cocos2d;
using namespace cocos2d::extension;

TriggerTestLayer::~TriggerTestLayer()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
}

TriggerTestLayer::TriggerTestLayer()
{
}

CCScene* TriggerTestLayer::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		TriggerTestLayer *layer = TriggerTestLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TriggerTestLayer::init()
{
	bool bRet = false;
	do 
	{
        CC_BREAK_IF(! CCLayerColor::initWithColor( ccc4(0,0,0,255) ) );
        
        CCNode *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);

		bRet = true;
	} while (0);

	return bRet;
}

cocos2d::CCNode* TriggerTestLayer::createGameScene()
{
    CCMenuItemFont *itemBack = CCMenuItemFont::create("Back", this, menu_selector(TriggerTestLayer::toExtensionsMainLayer));
        itemBack->setColor(ccc3(255, 255, 255));
        itemBack->setPosition(ccp(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        CCMenu *menuBack = CCMenu::create(itemBack, NULL);
        menuBack->setPosition(CCPointZero);
		menuBack->setZOrder(4);
    
      TriggerMng::sharedTriggerMng()->parse("triggerTest.json");
    
    return menuBack;
}

void TriggerTestLayer::toExtensionsMainLayer(cocos2d::CCObject *sender)
{
	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}


void runTriggerTestLayer()
{
    CCScene *pScene = TriggerTestLayer::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
    sendEvent(TRIGGEREVENT_ENTERGAME);
    TriggerMng::sharedTriggerMng()->remove(TRIGGEREVENT_ENTERGAME);
}

