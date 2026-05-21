#pragma once

// I_InventoryListener — inventory event callback interface
// Inherited by C_Soul to receive inventory change notifications

namespace wh::entitymodule {

class I_InventoryListener {
public:
    virtual ~I_InventoryListener() {}
};

}  // namespace wh::entitymodule
