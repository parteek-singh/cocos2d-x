
#include "acts.h"

using namespace cocos2d;
using namespace cocos2d::extension;

IMPLEMENT_CLASS_INFO(PlayMusic)

PlayMusic::PlayMusic(void)
{
}

PlayMusic::~PlayMusic(void)
{
}

bool PlayMusic::init()
{
    return true;
}

void PlayMusic::done()
{
    CCLOG("PlayMusic::done");
}

void PlayMusic::serialize(const rapidjson::Value &val)
{
    CCLOG("PlayMusic::serialize");
}

void PlayMusic::removeAll()
{
}
