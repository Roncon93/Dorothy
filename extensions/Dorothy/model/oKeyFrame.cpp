#include "Dorothy/const/oDefine.h"
#include "Dorothy/model/oKeyFrame.h"
#include "Dorothy/model/oKeyFrameDef.h"

NS_DOROTHY_BEGIN

void oKeyReset::update( float time )
{
	CC_UNUSED_PARAM(time);
	m_pTarget->setPosition(_x, _y);
	m_pTarget->setScaleX(_scaleX);
	m_pTarget->setScaleY(_scaleY);
	m_pTarget->setSkewX(_skewX);
	m_pTarget->setSkewY(_skewY);
	m_pTarget->setRotation(_rotation);
	m_pTarget->setVisible(_visible);
	((CCSprite*)m_pTarget)->setOpacity(_opacity);
}
CCFiniteTimeAction* oKeyReset::reverse()
{
	return (CCFiniteTimeAction*)oKeyReset::copyWithZone(nullptr);
}
CCObject* oKeyReset::copyWithZone( CCZone* zone )
{
	CCZone *pNewZone = NULL;
	oKeyReset *pRet = NULL;
	if (zone && zone->m_pCopyObject) {
		pRet = (oKeyReset*) (zone->m_pCopyObject);
	} else {
		pRet = new oKeyReset();
		zone = pNewZone = new CCZone(pRet);
	}

	CCActionInstant::copyWithZone(zone);
	CC_SAFE_DELETE(pNewZone);
	return pRet;
}
oKeyReset* oKeyReset::create( oKeyFrameDef* def )
{
	oKeyReset* keyReset = new oKeyReset();
	keyReset->_x = def->x;
	keyReset->_y = def->y;
	keyReset->_scaleX = def->scaleX;
	keyReset->_scaleY = def->scaleY;
	keyReset->_skewX = def->skewX;
	keyReset->_skewY = def->skewY;
	keyReset->_rotation = def->rotation;
	keyReset->_visible = def->visible;
	keyReset->_opacity = def->opacity;
	keyReset->autorelease();
	return keyReset;
}

void oKeyPos::setEase( int easeId )
{
	_ease = oEase::get(easeId);
}
bool oKeyPos::initWithDuration( float duration, float posX, float posY )
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_endPosX = posX;
		_endPosY = posY;
		return true;
	}
	return false;
}
CCObject* oKeyPos::copyWithZone( CCZone* pZone )
{
	CCZone* pNewZone = NULL;
	oKeyPos* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		pCopy = (oKeyPos*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oKeyPos();
		pZone = pNewZone = new CCZone(pCopy);
	}
	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	pCopy->initWithDuration(m_fDuration, _endPosX, _endPosY);
	return pCopy;
}
void oKeyPos::startWithTarget( CCNode *pTarget )
{
	CCActionInterval::startWithTarget(pTarget);
	_startPosX = pTarget->getPositionX();
	_startPosY = pTarget->getPositionY();
	_deltaPosX = _endPosX - _startPosX;
	_deltaPosY = _endPosY - _startPosY;
}
void oKeyPos::update( float time )
{
	m_pTarget->setPosition(
		_ease(time, _startPosX, _deltaPosX),
		_ease(time, _startPosY, _deltaPosY));
}
oKeyPos* oKeyPos::create( float duration, float posX, float posY, int easeId )
{
	oKeyPos* keyPos = new oKeyPos();
	keyPos->_ease = oEase::get(easeId);
	keyPos->initWithDuration(duration, posX, posY);
	keyPos->autorelease();
	return keyPos;
}
void oKeyPos::setValue( float endX, float endY )
{
	_endPosX = endX;
	_endPosY = endY;
}

