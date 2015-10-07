//
//  Card.h
//  CardFlip
//
//  Created by JasonWu on 11/13/14.
//
//

#ifndef __CardFlip__Card__
#define __CardFlip__Card__

#include <stdio.h>
#include "cocos2d.h"

#include "ICard.h"

USING_NS_CC;


class Card:public ICard,public Node{
    Card();
    virtual ~Card();
    
protected:
    
    CardState _state;
    
    CardData _cardData;
    
    CC_PROPERTY(Node*, _backImage, BackImage);
    
    CC_PROPERTY(Node*, _frontImage, FrontImage);

    void flipFromTo(Node* a,Node* b,const std::function<void ()> &callback=nullptr);

    
public:
    CREATE_FUNC(Card);
    
    virtual void flipToBack(const std::function<void ()> &callback=nullptr);
    virtual void flipToFront(const std::function<void ()> &callback=nullptr);
    virtual CardState getCardState() const;
    virtual void setCardData(CardData data);
    virtual CardData* getCardData();
    
};


#endif /* defined(__CardFlip__Card__) */
