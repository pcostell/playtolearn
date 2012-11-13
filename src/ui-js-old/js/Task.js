goog.provide('playtolearn.Task');
goog.provide('playtolearn.TaskDropHandler');

goog.require('playtolearn.handlers.DropSourceHandler');
goog.require('goog.style');

var taskID = 0;

/**
 * [Task description]
 * @constructor
 * @param {string} text [description]
 */
playtolearn.Task = function(text) {
  
  /**
   * [id description]
   * @private
   * @type {Number}
   */
  this.id = taskID++;

  this.set_text = function(new_text) {
    text = new_text;
  }
  
  this.get_text = function() {
    return text;
  }
  
  this.render = function(taskDisplay) {
    var task = goog.dom.createDom("div", 
      {'id' : this.id,
       'class' : 'task'});
    task.innerHTML = text;
    taskDisplay.setupHandler(task, this);
    return task;
  }
  
}
goog.inherits(playtolearn.Task, goog.ui.Component);


/**
 * [TaskDropHandler description]
 * @constructor
 * @extends {playtolearn.handlers.DropSourceHandler}
 * @param {playtolearn.util.Table} questData  [description]
 * @param {playtolearn.util.Table.Row} questLevel [description]
 * @param {playtolearn.Task} task       [description]
 */
playtolearn.TaskDropHandler = function(questData, questLevel, task) {
  
  /**
   * The table that stores task data.
   * @type {playtolearn.util.Table}
   */
  this.questData = questData;
  
  /**
   * The row of the table for the specific task.
   * @type {playtolearn.util.Table.Row}
   */
  this.questLevel = questLevel;
  
  /**
   * The specific task for the handler.
   * @type {playtolearn.Task}
   */
  this.task = task;
  
  this.onDropped = function(e) {
    this.questLevel.remove(this.task);
    e.dropTargetItem.data.addTask(this.task);
    if (this.questLevel.length() == 0) {
      this.questData.removeRow(this.questLevel);
    }
  }
}
goog.inherits(playtolearn.TaskDropHandler, playtolearn.handlers.DropSourceHandler);


/**
 * The size of a task block.
 * @const
 * @type {Number}
 */
playtolearn.Task.SIZE = 40;