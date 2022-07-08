cmake_minimum_required(VERSION 3.13)

project(UdpSocketSamples
	VERSION 0.1
	LANGUAGES C CXX
)

# Add module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include(EnableWarnings)
# include(FindPkgConfig)

#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
find_package(csnip REQUIRED)
#pkg_check_modules(Libevent REQUIRED IMPORTED_TARGET libevent_pthreads)

# Environment configuration
include(CheckSymbolExists)
#check_symbol_exists(UDP_SEGMENT "netinet/udp.h" HAVE_UDP_SEGMENT)
#check_symbol_exists(UDP_GRO "netinet/udp.h" HAVE_UDP_GRO)

# Targets

add_executable(udp_receiver
	 udp_receiver.c       
)
target_link_libraries(udp_receiver csnip::csnip-static Ws2_32)

add_executable(udp_sender
	udp_sender.c
)
target_link_libraries(udp_sender csnip::csnip-static Ws2_32)

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
