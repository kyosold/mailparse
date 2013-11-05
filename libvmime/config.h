/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.in by autoheader.  */


/* hack for BROKEN autoheader, since it will not predicitably order
   macros by any obvious means. */

#define HAVE_UNISTD_H 1
#define HAVE_FEATURES_H 1
#define HAVE_SYS_TYPES_H 1

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifndef	WIN32
#ifdef	HAVE_FEATURES_H
#include <features.h>
#endif
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
	


#define HAVE_SYS_TIME_H 1
#if TIME_WITH_SYS_TIME
#include <sys/time.h>
#include <time.h>
#else
#if HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif
#endif
	

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* aix fixes needed */
/* #undef COMMON_AIX_FIXES */

/* atomic aix operations */
/* #undef HAVE_ATOMIC_AIX */

/* Define to 1 if you have the <bits/atomicity.h> header file. */
/* #undef HAVE_BITS_ATOMICITY_H */

/* Define to 1 if you have the `clock_gettime' function. */
/* #undef HAVE_CLOCK_GETTIME */

/* Define to 1 if you have the <dirent.h> header file, and it defines `DIR'.
   */
#define HAVE_DIRENT_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <features.h> header file. */
#define HAVE_FEATURES_H 1

/* has gcc atomic functions */
/* #undef HAVE_GCC_BITS_ATOMIC */

/* has __gnu_cxx atomic functions */
/* #undef HAVE_GCC_CXX_BITS_ATOMIC */

/* have hires */
#define HAVE_HIRES_TIMER 1

/* Define if you have the iconv() function. */
#define HAVE_ICONV 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `malloc' library (-lmalloc). */
/* #undef HAVE_LIBMALLOC */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mlock' function. */
#define HAVE_MLOCK 1

/* Define to 1 if you have the `mlockall' function. */
#define HAVE_MLOCKALL 1

/* Define to 1 if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define to 1 if you have the <netdb.h> header file. */
#define HAVE_NETDB_H 1

/* has pwrite */
#define HAVE_PREAD_PWRITE 1

/* Define if you have POSIX threads libraries and header files. */
/* #undef HAVE_PTHREAD */

/* has stack size */
#define HAVE_PTHREAD_ATTR_SETSTACKSIZE 1

/* has cancel */
#define HAVE_PTHREAD_CANCEL 1

/* has non portable delay */
/* #undef HAVE_PTHREAD_DELAY_NP */

/* posix thread header */
#define HAVE_PTHREAD_H 1

/* has mach link */
/* #undef HAVE_PTHREAD_MACH_THREAD_NP */

/* has non portable setkind */
/* #undef HAVE_PTHREAD_MUTEXATTR_SETKIND_NP */

/* has setttype */
#define HAVE_PTHREAD_MUTEXATTR_SETTYPE 1

/* has non portable settype */
/* #undef HAVE_PTHREAD_MUTEXATTR_SETTYPE_NP */

/* has nanosleep */
#define HAVE_PTHREAD_NANOSLEEP 1

/* Define to 1 if you have the <pthread_np.h> header file. */
/* #undef HAVE_PTHREAD_NP_H */

/* has rwlock support */
#define HAVE_PTHREAD_RWLOCK 1

/* has sched yield */
/* #undef HAVE_PTHREAD_SCHED_YIELD */

/* has setcancel */
/* #undef HAVE_PTHREAD_SETCANCEL */

/* has setcanceltype */
#define HAVE_PTHREAD_SETCANCELTYPE 1

/* has suspend */
/* #undef HAVE_PTHREAD_SUSPEND */

/* has yield */
#define HAVE_PTHREAD_YIELD 1

/* has np yield */
/* #undef HAVE_PTHREAD_YIELD_NP */

/* Define to 1 if you have the `sched_getscheduler' function. */
#define HAVE_SCHED_GETSCHEDULER 1

/* Define to 1 if you have the <sched.h> header file. */
#define HAVE_SCHED_H 1

