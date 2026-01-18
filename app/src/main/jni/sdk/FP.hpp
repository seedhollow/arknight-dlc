/**
 * Project     : arknight-dlc-r3dnetwork
 * Created on  : 17/01/26
 * Author      : github.com/seedhollow
 * File        : FP.kt
 * Description :
 */


#ifndef ARKNIGHT_DLC_R3DNETWORK_FP_HPP
#define ARKNIGHT_DLC_R3DNETWORK_FP_HPP

#include "engine/il2cpp/il2cpp.hpp"

struct FP {
    long _serializedValue; //0x10


    static FP FromFloat(float value) {
        auto method = Il2Cpp::GetMethodOffset(OBFUSCATE("Torappu.Common.dll"), OBFUSCATE("Torappu"), OBFUSCATE("FP"), OBFUSCATE("FromFloat"), 1);
        if (method) {
            return CALL_STATIC_METHOD<FP, float>((uintptr_t) method, value);
        }
    }

    // public static Single ToFloat(FP value) { }
    static float ToFloat(FP value) {
        auto method = Il2Cpp::GetMethodOffset(OBFUSCATE("Torappu.Common.dll"), OBFUSCATE("Torappu"), OBFUSCATE("FP"), OBFUSCATE("ToFloat"), 1);
        if (method) {
            return CALL_STATIC_METHOD<float, FP>((uintptr_t) method, value);
        }
        return 0.0f;
    }
};

#endif //ARKNIGHT_DLC_R3DNETWORK_FP_HPP
