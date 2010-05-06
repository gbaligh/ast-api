#ifndef SIPCONF_H_INCLUDED
#define SIPCONF_H_INCLUDED

#include "common.h"

int astSipConfUpdateParamValue(astSipParam param,char *category, char *value);
int astSipConfInsertParamValue(astSipParam param,char *category, char *value);

#endif // SIPCONF_H_INCLUDED
