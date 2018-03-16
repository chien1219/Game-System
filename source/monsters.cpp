#include "monsters.h"
#include "BasicTools.h"

MONSTER::MONSTER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
}

/*
Update the view direction of the monster.
*/
void MONSTER::updateViewDirection()
{
    if (mTarget == 0) return;
	Vector3 pos = mTarget->getPosition();
	Vector3 target_pos = mSceneNode->getPosition();
	target_pos.x = pos.x;
	target_pos.z = pos.z;

	mSceneNode->lookAt(target_pos, Node::TS_WORLD);
	mSceneNode->yaw(Radian(3.14159));
}

/*
Update the position and view direction of the monster.
*/
void MONSTER::update(const Ogre::FrameEvent& evt)
{
    //compute the position of the monster
	moveTowardMainChar();
	moveAwayMainChar();
	moveUpDown();

    updateViewDirection();
}

void MONSTER::setState(bool random)
{
	this->State = random;
}

void MONSTER::moveTowardMainChar(){

	if (mTarget == 0) return;
	Vector3 target_pos = mTarget->getPosition();
	Vector3 pos = mSceneNode->getPosition();
	target_pos.y = 0;
	pos.y = 0;

	if ((target_pos - pos).length() > 90){
		Vector3 curPos = mSceneNode->getPosition();
		Vector3 offset = (target_pos - pos).normalisedCopy()*0.3;
		mSceneNode->setPosition(curPos + offset);
	}
}

void MONSTER::moveAwayMainChar(){

	if (mTarget == 0) return;
	Vector3 target_pos = mTarget->getPosition();
	Vector3 pos = mSceneNode->getPosition();
	target_pos.y = 0;
	pos.y = 0;

	float length =(target_pos - pos).length();
	if (length < 200 ){
		Vector3 curPos = mSceneNode->getPosition();
		Vector3 offset = (pos - target_pos).normalisedCopy()*0.5;
		mSceneNode->setPosition(curPos + offset);
	}
}

void MONSTER::moveUpDown()
{
	Vector3 pos = mSceneNode->getPosition();
	Vector3 newPos;

	
	//Move Up
	if(State){
		Vector3 velocity = Vector3(0, 20, 0);
		newPos = pos + velocity*0.01;
		if(pos.y > 140){
			State = false;
		}
	}
	//Move Down
	else if(!State){
		Vector3 velocity = Vector3(0, -20, 0);
		newPos = pos + velocity*0.01;
		if(pos.y < 110){
			State = true;
		}
	}
	mSceneNode->setPosition(newPos);
}
