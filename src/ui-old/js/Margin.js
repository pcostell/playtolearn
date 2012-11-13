goog.provide('playtolearn.Margin');

/**
 * Create a new margin object.
 * @param {} canvas The html5 canvas to draw the margin in.
 * @param {double} x      The x position of the mouse.
 * @param {double} y      The y position of the mouse.
 */
playtolearn.Margin = function(canvas, x, y) {

  /**
   * @private
   * @type {[type]}
   */
  this.canvas = canvas;
  /**
   * [canvas_ctx description]
   * @private
   * @type {[type]}
   */
  this.canvas_ctx = this.canvas.getContext("2d");
  
  /**
   * @private
   */
  this.pos = (function() {
    if (x < 20) {
      return 2;
    } 
    if (y < 20) {
      return 3;
    }
    if (x > canvas.width - 20) {
      return 0;
    }
    if (y > canvas.height - 20) {
      return 1;
    }
    return -1;
  })();

  /**
   * Returns the position of the playtolearn.Margin.
   * @return {int}
   */
  this.get_pos = function() { return this.pos; }
  
  /**
   * @return {Boolean} true if the position is valid
   */
  this.is_valid = function() { return this.pos >= 0; }
  
  /**
   * Draws a quarter circle in the quadrant given by dir. The directions are
   * defined as:
   *         2 | 3
   *          -+- 
   *         1 | 0
   * 
   * @private
   * @param  {} canvas_ctx the canvas context.
   * @param  {double} x          the x location of the corner of the circle
   * @param  {double} y          the y location of the corner of the circle
   * @param  {double} r          the radius of the circle
   * @param  {int} dir           the direction of the circle
   */
  this.drawQuarterCircle = function(canvas_ctx, x, y, r, dir) {
    var dirX = (1 - dir) * ((dir + 1) % 2);
    var dirY = (2 - dir) * (dir % 2);  
    
    this.canvas_ctx.beginPath();
    this.canvas_ctx.arc(x, y, r - canvas_ctx.lineWidth / 2, dir * Math.PI / 2, (dir + 1) * Math.PI /2);
    this.canvas_ctx.stroke();

    this.canvas_ctx.beginPath();
    this.canvas_ctx.moveTo(x, y);
    this.canvas_ctx.lineTo(x + dirX * r, y + dirY * r);
    this.canvas_ctx.arc(x, y, r - canvas_ctx.lineWidth / 2, dir * Math.PI / 2, (dir + 1) * Math.PI /2);
    this.canvas_ctx.lineTo(x, y);
    this.canvas_ctx.fill();
  }
}

/**
 * Renders the Margin object.
 */
playtolearn.Margin.prototype.render = function() {
  if (this.pos < 0) return;
  
  this.canvas_ctx.save();

  this.canvas_ctx.fillStyle = playtolearn.Margin.FILL_STYLE;
  this.canvas_ctx.strokeStyle = playtolearn.Margin.STROKE_STYLE;
  this.canvas_ctx.lineWidth = playtolearn.Margin.LINE_WIDTH;
        
  var nx = this.pos <= 1 ? this.canvas.width : 0;
  var ny = this.pos == 1 || this.pos == 2 ? this.canvas.height : 0;
  var width = this.pos % 2 == 0 ? this.canvas.height : this.canvas.width;
  var m = playtolearn.Margin.MARGIN - (playtolearn.Margin.LINE_WIDTH / 2.0);

  this.canvas_ctx.translate(nx, ny);
  this.canvas_ctx.rotate((this.pos+1) * Math.PI / 2);
  
  this.drawQuarterCircle(this.canvas_ctx, m, 0, m, 1);
  this.drawQuarterCircle(this.canvas_ctx, width - m, 0, m, 0);
  this.canvas_ctx.beginPath();
  this.canvas_ctx.moveTo(m, m - playtolearn.Margin.LINE_WIDTH / 2.0);
  this.canvas_ctx.lineTo(width - m, m - playtolearn.Margin.LINE_WIDTH / 2.0);
  this.canvas_ctx.stroke();
  this.canvas_ctx.fillRect(m, 0, width - 2*m, m);
  
  this.canvas_ctx.restore();
  
}

playtolearn.Margin.FILL_STYLE = "rgba(0, 0, 200, 0.4)";
playtolearn.Margin.STROKE_STYLE = "rgba(0, 0, 200, 0.9)";
playtolearn.Margin.MARGIN = 20;
playtolearn.Margin.LINE_WIDTH = 4;
  
  