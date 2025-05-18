cmake_minimum_required(VERSION 3.10)
project(SWE VERSION 1.0 LANGUAGES CXX)

# ============================ [Build Settings] ============================
set(CMAKE_CXX_STANDARD 11) # Code is currently fully C++11 compliant
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================ [Platform Detection] ============================
# Define CMAKE_VS_PLATFORM_NAME if not already set
if(NOT DEFINED CMAKE_VS_PLATFORM_NAME)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CMAKE_VS_PLATFORM_NAME "x64")
    else()
        set(CMAKE_VS_PLATFORM_NAME "Win32")
    endif()
endif()

# ============================ [Output Directory Setup] ============================
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(NOT IS_MULTI_CONFIG)
    set(OUTPUT_CONFIG_DIR "${CMAKE_VS_PLATFORM_NAME}/${CMAKE_BUILD_TYPE}")
else()
    set(OUTPUT_CONFIG_DIR "${CMAKE_VS_PLATFORM_NAME}")
endif()

# ============================ [Options] ============================
option(SWE_BUILD_TESTS "Build tests" ON)
option(SWE_BUILD_DOCS "Build documentation" ON)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ============================ [Library Target] ============================
add_library(swe STATIC
    "src/swe.cpp"
    "src/string.cpp"
)

set_target_properties(swe PROPERTIES
    OUTPUT_NAME "swe"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dist/lib/${OUTPUT_CONFIG_DIR}"
)

# ============================ [Tests] ============================
if (SWE_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL "https://github.com/google/googletest/archive/refs/heads/main.zip"
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    function(add_swe_test name)
        add_executable(${name} "tests/${name}.cpp")
        set_target_properties(${name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/dist/tests/${OUTPUT_CONFIG_DIR}"
        )
        target_link_libraries(${name} swe gtest_main)
        add_test(NAME ${name} COMMAND ${name})
    endfunction()

    add_swe_test(ci_map_test)
    add_swe_test(concurrent_static_event_test)
    add_swe_test(static_event_test)
    add_swe_test(string_test)
endif()

# ============================ [Documentation] ============================
if(SWE_BUILD_DOCS)
    find_package(Doxygen QUIET)

    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
        set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/dist/docs")
        set(DOXYGEN_CONFIGURED ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.generated)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_CONFIGURED} @ONLY)

        add_custom_target(doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            VERBATIM
        )
    else()
        message(STATUS "Doxygen not found, documentation will not be generated.")
    endif()
endif()

# ============================ [Header Copying] ============================
add_custom_target(copy_headers ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_BINARY_DIR}/dist/include"
)