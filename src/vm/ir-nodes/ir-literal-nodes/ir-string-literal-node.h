//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_STRING_LITERAL_NODE_H
#define JETLANG_IR_STRING_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "ir-literal-node.h"
#include "../../ir-type/ir-type.h"
#include "../ir-array-node.h"

class IRStringLiteralNode : public IRLiteralNode {
private:
    ASTStringLiteralNode* _astNode;
    llvm::Constant* _irValue;
    IRArrayNode* _irArray;
    IRType* _type;
public:
    IRStringLiteralNode(ASTStringLiteralNode* astNode, llvm::Constant* irValue, IRArrayNode* irArray);
    IRArrayNode* getIRArray();
    llvm::Constant* getConstantIRValue() override;
    IRType* getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRING_LITERAL_NODE_H
