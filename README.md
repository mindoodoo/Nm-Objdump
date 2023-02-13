# Nm and Objdump Command Implementations

The goal of this project was to implement an equivalent to the system commands ```nm``` (no arguments) and ```objdump -fs```.

The two produced binaries should be able to run on a variety of file types.

The **main restriction of this project** was that we **were not allowed to use the ```libelf.h``` library.** Instead, we have to reimplement the functions we needed using the structures in the ```elf.h``` header file.

## Building

This project produces **two** binaries :

- ```my_nm```
- ```my_objdump```

These binaries can be built by installing ```make``` and running :

```
make
```

You can optionally specify which binary you want to build.

## Usage

```
./my_nm <file>
```

```
./my_objdump <file>
```

## Features

- **Supports**
    - Relocatable files .o & .a
    - Shared files .so
    - Executable files
- In most cases, exact same outputs as original commands
- **No usage of libelf**