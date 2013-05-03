#ifndef __DOROTHY_CONST_ODEFINE_H__
#define __DOROTHY_CONST_ODEFINE_H__

#include "cocos2d.h"
USING_NS_CC;
#include "ExtensionMacros.h"
#include "Box2D/Box2D.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <functional>
using std::function;
#include <unordered_map>
using std::unordered_map;
#include <stack>
using std::stack;
#include <memory>
#include <sstream>
using std::ostringstream;
#include <tuple>
using std::tuple;
#include "Dorothy/other/AcfDelegate.h"
using Acf::Delegate;
#include "Dorothy/other/hash_strmap.hpp"
using febird::hash_strmap;

#define NS_DOROTHY_BEGIN namespace Dorothy {
#define NS_DOROTHY_END }

NS_DOROTHY_BEGIN

#define PROPERTY(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName() const;\
public: void set##funName(varType var)

#define PROPERTY_NAME(varType, funName)\
public: varType get##funName() const;\
public: void set##funName(varType var)

#define PROPERTY_REF(varType, varName, funName)\
protected: varType varName;\
public: const varType& get##funName(void) const;\
public: void set##funName(const varType& var)

#define PROPERTY_NAME_REF(varType, funName)\
public: const varType& get##funName(void) const;\
public: void set##funName(const varType& var)

#define PROPERTY_VIRTUAL(varType, varName, funName)\
protected: varType varName;\
public: varType get##funName() const;\
public: virtual void set##funName(varType var)

#define PROPERTY_READONLY(varType, funName)\
public: varType get##funName() const

#define PROPERTY_READONLY_REF(varType, funName)\
public: const varType& get##funName(void) const

#define PROPERTY_BOOL(varName, funName)\
protected: bool varName;\
public: bool is##funName() const;\
public: void set##funName(bool var)

#define BLOCK_START do
#define BREAK_IF(cond) if(cond) break
#define BREAK_NOT(cond) if(!cond) break
#define BLOCK_END while(false);

/** @brief A more efficient switch case for strings
	@example Use it as below.

	string str = "abc";
	SWITCH_STR_START(str)
	{
		CASE_STR("Pig")
		{
			break;
		}
		CASE_STR("Dog")
		{
			break;
		}
	}
	SWITCH_STR_END
*/
size_t oFNVHash(const char* str);
inline size_t oFNVHash(const string& str) { return oFNVHash(str.c_str()); }
#define SWITCH_STR_START(x) { size_t __strHashCodeForSwitch = oFNVHash(x);string __targetStrForSwitch(x); do
#define __CASE_STR0(x, name, line) static size_t name##line = oFNVHash(x);if (__strHashCodeForSwitch == name##line && __targetStrForSwitch == x)
#define __CASE_STR1(x, line) __CASE_STR0(x, __strCase, line)
#define CASE_STR(x) __CASE_STR1(x, __LINE__)
#define SWITCH_STR_END while (false); }

#define SHARED_FUNC(name) public: static name* shared(){ static name instance;return &instance; }

NS_DOROTHY_END

#include "Dorothy/misc/oRef.h"
#include "Dorothy/misc/oRefVector.h"
#include "Dorothy/misc/oOwn.h"
#include "Dorothy/misc/oOwnVector.h"

#endif // __DOROTHY_CONST_ODEFINE_H__