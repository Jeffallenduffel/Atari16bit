/**************************************************************************
 * RSCGSTR.C - Get pointers to object strings from within a tree.
 *************************************************************************/

#include <stdarg.h>
#include "gemfast.h"

void rsc_gstrings(thetree)
    OBJECT          *thetree;
{
    register OBJECT *ptree;
    register char  **ppobjstr;
    register char  **ppretstr;
    register int     thisobj;
    va_list          args;

    va_start(args, thetree);
    ptree = thetree;
    
    for (;;) {
        thisobj = va_arg(args, int);
        if (thisobj < 0)
            break;
        ppobjstr  = obj_ppstring(&ptree[thisobj]);
        ppretstr  = va_arg(args, char **);
        *ppretstr = *ppobjstr;
    }

    va_end(args);
}
