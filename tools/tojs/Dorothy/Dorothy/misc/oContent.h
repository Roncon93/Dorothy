#ifndef __DOROTHY_MISC_OCONTENT_H__
#define __DOROTHY_MISC_OCONTENT_H__

NS_DOROTHY_BEGIN

class oContent
{
public:
	~oContent();
	bool setGameFile(const string& filename);
	void setPassword(const string& password);
	void setUseGameFile(bool use);
	bool isUsingGameFile() const;
	CCTexture2D* loadTexture(const char* filename);
	string extractGameFile(const char* filename);
	string getExtractedName(const char* filename);
	static oContent* shared();
};

#define oSharedContent (*oContent::shared())

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OCONTENT_H__