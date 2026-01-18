//
// Created by github.com/seedhollow on 18/01/26.
//

/**
 * Project     : arknight-dlc-r3dnetwork
 * Created on  : 18/01/26
 * Author      : github.com/seedhollow
 * File        : ITextView.kt
 */

#ifndef ARKNIGHT_DLC_R3DNETWORK_ITEXTVIEW_HPP
#define ARKNIGHT_DLC_R3DNETWORK_ITEXTVIEW_HPP

#include "BaseWidget.hpp"
class ITextView : public BaseWidget {
public:
    /* Constructor
     * pName: Name of the text view
     * pText: Initial text of the text view (optional, default is empty)
     */
    ITextView(const std::string& pName) {
        type = "ITextView";
        name = pName;
    }

    json ToJson() const override {
        return {
                {"type", type},
                {"name", name},
        };
    }

    std::string text;
};

#endif //ARKNIGHT_DLC_R3DNETWORK_ITEXTVIEW_HPP
