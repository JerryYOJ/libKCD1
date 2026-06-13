project(FastTravelCancel LANGUAGES CXX)

file(GLOB_RECURSE PLUGIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

add_library(FastTravelCancel SHARED ${PLUGIN_SOURCES})

target_precompile_headers(FastTravelCancel PRIVATE "${RE_BUILDENV}/PCH.h")

target_compile_definitions(FastTravelCancel PRIVATE
    _ITERATOR_DEBUG_LEVEL=0 WIN32_LEAN_AND_MEAN NOMINMAX)

target_compile_options(FastTravelCancel PRIVATE /utf-8 /W4 /wd4819 /wd4100)

target_include_directories(FastTravelCancel PRIVATE
    ${RE_ROOT}/include ${RE_ROOT}/include/CryEngine/CryCommon ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(FastTravelCancel PRIVATE kcd_re spdlog::spdlog)

# ---- Auto-deploy to the game's mod folder ----
set(PLUGIN_DEPLOY "C:/Program Files (x86)/Steam/steamapps/common/KingdomComeDeliverance/mods/FastTravelCancel/KCSE/Plugins")
add_custom_command(TARGET FastTravelCancel POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${PLUGIN_DEPLOY}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:FastTravelCancel>" "${PLUGIN_DEPLOY}/"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_PDB_FILE:FastTravelCancel>" "${PLUGIN_DEPLOY}/"
    COMMENT "Deploying FastTravelCancel.dll + .pdb to ${PLUGIN_DEPLOY}"
)
