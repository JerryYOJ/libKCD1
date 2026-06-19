project(CheatXtended LANGUAGES CXX)

file(GLOB_RECURSE PLUGIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

add_library(CheatXtended SHARED ${PLUGIN_SOURCES})

target_precompile_headers(CheatXtended PRIVATE "${RE_BUILDENV}/PCH.h")

target_compile_definitions(CheatXtended PRIVATE
    _ITERATOR_DEBUG_LEVEL=0 WIN32_LEAN_AND_MEAN NOMINMAX)

target_compile_options(CheatXtended PRIVATE /utf-8 /W4 /wd4819 /wd4100)

target_include_directories(CheatXtended PRIVATE
    ${RE_ROOT}/include ${RE_ROOT}/include/CryEngine/CryCommon ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(CheatXtended PRIVATE kcd_re spdlog::spdlog)

set(PLUGIN_DEPLOY "C:/Program Files (x86)/Steam/steamapps/common/KingdomComeDeliverance/mods/CheatXtended/KCSE/Plugins")
add_custom_command(TARGET CheatXtended POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PLUGIN_DEPLOY}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:CheatXtended>" "${PLUGIN_DEPLOY}/"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_PDB_FILE:CheatXtended>" "${PLUGIN_DEPLOY}/"
    COMMENT "Deploying CheatXtended.dll + .pdb to ${PLUGIN_DEPLOY}"
)
