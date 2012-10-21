  
  function Margin(canvas, x, y) {
    
    var FILL_STYLE = "rgba(0, 0, 200, 0.4)";
    var STROKE_STYLE = "rgba(0, 0, 200, 0.9)";
    var MARGIN = 20;
    var LINE_WIDTH = 4;
    
    var canvas_ctx = canvas.getContext("2d");
    var pos = (function() {
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

    this.get_pos = function() { return pos; }
    this.is_valid = function() { return pos >= 0; }
    
    /** Direction is defined:
      
              2 | 3
               -+- 
              1 | 0
    **/
    function drawQuarterCircle(canvas_ctx, x, y, r, dir) {
      var dirX = (1 - dir) * ((dir + 1) % 2);
      var dirY = (2 - dir) * (dir % 2);  
      
      canvas_ctx.beginPath();
      canvas_ctx.arc(x, y, r - canvas_ctx.lineWidth / 2, dir * Math.PI / 2, (dir + 1) * Math.PI /2);
      canvas_ctx.stroke();
      
      canvas_ctx.beginPath();
      canvas_ctx.moveTo(x, y);
      canvas_ctx.lineTo(x + dirX * r, y + dirY * r);
      canvas_ctx.arc(x, y, r - canvas_ctx.lineWidth / 2, dir * Math.PI / 2, (dir + 1) * Math.PI /2);
      canvas_ctx.lineTo(x, y);
      canvas_ctx.fill();
    }
    
    this.render = function() {
      if (pos < 0) return;
      
      canvas_ctx.save();
            
      canvas_ctx.fillStyle = FILL_STYLE;
      canvas_ctx.strokeStyle = STROKE_STYLE;
      canvas_ctx.lineWidth = LINE_WIDTH;
            
      var nx = pos <= 1 ? canvas.width : 0;
      var ny = pos == 1 || pos == 2 ? canvas.height : 0;
      var width = pos % 2 == 0 ? canvas.height : canvas.width;
      var m = MARGIN - (LINE_WIDTH / 2.0);
    
      canvas_ctx.translate(nx, ny);
      canvas_ctx.rotate((pos+1) * Math.PI / 2);
      
      drawQuarterCircle(canvas_ctx, m, 0, m, 1);
      drawQuarterCircle(canvas_ctx, width - m, 0, m, 0);
      canvas_ctx.beginPath();
      canvas_ctx.moveTo(m, m - LINE_WIDTH / 2.0);
      canvas_ctx.lineTo(width - m, m - LINE_WIDTH / 2.0);
      canvas_ctx.stroke();
      canvas_ctx.fillRect(m, 0, width - 2*m, m);
      
      canvas_ctx.restore();
      
    }
  }
  
  