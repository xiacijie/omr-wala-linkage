/* File generated by tracegen, do not edit */
#include "ut_j9hook.h"



#define UT_TRACE_VERSION 8
UtTraceVersionInfo j9hook_UtTraceVersionInfo = {UT_TRACE_VERSION};
#if defined(UT_TRACE_ENABLED_IN_BUILD)
unsigned char j9hook_UtActive[1] = { 
	0};

unsigned char j9hook_UtLevels[1] = { 
	1};



UtGroupDetails j9hook_group4 = {
	(char *)"Debug",
	0,
	NULL,
	NULL};

UtGroupDetails j9hook_group3 = {
	(char *)"Exception",
	0,
	NULL,
	&j9hook_group4};
int32_t j9hook_tpids2[] = {

	0	};

UtGroupDetails j9hook_group2 = {
	(char *)"Event",
	1,
	j9hook_tpids2,
	&j9hook_group3};

UtGroupDetails j9hook_group1 = {
	(char *)"Exit",
	0,
	NULL,
	&j9hook_group2};

UtGroupDetails j9hook_group0 = {
	(char *)"Entry",
	0,
	NULL,
	&j9hook_group1};
UtModuleInfo j9hook_UtModuleInfo = {(char*) "j9hook", 6, 1, 0, j9hook_UtActive , NULL, NULL, &j9hook_UtTraceVersionInfo, (char*) "J9TraceFormat.dat", j9hook_UtLevels, &j9hook_group0, NULL, NULL, 0, 0};

#else
unsigned char j9hook_UtActive[1];
UtModuleInfo j9hook_UtModuleInfo = {(char*) "j9hook", 6, 0, 0, NULL, NULL, NULL, &j9hook_UtTraceVersionInfo, (char*) "J9TraceFormat.dat", NULL, NULL, NULL, NULL, 0, 0};

#endif /* defined(UT_TRACE_ENABLED_IN_BUILD) */
/* function to register with trace engine and configure current module */
int32_t
registerj9hookWithTrace(UtInterface *utIntf, UtModuleInfo * containerModule)
{
	I_32 rc = 0;

#if defined(UT_TRACE_ENABLED_IN_BUILD)

	j9hook_UtModuleInfo.containerModule = containerModule;

	if( utIntf == NULL ) {
		rc = -1;
	}

	if (rc == 0) {
		utIntf->module->TraceInit(NULL, &j9hook_UtModuleInfo);
	}

#else
	/* trace not present in build - NOOP */
#endif /* defined(UT_TRACE_ENABLED_IN_BUILD) */
	return rc;
}

/* function to deregister with trace engine and configure current module */
int32_t
deregisterj9hookWithTrace(UtInterface *utIntf)
{
	I_32 rc = 0;

#if defined(UT_TRACE_ENABLED_IN_BUILD)
	if( utIntf == NULL ) {
		rc = -1;
	}

	if (rc == 0) {
		utIntf->module->TraceTerm(NULL, &j9hook_UtModuleInfo);
	}
#else
	/* trace not present in build - NOOP */
#endif /* defined(UT_TRACE_ENABLED_IN_BUILD) */
	return rc;
}
/* End of generated file */
