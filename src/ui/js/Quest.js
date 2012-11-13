goog.provide('playtolearn.Quest');

goog.require('playtolearn.base');
goog.require('playtolearn.component.SideBarComponent');
goog.require('playtolearn.component.DragDropTargetComponent');
goog.require('playtolearn.component.SelectableComponent');

goog.require('goog.dom');
goog.require('goog.style');
goog.require('goog.ui.Component');
goog.require('goog.fx.Dragger');

var questID = 0;
/**
 * [Quest description]
 * @constructor
 */
playtolearn.Quest = function(opt_domHelper) {
  goog.base(this, opt_domHelper);
  
  /**
   *  [id description]
   *  @private
   *  @type {number}
   */
  this.id = questID++;
  this.questName_ = "New Quest";
  this.taskDom_ = null;
  this.label_ = null;

}
playtolearn.base.inherits(playtolearn.Quest, goog.ui.Component);
playtolearn.base.decorator(playtolearn.Quest, playtolearn.component.SideBarComponent);
playtolearn.base.decorator(playtolearn.Quest, playtolearn.component.SelectableComponent);

/**
 * Creates an initial DOM representation for the component.
 */
playtolearn.Quest.prototype.createDom = function() {
  this.decorateInternal(this.dom_.createElement('div'));
};


/**
 * Decorates an existing HTML DIV element as a SampleComponent.
 *
 * @param {Element} element The DIV element to decorate. The element's
 *    text, if any will be used as the component's label.
 */
playtolearn.Quest.prototype.decorateInternal = function(element) {
  playtolearn.base.super(this, "decorateInternal", element);
  
  goog.dom.classes.add(this.getElement(), goog.getCssName('playtolearn-quest'));
};


/** @override */
playtolearn.Quest.prototype.disposeInternal = function() {
  playtolearn.base.super(this, "disposeInternal");
};

playtolearn.Quest.prototype.getWidth = function(ctx, font, name) {
  ctx.font = font;
  var metrics = ctx.measureText(name);
  return metrics.width; 
}

playtolearn.Quest.prototype.getFont = function() {
  return goog.style.getFontSize(this.getElement()) + " " + goog.style.getFontFamily(this.getElement());
}

playtolearn.Quest.prototype.generateLabel = function() {
  if (this.label_ == null) {
    this.label_ = goog.dom.createElement('canvas');
    goog.dom.classes.add(this.label_, goog.getCssName('playtolearn-quest-name'));
  }
  var font = this.getFont();
  var ctx = this.label_.getContext('2d');
  this.label_.height = this.getWidth(ctx, this.getFont(), this.questName_) + 20;
  this.label_.width = goog.style.getFontSize(this.getElement()) + 20;
  ctx = this.label_.getContext('2d');
  ctx.save();
  ctx.clearRect(0, 0, this.label_.width, this.label_.height);
  ctx.font = this.getFont();
  ctx.textAlign = 'center';
  ctx.fillStyle = goog.style.getComputedStyle(this.getElement(), "color");
  ctx.translate(this.label_.width/2, this.label_.height/2);  
  ctx.rotate(-Math.PI/2);
  ctx.fillText(this.questName_, 0, 0);
  ctx.restore();
  return this.label_;
}

playtolearn.Quest.prototype.getName = function() {
  return this.questName_; 
}

playtolearn.Quest.prototype.setName = function(name) {
  this.questName_ = name;
  this.generateLabel();
}

playtolearn.Quest.prototype.showTasks = function(hide) {
  goog.style.showElement(this.taskDom_, hide);
}

/**
 * Called when component's element is known to be in the document.
 */
playtolearn.Quest.prototype.enterDocument = function() {
  playtolearn.base.super(this, "enterDocument");
  
  var elem = this.getElement();
  goog.dom.append(elem, this.generateLabel());
  this.taskDom_ = goog.dom.createElement('div');
  goog.dom.classes.add(this.taskDom_, goog.getCssName('playtolearn-quest-tasks'));
  goog.dom.append(elem, this.taskDom_);
  this.addChildAt(new playtolearn.TemporaryQuestLevel(), 0, true);
  
  var dragger = new goog.fx.Dragger(this.getElement()); 
  dragger.defaultAction = function(x, y) {
    goog.style.setPosition(this.target, null, y - (y % 70) + 10);
  }
  this.showTasks(false);
};

playtolearn.Quest.prototype.onSelected = function() {
  this.showTasks(true);
}


playtolearn.Quest.prototype.onUnselected = function() {
  this.showTasks(false);
}

playtolearn.Quest.prototype.addChild = function(elem, opt_render) {
  
  this.addChildAt(elem, this.getChildCount() - 1, opt_render);
}

playtolearn.Quest.prototype.getContentElement = function() {
  return this.taskDom_;
}

/**
 * Called when component's element is known to have been removed from the
 * document.
 */
playtolearn.Quest.prototype.exitDocument = function() {
  playtolearn.Quest.superClass_.exitDocument.call(this);
};

playtolearn.Quest.prototype.getProperties = function() {
  return ['Name'];
}

/**
 * [Quest description]
 * @constructor
 */
playtolearn.QuestLevel = function(opt_domHelper) {
  playtolearn.base.super(this, opt_domHelper);
}
playtolearn.base.inherits(playtolearn.QuestLevel, goog.ui.Component);
playtolearn.base.decorator(playtolearn.QuestLevel, playtolearn.component.DragDropTargetComponent);
//goog.inherits(playtolearn.QuestLevel, playtolearn.base.DragDropTargetComponent);

