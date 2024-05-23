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
#include "../../../../ast/ast-nodes/ast-statement-nodes/ast-statement-node.h"


class TypeSignatureStrategyProvider {
private:
    LiteralTypeSignatureLookupTable _literalTypeSignatureLookupTable;
    TypeSignatureStrategyMap* _typeSignatureStrategyMap;
public:
    TypeSignatureStrategyProvider();
    void assignTypeSignatureForExpression(ASTExpressionNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForType(ASTTypeNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForBaseType(ASTTypeBaseNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForClassProperty(ASTClassPropertyDeclarationNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForClassConstructor(ASTClassConstructorDeclarationNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForClassMethod(ASTClassMethodDeclarationNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForEnumKeyValue(ASTEnumKeyValueNode* node);
    void assignTypeSignatureForParameter(ASTFunctionParameterNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForParameterList(ASTFunctionParameterListNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForLiteral(ASTLiteralNode* node);
    void assignTypeSignatureForAccessModifier(ASTAccessModifierNode* node);
    void assignTypeSignatureForDeclaration(ASTDeclarationNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForBlockContents(ASTScopedBlockNode* node, TypeSignatureLookupTable* scope);
    void assignTypeSignatureForStatement(ASTStatementNode* node, TypeSignatureLookupTable* scope);

};

#endif //JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
