goog.provide('playtolearn.Logging');

/**
 * Log the given message according to it's level.
 * @param  {Logging.Level} level the severity of the message
 * @param  {string} msg   the message
 */
Logging.log = function(level, msg) {
  if (level < Logging.LOG_LEVEL) {
    console.log(level.name + ": " + msg);
  }
  if (level < Logging.ALERT_LEVEL) {
    alert(level.name + ": " + msg);
  }
}

/**
 * Enum for determining the log level.
 * @Enum
 **/
Logging.Level = {
  ERROR : {value: 0, name: "Error"},
  WARN : {value: 1, name: "Warn"},
  INFO : {value: 2, name: "Info"}
}

/**
 * The message level to send to the log.
 * @define {Logging.level}
 **/
Logging.LOG_LEVEL = Logging.Level.INFO;

/**
 * The message level to send to an alert.
 * @define {Logging.Level}
 **/
Logging.ALERT_LEVEL = Logging.Level.ERROR;