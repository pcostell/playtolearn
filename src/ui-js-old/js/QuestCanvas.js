
goog.provide('playtolearn.QuestCanvas');

goog.require('playtolearn.Graph');
goog.require('playtolearn.TaskDisplay');
goog.require('goog.dom');
goog.require('goog.events');

playtolearn.QuestCanvas = function() {
  var graph = new playtolearn.Graph('canvas');
  var taskDisplay = new playtolearn.TaskDisplay('task_display');
  graph.render(taskDisplay);
  
  goog.events.listen(goog.dom.getElement("refresh_button"), goog.events.EventType.CLICK,
    function(e) {
      graph.render(taskDisplay);
    });
  
  goog.events.listen(goog.dom.getElement("new_quest_button"), goog.events.EventType.CLICK,
    function(e) {
      graph.insert_quest();
      graph.render(taskDisplay);
    });
}

goog.exportSymbol('playtolearn.QuestCanvas', playtolearn.QuestCanvas);
