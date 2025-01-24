// Copyright (c) 2017-2024, The Khronos Group Inc.
// Copyright (c) 2017-2019 Valve Corporation
// Copyright (c) 2017-2019 LunarG, Inc.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT
//
// Initial Authors: Mark Young <marky@lunarg.com>, Dave Houlton <daveh@lunarg.com>
//

#pragma once

#include <cassert>
#include <sstream>
#include <string>

#include "xr_dependencies.h"
#include "platform_utils.hpp"

#if defined(__GNUC__) && __GNUC__ >= 4
#define LOADER_EXPORT __attribute__((visibility("default")))
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590)
#define LOADER_EXPORT __attribute__((visibility("default")))
#else
#define LOADER_EXPORT
#endif

// Environment variables

#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

#define PATH_SEPARATOR ':'
#define DIRECTORY_SYMBOL '/'

// Dynamic Loading of libraries:
typedef void *LoaderPlatformLibraryHandle;
static inline LoaderPlatformLibraryHandle LoaderPlatformLibraryOpen(const std::string &path) {
    // When loading the library, we use RTLD_LAZY so that not all symbols have to be
    // resolved at this time (which improves performance). Note that if not all symbols
    // can be resolved, this could cause crashes later.
    // For experimenting/debugging: Define the LD_BIND_NOW environment variable to force all
    // symbols to be resolved here.
    return dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
}

static inline const char *LoaderPlatformLibraryOpenError(const std::string &path) {
    (void)path;
    return dlerror();
}

static inline void LoaderPlatformLibraryClose(LoaderPlatformLibraryHandle library) { dlclose(library); }

static inline void *LoaderPlatformLibraryGetProcAddr(LoaderPlatformLibraryHandle library, const std::string &name) {
    assert(library);
    assert(!name.empty());
    return dlsym(library, name.c_str());
}

static inline const char *LoaderPlatformLibraryGetProcAddrError(const std::string &name) {
    (void)name;
    return dlerror();
}
