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

cch._debug = false;
cch.setDebug = function(debug) {
    cch._debug = debug;
};
cch.isDebug = function() {
    return cch._debug;
};

cch._logToFile = false;
cch.setLogToFile = function(logToFile) {
    cch._logToFile = logToFile;
};
cch.isLogToFile = function() {
    return cch._logToFile;
};

cch.log = function(msg, noStack) {
    if (!cch._debug) {
        return;
    }
    noStack = noStack || false;
    msg = cch.toA(msg);
    var str = "";
    if (!noStack) {
        var err = new Error(msg);
        var stackArr = err.stack.split("\n");
        stackArr.shift();
        var stack = stackArr.join("\n");
        str = "-----STACK-----:";
        str += "\n" + stack;
        str += "----MESSAGE----:\n";
    }
    str += msg;
    cc.log(str);
    if (cch._logToFile) {
        cch.HLogFile.logFile(str);
    }
};

cch.assert = function(condition, msg) {
    if (!cch._debug || condition) {
        return;
    }
    msg = cch.toA(msg);
    var err = new Error(msg);
    var stackArr = err.stack.split("\n");
    stackArr.shift();
    var stack = stackArr.join("\n");
    var str = "-----STACK-----:";
    str += "\n" + stack;
    str += "----MESSAGE----:\n" + msg;
    cc.log(str);
    if (cch._logToFile) {
        cch.HLogFile.logFile(str);
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
