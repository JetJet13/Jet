//
// Created by Johny Georges on 2024-07-15.
//

#ifndef JETLANG_IR_ENUM_DECLARATION_NODE_H
#define JETLANG_IR_ENUM_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "ir-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"
#include "../ir-global-variable-node.h"

class IREnumDeclarationNode : public IRDeclarationNode {
private:
    ASTEnumDeclarationNode* _node;
    IRInstructionNode* _irValue;
public:
    IREnumDeclarationNode(ASTEnumDeclarationNode* node, IRInstructionNode* irValue);
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ENUM_DECLARATION_NODE_H
