# TactiSim: 2D Tactical Scenario Simulator & Mini C2 System

## 🚀 Overview

TactiSim is a C++ project designed to simulate 2D tactical scenarios. It allows users to place and command various unit types on a map, observe interactions, and manage basic command and control (C2) elements. This project serves as a demonstration of fundamental simulation concepts.

## ✨ Features

*   **2D Map Environment:** A grid-based or continuous 2D map for scenario visualization.
*   **Unit Management:**
    *   Place friendly and enemy units (e.g., Infantry, Tanks).
    *   Distinct unit attributes (health, speed, attack range, etc.).
    *   Visual representation of units.
*   **Command & Control:**
    *   Select individual units.
    *   Issue basic commands:
        *   Move to location.
        *   Attack target unit.
*   **Basic Combat Simulation:**
    *   Units engage enemies within range.
    *   Simple damage and health model.
*   **Scenario Management:**
    *   Save current scenario.
    *   Load scenarios from a file.
*   **User Interface:**
    *   Basic GUI for interaction, scenario controls, and information display.

## 🛠️ Technologies Used

*   **Language:** C++ (targeting C++17 or newer)
*   **IDE:** Microsoft Visual Studio (e.g., 2019, 2022)
*   **Build System:** MSBuild (via Visual Studio Project/Solution)
*   **Graphics/Windowing:** SFML 3.0
*   **Version Control:** Git

## 🏗️ How to Build

**Prerequisites:**

*   **Microsoft Visual Studio:** Version 2022 is recommended, with the "Desktop development with C++" workload installed.
*   **SFML development libraries:** You'll need to configure your Visual Studio project to link against these libraries. Please visit SFML official web-site.

**Build Steps:**

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/TactiSim.git
    cd TactiSim
    ```

2.  **Open the Solution in Visual Studio:**
    *   Locate the Visual Studio Solution file (`.sln`) in the root directory (or a relevant subdirectory if you create one, e.g., `TactiSim.sln`).
    *   Double-click the `.sln` file to open it in Visual Studio.
    *   *(If you haven't created a solution/project yet, you'll need to create a new C++ project in Visual Studio and add your source files to it.)*

3.  **Configure Project Properties (First-time setup for dependencies):**
    *   Right-click on your project in the Solution Explorer (e.g., "TactiSim") and select "Properties".
    *   **C/C++ -> General -> Additional Include Directories:** Add paths to the header files of your external libraries (SFML, etc.).
    *   **Linker -> General -> Additional Library Directories:** Add paths to the `.lib` files of your external libraries.
    *   **Linker -> Input -> Additional Dependencies:** Add the names of the `.lib` files (e.g., `sfml-graphics-d.lib`, `sfml-window-d.lib`, `sfml-system-d.lib` for SFML debug).
    *   Ensure you configure these for both Debug and Release configurations.

4.  **Select Build Configuration:**
    *   In Visual Studio, choose your desired build configuration (e.g., "Debug" or "Release") and platform (e.g., "x64" or "x86").

5.  **Build the Solution:**
    *   From the Visual Studio menu, select `Build > Build Solution` (or press `Ctrl+Shift+B`).

6.  **Run the Executable:**
    *   You can run the project directly from Visual Studio by pressing `F5` (Start Debugging) or `Ctrl+F5` (Start Without Debugging).
    *   Alternatively, the executable (`.exe`) will be located in a subdirectory like `x64/Debug/`, `x64/Release/`, `Win32/Debug/`, or `Win32/Release/` relative to your solution or project directory.

## 🤝 Contribution

Currently, this is a solo project for learning and demonstration purposes. Feedback and suggestions are welcome via GitHub Issues.

## 📜 License

This project is licensed under the MIT License.
