//
//  GameScene.cpp
//  snakegame
//
//  Created by CTC on 15/7/6.
//
//

#include "GameScene.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "GameOver.h"
#include "PauseLayer.h"

USING_NS_CC;
//添加音效时需要引用
using namespace CocosDenshion;

SnakeNode *SnakeNode::create(ENUM_TYPE type, float fWidth)
{
    SnakeNode *pRet = new SnakeNode(type, fWidth);
    //if (pRet && pRet->init(type)) {
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

SnakeNode::SnakeNode(ENUM_TYPE type, float fWidth)
{
    m_type = type;
    m_fWidth1 = fWidth;
}

SnakeNode::~SnakeNode()
{
    
}

//bool SnakeNode::init(ENUM_TYPE type)
bool SnakeNode::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    // 根据类型不同初始化不同的纹理
    switch (m_type) {
        // 蛇头
        case TYPE_HEAD:
        {   auto sprite = Sprite::create("redstar.png");
            // 设置自身的锚点 再加载到上一层中去 不用设置所在位置
            sprite->setAnchorPoint(Point::ZERO);
            //sprite->setPosition(50,50);
            this->addChild(sprite);
        }
            // 初始方向为 自动向右移动
            m_dir = DIR_RIGHT;
            break;
        
        // 身体
        case TYPE_BODY:
        {   auto sprite = Sprite::create("orangestar.png");
            sprite->setAnchorPoint(Point::ZERO);
            //sprite->setPosition(50,50);
            this->addChild(sprite);
        }
            // 初始方向停止
            m_dir = DIR_STOP;
            break;
            
        // 食物
        case TYPE_FOOD:
        {   auto sprite = Sprite::create("purplestar.png");
            sprite->setAnchorPoint(Point::ZERO);
            //sprite->setPosition(50,50);
            this->addChild(sprite);
        }
            // 食物不动
            m_dir = DIR_STOP;
            break;
            
        default:
            break;
    }
    
    return true;
}

// 设置节点坐标 用坐标值计算出在屏幕中的位置
void SnakeNode::setPositionRC(int row, int col)
{
    this->m_iRow = row;
    this->m_iCol = col;
    setPosition(Point(50 + row * m_fWidth1, 50 + col * m_fWidth1));
}

// 设置节点横坐标定义
void SnakeNode::setRow(int row)
{
    m_iRow = row;
}

// 获取节点横坐标定义
int SnakeNode::getRow()
{
    return m_iRow;
}

void SnakeNode::setCol(int col)
{
    m_iCol = col;
}

int SnakeNode::getCol()
{
    return m_iCol;
}

// 设置节点方向
void SnakeNode::setDir(ENUM_DIR dir)
{
    m_dir = dir;
}

// 获取节点方向
ENUM_DIR SnakeNode::getDir()
{
    return m_dir;
}


Scene *GameScene::createScene(){
    Scene *scene = Scene::create();
    Layer *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
    
}

//构造函数 初始化
GameScene::GameScene()
{
    m_iScore=0;
    m_szScene = Director::getInstance()->getWinSize();
    m_fWidth = (m_szScene.height - 100) / 10;
    //m_enumStatus = START;
    m_snTail = SnakeNode::create(TYPE_BODY, m_fWidth);
}

GameScene:: ~GameScene()
{
    
}

