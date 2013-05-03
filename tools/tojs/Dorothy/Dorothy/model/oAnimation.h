#ifndef __DOROTHY_MODEL_OANIMATION_H__
#define __DOROTHY_MODEL_OANIMATION_H__

#include "Dorothy/misc/oXmlItemCache.h"
#include "Dorothy/model/oActionDuration.h"
#include "Dorothy/model/oModelAnimationDef.h"

NS_DOROTHY_BEGIN

class oClipDef;
class oFrameAction;

class oFrameAction : public CCFiniteTimeAction
{
public:
	void setLoop(bool loop);
	static oFrameAction* create(const char* filename);
};

class oAnimationCache: public CCObject
{
public:
	bool load( const char* filename );
	bool unload( const char* filename );
	void unload();
	SHARED_FUNC(oAnimationCache);
};

#define oSharedAnimationCache oAnimationCache::sharedCache()

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OANIMATION_H__
