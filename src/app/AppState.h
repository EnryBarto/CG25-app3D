#pragma once

#include <string>

enum class AppState {
    NAVIGATION,
    PICKING,
    EDITING,
    PAUSED,
    CLOSED
};

inline std::string appStateToString(AppState state) {
    switch (state) {
        case AppState::NAVIGATION:  return "Navigation mode";
        case AppState::PICKING:     return "Picking";
        case AppState::EDITING:     return "Editing object";
        case AppState::PAUSED:      return "Paused";
        case AppState::CLOSED:      return "Closing";
        default:                    return "Unknown";
    }
}