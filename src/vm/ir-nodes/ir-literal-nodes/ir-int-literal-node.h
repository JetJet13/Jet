//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_INT_LITERAL_NODE_H
#define JETLANG_IR_INT_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "ir-literal-node.h"

class IRIntLiteralNode : public IRLiteralNode {
private:
    ASTIntLiteralNode* _astNode;
    llvm::ConstantInt* _irValue;
    IRType* _type;
public:
    IRIntLiteralNode(ASTIntLiteralNode* astNode, llvm::ConstantInt* irValue, IRType* type);
    llvm::ConstantInt* getConstantIRValue() override;
    IRType* getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INT_LITERAL_NODE_H
