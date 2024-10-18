# SafeZoneDetector

The `SafeZoneDetector` library is designed to detect whether the current environment is a sandbox, emulator, debugger or virtual machine. This functionality is useful for security applications that require assurance that software is running in a trusted environment.

## Features

- Detects if the environment is a sandbox.
  
  ![VirtualEnv](./.img/AvastSanbox.png)
- Detects if the environment is an emulator.
- Detects if a debugger is present.
  
  ![VirtualEnv](./.img/Debugger.png)
- Detects if the environment is a virtual machine.
  
  ![VirtualEnv](./.img/VMWare.png)
- Provides a unified method to check for any virtual environment.

  ![VirtualEnv](./.img/CleanEnvironment.png)

## Usage

### 1. Create a New Project

Create a new C# console application using the .NET CLI:

```bash
dotnet new console -n SafeZoneDetectorDemo
cd SafeZoneDetectorDemo
```

### 2. Add the Detector Class

Copy a file named SafeZoneDetector.cs in your project directory and paste the SafeZoneDetector class code into it.


### 3. Use the library

Utilize the library methods to check for emulators, sandboxes, debuggers or virtual machines.

```cs
using System;

namespace SafeZoneDetectorDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            var detector = new SafeZoneDetector.Detector();

            if (detector.IsAnyVirtualEnvironment())
            {
                Console.WriteLine("Virtual environment detected!");
            }
            else
            {
                Console.WriteLine("No virtual environment detected.");
            }
        }
    }
}


// Check for any virtual environment
if (detector.isAnyVirtualEnvironment()) {
    std::cout << "Virtual environment detected!" << std::endl;
} else {
    std::cout << "No virtual environment detected." << std::endl;
}

// Check for a sandboxed environment
if (detector.isSandboxed()) {
    std::cout << "Sandboxed environment detected!" << std::endl;
} else {
    std::cout << "No Sandboxed environment detected." << std::endl;
}

// Check for an emulator
if (detector.isEmulator()) {
    std::cout << "Emulator environment detected!" << std::endl;
} else {
    std::cout << "No Emulator environment detected." << std::endl;
}

// Check for a debugger
if (detector.isDebuggerPresentCheck()) {
    std::cout << "Debugger environment detected!" << std::endl;
} else {
    std::cout << "No debugger environment detected." << std::endl;
}

// Check for virtual machine presence
if (detector.isVirtualMachine()) {
    std::cout << "Virtual Machine environment detected!" << std::endl;
} else {
    std::cout << "No Virtual Machine environment detected." << std::endl;
}
```

### 4. Compile the binary

Compile the binary with dotnet:
```bash
dotnet build

# and run
dotnet run
# or locate binary in ./bin/... folder
```


### (optional) Strip the symbols and selections
Remove all symbol and relocation information to reduce the binary size and make it harder to analyze:

```bash
dotnet publish -c Release -o ./publish
```
