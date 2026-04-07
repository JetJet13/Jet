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
    std::unordered_map<std::string, IRJetFile*> _jetFileMap;
    std::optional<IRJetFile*> findCompiledJetFile(std::string id);
    void addCompiledJetFile(IRJetFile* irJetFile);
public:
    VM(IRGenerator* irGenerator, IRInjector* irInjector);
    IRFunctionNode* compile(IRJetFile* irJetFile, std::shared_ptr<IRModuleNode> irModule);
    IRJetFile* compileMain(JetFile* jetFile);
    void linkJetFiles(IRJetFile* jetFileToLink, IRJetFile* destination);
};

#endif //JETLANG_VM_H
