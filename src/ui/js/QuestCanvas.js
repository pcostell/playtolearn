
goog.provide('playtolearn.QuestCanvas');

goog.require('playtolearn.base');
goog.require('playtolearn.Graph');
goog.require('playtolearn.TaskDisplay');
goog.require('playtolearn.component.SideBarComponent');

goog.require('goog.dom');
goog.require('goog.events');

playtolearn.QuestCanvas = function() {
  var currQuest = null;
  var currQuestLevel = null;
  var graph = new playtolearn.Graph();
  var taskDisplay = new playtolearn.TaskDisplay();
  graph.render(goog.dom.getElement('canvas'));
  taskDisplay.render(goog.dom.getElement('task_display'));
  var newQuestLevel = new playtolearn.NewQuestLevel();
  newQuestLevel.render(goog.dom.getElement('new_task'));
  playtolearn.base.setDrawingRoot(graph);
  goog.events.listen(playtolearn.component.SideBarEventSource, "TARGET_CHANGE", function(e) {taskDisplay.setTask(e.target)})
  
  goog.events.listen(graph.getElement(), goog.events.EventType.CLICK,
    function(e) {
      taskDisplay.setTask(null);
    });

  goog.events.listen(goog.dom.getElement("new_quest_button"), goog.events.EventType.CLICK,
    function(e) {
      currQuest = new playtolearn.Quest();
      graph.addChild(currQuest, true, true);
    });
  
  goog.events.listen(goog.dom.getElement("populate"), goog.events.EventType.CLICK,
    function(e) {
      var quest1 = new playtolearn.Quest();
      graph.addChild(quest1, true, true);
      var questLevel1 = new playtolearn.QuestLevel();
      questLevel1.addChild(new playtolearn.Task("Task 1"), true);      
      questLevel1.addChild(new playtolearn.Task("Task 2"), true);      
      questLevel1.addChild(new playtolearn.Task("Task 3"), true);      
      var questLevel2 = new playtolearn.QuestLevel();
      questLevel2.addChild(new playtolearn.Task("Task 4"), true);      
      var questLevel3 = new playtolearn.QuestLevel();
      questLevel3.addChild(new playtolearn.Task("Task 5"), true);   
      quest1.addChild(questLevel1, true);
      quest1.addChild(questLevel2, true);
      quest1.addChild(questLevel3, true);
      
      var quest2 = new playtolearn.Quest();
      graph.addChild(quest2, true, true);
      var questLevel1 = new playtolearn.QuestLevel();
      questLevel1.addChild(new playtolearn.Task("Task 1"), true);      
      questLevel1.addChild(new playtolearn.Task("Task 2"), true);      
      questLevel1.addChild(new playtolearn.Task("Task 3"), true);      
      var questLevel2 = new playtolearn.QuestLevel();
      questLevel2.addChild(new playtolearn.Task("Task 4"), true);      
      var questLevel3 = new playtolearn.QuestLevel();
      questLevel3.addChild(new playtolearn.Task("Task 5"), true);   
      quest2.addChild(questLevel1, true);
      quest2.addChild(questLevel2, true);
      quest2.addChild(questLevel3, true);        
    });
}

goog.exportSymbol('playtolearn.QuestCanvas', playtolearn.QuestCanvas);
