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
    std::shared_ptr<IRGenerator> _irGenerator;
    std::shared_ptr<IRInjector> _irInjector;
    std::unordered_map<std::string, std::shared_ptr<IRJetFile>> _jetFileMap;
    std::optional<std::shared_ptr<IRJetFile>> findCompiledJetFile(std::string id);
    void addCompiledJetFile(std::shared_ptr<IRJetFile> irJetFile);
public:
    VM(std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRInjector> irInjector);
    std::shared_ptr<IRFunctionNode> compile(std::shared_ptr<IRJetFile> irJetFile, std::shared_ptr<IRModuleNode> irModule);
    std::shared_ptr<IRJetFile> compileMain(std::shared_ptr<JetFile> jetFile);
    void linkJetFiles(std::shared_ptr<IRJetFile> jetFileToLink, std::shared_ptr<IRJetFile> destination);
};

#endif //JETLANG_VM_H
