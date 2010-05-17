/* $Id: peer.c,v 1.6 2010/05/17 09:32:43 bguesmi Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "astman.h"
#include "action.h"
#include "sipconf.h"

#define OBJECT_NAME "PEER"
#define SIP_CONF_FILE    "sip.conf"

extern astContext ast_api;

static void getPeerFromMessage(message_t *m, Peer *p);
static int astPeer2Cat(Peer *p, Category *c);
static int astPeerFromCategory(Peer *p);
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astPeerGetList(Peer p[], int *len)
{
    message_t m[*len];
    int size = *len;
    int i = 0;
    if(!astSipPeers(OBJECT_NAME, m, &size))
        return ASTMAN_FAILURE;
    for(i=0;i<size;i++) {
        getPeerFromMessage(&m[i], &p[i]);
    }
    *len = size;
    astlog(ASTLOG_INFO, "Number of Peers Found: %d", size);
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
static void getPeerFromMessage(message_t *m, Peer *p)
{
    p->natSupport = !strncasecmp(astman_get_header(m, "Natsupport"), "y", 1)?1:0;
    p->dynamic = strncasecmp(astman_get_header(m, "Dynamic"), "y", 1)?0:1;
    p->videoSupport = strncasecmp(astman_get_header(m, "VideoSupport"), "y", 1)?0:1;
    p->textSupport = strncasecmp(astman_get_header(m, "TextSupport"), "y", 1)?0:1;
    p->acl = strncasecmp(astman_get_header(m, "ACL"), "y", 1)?0:1;
    p->realtimeDevice = strncasecmp(astman_get_header(m, "RealtimeDevice"), "y", 1)?0:1;
    p->DTMFMode += strncasecmp(astman_get_header(m, "SIP-DTMFmode"), "rfc2833", 7)?DTMF_NOT_SET:DTMF_RFC2833;
    p->DTMFMode += strncasecmp(astman_get_header(m, "SIP-DTMFmode"), "inband", 6)?DTMF_NOT_SET:DTMF_INBAND;
    p->DTMFMode += strncasecmp(astman_get_header(m, "SIP-DTMFmode"), "info", 7)?DTMF_NOT_SET:DTMF_SIPINFO;
    if(strlen(astman_get_header(m, "IPport")))
        p->ipPort = atoi(astman_get_header(m, "IPport"));
    else if(strlen(astman_get_header(m, "Address-Port")))
        p->ipPort = atoi(astman_get_header(m, "Address-Port"));
    else
        p->ipPort = 0;
    if(strlen(astman_get_header(m, "IPaddress")))
        strncpy(p->ipAddress, astman_get_header(m, "IPaddress"), MAX_VALUE_LEN);
    else if (strlen(astman_get_header(m, "Address-IP")))
        strncpy(p->ipAddress, astman_get_header(m, "Address-IP"), MAX_VALUE_LEN);
    else
        strcpy(p->ipAddress, "0.0.0.0");
    strncpy(p->channelType, astman_get_header(m, "Channeltype"), MAX_VALUE_LEN);
    strncpy(p->chanObjectType, astman_get_header(m, "ChanObjectType"), MAX_VALUE_LEN);
    strncpy(p->objectName, astman_get_header(m, "ObjectName"), MAX_VALUE_LEN);
    strncpy(p->status, astman_get_header(m, "Status"), MAX_VALUE_LEN);
    strncpy(p->userAgent, astman_get_header(m, "SIP-Useragent"), MAX_VALUE_LEN);
    strncpy(p->callerID, astman_get_header(m, "Callerid"), MAX_VALUE_LEN);

    if(!astPeerFromCategory(p)) {
        astlog(ASTLOG_ERROR, "Error reading Category fo Peer %s", p->objectName);
    }
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
static int astPeerFromCategory(Peer *p)
{
    Category c;
    if(astCategoryGet(p->objectName, &c)) {
        int i = 0;
        for(i=0; i<c.nb_params; i++) {
            if(!strncasecmp(c.params[i].name, astSipConfParamMap[PARAM_SIP_SECRET].str, MAX_NAME_LEN)) {
                strncpy(p->secret, c.params[i].value, MAX_VALUE_LEN);
            } else if(!strncasecmp(c.params[i].name, astSipConfParamMap[PARAM_PROV_MAC].str, MAX_NAME_LEN)) {
                strncpy(p->mac, c.params[i].value, MAX_VALUE_LEN);
            } else if(!strncasecmp(c.params[i].name, astSipConfParamMap[PARAM_PROV_MODEL].str, MAX_NAME_LEN)) {
                strncpy(p->ipPhoneModel, c.params[i].value, MAX_VALUE_LEN);
            }
        }
    } else {
        astlog(ASTLOG_ERROR, "Error Category %s", p->objectName);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
static int astPeer2Cat(Peer *p, Category *c)
{
    c->nb_params = 0;
    strncpy(c->cat, p->objectName, MAX_NAME_LEN);
    astCategoryAddParam(c, astSipConfParamMap[PARAM_SIP_TPYPE].str, "friend");
    astCategoryAddParam(c, astSipConfParamMap[PARAM_SIP_HOST].str, p->dynamic?"dynamic":p->ipAddress);
    astCategoryAddParam(c, astSipConfParamMap[PARAM_SIP_NAT].str, p->natSupport?"auto":"never");
    astCategoryAddParam(c, astSipConfParamMap[PARAM_SIP_CANREINVITE].str, "nonat");
    astCategoryAddParam(c, astSipConfParamMap[PARAM_SIP_SECRET].str, p->secret);
    astCategoryAddParam(c, astSipConfParamMap[PARAM_SIP_DTMF_MODE].str, astDtmfModeMap[p->DTMFMode].str);
    astCategoryAddParam(c, astSipConfParamMap[PARAM_SIP_FROMUSER].str, p->fromUser);
    astCategoryAddParam(c, astSipConfParamMap[PARAM_SIP_CALLERID].str, p->callerID);
    astCategoryAddParam(c, astSipConfParamMap[PARAM_PROV_MAC].str, p->mac);
    astCategoryAddParam(c, astSipConfParamMap[PARAM_PROV_MODEL].str, p->ipPhoneModel);
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astPeerSave(Peer *p)
{
    Category c;
    if(!astCategoryGet(p->objectName, &c)) {
        astlog(ASTLOG_INFO, "Peer %s not found, creating new one ...", p->objectName);
    }
    astPeer2Cat(p, &c);
    if(!astCategorySave(&c)) {
        astlog(ASTLOG_ERROR, "Error in saving Peer %s", p->objectName);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astPeerGet(char *peer, Peer *p)
{
    if(!astSipShowPeer(peer, OBJECT_NAME)) {
        astlog(ASTLOG_ERROR, "Error in Getting Peer %s", peer);
        return ASTMAN_FAILURE;
    }
    getPeerFromMessage(&ast_api.m, p);
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astPeerDel(Peer *p)
{
    Category c;
    if(!astCategoryGet(p->objectName, &c)) {
        astlog(ASTLOG_ERROR, "Error Peer %s not found", p->objectName);
        return ASTMAN_FAILURE;
    }
    if(!astCategoryDel(&c)) {
        astlog(ASTLOG_ERROR, "Error Peer %s not found", p->objectName);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astPeerCreateRegistry(Peer *p, Registry *r)
{
    if(strlen(p->ipAddress))
        strncpy(r->host, p->ipAddress, MAX_VALUE_LEN);

    strncpy(r->userName, p->objectName, MAX_VALUE_LEN);
    r->port = p->ipPort;
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astPeerSetExternalLine(Peer *p, Peer *line)
{
    return ASTMAN_SUCCESS;
}
