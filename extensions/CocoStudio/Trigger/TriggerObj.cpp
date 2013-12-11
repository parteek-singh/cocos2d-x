/****************************************************************************
Copyright (c) 2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "TriggerObj.h"

NS_CC_EXT_BEGIN

BaseTriggerCondition::BaseTriggerCondition(void)
{
}

BaseTriggerCondition::~BaseTriggerCondition(void)
{
}

bool BaseTriggerCondition::init()
{
    return true;
}

bool BaseTriggerCondition::check()
{
    return true;
}

void BaseTriggerCondition::serialize(rapidjson::Value &val)
{
}

void BaseTriggerCondition::removeAll()
{
}

BaseTriggerAction::BaseTriggerAction(void)
{
}

BaseTriggerAction::~BaseTriggerAction(void)
{
}

bool BaseTriggerAction::init()
{
    return true;
}

void BaseTriggerAction::done()
{

}

void BaseTriggerAction::serialize(rapidjson::Value &val)
{
}

void BaseTriggerAction::removeAll()
{
}

TriggerObj::TriggerObj(void)
:_cons(NULL)
,_acts(NULL)
{
}

TriggerObj::~TriggerObj(void)
{
}

bool TriggerObj::init()
{
    bool bRet = false;
    do {
         _cons = CCArray::create();
         _acts = CCArray::create();
         CC_BREAK_IF(_cons == NULL || _acts == NULL);
         _cons->retain();
         _acts->retain();
         bRet = true;
    } while (0);
    return bRet;
}

TriggerObj* TriggerObj::create()
{
    TriggerObj * pRet = new TriggerObj();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool TriggerObj::check()
{
    bool bRet = true;
    if (_cons == NULL)
    {
        return bRet;
    }
    if (_cons->count() == 0)
    {
        return bRet;
    }
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_cons, pObj)
    {
        BaseTriggerCondition* con = (BaseTriggerCondition*)pObj;
        bRet = bRet && con->check();
    }

    return bRet;
}

void TriggerObj::done()
{
    if (_acts == NULL)
    {
        return;
    }
    if (_acts->count() == 0)
    {
        return;
    }
    
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(_acts, pObj)
    {
        BaseTriggerAction* con = (BaseTriggerAction*)pObj;
        con->done();
    }
}

void TriggerObj::removeAll()
{
    CCObject* pObj = NULL;
    if (_cons != NULL)
    {
        CCARRAY_FOREACH(_cons, pObj)
        {
            BaseTriggerCondition* con = (BaseTriggerCondition*)pObj;
            con->removeAll();
        }
        _cons->removeAllObjects();
    }
    if (_acts != NULL)
    {
        CCARRAY_FOREACH(_acts, pObj)
        {
            BaseTriggerAction* con = (BaseTriggerAction*)pObj;
            con->removeAll();
        }
        _cons->removeAllObjects();
    }
}

void TriggerObj::serialize(rapidjson::Value &val)
{
}

NS_CC_EXT_END