

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
1. SKIA TOD



**Use the the build documentation to build the [sample project](building_project)**