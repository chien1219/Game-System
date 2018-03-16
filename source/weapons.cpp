#include "weapons.h"
#include "BasicTools.h"

WEAPON::WEAPON(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
	playedSound = false;
}

//return true if it hits the sphere with radius r.
bool WEAPON::hitTarget_Sphere(const Vector3 &p, Real r )
{
	bool flg = false;

	Vector3 pos = mSceneNode->getPosition();
	if ( r >= pos.distance( p ) ) {
		Vector3 normal_dir = pos - p;
		normal_dir.normalise( );
		Vector3 new_pos = p + (r+0.5)*normal_dir; 
		mSceneNode->setPosition( new_pos );
		Real d = mVelocity.dotProduct( normal_dir );
		if ( 0.0 >= d ) {
			mVelocity = mVelocity - d*normal_dir;
		}
		flg = true;
	}
	return flg;
}

//
// Decrease its life and disable it if its life is negative
// Compute the position of the weapon
// Check collision between it and the terrain surface
// Adjust its position if it his the terrain surface
//
//
void WEAPON::update(const Ogre::FrameEvent& evt)
{
    mLifeTime -= evt.timeSinceLastFrame;
	if (mLifeTime < 0 ) {
		mLifeTime = 0;
		mSceneNode->setVisible(false);
		mIsAlive = false;
		return;
	}
	Real t = evt.timeSinceLastFrame;
	Vector3 pos = mSceneNode->getPosition();
	pos += mVelocity*t;

	Vector3 grav(0,-29.8, 0);
	mVelocity += grav*t;

	Vector3 new_pos = pos;
	Real r = 5;
	new_pos -= Vector3(0, 1, 0)*r;

    //Check up direction
    bool flg = projectScenePointOntoTerrain_PosDirection(new_pos);
    if (flg) {
        pos = new_pos+Vector3(0,1.0, 0)+Vector3(0, 1, 0)*r;
        mVelocity.y = -mVelocity.y*0.9;
    }
    //
    //Check down direction. 
    
    //Why do we need to do it?

	mSceneNode->setPosition(pos);
    
}