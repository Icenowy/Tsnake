# Deploying

How to deploy it?

## Environment

You need a working GNU/Linux environment, with a working C++11 Compiler (Tested on G++ 5.2.1, 5.3.0 and Clang++ 3.7.0).

To get the latest source code, you should have Git installed.

If you want to enable the i18n support (enabled by default), you need a glibc system. (all LSB-complicant systems are OK.) In addition, you'd also have gettext installed.

To use the build system, you need `make` installed.

On Debian, Ubuntu or AOSC OS, you can use `make dependencies` to meet the dependencies, or `sh util/install-dependencies.sh` if you have ever no `make` installed.

## Deploying

### Build for temporarily running

`make` for build the main executable, `tsnake`.

`make install-mo` can be used to build the locale file for i18n.

Then you can play it with `./tsnake`.

### Build for the system

`make PREFIX=/usr && make PREFIX=/usr install` can create a system-wide executable file `/usr/bin/tsnake`.

### Cross-compiling

`make CXX=$TARGET-g++ HOSTCXX=g++` can be used to cross-compile a binary.
