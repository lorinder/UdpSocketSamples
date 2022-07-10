cmake_minimum_required(VERSION 3.13)

project(UdpSocketSamples
	VERSION 0.1
	LANGUAGES C CXX
)

# Enable compiler warnings
if (CMAKE_C_COMPILER_ID MATCHES GNU OR CMAKE_C_COMPILER_ID MATCHES CLANG)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES GNU OR
  CMAKE_CXX_COMPILER_ID MATCHES CLANG)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif ()

# Targets

add_executable(recv
	 recv.c       
)
if (WIN32)
	target_link_libraries(recv Ws2_32)
endif ()

add_executable(sender
	sender.c
)
if (WIN32)
	target_link_libraries(sender Ws2_32)
endif ()

# Subdirectories

#add_subdirectory(...)

# Testing

enable_testing()

# Packaging

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
#set(CPACK_PACKAGE_VENDOR "lminder@gmx.net")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
if(NOT DEFINED CPACK_SYSTEM_NAME)
	set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
endif()
set(CPACK_SOURCE_IGNORE_FILES ${PROJECT_BINARY_DIR} .git .gitignore)
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_GENERATOR "TGZ")

include(CPack)
