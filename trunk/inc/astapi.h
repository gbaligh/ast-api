#ifndef _ASTAPI_H
#define _ASTAPI_H

typedef void* hAstSession;
typedef void* hAstPeer;


typedef enum astSipParam_e {
    PARAM_SIP_CONTEXT=0,
    PARAM_SIP_ALLOW_GUEST,
    PARAM_SIP_ALLOW_OVERLAP,
    PARAM_SIP_REALM,
    PARAM_SIP_UDP_BIND_ADDRESS,
    PARAM_SIP_TCP_ENABLED,
    PARAM_SIP_TCP_BIND_ADDRESS,
    PARAM_SIP_SRV_LOOKUP,
    PARAM_SIP_PEDANTIC,
    PARAM_SIP_MAX_EXPIRY,
    PARAM_SIP_MIN_EXPIRY,
    PARAM_SIP_DEFAULT_EXPIRY,
    PARAM_SIP_MWI_EXPIRY,
    PARAM_SIP_BUGGY_MWI,
    PARAM_SIP_MW_EXTEN,
    PARAM_SIP_DISALLOW,
    PARAM_SIP_ALLOW,
    PARAM_SIP_LANGUAGE,
    PARAM_SIP_DTMF_MODE,
    PARAM_SIP_COMPACT_FORM,
    PARAM_SIP_NAT,
    PARAM_SIP_CANREINVITE,
    PARAM_SIP_ALLOW_SUBSCRIBE,
    PARAM_SIP_VAR_LIST_LENGTH /* This entry must always be the last in the list */
} astSipParam;


typedef enum {
    PARAM_SIP_PEER_CAHNNEL_TYPE,
    PARAM_SIP_PEER_OBJECT_NAME,
    PARAM_SIP_PEER_VAR_LIST_LENGTH /* This entry must always be the last in the list */
} astSipPeerParam;


int astConnect(char * username, char *secret, char *host, int port);
int astDeconnect();

int astSipConfListCategories();

int astSipConfGetGeneralConfig();



#endif
