/**
 * @module dorothy
 */
var o = o || {};

/**
 * @class oNode3D
 */
o.Node3D = {

/**
 * @method setRotationY
 * @param {float}
 */
setRotationY : function () {},

/**
 * @method setRotationX
 * @param {float}
 */
setRotationX : function () {},

/**
 * @method getRotationY
 * @return A value converted from C/C++ "float"
 */
getRotationY : function () {},

/**
 * @method getRotationX
 * @return A value converted from C/C++ "float"
 */
getRotationX : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oNode3D*"
 */
create : function () {},

/**
 * @method oNode3D
 * @constructor
 */
oNode3D : function () {},

};

/**
 * @class oFrameAction
 */
o.FrameAction = {

/**
 * @method setLoop
 * @param {bool}
 */
setLoop : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oFrameAction*"
 * @param {const char*}
 */
create : function () {},

};

/**
 * @class oAnimationCache
 */
o.AnimationCache = {

/**
 * @method load
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
load : function () {},

/**
 * @method shared
 * @return A value converted from C/C++ "Dorothy::oAnimationCache*"
 */
shared : function () {},

};

/**
 * @class oClipCache
 */
o.ClipCache = {

/**
 * @method load
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
load : function () {},

/**
 * @method shared
 * @return A value converted from C/C++ "Dorothy::oClipCache*"
 */
shared : function () {},

};

/**
 * @class oKeyPos
 */
o.Pos = {

/**
 * @method setEase
 * @param {int}
 */
setEase : function () {},

/**
 * @method setValue
 * @param {float}
 * @param {float}
 */
setValue : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oKeyPos*"
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {int}
 */
create : function () {},

};

/**
 * @class oKeyScale
 */
o.Scale = {

/**
 * @method setEase
 * @param {int}
 */
setEase : function () {},

/**
 * @method setValue
 * @param {float}
 * @param {float}
 */
setValue : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oKeyScale*"
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {int}
 */
create : function () {},

};

/**
 * @class oKeyRotate
 */
o.Rotate = {

/**
 * @method setEase
 * @param {int}
 */
setEase : function () {},

/**
 * @method setValue
 * @param {float}
 */
setValue : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oKeyRotate*"
 * @param {float}
 * @param {float}
 * @param {int}
 */
create : function () {},

};

/**
 * @class oKeyOpacity
 */
o.Opacity = {

/**
 * @method setEase
 * @param {int}
 */
setEase : function () {},

/**
 * @method setValue
 * @param {unsigned char}
 */
setValue : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oKeyOpacity*"
 * @param {float}
 * @param {unsigned char}
 * @param {int}
 */
create : function () {},

};

/**
 * @class oKeySkew
 */
o.Skew = {

/**
 * @method setEase
 * @param {int}
 */
setEase : function () {},

/**
 * @method setValue
 * @param {float}
 * @param {float}
 */
setValue : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oKeySkew*"
 * @param {float}
 * @param {float}
 * @param {float}
 * @param {int}
 */
create : function () {},

};

/**
 * @class oKeyRoll
 */
o.Roll = {

/**
 * @method setEase
 * @param {int}
 */
setEase : function () {},

/**
 * @method setValue
 * @param {float}
 */
setValue : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oKeyRoll*"
 * @param {float}
 * @param {float}
 * @param {int}
 */
create : function () {},

};

/**
 * @class oModelDef
 */
o.ModelDef = {

/**
 * @method isFaceRight
 * @return A value converted from C/C++ "bool"
 */
isFaceRight : function () {},

/**
 * @method toXml
 * @return A value converted from C/C++ "std::string"
 */
toXml : function () {},

/**
 * @method getTexture
 * @return A value converted from C/C++ "cocos2d::CCTexture2D*"
 */
getTexture : function () {},

/**
 * @method getKeyPoint
 * @return A value converted from C/C++ "cocos2d::CCPoint"
 * @param {unsigned int}
 */
getKeyPoint : function () {},

/**
 * @method getAnimationIndexByName
 * @return A value converted from C/C++ "int"
 * @param {std::string}
 */
getAnimationIndexByName : function () {},

/**
 * @method getLookIndexByName
 * @return A value converted from C/C++ "int"
 * @param {std::string}
 */
getLookIndexByName : function () {},

/**
 * @method isBatchUsed
 * @return A value converted from C/C++ "bool"
 */
isBatchUsed : function () {},

/**
 * @method toModel
 * @return A value converted from C/C++ "Dorothy::oModel*"
 */
toModel : function () {},

/**
 * @method addKeyPoint
 * @param {cocos2d::CCPoint}
 */
addKeyPoint : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oModelDef*"
 */
create : function () {},

};

