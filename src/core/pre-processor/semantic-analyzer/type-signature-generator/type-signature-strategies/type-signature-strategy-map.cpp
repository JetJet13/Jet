//
// Created by Johny Georges on 2024-05-06.
//

#include "type-signature-strategy-map.h"
#include "type-type-signature-strategy/type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/primitive-type-type-signature-strategy/primitive-type-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-access-expression-type-signature-strategy/array-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-access-invocation-expression-type-signature-strategy/array-access-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-expression-type-signature-strategy/array-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/binary-expression-type-signature-strategy/binary-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/concat-expression-type-signature-strategy/concat-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/class-method-invocation-expression-type-signature-strategy/class-method-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/class-property-expression-type-signature-strategy/class-property-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/curry-expression-type-signature-strategy/curry-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/function-invocation-expression-type-signature-strategy/function-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/function-return-expression-type-signature-strategy/function-return-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/identifier-expression-type-signature-strategy/identifier-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-expression-type-signature-strategy/lambda-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-with-fat-arrow-expression-type-signature-strategy/lambda-with-fat-arrow-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/lambda-return-expression-type-signature-strategy/lambda-return-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/literal-expression-type-signature-strategy/literal-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/logical-expression-type-signature-strategy/logical-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/new-class-instance-expression-type-signature-strategy/new-class-instance-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/object-access-expression-type-signature-strategy/object-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/struct-expression-type-signature-strategy/struct-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/this-expression-type-signature-strategy/this-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/tuple-access-expression-type-signature-strategy/tuple-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/tuple-access-invocation-expression-type-signature-strategy/tuple-access-invocation-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/tuple-expression-type-signature-strategy/tuple-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/unary-expression-type-signature-strategy/unary-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/module-access-expression-type-signature-strategy/module-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/share-expression-type-signature-strategy/share-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/ref-expression-type-signature-strategy/ref-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/dref-expression-type-signature-strategy/dref-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/struct-type-type-signature-strategy/struct-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/tuple-type-type-signature-strategy/tuple-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/ref-type-type-signature-strategy/ref-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/shared-type-type-signature-strategy/shared-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/module-type-type-signature-strategy/module-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/this-type-type-signature-strategy/this-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/lambda-type-type-signature-strategy/lambda-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/void-type-type-signature-strategy/void-type-type-signature-strategy.h"
#include "lambda-expression-scope-parameter-type-signature-strategy/lambda-expression-scope-parameter-type-signature-strategy.h"
#include "enum-type-signature-strategy/enum-key-value-type-signature-strategy/enum-key-value-type-signature-strategy.h"
#include "enum-type-signature-strategy/enum-type-signature-strategy.h"
#include "variable-type-signature-strategy/variable-type-signature-strategy.h"
#include "class-type-signature-strategy/class-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-type-signature-strategy/class-property-type-signature-strategy.h"
#include "class-type-signature-strategy/class-constructor-type-signature-strategy/class-constructor-type-signature-strategy.h"
#include "class-type-signature-strategy/class-method-type-signature-strategy/class-method-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-assignment-statement-type-signature-strategy/class-property-assignment-statement-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-ref-value-assignment-statement-type-signature-strategy/class-property-ref-value-assignment-statement-type-signature-strategy.h"
#include "class-type-signature-strategy/class-scope-parameter-type-signature-strategy/class-scope-parameter-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-item-type-signature-strategy/parameter-list-item-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-type-singature-strategy.h"
#include "function-type-signature-strategy/function-type-signature-strategy.h"
#include "procedure-type-signature-strategy/procedure-type-signature-strategy.h"
#include "literal-type-signature-strategy/literal-type-signature-strategy.h"
#include "access-modifier-type-signature-strategy/access-modifier-type-signature-strategy.h"
#include "variable-assignment-statement-type-signature-strategy/variable-assignment-statement-type-signature-strategy.h"
#include "ref-value-assignment-statement-type-signature-strategy/ref-value-assignment-statement-type-signature-strategy.h"
#include "block-type-signature-strategy/block-type-signature-strategy.h"
#include "if-statement-type-signature-strategy/if-statement-type-signature-strategy.h"
#include "try-statement-type-signature-strategy/try-statement-type-signature-strategy.h"
#include "while-statement-type-signature-strategy/while-statement-type-signature-strategy.h"
#include "for-in-statement-type-signature-strategy/for-in-statement-type-signature-strategy.h"
#include "condition-type-signature-strategy/condition-type-signature-strategy.h"
#include "expression-statement-type-signature-strategy/expression-statement-type-signature-strategy.h"
#include "import-type-signature-strategy/import-type-signature-strategy.h"
#include "module-type-signature-strategy/module-type-signature-strategy.h"
#include "interface-type-signature-strategy/interface-type-signature-strategy.h"
#include "interface-type-signature-strategy/interface-property-type-signature-strategy/interface-property-type-signature-strategy.h"
#include "custom-type-declaration-type-signature-strategy/custom-type-declaration-type-signature-strategy.h"
#include "argument-list-type-signature-strategy/argument-list-type-signature-strategy.h"
#include "expression-type-signature-strategies/object-access-invocation-expression-type-signature-strategy/object-access-invocation-expression-type-signature-strategy.h"
#include "array-access-assignment-statement-type-signature-strategy/array-access-assignment-statement-type-signature-strategy.h"
#include "array-access-ref-assignment-statement-type-signature-strategy/array-access-ref-assignment-statement-type-signature-strategy.h"
#include "object-access-assignment-statement-type-signature-strategy/object-access-assignment-statement-type-signature-strategy.h"
#include "object-access-ref-assignment-statement-type-signature-strategy/object-access-ref-assignment-statement-type-signature-strategy.h"
#include "tuple-access-assignment-statement-type-signature-strategy/tuple-access-assignment-statement-type-signature-strategy.h"
#include "tuple-access-ref-assignment-statement-type-signature-strategy/tuple-access-ref-assignment-statement-type-signature-strategy.h"
#include "module-access-assignment-statement-type-signature-strategy/module-access-assignment-statement-type-signature-strategy.h"
#include "module-access-ref-assignment-statement-type-signature-strategy/module-access-ref-assignment-statement-type-signature-strategy.h"

