goog.require('playtolearn.util.Table')
goog.require('playtolearn.Task');
goog.require('goog.dom');
goog.require('goog.style');

goog.provide('playtolearn.Quest');

playtolearn.Quest = function() {
  
  var task_levels = new Array();
  var x;
  var y;
  
  this.get_x = function() {
    return x;
  }
  
  this.get_y = function() {
    return y;
  }
  
  this.set_x = function(new_x) {
    x = new_x;
  }
  
  this.set_y = function(new_y) {
    y = new_y;
  }
  
  this.set_position = function(x, y) {
    this.set_x(x);
    this.set_y(y);
  }
  
  this.add_task = function(task) {
    for (var i = 0; i < task_levels.length; i++) {
      if (task.get_y() == task_levels[i][0].get_y()) {
        for (var j = 0; j < task_levels[i].length; j++) {
          if (task.get_x() == task_levels[i][j].get_x()) {
            return;
          }
        }
        task_levels[i].push(task);
        return;
      }
    }
    if (task_levels.length == 0 || task_levels[task_levels.length - 1][0].get_y() < task.get_y()) {
      task_levels.push(new Array());
      task_levels[task_levels.length - 1].push(task);
    }
  }
  
  this.get_width = function() {
    var largest_level = 1;
    for (var i = 0; i < task_levels.length; i++) {
      if (task_levels[i].length > largest_level) {
        largest_level = task_levels[i].length;
      }
    }
    return largest_level;
  }
  
  this.get_height = function() {
    return Math.max(2, task_levels.length);
  }
  
  this.get_render_width = function() {
    return this.get_width() * playtolearn.Task.SIZE + playtolearn.Quest.MARGIN*2;
  }
  
  this.get_render_height = function() {
    return this.get_height() * playtolearn.Task.SIZE + playtolearn.Quest.MARGIN*2; 
  }
  
  this.get_render_origin = function() {
    return [playtolearn.Quest.MARGIN + playtolearn.Task.SIZE / 2, playtolearn.Quest.MARGIN + playtolearn.Task.SIZE / 2];
  }
  
  this.render = function(canvas) {
    var ctx = canvas.getContext("2d");

    var largest_level = this.get_width();
    var num_levels = Math.max(2, task_levels.length);
    
    ctx.save();
    ctx.fillStyle = "rgba(0, 100, 0, 0.2)";
    ctx.fillRect(- playtolearn.Quest.MARGIN - playtolearn.Task.SIZE / 2, - playtolearn.Quest.MARGIN - playtolearn.Task.SIZE / 2, largest_level*playtolearn.Task.SIZE + playtolearn.Quest.MARGIN*2, playtolearn.Task.SIZE * num_levels + 2*playtolearn.Quest.MARGIN);
    ctx.restore();
    
    for (var i = 0; i < task_levels.length; i++) {
      for (var j = 0; j < task_levels[i].length; j++) {
        ctx.save();
        ctx.translate(- this.get_render_origin()[0], - this.get_render_origin()[1]);
        ctx.translate(playtolearn.Quest.MARGIN + j * playtolearn.Task.SIZE, playtolearn.Quest.MARGIN + i * playtolearn.Task.SIZE);
        task_levels[i][j].render(canvas);
        ctx.restore();
      }
    }
  }
  
  this.renderDom = function() {
    var obj = goog.dom.createDom("div", {'class' : 'quest', 'style' : 'padding: 5px; border: 1px solid black; background-color: red;'});
    for (var i = 0; i < task_levels.length; i++) {
      var level = obj;
      if (task_levels[i].length > 1) {
        level = goog.dom.createDom("div", {'class' : 'multi-quest', 'style' : 'margin: 5px; padding: 5px; border: 1px solid black; background-color: green;'});  
      }
      for (var j = 0; j < task_levels[i].length; j++) {
        var task = goog.dom.createDom("div", {'style' : 'margin:5px; border: 1px solid black; background-color: blue;'});
        if (task_levels[i].length > 1) {
          goog.style.setInlineBlock(task);
        }
        task.innerHTML = task_levels[i][j].get_text();
        goog.dom.append(level, task);
      }
      if (task_levels[i].length > 1) {
        goog.dom.append(obj, level);
      }
    }
    return obj;
  }
}

playtolearn.Quest.MARGIN = 20;
