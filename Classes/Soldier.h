#ifndef _Soldier_H_
#define _Soldier_H_
#include "string"
#include "cocos2d.h"
#include "GameManager.h"
USING_NS_CC;
using namespace std;
class Soldier :public CCNode
{
public:
	Soldier();
	~Soldier();
	virtual bool init();
	CREATE_FUNC(Soldier);//ͬcocos�ṩ�ĺ�������Soldier
	void StartMoveAction(Vec2 vec);//�����ƶ�
	void endMoveAction();//�Լ����ã������ж��ƶ��Ƿ���ֹ
	void bindSprite(Sprite *sprite);//��soldier��һ������
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void update(float dt);
	void attack(int id);
protected:
	bool isMoving = false;
	Sprite* m_sprite;
	string direction="up";//�����Ƿ���������8���ֱ�Ϊup,down,right,left,ur,rl,dr,dl
	string kind="qm2";//���࣬��������ͼƬ
	int id=0;//ID����������Ψһ�ı�ʶ
	int HP;//��ǰHP
	int HP_MAX;//HP���ֵ
	int ANT;//������ ��������������ҽ���д�ڷ����������ݿ���
	int DEF;//������
	int skill[5];//���ܣ����Ϊ�ĸ���0������ͨ����,-1������
	int sp;//���ܵ�
	int sp_MAX;//���ܵ����ֵ
	int owner;//����,0��������
	int soldierSpeed=5;//�ٶȣ��ٶ�ֵԽ���������ߵ�Խ������������ʱ�뵽���������
	int compareSpeed=0;//��speed�Ƚ���ͬ��ǰ����	
	int physical=10;//����ֵ
	int physical_Max=10;//����ֵ����
	int sunhao=10;//��ĵ�����
	int SunhaoStep=0;//
	CCAnimationCache *animCache;//����8������Ķ�������
	
	Map<string, SpriteFrame*>standMap;//����������վ����8������

	MoveTo *moveToAction;
	CCAnimation *animationUp;
	CCAnimation *animationDown;
	CCAnimation *animationRight;
	CCAnimation *animationLeft;
	CCAnimation *animationUR;
	CCAnimation *animationUL;
	CCAnimation *animationDR;
	CCAnimation *animationDL;
};
#endif