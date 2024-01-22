# 项目前置条件

在您构建和运行此项目之前，需要确保您的系统已安装以下依赖项：

- <strong>CMake</strong>：本项目使用 CMake 作为构建系统。您可以从[官方网站](https://cmake.org/download/)下载。安装后，请确保将 CMake 添加到您的系统 PATH 中。
- <strong>Python</strong>：本项目使用 Python 执行一些脚本。您可以从[官方网站](https://www.python.org/downloads/)下载 Python。安装后，请确保将 Python 添加到您的系统 PATH 中。
  - <strong>Jinja2</strong>：这是项目中使用的 Python 库。安装 Python 后，您可以通过在终端运行 `pip install jinja2` 来安装 Jinja2。
- <strong>C++203</strong>：本项目使用 C++20 编写。因此，您需要支持 C++20 的 C++ 编译器。推荐使用 GCC 10 或更高版本、Clang 10 或更高版本、MSVC 19.28（Visual Studio 2019 16.8）或更高版本。

请在继续构建过程之前确保满足所有这些前置条件。如果您遇到任何问题，请在 GitHub 上提出 issue。

本项目是跨平台的，但由于时间有限，目前仅配置了 Windows 平台（支持 Visual Studio 2022 编译或者使用 VSCode）。您可以通过以下链接访问项目的 GitHub 仓库：<https://github.com/yangyunzhao/toy>。

此外，项目还整合了以下工具和库以优化开发流程：

- <strong>Doxygen</strong>：用于生成项目文档。了解更多信息和下载，请访问[Doxygen 官方网站](http://www.doxygen.nl/)。
- <strong>Graphviz</strong>：用于生成图形化的文档内容。详情和下载信息，请查看[Graphviz 官方网站](https://graphviz.org/)。
- <strong>Clang-Format</strong>：用于统一代码风格。更多详情，请访问[Clang-Format 官方文档](https://clang.llvm.org/docs/ClangFormat.html)。
- <strong>Catch2 v2</strong>：用于单元测试。您可以从[Catch2 v2 官方GitHub仓库](https://github.com/catchorg/Catch2/tree/v2.x)获取。

在开始构建过程之前，请确保所有这些前置条件都已满足。如果您在过程中遇到任何问题，欢迎在 GitHub 上开启一个 issue。
