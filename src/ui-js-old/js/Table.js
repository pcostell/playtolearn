goog.provide('playtolearn.util.Table');

goog.require('goog.debug.Logger');

var logger = new goog.debug.Logger('playtolearn.util.Table');

/**
 * [Table description]
 * @constructor
 */
playtolearn.util.Table = function() {
   
   /**
    * Data for storing Table rows.
    * @private
    * @type {Array}
    */
   this.data = Array();
  
}

/** Public Methods **/
playtolearn.util.Table.prototype.getWidth = function() {
  var max = 0;
  for (var i = 0; i < this.data.length; i++) {
    if (this.data[i].length() > max) {
      max = this.data[i].length();
    }
  }
  return max;
}

playtolearn.util.Table.prototype.getHeight = function() {
  return this.data.length;
}

playtolearn.util.Table.prototype.set = function(rowIndex, colIndex, obj) {
   if (rowIndex < 0) {
    logger.severe("Tried to set on row at out-of-bounds index: " + rowIndex);
  }
  for (var i = 0; i < rowIndex - this.getHeight(); i++) {
    this.appendRow();
  }
  this.data[rowIndex].set(colIndex, obj);
}

playtolearn.util.Table.prototype.insertRow = function(rowIndex) {
  this.data.splice(rowIndex, 0, new playtolearn.util.Table.Row());
}

playtolearn.util.Table.prototype.getRow = function(rowIndex) {
  if (rowIndex >= this.data.length || rowIndex < 0) {
    logger.severe("Tried to get row at out-of-bounds index: " + rowIndex);
  }
  return this.data[rowIndex]; 
}

playtolearn.util.Table.prototype.appendRow = function() {
  this.data.push(new playtolearn.util.Table.Row());
}

playtolearn.util.Table.prototype.append = function(obj) {
  var row = new playtolearn.util.Table.Row();
  row.append(obj);
  this.data.push(row);
}

playtolearn.util.Table.prototype.get = function(rowIndex, colIndex) {
  if (rowIndex >= this.data.length || rowIndex < 0) {
    logger.severe("Tried to get row at out-of-bounds index: " + rowIndex);
  }
  return this.data[rowIndex].get(colIndex);
}

playtolearn.util.Table.prototype.empty = function() {
  return this.data.length == 0;
}

playtolearn.util.Table.prototype.length = function() {
  return this.data.length;
}

playtolearn.util.Table.prototype.contains = function(obj) {
  for (var i = 0; i < this.getHeight(); i++) {
    if (this.data[i].contains(obj)) {
      return true;
    }
  }
  return false;
}

playtolearn.util.Table.prototype.removeAt = function (rowIndex, columnIndex) {
  this.data[rowIndex].removeAt(columnIndex);
}

playtolearn.util.Table.prototype.remove = function(obj) {
  for (var i = 0; i < this.getHeight(); i++) {
    if (this.data[i].remove(obj)) {
      return true;
    }
  }
  return false;
}

playtolearn.util.Table.prototype.removeRow = function(row) {
  var index = this.data.indexOf(row);
  if (index < 0) {
    return false;
  }
  this.data.splice(index, 1);
  return true;
}

/**
 * [Row description]
 * @constructor
 */
playtolearn.util.Table.Row = function() {
  
  /**
   * Underlying data for this Row.
   * @private
   * @type {[type]}
   */
  this.data = Array();
  
}

playtolearn.util.Table.Row.prototype.removeAt = function(index) {
  this.data.splice(index, 1);
}

playtolearn.util.Table.Row.prototype.remove = function(obj) {
  var index = this.data.indexOf(obj);
  if (index < 0) {
    return false;
  }
  this.data.splice(index, 1);
  return true;
}

playtolearn.util.Table.Row.prototype.append = function(obj) {
  this.data.push(obj);
}

playtolearn.util.Table.Row.prototype.insert = function(columnIndex, obj) {
  if (columnIndex >= this.data.length || columnIndex < 0) {
    logger.severe("Tried to insert column at negative location: " + columnIndex);
  }
  this.data.splice(columnIndex, 0, obj);
}

/**
 * Get an item out of the row.
 * @param  {number} columnIndex the column index. Must be in bounds.
 * @return {type}             [description]
 */
playtolearn.util.Table.Row.prototype.get = function(columnIndex) {
  if (columnIndex >= this.data.length || columnIndex < 0) {
    logger.severe("Tried to get column of row at out-of-bounds index: " + columnIndex);
  }
  return this.data[columnIndex];
}

playtolearn.util.Table.Row.prototype.contains = function(obj) {
  return this.data.indexOf(obj) >= 0;
}

/**
 * Computes the length of the row.
 * @return {number} the length.
 */
playtolearn.util.Table.Row.prototype.length = function() {
  return this.data.length;
}
