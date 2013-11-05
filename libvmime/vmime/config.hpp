
//
// This file was automatically generated by configuration script.
//

#ifndef VMIME_CONFIG_HPP_INCLUDED
#define VMIME_CONFIG_HPP_INCLUDED


// Name of package
#define VMIME_PACKAGE "libvmime"

// Version number of package
#define VMIME_VERSION "0.9.1"
#define VMIME_API "0:0:0"

// Target OS and architecture
#define VMIME_TARGET_ARCH "x86_64"
#define VMIME_TARGET_OS "linux-gnu"

// Set to 1 if debugging should be activated
#define VMIME_DEBUG 0

// Byte order (set one or the other, but not both!)
#define VMIME_BYTE_ORDER_BIG_ENDIAN    0
#define VMIME_BYTE_ORDER_LITTLE_ENDIAN 1

// Generic types
// -- 8-bit
typedef signed char vmime_int8;
typedef unsigned char vmime_uint8;
// -- 16-bit
typedef signed short vmime_int16;
typedef unsigned short vmime_uint16;
// -- 32-bit
typedef signed int vmime_int32;
typedef unsigned int vmime_uint32;

// Options
// -- File-system support
#define VMIME_HAVE_FILESYSTEM_FEATURES 1
// -- SASL support
#define VMIME_HAVE_SASL_SUPPORT 0
// -- TLS support
#define VMIME_HAVE_TLS_SUPPORT 0
// -- Messaging support
#define VMIME_HAVE_MESSAGING_FEATURES 1
// -- Built-in messaging protocols
#define VMIME_BUILTIN_MESSAGING_PROTOS ""
#define VMIME_BUILTIN_MESSAGING_PROTO_POP3 0
#define VMIME_BUILTIN_MESSAGING_PROTO_SMTP 0
#define VMIME_BUILTIN_MESSAGING_PROTO_IMAP 0
#define VMIME_BUILTIN_MESSAGING_PROTO_MAILDIR 0
#define VMIME_BUILTIN_MESSAGING_PROTO_SENDMAIL 0
// -- Built-in platform handlers
#define VMIME_BUILTIN_PLATFORMS " posix"
#define VMIME_BUILTIN_PLATFORM_WINDOWS 0
#define VMIME_BUILTIN_PLATFORM_POSIX 1


// Miscellaneous flags
#define VMIME_SENDMAIL_PATH "/usr/sbin/sendmail"

// Additional defines
#define VMIME_HAVE_GETADDRINFO 1
#define VMIME_HAVE_PTHREAD 1

#endif // VMIME_CONFIG_HPP_INCLUDED