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
// Created by Johny Georges on 2024-05-13.
//

#include "class-method-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ClassMethodTypeSignatureStrategy::assign(std::shared_ptr<ASTClassMethodDeclarationNode> classMethodDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    std::optional<std::shared_ptr<TypeSignature>> returnType = {};
    if (classMethodDeclaration->getReturnType()) {
        strategyMap->assignTypeSignatureFor(classMethodDeclaration->getReturnType().value(), context, scope);
        returnType = classMethodDeclaration->getReturnType().value()->getTypeSignature()->convertToVariableTypeSignature();
    }

    strategyMap->assignTypeSignatureFor(classMethodDeclaration->getClassMethodDefinition()->getAccessModifier(), context, scope);
    strategyMap->assignTypeSignatureFor(classMethodDeclaration->getParameters(), context, scope);

    classMethodDeclaration->setTypeSignature(
            std::make_shared<ClassMethodTypeSignature>(
                classMethodDeclaration->getClassMethodDefinition()->getAccessModifier()->getAccessModifierTypeSignature(),
                classMethodDeclaration->getParameters()->getParameterListTypeSignature(),
                classMethodDeclaration->getClassMethodDefinition()->isStatic(),
                returnType
    ));
}