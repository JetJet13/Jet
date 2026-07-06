//
// Created by Johny Georges on 2024-07-02.
//

#ifndef JETLANG_IR_LITERAL_EXPRESSION_NODE_H
#define JETLANG_IR_LITERAL_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../ir-literal-nodes/ir-literal-node.h"
#include "../../ir-type/ir-pointer-type.h"

class IRLiteralExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTLiteralExpressionNode> _node;
    std::shared_ptr<IRLiteralNode> _irValue;
    std::shared_ptr<IRType> _irType;
public:
    IRLiteralExpressionNode(std::shared_ptr<ASTLiteralExpressionNode> node, std::shared_ptr<IRLiteralNode> irValue, std::shared_ptr<IRType> irType);
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    llvm::Constant* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};


#endif //JETLANG_IR_LITERAL_EXPRESSION_NODE_H
