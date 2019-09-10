cmake_minimum_required(VERSION 2.8)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

project(Nachos)

option(USER_PROGRAM ON)
option(FILESYS ON)
option(NETWORK ON)
option(THREADS ON)

FILE(GLOB_RECURSE src *.c *.cc *.h *.S)
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SUBDIRS}
    )

add_executable(${PROJECT_NAME} ${src})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LINK_LIBS} )


