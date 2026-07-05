//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H
#define JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "ir-binary-expression-node.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-comparator-expression-node.h"

class IRBinaryComparisonExpressionNode : public IRBinaryExpressionNode {
private:
    std::shared_ptr<ASTBinaryComparatorExpressionNode> _node;
    llvm::CmpInst* _irValue;
    IRExpressionNode* _irLeftNode;
    IRExpressionNode* _irRightNode;
    std::shared_ptr<IRType> _type;
    std::shared_ptr<IRType> _leftIrType;
    std::shared_ptr<IRType> _rightIrType;
public:
    IRBinaryComparisonExpressionNode(std::shared_ptr<ASTBinaryComparatorExpressionNode> astNode, llvm::CmpInst* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, std::shared_ptr<IRType> type, std::shared_ptr<IRType> leftIrType, std::shared_ptr<IRType> rightIrType);
    void markAsGlobal() override;
    llvm::CmpInst* getValue() override;
    bool isPredicateEqual();
    bool isPredicateNotEqual();
    std::shared_ptr<IRType> getLeftIrType();
    std::shared_ptr<IRType> getRightIrType();
    IRExpressionNode* getLeftNode();
    IRExpressionNode* getRightNode();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H
