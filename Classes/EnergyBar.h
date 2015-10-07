//
//  EnergyBar.h
//  MemoryCard
//
//  Created by JasonWu on 12/3/14.
//
//

#ifndef __MemoryCard__EnergyBar__
#define __MemoryCard__EnergyBar__

#include <stdio.h>

#include "cocos2d.h"

USING_NS_CC;

class EnergyBar:public Node
{
protected:
    ProgressTimer* _progress;
    Sprite* _background;
    
    float _percentage;
    
public:
    EnergyBar();
    virtual ~EnergyBar();
    
    CREATE_FUNC(EnergyBar);
    virtual bool init();
    
    void updateView(int value);
};


#endif /* defined(__MemoryCard__EnergyBar__) */
