#ifndef _ASTAPI_H
#define _ASTAPI_H

/**
 *  @def    MAX_LEN
 *  @brief  One Header Max Len supported
 */
#define MAX_NAME_LEN    128
#define MAX_VALUE_LEN   256
#define MAX_LEN         ((MAX_NAME_LEN)+(MAX_VALUE_LEN))
/**
 *  @def    ASTMAN_SUCCESS
 *  @brief
 */
#define ASTMAN_SUCCESS 1
/**
 *  @def    ASTMAN_FAILURE
 *  @brief
 */
#define ASTMAN_FAILURE 0
/**
 *  @def    MAX_HEADERS
 *  @brief  MAX Header supported in one message command
 */
#define MAX_HEADERS 256
/**
 *  @def    MAX_EVENTS
 *  @brief
 */
#define MAX_EVENTS 16

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
    PARAM_SIP_TPYPE,
    PARAM_SIP_HOST,
    PARAM_SIP_SECRET,
    PARAM_SIP_FROMUSER,
    PARAM_SIP_CALLERID,
    PARAM_PROV_MAC,
    PARAM_PROV_MODEL,
    PARAM_SIP_VAR_LIST_LENGTH /* This entry must always be the last in the list */
} astSipParam;


typedef enum {
    PARAM_SIP_PEER_CAHNNEL_TYPE,
    PARAM_SIP_PEER_OBJECT_NAME,
    PARAM_SIP_PEER_VAR_LIST_LENGTH /* This entry must always be the last in the list */
} astSipPeerParam;

typedef enum {
    DTMF_NOT_SET,
    DTMF_RFC2833,
    DTMF_INBAND,
    DTMF_SIPINFO
} astDtmfMode;


typedef struct {
    char status[MAX_VALUE_LEN];
    char channelType[MAX_VALUE_LEN];
    char objectName[MAX_VALUE_LEN];
    char chanObjectType[MAX_VALUE_LEN];
    char ipAddress[MAX_VALUE_LEN];
    char userAgent[MAX_VALUE_LEN];
    char secret[MAX_VALUE_LEN];
    char fromUser[MAX_VALUE_LEN];
    char callerID[MAX_VALUE_LEN];
    char mac[MAX_VALUE_LEN];
    char ipPhoneModel[MAX_VALUE_LEN];
    astDtmfMode DTMFMode;
    int ipPort;
    int dynamic;
    int natSupport;
    int videoSupport;
    int textSupport;
    int acl;
    int realtimeDevice;
} Peer;


typedef struct {
    char host[MAX_VALUE_LEN];
    char userName[MAX_VALUE_LEN];
    char state[MAX_VALUE_LEN];
    char registrationTime[MAX_VALUE_LEN];
    int port;
    int refresh;
} Registry;

typedef struct {
    int line;
    char name[MAX_NAME_LEN];
    char value[MAX_VALUE_LEN];
} confParam;


typedef struct {
    char cat[MAX_NAME_LEN];
    int line;
    int nb_params;
    confParam params[MAX_HEADERS];
} Category;

int astInit();
int astConnect(char * username, char *secret, char *host, int port);
int astDeconnect();

int astPeerGet(char *peer, Peer *p);
int astPeerGetList(Peer p[], int *len);
int astPeerSave(Peer *p);
int astPeerDel(Peer *p);

int astRegistryGetList(Registry r[], int *len);
int astRegistryGet(Registry *r);
int astRegistrySave(Registry *r);

int astCategoryGet(char *strCategory, Category *c_out);
int astCategoryDel(Category *c_in);
int astCategorySave(Category *c_in);

#endif
