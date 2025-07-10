# CMake main execution unit
# This CMake file is used to build for Windows and for Linux, a platform specific makefile.
#
# Normally there is no direct need to adjust this file.
# Use the following files to update the include\library paths and used libraries:
#
#   - 'cmake/windows.cmake' to update Windows settings 
#   - 'cmake/linux.cmake' to update Linux settings 
#
# =========================================================================================

include(cmake/windows.cmake)                  # Include the function that defines the Windows specific (paths, libraries)
include(cmake/linux.cmake)                    # Include the function that defines the Windows specific (paths, libraries)
include(cmake/linux_utilities.cmake)


# Generic settings
# =============================================================================================
cmake_minimum_required(VERSION 3.25)
project(glfw_sample LANGUAGES C CXX)         # This will become the output name of the binary
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Mai function called by entrypoint
function(main)   
    add_executable(${PROJECT_NAME} src/main.cpp)
    #add_executable(${PROJECT_NAME} src/main_simple.cpp)
    
    if (WIN32)
        
        # Must be placed before add_executable()
        #_WinRuntimeLib("MultiThreadedDebugDLL" ${varITERATOR_DEBUG_LEVEL})                         # Define binary type
        WinLinkage_Controller()

        # Define the directories and libraries need to create the Windows binary
        # Note target_* should be after add_executables, because 'PROJECT_NAME' is defined there
        WinConfigureTarget(${PROJECT_NAME})
        



    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")                

        # Output system information
        display_system_info()
        display_graphics_info()

        _LinuxRuntimeSettings("Debug")
        LinuxConfigureTarget(${PROJECT_NAME})

    endif()
endfunction()



# ENTRY POINT, call main
main()








