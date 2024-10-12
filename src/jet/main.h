//
// Created by Johny Georges on 2023-12-19.
//

#ifndef JETLANG_MAIN_H
#define JETLANG_MAIN_H

#include "clang/Driver/Compilation.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "llvm/IR/Module.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/Host.h"
#include "llvm/Target/TargetMachine.h"
#include <vector>
#include <clang/Driver/Driver.h>

#endif //JETLANG_MAIN_H
