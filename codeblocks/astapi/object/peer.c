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
 *  @file peer.c
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100524
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astapi.h"
#include "action.h"
#include "astlog.h"
#include "connection.h"
#include "config.h"
#include "peer.h"
/*******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 ******************************************************************************/
static int getPeerFromSipPeersResponse(struct message *m, Peer *p)
{
    memset(p, 0, sizeof(Peer));

    p->dynamic = strncasecmp(astman_get_header(m, "Dynamic"), "y", 1)?0:1;
    p->natSupport = strncasecmp(astman_get_header(m, "Natsupport"), "y", 1)?0:1;
//    p->videoSupport = strncasecmp(astman_get_header(m, "VideoSupport"), "y", 1)?0:1;
//    p->textSupport = strncasecmp(astman_get_header(m, "TextSupport"), "y", 1)?0:1;
//    p->acl = strncasecmp(astman_get_header(m, "ACL"), "y", 1)?0:1;
    p->realtimeDevice = strncasecmp(astman_get_header(m, "RealtimeDevice"), "y", 1)?0:1;
    strncpy(p->status, astman_get_header(m, "Status"), MAX_VALUE_LEN);
    p->ipPort = atoi(astman_get_header(m, "IPport"));
    strncpy(p->ipAddress, astman_get_header(m, "IPaddress"),
            MAX_VALUE_LEN);
    strncpy(p->channelType, astman_get_header(m, "Channeltype"), MAX_VALUE_LEN);
    strncpy(p->chanObjectType, astman_get_header(m, "ChanObjectType"),
            MAX_VALUE_LEN);
    strncpy(p->objectName, astman_get_header(m, "ObjectName"), MAX_VALUE_LEN);
    strncpy(p->userAgent, astman_get_header(m, "SIP-Useragent"), MAX_VALUE_LEN);
    strncpy(p->callerID, astman_get_header(m, "Callerid"), MAX_VALUE_LEN);
    return ASTMAN_SUCCESS;
}
/*******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 ******************************************************************************/
static int getPeerFromSipShowPeerResponse(struct message *m, Peer *p)
{
    memset(p, 0, sizeof(Peer));

    strncpy(p->channelType, astman_get_header(m, "Channeltype"), MAX_VALUE_LEN);
    strncpy(p->objectName, astman_get_header(m, "ObjectName"), MAX_VALUE_LEN);
    strncpy(p->chanObjectType, astman_get_header(m, "ChanObjectType"),
            MAX_VALUE_LEN);
    p->secretExist = strncasecmp(astman_get_header(m, "SecretExist"), "y", 1)?0:1;
    p->remoteSecretExist = strncasecmp(astman_get_header(m, "RemoteSecretExist"), "y", 1)?0:1;
    p->md5SecretExist = strncasecmp(astman_get_header(m, "MD5SecretExist"), "y", 1)?0:1;
    strncpy(p->context, astman_get_header(m, "Context"), MAX_VALUE_LEN);
    p->callLimit = atoi(astman_get_header(m, "Call-limit"));
    p->busyLevel = atoi(astman_get_header(m, "Busy-level"));
    p->dynamic = strncasecmp(astman_get_header(m, "Dynamic"), "y", 1)?0:1;
    strncpy(p->callerID, astman_get_header(m, "Callerid"), MAX_VALUE_LEN);
    p->regExpire = atoi(astman_get_header(m, "RegExpire"));
    strncpy(p->toHost, astman_get_header(m, "ToHost"), MAX_VALUE_LEN);
    strncpy(p->ipAddress, astman_get_header(m, "Address-IP"),
            MAX_VALUE_LEN);
    p->ipPort = atoi(astman_get_header(m, "Address-Port"));
    strncpy(p->status, astman_get_header(m, "Status"), MAX_VALUE_LEN);
    strncpy(p->userAgent, astman_get_header(m, "SIP-Useragent"), MAX_VALUE_LEN);
    return ASTMAN_SUCCESS;
}
/*******************************************************************************
 * @fn int astPeerGetList(char *filename, Peer p[], int *len)
 * @brief Get the List of all Peer, configured in Asterisk
 * @param filename: to get Extra information from file
 * @param p[]: list of pre-allocated Peers
 * @param len: number of pre-allocated elements in the Peer list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
int astPeerGetList(Peer p[], int *len)
{
    struct message *msg = NULL;
    int size = 0;
    int i = 0;
    int res = ASTMAN_SUCCESS;
    astlog_init();
    if(!(size = astman_sip_peers(astConnectionGetSession(),&msg,""))) {
        res = ASTMAN_FAILURE;
        goto Exit;
    }

    for(i=0;((i<size)&&(i<*len));i++) {
        getPeerFromSipPeersResponse((msg+i), &p[i]);
    }
    *len = i;
    astlog(ASTLOG_INFO, "Number of Peers Found: %d", size);
    astlog(ASTLOG_INFO, "Number of Peers Passed: %d", i);
Exit:
    free(msg);
    astlog_end();
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @fn int astPeerGet(char *filename, char *peer, Peer *p)
 * @brief Get informations from Asterisk using the SipShowPee Action, and parse
 *        response
 * @param filename
 * @param peer
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astPeerGet(char *peer, Peer *p)
{
    struct message m;
    int ret = ASTMAN_SUCCESS;
    astlog_init();
    if(astman_strlen_zero(peer)) {
        astlog(ASTLOG_ERROR, "Peer must be given to search for");
        ret = ASTMAN_FAILURE;
        goto Exit;
    }
    //memset(p, 0, sizeof(Peer));

    if(!astman_sip_show_peer(astConnectionGetSession(), &m,
                             peer, "")) {
        astlog(ASTLOG_ERROR, "astSipShowPeer (%s)", peer);
        ret = ASTMAN_FAILURE;
        goto Exit;
    }

    getPeerFromSipShowPeerResponse(&m, p);
Exit:
    astlog_end();
    return ret;
}
/******************************************************************************
 * @fn int astPeerSave(char *filename, Peer *p)
 * @brief Save Informations to Asterisk File
 * @param filename
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astPeerSave(char *filename, Peer *p)
{
    if((p->c.nb_params<=0))
        return ASTMAN_FAILURE;
    return astCategorySave(filename, &(p->c));
}
/******************************************************************************
 * @fn char* astPeerGetParam(char *filename, Peer *p, char *param)
 * @brief Get Parameter saved in Asterisk's Configuration File
 * @param filename
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astPeerGetParam(char *filename, Peer *p, char *param)
{
    astlog_init();
    if(p->c.nb_params<=0) {
        if(!astCategoryGet(filename, p->objectName, &p->c)) {
            astlog(ASTLOG_ERROR, "astCategory failed");
            return NULL;
        }
    }
    astlog_end();
    return astCategoryGetParamValue(&p->c, param);
}
