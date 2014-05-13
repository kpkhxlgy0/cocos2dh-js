cch = cch || {};

cch.dateFormat = function(date, pat) {
    var year = date.getFullYear();
    var month = date.getMonth() + 1;
    var day = date.getDate();
    var hour = date.getHours();
    var minute = date.getMinutes();
    var second = date.getSeconds();

    month = month > 9 ? month : "0" + month;
    day = day > 9 ? day : "0" + day;
    hour = hour > 9 ? hour : "0" + hour;
    minute = minute > 9 ? minute : "0" + minute;
    second = second > 9 ? second : "0" + second;
    if (!pat) {
        pat = "yyyy-MM-dd";
    }
    pat = pat.replace(/yyyy/g, year);
    pat = pat.replace(/MM/g, month);
    pat = pat.replace(/dd/g, day);
    pat = pat.replace(/HH/gi, hour);
    pat = pat.replace(/mm/g, minute);
    pat = pat.replace(/ss/g, second);
    return pat;
};

cch.dateGetTime2 = function(date) {
    return date.getTime() - date.getTimezoneOffset() / 60 * 3600 * 1000;
};

cch.dateDiff = function(date, date2) {
    return Math.ceil((date - date2) / (1000 * 60 * 60 * 24));
};

cch.dateAdd = function(date, days) {
    return new Date(date.getTime() + days * (1000 * 60 * 60 * 24));
};

cch.dateAddMonth = function(date, months) {
    var day = date.getDate();
    var month = date.getMonth() + 1;
    var year = date.getFullYear();
    month += months;
    if (month > 12) {
        year += Math.floor(month / 12);
        month = month % 12;
    }
    return Date.parse(month + "/" + day + "/" + year);
};

// yyyy-MM-dd
cch.dateParse2 = function(str) {
    if (str === null || str === "") {
        return new Date();
    }
    var rstr = str.replace(/(\d{4})([-\./])(\d{1,2})\2(\d{1,2})/, "$3/$4/$1");
    return new Date(Date.parse(rstr));
};

// json
cch.dateParse3 = function(obj) {
    return new Date(obj.time - new Date().getTimezoneOffset() / 60 * 3600 * 1000);
};

// global function

cch.dateGetWeek = function() {
    var a = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];
    var d = new Date().getDay();
    return a[d];
};

cch.dateGetDate = function() {
    var mydate = new Date();
    var y = mydate.getYear();
    var m = String(mydate.getMonth() + 1).lpad(2, "0");
    var d = String(mydate.getDate()).lpad(2, "0");
    var a = new Array(y, m, d);
    return a.join("-");
};