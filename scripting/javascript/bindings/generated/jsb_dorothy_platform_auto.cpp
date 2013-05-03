#include "jsb_dorothy_platform_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "Dorothy.h"

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
	cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
	if (_ccobj) {
		_ccobj->autorelease();
	}
	js_proxy_t *pp;
	JS_NEW_PROXY(pp, cobj, _tmp);
	JS_AddObjectRoot(cx, &pp->obj);
	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *jsb_oCamera_class;
JSObject *jsb_oCamera_prototype;

JSBool js_dorothy_platform_oCamera_getView(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oCamera* cobj = (Dorothy::Platform::oCamera *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCSize ret = cobj->getView();
		jsval jsret;
		jsret = ccsize_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oCamera_setBoudary(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oCamera* cobj = (Dorothy::Platform::oCamera *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCRect arg0;
		ok &= jsval_to_ccrect(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setBoudary(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oCamera_getFollowRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oCamera* cobj = (Dorothy::Platform::oCamera *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCPoint ret = cobj->getFollowRatio();
		jsval jsret;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oCamera_follow(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oCamera* cobj = (Dorothy::Platform::oCamera *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCNode* arg0;
		do {
			js_proxy_t *proxy;
			JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
			JS_GET_NATIVE_PROXY(proxy, tmpObj);
			arg0 = (cocos2d::CCNode*)(proxy ? proxy->ptr : NULL);
			JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
		} while (0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->follow(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oCamera_setView(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oCamera* cobj = (Dorothy::Platform::oCamera *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCSize arg0;
		ok &= jsval_to_ccsize(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setView(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oCamera_setFollowRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oCamera* cobj = (Dorothy::Platform::oCamera *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		cocos2d::CCPoint arg0;
		ok &= jsval_to_ccpoint(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setFollowRatio(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oCamera_getBoudary(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oCamera* cobj = (Dorothy::Platform::oCamera *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCRect ret = cobj->getBoudary();
		jsval jsret;
		jsret = ccrect_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oCamera_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		Dorothy::Platform::oCamera* ret = Dorothy::Platform::oCamera::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<Dorothy::Platform::oCamera>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}



extern JSObject *jsb_CCNode_prototype;

void js_dorothy_platform_oCamera_finalize(JSFreeOp *fop, JSObject *obj) {
}

void js_register_dorothy_platform_oCamera(JSContext *cx, JSObject *global) {
	jsb_oCamera_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_oCamera_class->name = "Camera";
	jsb_oCamera_class->addProperty = JS_PropertyStub;
	jsb_oCamera_class->delProperty = JS_PropertyStub;
	jsb_oCamera_class->getProperty = JS_PropertyStub;
	jsb_oCamera_class->setProperty = JS_StrictPropertyStub;
	jsb_oCamera_class->enumerate = JS_EnumerateStub;
	jsb_oCamera_class->resolve = JS_ResolveStub;
	jsb_oCamera_class->convert = JS_ConvertStub;
	jsb_oCamera_class->finalize = js_dorothy_platform_oCamera_finalize;
	jsb_oCamera_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getView", js_dorothy_platform_oCamera_getView, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setBoudary", js_dorothy_platform_oCamera_setBoudary, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getFollowRatio", js_dorothy_platform_oCamera_getFollowRatio, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("follow", js_dorothy_platform_oCamera_follow, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setView", js_dorothy_platform_oCamera_setView, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setFollowRatio", js_dorothy_platform_oCamera_setFollowRatio, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getBoudary", js_dorothy_platform_oCamera_getBoudary, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_dorothy_platform_oCamera_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_oCamera_prototype = JS_InitClass(
		cx, global,
		jsb_CCNode_prototype,
		jsb_oCamera_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Camera", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Dorothy::Platform::oCamera> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_oCamera_class;
		p->proto = jsb_oCamera_prototype;
		p->parentProto = jsb_CCNode_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_oLayer_class;
JSObject *jsb_oLayer_prototype;



extern JSObject *jsb_oNode3D_prototype;

void js_dorothy_platform_oLayer_finalize(JSFreeOp *fop, JSObject *obj) {
}

void js_register_dorothy_platform_oLayer(JSContext *cx, JSObject *global) {
	jsb_oLayer_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_oLayer_class->name = "Layer";
	jsb_oLayer_class->addProperty = JS_PropertyStub;
	jsb_oLayer_class->delProperty = JS_PropertyStub;
	jsb_oLayer_class->getProperty = JS_PropertyStub;
	jsb_oLayer_class->setProperty = JS_StrictPropertyStub;
	jsb_oLayer_class->enumerate = JS_EnumerateStub;
	jsb_oLayer_class->resolve = JS_ResolveStub;
	jsb_oLayer_class->convert = JS_ConvertStub;
	jsb_oLayer_class->finalize = js_dorothy_platform_oLayer_finalize;
	jsb_oLayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	JSFunctionSpec *funcs = NULL;

	JSFunctionSpec *st_funcs = NULL;

	jsb_oLayer_prototype = JS_InitClass(
		cx, global,
		jsb_oNode3D_prototype,
		jsb_oLayer_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "Layer", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Dorothy::Platform::oLayer> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_oLayer_class;
		p->proto = jsb_oLayer_prototype;
		p->parentProto = jsb_oNode3D_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_oPlatformWorld_class;
JSObject *jsb_oPlatformWorld_prototype;

JSBool js_dorothy_platform_oPlatformWorld_setLayerOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oPlatformWorld* cobj = (Dorothy::Platform::oPlatformWorld *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		cocos2d::CCPoint arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setLayerOffset(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oPlatformWorld_clearLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Dorothy::Platform::oPlatformWorld* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	cobj = (Dorothy::Platform::oPlatformWorld *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 0) {
			cobj->clearLayer();
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->clearLayer(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_dorothy_platform_oPlatformWorld_getUILayer(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oPlatformWorld* cobj = (Dorothy::Platform::oPlatformWorld *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cocos2d::CCNode* ret = cobj->getUILayer();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CCNode>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oPlatformWorld_getCamera(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oPlatformWorld* cobj = (Dorothy::Platform::oPlatformWorld *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		Dorothy::Platform::oCamera* ret = cobj->getCamera();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<Dorothy::Platform::oCamera>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oPlatformWorld_setLayerRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oPlatformWorld* cobj = (Dorothy::Platform::oPlatformWorld *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		cocos2d::CCPoint arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= jsval_to_ccpoint(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setLayerRatio(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oPlatformWorld_getLayer(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oPlatformWorld* cobj = (Dorothy::Platform::oPlatformWorld *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		Dorothy::Platform::oLayer* ret = cobj->getLayer(arg0);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<Dorothy::Platform::oLayer>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oPlatformWorld_getLayerOffset(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oPlatformWorld* cobj = (Dorothy::Platform::oPlatformWorld *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::CCPoint ret = cobj->getLayerOffset(arg0);
		jsval jsret;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oPlatformWorld_getLayerRatio(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy; JS_GET_NATIVE_PROXY(proxy, obj);
	Dorothy::Platform::oPlatformWorld* cobj = (Dorothy::Platform::oPlatformWorld *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cocos2d::CCPoint ret = cobj->getLayerRatio(arg0);
		jsval jsret;
		jsret = ccpoint_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_dorothy_platform_oPlatformWorld_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		Dorothy::Platform::oPlatformWorld* ret = Dorothy::Platform::oPlatformWorld::create();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<Dorothy::Platform::oPlatformWorld>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}



extern JSObject *jsb_oWorld_prototype;

void js_dorothy_platform_oPlatformWorld_finalize(JSFreeOp *fop, JSObject *obj) {
}

void js_register_dorothy_platform_oPlatformWorld(JSContext *cx, JSObject *global) {
	jsb_oPlatformWorld_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_oPlatformWorld_class->name = "PlatformWorld";
	jsb_oPlatformWorld_class->addProperty = JS_PropertyStub;
	jsb_oPlatformWorld_class->delProperty = JS_PropertyStub;
	jsb_oPlatformWorld_class->getProperty = JS_PropertyStub;
	jsb_oPlatformWorld_class->setProperty = JS_StrictPropertyStub;
	jsb_oPlatformWorld_class->enumerate = JS_EnumerateStub;
	jsb_oPlatformWorld_class->resolve = JS_ResolveStub;
	jsb_oPlatformWorld_class->convert = JS_ConvertStub;
	jsb_oPlatformWorld_class->finalize = js_dorothy_platform_oPlatformWorld_finalize;
	jsb_oPlatformWorld_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("setLayerOffset", js_dorothy_platform_oPlatformWorld_setLayerOffset, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("clearLayer", js_dorothy_platform_oPlatformWorld_clearLayer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getUILayer", js_dorothy_platform_oPlatformWorld_getUILayer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCamera", js_dorothy_platform_oPlatformWorld_getCamera, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setLayerRatio", js_dorothy_platform_oPlatformWorld_setLayerRatio, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getLayer", js_dorothy_platform_oPlatformWorld_getLayer, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getLayerOffset", js_dorothy_platform_oPlatformWorld_getLayerOffset, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getLayerRatio", js_dorothy_platform_oPlatformWorld_getLayerRatio, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("create", js_dorothy_platform_oPlatformWorld_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_oPlatformWorld_prototype = JS_InitClass(
		cx, global,
		jsb_oWorld_prototype,
		jsb_oPlatformWorld_class,
		dummy_constructor<Dorothy::Platform::oPlatformWorld>, 0, // no constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PlatformWorld", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Dorothy::Platform::oPlatformWorld> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_oPlatformWorld_class;
		p->proto = jsb_oPlatformWorld_prototype;
		p->parentProto = jsb_oWorld_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_dorothy_platform(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "o", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "o", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_dorothy_platform_oPlatformWorld(cx, obj);
	js_register_dorothy_platform_oCamera(cx, obj);
	js_register_dorothy_platform_oLayer(cx, obj);
}

