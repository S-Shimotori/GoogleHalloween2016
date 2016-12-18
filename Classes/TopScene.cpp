#include "TopScene.h"
#include "SimpleAudioEngine.h"
#include "Position.h"
#include <string>
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Top::createScene()
{
    auto scene = Scene::create();
    auto layer = Top::create();
    scene->addChild(layer);
    return scene;
}

bool Top::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Top::menuCloseCallback, this));
    closeItem->setPosition(Position::create(closeItem->getContentSize(), 1, 0, 0.5, -0.5));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    this->scoreLabel = Label::create();
    this->scoreLabel->setTTFConfig(TTFConfig("fonts/Marker Felt.ttf", 24, GlyphCollection::DYNAMIC));
    setScoreLabel(0);
    scoreLabel->setPosition(Position::create(scoreLabel->getContentSize(), 0.5, 1, 0, 0.5));
    this->addChild(scoreLabel, 1);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Position::create(sprite->getContentSize(), 0.5, 0.5, 0, 0));

    this->addChild(sprite, 0);

    return true;
}

void Top::setScoreLabel(int newScore)
{
    this->score = newScore;
    if (this->scoreLabel != NULL) {
        // TODO: Refactoring
        if (newScore <= 0) {
            this->scoreLabel->setString("0000");
        } else if (newScore < 10) {
            this->scoreLabel->setString("000" + std::to_string(newScore));
        } else if (newScore < 100) {
            this->scoreLabel->setString("00" + std::to_string(newScore));
        } else if (newScore < 1000) {
            this->scoreLabel->setString("0" + std::to_string(newScore));
        } else if (newScore >= 9999) {
            this->scoreLabel->setString("9999");
        } else {
            this->scoreLabel->setString(std::to_string(newScore));
        }
    }
}

void Top::incrementScore() {
    this->score += 1;
    this->setScoreLabel(this->score);
}

void Top::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}
