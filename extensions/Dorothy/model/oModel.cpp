#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oModel.h"
#include "Dorothy/model/oModelDef.h"
#include "Dorothy/model/oSequence.h"
#include "Dorothy/model/oModelAnimationDef.h"
#include "Dorothy/model/oKeyFrame.h"
#include "Dorothy/model/oModelCache.h"
#include "Dorothy/misc/oCallFunc.h"

NS_DOROTHY_BEGIN

void oLook::add( CCNode* node )
{
	_nodes.push_back(node);
}

void oLook::apply()
{
	for (CCNode* node : _nodes)
	{
		node->setVisible(false);
	}
}

void oLook::unApply()
{
	for (CCNode* node : _nodes)
	{
		node->setVisible(true);
	}
}

typedef hash_strmap<CCNode*> oNodeMap;

oModel::oModel( oModelDef* def ):
_isPlaying(false),
_isPaused(false),
_faceRight(def->isFaceRight()),
_loop(false),
_currentLook(oLook::None),
_currentAnimation(oAnimation::None),
_modelDef(def),
_speed(1.0f),
_recoverTime(0.0f)
{
	handlers.owner = this;
	_resetAnimation.end = std::make_pair(this, &oModel::onResetAnimationEnd);
}

bool oModel::init()
{
	_root = _modelDef->isBatchUsed() ?
		CCSpriteBatchNode::createWithTexture(_modelDef->getTexture()) :
		CCNode::create();
	oModel::visit(_modelDef->getRoot(), _root);
	this->addChild(_root);
	//Make model`s none look applied below.
	_root->setVisible(false);
	return true;
}

void oModel::addLook( uint32 index, CCNode* node )
{
	for (uint32 n = _looks.size();n < index + 1;_looks.push_back(new oLook()), n++);
	_looks[index]->add(node);
}

void oModel::setLook( int index )
{
	if (index < oLook::None || index >= (int)_looks.size())
	{
		if (_looks.empty() && oLook::None < index && _currentLook == oLook::None)
		{
			_currentLook = index;
			_root->setVisible(true);
		}
		return;
	}
	if (_currentLook != index)
	{
		if (_currentLook != oLook::None)
		{
			_looks[_currentLook]->unApply();
		}
		else
		{
			_root->setVisible(true);
		}
		_currentLook = index;
		if (_currentLook != oLook::None)
		{
			_looks[_currentLook]->apply();
		}
		else
		{
			_root->setVisible(false);
		}
	}
}

void oModel::setLook( const string& name )
{
	int index = _modelDef->getLookIndexByName(name);
	oModel::setLook(index);
}

int oModel::getLook() const
{
	return _currentLook;
}

void oModel::setFaceRight(bool var)
{
	if (_faceRight != var)
	{
		_faceRight = var;
		float right = _modelDef->isFaceRight() ? 1.0f : -1.0f;
		_root->setScaleX(var == _modelDef->isFaceRight() ? right : -right);
	}
}

bool oModel::isFaceRight() const
{
	return _faceRight;
}

void oModel::play( uint32 index )
{
	if (index >= _animationGroups.size())
	{
		return;
	}
	oModel::stop();
	_isPlaying = true;
	_currentAnimation = index;
	if (_recoverTime > 0.0f)
	{
		_isRecovering = true;
		_resetAnimation.run(_recoverTime, _currentAnimation);
	}
	else
	{
		oModel::reset(_modelDef->getRoot(), _root);
		oModel::onResetAnimationEnd();
	}
}

void oModel::play( const string& name )
{
	int index = _modelDef->getAnimationIndexByName(name);
	oModel::play(index);
}

void oModel::addAnimation( uint32 index, CCNode* node, oActionDuration* action )
{
	for (uint32 n = _animationGroups.size();n < index + 1;_animationGroups.push_back(new oAnimationGroup()), n++);
	if (_animationGroups[index]->animations.size() == 0)
	{
		action = oSequence::createWithTwoActions(
			action,
			oCallFunc::create(this, callfunc_selector(oModel::onActionEnd)));
	}
	_animationGroups[index]->animations.push_back(new oAnimation(node, action));
}

void oModel::stop()
{
	_isPlaying = false;
	oModel::resume();
	if (_isRecovering)
	{
		_resetAnimation.stop();
	}
	else
	{
		if (_currentAnimation != oAnimation::None)
		{
			for (oAnimation* animation : _animationGroups[_currentAnimation]->animations)
			{
				animation->stop();
			}
		}
	}
}

bool oModel::isPlaying() const
{
	return _isPlaying;
}

