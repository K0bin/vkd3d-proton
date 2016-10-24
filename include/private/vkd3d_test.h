/*
 * Copyright 2016 Józef Kucia for CodeWeavers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __VKD3D_TEST_H
#define __VKD3D_TEST_H

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vkd3d_common.h"

static void vkd3d_test_main(void);
static const char *vkd3d_test_name;

#define START_TEST(name) static const char *vkd3d_test_name = #name; \
        static void vkd3d_test_main(void)

#define ok ok_(__LINE__)
#define todo todo_(__LINE__)
#define skip skip_(__LINE__)
#define trace trace_(__LINE__)

#define ok_(line) \
        do { \
        unsigned int vkd3d_line = line; \
        VKD3D_TEST_OK

#define VKD3D_TEST_OK(args...) \
        vkd3d_test_ok(vkd3d_line, args); } while (0)

#define todo_(line) \
        do { \
        unsigned int vkd3d_line = line; \
        VKD3D_TEST_TODO

#ifdef _WIN32
# define VKD3D_TEST_TODO(args...) \
        vkd3d_test_ok(vkd3d_line, args); } while (0)
#else
# define VKD3D_TEST_TODO(args...) \
        vkd3d_test_todo(vkd3d_line, args); } while (0)
#endif  /* _WIN32 */

#define skip_(line) \
        do { \
        unsigned int vkd3d_line = line; \
        VKD3D_TEST_SKIP

#define VKD3D_TEST_SKIP(args...) \
        vkd3d_test_skip(vkd3d_line, args); } while (0)

#define trace_(line) \
        do { \
        unsigned int vkd3d_line = line; \
        VKD3D_TEST_TRACE

#define VKD3D_TEST_TRACE(args...) \
        vkd3d_test_trace(vkd3d_line, args); } while (0)

static struct
{
    LONG success_count;
    LONG failure_count;
    LONG skip_count;
    LONG todo_count;
    LONG todo_success_count;

    unsigned int debug;
} vkd3d_test_state;

static void VKD3D_PRINTF_FUNC(3, 4) VKD3D_UNUSED
vkd3d_test_ok(unsigned int line, bool result, const char *fmt, ...)
{
    if (result)
    {
        if (vkd3d_test_state.debug)
            printf("%s:%d: Test succeeded.\n", vkd3d_test_name, line);
        InterlockedIncrement(&vkd3d_test_state.success_count);
    }
    else
    {
        va_list args;
        va_start(args, fmt);
        printf("%s:%d: Test failed: ", vkd3d_test_name, line);
        vprintf(fmt, args);
        va_end(args);
        InterlockedIncrement(&vkd3d_test_state.failure_count);
    }
}

static void VKD3D_PRINTF_FUNC(3, 4) VKD3D_UNUSED
vkd3d_test_todo(unsigned int line, bool result, const char *fmt, ...)
{
    va_list args;

    if (result)
    {
        printf("%s:%d Todo succeeded: ", vkd3d_test_name, line);
        InterlockedIncrement(&vkd3d_test_state.todo_success_count);
    }
    else
    {
        printf("%s:%d: Todo: ", vkd3d_test_name, line);
        InterlockedIncrement(&vkd3d_test_state.todo_count);
    }

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

static void VKD3D_PRINTF_FUNC(2, 3) VKD3D_UNUSED
vkd3d_test_skip(unsigned int line, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("%s:%d: Test skipped: ", vkd3d_test_name, line);
    vprintf(fmt, args);
    va_end(args);
    InterlockedIncrement(&vkd3d_test_state.skip_count);
}

static void VKD3D_PRINTF_FUNC(2, 3) VKD3D_UNUSED
vkd3d_test_trace(unsigned int line, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    printf("%s:%d: ", vkd3d_test_name, line);
    vprintf(fmt, args);
    va_end(args);
}

#ifdef _WIN32
int wmain(void)
#else
int main(void)
#endif
{
    const char *vkd3d_test_debug;

    memset(&vkd3d_test_state, 0, sizeof(vkd3d_test_state));

    vkd3d_test_state.debug = (vkd3d_test_debug = getenv("VKD3D_TEST_DEBUG"))
            && (*vkd3d_test_debug == 'y' || *vkd3d_test_debug == '1');

    vkd3d_test_main();

    printf("%s: %lu tests executed (%lu failures, %lu skipped, %lu todo).\n",
            vkd3d_test_name,
            (unsigned long)(vkd3d_test_state.success_count
            + vkd3d_test_state.failure_count + vkd3d_test_state.todo_count
            + vkd3d_test_state.todo_success_count),
            (unsigned long)(vkd3d_test_state.failure_count
            + vkd3d_test_state.todo_success_count),
            (unsigned long)vkd3d_test_state.skip_count,
            (unsigned long)vkd3d_test_state.todo_count);

    return vkd3d_test_state.failure_count || vkd3d_test_state.todo_success_count;
}

#endif  /* __VKD3D_TEST_H */