/**
 * @class oModel
 */
o.Model = {

/**
 * @method setRecovery
 * @param {float}
 */
setRecovery : function () {},

/**
 * @method getTime
 * @return A value converted from C/C++ "float"
 */
getTime : function () {},

/**
 * @method getModelDef
 * @return A value converted from C/C++ "Dorothy::oModelDef*"
 */
getModelDef : function () {},

/**
 * @method getNodeByName
 * @return A value converted from C/C++ "cocos2d::CCNode*"
 * @param {std::string}
 */
getNodeByName : function () {},

/**
 * @method pause
 */
pause : function () {},

/**
 * @method setFaceRight
 * @param {bool}
 */
setFaceRight : function () {},

/**
 * @method getRecovery
 * @return A value converted from C/C++ "float"
 */
getRecovery : function () {},

/**
 * @method play
 * @param {std::string}
 */
play : function () {},

/**
 * @method getLook
 * @return A value converted from C/C++ "int"
 */
getLook : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method getLoop
 * @return A value converted from C/C++ "bool"
 */
getLoop : function () {},

/**
 * @method setTime
 * @param {float}
 */
setTime : function () {},

/**
 * @method getDuration
 * @return A value converted from C/C++ "float"
 */
getDuration : function () {},

/**
 * @method isPlaying
 * @return A value converted from C/C++ "bool"
 */
isPlaying : function () {},

/**
 * @method setLoop
 * @param {bool}
 */
setLoop : function () {},

/**
 * @method isFaceRight
 * @return A value converted from C/C++ "bool"
 */
isFaceRight : function () {},

/**
 * @method getSpeed
 * @return A value converted from C/C++ "float"
 */
getSpeed : function () {},

/**
 * @method setSpeed
 * @param {float}
 */
setSpeed : function () {},

/**
 * @method isPaused
 * @return A value converted from C/C++ "bool"
 */
isPaused : function () {},

/**
 * @method getCurrentAnimationName
 * @return A value converted from C/C++ "std::string"
 */
getCurrentAnimationName : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oModel*"
 * @param {const char*}
 */
create : function () {},

/**
 * @method none
 * @return A value converted from C/C++ "Dorothy::oModel*"
 */
none : function () {},

};

/**
 * @class oModelCache
 */
o.ModelCache = {

/**
 * @method load
 * @return A value converted from C/C++ "Dorothy::oModelDef*"
 * @param {const char*}
 */
load : function () {},

/**
 * @method shared
 * @return A value converted from C/C++ "Dorothy::oModelCache*"
 */
shared : function () {},

};

/**
 * @class oFixtureDef
 */
o.FixtureDef = {

};

/**
 * @class oBodyDef
 */
o.BodyDef = {

/**
 * @method setIsBullet
 * @param {bool}
 */
setIsBullet : function () {},

/**
 * @method clearFixtures
 */
clearFixtures : function () {},

/**
 * @method toBody
 * @return A value converted from C/C++ "Dorothy::oBody*"
 * @param {Dorothy::oWorld*}
 * @param {int}
 * @param {float}
 * @param {float}
 * @param {float}
 */
toBody : function () {},

/**
 * @method attachChain
 * @param {Dorothy::b2Vec2Vector}
 * @param {float}
 * @param {float}
 */
attachChain : function () {},

/**
 * @method setGravityScale
 * @param {float}
 */
setGravityScale : function () {},

/**
 * @method attachLoop
 * @param {Dorothy::b2Vec2Vector}
 * @param {float}
 * @param {float}
 */
attachLoop : function () {},

/**
 * @method setFixedRotation
 * @param {bool}
 */
setFixedRotation : function () {},

/**
 * @method setType
 * @param {int}
 */
setType : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oBodyDef*"
 */
create : function () {},

/**
 * @method chain
 * @return A value converted from C/C++ "oFixtureDef*"
 * @param {Dorothy::b2Vec2Vector}
 * @param {float}
 * @param {float}
 */
chain : function () {},

/**
 * @method loop
 * @return A value converted from C/C++ "oFixtureDef*"
 * @param {Dorothy::b2Vec2Vector}
 * @param {float}
 * @param {float}
 */
loop : function () {},

};

