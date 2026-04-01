//
// Created by Johny Georges on 2024-11-04.
//

#ifndef JETLANG_IR_JET_FILE_H
#define JETLANG_IR_JET_FILE_H

#include "../../core/jet-file/jet-file.h"
#include "../ir-nodes/ir-module-node.h"

class IRJetFile {
private:
    JetFile* _jetFile;
    std::shared_ptr<IRModuleNode> _irModule;

public:
    IRJetFile(JetFile* jetFile, std::shared_ptr<IRModuleNode> irModule);
    JetFile* getFile();
    std::shared_ptr<IRModuleNode> getIRModule();
};

#endif //JETLANG_IR_JET_FILE_H
