#pragma once

// -----------------------------------------------
// IMovieSystem - CryEngine movie-system interface.
// -----------------------------------------------
// Binary slot order from CMovieSystem vtable @ RVA 0x279FD10.
// The SDK IMovieSystem header is interfuscator-tagged; only verified slots are named.

struct SCameraParams;

namespace Offsets {

struct IMovieSystem {
    virtual ~IMovieSystem() {} // [0] 0x181E33860
    virtual void _vf01() = 0;
    virtual void _vf02() = 0;
    virtual void _vf03() = 0;
    virtual void _vf04() = 0;
    virtual void _vf05() = 0;
    virtual void _vf06() = 0;
    virtual void _vf07() = 0;
    virtual void _vf08() = 0;
    virtual void _vf09() = 0;
    virtual void _vf10() = 0;
    virtual void _vf11() = 0;
    virtual void _vf12() = 0;
    virtual void _vf13() = 0;
    virtual void _vf14() = 0;
    virtual void _vf15() = 0;
    virtual void _vf16() = 0;
    virtual void _vf17() = 0;
    virtual void _vf18() = 0;
    virtual void _vf19() = 0;
    virtual void _vf20() = 0;
    virtual void _vf21() = 0;
    virtual void _vf22() = 0;
    virtual void _vf23() = 0;
    virtual void _vf24() = 0;
    virtual void _vf25() = 0;
    virtual void _vf26() = 0;
    virtual void _vf27() = 0;
    virtual void _vf28() = 0;
    virtual void _vf29() = 0;
    virtual void _vf30() = 0;
    virtual void _vf31() = 0;
    virtual void _vf32() = 0;
    virtual void _vf33() = 0;
    virtual void _vf34() = 0;
    virtual void _vf35() = 0;
    virtual void _vf36() = 0;
    virtual void _vf37() = 0;
    virtual void _vf38() = 0;
    virtual void _vf39() = 0;
    virtual void _vf40() = 0;
    virtual void _vf41() = 0;
    virtual void _vf42() = 0;
    virtual void _vf43() = 0;
    virtual void _vf44() = 0;
    virtual void _vf45() = 0;
    virtual void _vf46() = 0;
    virtual void _vf47() = 0;
    virtual void _vf48() = 0;
    virtual void _vf49() = 0;
    virtual void _vf50() = 0;
    virtual void _vf51() = 0;
    virtual void _vf52() = 0;
    virtual void _vf53() = 0;
    virtual void _vf54() = 0;
    virtual void _vf55() = 0;
    virtual void _vf56() = 0;
    virtual const SCameraParams& GetCameraParams() const = 0;     // [57] 0x18070F0C0
    virtual void SetCameraParams(const SCameraParams& params) = 0; // [58] 0x181E3E948
    virtual void _vf59() = 0;
    virtual void _vf60() = 0;
    virtual void _vf61() = 0;
    virtual void _vf62() = 0;
    virtual void _vf63() = 0;
    virtual void _vf64() = 0;
    virtual void _vf65() = 0;
    virtual void _vf66() = 0;
    virtual void _vf67() = 0;
    virtual void _vf68() = 0;
    virtual void _vf69() = 0;
    virtual void _vf70() = 0;
    virtual void _vf71() = 0;
    virtual void _vf72() = 0;
    virtual void _vf73() = 0;
    virtual void _vf74() = 0;
    virtual void _vf75() = 0;
    virtual void _vf76() = 0;
    virtual void _vf77() = 0;
    virtual void _vf78() = 0;
    virtual void _vf79() = 0;
    virtual void _vf80() = 0;
    virtual void _vf81() = 0;
    virtual void _vf82() = 0;
    virtual void _vf83() = 0;
    virtual void _vf84() = 0;
    virtual void _vf85() = 0;
    virtual void _vf86() = 0;
    virtual void _vf87() = 0;
    virtual void _vf88() = 0;
    virtual void _vf89() = 0;
    virtual void _vf90() = 0;
    virtual void _vf91() = 0;
};
static_assert(sizeof(IMovieSystem) == 0x8);

} // namespace Offsets