/**
 * Creates an initial DOM representation for the component.
 */
playtolearn.QuestLevel.prototype.createDom = function() {
  this.decorateInternal(this.dom_.createElement('div'));
};


/**
 * Decorates an existing HTML DIV element as a SampleComponent.
 *
 * @param {Element} element The DIV element to decorate. The element's
 *    text, if any will be used as the component's label.
 */
playtolearn.QuestLevel.prototype.decorateInternal = function(element) {
  playtolearn.base.super(this, "decorateInternal", element);

  var elem = this.getElement();
  goog.dom.classes.add(elem, goog.getCssName('playtolearn-quest-level'));
};

playtolearn.QuestLevel.prototype.enterDocument = function() {
  playtolearn.base.super(this, "enterDocument");
};

playtolearn.QuestLevel.prototype.removeChild = function(child, opt_unrender) {
  playtolearn.base.super(this, "removeChild", child, opt_unrender);
  if (this.getChildCount() == 0) {
    this.getParent().removeChild(this, true);
  }
};

playtolearn.QuestLevel.prototype.removeChildAt = function(index, opt_unrender) {
  playtolearn.base.super(this, "removeChildAt", index, opt_unrender);
  if (this.getChildCount() == 0) {
    this.getParent().removeChild(this, true);
  }
};

playtolearn.TemporaryQuestLevel = function(opt_domHelper) {
  playtolearn.base.super(this, opt_domHelper);
};

playtolearn.base.inherits(playtolearn.TemporaryQuestLevel, goog.ui.Component);
playtolearn.base.decorator(playtolearn.TemporaryQuestLevel, playtolearn.component.DragDropTargetComponent);

/**
 * Creates an initial DOM representation for the component.
 */
playtolearn.TemporaryQuestLevel.prototype.createDom = function() {
  this.decorateInternal(this.dom_.createElement('div'));
};

/**
 * Decorates an existing HTML DIV element as a SampleComponent.
 *
 * @param {Element} element The DIV element to decorate. The element's
 *    text, if any will be used as the component's label.
 */
playtolearn.TemporaryQuestLevel.prototype.decorateInternal = function(element) {
  playtolearn.base.super(this, "decorateInternal", element);
  var elem = this.getElement();
  goog.dom.classes.add(elem, goog.getCssName('playtolearn-temporary-quest-level'));
};

playtolearn.TemporaryQuestLevel.prototype.enterDocument = function() {
  playtolearn.base.super(this, "enterDocument");
}

playtolearn.TemporaryQuestLevel.prototype.onDrop = function(e) {
  var newQuestLevel = new playtolearn.QuestLevel();
  this.getParent().addChild(newQuestLevel, true);
  e.dropTargetItem.data = newQuestLevel;
  newQuestLevel.onDrop(e);
  goog.dom.classes.addRemove(this.getElement(), 
    goog.getCssName('playtolearn-quest-level'), 
    goog.getCssName('playtolearn-temporary-quest-level'));
}

playtolearn.TemporaryQuestLevel.prototype.onDragOver = function(e) {
  goog.dom.classes.addRemove(this.getElement(), 
      goog.getCssName('playtolearn-temporary-quest-level'), 
      goog.getCssName('playtolearn-quest-level'));
}

playtolearn.TemporaryQuestLevel.prototype.onDragOut = function(e) {
  goog.dom.classes.addRemove(this.getElement(), 
      goog.getCssName('playtolearn-quest-level'), 
      goog.getCssName('playtolearn-temporary-quest-level'));
}

playtolearn.NewQuestLevel = function(opt_domHelper) {
  playtolearn.base.super(this, opt_domHelper);
};

playtolearn.base.inherits(playtolearn.NewQuestLevel, goog.ui.Component);
playtolearn.base.decorator(playtolearn.NewQuestLevel, playtolearn.component.DragDropTargetComponent);
/**
 * Creates an initial DOM representation for the component.
 */
playtolearn.NewQuestLevel.prototype.createDom = function() {
  this.decorateInternal(this.dom_.createElement('div'));
};

/**
 * Decorates an existing HTML DIV element as a SampleComponent.
 *
 * @param {Element} element The DIV element to decorate. The element's
 *    text, if any will be used as the component's label.
 */
playtolearn.NewQuestLevel.prototype.decorateInternal = function(element) {
  playtolearn.base.super(this, "decorateInternal", element);
  var elem = this.getElement();
  goog.dom.classes.add(elem, goog.getCssName('playtolearn-new-quest-level'));
};

playtolearn.NewQuestLevel.prototype.enterDocument = function() {
  playtolearn.base.super(this, "enterDocument");
  var task = new playtolearn.Task("New Task");
  this.addChild(task, true);
}

playtolearn.NewQuestLevel.prototype.removeChild = function(child, opt_unrender) {
  playtolearn.base.super(this, "removeChild", child, opt_unrender);
  var task = new playtolearn.Task("New Task");
  this.addChild(task, true);
}

/**
 * Intentionally blank. We don't want users to be able to drop Tasks into a NewQuestLevel.
 * @param  {[type]} e [description]
 * @return {[type]}   [description]
 */
playtolearn.NewQuestLevel.prototype.onDrop = function(e) {}