void oModel::reset( oSpriteDef* parentDef, CCNode* parentNode )
{
	CCArray* children = parentNode->getChildren();
	if (children)
	{
		const oOwnVector<oSpriteDef>& childrenDefs = parentDef->children;
		for (uint32 n = 0;n < children->count();n++)
		{
			CCNode* childNode = (CCNode*)children->objectAtIndex(n);
			childrenDefs[n]->restore((CCSprite*)childNode);
			oModel::reset(childrenDefs[n], childNode);
		}
	}
}

void oModel::onActionEnd()
{
	if (_loop)
	{
		for (oAnimation* animation : _animationGroups[_currentAnimation]->animations)
		{
			animation->stop();
			animation->run();
		}
	}
	else
	{
		_isPlaying = false;
	}
	_animationGroups[_currentAnimation]->animationEnd(this);
}

void oModel::setLoop( bool loop )
{
	_loop = loop;
}

bool oModel::getLoop() const
{
	return _loop;
}

int oModel::getCurrentAnimationIndex() const
{
	if (_isPlaying)
	{
		return _currentAnimation;
	}
	return oAnimation::None;
}

void oModel::resume( uint32 index )
{
	oModel::resume();
	if (_currentAnimation != index)
	{
		oModel::play(index);
	}
}

void oModel::resume( const string& name )
{
	int index = _modelDef->getAnimationIndexByName(name);
	oModel::resume(index);
}

void oModel::resume()
{
	if (_isPaused)
	{
		_isPaused = false;
		if (!_isRecovering)
		{
			for (oAnimation* animation : _animationGroups[_currentAnimation]->animations)
			{
				animation->resume();
			}
		}
	}
}

oModelDef* oModel::getModelDef() const
{
	return _modelDef;
}

bool oModel::isPaused() const
{
	return _isPaused;
}

void oModel::pause()
{
	if (_isPlaying && !_isPaused)
	{
		_isPaused = true;
		for (oAnimation* animation : _animationGroups[_currentAnimation]->animations)
		{
			animation->pause();
		}
	}
}

void oModel::setSpeed( float speed )
{
	if (_speed != speed)
	{
		_speed = speed;
		for (oAnimationGroup* animationGroup : _animationGroups)
		{
			for (oAnimation* animation : animationGroup->animations)
			{
				animation->setSpeed(speed);
			}
		}
	}
}

float oModel::getSpeed() const
{
	return _speed;
}

void oModel::setTime( float time )
{
	if (_isPlaying)
	{
		for (oAnimation* animation : _animationGroups[_currentAnimation]->animations)
		{
			animation->setTime(time);
		}
	}
}

float oModel::getTime() const
{
	if (_isPlaying)
	{
		if (!_animationGroups[_currentAnimation]->animations.empty())
		{
			return _animationGroups[_currentAnimation]->animations[0]->getTime();
		}
	}
	return 0.0f;
}

void oModel::setRecovery(float var)
{
	if (var < 0.0f)
	{
		var = 0.0f;
	}
	_recoverTime = var;
}

float oModel::getRecovery() const
{
	return _recoverTime;
}

float oModel::getDuration() const
{
	if (_currentAnimation != oAnimation::None)
	{
		return _animationGroups[_currentAnimation]->animations[0]->getDuration();
	}
	return 0;
}

oModel* oModel::none()
{
	return oModelDef::create()->toModel();
}

void oModel::onResetAnimationEnd()
{
	_isRecovering = false;
	for (oAnimation* animation : _animationGroups[_currentAnimation]->animations)
	{
		animation->run();
	}
}

oModel* oModel::create( oModelDef* modelDef )
{
	oModel* model = new oModel(modelDef);
	if (model && model->init())
	{
		model->autorelease();
		return model;
	}
	CC_SAFE_DELETE(model);
	return nullptr;
}

oModel* oModel::create( const char* filename )
{
	oModelDef* modelDef = oSharedModelCache.load(filename);
	return modelDef->toModel();
}

void oModel::visit( oSpriteDef* parentDef, CCNode* parentNode )
{
	if (!parentDef)
	{
		return;
	}
	const oOwnVector<oSpriteDef>& childrenDefs = parentDef->children;
	for (uint32 n = 0;n < childrenDefs.size();n++)
	{
		oSpriteDef* nodeDef = childrenDefs[n];
		CCSprite* node = nodeDef->toSprite();
		oModel::visit(nodeDef, node);

		if (!_modelDef->isBatchUsed() && !nodeDef->name.empty())
		{
			oModel::nodeMap()[nodeDef->name] = node;
		}

		CCFiniteTimeAction* animation;
		CCArray* keyFrames;
		std::tie(animation, keyFrames) = nodeDef->toResetAction();
		_resetAnimation.add(nodeDef, node, animation, keyFrames);

		parentNode->addChild(node);
		// Look
		if (!nodeDef->looks.empty())
		{
			for (int lookIndex : nodeDef->looks)
			{
				oModel::addLook(lookIndex, node);
			}
		}
		// Animation
		const oOwnVector<oModelAnimationDef>& animationDefs = nodeDef->animationDefs;
		for (int i = 0;i < (int)animationDefs.size();i++)
		{
			oModelAnimationDef* animationDef = animationDefs[i];
			if (animationDef)
			{
				oModel::addAnimation(i, node, animationDef->toAction());
			}
		}
	}
}

