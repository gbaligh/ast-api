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

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "common.h"
#include "astcore.h"

#define OBJECT_NAME "Core"

extern astContext ast_api;

typedef enum {
    PARAM_CORE_SETTING_ASTERISK_VERSION,
    PARAM_CORE_SETTING_AMI_VERSION,
    PARAM_CORE_SETTING_VAR_LIST_LENGTH
}astCoreSettingParam;
typedef enum {
    PARAM_CORE_STARTUP_TIME,
    PARAM_CORE_RELOAD_TIME,
    PARAM_CORE_CURRENT_CALLS,
    PARAM_CORE_VAR_LIST_LENGTH
}astCoreStatusParam; /* This entry must always be the last in the list */


static const astMap astCoreSetingParamMap[] = {
    {PARAM_CORE_ASTERISK_VERSION, "AsteriskVersion"},
    {PARAM_CORE_AMI_VERSION, "AMIversion"},
};
static const astMap astCoreStatusParamMap[] = {
    {PARAM_CORE_STARTUP_TIME, "CoreStartupTime"},
    {PARAM_CORE_RELOAD_TIME, "CoreReloadTime"},
    {PARAM_CORE_CURRENT_CALLS, "CoreCurrentCalls"},
};

/*******************************************************************************
 * @brief Get All Setting from Asterisk Core
 ******************************************************************************/
char* astCoreGetSetting(CoreSetting *setting)
{
    astCoreSettings(OBJECT_NAME);
    if(strlen(astman_get_header(&ast_api.m,
        astCoreSettingParamMap[PARAM_CORE_ASTERISK_VERSION].str)))
    {
        strncpy(setting->AsteriskVersion, astman_get_header(&ast_api.m, astCoreSettingParamMap[PARAM_CORE_ASTERISK_VERSION].str), MAX_LEN);
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreSettingParamMap[PARAM_CORE_ASTERISK_VERSION].str, AsteriskVersion);
    }
    if(strlen(astman_get_header(&ast_api.m,
        astCoreSettingParamMap[PARAM_CORE_AMI_VERSION].str)))
    {
        strncpy(setting->AMIVersion, astman_get_header(&ast_api.m, astCoreSettingParamMap[PARAM_CORE_AMI_VERSION].str), MAX_LEN);
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreSettingParamMap[PARAM_CORE_AMI_VERSION].str, AMIVersion);
    }
    /* get other parameters from CoreStatus Actions */
    astCoreStatus(OBJECT_NAME);
    if(strlen(astman_get_header(&ast_api.m, astCoreStatusParamMap[PARAM_CORE_STARTUP_TIME].str)))
    {
        strncpy(setting->StartupTime, astman_get_header(&ast_api.m, astCoreStatusParamMap[PARAM_CORE_STARTUP_TIME].str), MAX_LEN);
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreStatusParamMap[PARAM_CORE_STARTUP_TIME].str, StartupTime);
    }
    if(strlen(astman_get_header(&ast_api.m, astCoreStatusParamMap[PARAM_CORE_RELOAD_TIME].str)))
    {
        strncpy(setting->ReloadTime, astman_get_header(&ast_api.m, astCoreStatusParamMap[PARAM_CORE_RELOAD_TIME].str), MAX_LEN);
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreStatusParamMap[PARAM_CORE_RELOAD_TIME].str, ReloadTime);
    }
    if(strlen(astman_get_header(&ast_api.m, astCoreStatusParamMap[PARAM_CORE_CURRENT_CALLS].str)))
    {
        strncpy(setting->CurrentCalls, astman_get_header(&ast_api.m, astCoreStatusParamMap[PARAM_CORE_CURRENT_CALLS].str), MAX_LEN);
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreStatusParamMap[PARAM_CORE_CURRENT_CALLS].str, CurrentCalls);
    }
Exit:
    return CoreSetting.AsteriskVersion;
}
