#include "Soldier.h"
#include "Math.h"

char *Soldier::angle_str[8] = { "right", "ur", "up", "ul", "left", "dl", "down", "dr" };
float Soldier::step_long = 10.0;

int Soldier::Vec2Angle(float x, float y) {
	if (x == 0.0) {
		return y > 0.0 ? 2 : 6;
	}
	double rate_225 = tan(0.3927); //22.5
	double rate_675 = tan(1.178); //67.5
	double rate = abs(y) / abs(x);
	if (rate <= rate_225) {
		return x > 0.0 ? 0 : 4;
	}
	if (rate >= rate_675) {
		return y > 0.0 ? 2 : 6;
	}
	if (x > 0.0) {
		return y > 0.0 ? 1 : 7;
	}
	else {
		return y > 0.0 ? 3 : 5;
	}
}

int Soldier::Vec2Angle(Vec2 &vec) {
	return Vec2Angle(vec.x, vec.y);
}

bool Soldier::init(){
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	//��plist���ص������
	CCAssert(m_type, "Soldier type is null");
	frameCache->addSpriteFramesWithFile(
		StringUtils::format("./Soldier/%s.plist", m_type), 
		StringUtils::format("./Soldier/%s.png", m_type));
	//
	Vector<SpriteFrame*> frameVec[8];
	for (int i = 0; i < 8; i++){ //֡��
		for (int j = 0; j < 8; j++){ //�Ƕ�
			frameVec[j].pushBack(
				frameCache->getSpriteFrameByName(StringUtils::format("%s%d.png", angle_str[j], 8 - i)));
		}
	}
	//
	auto ani_cache = AnimationCache::sharedAnimationCache();
	for (int i = 0; i < 8; i++){
		//��վ���Ķ�����ӵ�m_stand_frame��
		m_stand_frame[i] = 
			frameCache->getSpriteFrameByName(StringUtils::format("%s9.png", angle_str[i]));
		//��������
		m_animation[i] = Animation::createWithSpriteFrames(frameVec[i]);
		m_animation[i]->setLoops(-1);
		m_animation[i]->setDelayPerUnit(0.2);
		//�������ӵ�����������
		ani_cache->addAnimation(m_animation[i], angle_str[i]);
	}
	//��ʼ������
	m_sprite = Sprite::create();
	//m_sprite->setSpriteFrame();
	m_sprite->initWithSpriteFrame(m_stand_frame[1]);
	addChild(m_sprite);
	return true;
}

void Soldier::MoveTo(Vec2 vec) {
	Vec2 v = getPosition();
	Vec2 delta = vec - v;
	log("Cur: %f %f Mouse: %f %f Delta : %f %f", v.x, v.y, vec.x, vec.y , delta.x, delta.y);
	int angle = Vec2Angle(delta);
	//���ö������ŵ��ٶ�
	//float d_time = physical / 10 * 0.2f;
	float d_time = 0.1f;
	m_animation[angle]->setDelayPerUnit(d_time);
	m_sprite->stopAllActions();
	m_sprite->runAction(Animate::create(m_animation[angle]));
	runAction(cocos2d::MoveBy::create(delta.getLength()/8, delta));
}

void Soldier::attack(int id){
}

void Soldier:: update(float dt){
}