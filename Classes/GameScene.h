//
//  GameScene.h
//  snakegame
//
//  Created by CTC on 15/7/6.
//
//

#ifndef GameScene_h
#define GameScene_h
#include "cocos2d.h"
#include "PauseLayer.h"
USING_NS_CC;

// 枚举类型封装精灵层，每个精灵都有一个移动方向
enum ENUM_DIR {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_STOP
};

//设置节点的类型
enum ENUM_TYPE {
    TYPE_HEAD,
    TYPE_BODY,
    TYPE_FOOD
};

//屏幕状态
//enum ENUM_STATUS {
//    PAUSE,
//    START
//};

class SnakeNode : public Sprite {
private:
    // 获取当前节点的行列坐标
    int m_iRow;
    int m_iCol;
    // 移动方向
    ENUM_DIR m_dir;
    // 节点类型 1蛇头 2身体 3食物
    ENUM_TYPE m_type;
    //int nodeType;
    // 通过获取屏幕高度来设置每个格子的长度
    float m_fWidth1;

public:
    // 传参数的宏修改 新建图层
    static SnakeNode *create(ENUM_TYPE type, float fWidth);
    //构造函数 初始化
    SnakeNode(ENUM_TYPE type, float fWidth);
    ~SnakeNode();
    //virtual bool init(ENUM_TYPE type);
    virtual bool init();
    // 获取坐标值 设置屏幕中的位置
    void setPositionRC(int row,int col);
    // 设置节点横坐标 调用类中私有成员变量 让私有成员在其他类中也能使用
    void setRow(int row);
    // 私有成员变量 获取节点横坐标
    int getRow();
    void setCol(int col);
    int getCol();
    // 设置节点方向 枚举类型设置
    void setDir(ENUM_DIR dir);
    // 获取节点方向
    ENUM_DIR getDir();
};

// PauseSceneDelegate 继承纯虚函数的子类 必须写函数体
class GameScene : public Layer, public PauseSceneDelegate {
    
private:
    // 存储屏幕的大小 成员变量m_ 类型sz 名称那个的大小scene
    //Size m_szScene;
    Size m_szScene;
    // 每个格子的边长
    float m_fWidth;
    // 每吃到一个食物得100分 统计分数
    int m_iScore;
    // 食物节点指针
    //SnakeNode *spFood; 成员变量m_ 类型sn 名称food
    SnakeNode *m_snFood;
    // 蛇头
    SnakeNode *m_snHead;
    // 存储最后一个节点
    SnakeNode *m_snTail;
    // 向量保存蛇的身体 不固定长度
    Vector<SnakeNode *> allBody;
    //ENUM_STATUS m_enumStatus;
    //MenuItemFont *m_menuItemPause;
    
    void menuBackCallBack(Ref *object);
    void menuPauseCallBack(Ref *object);
    virtual bool onTouchBegan(Touch *touch, Event *event);
    //纯虚函数 定义函数体 处理另一层中传过来的值
    virtual void pauseReturn();
    void gameLogic(float t);
    // 添加一个新的身体节点
    void newBody();
    // 移动所有的身体节点
    void moveBody();
    bool testGameIsOver();
    
    
public:
    GameScene();
    ~GameScene();
    static Scene *createScene();
    CREATE_FUNC(GameScene);
    virtual bool init();
};

#endif /* GameScene_h */
