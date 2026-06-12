project(AutoSave LANGUAGES CXX)

file(GLOB_RECURSE PLUGIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

add_library(AutoSave SHARED ${PLUGIN_SOURCES})

target_precompile_headers(AutoSave PRIVATE "${RE_BUILDENV}/PCH.h")

target_compile_definitions(AutoSave PRIVATE
    _ITERATOR_DEBUG_LEVEL=0 WIN32_LEAN_AND_MEAN NOMINMAX)

target_compile_options(AutoSave PRIVATE /utf-8 /W4 /wd4819 /wd4100)

target_include_directories(AutoSave PRIVATE
    ${RE_ROOT}/include ${RE_ROOT}/include/CryEngine/CryCommon ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(AutoSave PRIVATE kcd_re spdlog::spdlog)
