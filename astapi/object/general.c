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
 *  @file general.c
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100523
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astapi.h"
#include "astlog.h"
#include "category.h"
#include "user.h"

#define STR_CATEGORY_GENERAL        "general"

static Category _c_general_;
static char _loaded;

static int astGeneralLoad(int force)
{
    int ret = 0;

    astlog_init();

    if((!force)&&(_loaded)) {
        astlog(ASTLOG_INFO, "using cached informations");
        ret = ASTMAN_SUCCESS;
        goto Exit;
    }

    if(!(ret = astCategoryGet(USER_FILENAME, STR_CATEGORY_GENERAL,
                    &_c_general_))) {
            astlog(ASTLOG_ERROR, "Get Category Failed");
            goto Exit;
    }

    /* set cached informations */
    _loaded = 1;

Exit:
    astlog_end();
    return ret;
}

Category* astGeneralGetCategory()
{
    if(!_loaded) {
        astlog(ASTLOG_INFO, "Loading %s Category", STR_CATEGORY_GENERAL);
        astGeneralLoad(0);
    }
    return &_c_general_;
}

int astGeneralSave()
{
    int ret = 0;

    if(_loaded)
        astCategorySave(USER_FILENAME, &_c_general_);

    return ret;
}
