cmake_minimum_required(VERSION 3.15)
project(KCD_RE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# RE headers live one level up
set(RE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")

file(GLOB_RECURSE RE_HEADERS "${RE_ROOT}/*.h")

add_library(kcd_re STATIC check_sizes.cpp "${RE_ROOT}/Offsets/Offsets.cpp" ${RE_HEADERS})

# Precompiled header
target_precompile_headers(kcd_re PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PCH.h")

# Release-size STL containers (debug std::vector is 40+ bytes, retail is 24)
target_compile_definitions(kcd_re PRIVATE
    _ITERATOR_DEBUG_LEVEL=0
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

target_compile_options(kcd_re PRIVATE /utf-8 /W4 /wd4819 /wd4100)

target_include_directories(kcd_re PRIVATE
    ${RE_ROOT}
    ${RE_ROOT}/CryEngine/CryCommon
)

# Class layout dump:
#   cmake --preset layout                            (dump ALL classes)
#   cmake --preset default -DCLASS_LAYOUT=C_Soul     (dump one class)
#   cmake --build --preset default
# ---- Test plugin DLL ----
add_library(kcd_plugin SHARED "${RE_ROOT}/src/plugin.cpp")

target_precompile_headers(kcd_plugin PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/PCH.h")

target_compile_definitions(kcd_plugin PRIVATE
    _ITERATOR_DEBUG_LEVEL=0
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

target_compile_options(kcd_plugin PRIVATE /utf-8 /W4 /wd4819 /wd4100)

target_include_directories(kcd_plugin PRIVATE
    ${RE_ROOT}
    ${RE_ROOT}/CryEngine/CryCommon
)

target_link_libraries(kcd_plugin PRIVATE kcd_re)

# Class layout dump:
if(DEFINED CLASS_LAYOUT)
    if(CLASS_LAYOUT STREQUAL "ALL")
        target_compile_options(kcd_re PRIVATE /d1reportAllClassLayout)
    else()
        target_compile_options(kcd_re PRIVATE /d1reportSingleClassLayout${CLASS_LAYOUT})
    endif()
endif()
