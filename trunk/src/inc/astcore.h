#ifndef _ASTCORE_H
#define _ASTCORE_H

#include "common.h"

struct ast_core_setting_s {
    char AMIVersion[AST_API_VERSION_STR_LENGTH];
    char asteriskVersion[AST_API_VERSION_STR_LENGTH];
    char systemName[AST_API_VERSION_STR_LENGTH];
    int  coreMaxCalls;
    char coreMaxLoadAvg[AST_API_VERSION_STR_LENGTH];
    char coreRunUser[AST_API_VERSION_STR_LENGTH];
    char coreRunGroup[AST_API_VERSION_STR_LENGTH];
    int  coreMaxFileHandlers;
    int  coreRealTimeEnabled;
    int  coreCDREnabled;
    int  HTTPEnabled;
};

enum astCoreSettingHeaders {
    AMIVersion,
    AsteriskVersion,
    SystemName,
    CoreMaxCalls,
    CoreMaxLoadAvg,
    CoreRunUser,
    CoreRunGroup,
    CoreMaxFileHandlers,
    CoreRealTimeEnabled,
    CoreCDREnabled,
    HTTPEnabled
};

int coreSettingFromParseMessage(message_t *m);

char *coreGetHeader(astCoreSettingHeaders type);


#endif