oNodeMap& oModel::nodeMap()
{
	if (!_nodeMap)
	{
		_nodeMap = oOwnMake(new oNodeMap());
	}
	return *_nodeMap;
}

CCNode* oModel::getNodeByName( const string& name )
{
	if (!_nodeMap)
	{
		return nullptr;
	}
	else
	{
		auto it = _nodeMap->find(name);
		if (it != _nodeMap->end())
		{
			return it->second;
		}
		return nullptr;
	}
}

string oModel::getCurrentAnimationName() const
{
	return _modelDef->getAnimationNameByIndex(_currentAnimation);
}

oAnimation::oAnimation( CCNode* node, oActionDuration* action ):
_node(node),
_action(action)
{ }

void oAnimation::run()
{
	_node->runAction(_action);
}

void oAnimation::stop()
{
	_node->stopAction(_action);
}

CCNode* oAnimation::getNode() const
{
	return _node;
}

oActionDuration* oAnimation::getAction()
{
	return _action;
}

void oAnimation::pause()
{
	_action->pause();
}

void oAnimation::resume()
{
	_action->resume();
}

void oAnimation::setSpeed( float speed )
{
	_action->setSpeed(speed);
}

float oAnimation::getSpeed() const
{
	return _action->getSpeed();
}

void oAnimation::setTime( float time )
{
	_action->setTime(time);
}

float oAnimation::getTime() const
{
	return _action->getTime();
}

float oAnimation::getDuration() const
{
	return _action->getDuration();
}

void oResetAnimation::add( oSpriteDef* spriteDef, CCNode* node, CCFiniteTimeAction* animation, CCArray* keyFrames )
{
	oAnimationData* data = new oAnimationData();
	data->spriteDef = spriteDef;
	data->node = node;
	data->animation = animation;
	data->keyFrames = keyFrames;
	_group.push_back(data);
	if (_group.size() == 1)
	{
		_group[0]->animation = oSequence::createWithTwoActions(
			_group[0]->animation,
			oCallFunc::create(this, callfunc_selector(oResetAnimation::onActionEnd)));
	}
}

void oResetAnimation::run(float duration, int index)
{
	for (oAnimationData* pair : _group)
	{
		if (pair->keyFrames)
		{
			oModelAnimationDef* animationDef = nullptr;
			if (index < (int)pair->spriteDef->animationDefs.size())
			{
				animationDef = pair->spriteDef->animationDefs[index];
			}
			if (animationDef)
			{
				animationDef->restoreResetAnimation(pair->keyFrames);
			}
			else
			{
				((oKeyPos*)(pair->keyFrames->objectAtIndex(0)))->setValue(pair->spriteDef->x, pair->spriteDef->y);
				((oKeyScale*)(pair->keyFrames->objectAtIndex(1)))->setValue(pair->spriteDef->scaleX, pair->spriteDef->scaleY);
				((oKeyRoll*)(pair->keyFrames->objectAtIndex(2)))->setValue(pair->spriteDef->rotation);
				((oKeySkew*)(pair->keyFrames->objectAtIndex(3)))->setValue(pair->spriteDef->skewX, pair->spriteDef->skewY);
				((oKeyOpacity*)(pair->keyFrames->objectAtIndex(4)))->setValue(pair->spriteDef->opacity);
			}
		}
		pair->node->stopAllActions();
		pair->animation->setDuration(duration);
		pair->node->runAction(pair->animation);
	}
}

void oResetAnimation::stop()
{
	for (oAnimationData* pair : _group)
	{
		pair->node->stopAction(pair->animation);
	}
}

void oResetAnimation::onActionEnd()
{
	end();
}

oAnimationHandler& oModel::oAnimationHandlerGroup::operator[]( int index )
{
	return owner->_animationGroups[index]->animationEnd;
}

oAnimationHandler& oModel::oAnimationHandlerGroup::operator[]( const string& name )
{
	return owner->_animationGroups[owner->_modelDef->getAnimationIndexByName(name)]->animationEnd;
}

NS_DOROTHY_END
