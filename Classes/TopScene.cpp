#include "TopScene.h"
#include "SimpleAudioEngine.h"
#include "Position.h"

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

    auto label = Label::createWithTTF("Top", "fonts/arial.ttf", 24);
    label->setPosition(Position::create(label->getContentSize(), 0.5, 1, 0, 0.5));

    this->addChild(label, 1);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Position::create(sprite->getContentSize(), 0.5, 0.5, 0, 0));

    this->addChild(sprite, 0);

    return true;
}


void Top::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}
