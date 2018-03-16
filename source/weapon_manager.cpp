#include "weapon_manager.h"

WEAPON_MANAGER::WEAPON_MANAGER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
	mCoolDownTimeForFiring = 0.0;
mMaxCoolDownTime = 0.1;
//
mMaxNum = 128;
mCurBulletsNum = mMaxNum;
for (int i = 0; i < mMaxNum; ++i) {
	mUsedWeaponsArr[i] = false;
	 mBulletsArr[i] = new WEAPON(mSceneMgr);
	 mBulletsArr[i]->createGameObj("b", "sphere.mesh");
mBulletsArr[i]->scale(0.05, 0.05, 0.05);
mBulletsArr[i]->setVisible(false);
mBulletsArr[i]->getEntity( )->setMaterialName("Examples/RustySteel");
}
mFlgTarget = false;
sound = new SOUND();
sound->init();
}

void WEAPON_MANAGER::setTarget( const Vector3 &pos, Real radius )
{
	 mTargetPos = pos;
	 mTargetRadius = radius;
	 mFlgTarget = true;
}


void WEAPON_MANAGER::setMaxBulletsNum(int a_Num)
{
	if (a_Num >= mMaxNum) {
		a_Num = mMaxNum;
	}

	mCurBulletsNum = a_Num;
}

void WEAPON_MANAGER::fire_Normal(const Vector3 &pos, const Vector3 &direction)
{

GAME_OBJ *g = 0;
for (int i = 0; i < mCurBulletsNum; ++i) {
		if (mUsedWeaponsArr[i] == true) continue;
g = mBulletsArr[i];
mUsedWeaponsArr[i] = true;
break;
}
if (g == 0) return;
	if (mCoolDownTimeForFiring < mMaxCoolDownTime) return;
mCoolDownTimeForFiring = 0;
g->setPosition(pos);
g->setVelocity(direction*200);
g->setSpeedFactor(1);
g->setLife(5, 5);
g->makeAlive();

}

void WEAPON_MANAGER::update(const Ogre::FrameEvent& evt)
{
	mCoolDownTimeForFiring += evt.timeSinceLastFrame;
	if (mCoolDownTimeForFiring > mMaxCoolDownTime)
	{
		mCoolDownTimeForFiring = mMaxCoolDownTime;
	}
	for (int i = 0; i < mMaxNum; ++i) {
		if (mUsedWeaponsArr[i] == false) continue;
		WEAPON *g = mBulletsArr[i];
		g->update(evt);

		if ( mFlgTarget ) {
			if(g->hitTarget_Sphere( mTargetPos, mTargetRadius)){
				if(!g->playedSound){
					//play Sound
					sound->play();
					g->playedSound = true;
				}
			}
		}
		if (!g->isAlive()) {
			mUsedWeaponsArr[i] = false;
			g->playedSound = false;
		}
	}

}
