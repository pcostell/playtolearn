<html>
  <head>
    <title>Quests</title>
    <script type="text/javascript" src="js/Graph.js" />
    <script type="text/javascript" src="../../external/jquery/build/release.js" />
    <script type="text/javascript">
      var graph;
      $("canvas_id").load(function() {
        graph = new Graph($("canvas_id"));
      })
      $("canvas_id").click(function(e){
        var x = e.pageX - this.offsetLeft;
        var y = e.pageY - this.offsetTop;
        graph.add_node(x, y);
      }
    </script>
  </head>
  <body>
    <canvas id="canvas_id" width="600px" height="800px" style="border:1px solid black;" />
  </body>
</html>