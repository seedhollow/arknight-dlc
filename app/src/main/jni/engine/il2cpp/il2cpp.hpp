/**
 * Project     : arknight-dlc-r3dnetwork
 * Created on  : 17/01/26
 * Author      : github.com/seedhollow
 * File        : il2cpp.kt
 * Description :
 */

#pragma once

#include <cstdio>
#include <android/log.h>
#include <dlfcn.h>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <cinttypes>
#include <codecvt>
#include <locale>
#include <iostream>
#include <vector>
#include <iterator>
#include "Includes/obfuscate.h"

using namespace std;

#ifndef ML_IL2CPP_H
#define ML_IL2CPP_H

#include "il2cpp_type.hpp"

// unity call
template<typename Ret, typename... Args>
Ret CALL_METHOD(uintptr_t address, void* instance, Args... args) {
    using NativeFn = Ret(*)(void*, Args..., void*);
    auto func = reinterpret_cast<NativeFn>(address);
    return func(instance, args..., nullptr);
}

template<typename Ret, typename... Args>
Ret CALL_STATIC_METHOD(uintptr_t address, Args... args) {
    using NativeFn = Ret(*)(Args..., void*);
    auto func = reinterpret_cast<NativeFn>(address);
    return func(args..., nullptr);
}


namespace Il2Cpp {
    bool Attach(const char *libname = OBFUSCATE("libil2cpp.so"));

    void *GetImage(const char *image);
    void *GetClass(const char *image, const char *namespaze, const char *clazz);
    void *CreateArray(const char *image, const char *namespaze, const char *clazz, size_t length);

    void *GetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, int argsCount = 0);
    void *GetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, char **args, int argsCount = 0);
    uintptr_t GetFieldOffset(const char *image, const char *namespaze, const char *clazz, const char *name);
    void GetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void *output);
    void SetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void *value);
    void *NewClassObject(const char *image, const char *namespaze, const char *clazz);

    vector<void*> GetOffset(const char *image, const char *namespaze, const char *clazz);
    vector<const char*> getNameMethod(const char *image, const char *namespaze, const char *clazz);
    bool IsAssembliesLoaded();
};

template<typename T>
using Array = Il2CppArray<T>;

typedef Il2CppString String;

template<typename T>
using List = Il2CppList<T>;

template<typename K, typename V>
using Dictionary = Il2CppDictionary<K, V>;

uintptr_t Il2CppBase();

#endif //ML_IL2CPP_H
