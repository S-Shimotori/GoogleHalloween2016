#include "TopScene.h"
#include "SimpleAudioEngine.h"
#include "Position.h"
#include <string>
#include "ui/CocosGUI.h"
#include <cmath>
#include "Ghost.h"

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

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Top::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Top::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Top::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(Top::onTouchCancelled, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    initializeTouchPath();
    initialTouchPosition[0] = 0;
    initialTouchPosition[1] = 0;

    this->isSwiping = false;
    this->isCheckingPath = false;

    this->ghostLayer = Layer::create();
    this->addChild(ghostLayer, 1);

    this->witchSprite = Sprite::create("majo.png");
    witchSprite->setPosition(Position::create(witchSprite->getContentSize(), 0.5, 0.25, 0, 0));
    this->addChild(witchSprite, 1);

    deltaCount = 0;

    this->scheduleUpdate();

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

bool Top::onTouchBegan(Touch *touch, Event *event)
{
    initialTouchPosition[0] = touch->getLocation().x;
    initialTouchPosition[1] = touch->getLocation().y;
    currentTouchPosition[0] = touch->getLocation().x;
    currentTouchPosition[1] = touch->getLocation().y;
    this->isSwiping = true;

    return true;
}

void Top::onTouchMoved(Touch *touch, Event *event)
{
    double diffX = std::abs(touch->getLocation().x - initialTouchPosition[0]);
    double diffY = std::abs(touch->getLocation().y - initialTouchPosition[1]);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    double noCheckDistance = MIN(visibleSize.width, visibleSize.height) * 0.2;
    if (!isCheckingPath && sqrt(std::pow(diffX, 2) + std::pow(diffY, 2)) >= noCheckDistance) {
        isCheckingPath = true;
        touchPath = 0b00011;
    }

    if (isCheckingPath) {
        // vertical line
        double shakeX = diffY * tan(30 * M_PI / 180.0);
        if (!((touch->getLocation().y - initialTouchPosition[1]) * (currentTouchPosition[1] - initialTouchPosition[1]) >= 0
              && (initialTouchPosition[0] - shakeX) <= touch->getLocation().x
              && touch->getLocation().x <= (initialTouchPosition[0] + shakeX))) { // not swipe down
            touchPath &= 0b11110;
        }

        // horizontal line
        double shakeY = diffX * tan(30 * M_PI / 180.0);
        if (!((touch->getLocation().x - initialTouchPosition[0]) * (currentTouchPosition[0] - initialTouchPosition[0]) >= 0
              && (initialTouchPosition[1] - shakeY <= touch->getLocation().y)
              && touch->getLocation().y <= (initialTouchPosition[1] + shakeY))) { // not swipe right
            touchPath &= 0b11101;
        }
    }

    currentTouchPosition[0] = touch->getLocation().x;
    currentTouchPosition[1] = touch->getLocation().y;
}

void Top::onTouchEnded(Touch *touch, Event *event)
{
    isSwiping = false;
    isCheckingPath = false;
}

void Top::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

void Top::initializeTouchPath() {
    touchPath = 0b00000;
}

void Top::update(float delta) {
    deltaCount += 1;
    if (deltaCount % 20 == 0) {
        deltaCount = 0;
        if (rand() % 4 == 0) {
            auto ghost = Ghost::create();
            // how get size?
            int side = rand() % 2;
            ghost->setPosition(Position::create(
                ghost->getContentSize(),
                side, double(rand()) / double(RAND_MAX),
                (side == 0 ? 0.5 : -1), 0,
                false, true
            ));
            ghost->speed = double(rand()) / double(RAND_MAX) + 1;
            ghostLayer->addChild(ghost);
        }
    }
    for (auto _ghost: ghostLayer->getChildren()) {
        // downcast?
        auto ghost = dynamic_cast<Ghost*>(_ghost);
        if (!isSwiping && ghost->commands[0] == touchPath) {
            ghost->commands.erase(ghost->commands.begin());
            ghost->updateCommandSprites();
        }
        auto remove = RemoveSelf::create();
        if (ghost->commands.size() == 0) {
            ghost->runAction(remove->clone());
            incrementScore();
        }
        double distance = ghost->getPosition().getDistance(witchSprite->getPosition());
        ghost->setPosition(
                ghost->getPosition().x - ghost->speed * (ghost->getPositionX() - witchSprite->getPositionX()) / distance,
                ghost->getPosition().y - ghost->speed * (ghost->getPositionY() - witchSprite->getPositionY()) / distance
        );
        if (ghost->getBoundingBox().intersectsRect(Rect(witchSprite->getPosition(), witchSprite->getContentSize()))) {
            ghost->runAction(remove->clone());
        }
    }
    if (!isSwiping) {
        initializeTouchPath();
    }
}

void Top::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}
