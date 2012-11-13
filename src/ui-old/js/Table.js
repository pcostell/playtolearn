goog.provide('playtolearn.util.Table')

/** playtolearn.util.Table Constructor **/
playtolearn.util.Table = function() {
  var data = Array();
  
}

/** Public Methods **/
playtolearn.util.Table.prototype.getWidth = function() {
  
}

playtolearn.util.Table.prototype.getHeight = function() {
  
}

playtolearn.util.Table.prototype.set = function(rowIndex, colIndex, obj) {
   if (rowIndex < 0) {
    Exception("Tried to set on row at out-of-bounds index: " + rowIndex);
  }
  for (var i = 0; i < rowIndex - this.getHeight(); i++) {
    this.appendRow();
  }
  data[rowIndex].set(colIndex, obj);
}

playtolearn.util.Table.prototype.insertRow = function(rowIndex) {
  data.splice(rowIndex, 0, new playtolearn.util.Table.Row());
}

playtolearn.util.Table.prototype.getRow = function(rowIndex) {
  if (rowIndex >= data.length || rowIndex < 0) {
    Exception("Tried to get row at out-of-bounds index: " + rowIndex);
  }
  return data[rowIndex]; 
}

playtolearn.util.Table.prototype.appendRow = function() {
  data.push(new playtolearn.util.Table.Row());
}

playtolearn.util.Table.prototype.append = function(obj) {
  var row = new playtolearn.util.Table.Row();
  row.append(obj);
  data.push(row);
}

playtolearn.util.Table.prototype.get = function(rowIndex, colIndex) {
  if (rowIndex >= data.length || rowIndex < 0) {
    Exception("Tried to get row at out-of-bounds index: " + rowIndex);
  }
  return data[rowIndex].get(colIndex);
}

playtolearn.util.Table.prototype.empty = function() {
  return data.length == 0;
}

/** Row Constructor **/
playtolearn.util.Table.Row = function() {
  var data = Array();
  
}

playtolearn.util.Table.Row.prototype.append = function(obj) {
  data.push(obj);
}

playtolearn.util.Table.Row.prototype.insert = function(columnIndex, obj) {
  if (columnIndex >= data.length || columnIndex < 0) {
    Exception("Tried to insert column at negative location: " + columnIndex);
  }
  data.splice(columnIndex, 0, obj);
}

playtolearn.util.Table.Row.prototype.get = function(columnIndex) {
  if (columnIndex >= data.length || columnIndex < 0) {
    Exception("Tried to get column of row at out-of-bounds index: " + columnIndex);
  }
  return data(columnIndex);
}
