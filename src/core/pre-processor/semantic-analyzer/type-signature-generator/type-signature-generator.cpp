//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature-generator.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"

TypeSignatureGenerator::TypeSignatureGenerator(TypeSignatureStrategyProvider* typeSignatureStrategyProvider) {
    _typeSignatureStrategyProvider = typeSignatureStrategyProvider;
}

TypeSignature* TypeSignatureGenerator::generateInitialTypeSignatureForTypeDeclaration(ASTDeclarationNode* node) {
    switch (node->getNodeType()) {
        case AST_FUNCTION_DECLARATION_NODE:
            return new FunctionTypeSignature();
        case AST_PROCEDURE_DECLARATION_NODE:
            return new ProcedureTypeSignature();
        case AST_ENUM_DECLARATION_NODE:
            return new EnumTypeSignature();
        case AST_CLASS_DECLARATION_NODE:
            return new ClassTypeSignature();
        default:
            return new UnknownTypeSignature();
    }
}

void  TypeSignatureGenerator::assignTypeSignatureFor(ASTNode* node, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignTypeSignatureFor(node, scope);
}