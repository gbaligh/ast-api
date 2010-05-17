/* $Id: sipconf.h,v 1.4 2010/05/17 09:32:43 bguesmi Exp $ */
#ifndef SIPCONF_H_INCLUDED
#define SIPCONF_H_INCLUDED

#include "common.h"

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
    {PARAM_SIP_ALLOW_SUBSCRIBE, "allowsubscribe"},
    {PARAM_SIP_TPYPE, "type"},
    {PARAM_SIP_HOST, "host"},
    {PARAM_SIP_SECRET, "secret"},
    {PARAM_SIP_FROMUSER, "fromuser"},
    {PARAM_SIP_CALLERID, "callerid"},
    {PARAM_PROV_MAC, "mac"},
    {PARAM_PROV_MODEL, "ipPhoneModel"},
};

static const astMap astDtmfModeMap[] = {
    {DTMF_NOT_SET, ""},
    {DTMF_INBAND, "inband"},
    {DTMF_RFC2833, "RFC2833"},
    {DTMF_SIPINFO, "info"},
    {DTMF_INBAND + DTMF_RFC2833, "inband, rfc2833"},
    {DTMF_INBAND + DTMF_SIPINFO, "inband, info"},
    {DTMF_RFC2833 + DTMF_SIPINFO, "rfc2833, info"},
    {DTMF_INBAND + DTMF_RFC2833 + DTMF_SIPINFO, "auto"}
};

int astCategoryGet(char *strCategory, Category *c_out);
int astCategorySave(Category *c_in);

#endif // SIPCONF_H_INCLUDED
