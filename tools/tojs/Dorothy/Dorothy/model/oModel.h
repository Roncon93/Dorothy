#ifndef __DOROTHY_MODEL_OMEDOL_H__
#define __DOROTHY_MODEL_OMEDOL_H__

NS_DOROTHY_BEGIN

class oModelDef;

class oModel: public CCNode
{
public:
	PROPERTY_NAME(int, Look);
	PROPERTY(float, _speed, Speed);
	PROPERTY(bool, _loop, Loop);
	PROPERTY_NAME(float, Time);
	PROPERTY_READONLY(float, Duration);
	PROPERTY(float, _recoverTime, Recovery);
	PROPERTY_BOOL(_faceRight, FaceRight);
	void setLook(const string& name);
	void play(const string& name);
	void pause();
	void resume();
	void resume(const string& name);
	void stop();
	bool isPlaying() const;
	bool isPaused() const;
	string getCurrentAnimationName() const;
	oModelDef* getModelDef() const;
	CCNode* getNodeByName(const string& name);
	static oModel* create(const char* filename);
	static oModel* none();
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMEDOL_H__