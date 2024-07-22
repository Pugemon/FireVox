#pragma once


#include "../Config.hpp"

class FIREVOX_API IApp {
public:
    virtual bool Init() = 0;
    virtual bool Exit() = 0;

    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    virtual const char* GetName() = 0;

    struct Settings {
        /// Window width
        int32_t mWidth = -1;
        /// Window height
        int32_t mHeight = -1;
        /// monitor index
        int32_t mMonitorIndex = -1;
        /// x position for window
        int32_t mWindowX = 0;
        /// y position for window
        int32_t mWindowY = 0;
        /// Set to true if fullscreen mode has been requested
        bool mFullScreen = false;
        /// Set to true if app wants to use an external window
        bool mExternalWindow = false;
        /// Drag to resize enabled
        bool mDragToResize = true;
        /// Border less window
        bool mBorderlessWindow = false;
        /// Set to true if oversize windows requested
        bool mAllowedOverSizeWindows = false;
        /// if settings is already initiazlied we don't fill when opening window
        bool mInitialized = false;
        /// if requested to quit the application
        bool mQuit = false;
        /// if benchmarking mode is enabled
        bool mBenchmarking = false;
        /// if the window is positioned in the center of the screen
        bool mCentered = true;
        /// if the window is focused or in foreground
        bool mFocused = true;
        /// Force lowDPI settings for this window
        bool mForceLowDPI = false;
    } mSettings;

    const char* pCommandLine = nullptr;

    static int argc;
    static const char** argv;
};

#if defined(_WINDOWS)
FORGE_API extern int WindowsMain(int argc, char** argv, IApp* app);
#define RUN_APPLICATION_MAIN(argc, argv, appInstance, customPtr) WindowsMain(argc, argv, &(appInstance))

#define DEFINE_APPLICATION_MAIN(appClass)                                                \
    int WindowsMain(int argc, char** argv, IApp* app);                                   \
    extern "C" {                                                                         \
    __declspec(dllexport) extern const UINT D3D12SDKVersion = D3D12_AGILITY_SDK_VERSION; \
    __declspec(dllexport) extern const char* D3D12SDKPath = u8"";                        \
    }                                                                                    \
                                                                                         \
    int main(int argc, char** argv) {                                                    \
        IApp::argc = argc;                                                               \
        IApp::argv = (const char**) argv;                                                \
        static appClass app = {};                                                        \
        return WindowsMain(argc, argv, &app);                                            \
    }
#elif defined(TARGET_IOS)
FORGE_API extern int iOSMain(int argc, char** argv, IApp* app);
#define RUN_APPLICATION_MAIN(argc, argv, appInstance, customPtr) iOSMain(argc, argv, &(appInstance))

#define DEFINE_APPLICATION_MAIN(appClass)                 \
    extern int iOSMain(int argc, char** argv, IApp* app); \
                                                          \
    int main(int argc, char** argv) {                     \
        IApp::argc = argc;                                \
        IApp::argv = (const char**) argv;                 \
        static appClass app = {};                         \
        return iOSMain(argc, argv, &app);                 \
    }
#elif defined(__APPLE__)
FORGE_API extern int macOSMain(int argc, const char** argv, IApp* app);
#define RUN_APPLICATION_MAIN(argc, argv, appInstance, customPtr) macOSMain(argc, (const char**) argv, &(appInstance))

#define DEFINE_APPLICATION_MAIN(appClass)                         \
    extern int macOSMain(int argc, const char** argv, IApp* app); \
                                                                  \
    int main(int argc, const char* argv[]) {                      \
        IApp::argc = argc;                                        \
        IApp::argv = argv;                                        \
        static appClass app = {};                                 \
        return macOSMain(argc, argv, &app);                       \
    }
#elif defined(__ANDROID__)
FORGE_API extern int AndroidMain(void* param, IApp* app);
#define RUN_APPLICATION_MAIN(argc, argv, appInstance, customPtr) AndroidMain(customPtr, &(appInstance))

#define DEFINE_APPLICATION_MAIN(appClass)           \
    extern int AndroidMain(void* param, IApp* app); \
                                                    \
    void android_main(struct android_app* param) {  \
        IApp::argc = 0;                             \
        IApp::argv = NULL;                          \
        static appClass app = {};                   \
        AndroidMain(param, &app);                   \
    }

#elif defined(__linux__)
FIREVOX_API extern int LinuxMain(int argc, char** argv, IApp* app);
#define RUN_APPLICATION_MAIN(argc, argv, appInstance, customPtr) LinuxMain(argc, argv, &(appInstance))

#define DEFINE_APPLICATION_MAIN(appClass)                   \
    extern int LinuxMain(int argc, char** argv, IApp* app); \
                                                            \
    int main(int argc, char** argv) {                       \
        IApp::argc = argc;                                  \
        IApp::argv = (const char**) argv;                   \
        static appClass app = {};                           \
        return LinuxMain(argc, argv, &app);                 \
    }
#endif
