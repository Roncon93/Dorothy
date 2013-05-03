/**
 * @module dorothy_platform
 */
var o = o || {};

/**
 * @class oCamera
 */
o.Camera = {

/**
 * @method getView
 * @return A value converted from C/C++ "cocos2d::CCSize"
 */
getView : function () {},

/**
 * @method setBoudary
 * @param {cocos2d::CCRect}
 */
setBoudary : function () {},

/**
 * @method getFollowRatio
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 */
getFollowRatio : function () {},

/**
 * @method follow
 * @param {cocos2d::CCNode*}
 */
follow : function () {},

/**
 * @method setView
 * @param {cocos2d::CCSize}
 */
setView : function () {},

/**
 * @method setFollowRatio
 * @param {cocos2d::CCPoint}
 */
setFollowRatio : function () {},

/**
 * @method getBoudary
 * @return A value converted from C/C++ "cocos2d::CCRect"
 */
getBoudary : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::Platform::oCamera*"
 */
create : function () {},

};

/**
 * @class oLayer
 */
o.Layer = {

};

/**
 * @class oPlatformWorld
 */
o.PlatformWorld = {

/**
 * @method setLayerOffset
 * @param {int}
 * @param {cocos2d::CCPoint}
 */
setLayerOffset : function () {},

/**
 * @method getUILayer
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 */
getUILayer : function () {},

/**
 * @method getCamera
 * @return A value converted from C/C++ "Dorothy::Platform::oCamera*"
 */
getCamera : function () {},

/**
 * @method setLayerRatio
 * @param {int}
 * @param {cocos2d::CCPoint}
 */
setLayerRatio : function () {},

/**
 * @method getLayer
 * @return A value converted from C/C++ "Dorothy::Platform::oLayer*"
 * @param {int}
 */
getLayer : function () {},

/**
 * @method getLayerOffset
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {int}
 */
getLayerOffset : function () {},

/**
 * @method getLayerRatio
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {int}
 */
getLayerRatio : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::Platform::oPlatformWorld*"
 */
create : function () {},

};
