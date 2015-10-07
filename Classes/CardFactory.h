//
//  CardFactory.h
//  MemoryCard
//
//  Created by JasonWu on 11/25/14.
//
//

#ifndef __MemoryCard__CardFactory__
#define __MemoryCard__CardFactory__

#include <stdio.h>

#include "ICard.h"

class CardFactory{
    
public:
    virtual ICard* createCard(int backId,int number);
};


#endif /* defined(__MemoryCard__CardFactory__) */
