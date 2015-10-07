//
//  ScoreStrategy.cpp
//  MemoryCard
//
//  Created by JasonWu on 12/3/14.
//
//

#include "ScoreStrategy.h"

ScoreStrategy::ScoreStrategy():_continuous(0)
{
    
}

void ScoreStrategy::execute(ScoreData* score, CardData* cardA,CardData* cardB)
{
    if (cardA->number==cardB->number) {
        //配对成功，增长能量 累计连击数
        _continuous++;
        if (_continuous>score->maxContinuous) {
            //赋予最大连击数
            score->maxContinuous=_continuous;
        }
        score->energy+=100;
        
        //我们的分数成倍增加
        score->score+=100*_continuous;
    }else{
        //配对失败
        if(cardA->flipCount==0&&cardB->flipCount==0)
        {
            //第一次翻开不扣能量
            
        }else{
            //不是第一次翻开 扣能量
            score->energy-=100;
            //清除连击数
            _continuous=0;
        }
    }
    cardA->flipCount++;
    cardB->flipCount++;
}
