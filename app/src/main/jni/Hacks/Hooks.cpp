//
// Created by github.com/seedhollow on 17/10/25.
//

#include "Hooks.hpp"


void Hooks::InitHooks() {
    // ----------------- Hooks -------------------

    DobbyHook(Offsets::ClientAntiCheatChecker_OnFixedUpdate,(void *) Hooks::HkClientAntiCheatChecker_OnFixedUpdate,(void **) &Hooks::orig_HkClientAntiCheatChecker_OnFixedUpdate);
    DobbyHook(Offsets::TimeCheatingDetector_get_LastResult,(void *) Hooks::HkTimeCheatingDetectorGetLastResult,(void **) &Hooks::orig_HkTimeCheatingDetectorGetLastResult);
    DobbyHook(Offsets::InjectionDetector_StartDetection,(void *) Hooks::HkInjectionDetector_StartDetection,(void **) &Hooks::orig_InjectionDetector_StartDetection);
    DobbyHook(Offsets::InjectionDetector_StartDetectionAutomatically,(void *) Hooks::HkInjectionDetector_StartDetectionAutomatically,(void **) &Hooks::orig_InjectionDetector_StartDetectionAutomatically);
    DobbyHook(Offsets::ObscuredCheatingDetector_StartDetection,(void *) Hooks::HkObscuredCheatingDetector_StartDetection,(void **) &Hooks::orig_ObscuredCheatingDetector_StartDetection);

    DobbyHook(Offsets::BattleController_Update,(void *) Hooks::HkBattleController_Update,(void **) &Hooks::orig_BattleController_Update);
    DobbyHook(Offsets::BattleController_GetCost,(void *) Hooks::HkBattleController_GetCost,(void **) &Hooks::orig_BattleController_GetCost);

    DobbyHook(Offsets::Entity_OnTick,(void *) Hooks::HkEntity_OnTick,(void **) &Hooks::orig_HkEntity_OnTick);
    DobbyHook(Offsets::Entity_get_attackTime,(void *) Hooks::HkEntity_get_attackTime,(void **) &Hooks::orig_Entity_get_attackTime);
    DobbyHook(Offsets::Entity_get_isFrozen,(void *) Hooks::HkEntity_get_isFrozen,(void **) &Hooks::orig_HkEntity_get_isFrozen);
    DobbyHook(Offsets::Entity_get_atk,(void *) Hooks::HkEntity_get_atk,(void **) &Hooks::orig_Entity_get_atk);

}

void (*Hooks::orig_HkClientAntiCheatChecker_OnFixedUpdate)(void *pInstance, void* deltaTime) = nullptr;
int (*Hooks::orig_HkTimeCheatingDetectorGetLastResult)(void *pInstance) = nullptr;

void (*Hooks::orig_InjectionDetector_StartDetection)() = nullptr;
void (*Hooks::orig_InjectionDetector_StartDetectionAutomatically)() = nullptr;
void (*Hooks::orig_ObscuredCheatingDetector_StartDetection)() = nullptr;

void (*Hooks::orig_BattleController_Update)(void *pInstance) = nullptr;
int (*Hooks::orig_BattleController_GetCost)(void *pInstance, int side) = nullptr;

void (*Hooks::orig_HkEntity_OnTick)(void *pInstance, FP deltaTime) = nullptr;

FP (*Hooks::orig_Entity_get_attackTime)(void *pInstance) = nullptr;
bool (*Hooks::orig_HkEntity_get_isFrozen)(void *pInstance) = nullptr;

FP (*Hooks::orig_Entity_get_atk)(void *pInstance) = nullptr;


