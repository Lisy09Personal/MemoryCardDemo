//
//  CardFactory.cpp
//  MemoryCard
//
//  Created by JasonWu on 11/25/14.
//
//

#include "CardFactory.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Card.h"

USING_NS_CC;

ICard* CardFactory::createCard(int backId,int number)
{
    const int cardSize=256;
    
    //创建背景
    
    if (backId<0||backId>=8) {
        backId=0;
    }
    int x=(backId%2)*cardSize;
    int y=(backId/2)*cardSize;
    
    auto backImage=Sprite::create("card_back.png",Rect(x,y,cardSize,cardSize));
    
    //创建前景
    auto frontImage=Node::create();
    frontImage->setContentSize(Size(cardSize, cardSize));
    frontImage->addChild(Sprite::create("card_front.png"));
    
    auto numberText=ui::TextAtlas::create(StringUtils::format("%d",number), "card_number.png", 140, 140, "0");
    
    frontImage->addChild(numberText);
    
    //创建卡片数据
    CardData data={};
    data.number=number;
    
    //创建卡片
    auto card=Card::create();
    card->setBackImage(backImage);
    card->setFrontImage(frontImage);
    card->setCardData(data);
    
    
    
    return card;
}