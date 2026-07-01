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
#include "expression-type-signature-strategies/ref-expression-type-signature-strategy/ref-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/dref-expression-type-signature-strategy/dref-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/struct-type-type-signature-strategy/struct-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/tuple-type-type-signature-strategy/tuple-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/ref-type-type-signature-strategy/ref-type-type-signature-strategy.h"
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
    _argumentListTypeSignatureStrategy = new ArgumentListTypeSignatureStrategy();
    _arrayAccessExpressionTypeSignatureStrategy = new ArrayAccessExpressionTypeSignatureStrategy();
    _arrayAccessInvocationExpressionTypeSignatureStrategy = new ArrayAccessInvocationExpressionTypeSignatureStrategy();
    _arrayExpressionTypeSignatureStrategy = new ArrayExpressionTypeSignatureStrategy();
    _binaryExpressionTypeSignatureStrategy = new BinaryExpressionTypeSignatureStrategy();
    _concatExpressionTypeSignatureStrategy = new ConcatExpressionTypeSignatureStrategy();
    _classMethodInvocationExpressionTypeSignatureStrategy = new ClassMethodInvocationExpressionTypeSignatureStrategy();
    _classPropertyAccessExpressionTypeSignatureStrategy = new ClassPropertyAccessExpressionTypeSignatureStrategy();
    _classPropertyAssignmentStatementTypeSignatureStrategy = new ClassPropertyAssignmentStatementTypeSignatureStrategy();
    _classPropertyRefValueAssignmentStatementTypeSignatureStrategy = new ClassPropertyRefValueAssignmentStatementTypeSignatureStrategy();
    _curryExpressionTypeSignatureStrategy = new CurryExpressionTypeSignatureStrategy();
    _functionInvocationExpressionTypeSignatureStrategy = new FunctionInvocationExpressionTypeSignatureStrategy();
    _functionReturnExpressionTypeSignatureStrategy = new FunctionReturnExpressionTypeSignatureStrategy();
    _identifierExpressionTypeSignatureStrategy = new IdentifierExpressionTypeSignatureStrategy();
    _lambdaExpressionTypeSignatureStrategy = new LambdaExpressionTypeSignatureStrategy();
    _lambdaWithFatArrowExpressionTypeSignatureStrategy = new LambdaWithFatArrowExpressionTypeSignatureStrategy();
    _lambdaReturnExpressionTypeSignatureStrategy = new LambdaReturnExpressionTypeSignatureStrategy();
    _literalExpressionTypeSignatureStrategy = new LiteralExpressionTypeSignatureStrategy();
    _logicalExpressionTypeSignatureStrategy = new LogicalExpressionTypeSignatureStrategy();
    _newClassInstanceExpressionTypeSignatureStrategy = new NewClassInstanceExpressionTypeSignatureStrategy();
    _objectAccessExpressionTypeSignatureStrategy = new ObjectAccessExpressionTypeSignatureStrategy();
    _objectAccessInvocationExpressionTypeSignatureStrategy = new ObjectAccessInvocationExpressionTypeSignatureStrategy();
    _structExpressionTypeSignatureStrategy = new StructExpressionTypeSignatureStrategy();
    _thisExpressionTypeSignatureStrategy = new ThisExpressionTypeSignatureStrategy();
    _tupleAccessExpressionTypeSignatureStrategy = new TupleAccessExpressionTypeSignatureStrategy();
    _tupleAccessInvocationExpressionTypeSignatureStrategy = new TupleAccessInvocationExpressionTypeSignatureStrategy();
    _tupleExpressionTypeSignatureStrategy = new TupleExpressionTypeSignatureStrategy();
    _unaryExpressionTypeSignatureStrategy = new UnaryExpressionTypeSignatureStrategy();
    _moduleAccessExpressionTypeSignatureStrategy = new ModuleAccessExpressionTypeSignatureStrategy();
    _refExpressionTypeSignatureStrategy = new RefExpressionTypeSignatureStrategy();
    _drefExpressionTypeSignatureStrategy = new DrefExpressionTypeSignatureStrategy();
    _lambdaExpressionScopeParameterTypeSignatureStrategy = new LambdaExpressionScopeParameterTypeSignatureStrategy();
    _classScopeParameterTypeSignatureStrategy = new ClassScopeParameterTypeSignatureStrategy();
    _typeTypeSignatureStrategy = new TypeTypeSignatureStrategy();
    _primitiveTypeTypeSignatureStrategy = new PrimitiveTypeTypeSignatureStrategy();
    _customTypeTypeSignatureStrategy = new CustomTypeTypeSignatureStrategy();
    _arrayTypeTypeSignatureStrategy = new ArrayTypeTypeSignatureStrategy();
    _structTypeTypeSignatureStrategy = new StructTypeTypeSignatureStrategy();
    _tupleTypeTypeSignatureStrategy = new TupleTypeTypeSignatureStrategy();
    _refTypeTypeSignatureStrategy = new RefTypeTypeSignatureStrategy();
    _moduleTypeTypeSignatureStrategy = new ModuleTypeTypeSignatureStrategy();
    _lambdaTypeTypeSignatureStrategy = new LambdaTypeTypeSignatureStrategy();
    _voidTypeTypeSignatureStrategy = new VoidTypeTypeSignatureStrategy();
    _thisTypeTypeSignatureStrategy = new ThisTypeTypeSignatureStrategy();
    _enumKeyValueTypeSignatureStrategy = new EnumKeyValueTypeSignatureStrategy();
    _enumTypeSignatureStrategy = new EnumTypeSignatureStrategy();
    _variableTypeSignatureStrategy = new VariableTypeSignatureStrategy();
    _classTypeSignatureStrategy = new ClassTypeSignatureStrategy();
    _classPropertyTypeSignatureStrategy = new ClassPropertyTypeSignatureStrategy();
    _classConstructorTypeSignatureStrategy = new ClassConstructorTypeSignatureStrategy();
    _classMethodTypeSignatureStrategy = new ClassMethodTypeSignatureStrategy();
    _parameterListItemTypeSignatureStrategy = new ParameterListItemTypeSignatureStrategy();
    _parameterListTypeSignatureStrategy = new ParameterListTypeSignatureStrategy();
    _functionTypeSignatureStrategy = new FunctionTypeSignatureStrategy();
    _procedureTypeSignatureStrategy = new ProcedureTypeSignatureStrategy();
    _literalTypeSignatureStrategy = new LiteralTypeSignatureStrategy();
    _accessModifierTypeSignatureStrategy = new AccessModifierTypeSignatureStrategy();
    _variableAssignmentStatementTypeSignatureStrategy = new VariableAssignmentStatementTypeSignatureStrategy();
    _refValueAssignmentStatementTypeSignatureStrategy = new RefValueAssignmentStatementTypeSignatureStrategy();
    _blockTypeSignatureStrategy = new BlockTypeSignatureStrategy();
    _expressionStatementTypeSignatureStrategy = new ExpressionStatementTypeSignatureStrategy();
    _conditionTypeSignatureStrategy = new ConditionTypeSignatureStrategy();
    _forStatementTypeSignatureStrategy = new ForInStatementTypeSignatureStrategy();
    _whileStatementTypeSignatureStrategy = new WhileStatementTypeSignatureStrategy();
    _tryStatementTypeSignatureStrategy = new TryStatementTypeSignatureStrategy();
    _ifStatementTypeSignatureStrategy = new IfStatementTypeSignatureStrategy();
    _importTypeSignatureStrategy = new ImportTypeSignatureStrategy();
    _moduleTypeSignatureStrategy = new ModuleTypeSignatureStrategy();
    _interfaceTypeSignatureStrategy = new InterfaceTypeSignatureStrategy();
    _interfacePropertyTypeSignatureStrategy = new InterfacePropertyTypeSignatureStrategy();
    _customTypeDeclarationTypeSignatureStrategy = new CustomTypeDeclarationTypeSignatureStrategy();
    _arrayAccessAssignmentStatementTypeSignatureStrategy = new ArrayAccessAssignmentStatementTypeSignatureStrategy();
    _arrayAccessRefAssignmentStatementTypeSignatureStrategy = new ArrayAccessRefAssignmentStatementTypeSignatureStrategy();
    _objectAccessAssignmentStatementTypeSignatureStrategy = new ObjectAccessAssignmentStatementTypeSignatureStrategy();
    _objectAccessRefAssignmentStatementTypeSignatureStrategy = new ObjectAccessRefAssignmentStatementTypeSignatureStrategy();
    _tupleAccessAssignmentStatementTypeSignatureStrategy = new TupleAccessAssignmentStatementTypeSignatureStrategy();
    _tupleAccessRefAssignmentStatementTypeSignatureStrategy = new TupleAccessRefAssignmentStatementTypeSignatureStrategy();
    _moduleAccessAssignmentStatementTypeSignatureStrategy = new ModuleAccessAssignmentStatementTypeSignatureStrategy();
    _moduleAccessRefAssignmentStatementTypeSignatureStrategy = new ModuleAccessRefAssignmentStatementTypeSignatureStrategy();
}