TypeSignatureStrategyMap::TypeSignatureStrategyMap() {
    _argumentListTypeSignatureStrategy = std::make_shared<ArgumentListTypeSignatureStrategy>();
    _arrayAccessExpressionTypeSignatureStrategy = std::make_shared<ArrayAccessExpressionTypeSignatureStrategy>();
    _arrayAccessInvocationExpressionTypeSignatureStrategy = std::make_shared<ArrayAccessInvocationExpressionTypeSignatureStrategy>();
    _arrayExpressionTypeSignatureStrategy = std::make_shared<ArrayExpressionTypeSignatureStrategy>();
    _binaryExpressionTypeSignatureStrategy = std::make_shared<BinaryExpressionTypeSignatureStrategy>();
    _concatExpressionTypeSignatureStrategy = std::make_shared<ConcatExpressionTypeSignatureStrategy>();
    _classMethodInvocationExpressionTypeSignatureStrategy = std::make_shared<ClassMethodInvocationExpressionTypeSignatureStrategy>();
    _classPropertyAccessExpressionTypeSignatureStrategy = std::make_shared<ClassPropertyAccessExpressionTypeSignatureStrategy>();
    _classPropertyAssignmentStatementTypeSignatureStrategy = std::make_shared<ClassPropertyAssignmentStatementTypeSignatureStrategy>();
    _classPropertyRefValueAssignmentStatementTypeSignatureStrategy = std::make_shared<ClassPropertyRefValueAssignmentStatementTypeSignatureStrategy>();
    _curryExpressionTypeSignatureStrategy = std::make_shared<CurryExpressionTypeSignatureStrategy>();
    _functionInvocationExpressionTypeSignatureStrategy = std::make_shared<FunctionInvocationExpressionTypeSignatureStrategy>();
    _functionReturnExpressionTypeSignatureStrategy = std::make_shared<FunctionReturnExpressionTypeSignatureStrategy>();
    _identifierExpressionTypeSignatureStrategy = std::make_shared<IdentifierExpressionTypeSignatureStrategy>();
    _lambdaExpressionTypeSignatureStrategy = std::make_shared<LambdaExpressionTypeSignatureStrategy>();
    _lambdaWithFatArrowExpressionTypeSignatureStrategy = std::make_shared<LambdaWithFatArrowExpressionTypeSignatureStrategy>();
    _lambdaReturnExpressionTypeSignatureStrategy = std::make_shared<LambdaReturnExpressionTypeSignatureStrategy>();
    _literalExpressionTypeSignatureStrategy = std::make_shared<LiteralExpressionTypeSignatureStrategy>();
    _logicalExpressionTypeSignatureStrategy = std::make_shared<LogicalExpressionTypeSignatureStrategy>();
    _newClassInstanceExpressionTypeSignatureStrategy = std::make_shared<NewClassInstanceExpressionTypeSignatureStrategy>();
    _objectAccessExpressionTypeSignatureStrategy = std::make_shared<ObjectAccessExpressionTypeSignatureStrategy>();
    _objectAccessInvocationExpressionTypeSignatureStrategy = std::make_shared<ObjectAccessInvocationExpressionTypeSignatureStrategy>();
    _structExpressionTypeSignatureStrategy = std::make_shared<StructExpressionTypeSignatureStrategy>();
    _thisExpressionTypeSignatureStrategy = std::make_shared<ThisExpressionTypeSignatureStrategy>();
    _tupleAccessExpressionTypeSignatureStrategy = std::make_shared<TupleAccessExpressionTypeSignatureStrategy>();
    _tupleAccessInvocationExpressionTypeSignatureStrategy = std::make_shared<TupleAccessInvocationExpressionTypeSignatureStrategy>();
    _tupleExpressionTypeSignatureStrategy = std::make_shared<TupleExpressionTypeSignatureStrategy>();
    _unaryExpressionTypeSignatureStrategy = std::make_shared<UnaryExpressionTypeSignatureStrategy>();
    _moduleAccessExpressionTypeSignatureStrategy = std::make_shared<ModuleAccessExpressionTypeSignatureStrategy>();
    _shareExpressionTypeSignatureStrategy = std::make_shared<ShareExpressionTypeSignatureStrategy>();
    _refExpressionTypeSignatureStrategy = std::make_shared<RefExpressionTypeSignatureStrategy>();
    _drefExpressionTypeSignatureStrategy = std::make_shared<DrefExpressionTypeSignatureStrategy>();
    _lambdaExpressionScopeParameterTypeSignatureStrategy = std::make_shared<LambdaExpressionScopeParameterTypeSignatureStrategy>();
    _classScopeParameterTypeSignatureStrategy = std::make_shared<ClassScopeParameterTypeSignatureStrategy>();
    _typeTypeSignatureStrategy = std::make_shared<TypeTypeSignatureStrategy>();
    _primitiveTypeTypeSignatureStrategy = std::make_shared<PrimitiveTypeTypeSignatureStrategy>();
    _customTypeTypeSignatureStrategy = std::make_shared<CustomTypeTypeSignatureStrategy>();
    _arrayTypeTypeSignatureStrategy = std::make_shared<ArrayTypeTypeSignatureStrategy>();
    _structTypeTypeSignatureStrategy = std::make_shared<StructTypeTypeSignatureStrategy>();
    _tupleTypeTypeSignatureStrategy = std::make_shared<TupleTypeTypeSignatureStrategy>();
    _refTypeTypeSignatureStrategy = std::make_shared<RefTypeTypeSignatureStrategy>();
    _sharedTypeTypeSignatureStrategy = std::make_shared<SharedTypeTypeSignatureStrategy>();
    _moduleTypeTypeSignatureStrategy = std::make_shared<ModuleTypeTypeSignatureStrategy>();
    _lambdaTypeTypeSignatureStrategy = std::make_shared<LambdaTypeTypeSignatureStrategy>();
    _voidTypeTypeSignatureStrategy = std::make_shared<VoidTypeTypeSignatureStrategy>();
    _thisTypeTypeSignatureStrategy = std::make_shared<ThisTypeTypeSignatureStrategy>();
    _enumKeyValueTypeSignatureStrategy = std::make_shared<EnumKeyValueTypeSignatureStrategy>();
    _enumTypeSignatureStrategy = std::make_shared<EnumTypeSignatureStrategy>();
    _variableTypeSignatureStrategy = std::make_shared<VariableTypeSignatureStrategy>();
    _classTypeSignatureStrategy = std::make_shared<ClassTypeSignatureStrategy>();
    _classPropertyTypeSignatureStrategy = std::make_shared<ClassPropertyTypeSignatureStrategy>();
    _classConstructorTypeSignatureStrategy = std::make_shared<ClassConstructorTypeSignatureStrategy>();
    _classMethodTypeSignatureStrategy = std::make_shared<ClassMethodTypeSignatureStrategy>();
    _parameterListItemTypeSignatureStrategy = std::make_shared<ParameterListItemTypeSignatureStrategy>();
    _parameterListTypeSignatureStrategy = std::make_shared<ParameterListTypeSignatureStrategy>();
    _functionTypeSignatureStrategy = std::make_shared<FunctionTypeSignatureStrategy>();
    _procedureTypeSignatureStrategy = std::make_shared<ProcedureTypeSignatureStrategy>();
    _literalTypeSignatureStrategy = std::make_shared<LiteralTypeSignatureStrategy>();
    _accessModifierTypeSignatureStrategy = std::make_shared<AccessModifierTypeSignatureStrategy>();
    _variableAssignmentStatementTypeSignatureStrategy = std::make_shared<VariableAssignmentStatementTypeSignatureStrategy>();
    _refValueAssignmentStatementTypeSignatureStrategy = std::make_shared<RefValueAssignmentStatementTypeSignatureStrategy>();
    _blockTypeSignatureStrategy = std::make_shared<BlockTypeSignatureStrategy>();
    _expressionStatementTypeSignatureStrategy = std::make_shared<ExpressionStatementTypeSignatureStrategy>();
    _conditionTypeSignatureStrategy = std::make_shared<ConditionTypeSignatureStrategy>();
    _forStatementTypeSignatureStrategy = std::make_shared<ForInStatementTypeSignatureStrategy>();
    _whileStatementTypeSignatureStrategy = std::make_shared<WhileStatementTypeSignatureStrategy>();
    _tryStatementTypeSignatureStrategy = std::make_shared<TryStatementTypeSignatureStrategy>();
    _ifStatementTypeSignatureStrategy = std::make_shared<IfStatementTypeSignatureStrategy>();
    _importTypeSignatureStrategy = std::make_shared<ImportTypeSignatureStrategy>();
    _moduleTypeSignatureStrategy = std::make_shared<ModuleTypeSignatureStrategy>();
    _interfaceTypeSignatureStrategy = std::make_shared<InterfaceTypeSignatureStrategy>();
    _interfacePropertyTypeSignatureStrategy = std::make_shared<InterfacePropertyTypeSignatureStrategy>();
    _customTypeDeclarationTypeSignatureStrategy = std::make_shared<CustomTypeDeclarationTypeSignatureStrategy>();
    _arrayAccessAssignmentStatementTypeSignatureStrategy = std::make_shared<ArrayAccessAssignmentStatementTypeSignatureStrategy>();
    _arrayAccessRefAssignmentStatementTypeSignatureStrategy = std::make_shared<ArrayAccessRefAssignmentStatementTypeSignatureStrategy>();
    _objectAccessAssignmentStatementTypeSignatureStrategy = std::make_shared<ObjectAccessAssignmentStatementTypeSignatureStrategy>();
    _objectAccessRefAssignmentStatementTypeSignatureStrategy = std::make_shared<ObjectAccessRefAssignmentStatementTypeSignatureStrategy>();
    _tupleAccessAssignmentStatementTypeSignatureStrategy = std::make_shared<TupleAccessAssignmentStatementTypeSignatureStrategy>();
    _tupleAccessRefAssignmentStatementTypeSignatureStrategy = std::make_shared<TupleAccessRefAssignmentStatementTypeSignatureStrategy>();
    _moduleAccessAssignmentStatementTypeSignatureStrategy = std::make_shared<ModuleAccessAssignmentStatementTypeSignatureStrategy>();
    _moduleAccessRefAssignmentStatementTypeSignatureStrategy = std::make_shared<ModuleAccessRefAssignmentStatementTypeSignatureStrategy>();
}

