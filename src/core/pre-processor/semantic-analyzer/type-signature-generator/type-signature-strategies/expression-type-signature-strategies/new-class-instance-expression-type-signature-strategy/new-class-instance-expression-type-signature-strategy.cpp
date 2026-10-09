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
// Created by Johny Georges on 2024-05-11.
//

#include "new-class-instance-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void NewClassInstanceExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTNewClassInstanceExpressionNode> newClassInstanceExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto moduleName = newClassInstanceExpression->getModuleName();
    auto typeSignature = moduleName
            ? typeSignatureLookupTable->find(moduleName.value(), newClassInstanceExpression->getClassName())
            : typeSignatureLookupTable->find(newClassInstanceExpression->getClassName());
    strategyMap->assignTypeSignatureFor(newClassInstanceExpression->getArguments(), context, typeSignatureLookupTable);
    if (typeSignature->typeSourceIs(CLASS_TYPE_SOURCE)) {
        auto classTypeSignature = std::dynamic_pointer_cast<ClassTypeSignature>(typeSignature);
        newClassInstanceExpression->setTypeSignature(
                std::make_shared<NewClassInstanceTypeSignature>(
                        classTypeSignature,
                        classTypeSignature->findConstructorForArguments(newClassInstanceExpression->getArguments()->getArgumentListTypeSignature()->getArgumentTypes()))
                );
        newClassInstanceExpression->getTypeSignature()->setModuleId(classTypeSignature->getModuleId());
        newClassInstanceExpression->getTypeSignature()->setId(newClassInstanceExpression->getClassName());
    } else {
        newClassInstanceExpression->setTypeSignature(std::make_shared<NewClassInstanceTypeSignature>());
    }
}