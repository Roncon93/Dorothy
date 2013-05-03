#ifndef __DOROTHY_PLATFORM_OCAMERA_H__
#define __DOROTHY_PLATFORM_OCAMERA_H__

NS_DOROTHY_PLATFORM_BEGIN

class oCamera: public CCNode
{
public:
	oCamera();
	PROPERTY_REF(CCRect, _boudary, Boudary);
	PROPERTY_REF(CCSize, _view, View);
	PROPERTY_REF(CCPoint, _ratio, FollowRatio);
	void follow(CCNode* target);
	CREATE_FUNC(oCamera);
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OCAMERA_H__