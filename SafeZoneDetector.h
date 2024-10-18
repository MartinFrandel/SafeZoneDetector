#ifndef SAFE_ZONE_DETECTOR_H
#define SAFE_ZONE_DETECTOR_H

#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

class SafeZoneDetector {
public:
    SafeZoneDetector() {}

    bool isSandboxed() {
        return checkSandbox();
    }

    bool isEmulator() {
        return checkEmulator();
    }

    bool isVirtualMachine() {
        return checkVirtualMachine();
    }

    bool isAnyVirtualEnvironment() {
        return isSandboxed() || isEmulator() || isVirtualMachine();
    }

private:
    bool checkSandbox() {
        std::vector<std::string> sandboxDlls = {
            "SbieDll", "SxIn", "Sf2", "snxhk", "cmdvrt32",
            "dbghelp", "api_log", "dir_watch", "pstorec",
            "vmGuestLib", "vmhgfs", "vboxhook", "VboxService",
            "VboxTray", "VmwVmx", "VBoxOGL", "vmwaretray",
            "vmtoolsd", "VBoxSF", "VBoxControl", "Procmon",
            "tcpview", "wireshark", "fiddler"
        };

        for (const auto& dll : sandboxDlls) {
            if (isModuleLoaded(dll + ".dll")) {
                std::cout << "Sandbox DLL detected: " << dll << ".dll" << std::endl;
                return true;
            }
        }
        return false;
    }

    bool isModuleLoaded(const std::string& moduleName) {
        HMODULE hModule = ::GetModuleHandleA(moduleName.c_str());
        return hModule != nullptr;
    }

    bool checkEmulator() {
        auto startTime = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        return duration < 10;
    }

    bool queryRegistryValue(HKEY rootKey, const std::wstring& subKey, const std::wstring& valueName, std::wstring& valueOut) {
        HKEY hKey;
        if (RegOpenKeyExW(rootKey, subKey.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
            return false;
        }

        DWORD dataSize = 0;
        RegQueryValueExW(hKey, valueName.c_str(), NULL, NULL, NULL, &dataSize);

        std::vector<wchar_t> buffer(dataSize / sizeof(wchar_t));
        if (RegQueryValueExW(hKey, valueName.c_str(), NULL, NULL, reinterpret_cast<LPBYTE>(buffer.data()), &dataSize) != ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return false;
        }

        valueOut.assign(buffer.begin(), buffer.end());
        RegCloseKey(hKey);
        return true;
    }

    bool checkVirtualMachine() {
        std::wstring manufacturer;
        if (!queryRegistryValue(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System", L"SystemBiosVersion", manufacturer)) {
            return false;
        }

        std::vector<std::wstring> vmIdentifiers = {
            L"VMware", L"VirtualBox", L"Microsoft", L"Xen", L"KVM", L"QEMU", L"Parallels"
        };

        for (const auto& identifier : vmIdentifiers) {
            if (manufacturer.find(identifier) != std::wstring::npos) {
                return true;
            }
        }
        return false;
    }
};

#endif // SAFE_ZONE_DETECTOR_H
