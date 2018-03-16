#ifndef __DATA_READER_H__
#define __DATA_READER_H__

#include <string>

class DATA_READER {
protected:
	static bool mEnableExpFog;
	static bool mEnableShadow;
	static float mExpFogDensity;
	static int mMaxBulletsNum;
	static int mMaxMonstersNum;
	static double mWaterCoord_Y;
	static std::string mWaterMaterialName;
	static std::string mMeshName;
	static double mMeshScale;
public:
	DATA_READER();
	static void readData();
	static bool isEnabledShadow();
	static bool isEnabledExpFog();
	static float getExpFogDensity();
	static int getMaxBulletsNum();
	static int getMaxMonstersNum();
	static double getWaterCoord_Y();
	static std::string getWaterMaterialName();
static std::string getMeshName();
static double getMeshScale();
};

#endif