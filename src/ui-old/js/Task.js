goog.provide('playtolearn.Task')

playtolearn.Task = function(text, x, y) {

  this.set_x = function(new_x) {
    x = new_x;
  }
  
  this.get_x = function() {
    return x;
  }
  
  this.set_y = function(new_y) {
    y = new_y;
  }
  
  this.get_y = function() {
    return y;
  }
  
  this.set_text = function(new_text) {
    text = new_text;
  }
  
  this.get_text = function() {
    return text;
  }
  
  this.set_position = function(new_x, new_y) {
    x = new_x;
    y = new_y;
  }
  
  this.render = function(canvas) {
    var ctx = canvas.getContext("2d");
    
    ctx.save();
    ctx.fillStyle="rgba(0,0,100, 0.1)";
    ctx.fillRect(0, 0, playtolearn.Task.SIZE, playtolearn.Task.SIZE);
    ctx.fillStyle="rgb(0,0,0)";
    ctx.font="12px Arial";
    ctx.fillText(text, 0, playtolearn.Task.SIZE);
    ctx.restore();
  }
}

/**
 * The size of a task block.
 * @const
 * @type {int}
 */
playtolearn.Task.SIZE = 40;