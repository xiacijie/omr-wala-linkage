/* File generated by tracegen, do not edit */
#include "ut_omrvm.h"



#define UT_TRACE_VERSION 8
UtTraceVersionInfo omrvm_UtTraceVersionInfo = {UT_TRACE_VERSION};
#if defined(UT_TRACE_ENABLED_IN_BUILD)
unsigned char omrvm_UtActive[2] = { 
	0,1};

unsigned char omrvm_UtLevels[2] = { 
	3,1};


int32_t omrvm_tpids5[] = {

	1	};

UtGroupDetails omrvm_group5 = {
	(char *)"Assertion",
	1,
	omrvm_tpids5,
	NULL};

UtGroupDetails omrvm_group4 = {
	(char *)"Debug",
	0,
	NULL,
	&omrvm_group5};

UtGroupDetails omrvm_group3 = {
	(char *)"Exception",
	0,
	NULL,
	&omrvm_group4};
int32_t omrvm_tpids2[] = {

	0	};

UtGroupDetails omrvm_group2 = {
	(char *)"Event",
	1,
	omrvm_tpids2,
	&omrvm_group3};

UtGroupDetails omrvm_group1 = {
	(char *)"Exit",
	0,
	NULL,
	&omrvm_group2};

UtGroupDetails omrvm_group0 = {
	(char *)"Entry",
	0,
	NULL,
	&omrvm_group1};
UtModuleInfo omrvm_UtModuleInfo = {(char*) "omrvm", 5, 2, 0, omrvm_UtActive , NULL, NULL, &omrvm_UtTraceVersionInfo, (char*) "OMRTraceFormat.dat", omrvm_UtLevels, &omrvm_group0, NULL, NULL, 0, 0};

#else
unsigned char omrvm_UtActive[1];
UtModuleInfo omrvm_UtModuleInfo = {(char*) "omrvm", 5, 0, 0, NULL, NULL, NULL, &omrvm_UtTraceVersionInfo, (char*) "OMRTraceFormat.dat", NULL, NULL, NULL, NULL, 0, 0};

#endif /* defined(UT_TRACE_ENABLED_IN_BUILD) */
/* function to register with trace engine and configure current module */
int32_t
registeromrvmWithTrace(UtInterface *utIntf, UtModuleInfo * containerModule)
{
	I_32 rc = 0;

#if defined(UT_TRACE_ENABLED_IN_BUILD)

	omrvm_UtModuleInfo.containerModule = containerModule;

	if( utIntf == NULL ) {
		rc = -1;
	}

	if (rc == 0) {
		utIntf->module->TraceInit(NULL, &omrvm_UtModuleInfo);
	}

#else
	/* trace not present in build - NOOP */
#endif /* defined(UT_TRACE_ENABLED_IN_BUILD) */
	return rc;
}

/* function to deregister with trace engine and configure current module */
int32_t
deregisteromrvmWithTrace(UtInterface *utIntf)
{
	I_32 rc = 0;

#if defined(UT_TRACE_ENABLED_IN_BUILD)
	if( utIntf == NULL ) {
		rc = -1;
	}

	if (rc == 0) {
		utIntf->module->TraceTerm(NULL, &omrvm_UtModuleInfo);
	}
#else
	/* trace not present in build - NOOP */
#endif /* defined(UT_TRACE_ENABLED_IN_BUILD) */
	return rc;
}
/* End of generated file */
