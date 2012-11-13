
goog.provide('playtolearn.QuestCanvas');

goog.require('playtolearn.Graph');

playtolearn.QuestCanvas = function() {
  var graph = new playtolearn.Graph('canvas_id', 4, 6);
  graph.renderDom();
        
  $("#task_button").click(function(e) {
    if (graph.current_node()) {
      graph.current_node().set_text($("#task_name").val());
      //graph.render();
    }
  });
  
  $("#new_quest_button").click(function(e) {
    graph.insert_quest();
    graph.renderDom();
  });
}

goog.exportSymbol('playtolearn.QuestCanvas', playtolearn.QuestCanvas);
