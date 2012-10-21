function Graph(canvas_id, grid_x, grid_y) {
  
  /** Instance variables **/
  var grid = [grid_x + 1, grid_y + 1];
  var curr_margin = null;
  var canvas = $('#' + canvas_id).get(0);
  var canvas_ctx = canvas.getContext("2d");
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
    for (grid_x = dx; grid_x < canvas.width; grid_x += dx) {
      for (grid_y = dy; grid_y < canvas.height; grid_y += dy) {
        var d = distance([x, y], [grid_x, grid_y]);
        if(min_dist < 0 || d < min_dist) {
          min_pt = [grid_x, grid_y];
          min_dist = d;
        }
      }
    }
    return min_pt;
  }
  
  /** Protected methods. **/
  
  this.current_node = function() {
    if (nodes.length == 0) {
      return null;
    }
    return nodes[nodes.length - 1];
  }
  
  this.mouse_move = function(x, y) {
    curr_margin = null;
    var margin = new Margin(canvas, x, y);
    if (margin.is_valid()) {
      curr_margin = margin;
    }
    if (curr_item) {
      curr_item.set_position(x, y);
    }
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
          nodes[i].set_x(nodes[i].get_x() + dx);
        }
        grid[0]++;
      } else if (curr_margin.get_pos() == 3) {
        canvas.height += canvas.height / grid[1];
        for(var i = 0; i < nodes.length; i++) {
          nodes[i].set_y(nodes[i].get_y() + dy);
        }
        grid[1]++;
      }
      curr_margin = null;
    } else if (curr_item) {
      this.add_node(curr_item);
      curr_item = null;
    }
    this.render(canvas);
  }
  
  this.mouse_out = function() {
    curr_margin = null;
    this.render();
  }
  
  this.insert_quest = function() {
    curr_item = new Node("hi", 0, 0);
  }
  
  this.render = function() {
    canvas_ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (var i = 0; i < nodes.length; i++) {
      nodes[i].render(canvas);
    }
    if (curr_margin) {
      curr_margin.render();
    }
    if (curr_item) {
      curr_item.render(canvas);
    }
    canvas_ctx.restore();
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