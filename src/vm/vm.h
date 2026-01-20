//
// Created by Johny Georges on 2024-11-04.
//

#ifndef JETLANG_VM_H
#define JETLANG_VM_H

#include "llvm/Linker/Linker.h"
#include "ir-generator/ir-generator.h"
#include "../core/jet-file/jet-file.h"
#include "ir-jet-file/ir-jet-file.h"

class VM {
private:
    IRGenerator* _irGenerator;
    IRInjector* _irInjector;
public:
    VM(IRGenerator* irGenerator, IRInjector* irInjector);
    IRJetFile* compile(JetFile* jetFile, std::shared_ptr<IRModuleNode> irCommonModule);
    IRJetFile* compileMain(JetFile* jetFile);
    void linkJetFiles(IRJetFile* jetFileToLink, IRJetFile* destination);
};

#endif //JETLANG_VM_H
