#ifndef __DOROTHY_MISC_ONODE3D_H__
#define __DOROTHY_MISC_ONODE3D_H__

NS_DOROTHY_BEGIN

class oNode3D: public CCNode
{
public:
	oNode3D();
	PROPERTY(float, _rotationX, RotationX);
	PROPERTY(float, _rotationY, RotationY);
	CREATE_FUNC(oNode3D);
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_ONODE3D_H__