ArgumentListTypeSignatureStrategy* TypeSignatureStrategyMap::getArgumentListTypeSignatureStrategy() {
    return _argumentListTypeSignatureStrategy;
}

ArrayAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayAccessExpressionTypeSignatureStrategy() {
    return _arrayAccessExpressionTypeSignatureStrategy;
}

ArrayAccessInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayAccessInvocationExpressionTypeSignatureStrategy() {
    return _arrayAccessInvocationExpressionTypeSignatureStrategy;
}

ArrayExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayExpressionTypeSignatureStrategy() {
    return _arrayExpressionTypeSignatureStrategy;
}

BinaryExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getBinaryExpressionTypeSignatureStrategy() {
    return _binaryExpressionTypeSignatureStrategy;
}

ConcatExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getConcatExpressionTypeSignatureStrategy() {
    return _concatExpressionTypeSignatureStrategy;
}

ClassMethodInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getClassMethodInvocationExpressionTypeSignatureStrategy() {
    return _classMethodInvocationExpressionTypeSignatureStrategy;
}

ClassPropertyAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getClassPropertyAccessExpressionTypeSignatureStrategy() {
    return _classPropertyAccessExpressionTypeSignatureStrategy;
}

ClassPropertyRefValueAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getClassPropertyRefValueAssignmentStatementTypeSignatureStrategy() {
    return _classPropertyRefValueAssignmentStatementTypeSignatureStrategy;
}

ClassPropertyAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getClassPropertyAssignmentStatementTypeSignatureStrategy() {
    return _classPropertyAssignmentStatementTypeSignatureStrategy;
}

CurryExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getCurryExpressionTypeSignatureStrategy() {
    return _curryExpressionTypeSignatureStrategy;
}

FunctionInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionInvocationExpressionTypeSignatureStrategy() {
    return _functionInvocationExpressionTypeSignatureStrategy;
}

FunctionReturnExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionReturnExpressionTypeSignatureStrategy() {
    return _functionReturnExpressionTypeSignatureStrategy;
}

IdentifierExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getIdentifierExpressionTypeSignatureStrategy() {
    return _identifierExpressionTypeSignatureStrategy;
}

LambdaExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaExpressionTypeSignatureStrategy() {
    return _lambdaExpressionTypeSignatureStrategy;
}

LambdaWithFatArrowExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaWithFatArrowExpressionTypeSignatureStrategy() {
    return _lambdaWithFatArrowExpressionTypeSignatureStrategy;
}

LambdaReturnExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaReturnExpressionTypeSignatureStrategy() {
    return _lambdaReturnExpressionTypeSignatureStrategy;
}

LiteralExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLiteralExpressionTypeSignatureStrategy() {
    return _literalExpressionTypeSignatureStrategy;
}

LogicalExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLogicalExpressionTypeSignatureStrategy() {
    return _logicalExpressionTypeSignatureStrategy;
}

NewClassInstanceExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getNewClassInstanceExpressionTypeSignatureStrategy() {
    return _newClassInstanceExpressionTypeSignatureStrategy;
}

ObjectAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getObjectAccessExpressionTypeSignatureStrategy() {
    return _objectAccessExpressionTypeSignatureStrategy;
}

ObjectAccessInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getObjectAccessInvocationExpressionTypeSignatureStrategy() {
    return _objectAccessInvocationExpressionTypeSignatureStrategy;
}

StructExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getStructExpressionTypeSignatureStrategy() {
    return _structExpressionTypeSignatureStrategy;
}

ThisExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getThisExpressionTypeSignatureStrategy() {
    return _thisExpressionTypeSignatureStrategy;
}

TupleAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleAccessExpressionTypeSignatureStrategy() {
    return _tupleAccessExpressionTypeSignatureStrategy;
}

TupleAccessInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleAccessInvocationExpressionTypeSignatureStrategy() {
    return _tupleAccessInvocationExpressionTypeSignatureStrategy;
}

TupleExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleExpressionTypeSignatureStrategy() {
    return _tupleExpressionTypeSignatureStrategy;
}

UnaryExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getUnaryExpressionTypeSignatureStrategy() {
    return _unaryExpressionTypeSignatureStrategy;
}

ModuleAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getModuleAccessExpressionTypeSignatureStrategy() {
    return _moduleAccessExpressionTypeSignatureStrategy;
}

RefExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getRefExpressionTypeSignatureStrategy() {
    return _refExpressionTypeSignatureStrategy;
}

DrefExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getDrefExpressionTypeSignatureStrategy() {
    return _drefExpressionTypeSignatureStrategy;
}

LambdaExpressionScopeParameterTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaExpressionScopeParameterTypeSignatureStrategy() {
    return _lambdaExpressionScopeParameterTypeSignatureStrategy;
}

ClassScopeParameterTypeSignatureStrategy* TypeSignatureStrategyMap::getClassScopeParameterTypeSignatureStrategy() {
    return _classScopeParameterTypeSignatureStrategy;
}

TypeTypeSignatureStrategy* TypeSignatureStrategyMap::getTypeTypeSignatureStrategy() {
    return _typeTypeSignatureStrategy;
}

PrimitiveTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getPrimitiveTypeTypeSignatureStrategy() {
    return _primitiveTypeTypeSignatureStrategy;
}

CustomTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getCustomTypeTypeSignatureStrategy() {
    return _customTypeTypeSignatureStrategy;
}

ArrayTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayTypeTypeSignatureStrategy() {
    return _arrayTypeTypeSignatureStrategy;
}

StructTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getStructTypeTypeSignatureStrategy() {
    return _structTypeTypeSignatureStrategy;
}

TupleTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleTypeTypeSignatureStrategy() {
    return _tupleTypeTypeSignatureStrategy;
}

RefTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getRefTypeTypeSignatureStrategy() {
    return _refTypeTypeSignatureStrategy;
}

ModuleTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getModuleTypeTypeSignatureStrategy() {
    return _moduleTypeTypeSignatureStrategy;
}

LambdaTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaTypeTypeSignatureStrategy() {
    return _lambdaTypeTypeSignatureStrategy;
}

VoidTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getVoidTypeTypeSignatureStrategy() {
    return _voidTypeTypeSignatureStrategy;
}

ThisTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getThisTypeTypeSignatureStrategy() {
    return _thisTypeTypeSignatureStrategy;
}

EnumKeyValueTypeSignatureStrategy* TypeSignatureStrategyMap::getEnumKeyValueTypeSignatureStrategy() {
    return _enumKeyValueTypeSignatureStrategy;
}

EnumTypeSignatureStrategy* TypeSignatureStrategyMap::getEnumTypeSignatureStrategy() {
    return _enumTypeSignatureStrategy;
}

VariableTypeSignatureStrategy* TypeSignatureStrategyMap::getVariableTypeSignatureStrategy() {
    return _variableTypeSignatureStrategy;
}

ClassTypeSignatureStrategy* TypeSignatureStrategyMap::getClassTypeSignatureStrategy() {
    return _classTypeSignatureStrategy;
}

ClassPropertyTypeSignatureStrategy* TypeSignatureStrategyMap::getClassPropertyTypeSignatureStrategy() {
    return _classPropertyTypeSignatureStrategy;
}

ClassConstructorTypeSignatureStrategy* TypeSignatureStrategyMap::getClassConstructorTypeSignatureStrategy() {
    return _classConstructorTypeSignatureStrategy;
}

ClassMethodTypeSignatureStrategy* TypeSignatureStrategyMap::getClassMethodTypeSignatureStrategy() {
    return _classMethodTypeSignatureStrategy;
}

ParameterListItemTypeSignatureStrategy* TypeSignatureStrategyMap::getParameterListItemTypeSignatureStrategy() {
    return _parameterListItemTypeSignatureStrategy;
}

ParameterListTypeSignatureStrategy* TypeSignatureStrategyMap::getParameterListTypeSignatureStrategy() {
    return _parameterListTypeSignatureStrategy;
}

FunctionTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionTypeSignatureStrategy() {
    return _functionTypeSignatureStrategy;
}

ProcedureTypeSignatureStrategy* TypeSignatureStrategyMap::getProcedureTypeSignatureStrategy() {
    return _procedureTypeSignatureStrategy;
}

LiteralTypeSignatureStrategy* TypeSignatureStrategyMap::getLiteralTypeSignatureStrategy() {
    return _literalTypeSignatureStrategy;
}

AccessModifierTypeSignatureStrategy* TypeSignatureStrategyMap::getAccessModifierTypeSignatureStrategy() {
    return _accessModifierTypeSignatureStrategy;
}

VariableAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getVariableAssignmentStatementTypeSignatureStrategy() {
    return _variableAssignmentStatementTypeSignatureStrategy;
}

RefValueAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getRefValueAssignmentStatementTypeSignatureStrategy() {
    return _refValueAssignmentStatementTypeSignatureStrategy;
}

ArrayAccessAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayAccessAssignmentStatementTypeSignatureStrategy() {
    return _arrayAccessAssignmentStatementTypeSignatureStrategy;
}

ArrayAccessRefAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayAccessRefAssignmentStatementTypeSignatureStrategy() {
    return _arrayAccessRefAssignmentStatementTypeSignatureStrategy;
}

ObjectAccessAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getObjectAccessAssignmentStatementTypeSignatureStrategy() {
    return _objectAccessAssignmentStatementTypeSignatureStrategy;
}

ObjectAccessRefAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getObjectAccessRefAssignmentStatementTypeSignatureStrategy() {
    return _objectAccessRefAssignmentStatementTypeSignatureStrategy;
}

TupleAccessAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleAccessAssignmentStatementTypeSignatureStrategy() {
    return _tupleAccessAssignmentStatementTypeSignatureStrategy;
}

TupleAccessRefAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleAccessRefAssignmentStatementTypeSignatureStrategy() {
    return _tupleAccessRefAssignmentStatementTypeSignatureStrategy;
}

ModuleAccessAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getModuleAccessAssignmentStatementTypeSignatureStrategy() {
    return _moduleAccessAssignmentStatementTypeSignatureStrategy;
}

ModuleAccessRefAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getModuleAccessRefAssignmentStatementTypeSignatureStrategy() {
    return _moduleAccessRefAssignmentStatementTypeSignatureStrategy;
}

BlockTypeSignatureStrategy* TypeSignatureStrategyMap::getBlockTypeSignatureStrategy() {
    return _blockTypeSignatureStrategy;
}

ExpressionStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getExpressionStatementTypeSignatureStrategy() {
    return _expressionStatementTypeSignatureStrategy;
}

ConditionTypeSignatureStrategy* TypeSignatureStrategyMap::getConditionTypeSignatureStrategy() {
    return _conditionTypeSignatureStrategy;
}

ForInStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getForStatementTypeSignatureStrategy() {
    return _forStatementTypeSignatureStrategy;
}

WhileStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getWhileStatementTypeSignatureStrategy() {
    return _whileStatementTypeSignatureStrategy;
}

TryStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getTryStatementTypeSignatureStrategy() {
    return _tryStatementTypeSignatureStrategy;
}

IfStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getIfStatementTypeSignatureStrategy() {
    return _ifStatementTypeSignatureStrategy;
}

ImportTypeSignatureStrategy* TypeSignatureStrategyMap::getImportTypeSignatureStrategy() {
    return _importTypeSignatureStrategy;
}

ModuleTypeSignatureStrategy* TypeSignatureStrategyMap::getModuleTypeSignatureStrategy() {
    return _moduleTypeSignatureStrategy;
}

InterfaceTypeSignatureStrategy* TypeSignatureStrategyMap::getInterfaceTypeSignatureStrategy() {
    return _interfaceTypeSignatureStrategy;
}

InterfacePropertyTypeSignatureStrategy* TypeSignatureStrategyMap::getInterfacePropertyTypeSignatureStrategy() {
    return _interfacePropertyTypeSignatureStrategy;
}

CustomTypeDeclarationTypeSignatureStrategy* TypeSignatureStrategyMap::getCustomTypeDeclarationTypeSignatureStrategy() {
    return _customTypeDeclarationTypeSignatureStrategy;
}
