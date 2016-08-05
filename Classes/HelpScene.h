//
//  HelpScene.h
//  snakegame
//
//  Created by CTC on 15/7/6.
//
//

#ifndef HelpScene_h
#define HelpScene_h
#include "cocos2d.h"
USING_NS_CC;

class HelpScene:public Layer {
    
public:
    static Scene * createScene();
    CREATE_FUNC(HelpScene);
    virtual bool init();
    void menuCallBack (Ref *object);
    
};


#endif /* HelpScene_h */
