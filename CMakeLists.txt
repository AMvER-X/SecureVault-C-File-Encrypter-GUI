# Define the minimum version
cmake_minimum_required(VERSION 3.10)

# 1. Project Definition
Project(FileEncrypterGUI
        VERSION 0.1
        LANGUAGES CXX)

# Enforcing a modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Point CMake to Qt installation
set(CMAKE_PREFIX_PATH 
"C:/Qt/6.10.1/mingw_64"
"C:\Users\Usera\vcpkg\installed\x64-mingw-dynamic"
)

# Required for Qt's "Magic" (MOC, UIC, RCC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORRC ON)

# 2. Integrate external libraries
find_package(unofficial-sodium CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 3. Executable Definitions
# Source files go here
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/mainwindow.cpp
    src/CryptoEngine.cpp
    src/FileManager.cpp
    src/KeyDeriver.cpp
    ui/mainwindow.ui
)

# 4. Compiler Warning Flags
if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # String warning for GCC and Clang
    add_compile_options(-Wall -Wextra -pedantic) 
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # Strict warings for Visual Studio
    add_compile_options(/W4)
endif()

# 5. Include Directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)    

# 6. Link Libraries 
target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        Qt6::Widgets
        unofficial-sodium::sodium
)
