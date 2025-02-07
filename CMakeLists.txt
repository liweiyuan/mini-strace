cmake_minimum_required(VERSION 3.10)

# 项目名称
project(mini-strace C)

# 启用严格警告
add_compile_options(-Wall -Wextra -g)

# 添加可执行文件
add_executable(strace strace.c)

# 自定义清理目标，删除可执行文件和构建目录
add_custom_target(mini_clean
    COMMAND ${CMAKE_COMMAND} -E remove -f strace
    COMMAND ${CMAKE_COMMAND} -E remove_directory CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove CMakeCache.txt cmake_install.cmake Makefile
    COMMENT "Cleaning up generated files"
)
