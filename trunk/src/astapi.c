
#include <stdio.h>
#include <string.h>

#include "common.h"


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



/*ast_core_setting_t *astCoreSettings()
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    memset(&ast_api.m, 0, AST_API_MAX_STR_LENGTH);
    astman_manager_action_params(ast_api.s, "CoreSettings", "Peer: 3200"CRLF);
    astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);

    return coreParseMessage(&ast_api.m);
}*/

/*int ast_CoreShowChannels(ast_core_setting_t *cs)
{
    //int i = 0;
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    memset(&ast_api.m, 0, AST_API_MAX_STR_LENGTH);
    astman_manager_action_params(ast_api.s, "CoreShowChannels", "Peer: 3200"CRLF);
    astman_wait_for_response(ast_api.s, &ast_api.m, 0);

        astman_dump_message(&ast_api.m);

    //for(i=0; i<ast_api.m->hdrcount; i++)
        //if(!strncasecmp(ast_api.m->headers[0], "AMIVersion"))
            //cs->AMIVersion


    return ASTMAN_SUCCESS;
}*/
