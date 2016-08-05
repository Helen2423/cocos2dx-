//
//  HelpScene.cpp
//  snakegame
//
//  Created by CTC on 15/7/6.
//
//

#include "HelpScene.h"
#include "MainMenu.h"

Scene *HelpScene::createScene()
{
    Scene *scene=Scene::create();
    Layer *layer=HelpScene::create();
    scene->addChild(layer);
    return scene;
}

bool HelpScene::init()
{
    if (!Layer::init()) {
        return false;}

    // 背景
    const Size &size = Director::getInstance()->getWinSize();
    Sprite *spriteBK = Sprite::create("menuback.png");
    spriteBK->setPosition(Point(size.width / 2, size.height / 2));
    spriteBK->setOpacity(175);
    this->addChild(spriteBK);

    // 帮助信息
    Label *labelScore=Label::createWithSystemFont("帮助信息", "宋体", 25);
    labelScore->setPosition(Point(size.width - 80, size.height - 50));
    this->addChild(labelScore);
    
    // 返回按钮
    MenuItemFont *menuItemBack = MenuItemFont::create("Back", CC_CALLBACK_1(HelpScene::menuCallBack, this));
    Menu *menu = Menu::create(menuItemBack, NULL);
    menu->setPosition(Point::ZERO);
    menuItemBack->setPosition(Point(size.width - menuItemBack->getContentSize().width - 100, menuItemBack->getContentSize().height + 10));
    this->addChild(menu);
    
    return true;
}

void HelpScene::menuCallBack (Ref *object)
{
    Scene *scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}