std::shared_ptr<ArgumentListTypeSignatureStrategy> TypeSignatureStrategyMap::getArgumentListTypeSignatureStrategy() {
    return _argumentListTypeSignatureStrategy;
}

std::shared_ptr<ArrayAccessExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getArrayAccessExpressionTypeSignatureStrategy() {
    return _arrayAccessExpressionTypeSignatureStrategy;
}

std::shared_ptr<ArrayAccessInvocationExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getArrayAccessInvocationExpressionTypeSignatureStrategy() {
    return _arrayAccessInvocationExpressionTypeSignatureStrategy;
}

std::shared_ptr<ArrayExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getArrayExpressionTypeSignatureStrategy() {
    return _arrayExpressionTypeSignatureStrategy;
}

std::shared_ptr<BinaryExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getBinaryExpressionTypeSignatureStrategy() {
    return _binaryExpressionTypeSignatureStrategy;
}

std::shared_ptr<ConcatExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getConcatExpressionTypeSignatureStrategy() {
    return _concatExpressionTypeSignatureStrategy;
}

std::shared_ptr<ClassMethodInvocationExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getClassMethodInvocationExpressionTypeSignatureStrategy() {
    return _classMethodInvocationExpressionTypeSignatureStrategy;
}

std::shared_ptr<ClassPropertyAccessExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getClassPropertyAccessExpressionTypeSignatureStrategy() {
    return _classPropertyAccessExpressionTypeSignatureStrategy;
}

