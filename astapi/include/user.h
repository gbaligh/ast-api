#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

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
 *  @file user.h
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100523
 *******************************************************************/
#include <string.h>
#include "peer.h"

#define USER_FILENAME               "sip.conf"
#define USER_PREFIX                 "astuser-"
#define TRUNK_USER_PREFIX           "asttrunk-"
/*******************************************************************************
 * @fn int astPeerGetList(char *filename, Peer p[], int *len)
 * @brief Get the List of all Peer, configured in Asterisk
 * @param filename: configuration file name
 * @param p[]: list of pre-allocated Peers
 * @param len: number of pre-allocated elements in the Peer list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
static inline __attribute__((always_inline)) void addPrefix(char *dst,
                                                            char *strname,
                                                            char *prefix)
{
    if(!strname)
        return;
    if(dst)
        snprintf(dst, MAX_NAME_LEN, "%s%s", prefix, strname);
    else
        snprintf(strname, MAX_NAME_LEN, "%s%s", prefix, strname);
}
/*******************************************************************************
 * @fn int astPeerGetList(char *filename, Peer p[], int *len)
 * @brief Get the List of all Peer, configured in Asterisk
 * @param filename: configuration file name
 * @param p[]: list of pre-allocated Peers
 * @param len: number of pre-allocated elements in the Peer list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
static inline __attribute__((always_inline)) void removePrefix(char *strname,
                                                               char *prefix)
{
    if(strlen(strname)<strlen(prefix)+1) {
        return;
    }
    snprintf(strname, MAX_NAME_LEN, "%s", strname+strlen(prefix));
}
/*******************************************************************************
 * @fn int astUserGetList(Peer p[], int *len)
 * @brief Get the List of all local Users, configured in Asterisk
 * @param p[]: list of pre-allocated Users
 * @param len: number of pre-allocated elements in the User list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
int astUserGetList(Peer p[], int *len);

/******************************************************************************
 * @fn char* astUserGetSecret(Peer *p)
 * @brief Get Peer's Secret
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetSecret(Peer *p);

/******************************************************************************
 * @fn int astUserGet(char *strUser, Peer *p)
 * @brief Get informations from Asterisk using the SipShowPee Action, and parse
 *        response
 * @param IN strUser
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astUserGet(char *strUser, Peer *p);

/******************************************************************************
 * @fn int astTrunkGet(char *strTrunk, Peer *p)
 * @brief Get Trunk informations
 * @param IN strTrunk
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astTrunkUserGet(char *strTrunk, Peer *p);

/*******************************************************************************
 * @fn int astTrunkGetList(Peer p[], int *len)
 * @brief Get the List of all remote Users, configured in Asterisk
 * @param p[]: list of pre-allocated Users
 * @param len: number of pre-allocated elements in the User list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
int astTrunkUserGetList(Peer p[], int *len);

/******************************************************************************
 * @fn int astTrunkEnableRegister(char *strTrunk, Peer *p)
 * @brief Get Trunk informations
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astTrunkUserEnableRegister(Peer *p);

/******************************************************************************
 * @fn char* astPeerGetOutboundProxy(char *filename, Peer *p)
 * @brief Get Peer's Outbound Proxy address parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetOutboundProxy(Peer *p);

/******************************************************************************
 * @fn char* astPeerGetFromUser(char *filename, Peer *p)
 * @brief Get From User parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetFromUser(Peer *p);

/******************************************************************************
 * @fn char* astPeerGetFromDomain(char *filename, Peer *p)
 * @brief Get Peer's From Domain parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetFromDomain(Peer *p);

/******************************************************************************
 * @fn char* astPeerGetRemoteSecret(char *filename, Peer *p)
 * @brief Get Peer's Remote Secret Parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetRemoteSecret(Peer *p);

/******************************************************************************
 * @fn char* astUserGetType(Peer *p)
 * @brief Get Type parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetType(Peer *p);

/******************************************************************************
 * @fn char* astUserGetUserName(Peer *p)
 * @brief Get Peer's user name parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetUserName(Peer *p);

/******************************************************************************
 * @fn char* astUserGetPhoneMac(Peer *p)
 * @brief Get Peer's Phone MAC parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetPhoneMac(Peer *p);

/******************************************************************************
 * @fn char* astUserGetPhoneModel(Peer *p)
 * @brief Get Peer's PhoneModel Parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetPhoneModel(Peer *p);

/******************************************************************************
 * @fn char* astUserGetMD5Secret(Peer *p)
 * @brief Get Peer's MD5 Secret Parameter
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetMD5Secret(Peer *p);

/******************************************************************************
 * @fn char* astUserGetSecret(Peer *p)
 * @brief Get Peer's Secret
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astUserGetSecret(Peer *p);

/******************************************************************************
 * @fn int astUserSave(Peer *p)
 * @brief Save Informations to Asterisk File
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astUserSave(Peer *p);
#endif // USER_H_INCLUDED
