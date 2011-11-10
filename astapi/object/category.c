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
 *  @file category.c
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100524
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astapi.h"
#include "action.h"
#include "astlog.h"
#include "connection.h"
#include "config.h"
#include "category.h"

/******************************************************************************
 * @fn astCategoryGet
 * @brief Get an Asterisk Category
 * @param IN strCategory: String caontains the name of the Category (e.: general)
 * @param OUT c_out: Category struct that will caontains the paring result
 * @return ASTMAN_SUCCES - ASTMAN_FAILURE
 *****************************************************************************/
int astCategoryGet(char *filename, char *strCategory, Category *c)
{
    int rv = ASTMAN_FAILURE;
    int i = 0;
    int j =0;
    int found = 0;
    int cat_num = 0;
    char cat_name[MAX_VALUE_LEN];
    char v[MAX_LEN];
    struct message *m;

    astlog_init();

    if(astman_strlen_zero(strCategory)) {
        astlog(ASTLOG_INFO, "Category must be specified");
        return ASTMAN_FAILURE;
    }

    if(!astConfigLoad(filename)) {
        astlog(ASTLOG_ERROR, "astConfigLoad faild");
        rv = ASTMAN_FAILURE;
        goto Exit;
    }
    m = astConfigGetMsg();

    for(i=0; i<m->hdrcount; i++)
    {
        if(strncasecmp("Category", m->headers[i], 8)==0) {
            sscanf(m->headers[i], "Category-%6d: %s", &cat_num, cat_name);
            if(strncasecmp(cat_name, strCategory, strlen(strCategory))==0) {
                found = 1;
                rv = ASTMAN_SUCCESS;
                strncpy(c->cat, cat_name, strlen(cat_name)+1);
            }
            else
                found = 0;
        }
        if((found) && (strncasecmp("Line", m->headers[i], 4)==0)) {
            sscanf(m->headers[i], "Line-%6d-%6d: %s", &cat_num, &(c->params[j].line), v);
            strncpy(c->params[j].value, strstr(v, "=")+1, MAX_VALUE_LEN);
            *(strstr(v, "=")) = '\0';
            strncpy(c->params[j].name, v, MAX_NAME_LEN);
            j++;
        }
    }
    c->nb_params = j;
Exit:
    astlog_end();
    return rv;
}
/******************************************************************************
 * @fn astCategorySave
 * @brief Save Category, or create if it does not existe
 * @param IN c_in: Category to be saved into Asterisk's configuration file
 *****************************************************************************/
int astCategorySave(char *filename, Category *c_in)
{
    int res;
    int i = 0;
    struct message m;
    astlog_init();
    res = astman_update_config_init(filename, filename, 0);
    res = astman_update_config_add_action(UPDATE_ACTION_DEL_CAT,
                                    c_in->cat,
                                    "",
                                    "",
                                    "",
                                    "");
    res = astman_update_config_add_action(UPDATE_ACTION_NEW_CAT,
                                    c_in->cat,
                                    "",
                                    "",
                                    "",
                                    "");

    for(i=0; i<c_in->nb_params; i++) {
        res = astman_update_config_add_action(UPDATE_ACTION_APPEND,
                                    c_in->cat,
                                    c_in->params[i].name,
                                    c_in->params[i].value,
                                    "",
                                    "");
    }
    if(!(res = astman_update_config_execute(astConnectionGetSession(), &m))) {
        astlog(ASTLOG_ERROR, "astman_update_config_execute: Saving Category Failed");
    }
    astlog_end();
    return res;
}
#if 0
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astCategoryCreate(char *filename,Category *c_in)
{
    astlog_init();
    if(!(astUpdateConfig(filename, 0, c_in->cat, "", "", "NewCat"))) {
        astlog(ASTLOG_ERROR, "Error in creating new Category %s", c_in->cat);
        return ASTMAN_FAILURE;
    }
    astlog_end();
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astCategoryDel(char *filename, Category *c_in)
{
    astlog_init();
    if(!(astUpdateConfig(filename, 0, c_in->cat, "", "", "DelCat"))) {
        astlog(ASTLOG_ERROR, "Error in Deleting Category %s", c_in->cat);
        return ASTMAN_FAILURE;
    }
    astlog_end();
    return ASTMAN_SUCCESS;
}
#endif //0
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astCategoryGetParamIndex(Category *c, char * name, char *subs)
{
    astlog_init();
    int i = 0;
    int found_v = astman_strlen_zero(subs);
    for(i=0;i<c->nb_params;i++) {
        if(!strncasecmp(c->params[i].name, name, strlen(name))) {
            if(found_v)
                return i;
            else if((strstr(c->params[i].value, subs)))
                return i;
        }
    }
    astlog_end();
    return -1;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
char* astCategoryGetParamValue(Category *c, char * name)
{
    astlog_init();
    int i = 0;
    for(i=0;i<c->nb_params;i++) {
        if(!strncasecmp(c->params[i].name, name, strlen(name)))
            return c->params[i].value;
    }
    astlog_end();
    return NULL;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
void astCategoryAddParam(Category *c, char * name, char * value)
{
    astlog_init();
    if(!astman_strlen_zero(value)) {
        strncpy(c->params[c->nb_params].name, name, MAX_NAME_LEN);
        strncpy(c->params[c->nb_params++].value, value, MAX_VALUE_LEN);
    }
    astlog_end();
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
void astCategorySetParamValue(Category *c, char * name, char *value)
{
    char *v = NULL;
    astlog_init();
    if(!(v=astCategoryGetParamValue(c,name)))
        astCategoryAddParam(c,name,value);
    else {
        strncpy(v, value, MAX_VALUE_LEN);
    }
    astlog_end();
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
void astCategorySetParamValueAt(Category *c, int index, char *value)
{
    astlog_init();
    if(index >= c->nb_params)
        return;
    strncpy(c->params[index].value, value, MAX_VALUE_LEN);
    astlog_end();
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
void astCategoryRemoveParam(Category *c, char * name)
{
    int i = -1;
    astlog_init();
    if((i=astCategoryGetParamIndex(c,name,""))<0) {
        astlog(ASTLOG_WARNING, "Parameter (%s) not existe in Category (%s)",
                    name, c->cat);
        return;
    }
    memmove(&c->params[i], &c->params[i+1], sizeof(confParam) * (c->nb_params - i - 1));
    c->nb_params--;
    astlog_end();
}
