//
//  MainMenu.h
//  snakegame
//
//  Created by CTC on 15/7/6.
//
//

#ifndef MainMenu_h
#define MainMenu_h
#include "cocos2d.h"
USING_NS_CC;

class MainMenu:public Layer{
    
public:
    static Scene *createScene();
    CREATE_FUNC(MainMenu);
    virtual bool init();
    void menuCallBack(Ref *object);
};

#endif /* MainMenu_h */
