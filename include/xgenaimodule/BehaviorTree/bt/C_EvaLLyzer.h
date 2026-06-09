#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "C_LinkNoData.h"
#include "C_LyzerBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EvaLLyzer>.

namespace wh::xgenaimodule::BehaviorTree {

// <EvaLLyzer>  RTTI C_EvaLLyzer  vtable 0x1821dad90  size 0x50  base C_LyzerBase<C_LinkNoData<C_FixedComposite<1>>>  ctx S_EvaLLyzerContext
struct S_EvaLLyzerContext;
class C_EvaLLyzer : public C_NodeWrapper<C_EvaLLyzer, C_LyzerBase<C_LinkNoData<C_FixedComposite<1>>>, S_EvaLLyzerContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_EvaLLyzer;
    uint8_t _ownState[0x20];   // [UNVERIFIED] own members above C_LyzerBase<C_LinkNoData<C_FixedComposite<1>>> (0x30)
};
static_assert(sizeof(C_EvaLLyzer) == 0x50);

}  // namespace wh::xgenaimodule::BehaviorTree
