//
// Created by Johny Georges on 2024-10-30.
//

#ifndef JETLANG_IR_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H
#define JETLANG_IR_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "ir-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"

class IRImportSingleModuleDeclarationNode : public IRDeclarationNode {
private:
    ASTImportSingleModuleDeclarationNode* _node;
public:
    IRImportSingleModuleDeclarationNode(ASTImportSingleModuleDeclarationNode* node);
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H
