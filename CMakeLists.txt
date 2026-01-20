# Define the minimum version
cmake_minimum_required(VERSION 3.21)

# 1. Project Definition
Project(FileEncrypterGUI
        VERSION 0.1
        LANGUAGES CXX)

# Enforcing a modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Required for Qt's "Magic" (MOC, UIC, RCC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORRC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.1/msvc2022_64")

# 2. Integrate external libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(unofficial-sodium_DIR "C:/Users/Usera/vcpkg/installed/x64-windows-static-md/share/unofficial-sodium")
find_package(unofficial-sodium CONFIG REQUIRED)

set(CMAKE_AUTOMOC_RELAXED_MODE ON)
include_directories(include)

# 3. Executable Definitions
# Source files go here
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/mainwindow.cpp
    src/CryptoEngine.cpp
    src/FileManager.cpp
    src/KeyDeriver.cpp
    src/DropZone.cpp
    src/EncryptionWorker.cpp
    
    include/mainwindow.h
    include/AlgoEnum.h
    include/CryptoEngine.h
    include/FileManager.h
    include/KeyDeriver.h
    include/DropZone.h
    include/EncryptionWorker.h
    src/mainwindow.ui
)


# 5. Include Directories
target_include_directories(${PROJECT_NAME}
PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_autogen/include
)    

# 6. Link Libraries 
target_link_libraries(${PROJECT_NAME}
PRIVATE 
    Qt6::Widgets
    unofficial-sodium::sodium
)

# 4. Compiler Warning Flags
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()