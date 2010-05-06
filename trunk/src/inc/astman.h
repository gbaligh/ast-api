#ifndef _ASTMAN_H
#define _ASTMAN_H
/*
 * libastman - library for useing Asterisk Manager API.
 * Copyright (C) 2007 Noriyuki Suzuki
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
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include <time.h>
#include <netinet/in.h>  /* struct sockaddr_in */
/**
 *  @def    MAX_HEADERS
 *  @brief  MAX Header supported in one message command
 */
#define MAX_HEADERS 256
/**
 *  @def    MAX_LEN
 *  @brief  One Header Max Len supported
 */
#define MAX_LEN 1024
/**
 *  @def    MAX_EVENTS
 *  @brief
 */
#define MAX_EVENTS 16
/**
 *  @def    ASTMAN_SUCCESS
 *  @brief
 */
#define ASTMAN_SUCCESS 1
/**
 *  @def    ASTMAN_FAILURE
 *  @brief
 */
#define ASTMAN_FAILURE 0
/**
 *  @def    CRLF
 *  @brief
 */
#define CRLF "\r\n"

/**
 * @struct  message
 * @brief   The struct representing the message command to send
 */
struct message {
  int hdrcount;                         /**< Header count */
  int gettingdata;                      /**< data */
  char headers[MAX_HEADERS][MAX_LEN];   /**< Headers list */
};
/**
 * @struct  message
 * @brief   The struct of an opened AMI session
 */
struct mansession {
  int fd;                   /**< the discriptor to the socket */
  char inbuf[MAX_LEN];      /**< buffer */
  int inlen;                /**< length of the buffer */
  struct sockaddr_in sin;   /**< address of the socket */
/**
 * @struct  mevent
 * @brief   The struct representing event id and callback
 */
  struct event {
    char *event;    ///< the event ID
    int (*func)(struct mansession *s, struct message *m); ///< callback associated to this event
  } events[MAX_EVENTS]; /**< event registred to */
  int eventcount; /**< the real count of event that the session is registred to */
  int debug;    /**< active/desactivated DEBUG */
};
/**
 * @typedef (*ASTMAN_EVENT_CALLBACK)
 * @brief   CallBack Event proto-type
 */
typedef int (*ASTMAN_EVENT_CALLBACK)(struct mansession *, struct message *);
/**
 * @fn  astman_strlen_zero(const char *s)
 * @brief inline function to test if the given char is not empty
 * @param IN s
 * @return >0 if the given char is not empty
 */
static inline __attribute__((always_inline)) int astman_strlen_zero(const char *s)
{
  return (!s || (*s == '\0'));
}
/**
 * @def esponse_is(M, RES)
 * @brief Get response Code
 */
#define response_is(M, RES)  !strcasecmp(astman_get_header(M, "Response"), RES)

int astman_add_param(char *buf, int buflen, char *header,const char *value);
void astman_dump_message(struct message *m);

struct mansession *astman_open(void);
int astman_connect(struct mansession *s, const char *hostname, const int port);
void astman_disconnect(struct mansession *s);

// Transmit/Response messages
int astman_manager_action(struct mansession *s, char *action, char *fmt, ...);
int astman_wait_for_response(struct mansession *s, struct message *msg, time_t timeout);
char *astman_get_header(struct message *m, const char *var);
int astman_manager_action_params(struct mansession *s, char *action, char *params);

// Events
int astman_add_event_handler(struct mansession *s, char *event, ASTMAN_EVENT_CALLBACK callback );
int astman_add_event_handler_system(struct mansession *s, ASTMAN_EVENT_CALLBACK callback );


// Debug
void astman_dump_message(struct message *m);

int astman_login(struct mansession *s, char *username, char *secret);
int astman_logoff(struct mansession *s);
//struct message *astman_ping(struct mansession *s, char *actionid);
int astman_queuestatus(struct mansession *s, struct message **,char *actionid);
#endif /* _ASTMAN_H */