std::shared_ptr<ClassPropertyRefValueAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getClassPropertyRefValueAssignmentStatementTypeSignatureStrategy() {
    return _classPropertyRefValueAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<ClassPropertyAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getClassPropertyAssignmentStatementTypeSignatureStrategy() {
    return _classPropertyAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<CurryExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getCurryExpressionTypeSignatureStrategy() {
    return _curryExpressionTypeSignatureStrategy;
}

std::shared_ptr<FunctionInvocationExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getFunctionInvocationExpressionTypeSignatureStrategy() {
    return _functionInvocationExpressionTypeSignatureStrategy;
}

std::shared_ptr<FunctionReturnExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getFunctionReturnExpressionTypeSignatureStrategy() {
    return _functionReturnExpressionTypeSignatureStrategy;
}

std::shared_ptr<IdentifierExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getIdentifierExpressionTypeSignatureStrategy() {
    return _identifierExpressionTypeSignatureStrategy;
}

std::shared_ptr<LambdaExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getLambdaExpressionTypeSignatureStrategy() {
    return _lambdaExpressionTypeSignatureStrategy;
}

std::shared_ptr<LambdaWithFatArrowExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getLambdaWithFatArrowExpressionTypeSignatureStrategy() {
    return _lambdaWithFatArrowExpressionTypeSignatureStrategy;
}

std::shared_ptr<LambdaReturnExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getLambdaReturnExpressionTypeSignatureStrategy() {
    return _lambdaReturnExpressionTypeSignatureStrategy;
}

std::shared_ptr<LiteralExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getLiteralExpressionTypeSignatureStrategy() {
    return _literalExpressionTypeSignatureStrategy;
}

std::shared_ptr<LogicalExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getLogicalExpressionTypeSignatureStrategy() {
    return _logicalExpressionTypeSignatureStrategy;
}

std::shared_ptr<NewClassInstanceExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getNewClassInstanceExpressionTypeSignatureStrategy() {
    return _newClassInstanceExpressionTypeSignatureStrategy;
}

std::shared_ptr<ObjectAccessExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getObjectAccessExpressionTypeSignatureStrategy() {
    return _objectAccessExpressionTypeSignatureStrategy;
}

std::shared_ptr<ObjectAccessInvocationExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getObjectAccessInvocationExpressionTypeSignatureStrategy() {
    return _objectAccessInvocationExpressionTypeSignatureStrategy;
}

std::shared_ptr<StructExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getStructExpressionTypeSignatureStrategy() {
    return _structExpressionTypeSignatureStrategy;
}

std::shared_ptr<ThisExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getThisExpressionTypeSignatureStrategy() {
    return _thisExpressionTypeSignatureStrategy;
}

std::shared_ptr<TupleAccessExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getTupleAccessExpressionTypeSignatureStrategy() {
    return _tupleAccessExpressionTypeSignatureStrategy;
}

std::shared_ptr<TupleAccessInvocationExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getTupleAccessInvocationExpressionTypeSignatureStrategy() {
    return _tupleAccessInvocationExpressionTypeSignatureStrategy;
}

std::shared_ptr<TupleExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getTupleExpressionTypeSignatureStrategy() {
    return _tupleExpressionTypeSignatureStrategy;
}

std::shared_ptr<UnaryExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getUnaryExpressionTypeSignatureStrategy() {
    return _unaryExpressionTypeSignatureStrategy;
}

std::shared_ptr<ModuleAccessExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getModuleAccessExpressionTypeSignatureStrategy() {
    return _moduleAccessExpressionTypeSignatureStrategy;
}

std::shared_ptr<ShareExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getShareExpressionTypeSignatureStrategy() {
    return _shareExpressionTypeSignatureStrategy;
}

std::shared_ptr<RefExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getRefExpressionTypeSignatureStrategy() {
    return _refExpressionTypeSignatureStrategy;
}

std::shared_ptr<DrefExpressionTypeSignatureStrategy> TypeSignatureStrategyMap::getDrefExpressionTypeSignatureStrategy() {
    return _drefExpressionTypeSignatureStrategy;
}

std::shared_ptr<LambdaExpressionScopeParameterTypeSignatureStrategy> TypeSignatureStrategyMap::getLambdaExpressionScopeParameterTypeSignatureStrategy() {
    return _lambdaExpressionScopeParameterTypeSignatureStrategy;
}

std::shared_ptr<ClassScopeParameterTypeSignatureStrategy> TypeSignatureStrategyMap::getClassScopeParameterTypeSignatureStrategy() {
    return _classScopeParameterTypeSignatureStrategy;
}

std::shared_ptr<TypeTypeSignatureStrategy> TypeSignatureStrategyMap::getTypeTypeSignatureStrategy() {
    return _typeTypeSignatureStrategy;
}

std::shared_ptr<PrimitiveTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getPrimitiveTypeTypeSignatureStrategy() {
    return _primitiveTypeTypeSignatureStrategy;
}

std::shared_ptr<CustomTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getCustomTypeTypeSignatureStrategy() {
    return _customTypeTypeSignatureStrategy;
}

std::shared_ptr<ArrayTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getArrayTypeTypeSignatureStrategy() {
    return _arrayTypeTypeSignatureStrategy;
}

std::shared_ptr<StructTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getStructTypeTypeSignatureStrategy() {
    return _structTypeTypeSignatureStrategy;
}

std::shared_ptr<TupleTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getTupleTypeTypeSignatureStrategy() {
    return _tupleTypeTypeSignatureStrategy;
}

std::shared_ptr<RefTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getRefTypeTypeSignatureStrategy() {
    return _refTypeTypeSignatureStrategy;
}

std::shared_ptr<SharedTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getSharedTypeTypeSignatureStrategy() {
    return _sharedTypeTypeSignatureStrategy;
}

std::shared_ptr<ModuleTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getModuleTypeTypeSignatureStrategy() {
    return _moduleTypeTypeSignatureStrategy;
}

std::shared_ptr<LambdaTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getLambdaTypeTypeSignatureStrategy() {
    return _lambdaTypeTypeSignatureStrategy;
}

std::shared_ptr<VoidTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getVoidTypeTypeSignatureStrategy() {
    return _voidTypeTypeSignatureStrategy;
}

std::shared_ptr<ThisTypeTypeSignatureStrategy> TypeSignatureStrategyMap::getThisTypeTypeSignatureStrategy() {
    return _thisTypeTypeSignatureStrategy;
}

std::shared_ptr<EnumKeyValueTypeSignatureStrategy> TypeSignatureStrategyMap::getEnumKeyValueTypeSignatureStrategy() {
    return _enumKeyValueTypeSignatureStrategy;
}

std::shared_ptr<EnumTypeSignatureStrategy> TypeSignatureStrategyMap::getEnumTypeSignatureStrategy() {
    return _enumTypeSignatureStrategy;
}

std::shared_ptr<VariableTypeSignatureStrategy> TypeSignatureStrategyMap::getVariableTypeSignatureStrategy() {
    return _variableTypeSignatureStrategy;
}

std::shared_ptr<ClassTypeSignatureStrategy> TypeSignatureStrategyMap::getClassTypeSignatureStrategy() {
    return _classTypeSignatureStrategy;
}

std::shared_ptr<ClassPropertyTypeSignatureStrategy> TypeSignatureStrategyMap::getClassPropertyTypeSignatureStrategy() {
    return _classPropertyTypeSignatureStrategy;
}

std::shared_ptr<ClassConstructorTypeSignatureStrategy> TypeSignatureStrategyMap::getClassConstructorTypeSignatureStrategy() {
    return _classConstructorTypeSignatureStrategy;
}

std::shared_ptr<ClassMethodTypeSignatureStrategy> TypeSignatureStrategyMap::getClassMethodTypeSignatureStrategy() {
    return _classMethodTypeSignatureStrategy;
}

std::shared_ptr<ParameterListItemTypeSignatureStrategy> TypeSignatureStrategyMap::getParameterListItemTypeSignatureStrategy() {
    return _parameterListItemTypeSignatureStrategy;
}

std::shared_ptr<ParameterListTypeSignatureStrategy> TypeSignatureStrategyMap::getParameterListTypeSignatureStrategy() {
    return _parameterListTypeSignatureStrategy;
}

std::shared_ptr<FunctionTypeSignatureStrategy> TypeSignatureStrategyMap::getFunctionTypeSignatureStrategy() {
    return _functionTypeSignatureStrategy;
}

std::shared_ptr<ProcedureTypeSignatureStrategy> TypeSignatureStrategyMap::getProcedureTypeSignatureStrategy() {
    return _procedureTypeSignatureStrategy;
}

std::shared_ptr<LiteralTypeSignatureStrategy> TypeSignatureStrategyMap::getLiteralTypeSignatureStrategy() {
    return _literalTypeSignatureStrategy;
}

std::shared_ptr<AccessModifierTypeSignatureStrategy> TypeSignatureStrategyMap::getAccessModifierTypeSignatureStrategy() {
    return _accessModifierTypeSignatureStrategy;
}

std::shared_ptr<VariableAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getVariableAssignmentStatementTypeSignatureStrategy() {
    return _variableAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<RefValueAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getRefValueAssignmentStatementTypeSignatureStrategy() {
    return _refValueAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<ArrayAccessAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getArrayAccessAssignmentStatementTypeSignatureStrategy() {
    return _arrayAccessAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<ArrayAccessRefAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getArrayAccessRefAssignmentStatementTypeSignatureStrategy() {
    return _arrayAccessRefAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<ObjectAccessAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getObjectAccessAssignmentStatementTypeSignatureStrategy() {
    return _objectAccessAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<ObjectAccessRefAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getObjectAccessRefAssignmentStatementTypeSignatureStrategy() {
    return _objectAccessRefAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<TupleAccessAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getTupleAccessAssignmentStatementTypeSignatureStrategy() {
    return _tupleAccessAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<TupleAccessRefAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getTupleAccessRefAssignmentStatementTypeSignatureStrategy() {
    return _tupleAccessRefAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<ModuleAccessAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getModuleAccessAssignmentStatementTypeSignatureStrategy() {
    return _moduleAccessAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<ModuleAccessRefAssignmentStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getModuleAccessRefAssignmentStatementTypeSignatureStrategy() {
    return _moduleAccessRefAssignmentStatementTypeSignatureStrategy;
}

std::shared_ptr<BlockTypeSignatureStrategy> TypeSignatureStrategyMap::getBlockTypeSignatureStrategy() {
    return _blockTypeSignatureStrategy;
}

std::shared_ptr<ExpressionStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getExpressionStatementTypeSignatureStrategy() {
    return _expressionStatementTypeSignatureStrategy;
}

std::shared_ptr<ConditionTypeSignatureStrategy> TypeSignatureStrategyMap::getConditionTypeSignatureStrategy() {
    return _conditionTypeSignatureStrategy;
}

std::shared_ptr<ForInStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getForStatementTypeSignatureStrategy() {
    return _forStatementTypeSignatureStrategy;
}

std::shared_ptr<WhileStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getWhileStatementTypeSignatureStrategy() {
    return _whileStatementTypeSignatureStrategy;
}

std::shared_ptr<TryStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getTryStatementTypeSignatureStrategy() {
    return _tryStatementTypeSignatureStrategy;
}

std::shared_ptr<IfStatementTypeSignatureStrategy> TypeSignatureStrategyMap::getIfStatementTypeSignatureStrategy() {
    return _ifStatementTypeSignatureStrategy;
}

std::shared_ptr<ImportTypeSignatureStrategy> TypeSignatureStrategyMap::getImportTypeSignatureStrategy() {
    return _importTypeSignatureStrategy;
}

std::shared_ptr<ModuleTypeSignatureStrategy> TypeSignatureStrategyMap::getModuleTypeSignatureStrategy() {
    return _moduleTypeSignatureStrategy;
}

std::shared_ptr<InterfaceTypeSignatureStrategy> TypeSignatureStrategyMap::getInterfaceTypeSignatureStrategy() {
    return _interfaceTypeSignatureStrategy;
}

std::shared_ptr<InterfacePropertyTypeSignatureStrategy> TypeSignatureStrategyMap::getInterfacePropertyTypeSignatureStrategy() {
    return _interfacePropertyTypeSignatureStrategy;
}

std::shared_ptr<CustomTypeDeclarationTypeSignatureStrategy> TypeSignatureStrategyMap::getCustomTypeDeclarationTypeSignatureStrategy() {
    return _customTypeDeclarationTypeSignatureStrategy;
}
