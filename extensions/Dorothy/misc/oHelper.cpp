#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oHelper.h"

NS_DOROTHY_BEGIN

void oHelper::getPosFromStr( const char* str, float& x, float& y )
{
	char temp[64];
	strcpy(temp, str);
	char* token = strtok(temp, ",");
	x = (float)atof(token);
	token = strtok(nullptr, ",");
	y = (float)atof(token);
}

NS_DOROTHY_END
