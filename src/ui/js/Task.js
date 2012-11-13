goog.provide('playtolearn.Task');

goog.require('playtolearn.base');
goog.require('playtolearn.component.SideBarComponent');
goog.require('playtolearn.component.DragDropSourceComponent');
goog.require('goog.style');


var taskID = 0;

/**
 * [Task description]
 * @constructor
 * @extends {goog.ui.Component}
 * @extends {playtolearn.handlers.DragDropSource}
 * @param {string=} opt_label [description]
 * @param {goog.dom.DomHelper=} opt_domHelper [description]
 */
playtolearn.Task = function(opt_label, opt_domHelper) {
  playtolearn.base.super(this, opt_domHelper);

  /**
   * @private
   * @type {string}
   */
  this.name = opt_label || "New Task";
}
playtolearn.base.inherits(playtolearn.Task, goog.ui.Component);

playtolearn.base.decorator(playtolearn.Task, playtolearn.component.DragDropSourceComponent);
playtolearn.base.decorator(playtolearn.Task, playtolearn.component.SideBarComponent); 

/**
 * [setName description]
 * @param {string} name the name to set.
 */
playtolearn.Task.prototype.setName = function(name) {
  this.name = name; 
  goog.dom.removeChildren(this.getElement());
  goog.dom.append(this.getElement(), goog.dom.createTextNode(this.name));
}

/**
 * [getName description]
 * @return {string} The task's name.
 */
playtolearn.Task.prototype.getName = function() {
  return this.name;
}

/**
 * Creates an initial DOM representation for the component.
 */
playtolearn.Task.prototype.createDom = function() {
  this.decorateInternal(this.dom_.createElement('div'));
};

/**
 * Decorates an existing HTML DIV element as a SampleComponent.
 *
 * @param {Element} element The DIV element to decorate. The element's
 *    text, if any will be used as the component's label.
 */
playtolearn.Task.prototype.decorateInternal = function(element) {
  playtolearn.base.super(this, "decorateInternal", element);

  var elem = this.getElement();
  goog.dom.classes.add(elem, goog.getCssName('playtolearn-task'));
  goog.dom.append(elem, goog.dom.createTextNode(this.name));
};

/**
 * Called when component's element is known to be in the document.
 */
playtolearn.Task.prototype.enterDocument = function() {
  playtolearn.base.super(this, "enterDocument");
};

playtolearn.Task.prototype.getProperties = function() {
  return ["Name"];
}
