//
//  GameOver.h
//  snakegame
//
//  Created by CTC on 15/7/9.
//
//

#ifndef GameOver_h
#define GameOver_h

#include "cocos2d.h"
USING_NS_CC;

class GameOver:public Layer{
    
private:
    int m_iScore;
    
public:
    static Scene * createScene(int score);
    static GameOver *create(int score);
    GameOver(int score);
    ~GameOver();
    virtual bool init();
    void menuCallBack (Ref *object);
    
};

#endif /* GameOver_h */
