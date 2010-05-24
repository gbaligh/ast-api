#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "astapi.h"
#include "connection.h"
#include "category.h"
#include "registry.h"
#include "peer.h"
#include "user.h"

int main(int argc, char *argv[])
{
    astInit();
    if(!astConnect("admin", "admin", "127.0.0.1", -1)) {
        fprintf(stderr, "Connection/Login Failed !!!\n");
        return 1;
    }

    Peer p[10];
    int size = sizeof(p)/sizeof(p[0]);
    astUserGetList(p, &size);
    int i=0;
    for(i=0; i<size; i++) {
        printf("====U=== %s:%s \n", p[i].objectName, astUserGetSecret(&p[i]));
        astUserSave(&p[i]);
    }

    Peer pp;
    astUserGet("baligh", &pp);
    astUserGetSecret(&pp);
    printf("\n**** %s \n", astUserGetSecret(&pp));
    astUserSave(&pp);

    Registry r[10];
    size = sizeof(r)/sizeof(r[0]);
    astRegGetList(r, &size);
    for(i=0; i<size; i++) {
        printf("===R==== %s \n", r[i].host);
    }

    size = sizeof(p)/sizeof(p[0]);
    astTrunkUserGetList(p, &size);
    for(i=0; i<size; i++) {
        printf("===T==== %s (%s)\n", p[i].objectName, astUserGetSecret(&p[i]));
        astUserSave(&p[i]);
    }

    astDisconnect();
    return 0;
}
