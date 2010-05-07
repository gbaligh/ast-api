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
/*******************************************************************************
 *  @file    action.c
 *  @brief   Base Functions implementation for the ASTMAN API.
 *  @author  Baligh.GUESMI Emira.MHAROUECH Olivier.BENEZE
 *  @version 0.1
 *  @date    26 Avril 2010
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

extern astContext ast_api;
/******************************************************************************
 *  \fn     astListCommands
 *  \brief  List available manager commands
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astListCommands() {
    if (!ast_api.connected)
        return ASTMAN_FAILURE;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionID", actionid);
    astman_manager_action_params(ast_api.s, "ListCommands", params);
    astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @fn     astListCategories
 * @brief  List categories in configuration file
 * @param  IN filename: Configuration file name
 * @return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astListCategories(char *filename) {
    if (!ast_api.connected)
        return ASTMAN_FAILURE;
    char params[MAX_LEN] = "";
    int rv = 0;
    astman_add_param(params, sizeof(params), "Filename", filename);
    astman_manager_action(ast_api.s, "ListCategories", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 *  @fn     astGetConfig
 *  @brief  Display a configuration file, used mainly by AJAM/Asterisk-gui
 *  @param  IN filename: Configuration file name
 *  @return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astGetConfig(char *filename) {
    if (!ast_api.connected)
        return ASTMAN_FAILURE;
    memset(&ast_api.m, 0, AST_API_MAX_STR_LENGTH);
    int rv = 0;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "Filename", filename);
    astman_manager_action_params(ast_api.s, "GetConfig", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 *  @fn     astSipPeers
 *  @brief  List SIP peers (text format)
 *  @param  IN actionid: action identifier
 *  @return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astSipPeers(char *actionid) {
    if (!ast_api.connected)
        return ASTMAN_FAILURE;
    int rv = 0;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionID", actionid);
    astman_manager_action(ast_api.s, "SIPpeers", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 *  @fn     astSipShowPeer
 *  @brief  Show SIP peer (text format)
 *  @param  IN peer: name of the PEER/USER
 *  @param  IN actionid: action identifier
 *  @return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astSipShowPeer(char *peer, char *actionid) {
    if (!ast_api.connected)
        return ASTMAN_FAILURE;
    int res = 0;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "Peer", peer);
    astman_add_param(params, sizeof(params), "ActionID", actionid);
    astman_manager_action(ast_api.s, "SIPshowpeer", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        return res;
    }
    return ASTMAN_FAILURE;
}
/******************************************************************************
 *  @fn     astPing
 *  @brief  Keepalive command
 *  @param  IN actionid: action identifier
 *  @return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astPing(char *actionid) {
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
/******************************************************************************
 *  @fn     astExecuteCLICommand
 *  @brief  Execute Asterisk CLI Command
 *  @param  IN command: Command to execute (e.: sip show peers)
 *  @param  IN actionid: action identifier
 *  @return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astExecuteCLICommand(char *command, char *actionid) {
    if (!ast_api.connected)
        return ASTMAN_FAILURE;
    int res;
    char params[MAX_LEN] = "";
    if (astman_strlen_zero(command))
        return ASTMAN_FAILURE;
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_add_param(params, sizeof(params), "Command", command);
    astman_manager_action(ast_api.s, "Command", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Follows")) {
        return res;
    }
    return ASTMAN_FAILURE;
}
/******************************************************************************
 *  @fn     astUpdateConfig
 *  @brief  Update basic configuration
 *  @param  IN actionid: action identifier
 *  @param  IN actionid: action identifier
 *  @param  IN actionid: action identifier
 *  @param  IN actionid: action identifier
 *  @param  IN actionid: action identifier
 *  @param  IN actionid: action identifier
 *  @return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astUpdateConfig(char *filename, int reload, char *category, char *param,
                    char *value, char *action) {
    if (!ast_api.connected)
        return ASTMAN_FAILURE;
    if (astman_strlen_zero(filename))
        return ASTMAN_FAILURE;
    if (astman_strlen_zero(category))
        return ASTMAN_FAILURE;
    if (astman_strlen_zero(param))
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
    if (rv < 0 || !response_is(&ast_api.m, "Success")) {
        astman_dump_message(&ast_api.m);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 *  \fn astListCommands()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astGetVar(char *channel, char *variable, char *actionid) {
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
/******************************************************************************
 *  \fn astListCommands()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astSetVar(char *channel, char *variable, char *value, char *actionid) {
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
/******************************************************************************
 *  \fn astListCommands()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astCoreStatus(char *actionid) {
    int res;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "CoreStatus", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        return res;
    }
    return ASTMAN_FAILURE;
}
/******************************************************************************
 *  \fn astListCommands()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astCoreSettings(char *actionid) {
    int res;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "CoreSettings", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        return res;
    }
    return ASTMAN_FAILURE;
}
/******************************************************************************
 *  \fn astListCommands()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int CoreShowChannelsCallBack(struct mansession *s, struct message *m) {
    printf("11111");
    return 0;
}
/******************************************************************************
 *  \fn astListCommands()
 *  \brief  Add a new parameter to the Command
 *  \return ASTMAN_SUCCESS / ASTMAN_FAILURE
 ******************************************************************************/
int astCoreShowChannels(char *actionid) {
    int res;
    char params[MAX_LEN] = "";
    astman_add_param(params, sizeof(params), "ActionId", actionid);
    astman_manager_action_params(ast_api.s, "CoreShowChannels", params);
    res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    //res = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    astman_add_event_handler(ast_api.s, "CoreShowChannel",
                             &CoreShowChannelsCallBack);
    astman_add_event_handler(ast_api.s, "CoreShowChannelsComplete",
                             &CoreShowChannelsCallBack);
    astman_dump_message(&ast_api.m);
    if ( res > 0 && response_is(&ast_api.m, "Success")) {
        return res;
    }
    return ASTMAN_FAILURE;
}
