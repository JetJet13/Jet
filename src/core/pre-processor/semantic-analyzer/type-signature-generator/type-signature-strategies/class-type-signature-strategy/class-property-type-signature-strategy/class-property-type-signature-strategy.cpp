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

#include "class-property-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ClassPropertyTypeSignatureStrategy::assign(std::shared_ptr<ASTClassPropertyDeclarationNode> classPropertyDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {;
    std::shared_ptr<TypeSignature> classPropertyType = std::make_shared<UnknownTypeSignature>();
    if (classPropertyDeclaration->getInitializer()) {
        strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getInitializer().value(), context, scope);
        classPropertyType = classPropertyDeclaration->getInitializer().value()->getTypeSignature()->convertToVariableTypeSignature();
    } else if (classPropertyDeclaration->getType()) {
        strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getType().value(), context, scope);
        classPropertyType = classPropertyDeclaration->getType().value()->getTypeSignature();
    }

    strategyMap->assignTypeSignatureFor(classPropertyDeclaration->getAccessModifier(), context);
    classPropertyDeclaration->setTypeSignature(std::make_shared<ClassPropertyTypeSignature>(
        classPropertyDeclaration->getAccessModifier()->getAccessModifierTypeSignature(),
        classPropertyType->convertToVariableTypeSignature(),
        classPropertyDeclaration->isStatic(),
        classPropertyDeclaration->isConstant()
    ));
    classPropertyType->setKeyId(classPropertyDeclaration->getNormalizedPropertyName());
    classPropertyDeclaration->getTypeSignature()->setKeyId(classPropertyDeclaration->getNormalizedPropertyName());
}