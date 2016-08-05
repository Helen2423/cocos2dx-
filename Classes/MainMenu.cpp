//
//  MainMenu.cpp
//  snakegame
//
//  Created by CTC on 15/7/6.
//
//

#include "MainMenu.h"
#include "GameScene.h"
#include "HelpScene.h"

Scene *MainMenu::createScene()
{
    Scene *scene = Scene::create();
    Layer *layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    const Size &size = Director::getInstance()->getWinSize();
//    CCLOG("size.w = %f", size.width);
//    CCLOG("size.h=%f",size.height);
    Sprite *spriteBK = Sprite::create("menuback.png");
    spriteBK->setPosition(Point(size.width / 2, size.height / 2));
    this->addChild(spriteBK);
    
    MenuItemFont *menuItemStart = MenuItemFont::create("Start", CC_CALLBACK_1(MainMenu::menuCallBack, this));
    //setTag给层命名一个编号 可以随时找到该层
    menuItemStart->setTag(1);
    MenuItemFont *menuItemHelp = MenuItemFont::create("Help", CC_CALLBACK_1(MainMenu::menuCallBack, this));
    Menu *menu = Menu::create(menuItemStart, menuItemHelp, NULL);
    menuItemHelp->setTag(2);
    menu->setPosition(Point::ZERO);
    menuItemStart->setPosition(Point(size.width-menuItemStart->getContentSize().width - 100, menuItemStart->getContentSize().height + 10));
    
    menuItemHelp->setPosition(Point(size.width-menuItemHelp->getContentSize().width - 10, menuItemHelp->getContentSize().height + 10));
    this->addChild(menu);
    
    return true;
}

void MainMenu::menuCallBack(Ref *object)
{
    Node *target = (Node *)object;
    Scene *scene;
    switch (target->getTag()) {
        // start
        case 1:
            scene = GameScene::createScene();
            break;
            
        // help
        case 2:
            scene = HelpScene::createScene();
            break;
            
        default:
            break;
    }
  
    Director::getInstance()->replaceScene(scene);
}