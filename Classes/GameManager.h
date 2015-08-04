#ifndef  _GAMEMANAGER_H_
#define  _GAMEMANAGER_H_
#include "cocos2d.h"
USING_NS_CC;
//������������ٿ�ȫ�ֵģ����������������Ϣ��
class GameManager :public Ref{
public :
	static GameManager* getInstance();
	CREATE_FUNC(GameManager);
	virtual bool init();
	//������Ϣ
	void addObsever(const std::string &sMsgName, std::function<void(Ref*)>func);
	//������Ϣ
	void postNotification(const std::string &sMsgName, Ref* data);
	static GameManager* m_GameManager;
	std::map<std::string, std::vector<std::function<void(Ref*)>>> m_funcMap;//ͨ��map��¼�˶�����Ϣ��ȫ������
	//������ר�����������ƶ���
	void addMoveObsever(const std::string sMsgName, std::function<void(Vec2)>func);
	void postMoveNotification(const std::string sMsgName, Vec2 data);
	std::map<std::string,std::function<void(Vec2)>> move_map;//һ��keyֻ��Ӧ��һ������������Ҫ�����vector�˷���
};
#endif
/*ͨ����άint����ģ���ͼ*/