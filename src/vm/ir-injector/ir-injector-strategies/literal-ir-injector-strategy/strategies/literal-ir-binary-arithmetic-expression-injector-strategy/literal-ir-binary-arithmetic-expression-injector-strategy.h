//
// Created by Johny Georges on 2025-03-07.
//

#ifndef JETLANG_LITERAL_IR_BINARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H
#define JETLANG_LITERAL_IR_BINARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H

#include <algorithm>
#include "../../../../../ir-nodes/ir-block-nodes/ir-block-node.h"
#include "../../../../ir-injector.h"
#include "../../../../../types/ir-operation-type.h"
#include "../../../../../ir-nodes/ir-expression-nodes/ir-binary-expression-nodes/ir-binary-arithmetic-expression-node.h"
#include "../../../../../ir-nodes/ir-binary-arithmetic-node.h"

class LiteralIRBinaryArithmeticExpressionInjectorStrategy {
private:
    IRBinaryArithmeticNode* findNextOperationIndex(std::vector<IRBinaryOperatorNode*>* operations);
    llvm::Value* calculate(IRBlockNode* irBlock, IRBinaryArithmeticNode* binaryOp, llvm::Value* leftValue, llvm::Value* rightValue, std::shared_ptr<IRModuleNode> irModule);
public:
    llvm::Value* inject(IRBinaryArithmeticExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};


#endif //JETLANG_LITERAL_IR_BINARY_ARITHMETIC_EXPRESSION_INJECTOR_STRATEGY_H
