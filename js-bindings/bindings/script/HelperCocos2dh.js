require("HelperDate.js");
require("HelperString.js");

var cch = cch || {};

cch.classof = function(obj) {
    if (obj === null) {
        return "Null";
    }
    var t = typeof(obj);
    if (t === "string") {
        return "String";
    } else if (t === "number") {
        return "Number";
    }
    if (obj && obj.constructor && obj.constructor.toString) {
        var arr = obj.constructor.toString().match(/function\s*(\w+)/);
        if (arr && arr.length === 2) {
            return arr[1];
        }
    }
    return undefined;
};

cch.countof = function(obj) {
    if (obj && typeof(obj) === "object") {
        if (obj.hasOwnProperty("__count__")) {
            return obj.__count__;
        } else {
            var count = 0;
            for (var i in obj) {
                if (obj.hasOwnProperty(i)) {
                    ++count;
                }
            }
            return count;
        }
    }
    return undefined;
};

cch.dealloc = function(INobj) {
    if (INobj && typeof(INobj.dealloc) === "function") {
        INobj.dealloc();
    }
};

cch.instanceFunc = function(INclass) {
    var mm = null;
    INclass.getInstance = function() {
        if (mm === null) {
            mm = new INclass();
        }
        return mm;
    };
    INclass.destroyInstance = function() {
        cch.dealloc(mm);
        mm = null;
    };
};

cch.propertyFunc = function(INclass, INvarName, readonly, setter, getter) {
    var funcName = null;
    if (!readonly) {
        if (setter) {
            INclass.prototype[setter] = function(INvar) {
                this[INvarName] = INvar;
            };
        } else {
            funcName = INvarName;
            if (INvarName.indexOf("_") === 0) {
                funcName = INvarName.substring(1);
            }
            funcName = "set" + cch.stringInitialsToUpper(funcName);
            INclass.prototype[funcName] = function(INvar) {
                this[INvarName] = INvar;
            };
        }
    }

    if (getter) {
        INclass.prototype[getter] = function() {
            return this[INvarName];
        };
    } else {
        funcName = INvarName;
        if (INvarName.indexOf("_") === 0) {
            funcName = INvarName.substring(1);
        }
        funcName = "get" + cch.stringInitialsToUpper(funcName);
        INclass.prototype[funcName] = function() {
            return this[INvarName];
        };
    }
};

cch.createEnum = function(INarrayString, INstart, OUTret) {
    var ret = OUTret || {};
    for (var i = 0; i < INarrayString.length; ++i) {
        var key = INarrayString[i];
        ret[key] = i + INstart;
    }
    return ret;
};

cch.toI = function(value) {
    return parseInt(value, 10);
};

cch.toA = function(value) {
    if (typeof(value) === "string") {
        return value;
    } else {
        return JSON.stringify(value);
    }
};

cch.toIA = function(value) {
    return parseInt(value, 10).toString();
};

cch.toF = function(value) {
    return parseFloat(value);
};

cch.log = function(msg, logFile) {
    msg = cch.toA(msg);
    var str = "";
    var err = new Error(msg);
    var stackArr = err.stack.split("\n");
    stackArr.shift();
    var stack = stackArr.join("\n");
    str = "-----STACK-----:";
    str += "\n" + stack;
    str += "\n----MESSAGE----:\n";
    str += msg;
    cc.log(str);
    if (logFile) {
        cch.logFile(str);
    }
};

cch.assert = function(condition, msg, logFile) {
    if (condition) {
        return;
    }
    msg = cch.toA(msg);
    var err = new Error(msg);
    var stackArr = err.stack.split("\n");
    stackArr.shift();
    var stack = stackArr.join("\n");
    var str = "-----STACK-----:";
    str += "\n" + stack;
    cc.log(str);
    if (logFile) {
        cch.logFile(str);
    }
    throw err;
};

cch.createEventLayer = function(rootController, arrArg) {
    if (rootController.eventLayer) {
        return;
    }
    var t = {};
    t.event = cc.EventListener.TOUCH_ONE_BY_ONE;
    if (arrArg && typeof(arrArg.swallowTouches) !== "undefined") {
        t.swallowTouches = arrArg.swallowTouches;
    } else {
        t.swallowTouches = true;
    }
    
    t.onTouchBegan = function(touch, event) {
        if (rootController.onTouchBegan) {
            var node = rootController.rootNode;
            while (node) {
                if (!node.isVisible()) {
                    return false;
                }
                node = node.getParent();
            }
            return rootController.onTouchBegan(touch, event);
        }
        cch.assert(false, "You should define onTouchBegan function");
        return false;
    };
    t.onTouchMoved = function(touch, event) {
        if (rootController.onTouchMoved) {
            rootController.onTouchMoved(touch, event);
        }
    };
    t.onTouchEnded = function(touch, event) {
        if (rootController.onTouchEnded) {
            rootController.onTouchEnded(touch, event);
        }
    };
    t.onTouchCancelled = function(touch, event) {
        if (rootController.onTouchCancelled) {
            rootController.onTouchCancelled(touch, event);
        }
    };
    var listener = cc.EventListener.create(t);
    cc.eventManager.addListener(listener, rootController.rootNode);
    rootController.eventLayer = listener;
};

