//
// Created by Johny Georges on 2024-05-13.
//

#include "procedure-type-signature-strategy.h"
#include "../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ProcedureTypeSignatureStrategy::assign(ASTProcedureDeclarationNode* procedureDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto procedureScope = TypeSignatureLookupTable();
    procedureScope.inheritGlobalScope(scope);
    for (auto parameter : procedureDeclaration->getParameters()->getParameters()) {
        procedureScope.insert(parameter->getIdentifier()->getId(), parameter->getTypeSignature()->getTypeSignature());
    }
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getBlock(), &procedureScope);
}

void ProcedureTypeSignatureStrategy::assignInitial(ASTProcedureDeclarationNode* procedureDeclaration, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto procedureScope = TypeSignatureLookupTable();
    procedureScope.inheritGlobalScope(scope);
    strategyMap->assignTypeSignatureFor(procedureDeclaration->getParameters(), &procedureScope);
    procedureDeclaration->setTypeSignature(new ProcedureTypeSignature(
            procedureDeclaration->getParameters()->getTypeSignature()
    ));


    auto procedureName = procedureDeclaration->getId();
    procedureScope.insertGlobal(procedureName, procedureDeclaration->getTypeSignature()->convertToVariableTypeSignature());

    procedureDeclaration->setId(FunctionIdGenerator::generateFor(procedureDeclaration));
}