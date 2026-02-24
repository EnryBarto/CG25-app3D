#pragma once

#include <string>

enum class AppState {
    NAVIGATION,
    PICKING,
    OBJECTS_LIST,
    EDITING_OBJ,
    EDITING_MESH,
    LOADING_FILES,
    FILE_LOAD,
    WAIT_OBJ_FILE_CONFIRM,
    WAIT_TEXTURE_FILE_CONFIRM,
    WAIT_FILE_ABORT,
    PAUSED,
    LIGHT_SETTINGS,
    CLOSED
};

inline std::string appStateToString(AppState state) {
    switch (state) {
        case AppState::NAVIGATION:      return "Navigation mode";
        case AppState::PICKING:         return "Picking";
        case AppState::OBJECTS_LIST:    return "Objects list";
        case AppState::EDITING_OBJ:     return "Editing object";
        case AppState::EDITING_MESH:    return "Editing mesh";
        case AppState::LOADING_FILES:   return "Started file loading";
        case AppState::FILE_LOAD:       return "Loading file";
        case AppState::WAIT_OBJ_FILE_CONFIRM:     return "Meshes loaded";
        case AppState::WAIT_TEXTURE_FILE_CONFIRM: return "Texture loaded";
        case AppState::WAIT_FILE_ABORT: return "File error";
        case AppState::PAUSED:          return "Paused";
        case AppState::LIGHT_SETTINGS:  return "Light settings";
        case AppState::CLOSED:          return "Closing";
        default:                        return "Unknown";
    }
}
