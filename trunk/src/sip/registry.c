/* $Id: registry.c,v 1.4 2010/05/17 09:32:43 bguesmi Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "action.h"

#define OBJECT_NAME     "REGISTRY"
#define SIP_CONF_FILE   "sip.conf"

extern astContext ast_api;

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
static void getRegistryFromMessage(message_t *m, Registry *r)
{
    r->port = atoi(astman_get_header(m, "Port"));
    r->refresh = atoi(astman_get_header(m, "Refresh"));

    strncpy(r->host, astman_get_header(m, "Host"), MAX_VALUE_LEN);
    strncpy(r->userName, astman_get_header(m, "Username"), MAX_VALUE_LEN);
    strncpy(r->state, astman_get_header(m, "State"), MAX_VALUE_LEN);
    strncpy(r->registrationTime, astman_get_header(m, "RegistrationTime"), MAX_VALUE_LEN);
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astRegistryGetList(Registry r[], int *len)
{
    message_t m[*len];
    int size = *len;
    int i = 0;
    if(!astSipShowRegistry(OBJECT_NAME, m, &size))
        return ASTMAN_FAILURE;
    for(i=0;i<size;i++) {
        getRegistryFromMessage(&m[i], &r[i]);
    }
    *len = size;
    astlog(ASTLOG_INFO, "Number of Registry Found: %d", size);
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astRegistryGetPeer(Registry *r, Peer *p)
{
    return astPeerGet(r->userName, p);
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astRegistrySave(Registry *r)
{
    astlog(ASTLOG_INFO, "%s: Not implemented yet ...", __FUNCTION__);
    return ASTMAN_SUCCESS;
}
