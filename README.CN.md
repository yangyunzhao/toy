# 项目前置条件

在构建和运行此项目之前，您需要确保您的系统上已安装以下依赖项：

- **CMake**：此项目使用 CMake 作为其构建系统。您可以从[官方网站](vscode-file://vscode-app/c:/Users/ZNMLR/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html)下载。安装后，请确保将 CMake 添加到您的系统 PATH 中。
- **Python**：此项目使用 Python 运行一些脚本。您可以从[官方网站](vscode-file://vscode-app/c:/Users/ZNMLR/AppData/Local/Programs/Microsoft VS Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.html)下载 Python。安装后，请确保将 Python 添加到您的系统 PATH 中。
  - **Jinja2**：这是此项目中使用的 Python 库。安装 Python 后，您可以在终端中运行 `pip install jinja2` 来安装 Jinja2。
- **C++17**：此项目使用 C++17 编写。因此，您需要一个支持 C++17 的 C++ 编译器。如果您使用的是 GCC，需要版本 7 或更高。如果您使用的是 Clang，需要版本 5 或更高。如果您使用的是 MSVC，需要版本 19.14 或更高。

请确保在进行构建过程之前满足所有这些前置条件。如果您遇到任何问题，欢迎在 GitHub 上开启一个 issue。