cmake_minimum_required(VERSION 3.19)
project(2 C)

set(CMAKE_C_STANDARD 99)


#add_library(readline)
#link_directories(~/.brew/Cellar/readline/8.1/lib/)
##
#target_link_libraries(
##        mini PRIVATE
#        readline
##        libft
#        libreadline.a
#        libhistory.a
#)
include_directories(/Users/paminna/.brew/opt/readline/lib/)
link_directories(/Users/paminna/.brew/opt/readline/lib/)
find_library(NAMES libreadline PATHS /Users/paminna/.brew/opt/readline/lib/ /Users/paminna/.brew/opt/readline/lib/)
set(INCLUDE_DIR /Users/paminna/.brew/opt/readline/lib/)
#target_compile_options(
#        -lreadline -L~/.brew/opt/readline/include ~/.brew/Cellar/readline/8.1/lib/libreadline.8.1.dylib ~/.brew/Cellar/readline/8.1/lib/libhistory.8.1.dylib -I~/.brew/opt/readline/include -ltermcap
#        #        -Wall -Wextra -Werror
#)
add_executable(2 main.c libft.c parser_quotes.c mini.h signals.c env.c function/cd.c function/ft_unset.c function/pwd.c  get_next_line.c get_next_line_utils.c parser_first_s.c export.c)
target_link_libraries(2 readline)