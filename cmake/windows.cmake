# =========================================================================================
# Windows definitions.
# =========================================================================================
# In this file one should update the include\library paths and used libraries,used 
# For compiling the Windows version of this library\application
#
# Check and modify the items in 1  and 2.
#
# =========================================================================================


# Prevent Visual Studio 2022 from loading all targets in this subdirectory as startup/debuggable projects.
# This avoids cluttering the "Startup Item" list in the IDE.
# Unfortunately, this behavior cannot be controlled via CMakePresets.json — it must be done here in CMakeLists.txt.
# Update the path 'depw' as needed. and make SURE the exclude folder contains a dummy CMakeList.txt file
# otherwise the manual build fails (./build.ps1, which is also used by VSC)
if(WIN32)    
    add_subdirectory(dependencies/win EXCLUDE_FROM_ALL)
endif()

include_guard()

# CONFIGURATION functions
# ===============================================================================================================================
#

# -----------------------------------------------------------------------------------------
# 1. Configuration Section (Edit This Part)
# -----------------------------------------------------------------------------------------
#
# 1.1 Set options
set(varITERATOR_DEBUG_LEVEL 2)      #
set(EXPLICITE_NAME true)            # Adds a suffix to binary indicating the debug\release and linkage type

# 1.2 Choose a linkage typ, *** you likely need to update 2 as well!
#set(LINK_TYPE MT)       # Release multi-threaded STATICAL
#set(LINK_TYPE MD)       # Release multi-threaded DLL
#set(LINK_TYPE MTd)      # Debug multi-threaded STATICAL
set(LINK_TYPE MDd)       # Debug multi-threaded DLL

# 1.3 Set the Windows Libraries used
set(GLFW_LIBS_WIN_LOCAL glfw3dll opengl32)         # glfw3 -> static   glfw3dll -> Dynamic(importlib)
set(SKIA_LIBS_WIN_LOCAL skia)

# 1.4 Specific build options for OS/Compiler
function(_SetBuildProperties)
    add_definitions(-DUNICODE -D_UNICODE)                                                   # For Unicode build 
    #set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")      # Specific for Win apps. Expect:WinMain instead of int main()

endfunction()

