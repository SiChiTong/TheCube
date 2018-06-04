# TheCube

## Project Structure

```
TheCube                                               <- Project name
  |
  +-- REngine                                         <- Engine library
  |
  +-- TheCube                                         <- Executable sources
  |
  +-- CMakeLists.txt
```

# Coding style

## Code Formatting

- Use **ClangFormat** to apply the format definitions from **.clang-format**.
- Use `// clang-format on` and `clang-format off` wherever appropriate  to 
prevent **ClangFormat** from changing the desired code formatting.

## Header Files Include Order

1. Corresponding header file
2. Local header files
3. This project's libraries' header files
4. Third party libraries' header files
5. System header files
6. Standard C library's header files
7. Standard C++ library's header files

## Documentation

Use [XML Documentation comments][1] to annotate classes, methods, etc.

[1]: https://docs.microsoft.com/en-gb/cpp/ide/xml-documentation-visual-cpp
"XML Documentation"
