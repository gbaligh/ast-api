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
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "sipconf.h"

extern astContext ast_api;
static const char * const fileName = "sip.conf.test";
static const char * const generalContext = "general";
static message_t GeneralConf;
static int get_done = 0;

static const astMap astSipConfParamMap[] = {
    {PARAM_SIP_CONTEXT, "context"},
    {PARAM_SIP_ALLOW_GUEST, "allowguest"},
    {PARAM_SIP_ALLOW_OVERLAP, "allowoverlap"},
    {PARAM_SIP_REALM, "realm"},
    {PARAM_SIP_UDP_BIND_ADDRESS, "udpbindaddres"},
    {PARAM_SIP_TCP_ENABLED, "tcpenabled"},
    {PARAM_SIP_TCP_BIND_ADDRESS, "tcpbindaddress"},
    {PARAM_SIP_SRV_LOOKUP, "srvlookup"},
    {PARAM_SIP_PEDANTIC, "pedantic"},
    {PARAM_SIP_MAX_EXPIRY, "maxexpiry"},
    {PARAM_SIP_MIN_EXPIRY, "minexpiry"},
    {PARAM_SIP_DEFAULT_EXPIRY, "defaultexpiry"},
    {PARAM_SIP_MWI_EXPIRY, "mwiexpiry"},
    {PARAM_SIP_BUGGY_MWI, "buggymwi"},
    {PARAM_SIP_MW_EXTEN, "mwexten"},
    {PARAM_SIP_DISALLOW, "disallow"},
    {PARAM_SIP_ALLOW, "allow"},
    {PARAM_SIP_LANGUAGE, "language"},
    {PARAM_SIP_DTMF_MODE, "dtmfmode"},
    {PARAM_SIP_COMPACT_FORM, "caompactform"},
    {PARAM_SIP_NAT, "nat"},
    {PARAM_SIP_CANREINVITE, "canreinvite"},
    {PARAM_SIP_ALLOW_SUBSCRIBE, "allowsubscribe"}
};


static const astMap astSipConfPeerParamMap[] = {
{PARAM_SIP_PEER_CAHNNEL_TYPE, "Channeltype"},
{PARAM_SIP_PEER_OBJECT_NAME, "ObjectName"}
//{"ChanObjectType"
/*{"SecretExist"
{"RemoteSecretExist"
{"MD5SecretExist"
{"Context"
{"Language"
{"AMAflags"
{"CID-CallingPres"
{"Callgroup"
{"Pickupgroup"
{"VoiceMailbox"
{"TransferMode"
{"LastMsgsSent"
{"Call-limit"
{"Busy-level"
{"MaxCallBR"
{"Dynamic"
{"Callerid"
{"RegExpire"
{"SIP-AuthInsecure"
{"SIP-NatSupport"
{"ACL"
{"SIP-CanReinvite"
{"SIP-DirectMedia"
{"SIP-PromiscRedir"
{"SIP-UserPhone"
{"SIP-VideoSupport"
{"SIP-TextSupport"
{"SIP-T.38Support"
{"SIP-T.38EC"
{"SIP-T.38MaxDtgrm"
{"SIP-Sess-Timers"
{"SIP-Sess-Refresh"
{"SIP-Sess-Expires"
{"SIP-Sess-Min"
{"SIP-DTMFmode"
{"ToHost"
{"Address-IP"
{"Address-Port"
{"Default-addr-IP"
{"Default-addr-port"
{"Default-Username"
{"Codecs"
{"CodecOrder"
{"Status"
{"SIP-Useragent"
{"Reg-Contact"
{"QualifyFreq"
{"Parkinglot"*/
};



int astSipConfGetPeer(char *peer)
{
    char actionid[10];
    int rv = 0;

    snprintf(actionid, 10, "%s", __FUNCTION__);
    rv = astSipShowPeer(peer, actionid);

    if(rv > 0 && response_is(&ast_api.m, "Success"))
    {
        astlog(ASTLOG_INFO, "%s: OK", __FUNCTION__);
    } else
    {
        astlog(ASTLOG_ERROR, "%s: Response ERROR", __FUNCTION__);
    }
    //astman_dump_message(&ast_api.m);

    return ASTMAN_SUCCESS;
}

