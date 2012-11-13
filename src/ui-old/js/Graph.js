goog.provide('playtolearn.Graph');

goog.require('playtolearn.Quest');
goog.require('playtolearn.Task');
goog.require('playtolearn.Margin');

playtolearn.Graph = function(canvas_id, grid_x, grid_y) {
  
  /** Instance variables **/
  /*var grid = [grid_x, grid_y];
  var curr_margin = null;
  var canvas = $('#' + canvas_id).get(0);
  var canvas_ctx = canvas.getContext("2d");
  var grid_size = [canvas.width/grid[0], canvas.height/grid[1]];
  var mouse_x = -1;
  var mouse_y = -1;
  */
   var nodes = new Array();
  var curr_item = null;

  /** Private functions. **/
  var distance = function(p1, p2) {
    var x = p1[0] - p2[0];
    var y = p1[1] - p2[1];
    return Math.sqrt(x*x + y*y);
  }
  
  var get_closest_grid = function(x, y) {
    var dx = (canvas.width)/grid[0];
    var dy = (canvas.height)/grid[1];
    min_pt = [0, 0];
    min_dist = -1;
    // Measure distance to center of grid square, but the resulting value should
    // be the top-left corner of the square.
    for (grid_x = dx/2; grid_x < canvas.width; grid_x += dx) {
      for (grid_y = dy/2; grid_y < canvas.height; grid_y += dy) {
        var d = distance([x, y], [grid_x, grid_y]);
        if(min_dist < 0 || d < min_dist) {
          min_pt = [(grid_x - dx/2) / dx, (grid_y - dy/2) / dy];
          min_dist = d;
        }
      }
    }
    return min_pt;
  }
  
  /** Protected methods. **/
  
  this.mouse_move = function(x, y) {
    curr_margin = null;
    var margin = new playtolearn.Margin(canvas, x, y);
    if (margin.is_valid()) {
      curr_margin = margin;
    }
    if (curr_item) {
      curr_item.set_position(x, y);
    }
    mouse_x = x;
    mouse_y = y;
    this.render();
  }
  
  this.mouse_click = function(x, y) {
    var dx = (canvas.width)/grid[0];
    var dy = (canvas.height)/grid[1];
    if (curr_margin && curr_margin.is_valid()) {
      if(curr_margin.get_pos() == 0) {
        canvas.width += canvas.width / grid[0];
        grid[0]++;
      } else if (curr_margin.get_pos() == 1) {
        canvas.height += canvas.height / grid[1];
        grid[1]++;
      } else if (curr_margin.get_pos() == 2) {
        canvas.width += canvas.width / grid[1];
        for(var i = 0; i < nodes.length; i++) {
          nodes[i].set_x(nodes[i].get_x() + 1);
        }
        grid[0]++;
      } else if (curr_margin.get_pos() == 3) {
        canvas.height += canvas.height / grid[1];
        for(var i = 0; i < nodes.length; i++) {
          nodes[i].set_y(nodes[i].get_y() + 1);
        }
        grid[1]++;
      }
      curr_margin = null;
    } else if (curr_item) {
      this.add_node(curr_item);
      curr_item = null;
    } else {
      for (var i = 0; i < nodes.length; i++) {
        var xpos = nodes[i].get_x() * grid_size[0];
        var ypos = nodes[i].get_y() * grid_size[1];
        var xpos2 = xpos + nodes[i].get_width() * grid_size[0];
        var ypos2 = ypos + nodes[i].get_height() * grid_size[1];
        if (x > xpos && x < xpos2 && y > ypos && y < ypos2) {
          var task = new playtolearn.Task('hi', x, y);
          if (grid) {
            var pos = get_closest_grid(task.get_x(), task.get_y());
            task.set_x(pos[0]);
            task.set_y(pos[1]);
          }
          nodes[i].add_task(task);
        }
      }
    }
    mouse_x = x;
    mouse_y = y;
    this.render();
  }
  
  this.mouse_out = function() {
    curr_margin = null;
    this.render();
  }
  
  this.insert_quest = function() {
    curr_item = new playtolearn.Quest();
    curr_item.add_task(new playtolearn.Task("hi", 1, 1));
    curr_item.add_task(new playtolearn.Task("ok.", 1, 2));
    curr_item.add_task(new playtolearn.Task("no.", 2, 1));
    curr_item.set_x(1);
    curr_item.set_y(1);
    nodes.push(curr_item);
  }

  this.render = function() {
    canvas_ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (var i = 0; i < grid[0]; i++) {
      canvas_ctx.beginPath();
      canvas_ctx.moveTo(i * grid_size[0], 0);
      canvas_ctx.lineTo(i * grid_size[0], canvas.height);
      canvas_ctx.stroke();
    }
    for (var i = 0; i < grid[1]; i++) {
      canvas_ctx.beginPath();
      canvas_ctx.moveTo(0, i * grid_size[1]);
      canvas_ctx.lineTo(canvas.width, i * grid_size[1]);
      canvas_ctx.stroke(); 
    }
    for (var i = 0; i < nodes.length; i++) {
      canvas_ctx.save();
      var xscale = nodes[i].get_width() * grid_size[0] / nodes[i].get_render_width();
      var yscale = nodes[i].get_height() * grid_size[1] / nodes[i].get_render_height();
      var xtrans = nodes[i].get_x() * grid_size[0] + nodes[i].get_render_origin()[0] * xscale;
      var ytrans = nodes[i].get_y() * grid_size[1] + nodes[i].get_render_origin()[1] * yscale;
      canvas_ctx.translate(xtrans, ytrans);
      canvas_ctx.scale(xscale, yscale);
      nodes[i].render(canvas);
      canvas_ctx.restore();
    }
    if (curr_margin) {
      curr_margin.render();
    }
    if (curr_item) {
      canvas_ctx.save();
      canvas_ctx.translate(mouse_x, mouse_y);
      canvas_ctx.scale(curr_item.get_width() * grid_size[0] / curr_item.get_render_width(), curr_item.get_height() * grid_size[1] / curr_item.get_render_height());
      curr_item.render(canvas);
      canvas_ctx.restore();
    }
  }
  
  this.renderDom = function() {
    var d = goog.dom.getElement('dom_canvas');
    goog.dom.removeChildren(d);
    for (var i = 0; i < nodes.length; i++) {
      goog.dom.append(d, nodes[i].renderDom());
    }
  }
  
  this.add_node = function(node) {
    if (grid) {
      var pos = get_closest_grid(node.get_x(), node.get_y());
      node.set_x(pos[0]);
      node.set_y(pos[1]);
    }
    nodes.push(node);
  }

  /** Constructor **/
  var that = this;
  
  $('#' + canvas_id).click(function(e){
    var x = e.pageX - this.offsetLeft;
    var y = e.pageY - this.offsetTop;
    that.mouse_click(x, y);
  });
  
  $('#' + canvas_id).mousemove(function(e) {
    var x = e.pageX - this.offsetLeft;
    var y = e.pageY - this.offsetTop;
    that.mouse_move(x, y);
  });
  
  $('#' + canvas_id).mouseout(function(e) {
    that.mouse_out();
  });
}
