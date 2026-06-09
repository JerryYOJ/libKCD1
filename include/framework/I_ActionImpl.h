#pragma once

namespace wh::framework {

// ---------------------------------------------------------------------------
// I_ActionImpl — secondary MI base for action lifecycle.
//
// RTTI: .?AVI_ActionImpl@framework@wh@@
// TypeDescriptor: 0x1829f5298
//
// Provides the action lifecycle interface (Start/Stop/Update/Tick/Complete).
// Appears at offset +0x10 in C_Action via MI.
//
// In C_Action<I_CombatActorActionPrivate>, the secondary vtable at +0x10
// is at 0x1821aaaf0 with 8 method slots:
//   [0] dtor thunk (adjusts this by -0x10)
//   [1] Start — sets flags, calls primary vtable method
//   [2] Stop — clears state
//   [3] Update(float dt)
//   [4] Tick — calls primary vtable, fires signals
//   [5] Complete — sets m_isCompleted
//   [6] IsStarted — proxy, returns *(this-0x10+0xA8)
//   [7] GetParams — copies action params
// ---------------------------------------------------------------------------
class I_ActionImpl {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_ActionImpl;
    virtual ~I_ActionImpl() = default;                  // [0]
    virtual void Start() = 0;                           // [1] sub_18043065C
    virtual void Stop() = 0;                            // [2] sub_1804307F4
    virtual void Update(float dt) = 0;                  // [3] sub_1806236C4
    virtual void Tick() = 0;                            // [4] sub_180457948
    virtual void Complete() = 0;                        // [5] sub_1804305D8
    virtual bool IsStarted() const = 0;                 // [6] sub_180B1A324
    virtual void GetParams(void* outParams) const = 0;  // [7] sub_1806C1B44
};

}  // namespace wh::framework
