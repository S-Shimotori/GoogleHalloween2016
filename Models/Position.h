#ifndef __POSITION_H__
#define __POSITION_H__

#include "cocos2d.h"

class Position
{
public:
    static cocos2d::Vec2 create(cocos2d::Size size, float x, float y, float xRelative, float yRelative);
};

#endif // __POSITION_H__
