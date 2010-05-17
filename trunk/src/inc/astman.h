/* $Id: astman.h,v 1.3 2010/05/10 15:50:34 bguesmi Exp $ */
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

#include "common.h"


/**
 *  @def    CRLF
 *  @brief
 */
#define CRLF "\r\n"

int astman_add_param(char *buf, int buflen, char *header,const char *value);
void astman_dump_message(struct message *m);

struct mansession *astman_open(void);
int astman_connect(struct mansession *s, const char *hostname, const int port);
void astman_disconnect(struct mansession *s);

/* Transmit/Response messages */
int astman_manager_action(struct mansession *s, char *action, char *fmt, ...);
int astman_wait_for_response(struct mansession *s, struct message *msg, time_t timeout);
char *astman_get_header(struct message *m, const char *var);
int astman_manager_action_params(struct mansession *s, char *action, char *params);

/* Events */
int astman_add_event_handler(struct mansession *s, char *event, ASTMAN_EVENT_CALLBACK callback );
int astman_add_event_handler_system(struct mansession *s, ASTMAN_EVENT_CALLBACK callback );


/* Debug */
void astman_dump_message(struct message *m);

int astman_login(struct mansession *s, char *username, char *secret);
int astman_logoff(struct mansession *s);
/* struct message *astman_ping(struct mansession *s, char *actionid); */
int astman_queuestatus(struct mansession *s, struct message **,char *actionid);
#endif /* _ASTMAN_H */
