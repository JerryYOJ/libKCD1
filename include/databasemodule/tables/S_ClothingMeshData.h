#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mesh_file_path"  row_size: 24
// Registration: 0x1800f24d0
#pragma pack(push, 1)
struct S_ClothingMeshData {
    uint8_t _rowbase[8];  // 0x000
    const char* mesh_file_path;  // 0x008  // PK
    // int32_t used_translucency_max;  // 0x00C (alias)
    const char* triangle_opacity;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_ClothingMeshData) == 24, "Size mismatch for S_ClothingMeshData");

}  // namespace wh::databasemodule
