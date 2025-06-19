//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-prototype-invocation-expression-node.h"
#include "../../../../../shared/utils/logger/logger.h"

IRExpressionNode* TupleAccessInvocationExpressionIRStrategy::generate(ASTTupleAccessInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto arguments = std::vector<IRExpressionNode*>();
    for (auto argument : *node->getArguments()->getArguments()) {
        arguments.push_back(irGenerator->generateFor(argument, scope, irContext, IR_FUNCTION_ARGUMENT_OP));
    }

    // todo - add support for struct lambda's and other prototypes
    throw std::logic_error("TupleAccessInvocationExpressionIRStrategy failed");
}