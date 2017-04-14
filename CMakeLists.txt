cmake_minimum_required(VERSION 3.6)
project(ft_p)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libft)
include_directories(libft/includes)
include_directories(client_src)
include_directories(client_src/includes)
include_directories(server_src)
include_directories(server_src/includes)

set(SRCS_CLIENT
        client_src/srcs/main.c
        client_src/srcs/error.c
        client_src/srcs/set_client.c
        client_src/srcs/event.c
        client_src/srcs/main_loop.c
        client_src/srcs/ring_buffer.c
        client_src/srcs/cmd.c
        )
set(HEADER_CLIENT client_src/includes/client.h)

set(SRCS_SERVER
        server_src/srcs/main.c
        server_src/srcs/error.c
        server_src/srcs/util.c
        server_src/srcs/set_server.c
        server_src/srcs/set_client.c
        server_src/srcs/main_loop.c
        server_src/srcs/event.c
        server_src/srcs/set_action.c
        server_src/srcs/cmd.c
        server_src/srcs/cmd_nick.c
        server_src/srcs/cmd_join.c
        server_src/srcs/cmd_leave.c
        server_src/srcs/cmd_who.c
        server_src/srcs/cmd_msg.c
        server_src/srcs/cmd_list.c
        server_src/srcs/cmd_whois.c
        server_src/srcs/ring_buffer.c
        server_src/srcs/print_log_bonus.c
        server_src/srcs/util_channel.c
    )
set(HEADER_SERVER server_src/includes/server.h)


#set(SRC_BIRCD
#    bircd/bircd.h)

add_executable(client ${SRCS_CLIENT} ${HEADER_CLIENT})
add_executable(server ${SRCS_SERVER} ${HEADER_SERVER})
#add_executable(BIRCD ${SRC_BIRCD})

target_link_libraries(client ft)
target_link_libraries(server ft)