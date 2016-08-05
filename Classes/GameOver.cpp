//
//  GameOver.cpp
//  snakegame
//
//  Created by CTC on 15/7/9.
//
//
#include "GameOver.h"
#include "MainMenu.h"

Scene *GameOver::createScene(int score)
{
    Scene *scene = Scene::create();
    Layer *layer = GameOver::create(score);
    scene->addChild(layer);
    return scene;
}

GameOver *GameOver::create(int score)
{
    GameOver *pRet = new GameOver(score);
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

GameOver::GameOver(int score)
{
    m_iScore = score;
}

GameOver::~GameOver()
{
    
}

bool GameOver:: init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // 背景
    const Size &size=Director::getInstance()->getWinSize();
    Sprite *spriteBK=Sprite::create("menuback.png");
    spriteBK->setPosition(Point(size.width/2,size.height/2));
    spriteBK->setOpacity(175);
    this->addChild(spriteBK);
    
    // 游戏结束
    Label *label = Label::createWithSystemFont("GameOver", "Arial", 30);
    label->setPosition(Point(size.width / 2, size.height / 2));
    this->addChild(label);
    
    // 把int类型转换为string类型
    std::string strScore = StringUtils::format("得分：%d", m_iScore);
    Label *score = Label::createWithSystemFont(strScore, "Arial", 30);
    score->setPosition(Point(size.width / 2, size.height / 2 - 60));
    this->addChild(score);
    
    // 返回按钮
    MenuItemFont *menuItemBack = MenuItemFont::create("Back", CC_CALLBACK_1(GameOver::menuCallBack, this));
    Menu *menu = Menu::create(menuItemBack, NULL);
    menu->setPosition(Point::ZERO);
    menuItemBack->setPosition(Point(size.width - menuItemBack->getContentSize().width - 100, menuItemBack->getContentSize().height + 10));
    this->addChild(menu);
      
    return true;
}

void GameOver::menuCallBack(Ref *object)
{
    Scene *scene = MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}