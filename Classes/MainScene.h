#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__

#include "cocos2d.h"
#include "HorseSoldier.h"
USING_NS_CC;

class MainScene : public Layer {
	static float scale_cell;
	static Vec2  view_size;
public:
    static Scene* createScene();
    CREATE_FUNC(MainScene);
	void addSoldier(TMXTiledMap* map, Soldier *soldier);
	void loadMap(); //���ص�ͼ
	void scaleMap(Vec2 focu, float n = 1);  //���ŵ�ͼ
	void prepMoveMap(); //׼���ƶ���ͼ
	void begainMoveMap(Vec2 delta); //��ʼ�ƶ���ͼ
	bool borderDetected();
	const Vec2& mouse2map(Vec2 &mouse); //���λ��TO��ͼλ��
	const Vec2& getMapSize();
	const Vec2& getLeftDownPos();

    virtual bool init();

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onMouseScroll(cocos2d::Event* event);
private:
	TMXTiledMap *m_map; //��ͼ
	Node *m_sel_obj; //��ǰѡ�еĶ���

	Vec2  pos_down; //��������ʱ��λ��
	Vec2  pos_down_map; //��������ʱ��ͼ��λ��
	bool  mouse_down = false;
};

#endif