/**
 * @class oBody
 */
o.Body = {

/**
 * @method attach
 * @param {oFixtureDef*}
 */
attach : function () {},

/**
 * @method setVelocityY
 * @param {float}
 */
setVelocityY : function () {},

/**
 * @method getVelocity
 * @return A value converted from C/C++ "b2Vec2"
 */
getVelocity : function () {},

/**
 * @method setVelocityX
 * @param {float}
 */
setVelocityX : function () {},

/**
 * @method setPosition
 * @param {float}
 * @param {float}
 */
setPosition : function () {},

/**
 * @method setGroup
 * @param {int}
 */
setGroup : function () {},

/**
 * @method removeSensor
 * @return A value converted from C/C++ "bool"
 * @param {Dorothy::oSensor*}
 */
removeSensor : function () {},

/**
 * @method getBodyDef
 * @return A value converted from C/C++ "Dorothy::oBodyDef*"
 */
getBodyDef : function () {},

/**
 * @method getWorld
 * @return A value converted from C/C++ "Dorothy::oWorld*"
 */
getWorld : function () {},

/**
 * @method getSensorByTag
 * @return A value converted from C/C++ "Dorothy::oSensor*"
 * @param {unsigned int}
 */
getSensorByTag : function () {},

/**
 * @method getVelocityY
 * @return A value converted from C/C++ "float"
 */
getVelocityY : function () {},

/**
 * @method getVelocityX
 * @return A value converted from C/C++ "float"
 */
getVelocityX : function () {},

/**
 * @method removeSensorByTag
 * @return A value converted from C/C++ "bool"
 * @param {unsigned int}
 */
removeSensorByTag : function () {},

/**
 * @method getGroup
 * @return A value converted from C/C++ "int"
 */
getGroup : function () {},

/**
 * @method attachSensor
 * @return A value converted from C/C++ "Dorothy::oSensor*"
 * @param {int}
 * @param {oFixtureDef*}
 */
attachSensor : function () {},

};

/**
 * @class oSensor
 */
o.Sensor = {

/**
 * @method getEnable
 * @return A value converted from C/C++ "bool"
 */
getEnable : function () {},

/**
 * @method contains
 * @return A value converted from C/C++ "bool"
 * @param {Dorothy::oBody*}
 */
contains : function () {},

/**
 * @method setEnable
 * @param {bool}
 */
setEnable : function () {},

/**
 * @method getOwner
 * @return A value converted from C/C++ "Dorothy::oBody*"
 */
getOwner : function () {},

/**
 * @method sensed
 * @return A value converted from C/C++ "bool"
 */
sensed : function () {},

/**
 * @method getTag
 * @return A value converted from C/C++ "int"
 */
getTag : function () {},

};

/**
 * @class oWorld
 */
o.World = {

/**
 * @method setGravity
 * @param {b2Vec2}
 */
setGravity : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "Dorothy::oWorld*"
 */
create : function () {},

/**
 * @method getShouldContact
 * @return A value converted from C/C++ "bool"
 * @param {int}
 * @param {int}
 */
getShouldContact : function () {},

/**
 * @method setIterations
 * @param {int}
 * @param {int}
 */
setIterations : function () {},

/**
 * @method getGravity
 * @return A value converted from C/C++ "b2Vec2"
 */
getGravity : function () {},

/**
 * @method setShouldContact
 * @param {int}
 * @param {int}
 * @param {bool}
 */
setShouldContact : function () {},

/**
 * @method oWorld
 * @constructor
 */
oWorld : function () {},

};
