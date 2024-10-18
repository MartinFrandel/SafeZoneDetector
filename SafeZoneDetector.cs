using System;
using System.Collections.Generic;
using System.Diagnostics;
using Microsoft.Win32;
using System.Threading;

namespace SafeZoneDetector
{
    public class Detector
    {
        public Detector() {}

        public bool IsSandboxed()
        {
            return CheckSandbox();
        }

        public bool IsEmulator()
        {
            return CheckEmulator();
        }

        public bool IsVirtualMachine()
        {
            return CheckVirtualMachine();
        }

        public bool IsDebuggerPresentCheck()
        {
            return Debugger.IsAttached;
        }

        public bool IsAnyVirtualEnvironment()
        {
            return IsSandboxed() || IsEmulator() || IsVirtualMachine() || IsDebuggerPresentCheck();
        }

        private bool CheckSandbox()
        {
            var sandboxDlls = new List<string>
            {
                "SbieDll", "SxIn", "Sf2", "snxhk", "cmdvrt32",
                "dbghelp", "api_log", "dir_watch", "pstorec",
                "vmGuestLib", "vmhgfs", "vboxhook", "VboxService",
                "VboxTray", "VmwVmx", "VBoxOGL", "vmwaretray",
                "vmtoolsd", "VBoxSF", "VBoxControl", "Procmon",
                "tcpview", "wireshark", "fiddler"
            };

            foreach (var dll in sandboxDlls)
            {
                if (IsModuleLoaded(dll))
                {
                    Console.WriteLine($"Sandbox DLL detected: {dll}.dll");
                    return true;
                }
            }
            return false;
        }

        private bool IsModuleLoaded(string moduleName)
        {
            foreach (ProcessModule module in Process.GetCurrentProcess().Modules)
            {
                if (module.ModuleName.Equals(moduleName + ".dll", StringComparison.OrdinalIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        private bool CheckEmulator()
        {
            var stopwatch = System.Diagnostics.Stopwatch.StartNew();
            Thread.Sleep(10);
            stopwatch.Stop();
            return stopwatch.ElapsedMilliseconds < 10;
        }

        private bool QueryRegistryValue(RegistryKey rootKey, string subKey, string valueName, out string valueOut)
        {
            valueOut = string.Empty;
            try
            {
                using (var key = rootKey.OpenSubKey(subKey))
                {
                    if (key != null)
                    {
                        valueOut = key.GetValue(valueName)?.ToString();
                        return !string.IsNullOrEmpty(valueOut);
                    }
                }
            }
            catch
            {
                // Handle exceptions as necessary
            }
            return false;
        }

        private bool CheckVirtualMachine()
        {
            string manufacturer;
            if (!QueryRegistryValue(Registry.LocalMachine, @"HARDWARE\DESCRIPTION\System", "SystemBiosVersion", out manufacturer))
            {
                return false;
            }

            var vmIdentifiers = new List<string>
            {
                "VMware", "VirtualBox", "Microsoft", "Xen", "KVM", "QEMU", "Parallels"
            };

            foreach (var identifier in vmIdentifiers)
            {
                if (manufacturer.Contains(identifier, StringComparison.OrdinalIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }
    }
}
