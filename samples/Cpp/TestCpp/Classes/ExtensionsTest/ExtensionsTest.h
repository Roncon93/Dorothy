#ifndef __EXTENSIONS_TEST_H__
#define __EXTENSIONS_TEST_H__

#include "../testBasic.h"

class ExtensionsMainLayer : public CCLayer
{
public:
    virtual void onEnter();
    void menuCallback(CCObject* pSender);
};

class ExtensionsTestScene : public TestScene
{
public:
    virtual void runThisTest();
	CREATE_FUNC(ExtensionsTestScene);
};

#endif /* __EXTENSIONS_TEST_H__ */
