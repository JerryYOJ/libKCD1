#pragma once

// -----------------------------------------------
// I_ExactPosHelperListener — exact positioning callback
// -----------------------------------------------
// RTTI: .?AVI_ExactPosHelperListener@entitymodule@wh@@
// C_Player implements at object offset +0x9F0

namespace wh::entitymodule {

struct I_ExactPosHelperListener {
    inline static constexpr auto RTTI = Offsets::RTTI_I_ExactPosHelperListener;
    virtual ~I_ExactPosHelperListener() = default;
    virtual void OnExactPosReached() {}
    virtual bool OnExactPosQuery() { return false; }
};

} // namespace wh::entitymodule
