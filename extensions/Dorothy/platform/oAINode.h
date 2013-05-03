#ifndef __DOROTHY_PLATFORM_OAI_NODE_H__
#define __DOROTHY_PLATFORM_OAI_NODE_H__

#include "Dorothy/platform/oProperty.h"

NS_DOROTHY_PLATFORM_BEGIN

class oUnit;
class oAILeaf;

class oInstinct: public CCObject
{
public:
	void install(oUnit* unit);
	void uninstall(oUnit* unit);
	void onInstinctPropertyChanged(oUnit* unit, float oldValue, float newValue);
	static oInstinct* create(const string& propName, oAILeaf* node);
protected:
	oInstinct(const string& propName, oAILeaf* node);
private:
	string _propName;
	oRef<oAILeaf> _actionNode;
};

/** @brief Behavior Tree base node */

class oAILeaf: public CCObject
{
public:
	virtual bool doAction() = 0;
};

class oAINode: public oAILeaf
{
public:
	virtual void addChild(oAILeaf* node);
	virtual void removeChild(oAILeaf* node);
	virtual void clear();
	const oRefVector<oAILeaf>& getChildren() const;
protected:
	oRefVector<oAILeaf> _children;
};

/** @brief Selector Node */
class oSelNode: public oAINode
{
public:
	virtual bool doAction();
	static oSelNode* create();
};

/** @brief Sequence Node */
class oSeqNode: public oAINode
{
public:
	virtual bool doAction();
	static oSeqNode* create();
};

/** @brief Parallel Selector Node */
class oParSelNode: public oAINode
{
public:
	virtual bool doAction();
	static oParSelNode* create();
};

/** @brief Parallel Sequence Node */
class oParSeqNode: public oAINode
{
public:
	virtual bool doAction();
	static oParSeqNode* create();
};

class oActNode: public oAILeaf
{
public:
	virtual bool doAction();
	static oAILeaf* create(int actionId);
private:
	int _actionId;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OAI_NODE_H__
