//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: Richard Chien
\n
My ID: 0316235
\n
My Email: richard85014@hotmail.com

This is an assignment of 3D Game Programming

*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "main_char.h"
#include "monster_manager.h"

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);

	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	
	void initParticleSystemForExplosion();
void setOffParticleSystem(
	Ogre::SceneNode *fNode1, const Ogre::String pname, const Ogre::Vector3 &pos);

private:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_00();
	void createScene_01();

	bool mFlgMotion;
	bool mKeyPressed;
	Ogre::Real mToggle;
	Ogre::Light *mLight0;
	Ogre::SceneNode* fNode[512];
	String name[512];
	Ogre::SceneNode *mSN_Sphere;
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
//
	Real mSphereRadius;
	int mKeyPressedZoomMode;
	Real mCameraDistanceSlowDownSpeed;
	Real mCameraDistance;
	Real mCameraDistanceAdjustSpeed;
	MAIN_CHAR *mMainChar;
	MONSTER_MANAGER *mMonsterMgr;
	bool mSphereState;
	Vector3 mCameraHeight;
	int maxNum;

};

#endif // #ifndef __BasicTutorial_00_h_