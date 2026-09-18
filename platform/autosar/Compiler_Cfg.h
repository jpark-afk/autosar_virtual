#ifndef COMPILER_H
#define COMPILER_H

#include <autosar/Compiler_Cfg.h>

/* AUTOSAR compiler abstraction for Trampoline/POSIX */

#ifndef FUNC
#define FUNC(rettype, memclass) rettype memclass
#endif

#ifndef CONST
#define CONST(consttype, memclass) consttype const
#endif

#ifndef VAR
#define VAR(vartype, memclass) vartype
#endif

#ifndef P2VAR
#define P2VAR(ptrtype, memclass, ptrclass) ptrtype *
#endif

#ifndef P2CONST
#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype *
#endif

#ifndef CONSTP2VAR
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const
#endif

#ifndef CONSTP2CONST
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype * const
#endif

#ifndef P2FUNC
#define P2FUNC(rettype, ptrclass, fctname) rettype (*fctname)
#endif

#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif

#define SOAD_CODE
#define SOAD_APPL_DATA

#endif
