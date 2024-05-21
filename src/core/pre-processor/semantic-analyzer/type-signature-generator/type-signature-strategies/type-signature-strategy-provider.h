//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
#define JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H

#include <any>
#include "type-signature-strategy-map.h"
#include "../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../ast/ast-nodes/ast-node.h"
#include "../../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-declaration-node.h"
#include "../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-property-declaration-node.h"
#include "../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-constructor-declaration-node.h"
#include "../../../../ast/ast-nodes/ast-declaration-nodes/ast-class-method-declaration-node.h"
#include "../../../../ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"
#include "../../../../ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../../../ast/ast-nodes/ast-declaration-nodes/ast-function-declaration-node.h"
#include "../../../../ast/ast-nodes/ast-declaration-nodes/ast-procedure-declaration-node.h"
#include "../../../../type-signature/parameter-list-type-signature/parameter-list-type-signature.h"
#include "../../../../type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../../../../type-signature/function-type-signature/function-type-signature.h"
#include "../../../../type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../type-signature/class-type-signature/class-type-signature.h"
#include "../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"
#include "../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../../type-signature-lookup-table/literal-type-signature-lookup-table/literal-type-signature-lookup-table.h"


class TypeSignatureStrategyProvider {
private:
    LiteralTypeSignatureLookupTable _literalTypeSignatureLookupTable;
    TypeSignatureStrategyMap* _typeSignatureStrategyMap;
public:
    TypeSignatureStrategyProvider();
    TypeSignature*  getTypeSignatureForExpression(ASTExpressionNode* node, TypeSignatureLookupTable* scope);
    TypeSignature*  getTypeSignatureForType(ASTTypeNode* node, TypeSignatureLookupTable* scope);
    TypeSignature*  getTypeSignatureForBaseType(ASTTypeBaseNode* node, TypeSignatureLookupTable* scope);
    ClassPropertyTypeSignature*  getTypeSignatureForClassProperty(ASTClassPropertyDeclarationNode* node, TypeSignatureLookupTable* scope);
    ClassConstructorTypeSignature*  getTypeSignatureForClassConstructor(ASTClassConstructorDeclarationNode* node, TypeSignatureLookupTable* scope);
    ClassMethodTypeSignature*  getTypeSignatureForClassMethod(ASTClassMethodDeclarationNode* node, TypeSignatureLookupTable* scope);
    LiteralTypeSignature*  getTypeSignatureForEnumKeyValue(ASTEnumKeyValueNode* node);
    ParameterListItemTypeSignature*  getTypeSignatureForParameter(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope);
    ParameterListTypeSignature*  getTypeSignatureForParameterList(ASTFunctionParameterListNode* node, TypeSignatureLookupTable* scope);
    LiteralTypeSignature*  getTypeSignatureForLiteral(ASTLiteralNode* node);
    AccessModifierTypeSignature*  getTypeSignatureForAccessModifier(ASTAccessModifierNode* node);
    TypeSignature*  getTypeSignatureForDeclaration(ASTDeclarationNode* node, TypeSignatureLookupTable* scope);
};

#endif //JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
