
#pragma once

// Support external config file override
#if defined(EXTERNAL_CONFIG_FILEPATH)
#include EXTERNAL_CONFIG_FILEPATH
#elif defined(EXTERNAL_CONFIG_FILEPATH_NO_STRING)
// When invoking clanng from FastBuild the EXTERNAL_CONFIG_FILEPATH define doesn't get expanded to a string,
// quotes are removed, that's why we add this variation of the macro that turns the define back into a valid string
#define FV_EXTERNAL_CONFIG_STRINGIFY2(x) #x
#define FV_EXTERNAL_CONFIG_STRINGIFY(x) FV_EXTERNAL_CONFIG_STRINGIFY2(x)

#include FV_EXTERNAL_CONFIG_STRINGIFY(EXTERNAL_CONFIG_FILEPATH_NO_STRING)

#undef FV_EXTERNAL_CONFIG_STRINGIFY
#undef FV_EXTERNAL_CONFIG_STRINGIFY2
#else

#include <cstdint>
#include <cstdlib>

//////////////////////////////////////////////
//// Compiler setup
//////////////////////////////////////////////
#if INTPTR_MAX == 0x7FFFFFFFFFFFFFFFLL
#define PTR_SIZE 8
#elif INTPTR_MAX == 0x7FFFFFFF
#define PTR_SIZE 4
#else
#error unsupported platform
#endif

#ifdef __cplusplus
#define FIREVOX_CONSTEXPR constexpr
#define FIREVOX_EXTERN_C extern "C"
#else
#define FIREVOX_CONSTEXPR
#define FIREVOX_EXTERN_C
#endif

#if !defined(QUOTE)
#define _QUOTE(x) #x
#define QUOTE(x) _QUOTE(x)
#endif

#define FV_ARRAY_COUNT(array) \
    (sizeof(array) / (sizeof(array[0]) * (sizeof(array) != PTR_SIZE || sizeof(array[0]) <= PTR_SIZE)))

#ifndef FV_MIN
#define FV_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef FV_MAX
#define FV_MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#if !defined(_DEBUG) && !defined(NDEBUG)
#define NDEBUG
#endif

#define UNREF_PARAM(x) ((void) (x))
#define ALIGNAS(x) __declspec(align(x))
#define DEFINE_ALIGNED(def, a) __declspec(align(a)) def
#define FIREVOX_CALLCONV __cdecl
#define ALIGNOF(x) __alignof(x)
#define THREAD_LOCAL __declspec(thread)

#include <crtdbg.h>
#define COMPILE_ASSERT(exp) _STATIC_ASSERT(exp)

#include <BaseTsd.h>
typedef SSIZE_T ssize_t;

#if defined(_M_X64)
#define ARCH_X64
#define ARCH_X86_FAMILY
#elif defined(_M_IX86)
#define ARCH_X86
#define ARCH_X86_FAMILY
#else
#error "Unsupported architecture for msvc compiler"
#endif

// Msvc removes trailing commas
#define OPT_COMMA_VA_ARGS(...) , __VA_ARGS__

#elif defined(__GNUC__) || defined(__clang__)
#include <cassert>
#include <sys/types.h>

#ifdef __OPTIMIZE__
// Some platforms define NDEBUG for Release builds
#if !defined(NDEBUG) && !defined(_DEBUG)
#define NDEBUG
#endif
#else
#if !defined(_DEBUG) && !defined(NDEBUG)
#define _DEBUG
#endif
#endif

#ifdef __APPLE__
#define NOREFS __unsafe_unretained
#endif

#define UNREF_PARAM(x) ((void) (x))
#define ALIGNAS(x) __attribute__((aligned(x)))
#define DEFINE_ALIGNED(def, a) __attribute__((aligned(a))) def
#define FIREVOX_CALLCONV
#define ALIGNOF(x) __alignof__(x)
#define THREAD_LOCAL __thread

#if defined(__clang__) && !defined(__cplusplus)
#define COMPILE_ASSERT(exp) _Static_assert(exp, #exp)
#else
#define COMPILE_ASSERT(exp) static_assert(exp, #exp)
#endif

#if defined(__i386__)
#define ARCH_X86
#define ARCH_X86_FAMILY
#elif defined(__x86_64__)
#define ARCH_X64
#define ARCH_X86_FAMILY
#elif defined(__arm__)
#define ARCH_ARM
#define ARCH_ARM_FAMILY
#elif defined(__aarch64__)
#define ARCH_ARM64
#define ARCH_ARM_FAMILY
#else
#error "Unsupported architecture for gcc compiler"
#endif

#if defined(_WIN32)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#define OPT_COMMA_VA_ARGS(...) , ##__VA_ARGS__

#else
#error Unknown language dialect
#endif

#ifndef SSIZE_MAX
#if PTR_SIZE == 4
#define SSIZE_MAX INT32_MAX
COMPILE_ASSERT(sizeof(ssize_t) == sizeof(int32_t));
#elif PTR_SIZE == 8
#define SSIZE_MAX INT64_MAX
COMPILE_ASSERT(sizeof(ssize_t) == sizeof(int64_t));
#endif
#endif  // !SSIZE_MAX

