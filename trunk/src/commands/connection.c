/* $Id: connection.c,v 1.3 2010/05/10 15:50:34 bguesmi Exp $ */
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "astman.h"


astContext ast_api;


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

int astConnect(char * username, char *secret, char *host, int port)
{
    strncpy(ast_api.username, username, AST_API_MAX_STR_LENGTH);
    strncpy(ast_api.secret, secret, AST_API_MAX_STR_LENGTH);
    strncpy(ast_api.host, host, AST_API_MAX_STR_LENGTH);
    ast_api.port = port;

    ast_api.s = astman_open();
    astman_connect(ast_api.s, ast_api.host, ast_api.port);
    if(astman_login(ast_api.s, ast_api.username, ast_api.secret) == ASTMAN_FAILURE)
    {
        astlog(ASTLOG_ERROR, "Error in authorization");
        return ASTMAN_FAILURE;
    }
    ast_api.connected = 1;
    return ASTMAN_SUCCESS;
}

int astDeconnect()
{
    astman_logoff(ast_api.s);
    astman_disconnect(ast_api.s);
    astInit();
    return ASTMAN_SUCCESS;
}
