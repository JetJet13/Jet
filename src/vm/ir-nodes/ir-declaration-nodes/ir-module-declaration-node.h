//
// Created by Johny Georges on 2024-10-29.
//

#ifndef JETLANG_IR_MODULE_DECLARATION_NODE_H
#define JETLANG_IR_MODULE_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "ir-declaration-node.h"
#include "../ir-global-variable-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"

class IRModuleDeclarationNode : public IRDeclarationNode {
private:
    ASTModuleDeclarationNode* _node;
    std::vector<IRNode*> _exports;
public:
    IRModuleDeclarationNode(ASTModuleDeclarationNode* node, std::vector<IRNode*> exports);
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_MODULE_DECLARATION_NODE_H
