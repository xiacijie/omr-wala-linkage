/*
 *  Do not edit this file 
 *  Generated by TraceGen
 */
#ifndef UTE_J9HOOK_MODULE_HEADER
#define UTE_J9HOOK_MODULE_HEADER
#include "ute_module.h"
#ifndef UT_TRACE_OVERHEAD
#define UT_TRACE_OVERHEAD 1
#endif
#ifndef UT_THREAD
#define UT_THREAD(thr) (void *)thr
#endif /* UT_THREAD */
#ifndef UT_STR
#define UT_STR(arg) #arg
#endif
#ifdef __cplusplus
extern "C" {
#endif

#if (defined (__clang__) && !defined(_MSC_VER))
#include <unistd.h>
#define Trace_Unreachable() _exit(-1)
#else
#define Trace_Unreachable()
#endif

int32_t registerj9hookWithTrace(UtInterface * utIntf, UtModuleInfo* containerName);
int32_t deregisterj9hookWithTrace(UtInterface * utIntf);
#define UT_MODULE_LOADED(utIntf) registerj9hookWithTrace((utIntf), NULL);
#define UT_MODULE_UNLOADED(utIntf) deregisterj9hookWithTrace((utIntf));
#define UT_J9HOOK_MODULE_LOADED(utIntf) registerj9hookWithTrace((utIntf), NULL);
#define UT_J9HOOK_MODULE_UNLOADED(utIntf) deregisterj9hookWithTrace((utIntf));

#if UT_TRACE_OVERHEAD >= 1
#define Trc_Hook_Dispatch_Exceed_Threshold_Event(P1, P2) do { /* tracepoint name: j9hook.0 */ \
	if ((unsigned char) j9hook_UtActive[0] != 0){ \
		j9hook_UtModuleInfo.intf->Trace((void *)NULL, &j9hook_UtModuleInfo, ((0u << 8) | j9hook_UtActive[0]), "\377\6", P1, P2);} \
	} while(0)
#else
#define Trc_Hook_Dispatch_Exceed_Threshold_Event(P1, P2)   /* tracepoint name: j9hook.0 */
#endif

extern UtModuleInfo j9hook_UtModuleInfo;
extern unsigned char j9hook_UtActive[];

#ifndef UT_MODULE_INFO
#define UT_MODULE_INFO j9hook_UtModuleInfo
#endif /* UT_MODULE_INFO */

#ifndef UT_ACTIVE
#define UT_ACTIVE j9hook_UtActive
#endif /* UT_ACTIVE */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* UTE_J9HOOK_MODULE_HEADER */
/*
 * End of file
 */