//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BOOL_LITERAL_NODE_H
#define JETLANG_IR_BOOL_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "ir-literal-node.h"

class IRBoolLiteralNode : public IRLiteralNode {
private:
    ASTBooleanLiteralNode* _astNode;
    llvm::ConstantInt* _irValue;
public:
    IRBoolLiteralNode(ASTBooleanLiteralNode* astNode, llvm::ConstantInt* irValue);
    llvm::Constant* getConstantIRValue() override;
    llvm::ConstantInt* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_BOOL_LITERAL_NODE_H
