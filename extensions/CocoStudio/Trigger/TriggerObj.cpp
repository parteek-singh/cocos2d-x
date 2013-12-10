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

void TriggerCode::release()
{
}

bool TriggerCode::onCheck()
{
    bool bRet =false;
    for (std::vector<BaseTriggerCondition*>::iterator iter = _conVec.begin(); iter != _conVec.end(); ++iter)
    {
        bRet = bRet && (*iter)->check();
    }
	return bRet;
}

void TriggerCode::onDeal()
{
    for (std::vector<BaseTriggerAction*>::iterator iter = _actVec.begin(); iter != _actVec.end(); ++iter)
    {
        (*iter)->deal();
    }
}

TriggerCode* TriggerCode::create(void)
{
    TriggerCode * pRet = new TriggerCode();
    if (pRet != NULL)
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
	return pRet;
}


NS_CC_EXT_END