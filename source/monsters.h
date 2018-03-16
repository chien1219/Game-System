#ifndef __MONSTERS_H__
#define __MONSTERS_H__
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "game_obj.h"
#include "game_obj.h"
class MONSTER : public GAME_OBJ {
protected:
	void updateViewDirection();
	void moveUpDown();
	void moveTowardMainChar();
	void moveAwayMainChar();
	bool State;
public:
	MONSTER(SceneManager *a_SceneMgr);
	void setState(bool);
	virtual void update(const Ogre::FrameEvent& evt);
};

#endif