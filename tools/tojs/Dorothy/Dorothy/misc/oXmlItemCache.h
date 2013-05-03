#ifndef __DOROTHY_MISC_OXMLITEMCACHE_H__
#define __DOROTHY_MISC_OXMLITEMCACHE_H__

#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oContent.h"

NS_DOROTHY_BEGIN

#define SHARED_FUNC(name) public: static name* shared(){ static name instance;return &instance; }

/** @brief Useful for reading xml files and cache them in memory.
 T is the class to store every parsed xml file.
*/
template<class T = CCObject>
class oXmlItemCache: public CCSAXDelegator
{
public:
	~oXmlItemCache();
	/** Load a new xml file or get its data for cache. */
	T* load( const char* filename );
	/** Purge the cached file. */
	bool unload( const char* filename );
	/** Purge all cached files. */
	void unload();
private:
	/** Implement it to get prepare for specific xml parse. */
	virtual void beforeParse( const char* filename ) = 0;
	/** Implement it to do something after xml is parsed. */
	virtual void afterParse( const char* filename ) = 0;
	/** Implement it to parse xml. */
	virtual void textHandler( void *ctx, const char *s, int len ) = 0;
	/** Implement it to parse xml. */
	virtual void startElement( void *ctx, const char *name, const char **atts ) = 0;
	/** Implement it to parse xml. */
	virtual void endElement( void *ctx, const char *name ) = 0;
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OXMLITEMCACHE_H__