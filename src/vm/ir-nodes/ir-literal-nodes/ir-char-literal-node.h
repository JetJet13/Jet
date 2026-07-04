//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_CHAR_LITERAL_NODE_H
#define JETLANG_IR_CHAR_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "ir-literal-node.h"

class IRCharLiteralNode : public IRLiteralNode {
private:
    std::shared_ptr<ASTCharLiteralNode> _astNode;
    llvm::ConstantInt* _irValue;
    IRType* _type;
public:
    IRCharLiteralNode(std::shared_ptr<ASTCharLiteralNode> astNode, llvm::ConstantInt* irValue);
    llvm::ConstantInt* getConstantIRValue() override;
    IRType* getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_CHAR_LITERAL_NODE_H
