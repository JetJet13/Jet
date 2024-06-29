//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_INT_LITERAL_NODE_H
#define JETLANG_IR_INT_LITERAL_NODE_H

#include <llvm/IR/Constants.h>
#include "../ir-node.h"
#include "../../../core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"

class IRIntLiteralNode : public IRNode {
private:
    ASTIntLiteralNode* _astNode;
    llvm::ConstantInt* _irValue;
public:
    IRIntLiteralNode(ASTIntLiteralNode* astIntLiteralNode, llvm::ConstantInt* irValue);
    llvm::ConstantInt* getIRValue();
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_INT_LITERAL_NODE_H
