#ifndef __DOROTHY_MODEL_OMEDOLDEF_H__
#define __DOROTHY_MODEL_OMEDOLDEF_H__

NS_DOROTHY_BEGIN

class oModel;

/** @brief Data define for a 2D model. */
class oModelDef: public CCObject
{
public:
	CCTexture2D* getTexture();
	//oSpriteDef* getRoot();
	void addKeyPoint(const CCPoint& point);
	const CCPoint& getKeyPoint(uint32 index) const;
	bool isFaceRight() const;
	bool isBatchUsed() const;
	int getAnimationIndexByName(const string& name);
	int getLookIndexByName(const string& name);
	oModel* toModel();
	string toXml();
	static oModelDef* create();
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMEDOLDEF_H__