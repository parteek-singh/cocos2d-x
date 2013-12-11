
#include "cons.h"

using namespace cocos2d;
using namespace cocos2d::extension;


IMPLEMENT_CLASS_INFO(InputConditon)

InputConditon::InputConditon(void)
{
}

InputConditon::~InputConditon(void)
{
}

bool InputConditon::init()
{
    return true;
}

bool InputConditon::check()
{
    return true;
}

void InputConditon::serialize(rapidjson::Value &val)
{
}

void InputConditon::removeAll()
{
}
