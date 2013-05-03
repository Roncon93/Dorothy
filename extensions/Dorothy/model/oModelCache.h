#ifndef __DOROTHY_MODEL_OMODELCACHE__
#define __DOROTHY_MODEL_OMODELCACHE__

#include "Dorothy/misc/oXmlItemCache.h"

NS_DOROTHY_BEGIN

class oSpriteDef;
class oModelAnimationDef;
class oKeyAnimationDef;
//class oFrameAnimationDef;
class oModelDef;
class oClipDef;
class oModel;

class oModelCache: public oXmlItemCache<oModelDef>
{
public:
	SHARED_FUNC(oModelCache);
protected:
	oModelCache(){}
	virtual void beforeParse( const char* filename );
	virtual void afterParse( const char* filename );
	virtual void textHandler( void *ctx, const char *s, int len );
	virtual void startElement( void *ctx, const char *name, const char **atts );
	virtual void endElement( void *ctx, const char *name );
	const static uint32 MAX_LOOKS;
private:
	oKeyAnimationDef* getCurrentKeyAnimation();
	stack<oSpriteDef*> _nodeStack;
	CCTexture2D* _currentTexture;
	oClipDef* _currentClip;
	oModelAnimationDef* _currentAnimationDef;
};

#define oSharedModelCache (*oModelCache::shared())

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMODELCACHE__