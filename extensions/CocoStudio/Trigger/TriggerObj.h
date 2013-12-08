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

#ifndef __TRIGGEROBJ_H__
#define __TRIGGEROBJ_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"
#include "TriggerCondition.h"
#include <vector>

NS_CC_EXT_BEGIN

class TriggerCode : CCObject
{
	
public:
	std::vector<BaseTriggerElement*>    m_ConditionVec;
	std::vector<BaseTriggerElement*>    m_TriggerVec;
    std::vector<BaseTriggerElement*>    m_OccurrenceVec;


	bool    m_bChackConditionEnable;
	bool    m_bChackTriggerEnable;
    
public:
	TriggerCode()
        :m_bChackConditionEnable(false)
		,m_bChackTriggerEnable(false)
	{
		m_ConditionVec.clear();
		m_OccurrenceVec.clear();
	}

	virtual ~TriggerCode()
	{
		release();
	}
    
	bool onChackCondition();
	bool onChackTrigger();
	void onDoOccurrence();
	void release();
 
};

NS_CC_EXT_END

#endif


