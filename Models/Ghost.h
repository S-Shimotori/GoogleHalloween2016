#ifndef __GHOST_H__
#define __GHOST_H__

#include "cocos2d.h"

class Ghost: public cocos2d::Sprite {

public:
    virtual bool init();

    CREATE_FUNC(Ghost);

    double speed;

    std::vector<int> commands;

    void updateCommandSprites();

    void initCommandSprites();
};

#endif // __GHOST_H__
