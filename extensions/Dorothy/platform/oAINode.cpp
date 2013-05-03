#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oAINode.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/platform/oProperty.h"
#include "Dorothy/platform/oUnit.h"

NS_DOROTHY_PLATFORM_BEGIN

oInstinct::oInstinct( const string& propName, oAILeaf* node ):
_actionNode(node),
_propName(propName)
{ }

void oInstinct::install(oUnit* unit)
{
	oProperty* prop = unit->properties.get(_propName);
	if (prop)
	{
		prop->changed += std::make_pair(this, &oInstinct::onInstinctPropertyChanged);
	}
}

void oInstinct::uninstall( oUnit* unit )
{
	oProperty* prop = unit->properties.get(_propName);
	if (prop)
	{
		prop->changed -= std::make_pair(this, &oInstinct::onInstinctPropertyChanged);
	}
}

void oInstinct::onInstinctPropertyChanged( oUnit* unit, float oldValue, float newValue )
{
	oAI::_self = unit;
	oAI::_lastDeltaInstinctProperty = newValue - oldValue;
	_actionNode->doAction();
}

oInstinct* oInstinct::create( const string& propName, oAILeaf* node )
{
	oInstinct* instinct = new oInstinct(propName, node);
	instinct->autorelease();
	return instinct;
}

void oAINode::addChild( oAILeaf* node )
{
	_children.push_back(node);
}

void oAINode::removeChild( oAILeaf* node )
{
	_children.remove(node);
}

void oAINode::clear()
{
	_children.clear();
}

const oRefVector<oAILeaf>& oAINode::getChildren() const
{
	return _children;
}

bool oSelNode::doAction()
{
	for (oAILeaf* node : _children)
	{
		if (node->doAction())
		{
			return true;
		}
	}
	return false;
}

oSelNode* oSelNode::create()
{
	oSelNode* node = new oSelNode();
	node->autorelease();
	return node;
}

oSeqNode* oSeqNode::create()
{
	oSeqNode* node = new oSeqNode();
	node->autorelease();
	return node;
}

bool oSeqNode::doAction()
{
	for (oAILeaf* node : _children)
	{
		if (!node->doAction())
		{
			return false;
		}
	}
	return true;
}

oParSelNode* oParSelNode::create()
{
	oParSelNode* node = new oParSelNode();
	node->autorelease();
	return node;
}

bool oParSelNode::doAction()
{
	bool result = true;
	for (oAILeaf* node : _children)
	{
		if (!node->doAction())
		{
			result = false;
		}
	}
	return result;
}

oParSeqNode* oParSeqNode::create()
{
	oParSeqNode* node = new oParSeqNode();
	node->autorelease();
	return node;
}

bool oParSeqNode::doAction()
{
	bool result = false;
	for (oAILeaf* node : _children)
	{
		if (node->doAction())
		{
			result = true;
		}
	}
	return result;
}

bool oActNode::doAction()
{
	return oAI::self()->doIt(_actionId);
}

oAILeaf* oActNode::create(int actionId)
{
	oActNode* node = new oActNode();
	node->_actionId = actionId;
	node->autorelease();
	return node;
}

NS_DOROTHY_PLATFORM_END