int astSipConfGetPeerParam(char *peer, astSipPeerParam param, char* value, int len)
{
    int i = 0;
    astSipConfGetPeer(peer);
    for(i=0; i<ast_api.m.hdrcount; i++)
    {
        if(strlen(astman_get_header(&ast_api.m, astSipConfPeerParamMap[param].str)))
        {
            strncpy(value, astman_get_header(&ast_api.m, astSipConfPeerParamMap[param].str), len);
            astlog(ASTLOG_INFO, "%s: %s=%s",__FUNCTION__, astSipConfPeerParamMap[param].str, value);
            break;
        }

    }
    return ASTMAN_SUCCESS;
}

int astSipConfSetPeerParam(message_t *Peer, astSipParam param, char* value)
{
    char category[MAX_LEN];
    int rv = 0;
    if(!(rv =astSipConfUpdateParamValue(param, category, value)))
    {
        rv = astSipConfInsertParamValue(param, category, value);
    }
    return rv;
}

int astSipConfGetGeneralConfig()
{
    return ASTMAN_SUCCESS;
}

int astSipConfGetGeneralParam(astSipParam param, char *value[], int *size)
{
    if(value == NULL)
        return ASTMAN_FAILURE;

    int i = 0;
    int found = 0;
    if(!get_done)
        astSipConfGetGeneralConfig();
    for(i=0; found<(*size) && i<GeneralConf.hdrcount; i++)
    {
        char *begin = NULL;
        char *end = NULL;
        if(NULL!=(begin=strstr(GeneralConf.headers[i], astSipConfParamMap[param].str)))
        {
            end = begin+strlen(astSipConfParamMap[param].str);
            if((*(end)=='=')&&(*(begin-1)==' '))
            {
                value[found] = strstr(GeneralConf.headers[i], "=")+1;
                found++;
            }
        }

    }
    *size = found;
    return ASTMAN_SUCCESS;
}

int astSipConfUpdateParamValue(astSipParam param,char *category, char *value)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;

    char params[MAX_LEN] = "";
    int rv = 0;
    astman_add_param(params, sizeof(params), "SrcFilename", fileName);
    astman_add_param(params, sizeof(params), "DstFilename", fileName);
    astman_add_param(params, sizeof(params), "Reload", "no");
    astman_add_param(params, sizeof(params), "Action-000000", "update");
    astman_add_param(params, sizeof(params), "Cat-000000", category);
    astman_add_param(params, sizeof(params), "Var-000000", astSipConfParamMap[param].str);
    astman_add_param(params, sizeof(params), "Value-000000", value);

    astman_manager_action_params(ast_api.s, "updateconfig", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if(rv < 0 || !response_is(&ast_api.m, "Success"))
    {
        astlog(ASTLOG_ERROR, "%s: === Begin ==", __FUNCTION__);
        astman_dump_message(&ast_api.m);
        astlog(ASTLOG_ERROR, "%s: === End ==", __FUNCTION__);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}


int astSipConfInsertParamValue(astSipParam param,char *category, char *value)
{
    if(!ast_api.connected)
        return ASTMAN_FAILURE;

    char params[MAX_LEN] = "";
    int rv = 0;
    astman_add_param(params, sizeof(params), "SrcFilename", fileName);
    astman_add_param(params, sizeof(params), "DstFilename", fileName);
    astman_add_param(params, sizeof(params), "Reload", "no");
    astman_add_param(params, sizeof(params), "Action-000000", "append");
    astman_add_param(params, sizeof(params), "Cat-000000", category);
    astman_add_param(params, sizeof(params), "Var-000000", astSipConfParamMap[param].str);
    astman_add_param(params, sizeof(params), "Value-000000", value);

    astman_manager_action_params(ast_api.s, "updateconfig", params);
    rv = astman_wait_for_response(ast_api.s, &ast_api.m, 0);
    if(rv < 0 || !response_is(&ast_api.m, "Success"))
    {
        astlog(ASTLOG_ERROR, "%s: === Begin ==", __FUNCTION__);
        astman_dump_message(&ast_api.m);
        astlog(ASTLOG_ERROR, "%s: === End ==", __FUNCTION__);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}
