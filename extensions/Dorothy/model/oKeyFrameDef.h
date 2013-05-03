#ifndef __DOROTHY_MODEL_OKEYFRAMEDEF_H__
#define __DOROTHY_MODEL_OKEYFRAMEDEF_H__

#include "Dorothy/model/oModelAnimationDef.h"

NS_DOROTHY_BEGIN

class oSequence;

class oKeyFrameDef
{
public:
	enum
	{
		MaxKeyAttributes = 6
	};
	oKeyFrameDef();
	int8 easePos;
	int8 easeScale;
	int8 easeOpacity;
	int8 easeRotation;
	int8 easeSkew;
	bool visible;/*1*/
	GLubyte opacity;/*2*/
	float duration;
	float x;
	float y;/*3*/
	float scaleX;
	float scaleY;/*4*/
	float rotation;/*5*/
	float skewX;
	float skewY;/*6*/
	string toXml();
};

class oKeyAnimationDef: public oModelAnimationDef
{
public:
	void add(oKeyFrameDef* def);
	virtual oActionDuration* toAction();
	virtual string toXml();
	virtual void restoreResetAnimation(CCObject* data);
private:
	oOwnVector<oKeyFrameDef> _keyFrameDefs;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OKEYFRAMEDEF_H__