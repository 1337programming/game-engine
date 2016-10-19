var sampleWrapper = require('./sample-wrapper');

exports.create = function (num) {
  sampleWrapper.createObject(num);
};
exports.addObjects = function (obj1, obj2) {
  sampleWrapper.addObjects(obj1, obj2);
};
exports.getSum = function () {
  return sampleWrapper.sumAll();
};
exports.getObjects = function () {
  return sampleWrapper.objStore;
};
exports.getValues = function () {
  return sampleWrapper.store;
};

