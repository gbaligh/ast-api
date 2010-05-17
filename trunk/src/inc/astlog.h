/* $Id: astlog.h,v 1.4 2010/05/17 09:32:43 bguesmi Exp $ */
#ifndef ASTLOG_H_INCLUDED
#define ASTLOG_H_INCLUDED
/**
 *  @file astlog.h
 *  @brief LOG Functions
 *  @author Baligh.GUESMI Emira.MHAROUECH Olivier.BENEZE
 *  @version 0.1
 *  @date 26 Avril 2010
 *
 *
 */


enum astlog_level {
    ASTLOG_INFO,
    ASTLOG_WARNING,
    ASTLOG_ERROR
};


static char *astlog_map[] = {
    "AST_API_INFO",
    "AST_API_WARNING",
    "AST_API_ERROR"
};


#define astlog(log_level,format,...) fprintf(stdout, "[%s:%d]-[%s]: "format"\n", __FUNCTION__, __LINE__, \
                                                astlog_map[log_level], ##__VA_ARGS__)


#endif /* ASTLOG_H_INCLUDED*/
