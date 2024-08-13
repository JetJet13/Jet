//
// Created by Johny Georges on 2024-07-15.
//

#ifndef JETLANG_IR_ENUM_DECLARATION_NODE_H
#define JETLANG_IR_ENUM_DECLARATION_NODE_H

#include <llvm/IR/Instructions.h>
#include "ir-declaration-node.h"
#include "../../../core/ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"
#include "../ir-global-variable-node.h"
#include "../../ir-injector/ir-injector-map.h"

class IREnumDeclarationNode : public IRDeclarationNode {
private:
    ASTEnumDeclarationNode* _node;
    IRGlobalVariableNode* _irValue;
public:
    IREnumDeclarationNode(ASTEnumDeclarationNode* node, IRGlobalVariableNode* irValue);
    void insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ENUM_DECLARATION_NODE_H
