#include "Position.h"

USING_NS_CC;

Vec2 Position::create(Size size, float x, float y, float xRelative, float yRelative, bool visibleX, bool visibleY)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto positionX = origin.x + visibleSize.width * x - size.width * xRelative;
    auto positionY = origin.y + visibleSize.height * y - size.width * yRelative;

    if (visibleX) {
        if (positionX - size.width / 2 <= origin.x) {
            positionX = origin.x + size.width / 2;
        } else if (origin.x + visibleSize.width <= positionX + size.width / 2) {
            positionX = origin.x + visibleSize.width - size.width / 2;
        }
    }
    if (visibleY) {
        if (positionY - size.height / 2 <= origin.y) {
            positionY = origin.y + size.height / 2;
        } else if (origin.y + visibleSize.height <= positionY + size.height / 2) {
            positionY = origin.y + visibleSize.height - size.height / 2;
        }
    }
    return cocos2d::Vec2(positionX, positionY);
}
