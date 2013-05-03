#ifndef __DOROTHY_MODEL_OKEYFRAME_H__
#define __DOROTHY_MODEL_OKEYFRAME_H__

NS_DOROTHY_BEGIN

class oKeyPos: public CCActionInterval
{
public:
	void setEase(int easeId);
	void setValue(float endX, float endY);
public:
	static oKeyPos* create(float duration, float posX, float posY, int easeId = 0);
};

class oKeyScale: public CCActionInterval
{
public:
	void setEase(int easeId);
	void setValue(float endScaleX, float endScaleY);
public:
	static oKeyScale* create(float duration, float scaleX, float scaleY, int easeId = 0);
};

class oKeyRotate: public CCActionInterval
{
public:
	void setEase(int easeId);
	void setValue(float endRotate);
public:
	static oKeyRotate* create(float duration, float rotate, int easeId = 0);
};

class oKeyOpacity: public CCActionInterval
{
public:
	void setEase(int easeId);
	void setValue(GLubyte endOpacity);
public:
	static oKeyOpacity* create(float duration, GLubyte opacity, int easeId = 0);
};

class oKeySkew: public CCActionInterval
{
public:
	void setEase(int easeId);
	void setValue(float endSkewX, float endSkewY);
public:
	static oKeySkew* create(float duration, float skewX, float skewY, int easeId = 0);
};

class oKeyRoll: public CCActionInterval
{
public:
	void setEase(int easeId);
	void setValue(float endRoll);
public:
	static oKeyRoll* create(float duration, float roll, int easeId = 0);
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OKEYFRAME_H__