cmake_minimum_required(VERSION 3.21)
project(eraser LANGUAGES CXX VERSION 1.0.0)

# --------------------------------------------------------------------------------------------------------
# Library options
# --------------------------------------------------------------------------------------------------------

option(eraser_tests "Build tests" ON)

# --------------------------------------------------------------------------------------------------------
# Create library
# --------------------------------------------------------------------------------------------------------

add_library(${PROJECT_NAME} INTERFACE)
add_library(cr::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------------------------------------------------------------
# Include "include" folder
# --------------------------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} INTERFACE "include")

# --------------------------------------------------------------------------------------------------------
# Build Tests
# --------------------------------------------------------------------------------------------------------
    
if (eraser_tests)
  message(STATUS "[eraser] Building Tests")
  add_subdirectory(tests)
endif()

# --------------------------------------------------------------------------------------------------------
# Install Targets
# --------------------------------------------------------------------------------------------------------

install(DIRECTORY "include/" TYPE INCLUDE)
install(TARGETS ${PROJECT_NAME} INCLUDES DESTINATION include)