# -----------------------------------------------------------------------------------------
# 2.  Define the folder location (Edit This Part)
# -----------------------------------------------------------------------------------------
#
function(_SetExtraWindowsFolders)    

    # GLFW folder locations (include & Library)
    set(GLFW_WIN_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/depw/glfw/include" CACHE PATH "GLFW include dir")
    #set(GLFW_WIN_LIB_DIR "${PROJECT_SOURCE_DIR}/depw/glfw/outstatic/src/debug"  CACHE PATH "GLFW lib dir")  # *** Update when 'LINK_TYPE' changes ***    
     set(GLFW_WIN_LIB_DIR "${PROJECT_SOURCE_DIR}/depw/glfw/outdll/src/debug"  CACHE PATH "GLFW lib dir")  # *** Update when 'LINK_TYPE' changes ***    
    _CheckFolderExists("${GLFW_WIN_INCLUDE_DIR}" "GLFW include directory")
    _CheckFolderExists("${GLFW_WIN_LIB_DIR}" "GLFW library directory")

    # SKIA folder locations (include & Library)
    #   - Skia internal uses: include/core/xxx.h so we should not add include to include variable
    set(SKIA_WIN_CORE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/depw/skia" CACHE PATH "SKIA include dir")
    set(SKIA_WIN_LIBS_DIR "${PROJECT_SOURCE_DIR}/depw/skia/out/Debug" CACHE PATH "SKIA Lib dir")            # *** Update when 'LINK_TYPE' changes ***
    _CheckFolderExists("${SKIA_WIN_CORE_INCLUDE_DIR}" "SKIA include directory")
    _CheckFolderExists("${SKIA_WIN_LIBS_DIR}" "SKIA library directory")
    message(STATUS "\n")

    
endfunction()


# END CONFIGURATION functions
# ===============================================================================================================================


# IMPLEMENTATION functions
# ===============================================================================================================================
#

# Set the lib ,uses vars defined in 1.3:
function(_SetWindowsLibs)
    if(NOT DEFINED GLFW_LIBS_WIN_LOCAL)
        message(FATAL_ERROR "GLFW_LIBS_WIN_LOCAL is not defined. Please set it in section 1.3.")
    endif()

    if(NOT DEFINED SKIA_LIBS_WIN_LOCAL)
        message(FATAL_ERROR "SKIA_LIBS_WIN_LOCAL is not defined. Please set it in section 1.3.")
    endif()

    set(GLFW_LIBS "${GLFW_LIBS_WIN_LOCAL}" PARENT_SCOPE)
    set(SKIA_LIBS "${SKIA_LIBS_WIN_LOCAL}" PARENT_SCOPE)
endfunction()

# Define binary linking type and debug setting
function(_WinRuntimeLib varRuntime varITERATOR_DEBUG_LEVEL )

    # Info.
    # set(CMAKE_MSVC_RUNTIME_LIBRARY ${varRuntime})  # alternative, but is global and must be called before: add_executable())

    set_target_properties(${PROJECT_NAME} PROPERTIES  MSVC_RUNTIME_LIBRARY ${varRuntime} )    
    add_compile_definitions(_ITERATOR_DEBUG_LEVEL=${varITERATOR_DEBUG_LEVEL} )
    message(STATUS "\n\t*** Generating *** '${varRuntime}' ${CMAKE_BUILD_TYPE} code!\n")
    
endfunction()


function(_WinLinkage_MDd )
    set(CMAKE_BUILD_TYPE Debug)
    _WinRuntimeLib("MultiThreadedDebugDLL" ${varITERATOR_DEBUG_LEVEL})                      # Multi-Threaded Debug DLL (-MDd)
    # Debug files please
    set(MSVC_DEBUG_COMPILE_OPTIONS /Zi /Od /MDd CACHE STRING "" FORCE)
    set(MSVC_DEBUG_LINK_OPTIONS /DEBUG CACHE STRING "" FORCE)
    
endfunction()

function(_WinLinkage_MTd )
    _WinRuntimeLib("MultiThreadedDebug" ${varITERATOR_DEBUG_LEVEL})                         # Multi-Threaded Debug Static -(MTd)
    # Debug files please
    set(MSVC_DEBUG_COMPILE_OPTIONS /Zi /Od /MDd CACHE STRING "" FORCE)
    set(MSVC_DEBUG_LINK_OPTIONS /DEBUG CACHE STRING "" FORCE)

endfunction()

function(_WinLinkage_MT )
    set(varITERATOR_DEBUG_LEVEL 0)                                                          # Override
    _WinRuntimeLib("MultiThreaded" ${varITERATOR_DEBUG_LEVEL})                              # Multi-Threaded Release StaticL (-MT)
    
endfunction()

function(_WinLinkage_MD )
    set(varITERATOR_DEBUG_LEVEL 0)                                                          # Override    
    _WinRuntimeLib("MultiThreadedDLL" ${varITERATOR_DEBUG_LEVEL})                           # Multi-Threaded Debug DLL (-MD)
   
endfunction()

# Function to check if a folder exists and show a fatal error if not
function(_CheckFolderExists folder_path folder_description)
    set(ERROR_INSTR "\t - Fix the error, **clean!** the directory and do a rebuild")
    if(NOT EXISTS "${folder_path}")
        message(FATAL_ERROR  "\n*** ERROR ***:\t-->  ${folder_description} not found: ${folder_path}${ERROR_INSTR}\n")
    else()
        # Display used Library path folders when using it
        message(STATUS "\tUsing: '${folder_description}' ${folder_path}")
    endif()
    
endfunction()

# END IMPLEMENTATION functions
# ===============================================================================================================================


# CALLED BY MAIN CMAKE
# ===============================================================================================================================

# Controls based on the LINK_TYPE variable which linkage function must be used to set the app/lib linkage abd debug settings
function(WinLinkage_Controller)
    if (LINK_TYPE STREQUAL "MDd")
        set(OUTPUT_SUFFIX "_md_dbg")
        _WinLinkage_MDd() 
    elseif(LINK_TYPE STREQUAL "MTd")
        set(OUTPUT_SUFFIX "_mt_dbg")
        _WinLinkage_MTd()
    elseif(LINK_TYPE STREQUAL "MD")
        set(OUTPUT_SUFFIX "_md")
        _WinLinkage_MD()
    elseif(LINK_TYPE STREQUAL "MT")
        set(OUTPUT_SUFFIX "_mt")
        _WinLinkage_MT()
    elseif()
        message(FATAL_ERROR  "\n\n** ERROR **: WinLinkage_Controller() wrong linkage property: ${LINK_TYPE} \n")
    endif()



    # Set binary file name suffix without changing target name
    if(EXPLICITE_NAME STREQUAL "true")
        set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}${OUTPUT_SUFFIX}")
    endif()
endfunction()


# Controller, uses the set folders abd libraries
function(WinConfigureTarget target)
    _SetExtraWindowsFolders()              # Update Win specific folders here (CMakeLists_WIN_definitions.txt)
    _SetBuildProperties()
    _SetWindowsLibs()                      # Update Win specific libraries here CMakeLists_WIN_definitions.txt

    target_include_directories(${target} PRIVATE ${GLFW_WIN_INCLUDE_DIR} ${SKIA_WIN_CORE_INCLUDE_DIR} )
    target_link_directories(${target} PRIVATE ${GLFW_WIN_LIB_DIR} ${SKIA_WIN_LIBS_DIR} )    # include and lib folder
    target_link_libraries(${target} PRIVATE ${GLFW_LIBS} ${SKIA_LIBS})                      # Libraries used
    
    target_compile_options(${target} PRIVATE ${MSVC_DEBUG_COMPILE_OPTIONS})
    target_link_options(${target} PRIVATE ${MSVC_DEBUG_LINK_OPTIONS})

    # Determine the real output file name. Then Write name of binary to file, for usage in calling scripts
    get_target_property(REAL_OUTPUT_NAME ${target} OUTPUT_NAME)
    if(NOT REAL_OUTPUT_NAME)
        set(REAL_OUTPUT_NAME ${target})
    endif()
    file(WRITE "${CMAKE_BINARY_DIR}/target_name.txt" "${REAL_OUTPUT_NAME}")
    
endfunction()