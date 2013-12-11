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

#include "ObjectFactory.h"

NS_CC_EXT_BEGIN

TInfo::TInfo(void)
:_class("")
,_fun(NULL)
{
}

TInfo::TInfo(const std::string& type, Instance ins)
:_class(type)
,_fun(ins)
{
    cocos2d::extension::ObjectFactory::sharedFactory()->registerType(*this);
}

TInfo::TInfo(const TInfo &t)
{
    _class = t._class;
    _fun = t._fun;
}

TInfo::~TInfo(void)
{
   _class = "";
   _fun = NULL;
}

TInfo& TInfo::operator= (const TInfo &t)
{
    _class = t._class;
    _fun = t._fun;
    return *this;
}


ObjectFactory* ObjectFactory::_sharedFactory = NULL;

ObjectFactory::ObjectFactory(void)
{

}

ObjectFactory::~ObjectFactory(void)
{

}

ObjectFactory* ObjectFactory::sharedFactory()
{
    if ( NULL == _sharedFactory)
    {
        _sharedFactory = new ObjectFactory();
    }
    return _sharedFactory;
}

void ObjectFactory::purgeFactory()
{
    CC_SAFE_DELETE(_sharedFactory);
}

CCObject* ObjectFactory::createObject(const char *name)
{
    const TInfo t = _typeMap[name];
    CCObject *o = t._fun();
    return o;
}

void ObjectFactory::registerType(const TInfo &t)
{
    _typeMap.insert(FactoryMap::value_type(t._class, t));
}
NS_CC_EXT_END