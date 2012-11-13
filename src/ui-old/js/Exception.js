function Exception(msg) {
  Logging.log(Logging.Level.ERROR, msg);
  throw msg;
}