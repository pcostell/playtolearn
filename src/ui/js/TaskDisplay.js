goog.provide('playtolearn.TaskDisplay');

goog.require('goog.dom');
goog.require('goog.events');
goog.require('goog.events.InputHandler.EventType');
goog.require('goog.style');
goog.require('goog.ui.LabelInput');

/**
 * [TaskDisplay description]
 * @constructor
 * @param {goog.dom.DomHelper=} opt_domHelper [description]
 */
playtolearn.TaskDisplay = function(opt_domHelper) {
    goog.ui.Component.call(this, opt_domHelper);
    this.curr_task = null;
}
goog.inherits(playtolearn.TaskDisplay, goog.ui.Component);

/**
 * [set_task description]
 * @param {[type]} task [description]
 */
playtolearn.TaskDisplay.prototype.setTask = function(task) {
    if (this.curr_task != null) {
      goog.dom.classes.remove(this.curr_task.getElement(), goog.getCssName('playtolearn-task-edit'));
    }
    this.curr_task = task;
    this.clearTask();
    if (task == null) {
      goog.style.showElement(this.getElement(), false);
      return;
    }
    goog.dom.classes.add(task.getElement(), goog.getCssName('playtolearn-task-edit'));
    goog.style.showElement(this.getElement(), true);
    this.renderTask(task);
}

playtolearn.TaskDisplay.prototype.clearTask = function() {
  goog.dom.removeChildren(this.getElement());
}

playtolearn.TaskDisplay.prototype.renderTask = function(task) {
  var elem = this.getElement();
  var props = task.getProperties();
  for (var i in props) {
    goog.dom.append(elem, goog.dom.createTextNode(props[i] + ":"));
    var label = new goog.ui.LabelInput((task["get" + props[i]])());
    label.render(elem);
    goog.events.listen(label.getElement(), goog.events.InputHandler.EventType.INPUT, function(e) {
      this.curr_task.setName(label.getValue());
    }, false, this);
  }
}

/**
 * Creates an initial DOM representation for the component.
 */
playtolearn.TaskDisplay.prototype.createDom = function() {
  this.decorateInternal(this.dom_.createElement('div'));
};


/**
 * Decorates an existing HTML DIV element as a SampleComponent.
 *
 * @param {Element} element The DIV element to decorate. The element's
 *    text, if any will be used as the component's label.
 */
playtolearn.TaskDisplay.prototype.decorateInternal = function(element) {
  playtolearn.TaskDisplay.superClass_.decorateInternal.call(this, element);
  var elem = this.getElement();
  goog.style.showElement(elem, false);
  goog.dom.classes.add(elem, goog.getCssName('playtolearn-taskdisplay'));
};