void oKeyScale::setEase( int easeId )
{
	_ease = oEase::get(easeId);
}
bool oKeyScale::initWithDuration( float duration, float scaleX, float scaleY )
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_endScaleX = scaleX;
		_endScaleY = scaleY;
		return true;
	}
	return false;
}
CCObject* oKeyScale::copyWithZone( CCZone* pZone )
{
	CCZone* pNewZone = NULL;
	oKeyScale* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		pCopy = (oKeyScale*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oKeyScale();
		pZone = pNewZone = new CCZone(pCopy);
	}
	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	pCopy->initWithDuration(m_fDuration, _endScaleX, _endScaleY);
	return pCopy;
}
void oKeyScale::startWithTarget( CCNode *pTarget )
{
	CCActionInterval::startWithTarget(pTarget);
	_startScaleX = pTarget->getScaleX();
	_startScaleY = pTarget->getScaleY();
	_deltaScaleX = _endScaleX - _startScaleX;
	_deltaScaleY = _endScaleY - _startScaleY;
}
void oKeyScale::update( float time )
{
	m_pTarget->setScaleX(_ease(time, _startScaleX, _deltaScaleX));
	m_pTarget->setScaleY(_ease(time, _startScaleY, _deltaScaleY));
}
oKeyScale* oKeyScale::create( float duration, float scaleX, float scaleY, int easeId )
{
	oKeyScale* keyScale = new oKeyScale();
	keyScale->_ease = oEase::get(easeId);
	keyScale->initWithDuration(duration, scaleX, scaleY);
	keyScale->autorelease();
	return keyScale;
}
void oKeyScale::setValue( float endScaleX, float endScaleY )
{
	_endScaleX = endScaleX;
	_endScaleY = endScaleY;
}

void oKeyRotate::setEase( int easeId )
{
	_ease = oEase::get(easeId);
}
bool oKeyRotate::initWithDuration( float duration, float rotate )
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_endRotate = rotate;
		return true;
	}
	return false;
}
CCObject* oKeyRotate::copyWithZone( CCZone* pZone )
{
	CCZone* pNewZone = NULL;
	oKeyRotate* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		pCopy = (oKeyRotate*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oKeyRotate();
		pZone = pNewZone = new CCZone(pCopy);
	}
	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	pCopy->initWithDuration(m_fDuration, _endRotate);
	return pCopy;
}
void oKeyRotate::startWithTarget( CCNode *pTarget )
{
	CCActionInterval::startWithTarget(pTarget);
	_startRotate = pTarget->getRotation();
	_deltaRotate = _endRotate - _startRotate;
}
void oKeyRotate::update( float time )
{
	m_pTarget->setRotation(_ease(time, _startRotate, _deltaRotate));
}
oKeyRotate* oKeyRotate::create( float duration, float rotate, int easeId )
{
	oKeyRotate* keyRotate = new oKeyRotate();
	keyRotate->_ease = oEase::get(easeId);
	keyRotate->initWithDuration(duration, rotate);
	keyRotate->autorelease();
	return keyRotate;
}
void oKeyRotate::setValue( float endRotate )
{
	_endRotate = endRotate;
}

void oKeyOpacity::setEase( int easeId )
{
	_ease = oEase::get(easeId);
}
bool oKeyOpacity::initWithDuration( float duration, GLubyte opacity )
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_endOpacity = opacity;
		return true;
	}
	return false;
}
CCObject* oKeyOpacity::copyWithZone( CCZone* pZone )
{
	CCZone* pNewZone = NULL;
	oKeyOpacity* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		pCopy = (oKeyOpacity*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oKeyOpacity();
		pZone = pNewZone = new CCZone(pCopy);
	}
	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	pCopy->initWithDuration(m_fDuration, _endOpacity);
	return pCopy;
}
void oKeyOpacity::startWithTarget( CCNode *pTarget )
{
	CCActionInterval::startWithTarget(pTarget);
	_startOpacity = ((CCSprite*)pTarget)->getOpacity();
	_deltaOpacity = _endOpacity - _startOpacity;
}
void oKeyOpacity::update( float time )
{
	((CCSprite*)m_pTarget)->setOpacity(GLubyte(_ease(time, _startOpacity, _deltaOpacity)));
}
oKeyOpacity* oKeyOpacity::create( float duration, GLubyte opacity, int easeId )
{
	oKeyOpacity* keyOpacity = new oKeyOpacity();
	keyOpacity->_ease = oEase::get(easeId);
	keyOpacity->initWithDuration(duration, opacity);
	keyOpacity->autorelease();
	return keyOpacity;
}
void oKeyOpacity::setValue( GLubyte endOpacity )
{
	_endOpacity = endOpacity;
}

