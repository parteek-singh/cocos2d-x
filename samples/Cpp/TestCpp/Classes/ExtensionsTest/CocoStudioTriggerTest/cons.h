#ifndef __CONS_H__
#define __CONS_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"


class InputConditon : public cocos2d::extension::BaseTriggerCondition
{
    DECLARE_CLASS_INFO
public:
     InputConditon(void);
     virtual ~InputConditon(void);

     virtual bool init();
     virtual bool check();
	 virtual void serialize(rapidjson::Value &val);
     virtual void removeAll();
};


#endif


