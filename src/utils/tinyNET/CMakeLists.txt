cmake_minimum_required(VERSION 2.8)

set(PRONAME tinyNET)
project(tinyNET)

set(TARGET_ASK tinyASK)
set(TINYASK_DIR ${PROJECT_SOURCE_DIR}/../tinySAK)

set(TINY_SUBDIRS ${PROJECT_SOURCE_DIR} 
	${PROJECT_SOURCE_DIR}/dhcp
	${PROJECT_SOURCE_DIR}/dhcp6 
	${PROJECT_SOURCE_DIR}/dns 
	${PROJECT_SOURCE_DIR}/ice 
	${PROJECT_SOURCE_DIR}/stun 
	${PROJECT_SOURCE_DIR}/turn 
	${PROJECT_SOURCE_DIR}/tls 
)

aux_source_directory(${TINYASK_DIR} TINY_SRC)
include_directories(${TINYASK_DIR})

add_library(${TARGET_ASK} STATIC ${TINY_SRC})
target_link_libraries(${TARGET_ASK} -no-undefined)

foreach(AVR ${TINY_SUBDIRS}) 
	aux_source_directory(${AVR} SRC_LIST)
endforeach(AVR)

include_directories(${PROJECT_SOURCE_DIR} ${TINY_SUBDIRS}) 

#foreach(AVR ${SRC_LIST}) 
#	message("file : ${AVR} ")
#endforeach(AVR)

add_library(${PRONAME} STATIC ${SRC_LIST})
target_link_libraries(${PRONAME} ${TARGET_ASK} -no-undefined)






