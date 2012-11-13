goog.provide('playtolearn.Graph');

goog.require('playtolearn.Quest');
goog.require('playtolearn.Task');


/**
 * [Graph description]
 * @constructor
 * @param {string} canvas_id [description]
 */
playtolearn.Graph = function(opt_domHelper) {
  goog.ui.Component.call(this, opt_domHelper);
}
goog.inherits(playtolearn.Graph, goog.ui.Component);

/**
 * Creates an initial DOM representation for the component.
 */
playtolearn.Graph.prototype.createDom = function() {
  this.decorateInternal(this.dom_.createElement('div'));
};


/**
 * Decorates an existing HTML DIV element as a SampleComponent.
 *
 * @param {Element} element The DIV element to decorate. The element's
 *    text, if any will be used as the component's label.
 */
playtolearn.Graph.prototype.decorateInternal = function(element) {
  playtolearn.Graph.superClass_.decorateInternal.call(this, element);

  var elem = this.getElement();
  goog.dom.classes.add(elem, goog.getCssName('playtolearn-graph'));
};


/** @override */
playtolearn.Graph.prototype.disposeInternal = function() {
  playtolearn.Graph.superClass_.disposeInternal.call(this);
};


/**
 * Called when component's element is known to be in the document.
 */
playtolearn.Graph.prototype.enterDocument = function() {
  playtolearn.Graph.superClass_.enterDocument.call(this);
};


/**
 * Called when component's element is known to have been removed from the
 * document.
 */
playtolearn.Graph.prototype.exitDocument = function() {
  playtolearn.Graph.superClass_.exitDocument.call(this);
};
