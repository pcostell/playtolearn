goog.provide('playtolearn.handlers');
goog.provide('playtolearn.handlers.DropSourceHandler');
goog.provide('playtolearn.handlers.DropTargetHandler');
/**
 * Drop handlers.
 **/
 
goog.require('goog.style');

/**
 * [DropHandler description]
 * @interface
 */
playtolearn.handlers.DropHandler = function() {}
playtolearn.handlers.DropHandler.prototype.dropEvent = function(e) {}
playtolearn.handlers.DropHandler.prototype.overEvent = function(e) {}
playtolearn.handlers.DropHandler.prototype.outEvent = function(e) {}

/**
 * [DropSourceHandler description]
 * @interface
 * @extends{DropHandler}
 */
playtolearn.handlers.DropSourceHandler = function() {}
goog.inherits(playtolearn.handlers.DropSourceHandler, playtolearn.handlers.DropHandler);
/**
 * [droppedEvent description]
 * @protected
 * @param  {Event} e [description]
 */
playtolearn.handlers.DropSourceHandler.prototype.dropEvent = function(e) {
  this.onDropped(e);
}

/**
 * [overEvent description]
 * @protected
 * @param  {[type]} e [description]
 */
playtolearn.handlers.DropSourceHandler.prototype.overEvent = function(e) {
  this.onOver(e);
}

/**
 * [outEvent description]
 * @protected
 * @param  {[type]} e [description]
 */
playtolearn.handlers.DropSourceHandler.prototype.outEvent = function(e) {
  this.onOut(e);
}

playtolearn.handlers.DropSourceHandler.prototype.onDropped = function(e) {}
playtolearn.handlers.DropSourceHandler.prototype.onOver = function(e) {}
playtolearn.handlers.DropSourceHandler.prototype.onOut = function(e) {}


/**
 * [DropTargetHandler description]
 * @interface
 * @extends{DropHandler}
 */
playtolearn.handlers.DropTargetHandler = function() {}
goog.inherits(playtolearn.handlers.DropTargetHandler, playtolearn.handlers.DropHandler);
/**
 * [droppedEvent description]
 * @protected
 * @param  {Event} e [description]
 */
playtolearn.handlers.DropTargetHandler.prototype.droppedEvent = function(e) {
  this.onElementDropped(e);
}

/**
 * [overEvent description]
 * @protected
 * @param  {[type]} e [description]
 */
playtolearn.handlers.DropTargetHandler.prototype.overEvent = function(e) {
  this.onElementOver(e);
}

/**
 * [outEvent description]
 * @protected
 * @param  {[type]} e [description]
 */
playtolearn.handlers.DropTargetHandler.prototype.outEvent = function(e) {
  this.onElementOut(e);
}

playtolearn.handlers.DropTargetHandler.prototype.onElementDropped = function(e) {}
playtolearn.handlers.DropTargetHandler.prototype.onElementOver = function(e) {}
playtolearn.handlers.DropTargetHandler.prototype.onElementOut = function(e) {}
