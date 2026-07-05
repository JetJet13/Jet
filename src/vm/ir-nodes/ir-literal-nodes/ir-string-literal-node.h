//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_STRING_LITERAL_NODE_H
#define JETLANG_IR_STRING_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "ir-literal-node.h"
#include "../../ir-type/ir-type.h"
#include "../../ir-type/ir-array-type.h"

class IRStringLiteralNode : public IRLiteralNode {
private:
    std::shared_ptr<ASTStringLiteralNode> _astNode;
    llvm::Constant* _irValue;
    std::shared_ptr<IRArrayType> _type;
public:
    IRStringLiteralNode(std::shared_ptr<ASTStringLiteralNode> astNode, llvm::Constant* irValue, std::shared_ptr<IRArrayType> type);
    llvm::Constant* getConstantIRValue() override;
    std::shared_ptr<IRArrayType> getIRArrayType();
    std::shared_ptr<IRType> getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRING_LITERAL_NODE_H
