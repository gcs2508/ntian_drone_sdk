#CMake 最低版本号
cmake_minimum_required(VERSION 2.8)

set(PRONAME ntian_sdk)
set(SDK_VERSION_MAJOR 1.0)
set(SDK_VERSION_MINOR 0)

project(${PRONAME})

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(TINYASK_DIR ${PROJECT_SOURCE_DIR}/src/uitls/tinySAK)
set(TINYNET_DIR ${PROJECT_SOURCE_DIR}/src/uitls/tingNET)

set(TINYNET_SUBDIRS ${TINYNET_DIR}
	${TINYNET_DIR}/dhcp
	${TINYNET_DIR}/dhcp6
	${TINYNET_DIR}/dns
	${TINYNET_DIR}/ice
	${TINYNET_DIR}/stun
	${TINYNET_DIR}/turn
	${TINYNET_DIR}/tls
	)

set(LIB_TINYSAK tinySAK)
set(LIB_TINYNET tinyNET)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
if(${ANDROID} matches "True") 
	message("HOST: ${CMAKE_SYSTEM_NAME}")
	message("Target : Android")
else()
	message("HOST: ${CMAKE_SYSTEM_NAME}")
endif()

#加入一个配置头文件 用于处理 CMake 对源码的设置
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_SOURCE_DIR}/include/config.h"
	)


#头文件目录
include_directories(src/mavlink include ${TINYASK_DIR} ${TINYNET_DIR})
aux_source_directory(TINYASK_SRCS ${TINYASK_DIR})

foreach(AVR ${TINYNET_SUBDIRS}) 
	aux_source_directory(${AVR} TINYNET_SRCS)
endforeach(AVR)


#设置源文件
if(${ANDROID} matches "True") 

	add_library(${LIB_TINYSAK} STATIC ${TINYASK_SRCS})
	target_link_libraries(${LIB_TINYSAK} -no-undefined)

	add_library(${LIB_TINYNET} STATIC ${TINYNET_SRCS})
	target_link_libraries(${LIB_TINYNET} ${LIB_TINYSAK} -no-undefined)

	add_library(${target_name} SHARED ${source_files})
	target_link_libraries(${target_name} ${LIB_TINYSAK} ${LIB_TINYNET} -pthread -llog)

else()

	add_library(${LIB_TINYSAK} SHARED ${TINYASK_SRCS})
	target_link_libraries(${LIB_TINYSAK} -no-undefined)

	add_library(${LIB_TINYNET} SHARED ${TINYNET_SRCS})
	target_link_libraries(${LIB_TINYNET} ${LIB_TINYSAK} -no-undefined)

	add_library(${target_name} SHARED ${source_files})
	target_link_libraries(${target_name} ${LIB_TINYSAK} ${LIB_TINYNET} -pthread)
endif()

#set(test_thread_files )





