#ifndef _Soldier_H_
#define _Soldier_H_
#include "string"
#include "cocos2d.h"
#include "GameManager.h"
USING_NS_CC;
using namespace std;

class Soldier :public Node
{
	static char *angle_str[8];
	static float step_long;
	static int   Vec2Angle(Vec2 &vec);
	static int   Vec2Angle(float x, float y);
public:
	CREATE_FUNC(Soldier);
	virtual bool init();

	//virtual void MoveStep(int angle, int nStep = 1);
	virtual void MoveTo(Vec2 vec);
	//virtual void MoveTo(int nStep, int angle) = 0;
	void StartMoveAction(Vec2 vec);//�����ƶ�
	void endMoveAction();//�Լ����ã������ж��ƶ��Ƿ���ֹ
	void update(float dt);
	void attack(int id);
protected:
	Sprite* m_sprite;
	char *m_type = NULL;
	int m_id = 0;//ID����������Ψһ�ı�ʶ
	int m_hp;//��ǰHP
	int m_hp_max;//HP���ֵ
	int m_sp;//���ܵ�
	int m_sp_max;//���ܵ����ֵ
	float m_speed; //�����ƶ��ٶ�
	bool isMoving = false;
	int ANT;//������ ��������������ҽ���д�ڷ����������ݿ���
	int DEF;//������
	int skill[5];//���ܣ����Ϊ�ĸ���0������ͨ����,-1������
	int owner;//����,0��������
	int soldierSpeed=5;//�ٶȣ��ٶ�ֵԽ���������ߵ�Խ������������ʱ�뵽���������
	int compareSpeed=0;//��speed�Ƚ���ͬ��ǰ����	
	
	Animation *m_animation[8]; //8�����򶯻�
	SpriteFrame* m_stand_frame[8]; //8������վ��ͼƬ
};
#endif