void oKeySkew::setEase( int easeId )
{
	_ease = oEase::get(easeId);
}
bool oKeySkew::initWithDuration( float duration, float skewX, float skewY )
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_endSkewX = skewX;
		_endSkewY = skewY;
		return true;
	}
	return false;
}
CCObject* oKeySkew::copyWithZone( CCZone* pZone )
{
	CCZone* pNewZone = NULL;
	oKeySkew* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		pCopy = (oKeySkew*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oKeySkew();
		pZone = pNewZone = new CCZone(pCopy);
	}
	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	pCopy->initWithDuration(m_fDuration, _endSkewX, _endSkewY);
	return pCopy;
}
void oKeySkew::startWithTarget( CCNode *pTarget )
{
	CCActionInterval::startWithTarget(pTarget);
	_startSkewX = pTarget->getSkewX();
	_startSkewY = pTarget->getSkewY();
	_deltaSkewX = _endSkewX - _startSkewX;
	_deltaSkewY = _endSkewY - _startSkewY;
}
void oKeySkew::update( float time )
{
	m_pTarget->setSkewX(_ease(time, _startSkewX, _deltaSkewX));
	m_pTarget->setSkewY(_ease(time, _startSkewY, _deltaSkewY));
}
oKeySkew* oKeySkew::create( float duration, float skewX, float skewY, int easeId )
{
	oKeySkew* keySkew = new oKeySkew();
	keySkew->_ease = oEase::get(easeId);
	keySkew->initWithDuration(duration, skewX, skewY);
	keySkew->autorelease();
	return keySkew;
}
void oKeySkew::setValue( float endSkewX, float endSkewY )
{
	_endSkewX = endSkewX;
	_endSkewY = endSkewY;
}

void oKeyRoll::setEase( int easeId )
{
	_ease = oEase::get(easeId);
}
bool oKeyRoll::initWithDuration( float duration, float roll )
{
	if (CCActionInterval::initWithDuration(duration))
	{
		_endRoll = roll;
		return true;
	}
	return false;
}
CCObject* oKeyRoll::copyWithZone( CCZone* pZone )
{
	CCZone* pNewZone = NULL;
	oKeyRoll* pCopy = NULL;
	if(pZone && pZone->m_pCopyObject) 
	{
		pCopy = (oKeyRoll*)(pZone->m_pCopyObject);
	}
	else
	{
		pCopy = new oKeyRoll();
		pZone = pNewZone = new CCZone(pCopy);
	}
	CCFiniteTimeAction::copyWithZone(pZone);
	CC_SAFE_DELETE(pNewZone);
	pCopy->initWithDuration(m_fDuration, _endRoll);
	return pCopy;
}
void oKeyRoll::startWithTarget( CCNode *pTarget )
{
	CCActionInterval::startWithTarget(pTarget);
	_startRoll = pTarget->getRotation();
	if (_startRoll > 0)
	{
		_startRoll = fmodf(_startRoll, 360.0f);
	}
	else
	{
		_startRoll = fmodf(_startRoll, -360.0f);
	}
	_deltaRoll = _endRoll - _startRoll;
	if (_deltaRoll > 180)
	{
		_deltaRoll -= 360;
	}
	if (_deltaRoll < -180)
	{
		_deltaRoll += 360;
	}
}
void oKeyRoll::update( float time )
{
	m_pTarget->setRotation(_ease(time, _startRoll, _deltaRoll));
}
oKeyRoll* oKeyRoll::create( float duration, float roll, int easeId )
{
	oKeyRoll* keyRoll = new oKeyRoll();
	keyRoll->_ease = oEase::get(easeId);
	keyRoll->initWithDuration(duration, roll);
	keyRoll->autorelease();
	return keyRoll;
}
void oKeyRoll::setValue( float endRoll )
{
	_endRoll = endRoll;
}

NS_DOROTHY_END
