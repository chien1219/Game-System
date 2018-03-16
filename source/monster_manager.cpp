#include "monster_manager.h"
#include "read_data.h"

MONSTER_MANAGER::MONSTER_MANAGER(SceneManager *a_SceneMgr): GAME_OBJ(a_SceneMgr)
{

	mMonstersTarget = 0;
	mCurMonstersNum = mNumMonsters = 512;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		mLifeStateArr[i] = true;
		mMonstersArr[i] = new MONSTER(a_SceneMgr);
		bool state = rand()%2;
		mMonstersArr[i]->setState(state);
		//mMonstersArr[i]->createGameObj("m", "ogrehead.mesh");
		//mMonstersArr[i]->createGameObj("m", "cube.mesh");
		mMonstersArr[i]->createGameObj("m", DATA_READER::getMeshName());
		Vector3 org(750, 100, 750);
		Vector3 pos;
		Real x = -1+2*(rand()%100)/100.0;
		Real z = -1+2*(rand()%100)/100.0;
		pos.x = 700*x;
		pos.z = 700*z;
		pos.y = 20;

		mMonstersArr[i]->setPosition(pos+org);
		mMonstersArr[i]->setInitPosition(pos+org);
		Real sx, sy, sz;
		sx = sy = sz = DATA_READER::getMeshScale();
		mMonstersArr[i]->scale(sx, sy, sz);
	}

}
void MONSTER_MANAGER::setMaxMonstersNum(int a_Num)
{
	if (a_Num >= mNumMonsters) 
	{
		a_Num = mNumMonsters;
	}


	mCurMonstersNum = a_Num;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		if (i<mCurMonstersNum) {
			mMonstersArr[i]->setVisible(true);
			mMonstersArr[i]->makeAlive(true);
		} else {
			mMonstersArr[i]->setVisible(false);
			mMonstersArr[i]->makeAlive(false);
		}
	}
}

void MONSTER_MANAGER::setTargetForMonsters(GAME_OBJ *a_Target)
{

	mMonstersTarget = a_Target;
	for (int i = 0; i < mNumMonsters; ++i) 
	{
		Vector3 p = mMonstersArr[i]->getInitPosition();
		mMonstersArr[i]->setTarget(a_Target, 0);
	}
}

//resolve collision between the target and the monsters
void MONSTER_MANAGER::resolveMonsterTargetCollision()
{
	if (mMonstersTarget == 0) return;	
	Vector3 p1 = mMonstersTarget->getPosition();
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		Vector3 p0 = mMonstersArr[i]->getPosition();
		Vector3 mm = p0 - p1;
		mm.y = 0;
		Real d = mm.length();
		mm.length();
		mm.normalise();
		if (d < 70) {
			d = 70 - d +1.0;
			mMonstersArr[i]->translate(d*mm);
		}
	}
}

//resolve collision between monsters
void MONSTER_MANAGER::resolveMonsterCollision()
{
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		for (int j = i+1; j < mCurMonstersNum; ++j) 
		{
			Vector3 p0 = mMonstersArr[i]->getPosition();
			Vector3 p1 = mMonstersArr[j]->getPosition();
			Vector3 mm = p0 - p1;
			mm.y = 0;
			Real d = mm.length();
			mm.length();
			mm.normalise();
			if (d < 50) {
				d = 50 - d +1.0;
				mMonstersArr[i]->translate(d*mm);
				mMonstersArr[j]->translate(-d*mm);
			}
		}
	}
}

Vector3 MONSTER_MANAGER::getMonsterPos(int i){
	Vector3 pos = mMonstersArr[i]->getPosition();
	return pos;
}

//compute the positions of the monsters
//resolve collision between monsters
//resolve collision between the target and the monsters
void MONSTER_MANAGER::update(const Ogre::FrameEvent& evt)
{
	for (int i = 0; i < mCurMonstersNum; ++i) 
	{
		Vector3 p = mMonstersArr[i]->getInitPosition();

		mMonstersArr[i]->update(evt);
	}

    resolveMonsterCollision();
    resolveMonsterTargetCollision();
	
}
