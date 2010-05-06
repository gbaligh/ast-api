/*
 * libast-api - library for using Asterisk Manager API.
 * Copyright (C) 2010 Baligh GUESMI
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 *   along with libast-api.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include <stdio.h>


#include "astman.h"
#include "astlog.h"

//*** MSGBUF macros ***
struct msgbuf {
  struct message *msg;
  int count;
  int len;
};

#define MSGBUF_INIT(L)	\
  struct msgbuf _buf; \
  _buf.msg = (struct message *)calloc(L, sizeof(struct message)); \
  _buf.count = 0; \
  _buf.len = L; \
  if (!_buf.msg) return ASTMAN_FAILURE;

#define MSGBUF_ADD(M)	\
  memcpy(_buf.msg+_buf.count, M, sizeof(struct message)); \
  _buf.count++; \
  if (_buf.count >= _buf.len) { \
    _buf.msg = (struct message *)realloc(_buf.msg, _buf.len * 2 * sizeof(struct message)); \
    memset(_buf.msg+_buf.len, 0, _buf.len * sizeof(struct message)); \
    _buf.len *= 2; \
  }

#define MSGBUF_MSG _buf.msg;

/**
 * @fn astman_originate(struct mansession *s, struct message *m,
 *		     char *channel,
 *		     char *exten, char *context, int priority,
 *		     char *application, char *data,
 *		     int timeout,
 *		     char *callerid,
 *		     char *variable,
 *		     char *account,
 *		     int async,
 *		     char *actionid)
 * @brief Originate
 *          Generates an outgoing call to a Extension/Context/Priority or
 *          Application/Data
 *
 *  @param Channel: Channel name to call(required)
 *  @param Exten: Extension to use (requires 'Context' and 'Priority')
 *  @param Context: Context to use (requires 'Exten' and 'Priority')
 *  @param Priority: Priority to use (requires 'Exten' and 'Context')
 *  @param Application: Application to use
 *  @param Data: Data to use (requires 'Application')
 *  @param Timeout: How long to wait for call to be answered (in ms)
 *  @param CallerID: Caller ID to be set on the outgoing channel
 *  @param Variable: Channel variable to set, multiple Variable: headers are allowed
 *  @param Account: Account code
 *  @param Async: Set to 'true' for fast origination
 */
int astman_originate(struct mansession *s, struct message *m,
		     char *channel,
		     char *exten, char *context, int priority,
		     char *application, char *data,
		     int timeout,
		     char *callerid,
		     char *variable,
		     char *account,
		     int async,
		     char *actionid) {
  int res;
  char params[MAX_LEN*12] = "";
  char strbuf[12];

  if (astman_strlen_zero(channel))
    return ASTMAN_FAILURE;

  if (!astman_strlen_zero(exten) && !astman_strlen_zero(context) &&
      priority > 0 ) {
    astman_add_param(params, sizeof(params), "Exten", exten);
    astman_add_param(params, sizeof(params), "Context", context);
    snprintf(strbuf, sizeof(strbuf), "%d", priority);
    astman_add_param(params, sizeof(params), "Priority", strbuf);
  } else if (astman_add_param(params, sizeof(params), "Application", data) > 0) {
    astman_add_param(params, sizeof(params), "Data", data);
  } else {
    return ASTMAN_FAILURE;
  }

  if (timeout > 0) {
    snprintf(strbuf, sizeof(strbuf), "%d", timeout);
    astman_add_param(params, sizeof(params), "Timeout", strbuf);
  }
  astman_add_param(params, sizeof(params), "Channel", channel);
  astman_add_param(params, sizeof(params), "CallerId", callerid);
  astman_add_param(params, sizeof(params), "Variable", variable);
  astman_add_param(params, sizeof(params), "Account", account);
  astman_add_param(params, sizeof(params), "Async", (async)?"true":"false");
  astman_add_param(params, sizeof(params), "ActionId", actionid);
  astman_manager_action_params(s, "Originate", params);

  res = astman_wait_for_response(s, m, 0);
  if ( res > 0 && response_is(m, "Success")) {
      return res;
  }
  return ASTMAN_FAILURE;
}

