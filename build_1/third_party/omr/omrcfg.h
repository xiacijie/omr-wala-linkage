/*******************************************************************************
 * Copyright (c) 2017, 2019 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0 OR GPL-2.0 WITH Classpath-exception-2.0 OR LicenseRef-GPL-2.0 WITH Assembly-exception
 *******************************************************************************/

/**
 * The OMR build configuration. A public header. Controls the APIs of all other headers.
 * Include at the top of every OMR source and header.
 */

#if !defined(OMRCFG_H_)
#define OMRCFG_H_

/**
 * @ddr_namespace: map_to_type=OmrBuildFlags
 * @ddr_options: valuesandbuildflags
 */

/* #undef OMR_GC */
#define OMR_COMPILER
#define OMR_JITBUILDER
/* #undef OMR_TEST_COMPILER */
#define OMR_PORT
#define OMR_THREAD
/* #undef OMR_OMRSIG */
#define OMR_EXAMPLE

#define OMR_GC_ALLOCATION_TAX
#define OMR_GC_BATCH_CLEAR_TLH
#define OMR_GC_COMBINATION_SPEC
/* #undef OMR_GC_CONCURRENT_SCAVENGER */
/* #undef OMR_GC_CONCURRENT_SWEEP */
#define OMR_GC_DEBUG_ASSERTS
/* #undef OMR_GC_EXPERIMENTAL_CONTEXT */
/* #undef OMR_GC_EXPERIMENTAL_OBJECT_SCANNER */
/* #undef OMR_GC_HEAP_CARD_TABLE */
/* #undef OMR_GC_IDLE_HEAP_MANAGER */
#define OMR_GC_LARGE_OBJECT_AREA
/* #undef OMR_GC_LEAF_BITS */
#define OMR_GC_MINIMUM_OBJECT_SIZE
/* #undef OMR_GC_MODRON_COMPACTION */
/* #undef OMR_GC_MODRON_CONCURRENT_MARK */
/* #undef OMR_GC_MODRON_SCAVENGER */
#define OMR_GC_MODRON_STANDARD
#define OMR_GC_NON_ZERO_TLH
/* #undef OMR_GC_OBJECT_ALLOCATION_NOTIFY */
/* #undef OMR_GC_SEGREGATED_HEAP */
#define OMR_GC_THREAD_LOCAL_HEAP
/* #undef OMR_GC_VLHGC */
/* #undef OMR_GC_VLHGC_CONCURRENT_COPY_FORWARD */

/**
 * Tells if a platform has support for Semaphores.
 * ifRemoved: platform cannot use semaphore operations.
 */
#define OMR_INTERP_HAS_SEMAPHORES

/**
 * Use TDF based trace engine
 * ifRemoved: No tracepoints
 */
#define OMR_RAS_TDF_TRACE

/**
 * Support options to adapt spinning as controlled by options provided to the vm.
 * Requires flag: OMR_THR_JLM_HOLD_TIMES
 * ifRemoved: No adaptive spinning supported
 */
#define OMR_THR_ADAPTIVE_SPIN

/**
 * Enable support for lock monitor to profile locking behaviour - counts only
 * ifRemoved: Lock monitor cannot be enabled
 */
#define OMR_THR_JLM

/**
 * Enable support for lock monitor to profile locking behaviour - counts + timings only
 * ifRemoved: Lock monitor cannot be enabled
 */
#define OMR_THR_JLM_HOLD_TIMES

/**
 * object header does not contain the monitor word
 * ifRemoved: object header will contain the monitor word
 */
#define OMR_THR_LOCK_NURSERY

/**
 * Output lots of thread statistics (Pentium only)
 * ifRemoved: Turn off in production VMs
 */
/* #undef OMR_THR_TRACING */

/* #undef OMRTHREAD_LIB_AIX */
#define OMRTHREAD_LIB_UNIX 1
/* #undef OMRTHREAD_LIB_WIN32 */
/* #undef OMRTHREAD_LIB_ZOS */

/**
 * This spec targets PPC processors.
 */
/* #undef OMR_ARCH_POWER */

/**
 * This spec targets ARM processors.
 */
/* #undef OMR_ARCH_ARM */

/**
 * This spec targets x86 processors.
 */
#define OMR_ARCH_X86

/**
 * This spec targets S390 processors.
 */
/* #undef OMR_ARCH_S390 */

