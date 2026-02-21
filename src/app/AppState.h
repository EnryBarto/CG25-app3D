#pragma once

#include <string>

enum class AppState {
    NAVIGATION,
    PICKING,
    EDITING_OBJ,
    EDITING_MESH,
    PAUSED,
    CLOSED
};

inline std::string appStateToString(AppState state) {
    switch (state) {
        case AppState::NAVIGATION:  return "Navigation mode";
        case AppState::PICKING:     return "Picking";
        case AppState::EDITING_OBJ: return "Editing object";
        case AppState::EDITING_MESH:return "Editing mesh";
        case AppState::PAUSED:      return "Paused";
        case AppState::CLOSED:      return "Closing";
        default:                    return "Unknown";
    }
}