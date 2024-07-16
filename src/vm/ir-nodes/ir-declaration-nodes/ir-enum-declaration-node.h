//
// Created by Johny Georges on 2024-07-15.
//

#ifndef JETLANG_IR_ENUM_DECLARATION_NODE_H
#define JETLANG_IR_ENUM_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "ir-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"

class IREnumDeclarationNode : public IRDeclarationNode {
private:
    ASTEnumDeclarationNode* _node;
    llvm::GlobalVariable* _irValue;
public:
    IREnumDeclarationNode(ASTEnumDeclarationNode* node, llvm::GlobalVariable* irValue);
    void insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ENUM_DECLARATION_NODE_H
