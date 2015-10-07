//
//  StartScene.h
//  MemoryCard
//
//  Created by JasonWu on 12/11/14.
//
//

#ifndef __MemoryCard__StartScene__
#define __MemoryCard__StartScene__

#include <stdio.h>

#include "cocos2d.h"
#include "Background.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class StartScene:public Layer
{
protected:
    Background* _background;
    
    Sprite* _logo;
    
    ui::Button* _startBtn;
    ui::Button* _chartBtn;
    ui::Button* _exitBtn;
    
public:
    StartScene();
    ~StartScene();
    
    CREATE_FUNC(StartScene);
    virtual bool init();
    
    static Scene* createScene();

};

#endif /* defined(__MemoryCard__StartScene__) */
