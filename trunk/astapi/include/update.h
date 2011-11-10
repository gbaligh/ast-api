#ifndef UPDATE_H_INCLUDED
#define UPDATE_H_INCLUDED

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
 *  @file update.h
 *  @brief
 *  @author Baligh.GUESMI
 *  @date 20100524
 ******************************************************************************/
/** NewCat,RenameCat,DelCat,EmptyCat,Update,Delete,Append,Insert */
#define UPDATE_ACTION_NEW_CAT       "NewCat"
#define UPDATE_ACTION_RENAME_CAT    "RenameCat"
#define UPDATE_ACTION_DEL_CAT       "DelCat"
#define UPDATE_ACTION_EMPTY_CAT     "EmptyCat"
#define UPDATE_ACTION_UPDATE        "Update"
#define UPDATE_ACTION_DELETE        "Delete"
#define UPDATE_ACTION_APPEND        "Append"
#define UPDATE_ACTION_INSERT        "Insert"

int astman_update_config_init(char *src_filename,
                              char *dst_filename,
                              int reload);
int astman_update_config_add_action(char *action,
                                    char *cat,
                                    char *var, char *val,
                                    char *match,
                                    char *line);

int astman_update_config_execute(struct mansession *s, struct message *m);

#endif // UPDATE_H_INCLUDED
