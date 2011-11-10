/*******************************************************************************
 * astapi - library for using Asterisk Manager API.
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
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc.,
 ******************************************************************************/
/*******************************************************************************
 *  @file config.c
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100522
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astapi.h"
#include "action.h"
#include "astlog.h"
#include "connection.h"

static char _filename_[30];
static struct message _msg_;

int astConfigLoad(char *filename)
{
    int res = ASTMAN_SUCCESS;
    astlog_init();
    if(astman_strlen_zero(filename)) {
        res = ASTMAN_FAILURE;
        goto Exit;
    }
    if(!astman_strlen_zero(_filename_) && !strncasecmp(_filename_, filename, strlen(filename))) {
        res = ASTMAN_SUCCESS;
        goto Exit;
    }
    if(!astman_get_config(astConnectionGetSession(), &_msg_,
                          filename, "", "")) {
        astlog(ASTLOG_ERROR, "Error reding Conf File %s", filename);
        res = ASTMAN_FAILURE;
        goto Exit;
    }
    strncpy(_filename_, filename, 30);
Exit:
    astlog_end();
    return res;
}

struct message * astConfigGetMsg()
{
    return (&_msg_);
}

void astConfigClear()
{
    memset(_filename_, 0, 30);
}
