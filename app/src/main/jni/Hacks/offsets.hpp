#pragma once
#include <cstdint>

/**
 * Project     : arknight-dlc-r3dnetwork
 * Created on  : 17/01/26
 * Author      : github.com/seedhollow
 * File        : offsets.kt
 * Description : 
 *
 * Copyright (c) 2026. 
 * All rights reserved. Unauthorized copying, modification, or distribution 
 * of this file, via any medium, is strictly prohibited.
 */

#ifndef ARKNIGHT_DLC_R3DNETWORK_OFFSETS_HPP
#define ARKNIGHT_DLC_R3DNETWORK_OFFSETS_HPP


namespace Offsets {
    inline void* ClientAntiCheatChecker_OnFixedUpdate           = nullptr;
    inline void* TimeCheatingDetector_get_LastResult            = nullptr;
    inline void* InjectionDetector_StartDetection               = nullptr;
    inline void* InjectionDetector_StartDetectionAutomatically  = nullptr;
    inline void* ObscuredCheatingDetector_StartDetection        = nullptr;

    inline void* BattleController_GetCost                       = nullptr;
    inline void* BattleController_Update                        = nullptr;

    inline void* Entity_set_hp                                  = nullptr;
    inline void* Entity_OnTick                                  = nullptr;
    inline void* Entity_get_attackTime                          = nullptr;
    inline void* Entity_get_isFrozen                            = nullptr;
    inline void* Entity_get_atk                                 = nullptr;

    inline void* BObject_get_side                               = nullptr;
}

#endif //ARKNIGHT_DLC_R3DNETWORK_OFFSETS_HPP
