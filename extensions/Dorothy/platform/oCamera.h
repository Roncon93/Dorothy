#ifndef __DOROTHY_PLATFORM_OCAMERA_H__
#define __DOROTHY_PLATFORM_OCAMERA_H__

NS_DOROTHY_PLATFORM_BEGIN

typedef Delegate<void (float deltaX, float deltaY)> oCameraHandler;

class oCamera: public CCNode
{
public:
	oCamera();
	PROPERTY_REF(CCRect, _boudary, Boudary);
	PROPERTY_REF(CCSize, _view, View);
	PROPERTY_REF(CCPoint, _ratio, FollowRatio);
	virtual void setPosition(const CCPoint& var);
	virtual const CCPoint& getPosition();
	void follow(CCNode* target);
	virtual CCAffineTransform nodeToParentTransform();
	virtual CCAffineTransform nodeToGameParentTransform();
	oCameraHandler moved;
	CREATE_FUNC(oCamera);
private:
	CCPoint _camPos;
	oRef<CCNode> _target;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OCAMERA_H__