cmake_minimum_required(VERSION 3.10)

project(VEDA_Chat C)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/login.c
    ${CMAKE_SOURCE_DIR}/src/signup.c
    ${CMAKE_SOURCE_DIR}/src/messagebuilder.c
    ${CMAKE_SOURCE_DIR}/src/chatprocess.c
    ${CMAKE_SOURCE_DIR}/src/connectserver.c
    ${CMAKE_SOURCE_DIR}/src/hideinput.c
    ${CMAKE_SOURCE_DIR}/main.c
)

add_executable(chat_client ${SOURCES})
