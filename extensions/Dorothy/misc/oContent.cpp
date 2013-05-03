#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oContent.h"

NS_DOROTHY_BEGIN

oContent::oContent():
_isUsingGameFile(false),
_writablePath(std::move(CCFileUtils::sharedFileUtils()->getWritablePath()))
{ }

oContent::~oContent()
{
	if (ccUZipIsOpened())
	{
		ccUZipClose();
	}
}

CCTexture2D* oContent::loadTexture( const char* filename )
{
	if (_isUsingGameFile)
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey(filename);
		if (!texture)
		{
			unsigned long size;
			unsigned char* buffer = ccUZipReadFile(
				filename,
				_password.empty() ? nullptr : _password.c_str(),
				size);
			CCImage* image = new CCImage();
			image->initWithImageData(buffer, size);
			texture = CCTextureCache::sharedTextureCache()->addUIImage(image, filename);
			delete image;
			delete buffer;
		}
		return texture;
	}
	else
	{
		CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(filename);
		return texture;
	}
}

char* oContent::loadFile( const char* filename, unsigned long& size )
{
	if (_isUsingGameFile)
	{
		char* buffer = (char*)ccUZipReadFile(
			filename,
			_password.empty() ? nullptr : _password.c_str(),
			size);
		return buffer;
	}
	else
	{
		char* buffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(filename, "rt", &size);
		return buffer;
	}
}

bool oContent::setGameFile(const string& var)
{
	_gameFileName = _writablePath + var;
	if (ccUZipIsOpened())
	{
		ccUZipClose();
	}
	if (!ccUZipOpen(_gameFileName.c_str()))
	{
		_gameFileName.clear();
		return false;
	}
	return true;
}

void oContent::setUseGameFile(bool use)
{
	_isUsingGameFile = use;
}

bool oContent::isUsingGameFile() const
{
	return _isUsingGameFile;
}

void oContent::setPassword( const string& password )
{
	_password = password;
}

string oContent::extractGameFile( const char* filename )
{
	if (!_gameFileName.empty())
	{
		string targetName = oContent::getExtractedName(filename);
		ccUZipExtract(
			filename,
			_password.empty() ? nullptr : _password.c_str(),
			targetName.c_str());
		return targetName;
	}
	return string();
}

string oContent::getExtractedName( const char* filename )
{
	string file(filename);
	int index = file.find_last_of('.');
	string targetName = _writablePath + file.substr(0, index) + ".tmp";
	return targetName;
}

NS_DOROTHY_END
