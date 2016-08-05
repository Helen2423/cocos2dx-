//
//  PauseLayer.h
//  snakegame
//
//  Created by CTC on 15/7/14.
//
//

#ifndef PauseLayer_h
#define PauseLayer_h

#include "cocos2d.h"
USING_NS_CC;

class PauseSceneDelegate;

// 写在一个.h中 PauseSceneDelegate已在前定义了 下一个类可以拿来用
class PauseLayer : public Layer {
    
private:
    virtual bool onTouchBegan(Touch *touch, Event *event);
    // 设置一个指向PauseSceneDelegate类的指针
    PauseSceneDelegate *m_pause;
    //PauseSceneDelegate *m_pDelegate;
    
public:
    // 与CREATE_FUNC(PauseLayer);同一功能 不同点：要传参数
    //static PauseLayer *create(PauseSceneDelegate *pDelegate);
    static PauseLayer *create(PauseSceneDelegate *pause);
    // 构造函数 传一个类的指针
    PauseLayer(PauseSceneDelegate *pause);
    ~PauseLayer();
    virtual bool init();
    void menuContinueCallBack (Ref *object);
    void menuRestartCallBack (Ref *object);
};

//代理函数 纯虚函数 实现层之间的值传递 子类 GameScene
class PauseSceneDelegate {
    
public:
    virtual void pauseReturn() = 0;
};

#endif /* PauseLayer_h */
