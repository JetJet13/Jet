//
// Created by Johny Georges on 2026-09-05.
//

#ifndef JETLANG_MAIN_H
#define JETLANG_MAIN_H

#include "llvm/IR/Module.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/VirtualFileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/Host.h"
#include "lld/Common/Driver.h"
#include <vector>

LLD_HAS_DRIVER(coff)
LLD_HAS_DRIVER(elf)
LLD_HAS_DRIVER(mingw)
LLD_HAS_DRIVER(macho)
LLD_HAS_DRIVER(wasm)

#endif //JETLANG_MAIN_H
