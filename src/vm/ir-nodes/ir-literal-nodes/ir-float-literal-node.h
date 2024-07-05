//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_FLOAT_LITERAL_NODE_H
#define JETLANG_IR_FLOAT_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "ir-literal-node.h"

class IRFloatLiteralNode : public IRLiteralNode {
private:
    ASTFloatLiteralNode* _astNode;
    llvm::ConstantFP* _irValue;
public:
    IRFloatLiteralNode(ASTFloatLiteralNode* astNode, llvm::ConstantFP* irValue);
    llvm::Constant* getConstantIRValue() override;
    llvm::ConstantFP* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FLOAT_LITERAL_NODE_H
