//
// Created by Ashe·Sun on 2019-02-01.
//

#ifndef MYSQL_VS_LOG_H
#define MYSQL_VS_LOG_H

#include "my_global.h"
#include <pthread.h>
//#include "auth/sql_security_ctx.h"

////////////////////////////////////////////////////////////
//
// Error Log
//
////////////////////////////////////////////////////////////
extern int log_error_level;

/**
   Prints a printf style error message to the error log.
   @see error_log_print
*/
void sql_print_error(const char *format, ...)
MY_ATTRIBUTE((format(printf, 1, 2)));

/**
   Prints a printf style warning message to the error log.
   @see error_log_print
*/
void sql_print_warning(const char *format, ...)
MY_ATTRIBUTE((format(printf, 1, 2)));

/**
   Prints a printf style information message to the error log.
   @see error_log_print
*/
void sql_print_information(const char *format, ...)
MY_ATTRIBUTE((format(printf, 1, 2)));

/**
   Prints a printf style message to the error log.
   The message is also sent to syslog and to the
   Windows event log if appropriate.

   @param level          The level of the msg significance
   @param format         Printf style format of message
   @param args           va_list list of arguments for the message
*/
void error_log_print(enum loglevel level, const char *format, va_list args)
MY_ATTRIBUTE((format(printf, 2, 0)));

/**
  Initialize structures (e.g. mutex) needed by the error log.

  @note This function accesses shared resources without protection, so
  it should only be called while the server is running single-threaded.

  @note The error log can still be used before this function is called,
  but that should only be done single-threaded.
*/
void init_error_log(int );

/**
  Open the error log and redirect stderr and optionally stdout
  to the error log file. The streams are reopened only for
  appending (writing at end of file).

  @note This function also writes any error log messages that
  have been buffered by calling flush_error_log_messages().

  @param filename        Name of error log file
*/
bool open_error_log(const char *filename);

/**
  Free any error log resources.

  @note This function accesses shared resources without protection, so
  it should only be called while the server is running single-threaded.

  @note The error log can still be used after this function is called,
  but that should only be done single-threaded. All buffered messages
  should be flushed before calling this function.
*/
void destroy_error_log();

/**
  Flush any pending data to disk and reopen the error log.
*/
bool reopen_error_log();

/**
  We buffer all error log messages that have been printed before the
  error log has been opened. This allows us to write them to the
  correct file once the error log has been opened.

  This function will explicitly flush buffered messages to stderr.
  It is only needed in cases where open_error_log() is not called
  as it otherwise will be done there.

  This function also turns buffering off (there is no way to turn
  buffering back on).
*/
void flush_error_log_messages();

////////////////////////////////////////////////////////////
//
// SysLog
//
////////////////////////////////////////////////////////////

/**
   DBA has changed syslog settings. Put them into effect!
*/
bool log_syslog_update_settings();

/**
   Translate a syslog facility name ("LOG_DAEMON", "local5", etc.)
   to its numeric value on the platform this mysqld was compiled for.
   Used for traditional unixoid syslog, harmless on systemd / Win
   platforms.
*/

bool log_syslog_init();
void log_syslog_exit();

#endif //MYSQL_VS_LOG_H
