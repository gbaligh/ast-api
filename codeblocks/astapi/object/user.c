/********************************************************************
 * astapi - library for using Asterisk Manager API.
 * Copyright (C) 2010 Baligh GUESMI
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc.,
 ********************************************************************/
/********************************************************************
 *  @file user.c
 *  @brief user controle interface
 *  @author Baligh.GUESMI
 *  @date 20100522
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astapi.h"
#include "astlog.h"
#include "peer.h"
#include "general.h"
#include "user.h"
/*******************************************************************************
 * @fn int astTrunkGetList(Peer p[], int *len)
 * @brief Get the List of all remote Users, configured in Asterisk
 * @param p[]: list of pre-allocated Users
 * @param len: number of pre-allocated elements in the User list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
int astTrunkUserGetList(Peer p[], int *len)
{
    int ret = 0;
    astlog_init();
    if(!(ret = astPeerGetList(p, len))) {
        astlog(ASTLOG_ERROR, "astPeerGetList failed");
        goto Exit;
    }
    int i = 0;
    for(i=0;i<*len;i++) {
        if(strncmp(p[i].objectName, TRUNK_USER_PREFIX, strlen(TRUNK_USER_PREFIX))) {
            /* remove Element from list */
            memmove(&p[i], &p[i+1], sizeof(Peer) * ((*len) - i - 1));
            i--;
            (*len)--;
        }
        //else {
            //strncpy(p[i].c.cat, p[i].objectName, MAX_NAME_LEN);
            /* remove prefix */
            //removePrefix(p[i].objectName, TRUNK_USER_PREFIX);
        //}
    }
Exit:
    astlog_end();
    return ret;
}
/******************************************************************************
 * @fn int astTrunkGet(char *strTrunk, Peer *p)
 * @brief Get Trunk informations
 * @param IN strTrunk
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astTrunkUserGet(char *strTrunk, Peer *p)
{
    int ret = 0;
    char tmp[MAX_NAME_LEN];
    astlog_init();

    addPrefix(tmp, strTrunk, TRUNK_USER_PREFIX);
    astlog(ASTLOG_INFO, "Searching for [%s] ...", tmp);

    if(!(ret = astPeerGet(tmp, p))) {
        astlog(ASTLOG_ERROR, "astPeerGet failed");
        ret = ASTMAN_FAILURE;
        goto Exit;
    }
    //strncpy(p->c.cat, p->objectName, MAX_NAME_LEN);
    //removePrefix(p->objectName, TRUNK_USER_PREFIX);
Exit:
    astlog_end();
    return ret;
}
/*******************************************************************************
 * @fn int astUserGetList(Peer p[], int *len)
 * @brief Get the List of all local Users, configured in Asterisk
 * @param p[]: list of pre-allocated Users
 * @param len: number of pre-allocated elements in the User list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
int astUserGetList(Peer p[], int *len)
{
    int ret = 0;
    astlog_init();
    if(!(ret = astPeerGetList(p, len))) {
        astlog(ASTLOG_ERROR, "astPeerGetList failed");
        goto Exit;
    }
    int i = 0;
    for(i=0;i<*len;i++) {
        if(strncmp(p[i].objectName, USER_PREFIX, strlen(USER_PREFIX))) {
            /* remove Element from list */
            memmove(&p[i], &p[i+1], sizeof(Peer) * ((*len) - i - 1));
            i--;
            (*len)--;
        }
        //else {
            //strncpy(p[i].c.cat, p[i].objectName, MAX_NAME_LEN);
            /* remove prefix */
            //removePrefix(p[i].objectName, USER_PREFIX);
        //}
    }
