//
//  Background.h
//  MemoryCard
//
//  Created by JasonWu on 12/3/14.
//
//

#ifndef __MemoryCard__Background__
#define __MemoryCard__Background__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Background:public Node
{
protected:
    Sprite* _backgorund;
    
public:
    Background();
    virtual ~Background();
    
    CREATE_FUNC(Background);
    virtual bool init();
    virtual void update(float t);
};

#endif /* defined(__MemoryCard__Background__) */
