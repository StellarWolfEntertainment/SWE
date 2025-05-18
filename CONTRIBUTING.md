# Contributing to SWE

Thank you for your interest in contributing!

## How to Contribute

- Fork the repo and create a branch named like `feature/your-feature` or `bugfix/issue-123` from `main`.
- Write clear, concise commit messages.
- Add tests for new features and bug fixes.
- Run all tests before submitting a pull request.
- Document new or changed public APIs.
- Follow the existing code style and run the formatter (`clang-format`) before committing.

## Dependency and Scope Policy

- SWE is a standalone utility library built exclusively on the C++ Standard Library.
- It does **not** extend, wrap, or depend on external libraries such as glm, stb, or others.
- Contributions must focus on utilities that complement or enhance the Standard Library types and algorithms only.
- Introducing third-party or non-std dependencies is strictly prohibited.

## Pull Requests

- Ensure your code builds and passes all tests.
- Clearly describe your changes in the pull request.
- Reference related issues if applicable.

## Code Style

- Follow the existing code style consistently.
- Use the provided `.clang-format` file to format your code before committing (`clang-format -i <files>`).
- Prefer C++11 features for broad compatibility, but allow newer standards if they bring clear benefits.
- Keep code modular, readable, and well-documented.

## Reporting Issues

- Use the [GitHub Issues](https://github.com/StellarWolfEntertainment/swe/issues) page.
- Provide as much detail as possible (OS, compiler, steps to reproduce, etc.).

---

Thank you for helping improve SWE!