// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"
#include "../../../ir-util-functions/array-access-ir-function/array-access-ir-function.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRArrayAccessExpressionNode> ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(std::shared_ptr<ASTArrayAccessExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto sourceValue = irGenerator->generateFor(node->getSource(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto indexValue = irGenerator->generateFor(node->getIndex()->getIndex(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    return std::make_shared<IRArrayAccessExpressionNode>(node, sourceValue, indexValue, irType, sourceAllocation);
}