Exit:
    astlog_end();
    return ret;
}
/******************************************************************************
 * @fn int astUserGet(char *strUser, Peer *p)
 * @brief Get informations from Asterisk using the SipShowPee Action, and parse
 *        response
 * @param IN strUser
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astUserGet(char *strUser, Peer *p)
{
    int ret = 0;
    char tmp[MAX_NAME_LEN];
    astlog_init();

    addPrefix(tmp, strUser, USER_PREFIX);
    astlog(ASTLOG_INFO, "Searching for [%s] ...", tmp);

    if(!(ret = astPeerGet(tmp, p))) {
        astlog(ASTLOG_ERROR, "astPeerGet failed");
        ret = ASTMAN_FAILURE;
        goto Exit;
    }
    //strncpy(p->c.cat, p->objectName, MAX_NAME_LEN);
    //removePrefix(p->objectName, USER_PREFIX);
Exit:
    astlog_end();
    return ret;
}
/******************************************************************************
 * @fn int astUserSave(Peer *p)
 * @brief Save Informations to Asterisk File
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astUserSave(Peer *p)
{
    return astPeerSave(USER_FILENAME, p);
}
/******************************************************************************
 * @fn char* astUserGetSecret(Peer *p)
 * @brief Get Peer's Secret
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetSecret(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "secret");
}
/******************************************************************************
 * @fn char* astUserGetMD5Secret(Peer *p)
 * @brief Get Peer's MD5 Secret Parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetMD5Secret(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "md5secret");
}
/******************************************************************************
 * @fn char* astUserGetPhoneModel(Peer *p)
 * @brief Get Peer's PhoneModel Parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetPhoneModel(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "phonemodel");
}
/******************************************************************************
 * @fn char* astUserGetPhoneMac(Peer *p)
 * @brief Get Peer's Phone MAC parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetPhoneMac(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "phonemac");
}
/******************************************************************************
 * @fn char* astUserGetUserName(Peer *p)
 * @brief Get Peer's user name parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetUserName(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "username");
}
/******************************************************************************
 * @fn char* astUserGetType(Peer *p)
 * @brief Get Type parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetType(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "type");
}
/******************************************************************************
 * @fn char* astPeerGetRemoteSecret(char *filename, Peer *p)
 * @brief Get Peer's Remote Secret Parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetRemoteSecret(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "remoteSecret");
}
/******************************************************************************
 * @fn char* astPeerGetFromDomain(char *filename, Peer *p)
 * @brief Get Peer's From Domain parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetFromDomain(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "fromDomain");
}
/******************************************************************************
 * @fn char* astPeerGetFromUser(char *filename, Peer *p)
 * @brief Get From User parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetFromUser(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "fromUser");
}
/******************************************************************************
 * @fn char* astPeerGetOutboundProxy(char *filename, Peer *p)
 * @brief Get Peer's Outbound Proxy address parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetOutboundProxy(Peer *p)
{
    return astPeerGetParam(USER_FILENAME, p, "outboundproxy");
}
/******************************************************************************
 * @fn int astTrunkAddRegister(char *strTrunk, Peer *p)
 * @brief Get Trunk informations
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astTrunkUserAddRegister(Peer *p)
{
    char sReg[1025] = "";
    char *s = NULL;
    char *d = NULL;
    char *h = NULL;
    char *a = NULL;
    char *u = NULL;

    astlog_init();

    a= astUserGetFromUser(p);
    s = astUserGetRemoteSecret(p);
    h = p->objectName;
    d = astUserGetFromDomain(p);
    u = astUserGetUserName(p);

    snprintf(sReg, 1024, "%s@%s:%s:%s@%s:%d",
             u?u:"",
             d?d:"",
             s?s:"",
             a?a:"",
             h?h:"",
             p->ipPort);

    astlog(ASTLOG_INFO, "Reg: %s", sReg);

    Category* c;
    c = astGeneralGetCategory();
    int i = -1;

    if(( i = astCategoryGetParamIndex(c,"register",p->objectName))<0) {
        astCategoryAddParam(c, "register", sReg);
    } else {
        astCategorySetParamValueAt(c, i, sReg);
    }

    astlog_end();
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @fn int astTrunkEnableRegister(char *strTrunk, Peer *p)
 * @brief Get Trunk informations
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astTrunkUserEnableRegister(Peer *p)
{
    char sReg[1025] = "";
    char *s = NULL;
    char *d = NULL;
    char *h = NULL;
    char *a = NULL;
    char *u = NULL;

    astlog_init();

    a= astUserGetFromUser(p);
    s = astUserGetRemoteSecret(p);
    h = p->objectName;
    d = astUserGetFromDomain(p);
    u = astUserGetUserName(p);

    snprintf(sReg, 1024, "%s@%s:%s:%s@%s:%d",
             u?u:"",
             d?d:"",
             s?s:"",
             a?a:"",
             h?h:"",
             p->ipPort);

    astlog(ASTLOG_INFO, "Reg: %s", sReg);

    Category* c;
    c = astGeneralGetCategory();
    int i = -1;

    if(( i = astCategoryGetParamIndex(c,"register",p->objectName))<0) {
        astCategoryAddParam(c, "register", sReg);
    } else {
        astCategorySetParamValueAt(c, i, sReg);
    }

    astCategorySave(USER_FILENAME, c);

    astlog_end();
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @fn int astTrunkGet(char *strTrunk, Peer *p)
 * @brief Get Trunk informations
 * @param IN strTrunk
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
/*int astTrunkUserDisableRegister(char *strTrunk, Peer *p)
{

}*/
