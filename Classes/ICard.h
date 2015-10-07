//
//  ICard.h
//  MemoryCard
//
//  Created by JasonWu on 11/24/14.
//
//

#ifndef MemoryCard_ICard_h
#define MemoryCard_ICard_h

#include "CardState.h"
#include "CardData.h"
#include <functional>

class ICard{
public:
    virtual void flipToBack(const std::function<void ()> &callback=nullptr)=0;
    virtual void flipToFront(const std::function<void ()> &callback=nullptr)=0;
    virtual CardState getCardState() const=0;
    virtual void setCardData(CardData data)=0;
    virtual CardData* getCardData()=0;
};

#endif
