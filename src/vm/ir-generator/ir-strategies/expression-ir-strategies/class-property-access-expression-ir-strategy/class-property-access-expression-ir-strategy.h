//
// Created by Johny Georges on 2024-12-14.
//

#ifndef JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_IR_STRATEGY_H
#define JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-property-access-expression-node.h"

class ClassPropertyAccessExpressionIRStrategy {
public:
    IRClassPropertyAccessExpressionNode* generate(ASTClassPropertyAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType);
};

#endif //JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_IR_STRATEGY_H
