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

#define OBJECT_NAME "Core"

extern astContext ast_api;

static struct {
    char *AMIversion;
    char *AsteriskVersion;
    char *CoreMaxCalls;
    char *CoreStartupTime;
    char *CoreReloadTime;
    char *CoreCurrentCalls;
} CoreSetting = {NULL,NULL,NULL,NULL,NULL,NULL};


typedef enum {
    PARAM_CORE_ASTERISK_VERSION,
    PARAM_CORE_AMI_VERSION,
    PARAM_CORE_STARTUP_TIME,
    PARAM_CORE_RELOAD_TIME,
    PARAM_CORE_CURRENT_CALLS,
    PARAM_CORE_VAR_LIST_LENGTH
}astCoreParam; /* This entry must always be the last in the list */


static const astMap astCoreParamMap[] = {
    {PARAM_CORE_ASTERISK_VERSION, "AsteriskVersion"},
    {PARAM_CORE_AMI_VERSION, "AMIversion"},
    {PARAM_CORE_STARTUP_TIME, "CoreStartupTime"},
    {PARAM_CORE_RELOAD_TIME, "CoreReloadTime"},
    {PARAM_CORE_CURRENT_CALLS, "CoreCurrentCalls"},
};

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
char* astCoreGetAsteriskVersion()
{
    if(!astman_strlen_zero(CoreSetting.AsteriskVersion))
        goto Exit;
    static char AsteriskVersion[MAX_LEN];
    astCoreSettings(OBJECT_NAME);
    if(strlen(astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_ASTERISK_VERSION].str)))
    {
        strncpy(AsteriskVersion, astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_ASTERISK_VERSION].str), MAX_LEN);
        CoreSetting.AsteriskVersion = AsteriskVersion;
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreParamMap[PARAM_CORE_ASTERISK_VERSION].str, AsteriskVersion);
    }
Exit:
    return CoreSetting.AsteriskVersion;
}

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
char* astCoreGetAMIVersion()
{
    if(!astman_strlen_zero(CoreSetting.AMIversion))
        goto Exit;
    static char AMIVersion[MAX_LEN];
    astCoreSettings(OBJECT_NAME);
    if(strlen(astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_AMI_VERSION].str)))
    {
        strncpy(AMIVersion, astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_AMI_VERSION].str), MAX_LEN);
        CoreSetting.AMIversion = AMIVersion;
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreParamMap[PARAM_CORE_AMI_VERSION].str, AMIVersion);
    }
Exit:
    return CoreSetting.AMIversion;
}

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
char* astCoreGetStartupTime()
{
    if(!astman_strlen_zero(CoreSetting.CoreStartupTime))
        goto Exit;
    static char StartupTime[MAX_LEN];
    astCoreStatus(OBJECT_NAME);
    if(strlen(astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_STARTUP_TIME].str)))
    {
        strncpy(StartupTime, astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_STARTUP_TIME].str), MAX_LEN);
        CoreSetting.CoreStartupTime = StartupTime;
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreParamMap[PARAM_CORE_STARTUP_TIME].str, StartupTime);
    }
Exit:
    return CoreSetting.CoreStartupTime;
}

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
char* astCoreGetReloadTime()
{
    if(!astman_strlen_zero(CoreSetting.CoreReloadTime))
        goto Exit;
    static char ReloadTime[MAX_LEN];
    astCoreStatus(OBJECT_NAME);
    if(strlen(astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_RELOAD_TIME].str)))
    {
        strncpy(ReloadTime, astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_RELOAD_TIME].str), MAX_LEN);
        CoreSetting.CoreReloadTime = ReloadTime;
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreParamMap[PARAM_CORE_RELOAD_TIME].str, ReloadTime);
    }
Exit:
    return CoreSetting.CoreReloadTime;
}

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
char* astCoreGetCurrentCalls()
{
    if(!astman_strlen_zero(CoreSetting.CoreCurrentCalls))
        goto Exit;
    static char CurrentCalls[MAX_LEN];
    astCoreStatus(OBJECT_NAME);
    if(strlen(astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_CURRENT_CALLS].str)))
    {
        strncpy(CurrentCalls, astman_get_header(&ast_api.m, astCoreParamMap[PARAM_CORE_CURRENT_CALLS].str), MAX_LEN);
        CoreSetting.CoreCurrentCalls = CurrentCalls;
        astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astCoreParamMap[PARAM_CORE_CURRENT_CALLS].str, CurrentCalls);
    }
Exit:
    return CoreSetting.CoreCurrentCalls;
}
