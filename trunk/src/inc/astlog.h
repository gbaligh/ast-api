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


/*static struct astlog_s {
    enum astlog_level id;
    char *str;
} astlog_map[] = {
    {ASTLOG_INFO, "[AST_LIB_INFO]"},
    {ASTLOG_WARNING, "[AST_LIB_WARNING]"},
    {ASTLOG_ERROR, "[AST_LIB_ERROR]"}
};*/


#define astlog(log_level,format,...) fprintf(stdout, "%d: "format"\n", log_level, ##__VA_ARGS__)


#endif // ASTLOG_H_INCLUDED
