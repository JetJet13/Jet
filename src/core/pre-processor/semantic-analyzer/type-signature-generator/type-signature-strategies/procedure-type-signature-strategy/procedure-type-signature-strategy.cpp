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

#include "procedure-type-signature-strategy.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ProcedureTypeSignatureStrategy::assign(std::shared_ptr<ASTProcedureDeclarationNode> procedureDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto procedureScope = std::make_shared<TypeSignatureLookupTable>();
    procedureScope->inheritGlobalScope(scope);
    for (auto parameter : procedureDeclaration->getParameters()->getParameters()) {
        procedureScope->insert(parameter->getIdentifier()->getId(), parameter->getParameterTypeSignature()->getTypeSignature());
    }
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getBlock(), context, procedureScope);
}

void ProcedureTypeSignatureStrategy::assignInitial(std::shared_ptr<ASTProcedureDeclarationNode> procedureDeclaration, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto procedureScope = std::make_shared<TypeSignatureLookupTable>();
    procedureScope->inheritGlobalScope(scope);
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getParameters(), context, procedureScope);
    procedureDeclaration->setTypeSignature(std::make_shared<ProcedureTypeSignature>(
        procedureDeclaration->getParameters()->getParameterListTypeSignature()
    ));
}