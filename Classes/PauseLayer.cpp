//
//  PauseLayer.cpp
//  snakegame
//
//  Created by CTC on 15/7/14.
//
//

#include <stdio.h>
#include "PauseLayer.h"
#include "GameScene.h"
#include "MainMenu.h"

PauseLayer *PauseLayer::create(PauseSceneDelegate *pause)
{
    PauseLayer *pRet = new PauseLayer(pause);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

//传一个类的指针 给它赋值成员变量
PauseLayer::PauseLayer(PauseSceneDelegate *pause)
{
    m_pause=pause;
}

PauseLayer::~PauseLayer()
{
    
}

bool PauseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    const Size &size=Director::getInstance()->getWinSize();
    
    //灰色背景
    LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 125));
    this->addChild(backLayerColor);

    // 暂停
    MenuItemFont *menuItemPause = MenuItemFont::create("Continue", CC_CALLBACK_1(PauseLayer::menuContinueCallBack, this));
    menuItemPause->setPosition(Point(size.width / 2 - 100, size.height / 2));
   // 重新开始
    MenuItemFont *menuItemRestart = MenuItemFont::create("Restart", CC_CALLBACK_1(PauseLayer::menuRestartCallBack, this));
    menuItemRestart->setPosition(Point(size.width / 2 + 100, size.height / 2));
    Menu *menu=Menu::create(menuItemPause, menuItemRestart, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

//不声明 不定义 ontouchbegan的使用方法
//    auto callback = [](Touch * ,Event *)
//    {
//        return true;
//    };
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = callback;
//    listener->setSwallowTouches(true);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void PauseLayer::menuContinueCallBack(Ref *object)
{
//    若只是暂停层 不需要传值 可使用这种方法 把暂停设为Director::getInstance()->pause();配套使用
//    不需要建立纯虚函数
//    Director::getInstance()->resume();
    //this指向暂停层 将自己从parent中走
    //或者写在pauseReturn()中 在上一层gamescene层将此层移走
    this->removeFromParentAndCleanup(true);
    
    if (m_pause) {
        m_pause->pauseReturn();
    }
}

void PauseLayer::menuRestartCallBack(Ref *object)
{
    Scene *scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

bool PauseLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
    

