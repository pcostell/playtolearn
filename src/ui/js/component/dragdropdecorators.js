goog.provide('playtolearn.component.DragDropSourceComponent');
goog.provide('playtolearn.component.DragDropTargetComponent');
goog.provide('playtolearn.component.DragDropTargetComponentHandler');

goog.require('goog.fx.DragDropGroup');
goog.require('goog.fx.DragDrop');

goog.require('playtolearn.base');

var group_ = new goog.fx.DragDropGroup();
group_.init();

playtolearn.component.DragDropSourceComponent = function() {};


playtolearn.component.DragDropSourceComponent.prototype.enterDocument = function() {
  this.dragDropItem_ = new goog.fx.DragDropItem(this.getElement(), this);
  group_.addDragDropItem(this.dragDropItem_); 
}

playtolearn.component.DragDropTargetComponentHandler = function() {}
playtolearn.component.DragDropTargetComponentHandler.prototype.onDrop = function(e) {
  e.dragSourceItem.data.getParent().removeChild(e.dragSourceItem.data); 
  e.dropTargetItem.data.addChild(e.dragSourceItem.data); 
}

playtolearn.component.DragDropTargetComponentHandler.prototype.onDragOver = function(e) {}
playtolearn.component.DragDropTargetComponentHandler.prototype.onDragOut = function(e) {}

playtolearn.component.DragDropTargetComponent = function() {}
playtolearn.base.interface(playtolearn.component.DragDropTargetComponent, playtolearn.component.DragDropTargetComponentHandler);

playtolearn.component.DragDropTargetComponent.prototype.enterDocument = function() {
  this.dragDropItem_ = new goog.fx.DragDrop(this.getElement(), this);
  group_.addTarget(this.dragDropItem_);
  
  goog.events.listen(this.dragDropItem_, goog.fx.AbstractDragDrop.EventType.DROP, 
    function(e) { this.onDrop(e); }, true, this);
  goog.events.listen(this.dragDropItem_, goog.fx.AbstractDragDrop.EventType.DRAGOVER, 
    function(e) { this.onDragOver(e); }, true, this);
  goog.events.listen(this.dragDropItem_, goog.fx.AbstractDragDrop.EventType.DRAGOUT, 
    function(e) { this.onDragOut(e); }, true, this);
};