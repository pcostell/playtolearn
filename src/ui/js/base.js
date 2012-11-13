goog.provide('playtolearn.base');

var root_ = null;
playtolearn.base.getDrawingRoot = function() {
  return root_;
}
playtolearn.base.setDrawingRoot = function(root) {
  root_ = root;
}

playtolearn.base.decorator = function(childCtor, parentCtor) {
  if (!parentCtor || !parentCtor.prototype) {
    throw Error('You cannot add an undefined decorator.');
  }
  if (!childCtor.decorators_) {
    childCtor.decorators_ = new Array();
  }
  childCtor.decorators_.push(parentCtor.prototype);
  if (parentCtor.interfaces_) {
    for (var i in parentCtor.interfaces_) {
      playtolearn.base.interface(childCtor, parentCtor.interfaces_[i]);
    }
  }
}

playtolearn.base.inherits = function(childCtor, parentCtor) {
  goog.inherits(childCtor, parentCtor);
}

playtolearn.base.interface = function(ctor, interfaceCtor) {
  if (!ctor.interfaces_) {
    ctor.interfaces_ = new Array();
  }
  ctor.interfaces_.push(interfaceCtor);
  for (var x in interfaceCtor.prototype) {
    if (! ctor.prototype[x]) {
      ctor.prototype[x] = interfaceCtor.prototype[x];
    }
  }
}

playtolearn.base.super = function(me, opt_methodName, var_args) {
  var caller = arguments.callee.caller;
  if (caller.superClass_) {
    // This is a constructor. Call the superclass constructor.
    var ret = caller.superClass_.constructor.apply(
        me, Array.prototype.slice.call(arguments, 1));
    if (me.constructor.decorators_) {
      for(var i in me.constructor.decorators_) {
        me.constructor.decorators_[i].constructor.apply(me);
        for (var x in me.constructor.decorators_[i].prototype) {
          if (! me.constructor.prototype[x]) {
            me.constructor.prototype[x] = function() { playtolearn.base.super(me, x, Array.prototype.slice.call(arguments, 2)); }
          }
        }
      }
    }
    return ret;
  }

  var args = Array.prototype.slice.call(arguments, 2);
  var foundCaller = false;
  for (var ctor = me.constructor;
       ctor; ctor = ctor.superClass_ && ctor.superClass_.constructor) {
    if (ctor.prototype[opt_methodName] === caller) {
      foundCaller = true;
    } else if (foundCaller) {
      var ret = ctor.prototype[opt_methodName].apply(me, args);
      if (me.constructor.decorators_) {
        for(var i in me.constructor.decorators_) {
          if (me.constructor.decorators_[i][opt_methodName]) {
            me.constructor.decorators_[i][opt_methodName].apply(me, args);
          }
        }
      }
      return ret;
    }
  }

  // If we did not find the caller in the prototype chain,
  // then one of two things happened:
  // 1) The caller is an instance method.
  // 2) This method was not called by the right caller.
  if (me[opt_methodName] === caller) {
    var ret = me.constructor.prototype[opt_methodName].apply(me, args);
    if (me.constructor.decorators_) {
      for(var i in me.constructor.decorators_) {
        if (me.constructor.decorators_[i][opt_methodName]) {
          me.constructor.decorators_[i][opt_methodName].apply(me, args);
        }
      }
    }
    return ret;
  } else {
    throw Error(
        'playtolearn.base.super called from a method of one name ' +
        'to a method of a different name');
  }
}

