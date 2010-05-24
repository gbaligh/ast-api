#ifndef REGISTRY_H_INCLUDED
#define REGISTRY_H_INCLUDED

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
 *  @file registry.h
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100524
 *******************************************************************/
#include "astapi.h"


typedef struct {
    char host[MAX_VALUE_LEN];
    char userName[MAX_VALUE_LEN];
    char state[MAX_VALUE_LEN];
    char registrationTime[MAX_VALUE_LEN];
    int port;
    int refresh;
} __attribute__((packed)) Registry;

/*******************************************************************************
 * @fn int astPeerGetList(char *filename, Peer p[], int *len)
 * @brief Get the List of all Peer, configured in Asterisk
 * @param p[]: list of pre-allocated Peers
 * @param len: number of pre-allocated elements in the Peer list
 * @return ASTMAN_FAILURE / ASTMAN_SUCCESS
 ******************************************************************************/
int astRegGetList(Registry r[], int *len);

#endif // REGISTRY_H_INCLUDED