cch.removeEventLayer = function(rootController) {
    if (rootController && rootController.eventLayer) {
        cc.eventManager.removeListener(rootController.eventLayer);
    }
};

cc.REPEAT_FOREVER = 0xfffffffe;
cch.setInterval = function(selector, target, duration) {
    var args;
    if (arguments.length > 3) {
        args = Array.prototype.slice.call(arguments, 3);
    }
    return setInterval(function() {
        selector.apply(target, args);
    }, duration);
};

cch.setTimeout = function(selector, target, duration) {
    var args;
    if (arguments.length > 3) {
        args = Array.prototype.slice.call(arguments, 3);
    }
    return setTimeout(function() {
        selector.apply(target, args);
    }, duration);
};

cch.clearAllInterval = function() {
    var arr = Object.keys(_windowTimeFunHash);
    for (var i = 0; i < arr.length; ++i) {
        clearInterval(arr[i]);
    }
    _windowTimeIntervalId = 0;
    _windowTimeFunHash = {};
};

cch.getShaderGray = function(mvp) {
    var shaderName = "ShaderProgramCustom_Gray";
    if (mvp) {
        shaderName += "_Scale9Sprite";
    } else {
        shaderName += "_Sprite";
    }
    var program = cc.shaderCache.getProgram(shaderName);
    if (program) {
        return program;
    }
    var srcV;
    var srcF =
    "#ifdef GL_ES \n" +
    "precision mediump float; \n" +
    "#endif \n" +
    // "uniform sampler2D CC_Texture0; \n" +
    "varying vec2 v_texCoord; \n" +
    "varying vec4 v_fragmentColor; \n" +
    "void main(void) \n" +
    "{ \n" +
    "// Convert to grayscale using NTSC weightings \n" +
    "vec4 col = texture2D(CC_Texture0, v_texCoord); \n" +
    "float gray = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n" +
    "gl_FragColor = vec4(gray, gray, gray, col.a); \n" +
    "}";
    if (mvp) {
        srcV =
        "attribute vec4 a_position;" +
        "attribute vec2 a_texCoord;" +
        "attribute vec4 a_color;" +
        "\n" +
        "\n#ifdef GL_ES\n" +
        "varying lowp vec4 v_fragmentColor;" +
        "varying mediump vec2 v_texCoord;" +
        "\n#else\n" +
        "    varying vec4 v_fragmentColor;" +
        "varying vec2 v_texCoord;" +
        "\n#endif\n" +
        "\n" +
        "void main()" +
        "{" +
        "    gl_Position = CC_MVPMatrix * a_position;" +
        "    v_fragmentColor = a_color;" +
        "    v_texCoord = a_texCoord;" +
        "}";
    } else {
        srcV =
        "attribute vec4 a_position;" +
        "attribute vec2 a_texCoord;" +
        "attribute vec4 a_color;" +
        "\n" +
        "\n#ifdef GL_ES\n" +
        "varying lowp vec4 v_fragmentColor;" +
        "varying mediump vec2 v_texCoord;" +
        "\n#else\n" +
        "    varying vec4 v_fragmentColor;" +
        "varying vec2 v_texCoord;" +
        "\n#endif\n" +
        "\n" +
        "void main()" +
        "{" +
        "    gl_Position = CC_PMatrix * a_position;" +
        "    v_fragmentColor = a_color;" +
        "    v_texCoord = a_texCoord;" +
        "}";
    }
    program = cc.GLProgram.createWithString(srcV, srcF);
    program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
    program.addAttribute(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR);
    program.addAttribute(cc.ATTRIBUTE_NAME_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
    program.link();
    program.updateUniforms();
    cc.shaderCache.addProgram(program, shaderName);
    return program;
};

cch.getScale9SpriteBatchNode = function(sprite) {
    var children = sprite.getChildren();
    for (var i = 0; i < children.length; ++i) {
        if (children[i] instanceof cc.SpriteBatchNode) {
            return children[i];
        }
    }
    return null;
};

cc.BuilderReader.registerController = function(controllerName, controller){
    cc.BuilderReader._controllerClassCache[controllerName] = controller;//cc.Class.extend(controller);
};
cc.BuilderReader.load = function(file, owner, parentSize)
{
    // Load the node graph using the correct function
    var reader = cc._Reader.create();
    reader.setCCBRootPath(cc.BuilderReader._resourcePath);
    
    var node;
    
    if (parentSize)
    {
        node = reader.load(file, null, parentSize);
    }
    else
    {
        node = reader.load(file);
    }
    
    // Assign owner callbacks & member variables
    if (owner)
    {
        // Callbacks
        var ownerCallbackNames = reader.getOwnerCallbackNames();
        var ownerCallbackNodes = reader.getOwnerCallbackNodes();
        
        for (var i = 0; i < ownerCallbackNames.length; i++)
        {
            var callbackName = ownerCallbackNames[i];
            var callbackNode = ownerCallbackNodes[i];
            
            if (owner[callbackName] === undefined)
            {
                cc.log("Warning: " + "owner." + callbackName + " is undefined.");
            }
            else
            {
                if(callbackNode instanceof cc.ControlButton)
                {
                    var ownerCallbackControlEvents = reader.getOwnerCallbackControlEvents();
                    callbackNode.addTargetWithActionForControlEvents(owner, owner[callbackName], ownerCallbackControlEvents[i]);
                }
                else
                {
                    callbackNode.setCallback(owner[callbackName], owner);
                }
            }
        }
        
        // Variables
        var ownerOutletNames = reader.getOwnerOutletNames();
        var ownerOutletNodes = reader.getOwnerOutletNodes();
        
        for (var i = 0; i < ownerOutletNames.length; i++)
        {
            var outletName = ownerOutletNames[i];
            var outletNode = ownerOutletNodes[i];
            
            owner[outletName] = outletNode;
        }
    }
    
    var nodesWithAnimationManagers = reader.getNodesWithAnimationManagers();
    var animationManagersForNodes = reader.getAnimationManagersForNodes();
    
    var controllerClassCache = cc.BuilderReader._controllerClassCache;
    // Attach animation managers to nodes and assign root node callbacks and member variables
    for (var i = 0; i < nodesWithAnimationManagers.length; i++)
    {
        var innerNode = nodesWithAnimationManagers[i];
        var animationManager = animationManagersForNodes[i];
        
        innerNode.animationManager = animationManager;
        
        var controllerName = animationManager.getDocumentControllerName();
        if (!controllerName) continue;
        
        // Create a controller
        var controllerClass = controllerClassCache[controllerName];
        if(!controllerClass) throw "Can not find controller : " + controllerName;
        var controller = new controllerClass();
        controller.controllerName = controllerName;
        
        innerNode.controller = controller;
        controller.rootNode = innerNode;
        
        // Callbacks
        var documentCallbackNames = animationManager.getDocumentCallbackNames();
        var documentCallbackNodes = animationManager.getDocumentCallbackNodes();
        
        var arrCallbackName = [];
        
        for (var j = 0; j < documentCallbackNames.length; j++)
        {
            var callbackName = documentCallbackNames[j];
            var callbackNode = documentCallbackNodes[j];
            
            if (controller[callbackName] === undefined)
            {
                cc.log("Warning: " + controllerName + "." + callbackName + " is undefined.");
            }
            else
            {
                if(callbackNode instanceof cc.ControlButton)
                {
                    var documentCallbackControlEvents = animationManager.getDocumentCallbackControlEvents();
                    var callback;
                    if (arrCallbackName.indexOf(callbackName) > -1) {
                        var temp = callbackName;
                        callback = function() {
                            this[temp].apply(this, arguments);
                        };
                    } else {
                        callback = controller[callbackName];
                        arrCallbackName.push(callbackName);
                    }
                    callbackNode.addTargetWithActionForControlEvents(controller, callback, documentCallbackControlEvents[j]);
                }
                else
                {
                    callbackNode.setCallback(controller[callbackName], controller);
                }
            }
        }
        
        
        // Variables
        var documentOutletNames = animationManager.getDocumentOutletNames();
        var documentOutletNodes = animationManager.getDocumentOutletNodes();
        
        for (var j = 0; j < documentOutletNames.length; j++)
        {
            var outletName = documentOutletNames[j];
            var outletNode = documentOutletNodes[j];
            
            controller[outletName] = outletNode;
        }
        
        if (typeof(controller.onDidLoadFromCCB) == "function")
        {
            controller.onDidLoadFromCCB();
        }
        
        // Setup timeline callbacks
        var keyframeCallbacks = animationManager.getKeyframeCallbacks();
        for (var j = 0; j < keyframeCallbacks.length; j++)
        {
            var callbackSplit = keyframeCallbacks[j].split(":");
            var callbackType = callbackSplit[0];
            var callbackName = callbackSplit[1];
            
            if (callbackType == 1) // Document callback
            {
                var callfunc = cc.CallFunc.create(controller[callbackName], controller);
                animationManager.setCallFunc(callfunc, keyframeCallbacks[j]);
            }
            else if (callbackType == 2 && owner) // Owner callback
            {
                var callfunc = cc.CallFunc.create(owner[callbackName], owner);
                animationManager.setCallFunc(callfunc, keyframeCallbacks[j]);
            }
        }
        
        // Start animation
        var autoPlaySeqId = animationManager.getAutoPlaySequenceId();
        if (autoPlaySeqId != -1)
        {
            animationManager.runAnimationsForSequenceIdTweenDuration(autoPlaySeqId, 0);
        }
    }
    
    return node;
};

// JS to Native bridges
if(window.JavascriptJavaBridge && cc.sys.os == cc.sys.OS_ANDROID){
    jsb.reflection = new JavascriptJavaBridge();
    cc.sys.capabilities["keyboard"] = true;
}
else if(window.JavaScriptObjCBridge && (cc.sys.os == cc.sys.OS_IOS || cc.sys.os == cc.sys.OS_OSX)){
    jsb.reflection = new JavaScriptObjCBridge();
}
