#include <fstream>
#include <iostream>
#include <string>
#include "read_data.h"
#define DATA_FILE_NAME	"0316235_game_data.txt"

using namespace std;
bool DATA_READER::mEnableShadow = true;
int	DATA_READER::mMaxBulletsNum = 10;
int	DATA_READER::mMaxMonstersNum = 10;
double	DATA_READER::mWaterCoord_Y = 0.0;
std::string DATA_READER::mWaterMaterialName = "";
std::string DATA_READER::mMeshName = "";
double DATA_READER::mMeshScale = 1.0;
bool DATA_READER::mEnableExpFog = true;
float DATA_READER::mExpFogDensity = 0.0003;

DATA_READER::DATA_READER()
{

}

void DATA_READER::readData()
{
	using namespace std;
	std::ifstream *fp;
	fp = new std::ifstream(DATA_FILE_NAME, ios::in | ios::binary);
	if (fp == 0 || fp->fail()) {
		cout << "Cannot open data file:" << DATA_FILE_NAME << endl;
		return;
	}
	
	std::string key;
	double num;
	while (!fp->eof()) {
	*fp >> key;
	
	

	if (key.compare("NUM_BULLETS") == 0) {
		*fp >> num;
		mMaxBulletsNum = num; // bug here
	}

	if (key.compare("NUM_MONSTERS") == 0) {
		*fp >> num;
		mMaxMonstersNum = num; // bug here
	}

if (key.compare("WATER_Y_COORD") == 0) {
		*fp >> num;
		mWaterCoord_Y = num; // bug here
	}

if (key.compare("MESH_SCALE") == 0) {
		*fp >> num; // bug here
		mMeshScale = num;
		//mMeshScale = 0.25; // bug here
	}

if (key.compare("WATER_MATERIAL") == 0) {
		 // bug here. read the material name 
		 // and store it to mWaterMaterialName
		 *fp >> mWaterMaterialName; 
	
	}
if (key.compare("MESH_NAME") == 0) {
		*fp >> mMeshName;
	
	}
if (key.compare("EXP_FOG_ENABLED") == 0) {
		*fp >> mEnableExpFog;
		*fp >> mExpFogDensity;
	}

if (key.compare("SHADOW_ENABLED") == 0) {
	   //bug here. Read the boolean value and store it to mEnableShadow
		*fp >> num;
		mEnableShadow = num;
	}

	}

}

bool DATA_READER::isEnabledShadow()
{
	return mEnableShadow;
}

int DATA_READER::getMaxBulletsNum()
{
	return mMaxBulletsNum;
}
	
bool DATA_READER::isEnabledExpFog()
{
	return mEnableExpFog;
}

float DATA_READER::getExpFogDensity()
{
	return mExpFogDensity;
}


int DATA_READER::getMaxMonstersNum()
{
	return mMaxMonstersNum;
}

double DATA_READER::getMeshScale()
{
	return mMeshScale;
}
double DATA_READER::getWaterCoord_Y()
{
	return mWaterCoord_Y;
}

std::string DATA_READER::getWaterMaterialName()
{
	return mWaterMaterialName;
}

std::string DATA_READER::getMeshName()
{
	return mMeshName;
}