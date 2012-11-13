goog.require('playtolearn.util.Table')
goog.require('playtolearn.Task');
goog.require('playtolearn.TaskDropHandler');
goog.require('playtolearn.handlers.DropTargetHandler');
goog.require('goog.dom');
goog.require('goog.style');
goog.require('goog.events');
goog.require('goog.fx.DragDrop');

goog.provide('playtolearn.Quest');

var questID = 0;

/**
 * [Quest description]
 * @constructor
 * @param {number=} id [description]
 */
playtolearn.Quest = function(id) {
  
  /**
   *  [id description]
   *  @private
   *  @type {number}
   */
  this.id = id != null ? id : questID++;
  
  /**
   * [tasks description]
   * @private
   * @type {playtolearn.util.Table}
   */
  this.tasks = new playtolearn.util.Table();
  
  /**
   * [start_level description]
   * @type {number}
   */
  this.start_level = 0;
  
  /**
   * The dom object used by this element.
   * @type {Element}
   */
  this.dom = null;
  
  this.move_down = function() {
    this.start_level++;
  }
  
  this.move_up = function() {
    this.start_level = Math.max(this.start_level - 1, 0);
  }

  this.renderLevel = function(levelData, levelID, dragSrcs, dragTargets, taskDisplay) {
    
    var level;
    if (levelData.length() > 1) {
      level = goog.dom.createDom("div", 
        {id : this.id + "_" + (levelID), 'class' : 'multi-quest'});
    } else {
      level = goog.dom.createDom("div",
        {id : this.id + "_" + (levelID),
        'class' : 'multi-quest'});
    }
    for (var i = 0; i < levelData.length(); i++) {
      var task = levelData.get(i).render(taskDisplay);
      //goog.style.setInlineBlock(task);
      goog.dom.append(level, task);
      dragSrcs.addItem(task, 
        new playtolearn.TaskDropHandler(this.tasks,
          levelData, levelData.get(i)));
    }
    var addItem = goog.dom.createDom("div", {'class' : 'add-item'});
    addItem.innerHTML = "+";
    goog.dom.append(level, addItem);
    dragTargets.addItem(level, new playtolearn.QuestLevelHandler(
      addItem,
      new playtolearn.QuestLevel(levelData)));
    return level;
  }
}

playtolearn.Quest.prototype.addTask = function(task) {
  this.tasks.append(task);
}

playtolearn.Quest.prototype.render = function(parent, dragSrcs, dragTargets, taskDisplay) {
  var quest = goog.dom.createDom("div", 
    { id     : this.id,
     'class' : 'quest',
     'style' : 'margin-top: ' + this.start_level * 40 + 'px'});

  for (var i = 0; i < this.tasks.length(); i++) {
    var level = this.renderLevel(this.tasks.getRow(i), i, dragSrcs, dragTargets, taskDisplay);
    goog.dom.append(quest, level);
  }
  var newTaskLevel = goog.dom.createDom('div', {style: 'width:100%; border:1px dashed black; height: 20px'});
  newTaskLevel.innerHTML = '+';
  dragTargets.addItem(newTaskLevel, new playtolearn.QuestHandler(newTaskLevel, this));
  
  // drag.setDragItemHoverClass('cursor_move');
  // drag.setDraggerElClass('cursor_move opacity_40');
  
//  var newTaskLevel = goog.dom.createDom('input', {'value' : '+', 'type' : 'submit'});
//  goog.events.listen(newTaskLevel, goog.events.EventType.CLICK,
//      this.addTask, false, this);
  var moveDown = goog.dom.createDom('input', {'value' : 'v', 'type' : 'submit'});
  var moveUp = goog.dom.createDom('input', {'value' : '^', 'type' : 'submit'});
  goog.events.listen(moveDown, goog.events.EventType.CLICK,
      this.move_down, false, this);
  goog.events.listen(moveUp, goog.events.EventType.CLICK,
      this.move_up, false, this);
  goog.dom.append(quest, newTaskLevel);
  goog.dom.append(quest, moveDown);
  goog.dom.append(quest, moveUp);
  this.dom = quest;
  goog.dom.append(parent, this.dom);
  return quest;
} 

function removeNonDivs(domObject) {
  var result = new Array();
  var children = goog.dom.getChildren(domObject);
  for (var i = 0; i < children.length; i++) {
    if (children[i].tagName === "DIV") {
      result.push(children[i]);
    }
  }
  return result;
}

/**
 * [QuestLevel description]
 * @constructor
 * @param {playtolearn.util.Table.Row} levelData [description]
 */
playtolearn.QuestLevel = function(levelData) {
  
  /**
   * [data description]
   * @private
   * @type {playtolearn.util.Table.Row}
   */
  this.data = levelData;
}

playtolearn.QuestLevel.prototype.addTask = function(task) {
  this.data.append(task);
}

/**
 * Handler for quest levels.
 * @constructor
 * @extends{playtolearn.handlers.DropTargetHandler}
 * @param {Element} addItem   [description]
 * @param {playtolearn.QuestLevel} levelData [description]
 */
playtolearn.QuestLevelHandler = function(addItem, levelData) {
  
  /**
   * [addItem description]
   * @type {Element}
   */
  this.addItem = addItem;
  
  /**
   * [levelData description]
   * @type {playtolearn.QuestLevel}
   */
  this.levelData = levelData;
  
  this.onElementOver = function(e) {
    this.addItem.style.width = "40px";
  }
  
  this.onElementOut = function(e) {
    this.addItem.style.width = "20px";
  }
  
  this.addTask = function(task) {
    this.levelData.addTask(task);
  }
}
goog.inherits(playtolearn.QuestLevelHandler, playtolearn.handlers.DropTargetHandler);

/**
 * Handler for quests.
 * @constructor
 * @extends{playtolearn.handlers.DropTargetHandler}
 * @param {Element} addItem [description]
 * @param {playtolearn.Quest} quest   [description]
 */
playtolearn.QuestHandler = function(addItem, quest) {
  
  /**
   * [addItem description]
   * @private
   * @type {Element}
   */
  this.addItem = addItem;
  
  /**
   * [quest description]
   * @private
   * @type {playtolearn.Quest}
   */
  this.quest = quest;

  this.onElementOver = function(e) {
    this.addItem.style.height = "40px";
  }
  
  this.onElementOut = function(e) {
    this.addItem.style.height = "20px";
  }
  
  this.addTask = function(task) {
    this.quest.addTask(task);
  }
}
goog.inherits(playtolearn.QuestHandler, playtolearn.handlers.DropTargetHandler);

playtolearn.Quest.MARGIN = 20;
