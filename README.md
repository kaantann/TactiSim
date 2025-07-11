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

*   **Language:** C++17
*   **IDE:** Microsoft Visual Studio 2022
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
    
2.  **Build the Solution:**
    *   From the Visual Studio menu, select `Build > Build Solution`.

3.  **Run the Executable:**
    *   The executable will be located in a subdirectory like `x64/Debug/`, `x64/Release/`, `Win32/Debug/`, or `Win32/Release/` relative to your solution or project directory.

## 🤝 Contribution

Currently, this is a solo project for learning and demonstration purposes. Feedback and suggestions are welcome via GitHub Issues.

## 📜 License

This project is licensed under the MIT License.
