/********************************************************************
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
 ********************************************************************/
/********************************************************************
 *  @file registry.c
 *  @brief register interface
 *  @author Baligh.GUESMI
 *  @date 20100523
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astapi.h"
#include "action.h"
#include "astlog.h"
#include "connection.h"
#include "config.h"
#include "category.h"
#include "user.h"
#include "registry.h"
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
static inline void getRegFromSipRegistryReponse(struct message *m, Registry *r)
{
    r->port = atoi(astman_get_header(m, "Port"));
    r->refresh = atoi(astman_get_header(m, "Refresh"));
    strncpy(r->host, astman_get_header(m, "Host"), MAX_VALUE_LEN);
    strncpy(r->userName, astman_get_header(m, "Username"), MAX_VALUE_LEN);
    strncpy(r->state, astman_get_header(m, "State"), MAX_VALUE_LEN);
    strncpy(r->registrationTime, astman_get_header(m, "RegistrationTime"), MAX_VALUE_LEN);
}
/*******************************************************************************
 * @fn int astPeerGetList(char *filename, Peer p[], int *len)
 * @brief Get the List of all Peer, configured in Asterisk
 * @param p[]: list of pre-allocated Peers
 * @param len: number of pre-allocated elements in the Peer list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
int astRegGetList(Registry r[], int *len)
{
    struct message *msg = NULL;
    int size = 0;
    int i = 0;
    int res = ASTMAN_SUCCESS;

    astlog_init();

    if(!(size = astman_sip_show_registry(astConnectionGetSession(),&msg,""))) {
        res = ASTMAN_FAILURE;
        goto Exit;
    }

    for(i=0;((i<size)&&(i<*len));i++) {
        getRegFromSipRegistryReponse((msg+i), &r[i]);
        //removePrefix(r[i].host, TRUNK_USER_PREFIX);
    }
    *len = i;
    astlog(ASTLOG_INFO, "Number of register found: %d", size);
    astlog(ASTLOG_INFO, "Number of register passed: %d", i);
Exit:
    free(msg);
    astlog_end();
    return res;
}
/*******************************************************************************
 * @fn int astPeerGetList(char *filename, Peer p[], int *len)
 * @brief Get the List of all Peer, configured in Asterisk
 * @param filename: to get Extra information from file
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
char * astRegGetTrunkUserName(Registry *r)
{
    return r->host;
}
