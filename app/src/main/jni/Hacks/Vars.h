//
// Created by rosetta on 01/06/2024.
//

// Here you can store the variables of your features

#pragma once
namespace Vars {
    struct PlayerData_t {
        bool infinite_cost = false;
        bool infinite_hp = false;

        int player_atk_spd = 1; // Attack speed multiplier
        int player_atk_multiplier = 1; // Attack damage multiplier
    };

    struct EnemyData_t {
        // Add enemy-related variables here
        bool auto_kill = false;
        bool freeze_position = false;
    };

    struct GameData_t {
        // Add game-related variables here
        int game_speed = 1; // Normal speed
        bool auto_win = false;
    };

    inline PlayerData_t PlayerData;
    inline GameData_t GameData;
    inline EnemyData_t EnemyData;
}
