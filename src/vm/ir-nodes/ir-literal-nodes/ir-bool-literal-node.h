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
    std::shared_ptr<ASTBooleanLiteralNode> _astNode;
    llvm::ConstantInt* _irValue;
    IRType* _type;
public:
    IRBoolLiteralNode(std::shared_ptr<ASTBooleanLiteralNode> astNode, llvm::ConstantInt* irValue);
    llvm::ConstantInt* getConstantIRValue() override;
    IRType* getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BOOL_LITERAL_NODE_H
