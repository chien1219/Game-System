//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "read_data.h"

using namespace Ogre;
BasicTutorial_00::BasicTutorial_00(void) {
	mFlgMotion = true;
	mToggle = 2.5;
	mKeyPressed = false;
	//
	mMainChar = 0;
	mCameraDistance = 0;
	mKeyPressedZoomMode = 0;
	mSphereState = false;
	mCameraDistanceAdjustSpeed = 0;
	mCameraDistanceSlowDownSpeed = 0;
	mCameraHeight = Vector3(0, 700, -1);
}

//
//handle the mouse motion (passive) event
//
bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
	bool flg = BaseApplication::mouseMoved(arg);
	mMainChar->updateViewDirection();
	return flg;
}

//handle the key pressed event
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
	//bool flg = BaseApplication::keyPressed(arg);
	bool flg = true;
	
	if (arg.key == OIS::KC_T) {
		mMainChar->setWalkForward();
	}
	if(arg.key == OIS::KC_G){
		mMainChar->setWalkBackward();
	}
	
	if(arg.key == OIS::KC_S){
		mCameraHeight += Vector3(0, -10 , 0);
	}

	if(arg.key == OIS::KC_D){
		mCameraHeight += Vector3(0, 10 , 0);
	}

	if (arg.key == OIS::KC_SPACE)
	{
		mMainChar->setFireAction_Normal();
	}

	return flg;
}

//handle the key released event
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
	bool flg = true;

	if (arg.key == OIS::KC_T) {
		mMainChar->unsetWalkForward();
	}
	if(arg.key == OIS::KC_G){
		mMainChar->unsetWalkBackward();
	}

	if(arg.key == OIS::KC_S){
		mCameraHeight += Vector3(0, -10 , 0);
	}

	if(arg.key == OIS::KC_D){
		mCameraHeight += Vector3(0, 10 , 0);
	}
		
	if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}
	return flg;
}
void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(
	ST_EXTERIOR_CLOSE, "primary");
	mSceneMgrArr[1] =mSceneMgrArr[0];

}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,90,0));
	mCamera->lookAt(Ogre::Vector3(0,50,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam2");
	mCamera->setPosition(mCameraArr[0]->getPosition() + mCameraHeight);
	mCamera->lookAt(mCameraArr[0]->getPosition());
	mCamera->setNearClipDistance(5);
	//mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller

}

void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,1));
	mCamera->setAspectRatio( Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()) );
	vp->setVisibilityMask(0xF);
}

void BasicTutorial_00::createViewport_01(void)
{
	mCamera = mCameraArr[1];

	Ogre::Viewport* vp = mWindow->addViewport(
		mCamera,
		1,
		0.75,
		0,
		0.25,
		0.5
		);
	vp->setBackgroundColour(Ogre::ColourValue(0,1,0));
	vp->setOverlaysEnabled(false);
	mCamera->setAspectRatio(1.0/4.0);

}



void BasicTutorial_00::createScene_00(void) 
{
    /////////////////////////////////////
	DATA_READER::readData(); //Read the data file here.
	bt_Init(mTrayMgr, mSceneMgrArr[0], mCameraArr[0]); //Set the pointers of the objects so that the other functions can use the objects.
    /////////////////////////////////////

	mSceneMgr = mSceneMgrArr[0];
	
	ColourValue fadeColour(0.9, 0.9, 0.9); 

	Vector3 org = Vector3(750, 51, 750);
    mSceneMgr->setAmbientLight( ColourValue( 0.7, 0.7, 0.7 ) ); 

	//Set Fog
	if(DATA_READER::isEnabledExpFog())
	{
		Real density = DATA_READER::getExpFogDensity();
		mSceneMgr->setFog(FOG_EXP, fadeColour, density);
	}

	//Set Shadow
	if(DATA_READER::isEnabledShadow())
	{
		mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);
	}

	//Set Terrain and Skybox
	mSceneMgr->setWorldGeometry("terrain.cfg");
	mSceneMgr->setSkyBox(true, "Examples/TrippySkyBox");

	//Create Plane
	Plane plane(Vector3::UNIT_Y, DATA_READER::getWaterCoord_Y());
	MeshManager::getSingleton().createPlane(
		"Water",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		20000, 20000,
		20, 20,
		true,
		1,
		5,5,
		Vector3::UNIT_Z
		);

	Entity *planeEnt = mSceneMgr->createEntity("WaterEntity", "Water");
	planeEnt->setMaterialName(DATA_READER::getWaterMaterialName());
	SceneNode *planeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	planeNode->setPosition(0, DATA_READER::getWaterCoord_Y(), 0);
	planeNode->attachObject(planeEnt);

	//init Particle System
	initParticleSystemForExplosion();
	Vector3 pos;

	//Create Light
	Light *light;
	light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_SPOTLIGHT);
	//light->setType(Light::LT_DIRECTIONAL);
	light->setPosition(Vector3(0, 450, 250)+org); 
	light->setDiffuseColour(0.7, 0.7, 0.7);		
	light->setSpecularColour(1.0, 1.0, 1.0);	
	light->setDirection(Vector3(1, 1, 1));
	mLight0 = light;

	//Create Charater
	mMainChar = new MAIN_CHAR(mSceneMgrArr[0]);
	mMainChar->createGameObj("m", "robot.mesh");
	mMainChar->attachCamera(mCameraArr[0]);
	mMainChar->setMaxBulletsNum(DATA_READER::getMaxBulletsNum());
	mMainChar->setVisibilityFlags(0xF0);

	//Create Monster
	mMonsterMgr = new MONSTER_MANAGER(mSceneMgrArr[0]);
	mMonsterMgr->setTargetForMonsters(mMainChar);
	mMonsterMgr->setMaxMonstersNum(DATA_READER::getMaxMonstersNum());

	//Set up Particle System
	maxNum = DATA_READER::getMaxMonstersNum();
	for(int i=0;i<maxNum;++i)
		setOffParticleSystem(fNode[i], name[i], mMonsterMgr->getMonsterPos(i));

	//Create Big Sphere
	Entity* sphereEntity = mSceneMgr->createEntity("SphereEntity", "sphere.mesh");
	sphereEntity->setMaterialName("Examples/SphereMappedRustySteel");
	mSN_Sphere = mSceneMgr->getRootSceneNode()->createChildSceneNode("LargeSphere", Vector3(800, 300, 800));
	mSN_Sphere->scale(Vector3(2,2,2));
	mSN_Sphere->attachObject(sphereEntity);
	mSphereRadius = 200;

}

