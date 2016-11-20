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
 *  @file connection.c
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100524
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "astlog.h"
#include "astman.h"

static struct mansession *gSession;
static int _is_connected = 0;
static char gUsername[80];
static char gSecret[60];
static char gHost[20];
static int gPort;
/*******************************************************************************
 *  \fn int astInit()
 *  \brief
 *  \return
 ******************************************************************************/
int astInit()
{
    gSession = NULL;
    _is_connected = 0;
    return ASTMAN_SUCCESS;
}
/*******************************************************************************
 *  \fn int astConnect(char * username, char *secret, char *host, int port)
 *  \brief
 *  \return
 ******************************************************************************/
int astConnect(char * username, char *secret, char *host, int port)
{
    int res = ASTMAN_SUCCESS;
    astlog_init();
    if(astman_strlen_zero(username)) {
        astlog(ASTLOG_WARNING, "Username for Login is empty");
    }

    strncpy(gUsername, username, 80);
    strncpy(gSecret, secret, 60);
    strncpy(gHost, host, 20);
    gPort = port;

    gSession = astman_open();
    gSession->debug = 0;
    astman_connect(gSession, gHost, gPort);
    if(astman_login(gSession, gUsername, gSecret) == ASTMAN_FAILURE)
    {
        astlog(ASTLOG_ERROR, "Error in authorization");
        res = ASTMAN_FAILURE;
        goto Exit;
    }
    _is_connected = 1; /* set connected to TRUE */
Exit:
    astlog_end();
    return res;
}
/*******************************************************************************
 *  \fn int astDisconnect()
 *  \brief
 *  \return
 ******************************************************************************/
int astDisconnect()
{
    astlog_init();
    astman_logoff(gSession);
    astman_disconnect(gSession);
    _is_connected = 0; // FIX ISSUE 1:  chrisTr1987
    astlog_end();
    return ASTMAN_SUCCESS;
}
/*******************************************************************************
 *  \fn int astIsConnected()
 *  \brief
 *  \return
 ******************************************************************************/
int astIsConnected()
{
    return _is_connected;
}
/*******************************************************************************
 *  \fn char* astConnectionGetUsername()
 *  \brief
 *  \return
 ******************************************************************************/
char* astConnectionGetUsername()
{
    return gUsername;
}
/*******************************************************************************
 *  \fn char* astConnectionGetUsername()
 *  \brief
 *  \return
 ******************************************************************************/
char* astConnectionGetPassword()
{
    return gSecret;
}
/*******************************************************************************
 *  \fn char* astConnectionGetUsername()
 *  \brief
 *  \return
 ******************************************************************************/
char* astConnectionGetHost()
{
    return gHost;
}
/*******************************************************************************
 *  \fn char* astConnectionGetUsername()
 *  \brief
 *  \return
 ******************************************************************************/
int astConnectionGetPort()
{
    return gPort;
}
/*******************************************************************************
 *  \fn char* astConnectionGetUsername()
 *  \brief
 *  \return
 ******************************************************************************/
struct mansession* astConnectionGetSession()
{
    return gSession;
}
