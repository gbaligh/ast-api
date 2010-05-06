#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int astDefaultCallback(struct mansession *s, struct message *m);
static ASTMAN_EVENT_CALLBACK defaultCallback = &astDefaultCallback;


int astDefaultCallback(struct mansession *s, struct message *m)
{
    static int i = 0;
    astlog(ASTLOG_WARNING,"%s not implemented called %d times\n", __FUNCTION__, i++);
    //astman_dump_message(&ast_api.m);
    return i;
}


ASTMAN_EVENT_CALLBACK astEventGetDefaultCallback()
{
    return defaultCallback;
}
