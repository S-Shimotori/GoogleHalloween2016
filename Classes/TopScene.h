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

    int touchPath;  // 0b<zigzag(2.down)><zigzag(1.up)><zigzag(0.down)><horizontal><vertical>

    cocos2d::Label* touchPathLabel;

    bool isCheckingPath;

    bool isSwiping;

    void initializeTouchPath();

    int initialTouchPosition[2];

    int currentTouchPosition[2];

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);

    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

    cocos2d::Layer* ghostLayer;

    int deltaCount;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(Top);

    void update(float delta);
};

#endif // __TOP_SCENE_H__
