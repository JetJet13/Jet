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
// Created by Johny Georges on 2024-05-23.
//

#include "class-property-assignment-statement-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"

void ClassPropertyAssignmentStatementTypeSignatureStrategy::assign(std::shared_ptr<ASTClassPropertyAssignmentStatementNode> classPropertyAssignmentStatementNode, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(classPropertyAssignmentStatementNode->getExpression(), context, scope);
    auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(scope->find(
            classPropertyAssignmentStatementNode
                    ->getPropertyAssignment()
                    ->getClassAccess()
                    ->getThis()
                    ->getId()
    ));

    if (!classTypeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        classPropertyAssignmentStatementNode
        ->getPropertyAssignment()
        ->setTypeSignature(std::make_shared<InvalidTypeSignature>());
    }

    auto propertyTypeSignature = classTypeSignature->getInstanceProperties()->find(
            classPropertyAssignmentStatementNode
                    ->getPropertyAssignment()
                    ->getProperty()
                    ->getId()
    );
    if (propertyTypeSignature) {
        classPropertyAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(propertyTypeSignature.value()->getType());
        return;
    }
    classPropertyAssignmentStatementNode->getPropertyAssignment()->setTypeSignature(
            std::make_shared<InvalidTypeSignature>()
    );
}