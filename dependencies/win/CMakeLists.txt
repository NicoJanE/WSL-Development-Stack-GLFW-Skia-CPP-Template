## Empty placeholder to avoid VS picking up everything as a startup target
if(WIN32)
	add_subdirectory(glfw-3.4 EXCLUDE_FROM_ALL)
#	add_subdirectory(skia EXCLUDE_FROM_ALL)
endif()