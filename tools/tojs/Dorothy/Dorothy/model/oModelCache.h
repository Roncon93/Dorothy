#ifndef __DOROTHY_MODEL_OMODELCACHE__
#define __DOROTHY_MODEL_OMODELCACHE__

#include "Dorothy/misc/oXmlItemCache.h"

NS_DOROTHY_BEGIN

class oModelDef;

class oModelCache: public CCObject
{
public:
	oModelDef* load( const char* filename );
	bool unload( const char* filename );
	void unload();
	SHARED_FUNC(oModelCache);
};

#define oSharedModelCache (*oModelCache::shared())

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMODELCACHE__