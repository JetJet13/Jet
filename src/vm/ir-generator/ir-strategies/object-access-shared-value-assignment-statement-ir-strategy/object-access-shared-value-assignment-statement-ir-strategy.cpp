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
// Created by Johny Georges on 2026-06-27.
//

#include "object-access-shared-value-assignment-statement-ir-strategy.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-object-access-shared-value-assignment-statement-node.h"
#include "../../../ir-nodes/ir-statement-nodes/ir-class-static-property-shared-value-assignment-statement-node.h"

std::shared_ptr<IRStatementNode> ObjectAccessSharedValueAssignmentStatementIRStrategy::generate(std::shared_ptr<ASTObjectAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext) {
    auto irExpression = irGenerator->generateFor(node->getExpression(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    irExpression->markAsAssigned();
    if (node->getObjectAccessAssignment()->getObjectAccess()->getSource()->getSource()->getTypeSignature()->typeSourceIs(CLASS_TYPE_SOURCE)) {
        return std::make_shared<IRClassStaticPropertySharedValueAssignmentStatementNode>(
                node,
                std::dynamic_pointer_cast<IRClassStaticPropertyAccessExpressionNode>(irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
                irExpression
        );
    }
    return std::make_shared<IRObjectAccessSharedValueAssignmentStatementNode>(
            node,
            std::dynamic_pointer_cast<IRObjectAccessExpressionNode>(irGenerator->generateFor(node->getObjectAccessAssignment()->getObjectAccess(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP))),
            irExpression
    );
}