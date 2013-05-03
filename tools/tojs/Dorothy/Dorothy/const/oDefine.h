#ifndef __DOROTHY_CONST_ODEFINE_H__
#define __DOROTHY_CONST_ODEFINE_H__

#include "cocos2d.h"
USING_NS_CC;
#include "Box2D/Box2D.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
//#include <functional>
//using std::function;

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

NS_DOROTHY_END

#endif // __DOROTHY_CONST_ODEFINE_H__