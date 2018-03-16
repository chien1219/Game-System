#include "main_char.h"
#include "BasicTools.h"
#include <OgreInstancedGeometry.h>

MAIN_CHAR::MAIN_CHAR(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
	mCamera = 0;
	mVelocity = Vector3(1, 0, 0);
mSpeedFactor = 1;
mActionMode = ACTION_NONE;
mEyePosition = Vector3(0,90, 0);

mFireActionMode = FIRE_ACTION_NONE;

mWeaponMgr = new WEAPON_MANAGER(mSceneMgr);
mTarget = 0; //null
mCurBulletsNum = 0;
}

WEAPON_MANAGER *MAIN_CHAR::getWeaponManager( )
{
	return mWeaponMgr;
}

void MAIN_CHAR::setMaxBulletsNum(int a_Num)
{
	mCurBulletsNum = a_Num;
	mWeaponMgr->setMaxBulletsNum(mCurBulletsNum);
}

void MAIN_CHAR::attachCamera(Camera *a_Camera)
{
	mCamera = a_Camera;
	mCamera->setPosition( mSceneNode->getPosition() + mEyePosition);
	FrameEvent evt;
	evt.timeSinceLastFrame = 0;
	walkForward(evt);
}

void MAIN_CHAR::updateViewDirection()
{
	Ogre::Camera* a_Camera;
		a_Camera = mCamera;
		a_Camera->setPosition(mCamera->getPosition());
		a_Camera->setDirection( mCamera->getRealDirection());
		attachCamera(a_Camera);

}

void MAIN_CHAR::walkForward(const Ogre::FrameEvent& evt)
{
	//exit(1);
	Vector3 actualDirection = mQuaternion*mInitDirection;
	Quaternion q = mCamera->getOrientation();
	Quaternion q0 = Quaternion(Radian(0), Vector3(1, 0, 0));
	q = q*q0;
	actualDirection = mCamera->getRealDirection();
	
	//BEGIN: BUG FIXED VERSION
	Vector3 p = mSceneNode->getPosition();
	actualDirection.y = 0.0;
	
	mSceneNode->lookAt(p+ actualDirection*10, Node::TS_WORLD);
	mSceneNode->yaw(Radian(3.14159*0.5));
	//END: BUG FIXED VERSION

	/*
	//BUG
	mSceneNode->setOrientation(q);
	mSceneNode->yaw(Radian(3.14159*0.5));
	*/

	actualDirection = mCamera->getRealDirection();
	Vector3 d;
	mSpeedFactor = 100;
	d = actualDirection*mSpeedFactor*evt.timeSinceLastFrame;

	logMessage("Direction\n");
	logMessage(actualDirection);

	logMessage(d);
	mSceneNode->translate(d);

	Vector3 pos = mSceneNode->getPosition();
	bool flg = projectScenePointOntoTerrain_PosDirection(pos);
	if (flg == false) {
		projectScenePointOntoTerrain_NegDirection(pos);
	}
	mSceneNode->setPosition(pos);

		Vector3 e = actualDirection*20;
	mCamera->setPosition(pos+mEyePosition+e);

}

void MAIN_CHAR::walkBackward(const Ogre::FrameEvent& evt)
{
	Vector3 actualDirection = mQuaternion*mInitDirection;
	Quaternion q = mCamera->getOrientation();
	Quaternion q0 = Quaternion(Radian(0), Vector3(1, 0, 0));
	q = q*q0;
	actualDirection = mCamera->getRealDirection();

	//BEGIN: BUG FIXED VERSION
	Vector3 p = mSceneNode->getPosition();
	actualDirection.y = 0.0;
	
	mSceneNode->lookAt(p+ actualDirection*10, Node::TS_WORLD);
	mSceneNode->yaw(Radian(3.14159*0.5));
	//END: BUG FIXED VERSION

	actualDirection = mCamera->getRealDirection();
	actualDirection = Vector3(-1*actualDirection.x, actualDirection.y, -1*actualDirection.z);
	Vector3 d;
	mSpeedFactor = 100;
	d = actualDirection*mSpeedFactor*evt.timeSinceLastFrame;

	logMessage("Direction\n");
	logMessage(actualDirection);

	logMessage(d);
	mSceneNode->translate(d);

	Vector3 pos = mSceneNode->getPosition();
	bool flg = projectScenePointOntoTerrain_PosDirection(pos);
	if (flg == false) {
		projectScenePointOntoTerrain_NegDirection(pos);
	}
	mSceneNode->setPosition(pos);

		Vector3 e = actualDirection*-20;
	mCamera->setPosition(pos+mEyePosition+e);
}


void MAIN_CHAR::setWalkForward()
{
	mActionMode |= ACTION_WALK_FORWARD;
}
	void MAIN_CHAR::setWalkBackward()
	{
	mActionMode |= ACTION_WALK_BACKWARD;

	}

	void MAIN_CHAR::unsetWalkForward()
{
	mActionMode ^= ACTION_WALK_FORWARD;
}
	void MAIN_CHAR::unsetWalkBackward()
	{
	mActionMode ^= ACTION_WALK_BACKWARD;

	}

	Vector3 MAIN_CHAR::getWeaponPosition() const
	{
		Vector3 p = mSceneNode->getPosition();
		p += mEyePosition;
		Vector3 d = mCamera->getRealDirection();
		p += d*20;
		return p;
	}

	void MAIN_CHAR::update(const Ogre::FrameEvent& evt)
	{
		if (mActionMode & ACTION_WALK_FORWARD) {
			walkForward(evt);
		}
		if (mActionMode & ACTION_WALK_BACKWARD) {
			walkBackward(evt);
		}
		
		//updateViewDirection();
		
		fireWeapon();
		updateWeapon(evt);
		Real sf = 3.0;
		//if (mAnimationState == 0) {
		if ( (mActionMode & ACTION_WALK_FORWARD)|| (mActionMode & ACTION_WALK_BACKWARD)) 
		{
				mAnimationState = mEntity->getAnimationState("Walk");
				mAnimationState->setLoop(true);
				mAnimationState->setEnabled(true);
				if (mActionMode & ACTION_WALK_FORWARD) {
					mAnimationState->addTime(evt.timeSinceLastFrame*sf);
				}
				else {
					mAnimationState->addTime(-evt.timeSinceLastFrame*sf);
				}
		} 
		else 
		{
			mAnimationState = mEntity->getAnimationState("Idle");
			mAnimationState->setLoop(true);
			mAnimationState->setEnabled(true);
			mAnimationState->addTime(evt.timeSinceLastFrame*sf);
		}
	}

	void MAIN_CHAR::fireWeapon()
	{
		Vector3 pos;
		Vector3 direction;
		if (mFireActionMode&FIRE_ACTION_NORMAL)
		{
			pos = getWeaponPosition();
			direction = mCamera->getRealDirection();
			mWeaponMgr->fire_Normal(pos, direction);
			mFireActionMode ^= FIRE_ACTION_NORMAL;
		}
	}

	void MAIN_CHAR::updateWeapon(const Ogre::FrameEvent& evt)
	{
		mWeaponMgr->update(evt);
	}

	void MAIN_CHAR::setFireAction_Normal()
	{
		mFireActionMode |= FIRE_ACTION_NORMAL;
	}