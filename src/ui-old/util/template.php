
class Template {
  var $file;
  var $vars;
  
  function __get($arg) {
    return $this->vars[$arg];
  }
  
  function __construct($file, $vars = array()) {
    $this->file = $file;
    $this->vars = $vars;
  }
  
  function render() {
    extract($this->vars);
    include $this->file;
  }
}