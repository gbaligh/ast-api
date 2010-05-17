/* $Id: astconf.h,v 1.2 2010/05/10 10:37:56 bguesmi Exp $ */
#ifndef _ASTCONF_H
#define _ASTCONF_H

#include "common.h"

typedef struct ast_conf_s {
    char directories[AST_CONF_DIR_MAX_NUMBER][AST_API_MAX_STR_LENGTH];
} ast_conf_t;

enum ast_dir_e {
    AST_ETC_DIR,
    AST_MOD_DIR,
    AST_VAR_LIB_DIR,
    AST_DB_DIR,
    AST_KEY_DIR,
    AST_DATA_DIR,
    AST_AGI_DIR,
    AST_SPOOL_DIR,
    AST_RUN_DIR,
    AST_LOG_DIR
};

struct ast_dir_s {
    int id;
    char str[255];
} ast_dir_map[] = {
    {AST_ETC_DIR, "astetcdir"},
    {AST_MOD_DIR, "astmoddir"},
    {AST_VAR_LIB_DIR, "astvarlibdir"},
    {AST_DB_DIR, "astdbdir"},
    {AST_KEY_DIR, "astkeydir"},
    {AST_DATA_DIR, "astdatadir"},
    {AST_AGI_DIR, "astagidir"},
    {AST_SPOOL_DIR, "astspooldir"},
    {AST_RUN_DIR, "astrundir"},
    {AST_LOG_DIR, "astlogdir"}
};

int ast_asterisk_conf(mansession_t *s, ast_conf_t *conf);


#endif
