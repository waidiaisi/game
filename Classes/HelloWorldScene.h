#ifndef __MainScene_SCENE_H__
#define __MainScene_SCENE_H__

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class Soldier;

class MainScene : public cocos2d::Layer
{
public:
    static Scene* createScene();
    virtual bool init();
	void addSoldier(TMXTiledMap* map, Soldier *soldier);
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(MainScene);

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onMouseScroll(cocos2d::Event* event);
private:
	TMXTiledMap *m_map;
	Node *m_cur_obj;
};

#endif // __MainScene_SCENE_H__
