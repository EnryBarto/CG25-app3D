#pragma once

enum class AppState {
    NAVIGATION,
    TRACKBALL,
    MOVING_TRACKBALL,
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

inline const char* appStateToString(AppState state) {
    switch (state) {
        case AppState::NAVIGATION:      return "Navigation";
        case AppState::TRACKBALL:       return "Trackball";
        case AppState::MOVING_TRACKBALL:return "Trackball moving";
        case AppState::PICKING:         return "Picking objects";
        case AppState::OBJECTS_LIST:    return "Objects list";
        case AppState::EDITING_OBJ:     return "Editing object";
        case AppState::EDITING_MESH:    return "Editing mesh";
        case AppState::LOADING_FILES:   return "Started file loading";
        case AppState::FILE_LOAD:       return "Loading file";
        case AppState::WAIT_OBJ_FILE_CONFIRM:     return "Mesh loaded";
        case AppState::WAIT_TEXTURE_FILE_CONFIRM: return "Texture loaded";
        case AppState::WAIT_FILE_ABORT: return "File error";
        case AppState::PAUSED:          return "Paused";
        case AppState::LIGHT_SETTINGS:  return "Light settings";
        case AppState::CLOSED:          return "Closing";
        default:                        return "Unknown";
    }
}
