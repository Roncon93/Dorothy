\#include "${out_file}.hpp"
\#include "cocos2d_specifics.hpp"
#for header in $headers
\#include "${os.path.basename(header)}"
#end for

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));
	if (ccIsInitializingClass())
	{
		return JS_TRUE;
	}
	T* cobj = new T();
#if not $script_control_cpp
	cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
	if (_ccobj) {
		_ccobj->autorelease();
	}
#end if
	js_proxy_t *pp;
	JS_NEW_PROXY(pp, cobj, _tmp);
#if not $script_control_cpp
	JS_AddObjectRoot(cx, &pp->obj);
#end if
	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}

