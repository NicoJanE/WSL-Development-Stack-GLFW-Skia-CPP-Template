# colors
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RESET='\033[0m'


echo -e "\n\n${GREEN}Run program from: ${RESET} \n\t ${YELLOW} - Make sure XLaunch is started on the host ${RESET}"
echo -e "\n"
echo -e "${GREEN}Running... (control-c to end)${RESET}"
./build-l/glfw_sample
