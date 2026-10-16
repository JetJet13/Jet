# Jet Programming Language
Jet is a C-like general purpose programming language. It's currently in alpha. Please visit [jet-lang.com](https://jet-lang.com) to learn more.

```
// main.jet
print("hello world");
```

```
$ jet ./main.jet # outputs ~/main

$ ./main
hello world
```

### Download
For download instructions, please visit [jet-lang.com/download](https://jet-lang.com/download).

### Build Jet From Source
1. Install the following project dependencies (if not already installed):
    - `cmake` >= v3.26
    - `zig` >= v0.13.0
2. Git clone the repo
3. Download the `target-deps` bundle from the github release page for your desired target
   - MacOS x86_64 - `x86_64-macos-target-deps-jet-<version>.tar.gz`
   - MacOS aarch64 - `aarch64-macos-target-deps-jet-<version>.tar.gz`
   - Linux GNU x86_64 - `x86_64-linux-gnu-target-deps-jet-<version>.tar.gz`
   - Linux GNU aarch64 - `aarch64linux-gnu-target-deps-jet-<version>.tar.gz`
   - Linux MUSL x86_64 - `x86_64-linux-musl-target-deps-jet-<version>.tar.gz`
   - Linux MUSL aarch64 - `aarch64-linux-musl-target-deps-jet-<version>.tar.gz`
4. Extract the target-deps bundle into a new folder that is named after your desired target
   - MacOS x86_64 - `jet-lang/zig-util/target/x86_64-macos`
   - MacOS aarch64 - `jet-lang/zig-util/target/aarch64-macos`
   - Linux GNU x86_64 - `jet-lang/zig-util/target/x86_64-linux-gnu`
   - Linux GNU aarch64 - `jet-lang/zig-util/target/aarch64linux-gnu`
   - Linux MUSL x86_64 - `jet-lang/zig-util/target/x86_64-linux-musl`
   - Linux MUSL aarch64 - `jet-lang/zig-util/target/aarch64-linux-musl`
   ```shell
   # We're going to use macOS x86_64 as an example
   
   # run from /jet-lang directory
   mkdir -p ./zig-util/target
   
   # unzip target dependencies into target folder
   tar -xf x86_64-macos-target-deps-jet-v0.1.0.tar.gz -C <path-to-jet-lang-repo>/jet-lang/zig-util/target
   ```
5. You should now have a folder structure like this
    ```
    /jet-lang
    ├── zig-util/
        ├── target/
            ├── x86_64-macos/
                ├── llvm/
                |   └── (sub-folders)
                └── sysroot/
                    └── (sub-folders)
    ```
6. Build `jet-cli`
     
   | Directory   | Command                             |
   |-------------|-------------------------------------|    
   | `/jet-lang` | `cmake -S ./src/jet-cli -B ./build` |
   | `/jet-lang` | `cmake --build build`               | 

7. Use `jet-cli` to build the jet compiler for your desired target
   
   | Directory   | Command                                 |
   |-------------|-----------------------------------------|    
   | `/jet-lang` | `./build/jet-cli --target x86_64-macos` |

8. Once the jet-cli command completes successfully, the executables will be located in the `zig-out` folder
    ```
   /jet-lang
    ├── zig-out/
        └── x86_64-macos/
            └── bin/
                ├── jet
                └── jet-debug
    ```
9. Congrats, you've just built Jet from source!

Note: If you get stuck or run into problems when attempting to build Jet from source, please review the github issues list to see if an issue already exists for the problem(s) you're dealing with. If no issue exists, then feel free to create a new issue.

### Documentation
Please visit [jet-lang.com/docs](https://jet-lang.com/docs)

### Contribute
Please visit [CONTRIBUTING.md](./CONTRIBUTING.md)

### FAQ
Please visit [FAQ.md](./FAQ.md)

### License
Jet is licensed under Apache License, Version 2.0.

To learn more, please visit [LICENSE.md](./LICENSE.md)