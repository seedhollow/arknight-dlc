#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include <numbers>

#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "dobby/dobby.h"
#include "Menu/FeatureModule.hpp"
#include "Includes/Utils.hpp"
#include "Includes/RemapTools.h"
#include "engine/il2cpp/il2cpp.hpp"
#include "KittyMemory/MemoryPatch.h"
#include "Includes/ObscuredTypes.hpp"
#include "Includes/ESPManager.h"
#include "Menu/JNILoader.hpp"
#include "Menu/Setup.hpp"
#include "Hacks/offsets.hpp"
#include "Hacks/Hooks.hpp"

//Target lib here
#define IL2CPP_MODULE OBFUSCATE("libil2cpp.so")

void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    espManager = new ESPManager();

    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!KittyMemory::getLibraryMap(IL2CPP_MODULE).isValid());

    LOGI(OBFUSCATE("%s has been loaded"), (const char *) IL2CPP_MODULE);
    LOGI(OBFUSCATE("Trying to hook in il2cpp now..."));

    sleep(5); // this is optional depending on your game if it takes time to load all the symbols

    auto p_handler = dlopen(IL2CPP_MODULE, RTLD_NOW);

    // check if dlopen succeeded
    if (!p_handler) {
        LOGE(OBFUSCATE("Failed to dlopen %s: %s"), (const char *) IL2CPP_MODULE, dlerror());
        return NULL;
    }

    do {
        sleep(1);
        LOGI(OBFUSCATE("Trying to attach to il2cpp..."));
    } while (!Il2Cpp::Attach());

    LOGI(OBFUSCATE("il2cpp attached successfully"));

    Offsets::ClientAntiCheatChecker_OnFixedUpdate           = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("ClientAntiCheatChecker"), OBFUSCATE("OnFixedUpdate"),1);
    Offsets::TimeCheatingDetector_get_LastResult            = Il2Cpp::GetMethodOffset(OBFUSCATE("ThirdPartyAssembly.dll"),OBFUSCATE("CodeStage.AntiCheat.Detectors"), OBFUSCATE("TimeCheatingDetector"), OBFUSCATE("get_LastResult"));
    Offsets::InjectionDetector_StartDetection               = Il2Cpp::GetMethodOffset(OBFUSCATE("ThirdPartyAssembly.dll"),OBFUSCATE("CodeStage.AntiCheat.Detectors"), OBFUSCATE("InjectionDetector"), OBFUSCATE("StartDetection"));
    Offsets::InjectionDetector_StartDetectionAutomatically  = Il2Cpp::GetMethodOffset(OBFUSCATE("ThirdPartyAssembly.dll"),OBFUSCATE("CodeStage.AntiCheat.Detectors"), OBFUSCATE("InjectionDetector"), OBFUSCATE("StartDetectionAutomatically"));
    Offsets::ObscuredCheatingDetector_StartDetection        = Il2Cpp::GetMethodOffset(OBFUSCATE("ThirdPartyAssembly.dll"),OBFUSCATE("CodeStage.AntiCheat.Detectors"), OBFUSCATE("ObscuredCheatingDetector"), OBFUSCATE("StartDetection"));

    Offsets::BattleController_GetCost                       = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("BattleController"), OBFUSCATE("GetCost"),1);
    Offsets::BattleController_Update                        = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("BattleController"), OBFUSCATE("Update"));

    Offsets::Entity_set_hp                                  = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("Entity"), OBFUSCATE("set_hp"),1);
    Offsets::Entity_OnTick                                  = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("Entity"), OBFUSCATE("OnTick"),1);
    Offsets::Entity_get_attackTime                          = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("Entity"), OBFUSCATE("get_attackTime"));
    Offsets::Entity_get_isFrozen                            = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("Entity"), OBFUSCATE("get_isFrozen"));
    Offsets::Entity_get_atk                                 = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("Entity"), OBFUSCATE("get_atk"));

    Offsets::BObject_get_side                               = Il2Cpp::GetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),OBFUSCATE("Torappu.Battle"), OBFUSCATE("BObject"), OBFUSCATE("get_side"));

    // Start hooking
    LOGI(OBFUSCATE("Starting hooks"));
    Hooks::InitHooks();
    return NULL;
}

__attribute__((constructor))
void init() {
    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
    RemapTools::RemapLibrary(OBFUSCATE("libLoader.so"));
}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // Failed to obtain JNIEnv
    }

    if (JNILoader::RegisterAll(env) != JNI_OK)
        return JNI_ERR;

    if (RegisterMenu(env) != 0)
        return JNI_ERR;

    return JNI_VERSION_1_6;
}
