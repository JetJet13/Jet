//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
#define JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H

#include "type-signature-strategy-map.h"
#include "../../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../token/token-table.h"
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


class TypeSignatureStrategyProvider {
private:
    TypeSignatureStrategyMap* _typeSignatureStrategyMap;
    TypeSignatureLookupTable* _typeSignatureLookupTable;
    TokenTable* _tokenTable;
public:
    explicit TypeSignatureStrategyProvider(TypeSignatureLookupTable* typeSignatureLookupTable, TokenTable* tokenTable);
    TypeSignature*  getTypeSignatureForExpression(ASTExpressionNode* node);
    TypeSignature*  getTypeSignatureForType(ASTTypeNode* node);
    TypeSignature*  getTypeSignatureForBaseType(ASTTypeBaseNode* node);
    TypeSignature*  getTypeSignatureForVariable(ASTVariableDeclarationNode* node);
    ClassTypeSignature*  getTypeSignatureForClass(ASTClassDeclarationNode* node);
    ClassPropertyTypeSignature*  getTypeSignatureForClassProperty(ASTClassPropertyDeclarationNode* node);
    ClassConstructorTypeSignature*  getTypeSignatureForClassConstructor(ASTClassConstructorDeclarationNode* node);
    ClassMethodTypeSignature*  getTypeSignatureForClassMethod(ASTClassMethodDeclarationNode* node);
    EnumTypeSignature*  getTypeSignatureForEnum(ASTEnumDeclarationNode* node);
    LiteralTypeSignature*  getTypeSignatureForEnumKeyValue(ASTEnumKeyValueNode* node);
    FunctionTypeSignature*  getTypeSignatureForFunction(ASTFunctionDeclarationNode* node);
    ProcedureTypeSignature*  getTypeSignatureForProcedure(ASTProcedureDeclarationNode* node);
    ParameterListItemTypeSignature*  getTypeSignatureForParameter(ASTFunctionParameterNode* node);
    ParameterListTypeSignature*  getTypeSignatureForParameterList(ASTFunctionParameterListNode* node);
    LiteralTypeSignature*  getTypeSignatureForLiteral(ASTLiteralNode* node);
    AccessModifierTypeSignature*  getTypeSignatureForAccessModifier(ASTAccessModifierNode* node);
    TypeSignature*  getTypeSignatureForDeclaration(ASTDeclarationNode* node);
};

#endif //JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
