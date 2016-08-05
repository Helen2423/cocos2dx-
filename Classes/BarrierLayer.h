//
//  BarrierLayer.h
//  snakegame
//
//  Created by CTC on 15/7/14.
//
//

#ifndef BarrierLayer_h
#define BarrierLayer_h
#include "cocos2d.h"
USING_NS_CC;
class BarrierLayer : public Layer
{
public:
    BarrierLayer();
    ~BarrierLayer();
    bool init();
    CREATE_FUNC(BarrierLayer);
};


#endif /* BarrierLayer_h */
