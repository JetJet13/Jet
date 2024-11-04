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
    IRModuleNode* _irModule;
public:
    IRJetFile(JetFile* jetFile, IRModuleNode* irModule);
    JetFile* getFile();
    IRModuleNode* getModule();
};

#endif //JETLANG_IR_JET_FILE_H
