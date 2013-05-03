#ifndef __dorothy_h__
#define __dorothy_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_oNode3D_class;
extern JSObject *jsb_oNode3D_prototype;

JSBool js_dorothy_oNode3D_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oNode3D_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oNode3D(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oNode3D_setRotationY(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oNode3D_setRotationX(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oNode3D_getRotationY(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oNode3D_getRotationX(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oNode3D_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oNode3D_oNode3D(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oFrameAction_class;
extern JSObject *jsb_oFrameAction_prototype;

JSBool js_dorothy_oFrameAction_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oFrameAction_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oFrameAction(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oFrameAction_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oFrameAction_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oAnimationCache_class;
extern JSObject *jsb_oAnimationCache_prototype;

JSBool js_dorothy_oAnimationCache_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oAnimationCache_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oAnimationCache(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oAnimationCache_load(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oAnimationCache_unload(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oAnimationCache_shared(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oClipCache_class;
extern JSObject *jsb_oClipCache_prototype;

JSBool js_dorothy_oClipCache_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oClipCache_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oClipCache(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oClipCache_load(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oClipCache_unload(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oClipCache_shared(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oKeyPos_class;
extern JSObject *jsb_oKeyPos_prototype;

JSBool js_dorothy_oKeyPos_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oKeyPos_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oKeyPos(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oKeyPos_setEase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyPos_setValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyPos_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oKeyScale_class;
extern JSObject *jsb_oKeyScale_prototype;

JSBool js_dorothy_oKeyScale_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oKeyScale_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oKeyScale(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oKeyScale_setEase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyScale_setValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyScale_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oKeyRotate_class;
extern JSObject *jsb_oKeyRotate_prototype;

JSBool js_dorothy_oKeyRotate_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oKeyRotate_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oKeyRotate(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oKeyRotate_setEase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyRotate_setValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyRotate_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oKeyOpacity_class;
extern JSObject *jsb_oKeyOpacity_prototype;

JSBool js_dorothy_oKeyOpacity_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oKeyOpacity_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oKeyOpacity(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oKeyOpacity_setEase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyOpacity_setValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyOpacity_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oKeySkew_class;
extern JSObject *jsb_oKeySkew_prototype;

JSBool js_dorothy_oKeySkew_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oKeySkew_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oKeySkew(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oKeySkew_setEase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeySkew_setValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeySkew_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oKeyRoll_class;
extern JSObject *jsb_oKeyRoll_prototype;

JSBool js_dorothy_oKeyRoll_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oKeyRoll_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oKeyRoll(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oKeyRoll_setEase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyRoll_setValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oKeyRoll_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oModelDef_class;
extern JSObject *jsb_oModelDef_prototype;

JSBool js_dorothy_oModelDef_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oModelDef_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oModelDef(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oModelDef_isFaceRight(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_toXml(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_getTexture(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_getKeyPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_getAnimationIndexByName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_getLookIndexByName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_isBatchUsed(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_toModel(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_addKeyPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelDef_create(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oModel_class;
extern JSObject *jsb_oModel_prototype;

JSBool js_dorothy_oModel_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oModel_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oModel(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oModel_setRecovery(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getTime(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getModelDef(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getNodeByName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_pause(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_setFaceRight(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getRecovery(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_play(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_setLook(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_resume(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getLook(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_stop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getLoop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_setTime(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getDuration(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_isPlaying(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_setLoop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_isFaceRight(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getSpeed(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_setSpeed(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_isPaused(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_getCurrentAnimationName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModel_none(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oModelCache_class;
extern JSObject *jsb_oModelCache_prototype;

JSBool js_dorothy_oModelCache_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oModelCache_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oModelCache(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oModelCache_load(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelCache_unload(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oModelCache_shared(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oFixtureDef_class;
extern JSObject *jsb_oFixtureDef_prototype;

JSBool js_dorothy_oFixtureDef_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oFixtureDef_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oFixtureDef(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);

extern JSClass  *jsb_oBodyDef_class;
extern JSObject *jsb_oBodyDef_prototype;

JSBool js_dorothy_oBodyDef_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oBodyDef_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oBodyDef(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oBodyDef_setIsBullet(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_clearFixtures(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_toBody(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_attachChain(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_setGravityScale(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_attachPolygon(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_attachCircleSensor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_attachLoop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_setFixedRotation(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_attachCircle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_attachPolygonSensor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_setType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_circle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_chain(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_polygon(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBodyDef_loop(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oBody_class;
extern JSObject *jsb_oBody_prototype;

JSBool js_dorothy_oBody_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oBody_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oBody(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oBody_attach(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_setVelocityY(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_getVelocity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_setVelocityX(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_setPosition(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_setGroup(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_removeSensor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_getBodyDef(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_getWorld(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_getSensorByTag(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_getVelocityY(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_getVelocityX(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_removeSensorByTag(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_setVelocity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_getGroup(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oBody_attachSensor(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oSensor_class;
extern JSObject *jsb_oSensor_prototype;

JSBool js_dorothy_oSensor_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oSensor_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oSensor(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oSensor_getEnable(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oSensor_contains(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oSensor_setEnable(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oSensor_getOwner(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oSensor_sensed(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oSensor_getTag(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_oWorld_class;
extern JSObject *jsb_oWorld_prototype;

JSBool js_dorothy_oWorld_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_dorothy_oWorld_finalize(JSContext *cx, JSObject *obj);
void js_register_dorothy_oWorld(JSContext *cx, JSObject *global);
void register_all_dorothy(JSContext* cx, JSObject* obj);
JSBool js_dorothy_oWorld_setGravity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oWorld_create(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oWorld_getShouldContact(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oWorld_setIterations(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oWorld_getGravity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oWorld_setShouldContact(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_dorothy_oWorld_oWorld(JSContext *cx, uint32_t argc, jsval *vp);
#endif