void Hooks::HkClientAntiCheatChecker_OnFixedUpdate(void *pInstance, void *deltaTime)  {
    // Bypass the anti-cheat mechanism
    if (pInstance){
        ObscuredTypes::SetObscuredFloat((uint64_t) pInstance + Il2Cpp::GetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Torappu.Battle"), OBFUSCATE("ClientAntiCheatChecker"), OBFUSCATE("m_checkTimes")), 0.0f);
        ObscuredTypes::SetObscuredFloat((uint64_t) pInstance + Il2Cpp::GetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Torappu.Battle"), OBFUSCATE("ClientAntiCheatChecker"), OBFUSCATE("m_moveMultiplier")), 0.0f);
        ObscuredTypes::SetObscuredFloat((uint64_t) pInstance + Il2Cpp::GetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("Torappu.Battle"), OBFUSCATE("ClientAntiCheatChecker"), OBFUSCATE("m_isValidBattle")), 1.0f);

        return;
    }

    orig_HkClientAntiCheatChecker_OnFixedUpdate(pInstance, deltaTime);
}

int Hooks::HkTimeCheatingDetectorGetLastResult(void *_this) {
    /*public const TimeCheatingDetectorResult Unknown = 0; // 0x0
    public const TimeCheatingDetectorResult CheckPassed = 5; // 0x0
    public const TimeCheatingDetectorResult CheatDetected = 10; // 0x0
    public const TimeCheatingDetectorResult Error = 15; // 0x0*/

    if (_this){
        return 5; // CheckPassed
    }
    return 0;
}

void Hooks::HkInjectionDetector_StartDetection() {
    // Bypass the injection detection
    LOGD(OBFUSCATE("InjectionDetector StartDetection bypassed"));
}

void Hooks::HkInjectionDetector_StartDetectionAutomatically() {
    // Bypass the injection detection automatically
    LOGD(OBFUSCATE("InjectionDetector StartDetectionAutomatically bypassed"));
}

void Hooks::HkObscuredCheatingDetector_StartDetection() {
    // Bypass the obscured cheating detection
    LOGD(OBFUSCATE("ObscuredCheatingDetector StartDetection bypassed"));
}

void Hooks::HkBattleController_Update(void *pInstance) {
    if (pInstance){
        // Set game speed
        //CALL_METHOD<void,int>((uintptr_t) Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("BattleController"), OBFUSCATE("set_speedLevel"),1), pInstance, Vars::GameData.game_speed);

        // Implement auto win logic here if needed
        if (Vars::GameData.auto_win) {
            // 0 = NOT_YET, 1 = WIN, 2 = LOSE
            auto _doFinishGameMethod = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("BattleController"), OBFUSCATE("_DoFinishGame"),2);
            auto _getGameResultMethod = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("BattleController"), OBFUSCATE("get_gameResult"),0);
            if (_doFinishGameMethod && _getGameResultMethod) {
                auto result = CALL_METHOD<int>((uintptr_t) _getGameResultMethod, pInstance);
                LOGD(OBFUSCATE("Current game result: %d"), result);
                if (result == 0) {
                    CALL_METHOD<void, int, bool>((uintptr_t)_doFinishGameMethod, pInstance, 1, true);
                }
            }
        }
        return;
    }
    orig_BattleController_Update(pInstance);
}

int Hooks::HkBattleController_GetCost(void *pInstance, int side) {
    if (pInstance){
        if (Vars::PlayerData.infinite_cost) {
            return 99;
        }
    }
    return orig_BattleController_GetCost(pInstance, side);
}


/*public const SideType NONE = 0; // 0x0
public const SideType ALLY = 1; // 0x0
public const SideType ENEMY = 2; // 0x0
public const SideType BOTH_ALLY_AND_ENEMY = 3; // 0x0
public const SideType NEUTRAL = 4; // 0x0
public const SideType ALL = 7; // 0x0*/

void Hooks::HkEntity_OnTick(void *pInstance, FP deltaTime) {
    if (pInstance){
        int _current_side = CALL_METHOD<int>((uintptr_t) Offsets::BObject_get_side, pInstance);

        if (Vars::PlayerData.infinite_hp && _current_side == 1) { // ALLY
            // Set HP to max HP
            auto max_hp = CALL_METHOD<FP>((uintptr_t) Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("Entity"), OBFUSCATE("get_maxHp"),0), pInstance);
            LOGD("Entity Max HP: %f", FP::ToFloat(max_hp));

            CALL_METHOD<void, FP>((uintptr_t) Offsets::Entity_set_hp, pInstance, max_hp);
        }

        if (Vars::EnemyData.auto_kill && _current_side == 2) { // ENEMY
            // Set HP to zero
            FP zero_fp = FP::FromFloat(0.0f);
            CALL_METHOD<void, FP>((uintptr_t) Offsets::Entity_set_hp, pInstance, zero_fp);
        }
    }
    orig_HkEntity_OnTick(pInstance, deltaTime);
}


FP Hooks::HkEntity_get_attackTime(void *pInstance) {
    if (pInstance){
        // Increase attack speed for player units
        int _current_side = CALL_METHOD<int>((uintptr_t) Offsets::BObject_get_side, pInstance);
        if (_current_side == 1) { // ALLY
            FP original_attack_time = orig_Entity_get_attackTime(pInstance);
            original_attack_time._serializedValue /= Vars::PlayerData.player_atk_spd;
            LOGD("Modified Attack Time: %f", FP::ToFloat(original_attack_time));
            return original_attack_time;
        }
    }
    return orig_Entity_get_attackTime(pInstance);
}

bool Hooks::HkEntity_get_isFrozen(void *pInstance) {
    if (pInstance){
        int _current_side = CALL_METHOD<int>((uintptr_t) Offsets::BObject_get_side, pInstance);
        if (Vars::EnemyData.freeze_position && _current_side == 2) { // ENEMY
            return true; // Freeze enemy position
        }
    }
    return orig_HkEntity_get_isFrozen(pInstance);
}

FP Hooks::HkEntity_get_atk(void *pInstance) {
    if (pInstance){
        // You can modify attack value here if needed
        int _current_side = CALL_METHOD<int>((uintptr_t) Offsets::BObject_get_side, pInstance);
        if (_current_side == 1) { // ALLY
            FP original_atk = orig_Entity_get_atk(pInstance);
            original_atk._serializedValue *= Vars::PlayerData.player_atk_multiplier;
            LOGD("Modified Attack Value: %f", FP::ToFloat(original_atk));
            return original_atk;
        }
    }
    return orig_Entity_get_atk(pInstance);
}