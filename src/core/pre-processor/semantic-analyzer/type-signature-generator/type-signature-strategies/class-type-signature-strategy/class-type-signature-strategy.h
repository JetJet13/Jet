//
// Created by Johny Georges on 2024-05-04.
//

#ifndef JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"
#include "../../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../type-signature-strategy-provider.h"
#include "../../../../../type-signature/class-type-signature/class-type-signature.h"

class ClassTypeSignatureStrategy {
private:
    void assignConstructorTypeSignatures(ASTClassDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
    void assignPropertyTypeSignatures(ASTClassDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
    void assignMethodTypeSignatures(ASTClassDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
    void assignConstructorBlocksTypeSignature(ASTClassDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
    void assignMethodBlocksTypeSignature(ASTClassDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, ClassTypeSignature* classTypeSignature, TypeSignatureStrategyProvider* strategyMap);
public:
    void assign(ASTClassDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
    void assignPostInitial(ASTClassDeclarationNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_CLASS_TYPE_SIGNATURE_STRATEGY_H
