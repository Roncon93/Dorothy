#ifndef __dorothy_platform_h__
#define __dorothy_platform_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_oCamera_class;
extern JSObject *jsb_oCamera_prototype;

JSBool js_dorothy_platform_oCamera_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_platform_oCamera_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_platform_oCamera(JSContext *cx, JSObject *global);
void register_all_dorothy_platform(JSContext* cx, JSObject* obj);
JSBool js_dorothy_platform_oCamera_getView(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oCamera_setBoudary(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oCamera_getFollowRatio(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oCamera_follow(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oCamera_setView(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oCamera_setFollowRatio(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oCamera_getBoudary(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oCamera_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oLayer_class;
extern JSObject *jsb_oLayer_prototype;

JSBool js_dorothy_platform_oLayer_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_platform_oLayer_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_platform_oLayer(JSContext *cx, JSObject *global);
void register_all_dorothy_platform(JSContext* cx, JSObject* obj);

extern JSClass  *jsb_oPlatformWorld_class;
extern JSObject *jsb_oPlatformWorld_prototype;

JSBool js_dorothy_platform_oPlatformWorld_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_platform_oPlatformWorld_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_platform_oPlatformWorld(JSContext *cx, JSObject *global);
void register_all_dorothy_platform(JSContext* cx, JSObject* obj);
JSBool js_dorothy_platform_oPlatformWorld_setLayerOffset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oPlatformWorld_clearLayer(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oPlatformWorld_getUILayer(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oPlatformWorld_getCamera(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oPlatformWorld_setLayerRatio(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oPlatformWorld_getLayer(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oPlatformWorld_getLayerOffset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oPlatformWorld_getLayerRatio(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_platform_oPlatformWorld_create(JSContext *cx, uint32_t argc, jsval *vp);
#endif

