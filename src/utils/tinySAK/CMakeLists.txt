cmake_minimum_required(VERSION 2.8)

set(PRONAME tinyASK)
project(tinyASK)

include_directories(${PROJECT_SOURCE_DIR}) 
aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)

add_library(${PRONAME} STATIC ${SRC_LIST})
target_link_libraries(${PRONAME} -no-undefined)






