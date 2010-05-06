#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED


#include "astman.h"
#include "astlog.h"
#include "action.h"
#include "astapi.h"

#define AST_CONF_DIR_MAX_NUMBER 10
#define AST_API_MAX_STR_LENGTH  255
#define AST_API_VERSION_STR_LENGTH 10



typedef struct mansession mansession_t;
typedef struct message message_t;
typedef int astCoreSettingHeaders;

struct ast_api_s {
    mansession_t *s;
    message_t m;
    char username[AST_API_MAX_STR_LENGTH];
    char secret[AST_API_MAX_STR_LENGTH];
    char host[AST_API_MAX_STR_LENGTH];
    int port;
    int connected;
};
typedef struct ast_api_s astContext;

typedef struct astMap_s {
    const int id;
    const char * const str;
} astMap;

ASTMAN_EVENT_CALLBACK astEventGetDefaultCallback();

int astCoreSettings(char *actionid);
int astCoreStatus(char *actionid);

#endif // COMMON_H_INCLUDED
