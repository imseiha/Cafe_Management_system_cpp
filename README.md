# Cafe Management System

This project is a C++ cafe management system for handling menu items, staff members, and sales records.

## Project structure

- `include/` - Header files for the application modules
- `src/` - Source files for implementation
- `data/` - Data files such as menu and staff records
- `docs/` - Project notes and documentation
- `CMakeLists.txt` - Build configuration for CMake

## Build instructions

### With CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
./cafe_management_system
```

### With g++

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/Menu.cpp src/Staff.cpp src/Finance.cpp -o cafe_management_system
./cafe_management_system
```

## Features

- Menu management
- Staff directory
- Sales and finance tracking
- Easy extension for more modules
