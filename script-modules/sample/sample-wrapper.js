var addon = require('bindings')('sample');

exports.store = [];
exports.objStore = [];
exports.createObject = function (x) {
  var obj = addon.createObject(x);
  this.store.push(x);
  this.objStore.push(obj);
};
exports.addObjects = function (obj1, obj2) {
  return addon.add(obj1, obj2);
};
exports.sumAll = function () {
  var total = 0, num;
  var tempStore = this.store;
  while (tempStore.length > 0) {
    total += tempStore.splice(0, 1);
  }
  return total;
};
exports.removeObject = function (id) {
  if (this.store.indexOf(id) > -1) {
    this.store.splice(this.store.indexOf(id), 1);
    return true;
  } else {
    return false;
  }
};

