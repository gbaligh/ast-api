/*
 * libast-api - library for using Asterisk Manager API.
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
 * You should have received a copy of the GNU General Public License
 *   along with libast-api.  If not, see <http://www.gnu.org/licenses/>.
 */
/*******************************************************************************
 *  @file    action.c
 *  @brief   Base Functions implementation for the ASTMAN API.
 *  @author  Baligh.GUESMI Emira.MHAROUECH Olivier.BENEZE
 *  @version 0.1
 *  @date    26 Avril 2010
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

extern astContext ast_api;


char* astResponseGetHeaderValue(char *header)
{
    return astman_get_header(&ast_api.m, header);
}

int astResponseIsEventList()
{
    if(strncasecmp("Start", astResponseGetHeaderValue("EventList"), 5)==0)
        return ASTMAN_SUCCESS;
    return ASTMAN_FAILURE;
}
