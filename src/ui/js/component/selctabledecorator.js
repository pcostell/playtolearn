
goog.provide('playtolearn.component.SelectableComponent');

goog.require('playtolearn.base');

playtolearn.component.SelectableHandler = function() {}
playtolearn.component.SelectableHandler.prototype.onSelected = function() {}
playtolearn.component.SelectableHandler.prototype.onUnselected = function() {}

playtolearn.component.SelectableComponent = function() {
  this.isSelected_ = false;
  
}
playtolearn.base.interface(playtolearn.component.SelectableComponent, playtolearn.component.SelectableHandler);

playtolearn.component.SelectableComponent.prototype.enterDocument = function() {
  goog.events.listen(this.getElement(), goog.events.EventType.CLICK, 
    function(e) {
      if (this.isSelected_) {
        this.onUnselected();
      } else {
        this.onSelected();
      }
      this.isSelected_ = !this.isSelected_;
      e.stopPropagation();
    }, false, this);
  goog.events.listen(playtolearn.base.getDrawingRoot().getElement(), goog.events.EventType.CLICK,
    function(e) {
      this.isSelected_ = false;
    }, false, this);
    
}
  