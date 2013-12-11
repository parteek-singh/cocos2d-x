#ifndef __ACTIONS_H__
#define __ACTIONS_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"


class PlayMusic : public cocos2d::extension::BaseTriggerAction
{
    DECLARE_CLASS_INFO
public:
     PlayMusic(void);
     virtual ~PlayMusic(void);

     virtual bool init();
     virtual void done();
	 virtual void serialize(const rapidjson::Value &val);
     virtual void removeAll();
};

#endif


