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
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-variable-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRStatementNode> VariableAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTVariableAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto isGlobal = scope->findGlobalVariable(node->getVariableAssignment()->getIdentifierNode()->getId()).has_value();
    auto irOperation = std::make_shared<IROperation>(IR_COPY_ASSIGNMENT_OP);
    if (isGlobal) {
        irOperation->markAsGlobal();
    }
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, irOperation);
    irExpression->markAsAssigned();
    return std::make_shared<IRVariableAssignmentStatementNode>(node, irExpression);
}