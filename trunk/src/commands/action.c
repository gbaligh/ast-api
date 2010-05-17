
/* $Id: action.c,v 1.5 2010/05/17 09:32:43 bguesmi Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "astman.h"
#include "event.h"

extern astContext ast_api;

int astListCommands()
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    memset(&ast_api.m, 0, AST_API_MAX_STR_LENGTH);
    astman_manager_action_params(ast_api.s, "ListCommands", "Parameters: ActionID"CRLF);
    astman_wait_for_response(ast_api.s, &ast_api.m, 0);
//    astman_dump_message(&ast_api.m);
    return ASTMAN_SUCCESS;
}

int astListCategories(char *filename)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    char params[MAX_LEN] = "";
    int rv = 0;
    astman_add_param(params, sizeof(params), "Filename", filename);
    astman_manager_action(ast_api.s, "ListCategories", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //astman_dump_message(&ast_api.m);
    return ASTMAN_SUCCESS;
}


int astGetConfig(char *filename)
{
    if(!ast_api.connected) {
        astlog(ASTLOG_ERROR, "Error in connection");
        return ASTMAN_FAILURE;
    }
    memset(&ast_api.m, 0, AST_API_MAX_STR_LENGTH);
    int rv = 0;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "Filename", filename);
    astman_manager_action_params(ast_api.s, "GetConfig", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if ( rv > 0 && response_is(&ast_api.m, "Success")) {
        return ASTMAN_SUCCESS;
    }
    //astman_dump_message(&ast_api.m);
    return ASTMAN_FAILURE;
}

int astGetConfigJSON(char *filename)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    memset(&ast_api.m, 0, sizeof(message_t));
    int rv = 0;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "Filename", filename);
    astman_manager_action_params(ast_api.s, "GetConfigJSON", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //astman_dump_message(&ast_api.m);
    return ASTMAN_SUCCESS;
}

int astSipPeers(char *actionid, message_t *m, int *size)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    int res = 0;
    char params[MAX_LEN] = "";
    //char event[80];
    astman_add_event_handler(ast_api.s, ASTMAN_EVENT_PEER_ENTRY, SipPeersCallBack);
    astman_add_event_handler(ast_api.s, ASTMAN_EVENT_PEER_LIST_COMPLETE, SipPeersCallBack);
    astman_add_param(params, sizeof(params), "ActionID", actionid);
    astman_manager_action(ast_api.s, "SIPpeers", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        int index = 0;
        if(strlen(astman_get_header(&ast_api.m, "Eventlist")))
            while(astman_wait_for_response(ast_api.s, &ast_api.m, 0)==ASTMAN_SUCCESS) {
                if(strncasecmp(astman_get_header(&ast_api.m, ASTMAN_HEADER_EVENT), ASTMAN_EVENT_PEER_LIST_COMPLETE,
                    strlen(ASTMAN_EVENT_PEER_LIST_COMPLETE)))
                {
                    if(m != NULL) {
                        if(index<*size)
                            memcpy(&m[index++], &ast_api.m, sizeof(message_t));
                        else
                            return ASTMAN_FAILURE;
                    }
                }
                else
                {
                    *size = atoi(astman_get_header(&ast_api.m, "ListItems"));
                    break;
                }
               // astman_dump_message(&ast_api.m);
            }
    }
    return ASTMAN_SUCCESS;
}

int astSipShowPeer(char *peer, char *actionid)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    int res = 0;
    char params[MAX_LEN] = "";
    //astman_add_event_handler(ast_api.s, "Registry", astEventGetDefaultCallback());
    astman_add_param(params, sizeof(params), "Peer", peer);
    astman_add_param(params, sizeof(params), "ActionID", actionid);
    astman_manager_action(ast_api.s, "SIPShowpeer", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
            return ASTMAN_SUCCESS;
    }
    return ASTMAN_FAILURE;
}


int astPing(char *actionid)
{
    int res;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "Ping", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if ( res > 0 && response_is(&ast_api.m, "Pong")) {
    return res;
    }
    return ASTMAN_FAILURE;
}


int astExecuteCLICommand(char *command, char *actionid)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    int res;
    char params[MAX_LEN] = "";
    if (astman_strlen_zero(command))
    return ASTMAN_FAILURE;
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_add_param(params, sizeof(params), "Command", command);
    astman_manager_action(ast_api.s, "Command", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Follows")) {
    return res;
    }
    return ASTMAN_FAILURE;
}

int astUpdateConfigInit(char *filename, int reload, char params[])
{
    astman_add_param(params, sizeof(params), "SrcFilename", filename);
    astman_add_param(params, sizeof(params), "DstFilename", filename);
    astman_add_param(params, sizeof(params), "Reload", reload?"yes":"no");
    return ASTMAN_SUCCESS;
}

int astUpdateConfigAddAction(char params[], char *category, char *param, char *value, char *action)
{
//    char seq[7];
    //sprintf(seq, "%6d", );
    astman_add_param(params, sizeof(params), "Action-000000", action);
    astman_add_param(params, sizeof(params), "Cat-000000", category);
    astman_add_param(params, sizeof(params), "Var-000000", param);
    astman_add_param(params, sizeof(params), "Value-000000", value);
    return ASTMAN_SUCCESS;
}


int astUpdateConfig(char *filename, int reload, char *category, char *param, char *value, char *action)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    if (astman_strlen_zero(filename))
    return ASTMAN_FAILURE;
    if (astman_strlen_zero(category))
    return ASTMAN_FAILURE;
    char params[MAX_LEN] = "";
    int rv = 0;
    astman_add_param(params, sizeof(params), "SrcFilename", filename);
    astman_add_param(params, sizeof(params), "DstFilename", filename);
    astman_add_param(params, sizeof(params), "Reload", reload?"yes":"no");
    astman_add_param(params, sizeof(params), "Action-000000", action);
    astman_add_param(params, sizeof(params), "Cat-000000", category);
    astman_add_param(params, sizeof(params), "Var-000000", param);
    astman_add_param(params, sizeof(params), "Value-000000", value);
    astman_manager_action_params(ast_api.s, "updateconfig", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if(rv < 0 || !response_is(&ast_api.m, "Success"))
    {
        //astman_dump_message(&ast_api.m);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}


int astGetVar(char *channel, char *variable, char *actionid)
{
    int res;
    char params[MAX_LEN] = "";
    if (astman_strlen_zero(variable))
    return ASTMAN_FAILURE;
    astman_add_param(params, sizeof(params), "Channel", channel);
    astman_add_param(params, sizeof(params), "Variable", variable);
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "GetVar", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        return res;
    }
    return ASTMAN_FAILURE;
}

int astSetVar(char *channel, char *variable, char *value, char *actionid)
{
    int res;
    char params[MAX_LEN] = "";
    if (astman_strlen_zero(variable))
    return ASTMAN_FAILURE;
    astman_add_param(params, sizeof(params), "Channel", channel);
    astman_add_param(params, sizeof(params), "Variable", variable);
    astman_add_param(params, sizeof(params), "Value", value);
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "SetVar", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        return res;
    }
    return ASTMAN_FAILURE;
}

int astCoreStatus(char *actionid)
{
    int res;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "CoreStatus", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
    return res;
    }
    return ASTMAN_FAILURE;
}


int astCoreSettings(char *actionid)
{
    int res;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "CoreSettings", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
    return res;
    }
    return ASTMAN_FAILURE;
}


int astCoreShowChannels(char *actionid)
{
    int res;
    char params[MAX_LEN] = "";
    char event[80];
    astman_add_event_handler(ast_api.s, "CoreShowChannelsComplete", CoreShowChannelsCallBack);
    astman_add_event_handler(ast_api.s, "CoreShowChannels", CoreShowChannelsCallBack);
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "CoreShowChannels", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        if(strlen(astman_get_header(&ast_api.m, "Eventlist")))
            for(;;)
            {
                memset(&ast_api.m, 0, sizeof(message_t));
                astlog(ASTLOG_INFO, "Wating Channels event...");
                res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
                if ( res > 0 ) {
                    strncpy(event, astman_get_header(&ast_api.m, "Event"), sizeof(event));
                    if (!strcasecmp(event, "Status")) {
                      //astman_dump_message(&ast_api.m);
                    } else if (!strcasecmp(event, "CoreShowChannelsComplete")) {
                        //astman_dump_message(&ast_api.m);
                        return ASTMAN_SUCCESS;
                    }
                }
            }
    }
    return ASTMAN_FAILURE;
}

int astSipShowRegistry(char *actionid, message_t *m, int *size)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;
    int res = 0;
    char params[MAX_LEN] = "";
    //char event[80];
    astman_add_event_handler(ast_api.s, ASTMAN_EVENT_REGISTRATIONS_COMPLETE, SipShowRegistryCallBack);
    astman_add_event_handler(ast_api.s, ASTMAN_EVENT_REGISTRY_ENTRY, SipShowRegistryCallBack);
    astman_add_param(params, sizeof(params), "ActionID", actionid);
    astman_manager_action(ast_api.s, "SIPshowregistry", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        int index = 0;
        if(strlen(astman_get_header(&ast_api.m, "Eventlist")))
            while(astman_wait_for_response(ast_api.s, &ast_api.m, 0)==ASTMAN_SUCCESS) {
                if(strncasecmp(astman_get_header(&ast_api.m, ASTMAN_HEADER_EVENT), ASTMAN_EVENT_REGISTRATIONS_COMPLETE,
                    strlen(ASTMAN_EVENT_REGISTRATIONS_COMPLETE)))
                {
                    //astman_dump_message(&ast_api.m);
                    if(m != NULL) {
                        if(index<*size)
                            memcpy(&m[index++], &ast_api.m, sizeof(message_t));
                        else
                            return ASTMAN_SUCCESS;
                    }
                }
                else
                {
                    *size = atoi(astman_get_header(&ast_api.m, "ListItems"));
                    return ASTMAN_SUCCESS;
                }
            }
    }

    return ASTMAN_FAILURE;
}

int astReload(char *actionid)
{
    int res;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "Reload", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
    return res;
    }
    return ASTMAN_FAILURE;
}

int astModuelLoad(char *actionid, char *module, char* loadType)
{
    int res;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_add_param(params, sizeof(params), "Module", module);
    astman_add_param(params, sizeof(params), "LoadType", loadType);
    astman_manager_action_params(ast_api.s, "ModuleLoad", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        astlog(ASTLOG_INFO, "Module %s is %s", module, loadType);
        return res;
    }
    return ASTMAN_FAILURE;
}
