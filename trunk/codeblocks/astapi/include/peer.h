#ifndef PEER_H_INCLUDED
#define PEER_H_INCLUDED

/*******************************************************************************
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
 ******************************************************************************/
/*******************************************************************************
 *  @file peer.h
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100524
 ******************************************************************************/
#include "category.h"
/*******************************************************************************
 *  @enum    astDtmfMode
 *  @brief
 ******************************************************************************/
typedef enum {
    DTMF_NOT_SET,
    DTMF_RFC2833,
    DTMF_INBAND,
    DTMF_SIPINFO
} astDtmfMode;
/*******************************************************************************
 *  @struct    Peer
 *  @brief
 ******************************************************************************/
typedef struct {
    astDtmfMode DTMFMode;
    int ipPort;
    int dynamic:1;
    int natSupport:1;
    int secretExist:1;
    int remoteSecretExist:1;
    int md5SecretExist:1;
    int realtimeDevice:1;
    int type;
    int callLimit;
    int busyLevel;
    int regExpire;
    Category c;
    char toHost[MAX_VALUE_LEN];
    char context[MAX_VALUE_LEN];
    char status[MAX_VALUE_LEN];
    char channelType[MAX_VALUE_LEN];
    char objectName[MAX_VALUE_LEN];
    char chanObjectType[MAX_VALUE_LEN];
    char ipAddress[MAX_VALUE_LEN];
    char userAgent[MAX_VALUE_LEN];
    char callerID[MAX_VALUE_LEN];
} __attribute__((packed)) Peer;
/*******************************************************************************
 * @fn int astPeerGetList(char *filename, Peer p[], int *len)
 * @brief Get the List of all Peer, configured in Asterisk
 * @param filename: configuration file name
 * @param p[]: list of pre-allocated Peers
 * @param len: number of pre-allocated elements in the Peer list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
int astPeerGetList(Peer p[], int *len);

/******************************************************************************
 * @fn int astPeerGet(char *filename, char *peer, Peer *p)
 * @brief Get informations from Asterisk using the SipShowPee Action, and parse
 *        response
 * @param filename
 * @param peer
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astPeerGet(char *peer, Peer *p);
/******************************************************************************
 * @fn char* astPeerGetParam(char *filename, Peer *p, char *param)
 * @brief Get Parameter saved in Asterisk's Configuration File
 * @param filename
 * @param p
 * @return VALUE / NULL
 *****************************************************************************/
char* astPeerGetParam(char *filename, Peer *p, char *param);
/******************************************************************************
 * @fn int astPeerSave(char *filename, Peer *p)
 * @brief Save Informations to Asterisk File
 * @param filename
 * @param p
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 *****************************************************************************/
int astPeerSave(char *filename, Peer *p);
#endif // PEER_H_INCLUDED
