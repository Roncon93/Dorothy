#ifndef __DOROTHY_PLATFORM_OPLATFORMWORLD_H__
#define __DOROTHY_PLATFORM_OPLATFORMWORLD_H__

#include "Dorothy/physics/oWorld.h"

NS_DOROTHY_PLATFORM_BEGIN

class oCamera;

class oLayer: public oNode3D
{ };

class oPlatformWorld: public oWorld
{
public:
	PROPERTY_READONLY(oCamera*, Camera);
	PROPERTY_READONLY(CCNode*, UILayer);
	void clearLayer(int zOrder);
	void clearLayer();
	void setLayerRatio(int zOrder, const CCPoint& ratio);
	const CCPoint& getLayerRatio(int zOrder);
	void setLayerOffset(int zOrder, const CCPoint& offset);
	const CCPoint& getLayerOffset(int zOrder);
	oLayer* getLayer(int zOrder);
	CREATE_FUNC(oPlatformWorld);
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OPLATFORMWORLD_H__