/* Define to 1 if you have the <semaphore.h> header file. */
#define HAVE_SEMAPHORE_H 1

/* Define to 1 if stdbool.h conforms to C99. */
#define HAVE_STDBOOL_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/atomic.h> header file. */
/* #undef HAVE_SYS_ATOMIC_H */

/* Define to 1 if you have the <sys/atomic_op.h> header file. */
/* #undef HAVE_SYS_ATOMIC_OP_H */

/* Define to 1 if you have the <sys/dir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_DIR_H */

/* Define to 1 if you have the <sys/ndir.h> header file, and it defines `DIR'.
   */
/* #undef HAVE_SYS_NDIR_H */

/* Define to 1 if you have the <sys/sched.h> header file. */
/* #undef HAVE_SYS_SCHED_H */

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <thread.h> header file. */
/* #undef HAVE_THREAD_H */

/* have unix header */
#define HAVE_UNISTD_H 1

/* has usable atomic functions */
/* #undef HAVE_WORKING_SYS_ATOMIC_H */

/* Define to 1 if the system has the type `_Bool'. */
#define HAVE__BOOL 1

/* Define as const if the declaration of iconv() needs const. */
#define ICONV_CONST 

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Name of package */
#define PACKAGE "vmime"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "vincent@vincent-richard.net"

/* Define to the full name of this package. */
#define PACKAGE_NAME "VMime Library"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "VMime Library 0.9.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "vmime"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.9.1"

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* mutex type */
#define PTHREAD_MUTEXTYPE_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP

/* The size of `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 8

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* Version number of package */
#define VERSION "0.9.1"

/* bsd system using linuxthreads */
/* #undef WITH_LINUXTHREADS */

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif


#ifdef HAVE_THREAD_H
#include "@thrprefix@/thread.h"
#if defined(i386) && defined(__svr4__) && !defined(__sun)
#define _THR_UNIXWARE
#endif
#if defined(__SVR4) && defined(__sun)
#define _THR_SUNOS5
#else
#if defined(__SVR4__) && defined(__SUN__)
#define _THR_SUNOS5
#endif
#endif
#endif

#ifdef HAVE_WORKING_SYS_ATOMIC_H
#include <sys/atomic.h>
#define HAVE_ATOMIC
#elif defined(HAVE_ATOMIC_AIX)
#include <sys/atomic_op.h>
#ifndef	HAVE_ATOMIC
#define	HAVE_ATOMIC
#endif
#endif

#if defined(__cplusplus)
#if defined(HAVE_GCC_BITS_ATOMIC) || defined(HAVE_GCC_CXX_BITS_ATOMIC)
#include <bits/atomicity.h>
#define HAVE_ATOMIC
#endif
#endif

#if defined(HAVE_PTHREAD_H) && ( defined(_THREAD_SAFE) || defined(_REENTRANT) )

#ifdef	__QNX__
#define	__EXT_QNX
#endif

#include <pthread.h>

#ifdef HAVE_PTHREAD_NP_H
#include <pthread_np.h>
#endif

#ifdef HAVE_SEMAPHORE_H
#include <semaphore.h>
#endif
#ifdef _POSIX_PRIORITY_SCHEDULING
#ifdef HAVE_SCHED_H
#include <sched.h>
#else
#ifdef HAVE_SYS_SCHED_H
#include <sys/sched.h>
#endif
#endif
#endif

