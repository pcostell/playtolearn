goog.provide('playtolearn.Graph');
goog.provide('playtolearn.NewTaskHandler');

goog.require('playtolearn.Quest');
goog.require('playtolearn.Task');
goog.require('playtolearn.handlers.DropSourceHandler');
goog.require('goog.events');
goog.require('goog.fx.DragDropGroup');

/**
 * [Graph description]
 * @constructor
 * @param {string} canvas_id [description]
 */
playtolearn.Graph = function(canvas_id) {
  
  /** Instance variables **/
  
  /**
   * [nodes description]
   * @private
   * @type {[playtolearn.Quest]}
   */
  this.nodes = new Array();
  
  /**
   * [curr_item description]
   * @type {playtolearn.Quest}
   */
  var curr_item = null;

  /** Protected methods. **/
  
  /**
   * [insert_quest description]
   * @protected
   */
  this.insert_quest = function() {
    curr_item = new playtolearn.Quest();
    this.nodes.push(curr_item);
  }

  /**
   * [render description]
   * @param {playtolearn.TaskDisplay} taskDisplay [description]
   * @protected
   */
  this.render = function(taskDisplay) {
    var d = goog.dom.getElement(canvas_id);
    if (d == null) {
      return;
    }
    goog.dom.removeChildren(d);
    var dragSrcs = new goog.fx.DragDropGroup();
    var newTaskItem = goog.dom.getElement('new_task');
    dragSrcs.addItem(newTaskItem, new playtolearn.NewTaskHandler());

    var dragTargets = new goog.fx.DragDropGroup();
    for (var i = 0; i < this.nodes.length; i++) {
      goog.dom.append(d, this.nodes[i].render(dragSrcs, dragTargets, taskDisplay));
    }
    dragSrcs.addTarget(dragTargets);
    var that = this;
    goog.events.listen(dragTargets, goog.fx.AbstractDragDrop.EventType.DRAGOVER,
      function(e) {
        e.dragSourceItem.data.overEvent(e);
        e.dropTargetItem.data.overEvent(e);
      });
    goog.events.listen(dragTargets, goog.fx.AbstractDragDrop.EventType.DROP,
      function(e) {
        e.dragSourceItem.data.dropEvent(e);
        e.dropTargetItem.data.dropEvent(e);
        that.render(taskDisplay);
      });
    goog.events.listen(dragTargets, goog.fx.AbstractDragDrop.EventType.DRAGOUT,
      function(e) {
        e.dragSourceItem.data.outEvent(e);
        e.dropTargetItem.data.outEvent(e);
      });
    dragTargets.init();
    dragSrcs.init();

  }
}


/**
 * Handler for new task items.
 * @constructor
 * @extends {playtolearn.handlers.DropSourceHandler}
 */
playtolearn.NewTaskHandler = function() {
  
  this.onDropped = function(e) {
    e.dropTargetItem.data.addTask(new playtolearn.Task("New Task"));
  }
}
goog.inherits(playtolearn.NewTaskHandler, playtolearn.handlers.DropSourceHandler);
