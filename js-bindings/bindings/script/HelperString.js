cch = cch || {};

cch.stringFormat = function() {
    var param = [];
    for (var i = 0, l = arguments.length; i < l; i++) {
        param.push(arguments[i]);
    }
    // get the first element(the original statement)
    var statment = param[0];
    // remove the first element from array
    param.shift();
    return statment.replace(/\{(\d+)\}/g, function(m, n) {
        return param[n];
    });
};

cch.stringCharLen = function(str) {
    var arr = str.match(/[^\x00-\xff]/ig);
    return str.length + (arr === null ? 0 : arr.length);
};

cch.stringReplaceLen = function(str, start, len, replaced) {
    if (!len)
        return str;

    if (start >= str.length)
        return str;

    var returnSeg = "";
    var returnSeg2 = "";
    var i = 0;
    for (; i < str.length; i++) {
        var c = str.charAt(i);
        if (i < start)
            returnSeg += c;

        if (i >= start + len)
            returnSeg2 += c;
    }

    return returnSeg + replaced + returnSeg2;
};

cch.stringReplaceChar = function(str, target, replaced, start) {
    if (!target)
        return str;

    if (!start)
        start = 0;

    var returnVal = str.substring(0, start);
    var index = 0;
    for (var i = start; i < str.length; i++) {
        var c = str.charAt(i);
        target = typeof target == "function" ? target.call(str, index) : target;
        if (c == target) {
            returnVal += typeof replaced == "function" ? replaced.call(str, index) : replaced;
            while (i < str.length - 1 && str.charAt(i + 1) == c) {
                i++;
            }
            index++;
        } else {
            returnVal += c;
        }
    }

    return returnVal;
};

cch.stringLpad = function(str, len, s) {
    var a = new Array(str);
    var n = (len - str.length);
    for (var i = 0; i < n; ++i)
        a.unshift(s);
    return a.join("");
};

cch.stringRpad = function(str, len, s) {
    var a = new Array(str);
    var n = (len - str.length);
    for (var i = 0; i < n; ++i)
        a.push(s);
    return a.join("");
};

cch.stringInitialsToUpper = function(str) {
    return str.substring(0, 1).toUpperCase().concat(str.substring(1));
};

cch.stringInitialsToLower = function(str) {
    return str.substring(0, 1).toLowerCase().concat(str.substring(1));
};

cch.stringFromUint16Array = function(array) {
    return String.fromCharCode.apply(null, new Uint16Array(array));
};
cch.stringToUint16Array = function(str) {
    var buf = new ArrayBuffer(str.length * 2); // 2 bytes for each char
    var bufView = new Uint16Array(buf);
    for (var i = 0, strLen = str.length; i < strLen; i++) {
        bufView[i] = str.charCodeAt(i);
    }
    return bufView;
};
cch.stringFromArrayBuffer = function(buf) {
    return String.fromCharCode.apply(null, new Uint16Array(buf));
};
cch.stringToArrayBuffer = function(str) {
    var buf = new ArrayBuffer(str.length * 2); // 2 bytes for each char
    var bufView = new Uint16Array(buf);
    for (var i = 0, strLen = str.length; i < strLen; i++) {
        bufView[i] = str.charCodeAt(i);
    }
    return buf;
};

cch.stringIsMobile = function(str) {
    return (/^(?:13\d|15[89])-?\d{5}(\d{3}|\*{3})$/).test(str.trim());
};

cch.stringIsPhone = function(str) {
    return (/^(([0\+]\d{2,3}-)?(0\d{2,3})-)(\d{7,8})(-(\d{3,}))?$/).test(str.trim());
};

cch.stringIsEmail = function(str) {
    return (/^[a-zA-Z0-9_\-]{1,}@[a-zA-Z0-9_\-]{1,}\.[a-zA-Z0-9_\-.]{1,}$/).test(str.trim());
};

cch.stringIsPost = function(str) {
    return (/^\d{6}$/).test(str.trim());
};

cch.stringIsUrl = function(str) {
    var strRegex = "^((https|http|ftp|rtsp|mms)://)" +
    // 验证ftp的user@
    "(([0-9a-z_!~*’().&=+$%-]+: )?[0-9a-z_!~*’().&=+$%-]+@)?" +
    // 验证IP形式的URL
    "(([0-9]{1,3}.){3}[0-9]{1,3}" +
        "|" + // 允许IP和DOMAIN（域名）
    "([0-9a-z_!~*’()-]+.)*" + // 域名- www.    
    "([0-9a-z][0-9a-z-]{0,61})?[0-9a-z]." + // 二级域名    
    "[a-z]{2,6})" + // 一级域名    
    "(:[0-9]{1,4})?"; // 端口        
    var re = new RegExp(strRegex);
    return re.test(str.trim());
};

cch.stringIsEnCn = function(str) {
    return (/^[a-zA-Z0-9_\u4e00-\u9fa5]+$/).test(str.trim());
};

cch.stringIsEn = function(str) {
    return (/^[a-zA-Z0-9_]+$/).test(str.trim());
};

cch.stringIsCn = function(str) {
    return (/^[\u4e00-\u9fa5]+$/).test(str.trim());
};

cch.stringRepeat = function(str, n) {
    return new Array(n + 1).join(str);
};