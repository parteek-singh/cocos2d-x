#ifndef __TRIGGERTEST_H__
#define __TRIGGERTEST_H__

#include "cocos2d.h"
#include "cocos-ext.h"

void runTriggerTestLayer();

class TriggerTestLayer : public cocos2d::CCLayerColor
{
public:
	TriggerTestLayer();
	~TriggerTestLayer();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, 
    // instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(TriggerTestLayer);

    // init scene
    cocos2d::CCNode* createGameScene();
    
    //back to Extensions Main Layer
    void toExtensionsMainLayer(cocos2d::CCObject *sender);
};

#endif  // __HELLOWORLD_SCENE_H__
