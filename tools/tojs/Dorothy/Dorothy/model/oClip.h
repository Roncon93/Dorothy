#ifndef __DOROTHY_MODEL_OCLIP__
#define __DOROTHY_MODEL_OCLIP__

#include "Dorothy/misc/oXmlItemCache.h"

NS_DOROTHY_BEGIN

class oClipCache: public CCObject
{
public:
	bool load( const char* filename );
	bool unload( const char* filename );
	void unload();
	SHARED_FUNC(oClipCache);
};

#define oSharedClipCache (*oClipCache::shared())

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OCLIP__