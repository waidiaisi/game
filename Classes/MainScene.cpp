#include "MainScene.h"
#include "HorseSoldier.h"
//#include "cocostudio\CocoStudio.h"

float MainScene::scale_cell = 0.02f;
Vec2 MainScene::view_size = Vec2(0.0, 0.0);

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
EventListenerTouchOneByOne *touch_listener;
HorseSoldier *soldier;

void MainScene::loadMap() {
	m_map = TMXTiledMap::create("map.tmx");
	addChild(m_map);
}
// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Layer::init() ) {
        return false;
    }
	//View大小
	auto glview = Director::getInstance()->getOpenGLView();
	auto size = glview->getVisibleSize();
	view_size.x = size.width;
	view_size.y = size.height;
	
	loadMap();

	//鼠标监听
	auto mouse_listener = EventListenerMouse::create();
	mouse_listener->onMouseScroll = CC_CALLBACK_1(MainScene::onMouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);
	//触摸监听
	touch_listener = EventListenerTouchOneByOne::create();
	touch_listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
	touch_listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
	touch_listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touch_listener, this);

	soldier = HorseSoldier::create();
	addSoldier(m_map, soldier);

    return true;
}

const Vec2& MainScene::getLeftDownPos() {
	return pos_down;
}

const Vec2& MainScene::getMapSize() {
	static Vec2 map_size;
	auto size = m_map->getContentSize();
	auto scale = m_map->getScale();map_size.x = size.width * scale;
	map_size.y = size.height * scale;
	return map_size;
}

const Vec2& MainScene::mouse2map(Vec2 &pos_mouse) {
	static Vec2 ret;
	Vec2 pos_map = m_map->getPosition();
	Vec2 delta = pos_mouse - pos_map;
	Size size_map = m_map->getContentSize(); //地图原大小
	Vec2 size = getMapSize(); //缩放后的地图大小
	Vec2 scale(delta.x / size.x, delta.y / size.y); //Delta 所占地图的比例
	ret.x = size_map.width * scale.x;
	ret.y = size_map.height * scale.y;
	return ret;
}

void MainScene::scaleMap(Vec2 focu, float n) {
	float old_scale = m_map->getScale();
	float new_scale = old_scale + scale_cell * n;
	if (new_scale > 1.2) return; //已经放大到原图比例
	if (new_scale <= 0.0) return; //已经缩小到最小
	auto size = getMapSize();
	Vec2 delta = size + m_map->getPosition() - view_size;//地图到View右上角的距离
	if (new_scale < old_scale) {
		if (size.x > view_size.x && size.y > view_size.y) {
			m_map->setScale(new_scale); //只有地图长宽都大于View时才缩小
			if (delta.x < 0.0 || delta.y < 0.0)
				begainMoveMap(Vec2(0, 0) - delta); //如果缩小到地图超出右上角则朝反方向移动地图
			return;
		}
	}
	else {
		m_map->setScale(new_scale);
	}
	//log("Current Scale: %1.2f, Map size: %.2f,%.2f , Mouse postion: %.2f,%.2f ", new_scale, m_map->getMapSize().width, m_map->getMapSize().height, e->getCursorX(), e->getCursorY());
}

void MainScene::prepMoveMap() {
	pos_down_map = m_map->getPosition();
}

void MainScene::begainMoveMap(Vec2 delta) {
	Vec2 pos = pos_down_map + delta;
	//超出左下角的处理
	pos.x = pos.x > 0.0 ? 0.0 : pos.x;
	pos.y = pos.y > 0.0 ? 0.0 : pos.y;
	//超出右上角的处理
	Vec2 ru_pos = pos + getMapSize(); 
	pos.x += ru_pos.x < view_size.x ? view_size.x - ru_pos.x : 0.0;
	pos.y += ru_pos.y < view_size.y ? view_size.y - ru_pos.y : 0.0;
	//
	m_map->setPosition(pos);
}

void MainScene::addSoldier(TMXTiledMap* map,Soldier *msoldier){ //将士兵添加到map中
	msoldier->setPosition(Vec2(view_size.x / 2, view_size.y / 2));
	map->addChild(msoldier);
}

void MainScene::onTouchMoved(Touch* touch, Event* event){
	Vec2 pos_cur = touch->getLocation();
	Vec2 delta = pos_cur - pos_down;
	if (mouse_down) //鼠标按下时，即拖动
		begainMoveMap(delta);
}

bool MainScene::onTouchBegan(Touch* touch, Event* event){
	{
		pos_down = touch->getLocation();
		mouse_down = true;
	}
	prepMoveMap();
	Node *cur_node = event->getCurrentTarget();
	//log("Current Node: %x", cur_node);
	//log("Layer:%.2f %.2f Map:%.2f %.2f, Mouse:%.2f %.2f", getPosition().x, getPosition().y, m_map->getPosition().x, m_map->getPosition().y, pos_down.x, pos_down.y);
	auto pos = convertToWorldSpace(soldier->getPosition());
	//log("Soldier :%.2f %.2f, Mouse:%.2f %.2f", pos.x, pos.y, pos_down.x, pos_down.y);
	log("Map size:%.2f %.2f View size:%.2f %.2f", getMapSize().x, getMapSize().y, view_size.x, view_size.y);
	return true;
}

void MainScene::onTouchEnded(Touch* touch, Event* event){
	mouse_down = false;
	//soldier->MoveTo(touch->getLocation());
	soldier->setPosition(mouse2map(touch->getLocation()));
}

void MainScene::onMouseScroll(Event* event){
	EventMouse *e = (EventMouse *)event;
	float fscrol = e->getScrollY();
	scaleMap(e->getLocation(), fscrol);
}
