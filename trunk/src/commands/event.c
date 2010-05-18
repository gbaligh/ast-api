/* $Id: event.c,v 1.4 2010/05/17 09:32:43 bguesmi Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "event.h"

extern astContext ast_api;


int astDefaultCallback(struct mansession *s, struct message *m);
static ASTMAN_EVENT_CALLBACK defaultCallback = &astDefaultCallback;


int astDefaultCallback(struct mansession *s, struct message *m)
{
    //astman_dump_message(&ast_api.m);
    return ASTMAN_SUCCESS;
}


ASTMAN_EVENT_CALLBACK astEventGetDefaultCallback()
{
    return defaultCallback;
}


int CoreShowChannelsCallBack(struct mansession *s, struct message *m)
{

    return ASTMAN_FAILURE;
}


int SipPeersCallBack(struct mansession *s, struct message *m)
{
    char *event;

    event = astman_get_header(m, ASTMAN_HEADER_EVENT);

    if (!strncasecmp(event, ASTMAN_EVENT_PEER_ENTRY, strlen(ASTMAN_EVENT_PEER_ENTRY))) {
      return ASTMAN_SUCCESS;
    } else if (!strncasecmp(event, ASTMAN_EVENT_PEER_LIST_COMPLETE, strlen(ASTMAN_EVENT_PEER_LIST_COMPLETE))) {
        return ASTMAN_SUCCESS;
    }

    return ASTMAN_FAILURE;
}


int SipShowRegistryCallBack(struct mansession *s, struct message *m)
{
    char *event;

    event = astman_get_header(m, ASTMAN_HEADER_EVENT);

    if (!strncasecmp(event, ASTMAN_EVENT_REGISTRY_ENTRY, strlen(ASTMAN_EVENT_REGISTRY_ENTRY))) {
      return ASTMAN_SUCCESS;
    } else if (!strncasecmp(event, ASTMAN_EVENT_REGISTRATIONS_COMPLETE, strlen(ASTMAN_EVENT_REGISTRATIONS_COMPLETE))) {
        return ASTMAN_SUCCESS;
    }

    return ASTMAN_FAILURE;
}
