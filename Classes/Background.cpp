//
//  Background.cpp
//  MemoryCard
//
//  Created by JasonWu on 12/3/14.
//
//

#include "Background.h"

Background::Background()
{

}
Background::~Background()
{
    this->unscheduleUpdate();
}

bool Background::init()
{
    if (Node::init()==false) {
        return false;
    }
    
    _backgorund=Sprite::create("background.png");
    
    _backgorund->setAnchorPoint(Vec2(0,0));
    
    Texture2D::TexParams tp={GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
    _backgorund->getTexture()->setTexParameters(tp);
    
    auto viewSzie=Director::getInstance()->getVisibleSize();
    Rect rect(0,0,viewSzie.width,viewSzie.height);
    
    _backgorund->setTextureRect(rect);
    
    this->addChild(_backgorund);
    
    this->scheduleUpdate();
    
    
    return true;
}
void Background::update(float t)
{
    Node::update(t);
    
    auto rect=_backgorund->getTextureRect();
    rect.origin.x+=100.0f*t;
    rect.origin.y+=100.0f*t;
    _backgorund->setTextureRect(rect);
    
}