/**
 * @fn astman_ping(struct mansession *s, struct message *m, char *actionid)
 * @brief Ping
 *      A 'Ping' action will ellicit a 'Pong' response.  Used to keep
 *      the manager connection open.
 * @param m:
 * @param actionid:
 * @param s:
 */
int astman_ping(struct mansession *s, struct message *m, char *actionid) {
  int res;
  char params[MAX_LEN] = "";

  astman_add_param(params, sizeof(params), "ActionId", actionid);

  astman_manager_action_params(s, "Ping", params);
  res = astman_wait_for_response(s, m, 0);
  if ( res > 0 && response_is(m, "Pong")) {
    return res;
  }
  return ASTMAN_FAILURE;
}

/**
 * Command
 *  Execute CLI Command
 */
int astman_command(struct mansession *s, struct message *m,
		   char *command,
		   char *actionid) {
  int res;
  char params[MAX_LEN] = "";

  if (astman_strlen_zero(command))
    return ASTMAN_FAILURE;

  astman_add_param(params, sizeof(params), "ActionId", actionid);

  astman_manager_action(s, "Command", "Command: %s\r\n%s", command, params);
  res = astman_wait_for_response(s, m, 0);
  if ( res > 0 && response_is(m, "Follows")) {
    return res;
  }
  return ASTMAN_FAILURE;
}

static int astman_queues_callback(struct mansession *s, struct message *m) {
  char event[80];
  strncpy(event, astman_get_header(m, "Event"), sizeof(event));

  if (!strcasecmp(event, "QueueParams") ||
      !strcasecmp(event, "QueueMember") ||
      !strcasecmp(event, "QueueEnter")  ||
      !strcasecmp(event, "QueueStatusComplete")) {
    return 1; /* return wait_for_answer() */
  }
  return 0;
}

/**
 * QueueStatus
 *  Queue, queue member and queued calls status
 */
int astman_queuestatus(struct mansession *s, struct message **m,
		       char *actionid) {
  int res;
  char params[MAX_LEN] = "";
  char event[80];
  struct message msg;

  MSGBUF_INIT(1);

  astman_add_event_handler_system(s, astman_queues_callback);

  astman_add_param(params, sizeof(params), "ActionId", actionid);
  astman_manager_action_params(s, "QueueStatus", params);
  res = astman_wait_for_response(s, &msg, 0);

  if ( res > 0 && response_is(&msg, "Success")) {
    for(;;) {
      res = astman_wait_for_response(s, &msg, 0);
      if ( res > 0 ) {
	strncpy(event, astman_get_header(&msg, "Event"), sizeof(event));

	if (!strcasecmp(event, "QueueParams") ||
	    !strcasecmp(event, "QueueMember") ||
	    !strcasecmp(event, "QueueEnter")) {

	  MSGBUF_ADD(&msg);

	} else if (!strcasecmp(event, "QueueStatusComplete")) {
	  *m = MSGBUF_MSG;
	  astman_add_event_handler_system(s, NULL);
	  return ASTMAN_SUCCESS;
	}
      } else {
	goto out;
      }
    } /* infinity loop */
  }

  out:
    astman_add_event_handler_system(s, NULL);
    return ASTMAN_FAILURE;
}

/**
 * \fn astman_absolutetimeout(struct mansession *s, struct message *m,
 *                          char *channel,
 *                          int timeout,
 *                          char *actionid)
 * \brief AbsoluteTimeout
 *          Hangup a channel after a certain time.
 *
 * \param OUT Channel: Channel name to hangup
 * \param OUT Timeout: Maximum duration of the call (sec)
 */
int astman_absolutetimeout(struct mansession *s, struct message *m,
                           char *channel,
                           int timeout,
                           char *actionid) {
  int res;
  char params[MAX_LEN] = "";
  char strtimeout[12] = "";

  if (astman_strlen_zero(channel))
    return ASTMAN_FAILURE;

  if (timeout>0) {
    snprintf(strtimeout, sizeof(strtimeout), "%d", timeout);
  } else {
    return ASTMAN_FAILURE;
  }

  astman_add_param(params, sizeof(params), "Channel", channel);
  astman_add_param(params, sizeof(params), "Timeout", strtimeout);
  astman_add_param(params, sizeof(params), "ActionId", actionid);

  astman_manager_action_params(s, "AbsoluteTimeout", params);
  res = astman_wait_for_response(s, m, 0);
  if ( res > 0 && response_is(m, "Success")) {
    return res;
  }
  return ASTMAN_FAILURE;
}

