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

#include "TriggerMng.h"
#include "TriggerObj.h"
#include "TriggerBase.h"

NS_CC_EXT_BEGIN

TriggerMng* TriggerMng::_sharedTriggerMng = NULL;

TriggerMng::TriggerMng(void)
: _eventTriggers(NULL)
{
    
}

TriggerMng::~TriggerMng(void)
{
    CC_SAFE_RELEASE(_eventTriggers);
}

const char* TriggerMng::triggerMngVersion()
{
    return "1.0.0.0";
}

TriggerMng* TriggerMng::sharedTriggerMng()
{
    if (NULL == _sharedTriggerMng)
    {
        _sharedTriggerMng = new TriggerMng();
    }
    return _sharedTriggerMng;
}

void TriggerMng::purgeTriggerMng()
{
    CC_SAFE_DELETE(_sharedTriggerMng);
}

void TriggerMng::parse(const char* pszFileName)
{
    CCLOG("%s", triggerMngVersion());
    rapidjson::Document jsonDict;
    do {
          CC_BREAK_IF(!readJson(pszFileName, jsonDict));
          CCLOG("11111111111111111111");
        
    } while (0);
}

TriggerObj* TriggerMng::get(unsigned int event) const
{
    TriggerObj* pRet = NULL;
    CCAssert(event >= 0, "Argument must be larger than 0");
    do {
        CC_BREAK_IF(NULL == _eventTriggers);
        pRet = dynamic_cast<TriggerObj*>(_eventTriggers->objectForKey(event));
        
    } while (0);
    return pRet;
}

bool TriggerMng::add(unsigned int event, TriggerObj *obj)
{
    bool bRet = false;
    CCAssert(obj != NULL, "Argument must be non-nil");
    do
    {
        if (_eventTriggers == NULL)
        {
            alloc();
        }
        TriggerObj *pObj = dynamic_cast<TriggerObj*>(_eventTriggers->objectForKey(event));
        CCAssert(pObj == NULL, "event already used. It can't be used again");
        CC_BREAK_IF(pObj);
        _eventTriggers->setObject(pObj, event);
        bRet = true;
    } while(0);
    return bRet;
}

void TriggerMng::removeAll(void)
{
    if(_eventTriggers != NULL)
    {
        CCDictElement *pElement, *tmp;
        HASH_ITER(hh, _eventTriggers->m_pElements, pElement, tmp)
        {
            HASH_DEL(_eventTriggers->m_pElements, pElement);
            ((TriggerObj*)pElement->getObject())->removeAll();
            CC_SAFE_DELETE(pElement);
        }
    }
}

bool TriggerMng::remove(unsigned int event)
{
    bool bRet = false;
    CCAssert(event > 0, "event must be larger than 0");
    do 
    {        
        CC_BREAK_IF(!_eventTriggers);
        CCObject* pRetObject = NULL;
        pRetObject = _eventTriggers->objectForKey(event);
        CC_BREAK_IF(!pRetObject);
        TriggerObj *obj = dynamic_cast<TriggerObj*>(pRetObject);
        CC_BREAK_IF(!obj);
        obj->removeAll();
        _eventTriggers->removeObjectForKey(event);
        CC_SAFE_DELETE(obj);
        bRet = true;
    } while(0);
    return bRet;
}


bool TriggerMng::isEmpty(void) const
{
    return (bool)(!(_eventTriggers && _eventTriggers->count()));
}

void TriggerMng::alloc(void)
{
    _eventTriggers = CCDictionary::create();
    _eventTriggers->retain();
}

bool TriggerMng::readJson(const char *pszFileName, rapidjson::Document &doc)
{
    bool bRet = false;
    unsigned long size = 0;
    unsigned char *pBytes = NULL;
    do {
          CC_BREAK_IF(pszFileName == NULL);
          std::string jsonpath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pszFileName);
          pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData(jsonpath.c_str(), "r", &size);
          CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
          CCData *data = new CCData(pBytes, size);
          std::string load_str = std::string((const char *)data->getBytes(), data->getSize() );
          CC_SAFE_DELETE(data);
          doc.Parse<0>(load_str.c_str());
          CC_BREAK_IF(doc.HasParseError());
          bRet = true;
        } while (0);
    return bRet;
}


NS_CC_EXT_END