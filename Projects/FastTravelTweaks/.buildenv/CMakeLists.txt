project(FastTravelTweaks LANGUAGES CXX)

file(GLOB_RECURSE PLUGIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

add_library(FastTravelTweaks SHARED ${PLUGIN_SOURCES})

target_precompile_headers(FastTravelTweaks PRIVATE "${RE_BUILDENV}/PCH.h")

target_compile_definitions(FastTravelTweaks PRIVATE
    _ITERATOR_DEBUG_LEVEL=0 WIN32_LEAN_AND_MEAN NOMINMAX)

target_compile_options(FastTravelTweaks PRIVATE /utf-8 /W4 /wd4819 /wd4100)

target_include_directories(FastTravelTweaks PRIVATE
    ${RE_ROOT}/include ${RE_ROOT}/include/CryEngine/CryCommon ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(FastTravelTweaks PRIVATE kcd_re spdlog::spdlog)

# ---- Auto-deploy to the game's mod folder ----
set(PLUGIN_DEPLOY "C:/Program Files (x86)/Steam/steamapps/common/KingdomComeDeliverance/mods/FastTravelTweaks/KCSE/Plugins")
add_custom_command(TARGET FastTravelTweaks POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PLUGIN_DEPLOY}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:FastTravelTweaks>" "${PLUGIN_DEPLOY}/"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_PDB_FILE:FastTravelTweaks>" "${PLUGIN_DEPLOY}/"
    COMMENT "Deploying FastTravelTweaks.dll + .pdb to ${PLUGIN_DEPLOY}"
)
