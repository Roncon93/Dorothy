/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
var TAG_SPRITE = 1;


var LAYER_FRONT = 2;
var LAYER_GAME = 1;
var LAYER_BACK = 0;

var ClickAndMoveTestScene = TestScene.extend({
    runThisTest:function () {
        var layer = new MainLayer();
        this.addChild(layer);
        director.replaceScene(this);
    }
});

cc.log("got problems? 0");
var MainLayer = o.PlatformWorld.extend(
{
    ctor:function()
	{
		cc.log("**|this|**");
		for (var name in this)
		{
			cc.log(name);
		}
		cc.log("**|end|**");
        this._super();
        cc.associateWithNative(this, o.PlatformWorld);
        this.init();
        if( 'touches' in sys.capabilities )
            this.setTouchEnabled(true);
        else if ('mouse' in sys.capabilities )
            this.setMouseEnabled(true);

        var sprite = cc.Sprite.create(s_pathGrossini);

        var layer = cc.LayerColor.create(cc.c4b(255, 255, 0, 100));
        this.addChild(layer, LAYER_BACK);

        this.addChild(sprite, 0, TAG_SPRITE);
        sprite.setPosition(20, 150);

        sprite.runAction(cc.JumpTo.create(4, cc.p(300, 48), 100, 4));

        var fadeIn = cc.FadeIn.create(1);
        var fadeOut = cc.FadeOut.create(1);
        var forever = cc.RepeatForever.create(cc.Sequence.create(fadeIn, fadeOut));
        layer.runAction(forever);
		
		var model = o.Model.create("jiandunA.model");
		model.setLoop(true);
		model.setRecovery(0.2);
		model.setLook("happy");
		model.play("walk");
		model.addHandler("walk",this.onWalk)
		
		var groupOne = 1;
		this.setShouldContact(groupOne, groupOne, true);
		
		var bodyDef = o.BodyDef.create();
		bodyDef.setType(o.BODY_TYPE_DYNAMIC);
		bodyDef.attachPolygon(100, 200, 1.0, 0.4, 0.4);
		var body = bodyDef.toBody(this, groupOne, 200, 200);
		body.addChild(model, 0, 998);
		
		this.addChild(body, LAYER_GAME, 998);
		
		this.getCamera().setBoudary(cc.rect(-1000,-1000,2000,2000));
		this.getCamera().follow(body);
		this.getCamera().setFollowRatio(cc.p(0.1,0.1));
		
		//Terrain
		bodyDef = o.BodyDef.create();
		bodyDef.setType(o.BODY_TYPE_STATIC);
		bodyDef.attachChain([cc.p(0,0), cc.p(1000,0)]);
		body = bodyDef.toBody(this, groupOne, 0, 0);
		this.addChild(body);
		
		//Sensor
		var sensorTag = 1;
		bodyDef = o.BodyDef.create();
		bodyDef.setType(o.BODY_TYPE_STATIC);
		body = bodyDef.toBody(this, groupOne, 200, 0);
		var sensor = body.attachSensor(sensorTag, o.BodyDef.polygon(100, 100));
		sensor.addEnterHandler(function(){cc.log("Entered !");});
		sensor.addLeaveHandler(this.onBodyLeave);
		this.addChild(body);
		
		var sp = cc.Sprite.createWithClip("jiandunA.clip|0");
		sp.setPosition(300,200);
		sp.runAction(o.Rotate.create(1.0, 360, o.EASE_OUT_BACK));
		this.addChild(sp, LAYER_FRONT, 999);
		
		this.getLayer(LAYER_BACK).setPositionZ(-100);
		this.getLayer(LAYER_BACK).setRotationX(-25);
		this.getLayer(LAYER_BACK).setRotationY(-25);
		
		this.getLayer(LAYER_GAME).setRotationY(25);
    },
	
	onBodyEnter:function(sensor, body)
	{
		
	},
	onBodyLeave:function(sensor, body)
	{
		cc.log(sensor.getOwner()+" "+body+" Left !");
	},
	onWalk:function(model)
	{
		//cc.log("A walk!");
	},

    moveSprite:function(position) {
        var sprite = this.getChildByTag(TAG_SPRITE);
        sprite.stopAllActions();
        sprite.runAction(cc.MoveTo.create(1, position));
        var current = sprite.getPosition();
        var o = position.x - current.x;
        var a = position.y - current.y;
        var at = Math.atan(o / a) * (180/Math.PI);  // radians to degrees

        if (a < 0) {
            if (o < 0)
                at = 180 + Math.abs(at);
            else
                at = 180 - Math.abs(at);
        }
        at = at % 360;

        sprite.runAction(cc.RotateTo.create(1, at));
    },
    onMouseUp:function (event) {
        var location = event.getLocation();
        this.moveSprite(location);
    },

    onTouchesEnded:function (touches, event) {
        if (touches.length <= 0)
        {
			return;
		}
		var body = this.getChildByTag(998);
		var model = body.getChildByTag(998);
		model.play("attack1");
		model.removeHandler("walk",this.onWalk);
		body.setVelocityX(model.isFaceRight() ? -400 : 400);
		//body.setPositionY(500);
		model.setFaceRight(!model.isFaceRight());
		var sp = this.getChildByTag(999);
		if (sp)
		{
			this.removeChild(sp);
		}
		this.query(cc.rect(0,0,1000,1000),function(body){if (body.getTag() == 998) body.setVelocityY(400);return false;});
        var touch = touches[0];
        var location = touch.getLocation();
        this.moveSprite(location);
    }
});
cc.log("got problems? 1");