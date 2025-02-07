# mini-strace

## 项目简介
`mini-strace` 是一个用 C 语言编写的简单系统调用跟踪工具。它类似于 `strace`，但功能较为简化，适用于学习和理解系统调用的工作原理。

## 文件结构
- `strace.c`：主程序文件，包含系统调用跟踪的实现。
- `Makefile`：用于构建项目的 Makefile。
- `CMakeLists.txt`：用于 CMake 构建系统的配置文件。
- `.gitignore`：Git 忽略文件配置。
- `build/`：构建输出目录。

## 构建和运行
### 使用 Makefile 构建
```bash
make
```

### 使用 CMake 构建
```bash
mkdir build
cd build
cmake ..
make
```

### 运行
构建完成后，可以使用以下命令运行 `mini-strace`：
```bash
./mini-strace <command>
```
其中 `<command>` 是你想要跟踪的命令。

## 贡献
欢迎贡献代码！请提交 Pull Request 或报告 Issue。