bool GameScene::init()
{
    if (!Layer::init()) {
      return false;
    }
  
    // 添加地图10行10列 绘图节点
    DrawNode *draw = DrawNode::create();
    draw->setAnchorPoint(Point::ZERO);
    // 起始点的初始位置
    draw->setPosition(50, 50);
    
    for (int i = 0; i < 11; i++) {
        //画横线 位置从哪到哪 线粗细 红、绿、蓝、透明度 都是满的白色
        draw->drawSegment(Point(0, m_fWidth * i), Point(m_fWidth * 10, m_fWidth * i), 1, Color4F(1, 1, 1, 1));
        draw->drawSegment(Point(m_fWidth * i, 0), Point(m_fWidth * i, m_fWidth * 10), 1, Color4F(1, 1, 1, 1));
    }
    this->addChild(draw);
    
    
    // 蛇头
    m_snHead = SnakeNode::create(TYPE_HEAD, m_fWidth);
    m_snHead->setPosition(50, 50);
//    m_row 为公有时这样设置spHead->m_row = 0;
    m_snHead->setRow(0);
    m_snHead->setCol(0);
    this->addChild(m_snHead);
    
//    spTail->m_row = spHead->m_row;
    m_snTail->setRow(m_snHead->getRow());
    
    m_snTail->setCol(m_snHead->getCol());
    m_snTail->setDir(m_snHead->getDir());
//    spTail->m_dir = spHead->m_dir;
    m_snTail->setVisible(false);
    this->addChild(m_snTail);

    // 食物 随机出现
    m_snFood = SnakeNode::create(TYPE_FOOD, m_fWidth);
    // 取余数0-10的数
    int row = rand()%10;
    int col = rand()%10;
//    log的写法
//    CCLOG("row = %d", row);
//    CCLOG("col = %d", col);
//    CCLOG("spFood1 .x = %f", spFood->getPosition().x);
//    CCLOG("spFood1 .x = %f", spFood->getPosition().x);
    m_snFood->setPositionRC(row, col);
    this->addChild(m_snFood);
    
    // 添加背景
    auto spriteBK = Sprite::create("menuback.png");
    spriteBK->setPosition(Point(m_szScene.width / 2, m_szScene.height / 2));
    // 设置背景的透明度
    spriteBK->setOpacity(175);
    this->addChild(spriteBK);
    
    // 分数显示
//    m_score = 0;构造函数中已设
    Label *labelScore = Label::createWithSystemFont("分数:0", "宋体", 25);
    labelScore->setTag(110);
    labelScore->setPosition(Point(m_szScene.width - 80, m_szScene.height - 50));
    this->addChild(labelScore);

    // 返回按钮
    MenuItemFont *menuItemBack = MenuItemFont::create("Back", CC_CALLBACK_1(GameScene::menuBackCallBack, this));
    menuItemBack->setPosition(Point(m_szScene.width - menuItemBack->getContentSize().width - 10, menuItemBack->getContentSize().height + 10));
    MenuItemFont *menuItemPause = MenuItemFont::create("Pause", CC_CALLBACK_1(GameScene::menuPauseCallBack, this));
    menuItemPause->setPosition(Point(m_szScene.width - menuItemBack->getContentSize().width - 100, menuItemBack->getContentSize().height + 10));
    Menu *menu = Menu::create(menuItemBack,menuItemPause, NULL);
//    将m_menuitempause设为成员变量 实现点击menu更改内容的效果
//    m_menuItemPause = MenuItemFont::create("Pause", CC_CALLBACK_1(GameScene::menuPause, this));
//    m_menuItemPause->setPosition(Point(m_size.width - menuItemBack->getContentSize().width - 100, menuItemBack->getContentSize().height + 10));
//    Menu *menu = Menu::create(menuItemBack,m_menuItemPause, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    // 计划任务 自动运行 逻辑每隔0.5秒执行一次 每0.5秒蛇头向右移动 0.3秒移动0.2秒停顿
    this->schedule(schedule_selector(GameScene::gameLogic), 0.5);
    
    // 用户触摸的时间侦听
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->setSwallowTouches(true);
//在.h中不写声明 不写listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this)时 可以这样调用
//    &按引用传递 ＝按值传递
//    listener->onTouchBegan = [&](Touch *t, Event *e) {
//        // 改变蛇移动的方向
//        // 用户触摸位置
//        int col = (t->getLocation().y - 50) / m_fWidth;
//        int row = (t->getLocation().x - 50) / m_fWidth;
//        // 蛇位置
//        int spHeadCol = (spHead->getPositionY() - 50) / m_fWidth;
//        int spHeadRow = (spHead->getPositionX() - 50) / m_fWidth;
//        // 触摸的点在蛇那个方向 abs求绝对值 纵向移动大于横向移动
//        if (abs(spHeadCol-col) > abs(spHeadRow-row)) {
//            if (spHeadCol<col) {
//                //spHead->getDir();
//                spHead->setDir(DIR_UP);
//                //spHead->m_dir= ENUM_DIR::DIR_UP;
//            } else {
//                spHead->setDir(DIR_DOWN);
//                //spHead->m_dir=ENUM_DIR::DIR_DOWN;
//            }
//        } else {
//            if (spHeadRow<row) {
//                spHead->setDir(DIR_RIGHT);
//                //spHead->m_dir=ENUM_DIR::DIR_RIGHT;
//            } else {
//                spHead->setDir(DIR_LEFT);
//               // spHead->m_dir=ENUM_DIR::DIR_LEFT;
//            }
//        }
//        
//        return true;
//    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
    
void GameScene::menuBackCallBack(Ref *object)
{
    Scene *scene=MainMenu::createScene();
    Director::getInstance()->replaceScene(scene);
}

void GameScene::menuPauseCallBack(Ref *object)
{
//1.在当前层面中暂停 开始 设一个成员变量获取屏幕状态 实现pause变为start
//判断当前状态 m_enumstatus初始值设为start再更改他的值的内容
//    当前是开始状态
//    if (m_enumStatus==START) {
//        // 按钮设置成START
//        
//        m_menuItemPause->setString("Start");
//        m_enumStatus=PAUSE;
//
//    // 当前是暂停状态
//    } else {
//        // 按钮设置PAUSE
//        m_menuItemPause->setString("Pause");
//
//        // 定时器开始
//        this->resume();
//        m_enumStatus=START;
    
// }
    
//2.将this->pause();替换为Director::getInstance()->pause();
//实现暂停 不需要建立纯虚函数

//3.this->pause();层间传值暂停 设置纯虚函数实现
    // 定时器暂停
    this->pause();
    // 创建一个暂停层 this指向gamescene 暂停层传到一个指向gamescene的指针
    PauseLayer *layer=PauseLayer::create(this);
    // 设置它的tag为10 方便remove
    //layer->setTag(10);
    //将创建的暂停层加到gamescene层
    this->addChild(layer);
}

bool GameScene::onTouchBegan(Touch* t, Event* e)
{
    // 改变蛇移动的方向
    // 用户触摸位置
    int col = (t->getLocation().y - 50) / m_fWidth;
    int row = (t->getLocation().x - 50) / m_fWidth;
    // 蛇位置
    int spHeadCol = (m_snHead->getPositionY() - 50) / m_fWidth;
    int spHeadRow = (m_snHead->getPositionX() - 50) / m_fWidth;
    // 触摸的点在蛇那个方向 abs求绝对值 纵向移动大于横向移动
    if (abs(spHeadCol - col) > abs(spHeadRow - row)) {
        if (spHeadCol < col) {
            //spHead->getDir();
            m_snHead->setDir(DIR_UP);
            //spHead->m_dir= ENUM_DIR::DIR_UP;
        } else {
            m_snHead->setDir(DIR_DOWN);
            //spHead->m_dir=ENUM_DIR::DIR_DOWN;
        }
    } else {
        if (spHeadRow < row) {
            m_snHead->setDir(DIR_RIGHT);
            //spHead->m_dir=ENUM_DIR::DIR_RIGHT;
        } else {
            m_snHead->setDir(DIR_LEFT);
            // spHead->m_dir=ENUM_DIR::DIR_LEFT;
        }
    }
    
    return true;
}

// 处理暂停层传过来的值
void GameScene::pauseReturn()
{
//再创建层时 将暂停层settag＝10
//法1 this->getChildByTag(10)->removeFromParentAndCleanup(true);
//法2 this->removeChildByTag(10);
    // this指向gamescene层 可以控制自己重新开始 不用remove其他层
    this->resume();
}

void GameScene::gameLogic(float t)
{
//    CCLOG("spTail1->nodeType = %d", spTail->nodeType);
//    CCLOG("spTail1->m_dir = %d", spTail->m_dir);
//    CCLOG("spTail1->m_fWidth1 = %f", spTail->m_fWidth1);
//    spTail->m_dir=spHead->m_dir;
//    spTail->m_col=spHead->m_col;
    m_snTail->setDir(m_snHead->getDir());
    m_snTail->setCol(m_snHead->getCol());
    m_snTail->setRow(m_snHead->getRow());
   // spTail->m_row=spHead->m_row;
   // spTail->setPositionRC(spTail->m_row, spTail->m_col);
    //蛇头移动
    switch (m_snHead->getDir()) {
//    switch (spHead->m_dir) {
        case DIR_RIGHT:
            // 300毫秒 纵坐标不动 横坐标移动32像素
            m_snHead->runAction(MoveBy::create(0.3, Point(m_fWidth, 0)));
            // 蛇头位置加1
            m_snHead->setRow(m_snHead->getRow() + 1);
//          spHead->m_row++;
            break;
        case DIR_LEFT:
            m_snHead->runAction(MoveBy::create(0.3, Point(-m_fWidth, 0)));
            m_snHead->setRow(m_snHead->getRow() - 1);
            break;
         
        case DIR_UP:
            m_snHead->runAction(MoveBy::create(0.3, Point(0, m_fWidth)));
            m_snHead->setCol(m_snHead->getCol() + 1);
            break;
         
        case DIR_DOWN:
            m_snHead->runAction(MoveBy::create(0.3, Point(0, -m_fWidth)));
            m_snHead->setCol(m_snHead->getCol() - 1);
            break;
            
        default:
            break;
    }
    
    // 碰撞结束
    if (this->testGameIsOver()) {
        // 返回true 游戏结束
        Scene *scene=GameOver::createScene(m_iScore);
        Director::getInstance()->replaceScene(scene);
    }
    
    // 移动所有身体节点
    moveBody();
    
    // 碰撞检测 食物与头在同一个坐标下
    if (m_snHead->getRow() == m_snFood->getRow() && m_snHead->getCol() == m_snFood->getCol()) {
//    if (spHead->m_row==spFood->m_row && spHead->m_col==spFood->m_col) {
        // 音效播放
        SimpleAudioEngine::getInstance()->playEffect("eat.mp3");//播放一次 可多个音效同时 可与背景一起
        // 分数增加
        this->m_iScore += 100;
        // 强制转换
        Label *label = (Label *)this->getChildByTag(110);//分数修改到界面中去 分数：0 tag
        char strscore[20];
        // 得到分数label 110 所在地 再进行修改
        sprintf(strscore, "分数:%d", m_iScore);
        label->setString(strscore);
        
        // 添加节点
        newBody();
        
        //食物产生新的位置
        int row = rand()%10; //取余数0-10的数
        int col = rand()%10;
        for (int j = 0; j < (int)allBody.size(); j++) {
            if (col == allBody.at(j)->getCol() && row == allBody.at(j)->getRow()) {
                row = rand() % 10; //取余数0-10的数
                col = rand() % 10;
                j = -1;
            } else {
                m_snFood->setPositionRC(row, col);
            }
        }
    }
}

void GameScene::newBody()//添加一个新的身体节点
{
    SnakeNode *bodynode = SnakeNode::create(TYPE_BODY, m_fWidth);
    // 新节点的方向位置与前一刻蛇状态的尾节点一致
    bodynode->setCol(m_snTail->getCol());
    bodynode->setRow(m_snTail->getRow());
    bodynode->setDir(m_snTail->getDir());
    bodynode->setPositionRC(m_snTail->getRow(), m_snTail->getCol());
//if (allBody.size()>0) {
        //有身体节点 新节点与身体的最后一个方向一样
        //auto lastbody=allBody.at(allBody.size()-1);
//        bodynode->m_dir=spTail->m_dir;
        //memcpy((void*)bodynode, (void*)spTail, sizeof(SnakeNode));
    // 设置这个节点的方向和坐标
    // bodynode->m_col=spTail->m_col;
    // bodynode->m_row=spTail->m_row;
    // bodynode->m_dir=spTail->m_dir;
//      bodynode->setPositionRC(spTail->m_row, spTail->m_col);
//
//        switch (bodynode->m_dir) {
//            case ENUM_DIR::DIR_UP:
//                bodynode->setPositionRC(spTail->m_row, spTail->m_col-1);
//                break;
//            case ENUM_DIR::DIR_DOWN:
//                bodynode->setPositionRC(spTail->m_row, spTail->m_col+1);
//                break;
//            case ENUM_DIR::DIR_RIGHT:
//                bodynode->setPositionRC(spTail->m_row-1, spTail->m_col);
//                break;
//            case ENUM_DIR::DIR_LEFT:
//                bodynode->setPositionRC(spTail->m_row+1, spTail->m_col);
//                break;
//            default:
//                break;
//        }
//    }
//    else{
////        bodynode=spHead;
//        
//        bodynode->m_col=spHead->m_col;
//        bodynode->m_row=spHead->m_row;
//        bodynode->m_dir=spHead->m_dir;
       // memcpy((void*)bodynode, (void*)spHead, sizeof(SnakeNode));
//        //只有蛇头节点，新节点方向等于蛇头方向
//        bodynode->m_dir = spHead->m_dir;
//        switch (bodynode->m_dir) {
//            case ENUM_DIR::DIR_UP:
//                bodynode->setPositionRC(spHead->m_row, spHead->m_col-1);
//                break;
//            case ENUM_DIR::DIR_DOWN:
//                bodynode->setPositionRC(spHead->m_row, spHead->m_col+1);
//                break;
//            case ENUM_DIR::DIR_RIGHT:
//                bodynode->setPositionRC(spHead->m_row-1, spHead->m_col);
//                break;
//            case ENUM_DIR::DIR_LEFT:
//                bodynode->setPositionRC(spHead->m_row+1, spHead->m_col);
//                break;
//                
//            default:
//                break;
//        }

//    }
    
    //添加节点到当前图层
    this->addChild(bodynode);
    
    //添加节点到当前集合中 allBody
    allBody.pushBack(bodynode);
}

void GameScene::moveBody()//移动所有的身体节点
{
    if (allBody.size() == 0) {
        return;
    }
//    CCLOG("spTail->nodeType = %d", spTail->nodeType);
//    CCLOG("spTail->m_dir = %d", spTail->m_dir);
//    CCLOG("spTail->m_fWidth1 = %f", spTail->m_fWidth1);
// spTail->m_dir=allBody.at(allBody.size()-1)->m_dir;
// spTail->m_row=allBody.at(allBody.size()-1)->m_row;
// spTail->m_col=allBody.at(allBody.size()-1)->m_col;
    
    // 将身体节点的最后一个节点存储到sptail中包括方向和位置
    // 不能直接sptail＝allbody.at(..) 因为sptail为指针获取到的是地址 蛇移动地址一直在变
    m_snTail->setDir(allBody.at(allBody.size() - 1)->getDir());
    m_snTail->setRow(allBody.at(allBody.size() - 1)->getRow());
    m_snTail->setCol(allBody.at(allBody.size() - 1)->getCol());
    
    for (SnakeNode *bodynode:allBody) {
        switch (bodynode->getDir()) {
            case DIR_RIGHT:
            // 300毫秒 纵坐标不动 横坐标移动32像素
            bodynode->runAction(MoveBy::create(0.3, Point(m_fWidth, 0)));
            // 蛇头位置加1
            bodynode->setRow(bodynode->getRow() + 1);
            break;
                
        case DIR_LEFT:
            bodynode->runAction(MoveBy::create(0.3, Point(-m_fWidth, 0)));
            bodynode->setRow(bodynode->getRow() - 1);
            // bodynode->m_row--;
            break;
                
        case DIR_UP:
            bodynode->runAction(MoveBy::create(0.3, Point(0, m_fWidth)));
            bodynode->setCol(bodynode->getCol() + 1);
            // bodynode->m_col++;
            break;
                
        case DIR_DOWN:
            bodynode->runAction(MoveBy::create(0.3, Point(0, -m_fWidth)));
            bodynode->setCol(bodynode->getCol() - 1);
            break;
        default:
            break;
        }
    }

    // 移动完成之后改变每个body的方向
    for (int i = (int)(allBody.size() - 1); i > 0; i--) {
        // 每个节点的方向调整为它前一个节点的方向
        allBody.at(i)->setDir(allBody.at(i-1)->getDir());
    }
    // 最后调整第一个节点等于蛇头
    allBody.at(0)->setDir(m_snHead->getDir());
}


bool GameScene::testGameIsOver(){
     if (m_snHead->getCol() > 9 || m_snHead->getCol() < 0 || m_snHead->getRow() > 9 || m_snHead->getRow() < 0) {
         return true;
    } else {
        for (int i = 0; i < (int)(allBody.size()); i++) {
//            CCLOG("allBody.at(%d)->m_col = %d", i, allBody.at(i)->m_col);
//            CCLOG("spHead->m_col = %d", spHead->m_col);
//            CCLOG("allBody.at(%d)->m_row = %d", i, allBody.at(i)->m_row);
//            CCLOG("spHead->m_row = %d", spHead->m_row);
            if (m_snHead->getCol() == allBody.at(i)->getCol() && m_snHead->getRow() == allBody.at(i)->getRow()) {
            //if (allBody.at(i)->m_col==spHead->m_col && allBody.at(i)->m_row==spHead->m_row) {
                return true;
            }
        }
    }
}


