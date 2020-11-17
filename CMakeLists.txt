cmake_minimum_required(VERSION 3.0)
project(cx_containers VERSION 0.1
        DESCRIPTION "A C++14 constexpr implementation of various containers"
        LANGUAGES CXX)

# TODO Find a way to specify these global properties to just the target
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -------- library --------
add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# -------- install --------
include(GNUInstallDirs)
if("${CMAKE_VERSION}" VERSION_GREATER "3.14.0")
    # TODO Find a way to copy over cx subfolder instead of manually specifying it
    file(GLOB_RECURSE INCLUDE_FILES "include/*")
    set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${INCLUDE_FILES}")
    install(TARGETS ${PROJECT_NAME}
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cx)
else()
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()

# -------- gtest --------
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

enable_testing()
add_executable(test_string tests/test_string.cpp)
target_link_libraries(test_string gtest_main ${PROJECT_NAME}::${PROJECT_NAME})
add_test(NAME test_string COMMAND test_string)

add_executable(test_pair tests/test_pair.cpp)
target_link_libraries(test_pair gtest_main ${PROJECT_NAME}::${PROJECT_NAME})
add_test(NAME test_pair COMMAND test_pair)

add_executable(test_map tests/test_map.cpp)
target_link_libraries(test_map gtest_main ${PROJECT_NAME}::${PROJECT_NAME})
add_test(NAME test_map COMMAND test_map)

add_executable(test_array tests/test_array.cpp)
target_link_libraries(test_array gtest_main ${PROJECT_NAME}::${PROJECT_NAME})
add_test(NAME test_array COMMAND test_array)
