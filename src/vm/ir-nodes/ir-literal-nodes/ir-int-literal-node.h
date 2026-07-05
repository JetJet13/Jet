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
    std::shared_ptr<ASTIntLiteralNode> _astNode;
    llvm::ConstantInt* _irValue;
    std::shared_ptr<IRType> _type;
public:
    IRIntLiteralNode(std::shared_ptr<ASTIntLiteralNode> astNode, llvm::ConstantInt* irValue);
    llvm::ConstantInt* getConstantIRValue() override;
    std::shared_ptr<IRType> getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_INT_LITERAL_NODE_H
