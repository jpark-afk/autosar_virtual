/*
 * Compatibility wrapper for RTI UDPInterface.c.
 *
 * Trampoline defines YES as a preprocessor macro while UDPInterface.c
 * uses YES as a local variable name.
 */
#include <Os.h>

#ifdef YES
#undef YES
#endif

#include "netiopsl/udp/UDPInterface.c"
