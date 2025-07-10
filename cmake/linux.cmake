# =========================================================================================
# Linux definitions.
# =========================================================================================
# In this file one should update the include\library paths and used libraries,used 
# For compiling the Linux version of this library\application
#
# Check and modify the items in 1  and 2.
#
# =========================================================================================

include_guard()


# =========================================================================================
# 1. Configuration Section (Edit This Part)
# =========================================================================================
#
# 1.1 Set options
set(varITERATOR_DEBUG_LEVEL 2)      #
set(EXPLICITE_NAME true)            # Adds a suffix to binary indicating the debug\release and linkage type

# 1.2 Choose a linkage type
#set(LINK_TYPE MT)       # Release multi-threaded STATICAL
#set(LINK_TYPE MD)       # Release multi-threaded DLL
#set(LINK_TYPE MTd)      # Debug multi-threaded STATICAL
set(LINK_TYPE MDd)       # Debug multi-threaded DLL

# 1.3 Set the Windows Libraries used
set(GLFW_LIBS_LOCAL glfw  GL X11 pthread dl m)
set(SKIA_LIBS_LOCAL skia )      # Add other skia libraries when needed


# =========================================================================================
# 2.  Define the folder location (Edit This Part)
# =========================================================================================
#
function(SetLinuxDirectories)    

    # GLFW folder locations (include & Library)
    set(GLFW_LINUX_INCLUDE_DIR "/usr/include/GLFW")
    set(GLFW_LINUX_LIB_DIR "/usr/lib/x86_64-linux-gnu")

    # SKIA folder locations (include & Library)
    #   - Skia internal uses: include/core/xxx.h so we should not add include to include variable
    set(SKIA_LINUX_CORE_INCLUDE_DIR "/root/tools/libs/skia" CACHE PATH "SKIA include dir")
    set(SKIA_LINUX_LIBS_DIR "/root/tools/libs/skia/out/debug/shared" CACHE PATH "SKIA Lib dir")

    # Check if the folders exist
    #   - FATAL_ERROR -> stops program, WARNING -> continues
    set(ERROR_INSTR "\n\t - Fix the error, **clean!** the directory and do a rebuild")
    if(NOT EXISTS "${GLFW_LINUX_INCLUDE_DIR}")
        message(FATAL_ERROR  "\n\n** ERROR **: GLFW include directory not found: ${GLFW_LINUX_INCLUDE_DIR}${ERROR_INSTR}\n")
    endif()
    if(NOT EXISTS "${GLFW_LINUX_LIB_DIR}")
        message(FATAL_ERROR  "\n\n** ERROR **: GLFW library directory not found: ${GLFW_LINUX_LIB_DIR}${ERROR_INSTR}\n")
    endif()

    # Display used Library path folders
    message(STATUS "\t*** Using *** GLFW debug lib folder: ${GLFW_LINUX_LIB_DIR}")
    message(STATUS "\t*** Using *** SKIA debug lib folder ${SKIA_LINUX_LIBS_DIR}\n")
    
endfunction()


function(SetLinuxLibs)
    if(NOT DEFINED GLFW_LIBS_LOCAL)
        message(FATAL_ERROR "GLFW_LIBS_LOCAL is not defined. Please set it in section 1.3.")
    endif()

    if(NOT DEFINED SKIA_LIBS_LOCAL)
        message(FATAL_ERROR "SKIA_LIBS_LOCAL is not defined. Please set it in section 1.3.")
    endif()

    set(GLFW_LIBS "${GLFW_LIBS_LOCAL}" PARENT_SCOPE)
    set(SKIA_LIBS "${SKIA_LIBS_LOCAL}" PARENT_SCOPE)
endfunction()



# IMPLEMENTATION functions
# ===============================================================================================================================
#


# Linux runtime setting function
function(_LinuxRuntimeSettings buildType)
    if("${buildType}" STREQUAL "Debug")
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
        set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
        message(STATUS "\n\t*** Generating: Debug build with debug symbols and no optimizations ***")
    elseif("${buildType}" STREQUAL "Release")
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
        set(CMAKE_CXX_FLAGS_RELEASE "-O3")
        message(STATUS "\n\t*** Generating: Release build with optimizations ***")
    else()
        message(WARNING "Unknown build type: ${buildType}")
    endif()
endfunction()





# Controller, uses the set folders abd libraries
function(LinuxConfigureTarget target)
    SetLinuxDirectories()                # Update Linux specific directories here 
    SetLinuxLibs()                       # Update Linux specific libraries here 

    target_include_directories(${target} PRIVATE ${GLFW_LINUX_INCLUDE_DIR} ${SKIA_LINUX_CORE_INCLUDE_DIR} )
    target_link_directories(${target} PRIVATE ${GLFW_LINUX_LIB_DIR} ${SKIA_LINUX_LIBS_DIR} )    # include and lib folder
    target_link_libraries(${target} PRIVATE ${GLFW_LIBS} ${SKIA_LIBS})                      # Libraries used

    # Determine the real output file name. Then Write name of binary to file, for usage in calling scripts
    get_target_property(REAL_OUTPUT_NAME ${target} OUTPUT_NAME)
    if(NOT REAL_OUTPUT_NAME)
        set(REAL_OUTPUT_NAME ${target})
    endif()
    file(WRITE "${CMAKE_BINARY_DIR}/target_name.txt" "${REAL_OUTPUT_NAME}")
    
endfunction()