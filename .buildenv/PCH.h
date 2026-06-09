// Precompiled header for the KCD RE project.
//
// The body is now the kcd.h umbrella (analysis/gen_kcd.py) — every RE header in
// dependency order. Because the PCH is force-included into every TU, this makes the
// full RE surface AND Offsets::RTTI_* visible everywhere, so individual class headers
// need no per-header "Offsets/Offsets_RTTI.h" include.
#pragma once

#include <cstdint>
#include <cstring>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <functional>
#include <string>

#include "kcd.h"