#define OMR_ENV_DATA64
/* #undef OMR_ENV_GCC */
#define OMR_ENV_LITTLE_ENDIAN
#define OMR_GC_ARRAYLETS
/* #undef OMR_GC_COMPRESSED_POINTERS */
#define OMR_GC_HYBRID_ARRAYLETS
/* #undef OMR_GC_OBJECT_MAP */
/* #undef OMR_GC_REALTIME */
/* #undef OMR_GC_TLH_PREFETCH_FTA */
/* #undef OMR_GC_VLHGC */

/**
 * Flag to indicate that on 64-bit platforms, the monitor slot in object headers is a U32 rather than a UDATA.
 * ifRemoved: The monitor slot is a UDATA.
 */
/* #undef OMR_INTERP_SMALL_MONITOR_SLOT */

/**
 * Add support for CUDA
 */
/* #undef OMR_OPT_CUDA */

/**
 * Enabling this flag implies the platform's vmem implementation is able to allocate memory top down.
 * ifRemoved: Implies the platform's vmem implementation is not able to allocate memory top down
 */
/* #undef OMR_PORT_ALLOCATE_TOP_DOWN */

/**
 * Enables async signal handler thread in the port library.
 * ifRemoved: Async signal handler thread is disabled.
 */
/* #undef OMR_PORT_ASYNC_HANDLER */

/**
 * The platform is able to attempt to reserve virtual memory via a call to omrvmem_reserve_memory at the address specified by the user.
 * ifRemoved: The platform is not able to reserve virtual memory at a specific address
 */
#define OMR_PORT_CAN_RESERVE_SPECIFIC_ADDRESS

/**
 * This platform is able to associate memory with a specific node, as is relevant when the system has a Non Uniform Memory Access configuration.
 * ifRemoved: This platform is not able to associate memory with a specific node.
 */
/* #undef OMR_PORT_NUMA_SUPPORT */

/**
 * If set, omrsig_protect will include support for registering a handler using CEEHDLR.
 * Pass OMRPORT_SIG_OPTIONS_ZOS_USE_CEEHDLR into omrsig_set_options() before the first call
 * to omrsig_protect() to turn on the use of CEEHDLR at runtime.
 * ifRemoved: omrsig_protect will not include support for CEEHDLR.
 */
/* #undef OMR_PORT_ZOS_CEEHDLRSUPPORT */

/**
 * Enable the j9thread library to be used after a fork().
 * ifRemoved: The j9thread library may be corrupt and unusable after a fork().
 */
/* #undef OMR_THR_FORK_SUPPORT */

/**
 * Attempt to enter raw monitors using user-space spinlocks before reverting to an OS synchronization object
 * ifRemoved: All raw monitor enters will proceed directly to an OS synchronization object
 */
/* #undef OMR_THR_THREE_TIER_LOCKING */

/**
 * Enable support for custom spin options.
 * Requires flag: OMR_THR_THREE_TIER_LOCKING.
 * ifRemoved: Custom spin options cannot be used.
 */
/* #undef OMR_THR_CUSTOM_SPIN_OPTIONS */

/**
 * Allows a user to select the thread notify policy: signal or broadcast.
 * ifRemoved: User will not be able to select the thread notify policy, and broadcast policy will always be used.
 */
/* #undef OMR_NOTIFY_POLICY_CONTROL */

/**
 * This flag enables new synchronization prototypes which  
 * -- prevent large number of threads to spin at a time on a monitor 
 * -- avoid the thundering herd problem on wake up
 *
 * The prototypes provide the following features
 * -- track number of threads spinning on a monitor
 * -- wake threads only when no thread is spinning on a monitor
 * -- limit/control number of threads that are woken up per monitor
 * -- limit/control number of threads that are allowed to spin per monitor
 */
/* #undef OMR_THR_SPIN_WAKE_CONTROL */

/**
 * This enables the option to select different algorithms for yielding.
 */
/* #undef OMR_THR_YIELD_ALG */

/**
 * This flags enables calls to omrsig_primary_signal, omrsig_primary_sigaction and
 * omrsig_handler (omrsig library). If disabled, then calls to signal and sigaction
 * will be enabled, and calls to functions in omrsig library will be disabled.
 */
/* #undef OMRPORT_OMRSIG_SUPPORT */

/* Plaform config options */
/* #undef OMR_USE_POSIX_SEMAPHORES */
#define OMR_USE_OSX_SEMAPHORES
/* #undef OMR_USE_ZOS_SEMAPHORES */

#endif /* !defined(OMRCFG_H_) */