void BasicTutorial_00::createScene_01(void) 
{
	return;
}

/*
Implement the game logic in this function.
*/
bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
	mToggle += evt.timeSinceLastFrame;
    
	//update second viewport camera position
	mCamera = mSceneMgr->getCamera("PlayerCam2");
	mCamera->setPosition(mCameraArr[0]->getPosition() + mCameraHeight);
	mCamera->lookAt(mCameraArr[0]->getPosition());

	//Update Big Sphere
	Vector3 LScurPos = mSN_Sphere->getPosition();
	if (mSphereState){
		Vector3 newPos = LScurPos + Vector3(0, 0.2, 0);
		if (newPos.y > 450)
			mSphereState = false;
		mSN_Sphere->setPosition(newPos);
	}
	else{
		Vector3 newPos = LScurPos + Vector3(0, -0.2, 0);
		if (newPos.y < 300)
			mSphereState = true;
		mSN_Sphere->setPosition(newPos);
	}
	mMainChar->getWeaponManager()->setTarget(mSN_Sphere->getPosition(),mSphereRadius);

	//Update Spotlight Direction
	mLight0->setDirection(mMainChar->getPosition() - mLight0->getPosition());

	//Particle System
	for(int i=0;i<maxNum;++i){
		if ((mCameraArr[0]->getPosition() - mMonsterMgr->getMonsterPos(i)).length() < 100)
			fNode[i]->setPosition(mMonsterMgr->getMonsterPos(i));
	}

	mMainChar->update(evt);	
    mMonsterMgr->update(evt);
	return flg;
}

void BasicTutorial_00::createViewports(void)
{
	createViewport_00();
	createViewport_01();
	mCamera = mCameraArr[0];
}

void BasicTutorial_00::createCamera(void) {
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
	mCamera = mCameraArr[0];
}

void BasicTutorial_00::createScene( void ) {
	createScene_00();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
}

void BasicTutorial_00::initParticleSystemForExplosion() {
	for(int i=0;i<512;++i){
		//String name;
		genNameUsingIndex("E1",i, name[i]);

		fNode[i] = static_cast<SceneNode*>(
			mSceneMgr->getRootSceneNode()->createChild());
		//ParticleSystem* p = mSceneMgr->createParticleSystem(
		//		name[i], "Examples/JetEngine1");
		ParticleSystem* p = mSceneMgr->createParticleSystem(
			name[i], "Examples/GreenyNimbus");

		ParticleEmitter *e = p->getEmitter(0);
		e->setEnabled(false);
		fNode[i]->attachObject(p);
		fNode[i]->setPosition(Vector3::ZERO);
		fNode[i]->setVisible(false);
	}
}

void BasicTutorial_00::setOffParticleSystem(
	Ogre::SceneNode *fNode1, const Ogre::String pname, const Ogre::Vector3 &pos) 
{
	fNode1->setPosition(pos);
	fNode1->setVisible(true);
	MovableObject *s = fNode1->getAttachedObject(pname);
	ParticleSystem* p =static_cast<ParticleSystem*>(s);
	if (p == NULL) return;
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
