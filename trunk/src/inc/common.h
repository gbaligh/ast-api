

/* $Id: common.h,v 1.4 2010/05/17 09:32:43 bguesmi Exp $ */
#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include "astapi.h"
#include "astlog.h"
#include <time.h>
#include <netinet/in.h>  /* struct sockaddr_in */

#define AST_CONF_DIR_MAX_NUMBER 10
#define AST_API_MAX_STR_LENGTH  255
#define AST_API_VERSION_STR_LENGTH 10

#define ASTMAN_HEADER_EVENT                 "Event"


/**
 * @struct  message
 * @brief   The struct representing the message command to send
 */
struct message {
  int hdrcount;                         /**< Header count */
  int gettingdata;                      /**< data */
  char headers[MAX_HEADERS][MAX_LEN];   /**< Headers list */
};
/**
 * @struct  message
 * @brief   The struct of an opened AMI session
 */
struct mansession {
  int fd;                   /**< the discriptor to the socket */
  char inbuf[MAX_LEN];      /**< buffer */
  int inlen;                /**< length of the buffer */
  struct sockaddr_in sin;   /**< address of the socket */
/**
 * @struct  mevent
 * @brief   The struct representing event id and callback
 */
  struct event {
    char *event;    /**< the event ID */
    int (*func)(struct mansession *s, struct message *m); /** < callback associated to this event */
  } events[MAX_EVENTS]; /**< event registred to */
  int eventcount; /**< the real count of event that the session is registred to */
  int debug;    /**< active/desactivated DEBUG */
};

typedef struct mansession mansession_t;
typedef struct message message_t;

struct ast_api_s {
    mansession_t *s;
    struct message m;
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


/**
 * @typedef (*ASTMAN_EVENT_CALLBACK)
 * @brief   CallBack Event proto-type
 */
typedef int (*ASTMAN_EVENT_CALLBACK)(struct mansession *, struct message *);
/**
 * @fn  astman_strlen_zero(const char *s)
 * @brief inline function to test if the given char is not empty
 * @param IN s
 * @return >0 if the given char is not empty
 */
static inline __attribute__((always_inline)) int astman_strlen_zero(const char *s)
{
  return (!s || (*s == '\0'));
}
/**
 * @def esponse_is(M, RES)
 * @brief Get response Code
 */
#define response_is(M, RES)  !strcasecmp(astman_get_header(M, "Response"), RES)

int astCoreSettings(char *actionid);
int astCoreStatus(char *actionid);
void astCategoryAddParam(Category *c, const char * const name, const char * const value);

char *astman_get_header(struct message *m, const char *var);


#endif // COMMON_H_INCLUDED
