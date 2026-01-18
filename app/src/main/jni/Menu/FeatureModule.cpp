//
// Created by rosetta on 13/09/2024.
//

#include "FeatureModule.hpp"


void FeatureModule::OnDraw(JNIEnv *env, jclass clazz, jobject draw_view, jobject canvas) {
    Draw draw(env, draw_view, canvas);
    if (draw.isValid()) {
        Visuals::Update(draw, draw.getWidth(), draw.getHeight());
    } else {
        LOGE(OBFUSCATE("Draw is not valid in OnDraw"));
    }
}

jstring FeatureModule::GetFeatureList(JNIEnv *env, jobject context) {
    RegisterFeatures();

    std::string json = Widget::ToJsonString();
    return env->NewStringUTF(json.c_str());
}


/** Here you can add your features using the Widget system
 * It's better to keep the IDs unique for each widget
 * And now we have various widgets available like ICheckBox, ISwitch, ISlider, ISpinner, ICollapse, ICategory, IRadioButton, IInputText, IInputInt, IButtonLink
 * Some feature are support some HTML tags like <font color=#FF0000>red text</font>
 *Refer to the WidgetExport.hpp for all available widgets
 **/
void FeatureModule::RegisterFeatures() {
    Widget::Add(ICollapse(OBFUSCATE("Player"), {
            ICollapse::Child(ICheckBox(1, OBFUSCATE("No Cost"), OBFUSCATE("Deploy units without cost"), Vars::PlayerData.infinite_cost)),
            ICollapse::Child(ICheckBox(2, OBFUSCATE("Infinite HP"), OBFUSCATE("Make player units invincible"), Vars::PlayerData.infinite_hp)),
            ICollapse::Child(ISlider(3, OBFUSCATE("Player Attack Speed"), 1.0f, 10.0f)),
            ICollapse::Child(ISlider(4, OBFUSCATE("Player Attack Multiplier"), 1.0f, 10.0f)),
    }));

    Widget::Add(ICollapse(OBFUSCATE("Enemy"), {
            ICollapse::Child(ICheckBox(20, OBFUSCATE("Auto Kill <font color=#FFFF00>(Hot!)</font>"), OBFUSCATE("Automatically kill enemy units"), Vars::EnemyData.auto_kill)),
            ICollapse::Child(ICheckBox(21, OBFUSCATE("Freeze Position"), OBFUSCATE("Freeze enemy units in place"), Vars::EnemyData.freeze_position)),
    }));


    Widget::Add(ICollapse(OBFUSCATE("Game Setting"), {
            /*ICollapse::Child(ISpinner(10, OBFUSCATE("Game Speed"), {
                    OBFUSCATE("Slow Motion"),
                    OBFUSCATE("Standard"),
                    OBFUSCATE("Fast"),
                    OBFUSCATE("Super Fast"),
            })),*/

            ICollapse::Child(ICheckBox(11, OBFUSCATE("Auto Win <font color=#FFFF00>(Hot!)</font>"),OBFUSCATE("Automatically win the level"),Vars::GameData.auto_win)),
            ICollapse::Child(ITextView(OBFUSCATE("<font color=#FFFF00>Note : </font> Auto win are not working on tutorial levels, so don't try it there."))),
    }));
}

void FeatureModule::OnFeatureChanged(JNIEnv *env, jclass clazz, jobject obj, jint featNum, jstring featName, jint value, jboolean boolean, jstring str) {

    const char* name = env->GetStringUTFChars(featName, nullptr);
    const char* strVal = str != nullptr ? env->GetStringUTFChars(str, nullptr) : "";

    switch (featNum) {
        case 1: Vars::PlayerData.infinite_cost      = boolean; break; // No Cost
        case 2: Vars::PlayerData.infinite_hp        = boolean; break; // Infinite HP
        case 3: Vars::PlayerData.player_atk_spd     = value; break; // Player Attack Speed
        case 4: Vars::PlayerData.player_atk_multiplier = value; break; // Player Attack Multiplier
        case 10: Vars::GameData.game_speed          = value; break; // Game Speed
        case 11: Vars::GameData.auto_win            = boolean; break; // Auto Win
        case 20: Vars::EnemyData.auto_kill          = boolean; break; // Auto Kill
        case 21: Vars::EnemyData.freeze_position    = boolean; break; // Freeze Position
        default: break;
    }

    env->ReleaseStringUTFChars(featName, name);
    if (str != nullptr) env->ReleaseStringUTFChars(str, strVal);
}