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
    ASTBinaryComparatorExpressionNode* _node;
    llvm::CmpInst* _irValue;
    IRExpressionNode* _irLeftNode;
    IRExpressionNode* _irRightNode;
    IRType* _type;
    IRType* _leftIrType;
    IRType* _rightIrType;
public:
    IRBinaryComparisonExpressionNode(ASTBinaryComparatorExpressionNode* astNode, llvm::CmpInst* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRType* type, IRType* leftIrType, IRType* rightIrType);
    void markAsGlobal() override;
    llvm::CmpInst* getValue() override;
    bool isPredicateEqual();
    bool isPredicateNotEqual();
    IRType* getLeftIrType();
    IRType* getRightIrType();
    IRExpressionNode* getLeftNode();
    IRExpressionNode* getRightNode();
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H
