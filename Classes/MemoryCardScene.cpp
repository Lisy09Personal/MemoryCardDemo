//
//  MemoryCardScene.cpp
//  MemoryCard
//
//  Created by JasonWu on 12/2/14.
//
//

#include "MemoryCardScene.h"

#include "PauseBox.h"
#include "SceneMediator.h"
#include "UserData.h"

#include "SimpleAudioEngine.h"


MemoryCardScene::MemoryCardScene():
_scoreData({}),
_nowLevelLayer(nullptr)
{
    _scoreData.energy=1000;
}

MemoryCardScene::~MemoryCardScene()
{
    this->unscheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

Scene* MemoryCardScene::createScene(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
    auto scene = Scene::create();
    
    auto layer = MemoryCardScene::create(scoreStrategy);
    
    scene->addChild(layer);
    
    return scene;
}


MemoryCardScene* MemoryCardScene::create(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
    MemoryCardScene *scene=new MemoryCardScene();
    
    if (scene && scene->initWithScoreStrategy(scoreStrategy)) {
        scene->autorelease();
        return scene;
    }
    
    CC_SAFE_DELETE(scene);
    
    return nullptr;
}

bool MemoryCardScene::initWithScoreStrategy(std::shared_ptr<ScoreStrategyBase> scoreStrategy)
{
    if (Layer::init()==false)
        return false;
    
    
    _scoreStrategy=scoreStrategy;
    
    initLevelDataList();
    
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("pitpat.mp3");
    
    initUI();
    
    newGame();
    
    this->scheduleUpdate();
    
    return true;
}

void MemoryCardScene::initLevelDataList()
{
    auto str= FileUtils::getInstance()->getStringFromFile("leveldata.csv");
    
    std::vector<std::string> rowList;
    
    char *row = strtok((char*)str.c_str(),"\n");
    while(row)
    {
        rowList.push_back(row);
        row=strtok(nullptr,"\n");
    }
    
    for (auto row=rowList.begin(); row!=rowList.end(); ++row) {
        char* rows= strtok((char*)row->c_str(),",");
        char* columns= strtok(nullptr,",");
        char* loss= strtok(nullptr,",");

        if (rows==nullptr || columns==nullptr || loss==nullptr) {
            continue;
        }

        LevelData level;
        
        level.rows= atoi(rows);
        level.columns=atoi(columns);
        level.loss=atoi(loss);
        
        if (level.rows*level.columns<=0||(level.rows*level.columns)%2!=0||level.loss<0) {
            continue;
        }
        _levelDataList.push_back(level);
        
    }
    _allLevel=static_cast<int>(_levelDataList.size());
}

void MemoryCardScene::initUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _background=Background::create();
    this->addChild(_background);
    
    _energyBar=EnergyBar::create();
    _energyBar->setPosition(visibleSize.width/2,visibleSize.height-100.0f);
    this->addChild(_energyBar);
    
    _scoreText=ScoreText::create();
    _scoreText->setPosition(Vec2(visibleSize.width-20,visibleSize.height-33));
    _scoreText->setScale(0.75f);
    this->addChild(_scoreText);
    
    
    _pauseButton=ui::Button::create("pause.png");
    _pauseButton->setAnchorPoint(Vec2(0,1));
    _pauseButton->setPosition(Vec2(0,visibleSize.height));
    this->addChild(_pauseButton);
    
    _pauseButton->addClickEventListener([this](Ref* ref){
        this->unscheduleUpdate();
        auto pauseBox= PauseBox::create();
        pauseBox->registerCallback([this,pauseBox](){
            pauseBox->removeFromParent();
            this->scheduleUpdate();
        },[](){
            SceneMediator::getInstance()->gotoStartScene();
        });
        
        this->addChild(pauseBox);
    });
}


void MemoryCardScene::newGame()
{
    
    _nowLevel=-1;
    nextLevel();
    
}

void MemoryCardScene::nextLevel()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _nowLevel++;
    if (_nowLevel>=_allLevel) {
        _nowLevel=0;
    }
    
    _nowLevelData=_levelDataList[_nowLevel];
    
    auto level=MemoryCardLevel::create(_nowLevelData);
    auto levelSize= level->getContentSize();
    level->setAnchorPoint(Vec2(0.5,0.5));
    level->ignoreAnchorPointForPosition(false);
    level->setPosition(visibleSize.width/2, visibleSize.height/2);
    
    auto scale=visibleSize.width/(levelSize.width+100);
    level->setPositionY(level->getPositionY()-80*scale);
    level->setScale(2);
    level->setOpacity(0);
    this->addChild(level);
    
    level->runAction(Spawn::create(FadeIn::create(0.25),ScaleTo::create(0.25, scale), NULL));
    
    _nowLevelLayer=level;//赋值当前的关卡
    
    level->registerCallFunc([this](CardData* dataA,CardData* dataB){
        _scoreStrategy->execute(&_scoreData, dataA, dataB);
        
        CCLOG("score:%d energy:%d maxContinuous:%d",_scoreData.score,_scoreData.energy,_scoreData.maxContinuous);
        
        
    }, [this](){
        _nowLevelLayer->removeFromParent();//移除
        nextLevel();
    });
}

void MemoryCardScene::update(float t)
{
    Layer::update(t);
    
    _scoreData.energy-=this->_nowLevelData.loss*t;
    
    if (_scoreData.energy>1000) {
        _scoreData.energy=1000;
    }else if(_scoreData.energy<0){
        _scoreData.energy=0;
    }
    
    _energyBar->updateView(_scoreData.energy);
    _scoreText->updateView(_scoreData.score);
    
    if (_scoreData.energy<=0) {
        //游戏结束,记录分数
        
        UserDefault::getInstance()->setIntegerForKey(NEW_SCORE, _scoreData.score);
        
        //刷新排行榜
        std::vector<int> scoreList;
        scoreList.push_back(_scoreData.score);
        
        for (int i=0; i<5; i++) {
            int score =UserDefault::getInstance()->getIntegerForKey(StringUtils::format("%s%d",RANK_SCORE,i).c_str(), 0);
            scoreList.push_back(score);
        }
        
        //排序
        std::sort(scoreList.begin(), scoreList.end(), [](int &a,int &b){
            return a>b;
        });
        
        //写入
        int rank=0;
        for (auto i=scoreList.begin(); i!=scoreList.end(); i++) {
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("%s%d",RANK_SCORE,rank).c_str(), *i);
            rank++;
        }
        this->unscheduleUpdate();
        
        SceneMediator::getInstance()->gotoChartsScene();
    }
    
    if (_scoreData.energy<600) {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume((600.0f-_scoreData.energy)/600.0f);
        
    }else{
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
    }
    
}
