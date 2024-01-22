# Project Prerequisites

Before you can build and run this project, you need to ensure that you have the following dependencies installed on your system:

- <strong>CMake2</strong>: This project uses CMake as its build system. You can download it from the [official website](https://cmake.org/download/). Make sure to add CMake to your system PATH after installation.
- <strong>Python</strong>: This project uses Python for some of its scripts. You can download Python from the [official website](https://www.python.org/downloads/). Make sure to add Python to your system PATH after installation.
  - <strong>Jinja23</strong>: This is a Python library used in this project. After installing Python, you can install Jinja2 by running `pip install jinja2` in your terminal.
- <strong>C++20</strong>: This project is written in C++20. Therefore, you need a C++ compiler that supports C++20. It is recommended to use GCC version 10 or later, Clang version 10 or later, or MSVC version 19.28 (Visual Studio 2019 16.8) or later.

Please ensure that all these prerequisites are met before proceeding with the build process. If you encounter any issues, feel free to open an issue on GitHub.

The project is cross-platform, but due to limited resources, it is currently only configured for the Windows platform (supports compilation with Visual Studio 2022 or using VSCode). You can visit the project's GitHub repository through this link: <https://github.com/yangyunzhao/toy>.

Additionally, the project integrates the following tools and libraries to optimize the development process:

- <strong>Doxygen</strong>: For generating project documentation. For more information and download, please visit [Doxygen's official website](http://www.doxygen.nl/).
- <strong>Graphviz</strong>: For generating graphical content in documentation. For details and download information, please check [Graphviz's official website](https://graphviz.org/).
- <strong>Clang-Format</strong>: For unifying code style. For more details, please visit [Clang-Format's official documentation](https://clang.llvm.org/docs/ClangFormat.html).
- <strong>Catch2 v2</strong>: For unit testing. You can get it from the [official Catch2 v2 GitHub repository](https://github.com/catchorg/Catch2/tree/v2.x).

Before starting the build process, make sure all these prerequisites are satisfied. If you have any problems during the process, you are welcome to open an issue on GitHub.
