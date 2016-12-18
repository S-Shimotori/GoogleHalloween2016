#include "Position.h"

USING_NS_CC;

Vec2 Position::create(Size size, float x, float y, float xRelative, float yRelative)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    return cocos2d::Vec2(
                         origin.x + visibleSize.width * x - size.width * xRelative,
                         origin.y + visibleSize.height * y - size.width * yRelative
    );
}
