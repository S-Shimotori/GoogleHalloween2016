#include "Ghost.h"

USING_NS_CC;

bool Ghost::init() {
    if (!Sprite::init()) {
        return false;
    }
    this->setTexture("obake.png");
    for (int i = 0; i < 4; i++) {
        if (i == 0 || rand() % 2 == 0) {
            this->commands.push_back(rand() % 2 == 0 ? 0b00001 : 0b00010);
        }
    }
    initCommandSprites();
    return true;
}

void Ghost::initCommandSprites() {
    double width = this->getContentSize().width / 4.0;
    for (int i = 0; i < this->commands.size(); i++) {
        auto commandLabel = Label::create();
        commandLabel->setTTFConfig(TTFConfig("fonts/Marker Felt.ttf", 24, GlyphCollection::DYNAMIC));
        if (this->commands[i] == 0b00001) {
            commandLabel->setString("V");
        } else {
            commandLabel->setString("H");
        }
        commandLabel->setPosition(Vec2(width * i, -1 * commandLabel->getContentSize().height / 2.0));
        this->addChild(commandLabel, 1);
    }
}

void Ghost::updateCommandSprites() {
    auto children = this->getChildren();
    int numberOfRemove = children.size() - commands.size();
    if (numberOfRemove > 0) {
        for (int i = 0; i < numberOfRemove; i++) {
            children.at(i)->setVisible(false);
        }
    }
}