#if defined(_MSC_VER)
#define FIREVOX_EXPORT __declspec(dllexport)
#define FIREVOX_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)  // clang & gcc
#define FIREVOX_EXPORT __attribute__((visibility("default")))
#define FIREVOX_IMPORT
#endif

//////////////////////////////////////////////
//// Platform setup
//////////////////////////////////////////////
#if defined(_WIN32)
// XBOX?
#if !defined(_WINDOWS)
#define _WINDOWS
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef _WINDOWS
// Restrict compilation to Windows 7 APIs
#define NTDDI_VERSION NTDDI_WIN7
#define WINVER _WIN32_WINNT_WIN7
#define _WIN32_WINNT _WIN32_WINNT_WIN7

// Whitelist of compiler versions
#if (_MSC_VER == 1929)  // VS 2019 all VC++ compilers
#else
#pragma message("Bad Visual Studio version: (" QUOTE(_MSC_VER) " " QUOTE(_MSC_FULL_VER) " " QUOTE(_MSC_BUILD) ").")
#error "Bad Visual Studio version"
#endif
#endif

#elif defined(__APPLE__)
#include <TargetConditionals.h>

#if defined(ARCH_ARM64)
#define TARGET_APPLE_ARM64
#endif


#ifndef MIN_MALLOC_ALIGNMENT
#if defined(__APPLE__)
#define MIN_MALLOC_ALIGNMENT 16
#elif PTR_SIZE == 4
#define MIN_MALLOC_ALIGNMENT 8
#elif PTR_SIZE == 8
#define MIN_MALLOC_ALIGNMENT 16
#endif
#endif
#endif

//////////////////////////////////////////////
//// General options
//////////////////////////////////////////////

// Uncomment this to enable empty mounts
// used for absolute paths
// #define ENABLE_FV_EMPTY_MOUNT

#ifdef ENABLE_PROFILER
// Enable this if you want to have the profiler through a web browser, see PROFILE_WEBSERVER_PORT for server location
// #define ENABLE_PROFILER_WEBSERVER
#endif

// Enable output of a .MTuner file for the memory profiler https://github.com/RudjiGames/MTuner/releases
// #define ENABLE_MTUNER

// For allocating space in uniform block. Must match with shader and application.
// 804 aligns as multiple of the 67 bones used in the animation test closest to having a 64k uniform buffer
#ifndef MAX_SKELETON_BATCHER_BLOCK_INSTANCES
#define MAX_SKELETON_BATCHER_BLOCK_INSTANCES 804
#endif

#define VISIBILITY_BUFFER_MAX_GEOMETRY_SETS 3
// Number of bits required to represent all geometry set values
#define VISIBILITY_BUFFER_GEOMETRY_SET_BITS 2
#define VISIBILITY_BUFFER_MAX_NUM_BUFFERS 2

#if defined(AUTOMATED_TESTING)
// Used for automated testing, the app will exit after 240 frames
#define DEFAULT_AUTOMATION_FRAME_COUNT 240
// Used for automated testing, emulates 60fps to ensure screenshots always look the same
#define AUTOMATION_FIXED_FRAME_TIME 0.0167f
#endif

//////////////////////////////////////////////
//// Build related options
//////////////////////////////////////////////
#define FIREVOX_API


#ifndef FIREVOX_DEBUG
#if defined(DEBUG) || defined(_DEBUG) || defined(AUTOMATED_TESTING)
#define FIREVOX_DEBUG
#endif
#endif

#define ENABLE_LOGGING
#define DEFAULT_LOG_LEVEL eALL
#if !defined(NDEBUG)
#define ENABLE_MEMORY_TRACKING
#endif
// #define ENABLE_FIREVOX_STACKTRACE_DUMP

#ifdef AUTOMATED_TESTING
#if defined(NX64) || (defined(_WINDOWS) && defined(_M_X64)) || defined(ORBIS)
#define ENABLE_FIREVOX_STACKTRACE_DUMP
#endif
#endif

//////////////////////////////////////////////
//// External libraries options
//////////////////////////////////////////////
// Allows conversion of non-owning bstrings to owning bstrings
#define BSTR_ENABLE_STATIC_TO_DYNAMIC_CONVERSION

//////////////////////////////////////////////
//// Config validation
//////////////////////////////////////////////
#if !defined(ENABLE_LOGGING) && !defined(DEFAULT_LOG_LEVEL)
#define DEFAULT_LOG_LEVEL eNONE
#endif

#if defined(_DEBUG) && defined(NDEBUG)
#error "_DEBUG and NDEBUG are defined at the same time"
#endif
#endif

//////////////////////////////////////////////
//// ImGui Remote Control
//////////////////////////////////////////////
#if defined(FIREVOX_DEBUG)
#if defined(ANDROID) || defined(_WIN32) || defined(PROSPERO) || defined(XBOX) || defined(__APPLE__) || defined(ORBIS)
#define ENABLE_FIREVOX_REMOTE_UI
#endif
#endif
