/* $Id: sipconf.c,v 1.6 2010/05/17 09:32:43 bguesmi Exp $ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "action.h"
#include "astman.h"
#include "sipconf.h"

extern astContext ast_api;
#define OBJECT_NAME         "Category"
#define FILENAME            "sip.conf"
#define MODULE_FILE         "chan_sip.so"
#define CATEGORY_GENERAL    "general"

/******************************************************************************
 * @fn astCategoryGet
 * @brief Get an Asterisk Category
 * @param IN strCategory: String caontains the name of the Category (e.: general)
 * @param OUT c_out: Category struct that will caontains the paring result
 * @return ASTMAN_SUCCES - ASTMAN_FAILURE
 *****************************************************************************/
int astCategoryGet(char *strCategory, Category *c)
{
    int rv = ASTMAN_FAILURE;
    int i = 0;
    int j =0;
    int found = 0;
    int cat_num = 0;
    char cat_name[MAX_VALUE_LEN];
    char v[MAX_LEN];
    if(!astGetConfig(FILENAME)) {
        astlog(ASTLOG_ERROR, "Error reding Conf File %s", FILENAME);
        return ASTMAN_FAILURE;
    }
    for(i=0; i<ast_api.m.hdrcount; i++)
    {
        if(strncasecmp("Category", ast_api.m.headers[i], 8)==0) {
            sscanf(ast_api.m.headers[i], "Category-%6d: %s", &cat_num, cat_name);
            if(strncasecmp(cat_name, strCategory, strlen(strCategory))==0) {
                found = 1;
                rv = ASTMAN_SUCCESS;
                c->line = cat_num;
                strncpy(c->cat, cat_name, strlen(cat_name)+1);
            }
            else
                found = 0;
        }
        if((found) && (strncasecmp("Line", ast_api.m.headers[i], 4)==0)) {
            sscanf(ast_api.m.headers[i], "Line-%6d-%6d: %s", &cat_num, &(c->params[j].line), v);
            strncpy(c->params[j].value, strstr(v, "=")+1, MAX_VALUE_LEN);
            *(strstr(v, "=")) = '\0';
            strncpy(c->params[j].name, v, MAX_NAME_LEN);
            j++;
        }
    }
    c->nb_params = j;
    return rv;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astSipConfGetGeneral(Category *c_out)
{
    return astCategoryGet(CATEGORY_GENERAL, c_out);
}
/******************************************************************************
 * @fn astCategorySave
 * @brief Save Category, or create if it does not existe
 * @param IN c_in: Category to be saved into Asterisk's configuration file
 *****************************************************************************/
int astCategorySave(Category *c_in)
{
    int rv = ASTMAN_FAILURE;
    int i = 0;
    if(!(rv = astUpdateConfig(FILENAME, 0, c_in->cat, "", "", "DelCat"))) {
        astlog(ASTLOG_WARNING, "Category %s not found", c_in->cat);
    }
    if(!(rv = astUpdateConfig(FILENAME, 0, c_in->cat, "", "", "NewCat"))) {
        astlog(ASTLOG_ERROR, "Error in creating new Category %s", c_in->cat);
        return rv;
    }
    for(i=0; i<c_in->nb_params; i++) {
        rv = astUpdateConfig(FILENAME, 0, c_in->cat, c_in->params[i].name, c_in->params[i].value, "Append");
    }
    return rv;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astCategoryCreate(Category *c_in)
{
    if(!(astUpdateConfig(FILENAME, 0, c_in->cat, "", "", "NewCat"))) {
        astlog(ASTLOG_ERROR, "Error in creating new Category %s", c_in->cat);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astCategoryDel(Category *c_in)
{
    if(!(astUpdateConfig(FILENAME, 0, c_in->cat, "", "", "DelCat"))) {
        astlog(ASTLOG_ERROR, "Error in Deleting Category %s", c_in->cat);
        return ASTMAN_FAILURE;
    }
    return ASTMAN_SUCCESS;
}
/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
void astCategoryAddParam(Category *c, const char * const name, const char * const value)
{
    if(!astman_strlen_zero(value)) {
        strncpy(c->params[c->nb_params].name, name, MAX_NAME_LEN);
        strncpy(c->params[c->nb_params++].value, value, MAX_VALUE_LEN);
    }
}
