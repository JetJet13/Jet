# Build Jet From Source
This is step-by-step guide to build Jet from source. If you get stuck or run into problems, please review the [github issues list](https://github.com/JetJet13/Jet/issues) to see if an issue already exists for the problem you're dealing with. If no issue exists, then feel free to create one.


1. Install the following project dependencies (if not already installed):
    - `cmake` >= v3.26
    - `zig` >= v0.13.0<br/><br/>
   Note: If you run into issues using zig versions > v0.13.0, switch to v0.13.0
2. Git clone the repo
    ```shell
    git clone git@github.com:JetJet13/Jet.git ./jet-lang
    ```
    Moving forward, if you see the term `root`, it is referring to `/jet-lang`.
3. Download the `target-deps` bundle from the [github release page](https://github.com/JetJet13/Jet/releases) for your desired target.

   | Target | Asset                                                 |
   |--------|-------------------------------------------------------| 
   | MacOS x86_64 | `x86_64-macos-target-deps-jet-<version>.tar.gz`       | 
   | MacOS aarch64 | `aarch64-macos-target-deps-jet-<version>.tar.gz`      | 
   | Linux GNU x86_64 | `x86_64-linux-gnu-target-deps-jet-<version>.tar.gz`   | 
   | Linux GNU aarch64 | `aarch64-linux-gnu-target-deps-jet-<version>.tar.gz`  | 
   | Linux MUSL x86_64 | `x86_64-linux-musl-target-deps-jet-<version>.tar.gz`  | 
   | Linux MUSL aarch64 | `aarch64-linux-musl-target-deps-jet-<version>.tar.gz` |
4. Extract the target-deps bundle into a new `target` folder
   
   | Directory | Command                                                       |
   |-----------|---------------------------------------------------------------|    
   | `root`    | `mkdir -p ./zig-util/target`                                  |
   | `root`    | `tar -xf <path-to-target-deps-tar-ball> -C ./zig-util/target` | 
   
   You should now have a folder structure like this
    ```
    /jet-lang (root)
    ├── zig-util/
        ├── target/
            ├── <target-name>/
                ├── llvm/
                |   └── (sub-folders)
                └── sysroot/
                    └── (sub-folders)
    ```
5. Build `jet-cli`

   | Directory | Command                             |
   |-----------|-------------------------------------|    
   | `root`    | `cmake -S ./src/jet-cli -B ./build` |
   | `root`    | `cmake --build build`               | 

6. Use `jet-cli` to build the jet compiler for your desired target. You can use `-h` to get a list of available target names.

   | Directory | Command                                  |
   |-----------|------------------------------------------|    
   | `root`    | `./build/jet-cli --target <target-name>` |

   Once the jet-cli command completes successfully, the executables will be located in the `zig-out` folder
    ```
   /jet-lang (root)
    ├── zig-out/
        └── <target-name>/
            └── bin/
                ├── jet
                └── jet-debug
    ```
7. Congrats, you just built Jet from source! 

##### Important Note
After building Jet from source, your machine might be missing some dependencies that Jet expects to be installed. Head over to the [github release page](https://github.com/JetJet13/Jet/releases) and select the version you've built against and refer to the `Download Instructions` section for more info.