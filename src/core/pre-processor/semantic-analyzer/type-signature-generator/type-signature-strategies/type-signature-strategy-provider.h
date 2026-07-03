//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
#define JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H

#include <any>
#include <set>
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
#include "../../../../type-signature/enum-type-signature/enum-type-signature.h"
#include "../../../../type-signature/class-type-signature/class-type-signature.h"
#include "../../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"
#include "../../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"
#include "../../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"
#include "../../type-signature-lookup-table/literal-type-signature-lookup-table/literal-type-signature-lookup-table.h"
#include "../../../../ast/ast-nodes/ast-statement-nodes/ast-statement-node.h"
#include "../../../../type-signature/struct-type-signature/struct-type-signature.h"
#include "array-prototype-type-signature-map/array-prototype-type-signature-map.h"
#include "ref-prototype-type-signature-map/ref-prototype-type-signature-map.h"
#include "../type-signature-context.h"
#include "string-prototype-type-signature-map/string-prototype-type-signature-map.h"


class TypeSignatureStrategyProvider {
private:
    LiteralTypeSignatureLookupTable _literalTypeSignatureLookupTable;
    TypeSignatureStrategyMap* _typeSignatureStrategyMap;
    ArrayPrototypeTypeSignatureMap _arrayPrototypeSignatureMap;
    StringPrototypeTypeSignatureMap _stringPrototypeSignatureMap;
    RefPrototypeTypeSignatureMap _refPrototypeSignatureMap;
public:
    TypeSignatureStrategyProvider();
    void assignTypeSignatureFor(ASTNode* node, std::shared_ptr<TypeSignatureContext> context, std::optional<std::shared_ptr<TypeSignatureLookupTable>> scope = {});
    void assignInitialTypeSignatureFor(ASTNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope);
    void assignPostInitialTypeSignatureFor(ASTNode* node, std::shared_ptr<TypeSignatureContext> context, std::optional<std::shared_ptr<TypeSignatureLookupTable>> scope = {});
    ParameterListItemTypeSignature* generateLambdaExpressionScopeParameter(std::set<std::string>* capturedVariableIds);
    ParameterListItemTypeSignature* generateClassScopeParameter(ClassTypeSignature* classTypeSignature);
    std::optional<FunctionTypeSignature*> findArrayPrototypeTypeSignature(std::string id, TypeSignature* elementType);
    std::optional<FunctionTypeSignature*> findStringPrototypeTypeSignature(std::string id);
    std::optional<FunctionTypeSignature*> findRefPrototypeTypeSignature(std::string id, TypeSignature* elementType);
};

#endif //JETLANG_TYPE_SIGNATURE_STRATEGY_PROVIDER_H
