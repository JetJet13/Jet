//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_STRING_LITERAL_NODE_H
#define JETLANG_IR_STRING_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../ir-node.h"
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"

class IRStringLiteralNode : public IRNode {
private:
    ASTStringLiteralNode* _astNode;
    llvm::ConstantArray* _irValue;
public:
    IRStringLiteralNode(ASTStringLiteralNode* astCharLiteralNode, llvm::ConstantArray* irValue);
    llvm::ConstantArray* getIRValue();
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_STRING_LITERAL_NODE_H
