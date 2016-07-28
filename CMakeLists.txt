#CMake 最低版本号
cmake_minimum_required(VERSION 2.8)

set(PRONAME ntian_sdk)
set(SDK_VERSION_MAJOR 1.0)
set(SDK_VERSION_MINOR 0)

project(${PRONAME})

set(target_name ${PRONAME})
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)

set(TINYASK_DIR ${PROJECT_SOURCE_DIR}/src/utils/tinySAK)
set(TINYNET_DIR ${PROJECT_SOURCE_DIR}/src/utils/tinyNET)

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

if(${ANDROID} MATCHES "True") 
	message("HOST: ${CMAKE_SYSTEM_NAME}")
	message("Target : Android")

else()
	message("HOST: ${CMAKE_SYSTEM_NAME}")
	if(WIN32)
		add_definitions(-DWIN32)	
	endif(WIN32)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

link_directories(${LIBRARY_OUTPUT_PATH})

#加入一个配置头文件 用于处理 CMake 对源码的设置
configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_SOURCE_DIR}/include/config.h"
	)

#头文件目录
include_directories(src/mavlink include ${TINYASK_DIR} ${TINYNET_DIR})
aux_source_directory(${TINYASK_DIR} TINYASK_SRCS )

foreach(AVR ${TINYNET_SUBDIRS}) 
	aux_source_directory(${AVR} TINYNET_SRCS)
endforeach(AVR)

#设置源文件
set(source_files src/api/ntian_sdk_api.c
	src/utils/list/list.c
	src/utils/timer/timer.c
	src/api/ntian_sdk_connect.c
	src/utils/tcp/tcp.c
	src/utils/udp/udp.c
	)

set(timer_test src/test/test_timer.c)
set(thread_test src/test/test.c)
set(net_test src/test/test_udp.c)

add_subdirectory( src/utils/openssl )
include_directories(src/utils/openssl/include)
get_property(SSL_LIB GLOBAL PROPERTY "SSL_LIB")

add_definitions(-DUSE_POLL=1 -DHAVE_OPENSSL -DOPENSSL_NO_ASM)
if(${ANDROID} MATCHES "True") 

	message("MAKE ANDROID")
	set(source_files ${source_files} src/jni_interface/NtianSdk.c)
	add_library(${LIB_TINYSAK} STATIC ${TINYASK_SRCS})
	#	target_link_libraries(${LIB_TINYSAK} -no-undefined)

	add_library(${LIB_TINYNET} STATIC ${TINYNET_SRCS})
	target_link_libraries(${LIB_TINYNET} ${LIB_TINYSAK} ${SSL_LIB})

	add_library(${target_name} SHARED ${source_files})
	target_link_libraries(${target_name} ${LIB_TINYSAK} ${LIB_TINYNET} -pthread -llog)

else()
	message("MAKE OTHER SSL : ${SSL_LIB}")
	add_library(${LIB_TINYSAK} SHARED ${TINYASK_SRCS})
	target_link_libraries(${LIB_TINYSAK}  ${SSL_LIB} -ldl -pthread -Wall)

	add_library(${LIB_TINYNET} SHARED ${TINYNET_SRCS})
	target_link_libraries(${LIB_TINYNET} ${LIB_TINYSAK} -pthread -Wall)

	add_library(${target_name} SHARED ${source_files})
	target_link_libraries(${target_name} ${LIB_TINYSAK} ${LIB_TINYNET} -pthread -ldl)

endif()

add_executable(timer_test ${timer_test})
target_link_libraries(timer_test  ${LIB_TINYSAK} ${LIB_TINYNET} ${target_name} -ldl)

add_executable(thread_test ${thread_test})
target_link_libraries(thread_test ${LIB_TINYSAK} ${LIB_TINYNET} ${target_name} -ldl)

add_executable(net_test ${net_test})
target_link_libraries(net_test ${LIB_TINYSAK} ${LIB_TINYNET} ${target_name} -ldl)




