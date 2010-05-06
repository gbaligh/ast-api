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
#include <string.h>

#include "common.h"


astContext ast_api;

/******************************************************************************
 *  \fn astInit()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astInit()
{
    ast_api.s = NULL;
    ast_api.username[0] = '\0';
    ast_api.secret[0] = '\0';
    ast_api.host[0] = '\0';
    ast_api.port = -1;
    ast_api.connected = 0;
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 *  \fn astConnect()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astConnect(char * username, char *secret, char *host, int port)
{
    strncpy(ast_api.username, username, AST_API_MAX_STR_LENGTH);
    strncpy(ast_api.secret, secret, AST_API_MAX_STR_LENGTH);
    strncpy(ast_api.host, host, AST_API_MAX_STR_LENGTH);
    ast_api.port = port;

    ast_api.s = astman_open();
    astman_connect(ast_api.s, ast_api.host, ast_api.port);
    if(astman_login(ast_api.s, ast_api.username, ast_api.secret)
                == ASTMAN_FAILURE)
    {
        astlog(ASTLOG_ERROR, "Error in authorization");
        return ASTMAN_FAILURE;
    }
    ast_api.connected = 1;
    astman_add_event_handler_system(ast_api.s, astGetDefaultCallback());
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 *  \fn astDeconnect()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astDeconnect()
{
    astman_logoff(ast_api.s);
    astman_disconnect(ast_api.s);
    astInit();
    return ASTMAN_SUCCESS;
}
