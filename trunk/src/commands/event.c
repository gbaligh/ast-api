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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int astDefaultCallback(struct mansession *s, struct message *m);
static ASTMAN_EVENT_CALLBACK defaultCallback = &astDefaultCallback;


int astDefaultCallback(struct mansession *s, struct message *m)
{
    static int i = 0;
    astlog(ASTLOG_WARNING,"%s not implemented called %d times\n", __FUNCTION__, i++);
    //astman_dump_message(&ast_api.m);
    return i;
}


ASTMAN_EVENT_CALLBACK astEventGetDefaultCallback()
{
    return defaultCallback;
}


