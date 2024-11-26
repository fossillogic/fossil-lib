# **Fossil Lib by Fossil Logic**

Fossil Lib is a versatile, cross-platform utilities library designed to provide essential functionalities for high-performance application development. It includes a suite of common utilities such as host system interaction, command execution, a cnullptr type definition, and secure memory management. Fossil Lib is implemented in both C and C++ and is optimized for consistency and efficiency across various operating systems.

## Key Features

1. **Cross-Platform Compatibility**: Provides a uniform interface and consistent behavior across major operating systems, including Windows, macOS, and Linux.
2. **Modular Design**: Contains modular components that can be easily integrated and customized for specific project needs.
3. **Efficient Build System**: Built using the Meson build system, which ensures fast build times and a straightforward development process.
4. **High Performance**: Developed in C and C++ to maximize performance and resource efficiency, suitable for both desktop and embedded systems.
5. **Extensive Documentation**: Offers comprehensive documentation and examples to help developers quickly understand and utilize the library.

## Prerequisites

Before using Fossil Lib, ensure you have the following:

- **Meson Build System**: Install Meson to manage the build process. For installation or upgrading, use:

  ```sh
  python -m pip install meson           # to install Meson
  python -m pip install --upgrade meson # to upgrade Meson
  ```

## Adding Dependency

1. **Install Meson Build System**: Ensure Meson `1.3` or newer is installed on your system.

2. **Add Wrap File**: Create a `.wrap` file (e.g., `fossil-lib.wrap`) in the `subprojects` directory with the following content:

   ```ini
   # ======================
   # Git Wrap package definition
   # ======================
   [wrap-git]
   url = https://github.com/fossillogic/fossil-lib.git
   revision = v0.1.1

   [provide]
   fossil-lib = fossil_lib_dep
   ```

3. **Integrate Dependency**: Add the dependency in your `meson.build` file:

   ```ini
   dep = dependency('fossil-lib')
   ```

## Configure Options

- **Running Tests**: Enable testing by configuring with `-Dwith_test=enabled`.

Example:

```sh
meson setup builddir -Dwith_test=enabled
```

## Contributing and Support

For contributions, issues, or support, please open an issue on the project repository or visit the [Fossil Logic Docs](https://fossillogic.com/docs) for more information. Contributions and feedback are always appreciated.

