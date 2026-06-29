#include "REL/Module.h"

#include <Windows.h>

#include <cstring>
#include <fstream>
#include <string>
#include <string_view>

namespace REL
{
	std::string_view to_string(Distribution a_dist) noexcept
	{
		switch (a_dist) {
		case Distribution::Steam: return "Steam";
		case Distribution::GOG:   return "GOG";
		case Distribution::Epic:  return "Epic";
		default:                  return "Unknown";
		}
	}

	Module& Module::get()
	{
		static Module singleton;
		return singleton;
	}

	Module::Module()
	{
		_base = reinterpret_cast<std::uintptr_t>(::GetModuleHandleW(FILENAME.data()));
		if (!_base) {
			::MessageBoxW(nullptr,
				L"REL::Module: WHGame.dll is not loaded into the process.",
				L"kcd_re", MB_OK | MB_ICONERROR);
			::TerminateProcess(::GetCurrentProcess(), 1);
		}
		resolve_game_root();
		load_pe();
		detect_distribution();
	}

	void Module::resolve_game_root()
	{
		wchar_t buf[MAX_PATH]{};
		const DWORD n = ::GetModuleFileNameW(nullptr, buf, MAX_PATH);
		std::wstring path(buf, n ? n : 0);
		// path = ...\KingdomComeDeliverance\Bin\Win64\<exe>  ->  strip exe, Win64, Bin
		for (int i = 0; i < 3; ++i) {
			const auto pos = path.find_last_of(L"\\/");
			if (pos == std::wstring::npos) {
				break;
			}
			path.resize(pos);
		}
		_gameRoot = path;
	}

	void Module::load_pe()
	{
		const auto b = reinterpret_cast<const std::uint8_t*>(_base);
		const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(b);
		const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS64*>(b + dos->e_lfanew);
		_timestamp = nt->FileHeader.TimeDateStamp;

		const auto sections = IMAGE_FIRST_SECTION(nt);
		const auto map = [&](const char* a_name, Segment::Name a_idx) {
			for (WORD i = 0; i < nt->FileHeader.NumberOfSections; ++i) {
				if (std::strncmp(reinterpret_cast<const char*>(sections[i].Name), a_name, 8) == 0) {
					_segments[a_idx] = Segment(
						_base,
						_base + sections[i].VirtualAddress,
						sections[i].Misc.VirtualSize);
					return;
				}
			}
		};
		map(".text", Segment::textx);
		map(".idata", Segment::idata);
		map(".rdata", Segment::rdata);
		map(".data", Segment::data);
		map(".pdata", Segment::pdata);
	}

	void Module::detect_distribution()
	{
		const auto seg = _segments[Segment::rdata];
		if (!seg.address() || !seg.size()) {
			_distribution = Distribution::Unknown;
			return;
		}
		const std::string_view hay(reinterpret_cast<const char*>(seg.address()), seg.size());
		if (hay.find("steam_api64.dll") != std::string_view::npos) {
			_distribution = Distribution::Steam;
		} else if (hay.find("Galaxy64.dll") != std::string_view::npos) {
			_distribution = Distribution::GOG;
		} else if (hay.find("EOSSDK-Win64-Shipping.dll") != std::string_view::npos) {
			_distribution = Distribution::Epic;
		} else {
			_distribution = Distribution::Unknown;
		}
	}

	std::string_view Module::release()
	{
		if (!_releaseQueried) {
			_releaseQueried = true;
			std::ifstream f((_gameRoot + L"\\system.cfg").c_str());
			std::string   line;
			while (std::getline(f, line)) {
				const auto key = line.find("wh_sys_version");
				if (key == std::string::npos) {
					continue;
				}
				const auto q1 = line.find('"', key);
				const auto q2 = q1 == std::string::npos ? std::string::npos : line.find('"', q1 + 1);
				if (q1 != std::string::npos && q2 != std::string::npos) {
					_release = line.substr(q1 + 1, q2 - q1 - 1);
				}
				break;
			}
		}
		return _release;
	}

	std::string_view Module::build_code()
	{
		if (!_buildQueried) {
			_buildQueried = true;
			std::ifstream f((_gameRoot + L"\\whdlversions.txt").c_str());
			std::string   line;
			if (std::getline(f, line)) {  // first line: "Build = 404-504czj4"
				const auto eq = line.find('=');
				if (eq != std::string::npos && line.find("Build") != std::string::npos) {
					auto v = line.substr(eq + 1);
					const auto s = v.find_first_not_of(" \t\r\n");
					const auto e = v.find_last_not_of(" \t\r\n");
					if (s != std::string::npos) {
						_buildCode = v.substr(s, e - s + 1);
					}
				}
			}
		}
		return _buildCode;
	}
}
