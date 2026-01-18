//
// Created by rosetta on 05/07/2024.
//



#ifndef HOOKS_H
#define HOOKS_H

#include "Vars.h"
#include "offsets.hpp"
#include "engine/il2cpp/il2cpp.hpp"
#include "Includes/ObscuredTypes.hpp"
#include "Includes/obfuscate.h"
#include "dobby.h"
#include "Includes/Logger.h"
#include "SDK/FP.hpp"



class Hooks {
public:
    static void InitHooks();

    static void (*orig_ObscuredCheatingDetector_StartDetection)();
    static void HkObscuredCheatingDetector_StartDetection();

    static void (*orig_InjectionDetector_StartDetection)();
    static void HkInjectionDetector_StartDetection();

    static void (*orig_InjectionDetector_StartDetectionAutomatically)();
    static void HkInjectionDetector_StartDetectionAutomatically();

    static void (*orig_HkClientAntiCheatChecker_OnFixedUpdate)(void *pInstance, void* deltaTime);
    static void HkClientAntiCheatChecker_OnFixedUpdate(void *pInstance, void* deltaTime);

    static int (*orig_HkTimeCheatingDetectorGetLastResult)(void *pInstance);
    static int HkTimeCheatingDetectorGetLastResult(void *_this);

    static void (*orig_BattleController_Update)(void *pInstance);
    static void HkBattleController_Update(void *pInstance);

    static int (*orig_BattleController_GetCost)(void *pInstance, int side);
    static int HkBattleController_GetCost(void *pInstance, int side);

    static void (*orig_HkEntity_OnTick)(void *pInstance, FP deltaTime);
    static void HkEntity_OnTick(void *pInstance, FP deltaTime);

    static FP (*orig_Entity_get_attackTime)(void *pInstance);
    static FP HkEntity_get_attackTime(void *pInstance);

    static bool (*orig_HkEntity_get_isFrozen)(void *pInstance);
    static bool HkEntity_get_isFrozen(void *pInstance);

    static FP (*orig_Entity_get_atk)(void *pInstance);
    static FP HkEntity_get_atk(void *pInstance);


};

#endif // HOOKS_H
