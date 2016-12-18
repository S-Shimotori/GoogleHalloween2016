#ifndef __TOP_SCENE_H__
#define __TOP_SCENE_H__

#include "cocos2d.h"

class Top : public cocos2d::Layer
{
private:
    int score;

    cocos2d::Label* scoreLabel;

    void setScoreLabel(int newScore);

    void incrementScore();

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Top);
};

#endif // __TOP_SCENE_H__
