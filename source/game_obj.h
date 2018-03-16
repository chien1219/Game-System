#ifndef __GAME_OBJ__
#define __GAME_OBJ__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

using namespace Ogre;

#define ACTION_NONE	0x0000
#define ACTION_WALK_FORWARD	0x0001
#define ACTION_WALK_BACKWARD	0x0002
#define ACTION_WALK_TURNRIGHT	0x0004
#define ACTION_WALK_TURNLEFT	0x0008

#define FIRE_ACTION_NONE	0x0
#define FIRE_ACTION_NORMAL	0x0001

class GAME_OBJ {
private:
	static int gs_NameIndex;
protected:
	SceneManager *mSceneMgr;
	SceneNode *mSceneNode;
	Entity *mEntity;
	Real mRadius;
	Real mMass;
	Vector3 mVelocity;
	Real mSpeedFactor;
	Quaternion mQuaternion;
	Vector3 mInitDirection;
	Vector3 mInitPosition;
	unsigned int mActionMode;
	unsigned int mFireActionMode;
	//
	Real mLifeTime;
	Real mMaxLifeTime;
	bool mIsAlive;
	//
	
	Real mRandSpeed;
	Real mTime;
	Real mAmplitude;
	GAME_OBJ *mTarget;
	Real mTargetRadius;
	AnimationState *mAnimationState;
	//
public:
	GAME_OBJ(SceneManager *a_SceneMgr);
	Entity *getEntity( ) const { return mEntity; }
virtual void createGameObj(const String &a_Name, const String &a_MeshName);
virtual void setTarget(GAME_OBJ *a_Target, Real radius);
const Vector3 &getPosition() const { return mSceneNode->getPosition();}
const Vector3 &getInitPosition() const { return mInitPosition;}
void translate(const Vector3 &v);
void scale(Real sx, Real sy, Real sz);
virtual void update(const Ogre::FrameEvent& evt);
//virtual void updatePosition(const Ogre::FrameEvent& evt);
bool isAlive() const;
void makeAlive(bool flg = true);
void setLife(Real cLife, Real cMaxLife = -1);

void setPosition(const Vector3 &pos);
void setInitPosition(const Vector3 &pos);
void setVelocity(const Vector3 &v);
void setSpeedFactor(Real f);
void setVisibilityFlags(unsigned int m);
void setVisible(bool flg);
};

#endif