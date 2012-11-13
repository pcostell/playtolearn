goog.provide('playtolearn.component.SideBarEvent');
goog.provide('playtolearn.component.SideBarEventSource');
goog.provide('playtolearn.component.SideBarComponent');
goog.provide('playtolearn.component.SideBarComponentHandler');

goog.require('playtolearn.base');

goog.require('goog.events.EventTarget');
goog.require('goog.events.Event');

var sideBarElem_ = null;

playtolearn.component.SideBarEvent = function() {
  this.type = "TARGET_CHANGE";
  this.target = sideBarElem_;
}
playtolearn.base.inherits(playtolearn.component.SideBarEvent, goog.events.Event);

SideBarEventSource_ = function() {}
playtolearn.base.inherits(SideBarEventSource_, goog.events.EventTarget);

playtolearn.component.SideBarEventSource = new SideBarEventSource_();


playtolearn.component.SideBarComponentHandler = function() {}
playtolearn.component.SideBarComponentHandler.prototype.getProperties = function() {
  return new Array();
};

playtolearn.component.SideBarComponent = function() {}
playtolearn.base.interface(playtolearn.component.SideBarComponent, playtolearn.component.SideBarComponentHandler);

playtolearn.component.SideBarComponent.prototype.enterDocument = function() {
  goog.events.listen(this.getElement(), goog.events.EventType.CLICK, 
    function(e) {
      sideBarElem_ = this;
      playtolearn.component.SideBarEventSource.dispatchEvent(new playtolearn.component.SideBarEvent());
      e.stopPropagation();
  }, false, this);
}
