//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_CHAR_LITERAL_NODE_H
#define JETLANG_IR_CHAR_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../ir-node.h"
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"

class IRCharLiteralNode : public IRNode {
private:
    ASTCharLiteralNode* _astNode;
    llvm::ConstantInt* _irValue;
public:
    IRCharLiteralNode(ASTCharLiteralNode* astCharLiteralNode, llvm::ConstantInt* irValue);
    llvm::ConstantInt* getIRValue();
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_CHAR_LITERAL_NODE_H