#define __PTHREAD_H__
#ifndef PTHREAD_MUTEXTYPE_RECURSIVE
#ifdef  MUTEX_TYPE_COUNTING_FAST
#define PTHREAD_MUTEXTYPE_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP
#endif
#endif
#ifndef PTHREAD_MUTEXTYPE_RECURSIVE
#ifdef  PTHREAD_MUTEX_RECURSIVE
#define PTHREAD_MUTEXTYPE_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP
#endif
#endif
#ifndef HAVE_PTHREAD_MUTEXATTR_SETTYPE
#if     HAVE_PTHREAD_MUTEXATTR_SETKIND_NP
#ifndef PTHREAD_MUTEXTYPE_RECURSIVE
#define PTHREAD_MUTEXTYPE_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP
#endif
#define pthread_mutexattr_gettype(x, y) pthread_mutexattr_getkind_np(x, y)
#define pthread_mutexattr_settype(x, y) pthread_mutexattr_setkind_np(x, y)
#endif
#if     HAVE_PTHREAD_MUTEXATTR_SETTYPE_NP
#ifndef PTHREAD_MUTEXTYPE_RECURSIVE
#define PTHREAD_MUTEXTYPE_RECURSIVE PTHREAD_MUTEX_RECURSIVE_NP
#endif
#define pthread_mutexattr_settype(x, y) pthread_mutexattr_settype_np(x, y)
#define pthread_mutexattr_gettype(x, y) pthread_mutexattr_gettype_np(x, y)
#endif
#endif

#ifdef	HAVE_PTHREAD_MACH_THREAD_NP
#define	_THR_MACH
#endif

#ifndef HAVE_PTHREAD_YIELD
#ifdef	HAVE_PTHREAD_YIELD_NP
#define	pthread_yield() pthread_yield_np()
#define HAVE_PTHREAD_YIELD 1
#endif
#endif

#ifndef HAVE_PTHREAD_YIELD
#ifdef HAVE_PTHREAD_SCHED_YIELD
#define pthread_yield() sched_yield()
#define HAVE_PTHREAD_YIELD 1
#endif
#endif

#ifndef HAVE_PTHREAD_DELAY
#ifdef HAVE_PTHREAD_DELAY_NP
#define HAVE_PTHREAD_DELAY
#define pthread_delay(x) pthread_delay_np(x)
#endif
#if defined(HAVE_PTHREAD_NANOSLEEP)
#ifndef HAVE_PTHREAD_DELAY
#define HAVE_PTHREAD_DELAY
#ifdef __FreeBSD__
#ifdef __cplusplus
extern "C" int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);
#endif
#endif
#define pthread_delay(x) nanosleep(x, NULL)
#endif
#endif
#endif

#ifdef HAVE_PTHREAD_ATTR_SETSTACK
#ifndef PTHREAD_STACK_MIN
#define PTHREAD_STACK_MIN 32768
#endif
#endif

#ifndef HAVE_PTHREAD_CANCEL
#ifdef SIGCANCEL
#define CCXX_SIG_THREAD_CANCEL SIGCANCEL
#else
#define CCXX_SIG_THREAD_CANCEL SIGQUIT
#endif
#define pthread_cancel(x) pthread_kill(x, CCXX_SIG_THREAD_CANCEL)
#define	pthread_setcanceltype(x, y)
#define	pthread_setcancelstate(x, y)
#endif

#ifndef HAVE_PTHREAD_SETCANCELTYPE
#ifdef HAVE_PTHREAD_SETCANCEL
enum
{ PTHREAD_CANCEL_ASYNCHRONOUS = CANCEL_ON,
  PTHREAD_CANCEL_DEFERRED = CANCEL_OFF};
enum
{ PTHREAD_CANCEL_ENABLE = CANCEL_ON,
  PTHREAD_CANCEL_DISABLE = CANCEL_OFF};
#define pthread_setcancelstate(x, y) \
        (y == NULL) ? pthread_setcancel(x) : *y = pthread_setcancel
#define pthread_setcanceltype(x, y) \
        (y == NULL) ? pthread_setasynccancel(x) | *y = pthread_setasynccancel(x)
#else
#define pthread_setcanceltype(x, y)
#define pthread_setcancelstate(x, y)
#endif
#endif

#ifdef  _AIX
#ifdef  HAVE_PTHREAD_SUSPEND
/* #undef HAVE_PTHREAD_SUSPEND */
#endif
#endif

#endif


	
