

<br>

# 1 Linux Setup Instruction



1. Make sure your in the PROJECT_ROOT
2. Check if the WSL_DEST_LOC exists if not create it
2. Change folder to: PROJECT_ROOT
2. Execute this command after substitute the variables:  
`wsl --import WSL_DEST_NAME  WSL_DEST_LOC\WSL_DEST_NAME\ WSL_EXPORT_FILE`
1. Start the new WSL with this command
`wsl -d WSL_DEST_NAME`
1. In the above started WSL execute: `sudo apt update`


**Use the the build documentation to build the [sample project](building_project)**