static int astman_status_callback(struct mansession *s, struct message *m) {
  char event[80];
  strncpy(event, astman_get_header(m, "Event"), sizeof(event));

  if (!strcasecmp(event, "Status")  ||
      !strcasecmp(event, "StatusComplete")) {
    return 1; /* return wait_for_answer() */
  }
  return 0;
}

/**
 * Status
 *   Lists channel status
 */
int astman_status(struct mansession *s, struct message **m,
                  char *actionid) {
  int res;
  char params[MAX_LEN] = "";
  char event[80];
  struct message msg;

  MSGBUF_INIT(1);

  astman_add_event_handler_system(s, astman_status_callback);

  astman_add_param(params, sizeof(params), "ActionId", actionid);

  astman_manager_action_params(s, "Status", params);
  res = astman_wait_for_response(s, &msg, 0);

  if ( res > 0 && response_is(&msg, "Success")) {
    for(;;) {
      res = astman_wait_for_response(s, &msg, 0);
      if ( res > 0 ) {
	strncpy(event, astman_get_header(&msg, "Event"), sizeof(event));

	if (!strcasecmp(event, "Status")) {
	  MSGBUF_ADD(&msg);
	} else if (!strcasecmp(event, "StatusComplete")) {
	  *m = MSGBUF_MSG;
	  astman_add_event_handler_system(s, NULL);
	  return ASTMAN_SUCCESS;
	}
      } else {
	goto out;
      }
    } /* infinity loop */
  }

  out:
    astman_add_event_handler_system(s, NULL);
    return ASTMAN_FAILURE;
}

/**
  Events
    Enable/Disable sending of events to this manager
      EventMask:
        system
        call
        log
        verbose
        command
        agent
        user
        all   if all events should be sent.
        none  if no events should be sent.
*/
int astman_events(struct mansession *s, struct message *m,
		  char *eventmask,
		  char *actionid) {
  int res;
  char params[MAX_LEN] = "";

  if (astman_strlen_zero(eventmask))
    return ASTMAN_FAILURE;

  astman_add_param(params, sizeof(params), "EventMask", eventmask);
  astman_add_param(params, sizeof(params), "ActionId", actionid);
  astman_manager_action_params(s, "Events", params);

  res = astman_wait_for_response(s, m, 0);

  if ( res > 0 )
    return res;
  else
    return ASTMAN_FAILURE;
}

/**
 * GetVar
 *  Get the value of a global or local channel variable.
 *
 *  Channel: Channel to read variable from
 *  *Variable: Variable name
 */
int astman_getvar(struct mansession *s, struct message *m,
		  char *channel, char *variable,
		  char *actionid) {
  int res;
  char params[MAX_LEN] = "";

  if (astman_strlen_zero(variable))
    return ASTMAN_FAILURE;

  astman_add_param(params, sizeof(params), "Channel", channel);
  astman_add_param(params, sizeof(params), "Variable", variable);
  astman_add_param(params, sizeof(params), "ActionId", actionid);

  astman_manager_action_params(s, "GetVar", params);
  res = astman_wait_for_response(s, m, 0);
  if ( res > 0 && response_is(m, "Success")) {
    return res;
  }
  return ASTMAN_FAILURE;
}

/**
 * SetVar
 *  Set a global or local channel variable.
 *
 *  Channel: Channel to set variable for
 *  Variable: Variable name
 *  Value: Value
 */
int astman_setvar(struct mansession *s, struct message *m,
                  char *channel, char *variable, char *value,
                  char *actionid) {
  int res;
  char params[MAX_LEN] = "";

  if (astman_strlen_zero(variable))
    return ASTMAN_FAILURE;

  astman_add_param(params, sizeof(params), "Channel", channel);
  astman_add_param(params, sizeof(params), "Variable", variable);
  astman_add_param(params, sizeof(params), "Value", value);
  astman_add_param(params, sizeof(params), "ActionId", actionid);

  astman_manager_action_params(s, "SetVar", params);
  res = astman_wait_for_response(s, m, 0);
  if ( res > 0 && response_is(m, "Success")) {
    return res;
  }
  return ASTMAN_FAILURE;
}
