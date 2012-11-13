goog.provide('playtolearn.TaskDisplay');

goog.require('goog.dom');
goog.require('goog.events');
goog.require('goog.events.InputHandler.EventType');
goog.require('goog.ui.LabelInput');

/**
 * [TaskDisplay description]
 * @constructor
 * @param {[type]} id [description]
 */
playtolearn.TaskDisplay = function(id) {
  this.dom = goog.dom.getElement(id);
  this.curr_task = null;
  
  this.set_task = function(task) {
    this.curr_task = task;
    this.render();
  }
}

playtolearn.TaskDisplay.prototype.render = function() {
  goog.dom.removeChildren(this.dom);
  goog.dom.append(this.dom, goog.dom.createTextNode('Task Name:'));
  var label = new goog.ui.LabelInput(this.curr_task.get_text());
  label.render(this.dom);
  goog.events.listen(label.getElement(), goog.events.InputHandler.EventType.INPUT, function(e) {
    this.curr_task.set_text(label.getValue());
    this.curr_task.render(this);
  }, false, this);
}

/**
 * [setupHandler description]
 * @param  {int} taskDom [description]
 * @param  {int} task    [description]
 */
playtolearn.TaskDisplay.prototype.setupHandler = function(taskDom, task) {
  goog.events.listen(taskDom, goog.events.EventType.CLICK, function(e) {
    this.set_task(task);
  }, false, this);
}

