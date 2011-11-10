#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

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
 *  @file category.h
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100521
 ******************************************************************************/
#include "astapi.h"
/*******************************************************************************
 *  @struct    MAX_EVENTS
 *  @brief
 ******************************************************************************/
 typedef struct {
    int line;
    char name[MAX_NAME_LEN];
    char value[MAX_VALUE_LEN];
} __attribute__((packed)) confParam;

/*******************************************************************************
 *  @struct    MAX_EVENTS
 *  @brief
 ******************************************************************************/
typedef struct category_s {
    char cat[MAX_NAME_LEN];
    int nb_params;
    confParam params[MAX_HEADERS];
} __attribute__((packed)) Category;

/******************************************************************************
 * @fn astCategoryGet
 * @brief Get an Asterisk Category
 * @param IN strCategory: String caontains the name of the Category (e.: general)
 * @param OUT c_out: Category struct that will caontains the paring result
 * @return ASTMAN_SUCCES - ASTMAN_FAILURE
 *****************************************************************************/
int astCategoryGet(char *filename, char *strCategory, Category *c);

/******************************************************************************
 * @fn astCategorySave
 * @brief Save Category, or create if it does not existe
 * @param IN c_in: Category to be saved into Asterisk's configuration file
 *****************************************************************************/
int astCategorySave(char *filename, Category *c_in);

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
void astCategoryAddParam(Category *c, char * name, char * value);

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
char* astCategoryGetParamValue(Category *c, char * name);

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
void astCategorySetParamValueAt(Category *c, int index, char *value);

/******************************************************************************
 * @brief Main Function of the Phone Provisioning Module
 *****************************************************************************/
int astCategoryGetParamIndex(Category *c, char * name, char *subs);
#endif // CATEGORY_H_INCLUDED
