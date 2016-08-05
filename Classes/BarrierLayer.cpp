//
//  BarrierLayer.cpp
//  snakegame
//
//  Created by CTC on 15/7/14.
//
//

#include <stdio.h>
#include "BarrierLayer.h"
BarrierLayer::BarrierLayer()
{
}
BarrierLayer::~BarrierLayer()
{
}
bool BarrierLayer::init()
{
    if(!Layer::init())
        return false;
    //添加一个半灰色的层
    LayerColor* backLayerColor = LayerColor::create(Color4B(25, 25, 25, 125));
    this->addChild(backLayerColor);
    //添加向下触摸屏蔽
    auto callback = [](Touch * ,Event *)
    {
        return true;
    };
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = callback;
    listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}