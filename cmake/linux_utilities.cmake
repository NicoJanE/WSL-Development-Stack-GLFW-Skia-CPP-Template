# display_graphics_info()
# ------------------------
# Shows basic GPU/display info before CMake configuration.
#
# - Detects session type: X11 or Wayland.
# - For X11: runs `glxinfo` to show OpenGL version, vendor, and rendering status.
# - For Wayland: runs `vulkaninfo` to show Vulkan API version, device name, and vendor.
#
# Useful for diagnosing graphics setup issues early.
# Requires: `bash`, `glxinfo` (X11), `vulkaninfo` (Wayland).
# Gracefully falls back if commands fail.

function(display_graphics_info)

    execute_process(COMMAND bash -c "printenv | sort"
                OUTPUT_VARIABLE all_env
                OUTPUT_STRIP_TRAILING_WHITESPACE)
    file(WRITE "${CMAKE_BINARY_DIR}/env_dump.txt" "${all_env}")


    # Detect which display server is in use
    execute_process(     COMMAND printenv XDG_SESSION_TYPE
                        OUTPUT_VARIABLE session_type
                        OUTPUT_STRIP_TRAILING_WHITESPACE )
    execute_process(     COMMAND printenv WAYLAND_DISPLAY
                        OUTPUT_VARIABLE session_type_wsl
                        OUTPUT_STRIP_TRAILING_WHITESPACE )                    

    # Defensive cleanup
    string(STRIP "${session_type}" session_type)
    string(STRIP "${session_type_wsl}" session_type_wsl)

    # Fallback detection logic
    if("${session_type}" STREQUAL "" AND NOT "${session_type_wsl}" MATCHES  "^wayland")
        message(WARNING "Could not detect session type, assuming X11")
        set(session_type "x11")
    endif()


    # For X11 session based Linux Systems
    if(session_type STREQUAL "x11")
        
        execute_process( COMMAND bash -c "glxinfo | grep 'OpenGL version' || echo 'OpenGL version: Not found'"
                         OUTPUT_VARIABLE opengl_version OUTPUT_STRIP_TRAILING_WHITESPACE )
        execute_process( COMMAND bash -c "glxinfo | grep 'direct rendering' || echo 'Direct rendering: Not found'"
                         OUTPUT_VARIABLE opengl_direct OUTPUT_STRIP_TRAILING_WHITESPACE )
        execute_process( COMMAND bash -c "glxinfo | grep 'OpenGL vendor string' || echo 'OpenGL vendor string: Not found'"
                         OUTPUT_VARIABLE opengl_vendor OUTPUT_STRIP_TRAILING_WHITESPACE )

        message(STATUS "\tUSING:${session_type}")
        message(STATUS "\tOpenGL Version: ${opengl_version}")
        message(STATUS "\t${opengl_vendor}")
        message(STATUS "\t${opengl_direct}")
        

        
    # For Wayland session based Linux Systems (WSLg)
    elseif("${session_type}" STREQUAL "wayland" OR "${session_type_wsl}" MATCHES "^wayland")            
        execute_process( COMMAND bash -c "vulkaninfo | grep 'apiVersion' || echo 'apiVersion: Not found'"
                         OUTPUT_VARIABLE vulkan_api OUTPUT_STRIP_TRAILING_WHITESPACE )
        execute_process( COMMAND bash -c "vulkaninfo | grep 'deviceName' | head -n 1 || echo 'deviceName: Not found'"
                         OUTPUT_VARIABLE vulkan_device OUTPUT_STRIP_TRAILING_WHITESPACE )
        execute_process( COMMAND bash -c "vulkaninfo | grep 'vendorID' | head -n 1 || echo 'vendorID: Not found'"
                         OUTPUT_VARIABLE vulkan_vendor OUTPUT_STRIP_TRAILING_WHITESPACE )

        message(STATUS "\tUSING:${session_type} ${session_type_wsl}")
        message(STATUS "\tVulkan API Version: ${vulkan_api}")
        message(STATUS "\tVulkan Device Name: ${vulkan_device}")
        message(STATUS "\tVulkan Vendor ID: ${vulkan_vendor}")


    # We are clueless regarding this sessions 
    else()
        message(STATUS "\tWARNING: while running 'display_graphics_info()'")
        message(WARNING "Unknown or unsupported session type: '${session_type}'")
    endif()
endfunction()


# display_system_info()
# --------------------
# Prints basic system info: OS name, kernel version, and architecture.
# Useful for context during CMake configuration.

function(display_system_info)
    execute_process( COMMAND uname -s
                     OUTPUT_VARIABLE sys_name
                     OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process( COMMAND uname -r
                     OUTPUT_VARIABLE sys_release
                     OUTPUT_STRIP_TRAILING_WHITESPACE)
    execute_process( COMMAND uname -m
                     OUTPUT_VARIABLE sys_arch
                     OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process( COMMAND bash -c "grep -m 1 'model name' /proc/cpuinfo | cut -d ':' -f2-"
                     OUTPUT_VARIABLE cpu_name OUTPUT_STRIP_TRAILING_WHITESPACE)

    message(STATUS "\tCPU INFO\t:${cpu_name}" )
    message(STATUS "\tSYSTEM INFO\t: ${sys_name} ${sys_release} (${sys_arch})\n")
endfunction()
