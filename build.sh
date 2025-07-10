# colors
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RESET='\033[0m'
clear
mkdir -p build-l && cd build-l
cp ../cmake/CMakeLists_start.sh.in ../start.sh
# Run CMake to configure make
cmake ..
# Run make to build the app
make
echo -e "\n\n${GREEN}Done, Result available in this directory:${RESET}"
echo -e "\t$(pwd)"
echo -e "\n${GREEN}Containing:${RESET}"
ls -al
echo -e "\n${GREEN}To start the program use: ${RESET}"
echo -e "\t ./start.sh\n"
echo -e "${YELLOW} - Don't forget to start XLaunche on the host!${RESET}\n"

## To Automatic start the binary!
# cd ..
# ./start.sh
