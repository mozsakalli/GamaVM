# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
#, --no-warn-shared-textrel
set (CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wall -v -Wl,--no-fatal-warnings")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fshort-wchar")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fshort-wchar")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set (CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        /Users/mustafa/Work/GamaVM/digi/digi/class.c
        /Users/mustafa/Work/GamaVM/digi/digi/exception.c
        /Users/mustafa/Work/GamaVM/digi/digi/gc.c
        /Users/mustafa/Work/GamaVM/digi/digi/interpret.c
        /Users/mustafa/Work/GamaVM/digi/digi/invoke.c
        /Users/mustafa/Work/GamaVM/digi/digi/mem.c
        /Users/mustafa/Work/GamaVM/digi/digi/miniz.c
        /Users/mustafa/Work/GamaVM/digi/digi/natives.c
        /Users/mustafa/Work/GamaVM/digi/digi/parse.c
        /Users/mustafa/Work/GamaVM/digi/digi/utf.c
        /Users/mustafa/Work/GamaVM/digi/digi/vm.c
        /Users/mustafa/Work/GamaVM/digi/digi/vm_native.c
        /Users/mustafa/Work/GamaVM/digi/digi/digiplay.c
        /Users/mustafa/Work/GamaVM/digi/digi/digiplay_gl.c
        /Users/mustafa/Work/GamaVM/digi/digi/android_native.cpp
        /Users/mustafa/Work/GamaVM/digi/digi/android_net.cpp
        /Users/mustafa/Work/GamaVM/digi/digi/jdwp.cpp
        /Users/mustafa/Work/GamaVM/digi/digi/jni.cpp
        /Users/mustafa/Work/GamaVM/digi/digi/d.c

)
# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        native-lib
        EGL
        GLESv2
        ${log-lib})