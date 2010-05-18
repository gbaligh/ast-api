/* $Id: sampleAction.c,v 1.4 2010/05/17 09:32:43 bguesmi Exp $ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "astapi.h"


int main(void)
{

    astInit();
    if(!astConnect("admin", "admin", "127.0.0.1", -1)){
        return 1;
    }

    int i = 15;
    int j = 0;
    int x = 5;

    Peer peerlist[15];
    if(!astPeerGetList(peerlist, &i)) {
        return 1;
    }
    for(j=0;j<i;j++) {
        printf("----------------- peer[%d].Name:\t\t%s\n", j, peerlist[j].objectName);
        printf("----------------- peer[%d].Useragent:\t%s\n", j, peerlist[j].userAgent);
        printf("----------------- peer[%d].ipAddress:\t%s\n", j, peerlist[j].ipAddress);
        printf("----------------- peer[%d].mac:\t%s\n", j, peerlist[j].mac);
    }

    Registry rlist[5];
    if(!astRegistryGetList(rlist, &x)) {
        return 1;
    }
    for(j=0;j<x;j++) {
        printf("----------------- registry[%d].username:\t%s\n", j, rlist[j].userName);
        printf("----------------- registry[%d].host:\t%s\n", j, rlist[j].host);
        printf("----------------- Registry[%d].state:\t%s\n", j, rlist[j].state);
    }
    //astPeerAdd(&peerlist[0]);
   /* Peer p;
    astPeerGet("baligh", &p);*/

    Category c;
    if(astCategoryGet("3300",&c)) {
        printf("%s:{", c.cat);
        for(j=0;j<c.nb_params;j++){
            printf("%s=%s ",c.params[j].name,c.params[j].value);
        }
        printf("}\n");
        strncpy(c.params[c.nb_params].name, "type", 4);
        strncpy(c.params[c.nb_params++].value, "friend", 6);
        strncpy(c.params[c.nb_params].name, "host", 4);
        strncpy(c.params[c.nb_params++].value, "dynamic", 7);
        astCategorySave(&c);
    }

    strncpy(peerlist[0].objectName, "baligh", 6);
    strncpy(peerlist[0].secret, "PASSWORD", 8);
    peerlist[0].natSupport = 1;
    astPeerSave(&peerlist[0]);

    //astPeerDel(&peerlist[0]);

    astDeconnect();
    return 0;
}
