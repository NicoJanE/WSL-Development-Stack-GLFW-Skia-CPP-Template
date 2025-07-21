

<br>

<!-- copilot-ignore-start -->
<small>***Note*** *instructions for AI Agent VSC for manual instruction [Linux go here](https://nicojane.github.io/WSL-Development-Stack-GLFW-Skia-CPP-Template/Howtos/setup_linux)*
</small>
<!-- copilot-ignore-end -->


# 1 Linux Setup Instruction

1. Make sure your in the PROJECT_ROOT
2. Check if the WSL_DEST_LOC exists if not create it
2. Change folder to: PROJECT_ROOT
2. Execute this command after substitute the variables:  
`wsl --import WSL_DEST_NAME  WSL_DEST_LOC\WSL_DEST_NAME\ WSL_EXPORT_FILE`
1. When possible combine all WSL command into one script and execute that, but first check if the script is okay.
1. in the WSL run this command
`sudo apt update`
1. in the WSL run this command
`sudo apt upgrade`
1. in the WSL run this these commands  
`sudo adduser --gecos "" --disabled-password nico`  
`echo "nico:nico" | sudo chpasswd`  
`usermod -aG sudo nico`
1. in the WSL run this these commands  
`sudo apt update`  
`sudo apt install cmake g++ libglfw3-dev libgl1-mesa-dev   libx11-dev gdb libxkbcommon-dev libxinerama-dev libxcursor-dev libxi-dev`
1. In the WSL run this command to find include folder for glfw
`dpkg -L libglfw3-dev | grep '\.h$'`
1. Use the above found location to update the variable 'GLFW_LINUX_INCLUDE_DIR' in the  file 'linux.cmake' which can be found in the PROJECT_ROOT/cmake/ folder
1. In the WSL run this command to find include folder for glfw
`dpkg -L libglfw3-dev | grep '\.so'`
1. Use the above found location to update the variable 'GLFW_LINUX_LIB_DIR' in the  file 'linux.cmake' which can be found in the PROJECT_ROOT/cmake/ folder
1. in the WSL run this these commands  
`sudo apt update`  
`sudo apt install build-essential git python3 pkg-config libglu1-mesa-dev libgl1-mesa-dev ninja-build libfontconfig1-dev libexpat1-dev libfreetype6-dev libpng-dev libjpeg-dev libharfbuzz-dev libwebp-dev mesa-utils vulkan-tools`
1. In the WSL make a directory in for the user home directory, in the WSL run this these commands  
`/home/nico/tools/libs`
`cd /home/nico/tools/libs`
1. Next we Install the library depot_tools. In the WSL run this these commands  
`git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git`  
` echo 'export PATH="$HOME/tools/libs/depot_tools:$PATH"' >> ~/.bashrc`  
`source ~/.bashrc`
1. In the WSL make a directory in for the user home directory, in the WSL run this these commands  
`cd /home/nico/tools/libs`  
`git clone https://skia.googlesource.com/skia.git`  
`cd /home/nico/tools/libs/skia`  
`git checkout chrome/m126`
1. Sync dependencies for Skia, in the WSL run this these command:  
`python3 tools/git-sync-deps`  
1. check if `gn` is installed, in the WSL run this these command:  
`which gn  `
1. Configure Skia to create Shared Debug build. In the WSL run this these commands  (preferred)
`./bin/gn gen out/debug/shared --args='is_debug=true is_official_build=false is_component_build=true skia_use_gl=true' `  
`ninja -C out/debug/shared`  
1. Configure Skia to create Shared Release build. In the WSL run this these commands  
`./bin/gn gen out/release/shared --args='is_debug=false is_official_build=true is_component_build=true skia_use_gl=true' `  
`ninja -C out/release/shared`  
1. Configure Skia to create static Release build. Ask the user if he wants this.IF yes the  In the WSL run this these commands  
`./bin/gn gen out/release/static --args='is_official_build=true is_component_build=false is_debug=false skia_use_gl=true' `  
`ninja -C out/release/static`  
1. Configure Skia to create static Debug build. Ask the user if he wants this.IF yes the  In the WSL run this these commands  
`./bin/gn gen out/debug/static --args='is_debug=true is_official_build=false is_component_build=false skia_use_gl=true' `  
`ninja -C out/debug/static`
1. Indicate to the user that the `cmake.linux` file will be update for the 'Shared Debug build'
1. update the variable 'SKIA_LINUX_CORE_INCLUDE_DIR' in the  file 'linux.cmake' which can be found in the PROJECT_ROOT/cmake/ folder with the skia include folder
1. update the variable 'SKIA_LINUX_LIBS_DIR' in the  file 'linux.cmake' which can be found in the PROJECT_ROOT/cmake/ folder. with the skia library folder of the Shared Debug build.
1. Check the variable 'SKIA_LIBS_LOCAL' in the  file 'linux.cmake' which can be found in the PROJECT_ROOT/cmake/ folder. this should already be okay.
1. check yourself that you did not skip a step, if you skipped a step, try to fix/ run that step now
1. **Use the the build documentation to build the [sample project for linux](building_project)**