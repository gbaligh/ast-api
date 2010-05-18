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

#ifdef AST_DEBUG
static char *astlog_map[] = {
    "AST_API_INFO",
    "AST_API_WARNING",
    "AST_API_ERROR"
};

#define astlog(log_level,format,...) fprintf(stdout, "[%s]-[%s:%d]: "format"\n", astlog_map[log_level], __FUNCTION__, __LINE__, \
                                                 ##__VA_ARGS__)
#else
#define astlog(log_level,format,...)
#endif


#endif /* ASTLOG_H_INCLUDED*/
