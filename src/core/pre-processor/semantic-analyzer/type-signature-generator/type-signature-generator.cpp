//
// Created by Johny Georges on 2024-04-30.
//

#include "type-signature-generator.h"
#include "../../../type-signature/module-type-signature/module-type-signature.h"

TypeSignatureGenerator::TypeSignatureGenerator(TypeSignatureStrategyProvider* typeSignatureStrategyProvider) {
    _typeSignatureStrategyProvider = typeSignatureStrategyProvider;
}

TypeSignature* TypeSignatureGenerator::generateInitialTypeSignatureForTypeDeclaration(ASTDeclarationNode* node) {
    switch (node->getNodeType()) {
        case AST_FUNCTION_DECLARATION_NODE:
            return (new FunctionTypeSignature())->setId(node->getId());
        case AST_PROCEDURE_DECLARATION_NODE:
            return (new ProcedureTypeSignature())->setId(node->getId());
        case AST_ENUM_DECLARATION_NODE:
            return (new EnumTypeSignature())->setId(node->getId());
        case AST_CLASS_DECLARATION_NODE:
            return (new ClassTypeSignature())->setId(node->getId());
        case AST_MODULE_DECLARATION_NODE:
            return (new ModuleTypeSignature())->setId(node->getId());
        case AST_INTERFACE_TYPE_DECLARATION_NODE:
            return (new InterfaceTypeSignature())->setId(node->getId());
        default:
            return (new UnknownTypeSignature())->setId(node->getId());
    }
}

void TypeSignatureGenerator::assignPartialTypeSignatureForTypeDeclaration(ASTDeclarationNode* node, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignPartialTypeSignatureFor(node, scope);
}

void  TypeSignatureGenerator::assignTypeSignatureFor(ASTNode* node, TypeSignatureLookupTable* scope) {
    _typeSignatureStrategyProvider->assignTypeSignatureFor(node, scope);
}