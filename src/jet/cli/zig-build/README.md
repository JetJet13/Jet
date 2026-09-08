# Cross-Compiling Jet using Zig

### MacOS x64 Host
OS: MacOS Monterey v12.7.2
Zig Version: 0.13.0 (installed via brew)

Note: Your zig installation might be missing the libSystem.tbd file so you'll need to link it from your MacOSX.sdk installation.

e.g. to confirm if your zig installation is missing libSystem.tbd
```
$ ls -la $(brew --prefix zig)/lib/zig/libc/darwin

// output (needs fixing, see command below)
total 8
drwxr-xr-x  4 <user>  admin  128  7 Sep 19:18 .
drwxr-xr-x  8 <user>  admin  256  6 Jun  2024 ..
-r--r--r--  1 <user>  admin   30  6 Jun  2024 SDKSettings.json


// output (all good)
total 8
drwxr-xr-x  4 <user>  admin  128  7 Sep 19:18 .
drwxr-xr-x  8 <user>  admin  256  6 Jun  2024 ..
-r--r--r--  1 <user>  admin   30  6 Jun  2024 SDKSettings.json
lrwxr-xr-x  1 <user>  admin   30  6 Jun  2024 libSystem.tbd

```
Fix:
```
$ sudo ln -s /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libSystem.tbd /usr/local/Cellar/zig/0.13.0/lib/zig/libc/darwin/libSystem.tbd
```
```
// verify link command worked
$ ls -la $(brew --prefix zig)/lib/zig/libc/darwin

// expected output
total 8
drwxr-xr-x  4 johny.georges  admin  128  7 Sep 19:18 .
drwxr-xr-x  8 johny.georges  admin  256  6 Jun  2024 ..
-r--r--r--  1 johny.georges  admin   30  6 Jun  2024 SDKSettings.json
lrwxr-xr-x  1 root           admin   77  7 Sep 19:18 libSystem.tbd -> /Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib/libSystem.tbd
```