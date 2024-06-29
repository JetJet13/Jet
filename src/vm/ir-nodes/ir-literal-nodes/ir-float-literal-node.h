//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_FLOAT_LITERAL_NODE_H
#define JETLANG_IR_FLOAT_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../ir-node.h"
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"

class IRFloatLiteralNode : public IRNode {
private:
    ASTFloatLiteralNode* _astNode;
    llvm::ConstantFP* _irValue;
public:
    IRFloatLiteralNode(ASTFloatLiteralNode* astFloatLiteralNode, llvm::ConstantFP* irValue);
    llvm::ConstantFP* getIRValue();
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_FLOAT_LITERAL_NODE_H
