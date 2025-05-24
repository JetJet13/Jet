//
// Created by Johny Georges on 2024-05-06.
//

#include "type-signature-strategy-map.h"
#include "type-type-signature-strategy/type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/primitive-type-type-signature-strategy/primitive-type-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-access-expression-type-signature-strategy/array-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/array-expression-type-signature-strategy/array-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/binary-expression-type-signature-strategy/binary-expression-type-signature-strategy.h"
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
#include "expression-type-signature-strategies/tuple-expression-type-signature-strategy/tuple-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/unary-expression-type-signature-strategy/unary-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/module-access-expression-type-signature-strategy/module-access-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/ref-expression-type-signature-strategy/ref-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/dref-expression-type-signature-strategy/dref-expression-type-signature-strategy.h"
#include "expression-type-signature-strategies/sref-expression-type-signature-strategy/sref-expression-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/custom-type-type-signature-strategy/custom-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/array-type-type-signature-strategy/array-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/tuple-type-type-signature-strategy/tuple-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/ref-type-type-signature-strategy/ref-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/this-type-type-signature-strategy/this-type-type-signature-strategy.h"
#include "lambda-expression-scope-parameter-type-signature-strategy/lambda-expression-scope-parameter-type-signature-strategy.h"
#include "enum-type-signature-strategy/enum-key-value-type-signature-strategy/enum-key-value-type-signature-strategy.h"
#include "enum-type-signature-strategy/enum-type-signature-strategy.h"
#include "variable-type-signature-strategy/variable-type-signature-strategy.h"
#include "class-type-signature-strategy/class-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-type-signature-strategy/class-property-type-signature-strategy.h"
#include "class-type-signature-strategy/class-constructor-type-signature-strategy/class-constructor-type-signature-strategy.h"
#include "class-type-signature-strategy/class-method-type-signature-strategy/class-method-type-signature-strategy.h"
#include "class-type-signature-strategy/class-property-assignment-statement-type-signature-strategy/class-property-assignment-statement-type-signature-strategy.h"
#include "class-type-signature-strategy/class-scope-parameter-type-signature-strategy/class-scope-parameter-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-item-type-signature-strategy/parameter-list-item-type-signature-strategy.h"
#include "parameter-list-type-signature-strategy/parameter-list-type-singature-strategy.h"
#include "function-type-signature-strategy/function-type-signature-strategy.h"
#include "procedure-type-signature-strategy/procedure-type-signature-strategy.h"
#include "literal-type-signature-strategy/literal-type-signature-strategy.h"
#include "access-modifier-type-signature-strategy/access-modifier-type-signature-strategy.h"
#include "variable-assignment-statement-type-signature-strategy/variable-assignment-statement-type-signature-strategy.h"
#include "block-type-signature-strategy/block-type-signature-strategy.h"
#include "if-statement-type-signature-strategy/if-statement-type-signature-strategy.h"
#include "try-statement-type-signature-strategy/try-statement-type-signature-strategy.h"
#include "while-statement-type-signature-strategy/while-statement-type-signature-strategy.h"
#include "for-in-statement-type-signature-strategy/for-in-statement-type-signature-strategy.h"
#include "condition-type-signature-strategy/condition-type-signature-strategy.h"
#include "expression-statement-type-signature-strategy/expression-statement-type-signature-strategy.h"
#include "import-type-signature-strategy/import-type-signature-strategy.h"
#include "module-type-signature-strategy/module-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/procedure-type-type-signature-strategy/procedure-type-type-signature-strategy.h"
#include "type-type-signature-strategy/base-type-type-signature-strategies/function-type-type-signature-strategy/function-type-type-signature-strategy.h"
#include "argument-list-type-signature-strategy/argument-list-type-signature-strategy.h"
#include "array-access-assignment-statement-type-signature-strategy/array-access-assignment-statement-type-signature-strategy.h"

TypeSignatureStrategyMap::TypeSignatureStrategyMap() {
    _argumentListTypeSignatureStrategy = new ArgumentListTypeSignatureStrategy();
    _arrayAccessExpressionTypeSignatureStrategy = new ArrayAccessExpressionTypeSignatureStrategy();
    _arrayExpressionTypeSignatureStrategy = new ArrayExpressionTypeSignatureStrategy();
    _binaryExpressionTypeSignatureStrategy = new BinaryExpressionTypeSignatureStrategy();
    _classMethodInvocationExpressionTypeSignatureStrategy = new ClassMethodInvocationExpressionTypeSignatureStrategy();
    _classPropertyAccessExpressionTypeSignatureStrategy = new ClassPropertyAccessExpressionTypeSignatureStrategy();
    _classPropertyAssignmentStatementTypeSignatureStrategy = new ClassPropertyAssignmentStatementTypeSignatureStrategy();
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
    _structExpressionTypeSignatureStrategy = new StructExpressionTypeSignatureStrategy();
    _thisExpressionTypeSignatureStrategy = new ThisExpressionTypeSignatureStrategy();
    _tupleAccessExpressionTypeSignatureStrategy = new TupleAccessExpressionTypeSignatureStrategy();
    _tupleExpressionTypeSignatureStrategy = new TupleExpressionTypeSignatureStrategy();
    _unaryExpressionTypeSignatureStrategy = new UnaryExpressionTypeSignatureStrategy();
    _moduleAccessExpressionTypeSignatureStrategy = new ModuleAccessExpressionTypeSignatureStrategy();
    _refExpressionTypeSignatureStrategy = new RefExpressionTypeSignatureStrategy();
    _drefExpressionTypeSignatureStrategy = new DrefExpressionTypeSignatureStrategy();
    _srefExpressionTypeSignatureStrategy = new SrefExpressionTypeSignatureStrategy();
    _lambdaExpressionScopeParameterTypeSignatureStrategy = new LambdaExpressionScopeParameterTypeSignatureStrategy();
    _classScopeParameterTypeSignatureStrategy = new ClassScopeParameterTypeSignatureStrategy();
    _typeTypeSignatureStrategy = new TypeTypeSignatureStrategy();
    _primitiveTypeTypeSignatureStrategy = new PrimitiveTypeTypeSignatureStrategy();
    _customTypeTypeSignatureStrategy = new CustomTypeTypeSignatureStrategy();
    _arrayTypeTypeSignatureStrategy = new ArrayTypeTypeSignatureStrategy();
    _tupleTypeTypeSignatureStrategy = new TupleTypeTypeSignatureStrategy();
    _refTypeTypeSignatureStrategy = new RefTypeTypeSignatureStrategy();
    _functionTypeTypeSignatureStrategy = new FunctionTypeTypeSignatureStrategy();
    _procedureTypeTypeSignatureStrategy = new ProcedureTypeTypeSignatureStrategy();
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
    _blockTypeSignatureStrategy = new BlockTypeSignatureStrategy();
    _expressionStatementTypeSignatureStrategy = new ExpressionStatementTypeSignatureStrategy();
    _conditionTypeSignatureStrategy = new ConditionTypeSignatureStrategy();
    _forStatementTypeSignatureStrategy = new ForInStatementTypeSignatureStrategy();
    _whileStatementTypeSignatureStrategy = new WhileStatementTypeSignatureStrategy();
    _tryStatementTypeSignatureStrategy = new TryStatementTypeSignatureStrategy();
    _ifStatementTypeSignatureStrategy = new IfStatementTypeSignatureStrategy();
    _importTypeSignatureStrategy = new ImportTypeSignatureStrategy();
    _moduleTypeSignatureStrategy = new ModuleTypeSignatureStrategy();
    _arrayAccessAssignmentStatementTypeSignatureStrategy = new ArrayAccessAssignmentStatementTypeSignatureStrategy();
}

ArgumentListTypeSignatureStrategy* TypeSignatureStrategyMap::getArgumentListTypeSignatureStrategy() {
    return this->_argumentListTypeSignatureStrategy;
}

ArrayAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayAccessExpressionTypeSignatureStrategy() {
    return this->_arrayAccessExpressionTypeSignatureStrategy;
}

ArrayExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayExpressionTypeSignatureStrategy() {
    return this->_arrayExpressionTypeSignatureStrategy;
}

BinaryExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getBinaryExpressionTypeSignatureStrategy() {
    return this->_binaryExpressionTypeSignatureStrategy;
}

ClassMethodInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getClassMethodInvocationExpressionTypeSignatureStrategy() {
    return this->_classMethodInvocationExpressionTypeSignatureStrategy;
}

ClassPropertyAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getClassPropertyAccessExpressionTypeSignatureStrategy() {
    return this->_classPropertyAccessExpressionTypeSignatureStrategy;
}

ClassPropertyAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getClassPropertyAssignmentStatementTypeSignatureStrategy() {
    return this->_classPropertyAssignmentStatementTypeSignatureStrategy;
}

CurryExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getCurryExpressionTypeSignatureStrategy() {
    return this->_curryExpressionTypeSignatureStrategy;
}

FunctionInvocationExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionInvocationExpressionTypeSignatureStrategy() {
    return this->_functionInvocationExpressionTypeSignatureStrategy;
}

FunctionReturnExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionReturnExpressionTypeSignatureStrategy() {
    return this->_functionReturnExpressionTypeSignatureStrategy;
}

IdentifierExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getIdentifierExpressionTypeSignatureStrategy() {
    return this->_identifierExpressionTypeSignatureStrategy;
}

LambdaExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaExpressionTypeSignatureStrategy() {
    return this->_lambdaExpressionTypeSignatureStrategy;
}

LambdaWithFatArrowExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaWithFatArrowExpressionTypeSignatureStrategy() {
    return this->_lambdaWithFatArrowExpressionTypeSignatureStrategy;
}

LambdaReturnExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaReturnExpressionTypeSignatureStrategy() {
    return this->_lambdaReturnExpressionTypeSignatureStrategy;
}

LiteralExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLiteralExpressionTypeSignatureStrategy() {
    return this->_literalExpressionTypeSignatureStrategy;
}

LogicalExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getLogicalExpressionTypeSignatureStrategy() {
    return this->_logicalExpressionTypeSignatureStrategy;
}

NewClassInstanceExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getNewClassInstanceExpressionTypeSignatureStrategy() {
    return this->_newClassInstanceExpressionTypeSignatureStrategy;
}

ObjectAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getObjectAccessExpressionTypeSignatureStrategy() {
    return this->_objectAccessExpressionTypeSignatureStrategy;
}

StructExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getStructExpressionTypeSignatureStrategy() {
    return this->_structExpressionTypeSignatureStrategy;
}

ThisExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getThisExpressionTypeSignatureStrategy() {
    return this->_thisExpressionTypeSignatureStrategy;
}

TupleAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleAccessExpressionTypeSignatureStrategy() {
    return this->_tupleAccessExpressionTypeSignatureStrategy;
}

TupleExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleExpressionTypeSignatureStrategy() {
    return this->_tupleExpressionTypeSignatureStrategy;
}

UnaryExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getUnaryExpressionTypeSignatureStrategy() {
    return this->_unaryExpressionTypeSignatureStrategy;
}

ModuleAccessExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getModuleAccessExpressionTypeSignatureStrategy() {
    return this->_moduleAccessExpressionTypeSignatureStrategy;
}

RefExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getRefExpressionTypeSignatureStrategy() {
    return this->_refExpressionTypeSignatureStrategy;
}

DrefExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getDrefExpressionTypeSignatureStrategy() {
    return this->_drefExpressionTypeSignatureStrategy;
}

SrefExpressionTypeSignatureStrategy* TypeSignatureStrategyMap::getSrefExpressionTypeSignatureStrategy() {
    return this->_srefExpressionTypeSignatureStrategy;
}

LambdaExpressionScopeParameterTypeSignatureStrategy* TypeSignatureStrategyMap::getLambdaExpressionScopeParameterTypeSignatureStrategy() {
    return this->_lambdaExpressionScopeParameterTypeSignatureStrategy;
}

ClassScopeParameterTypeSignatureStrategy* TypeSignatureStrategyMap::getClassScopeParameterTypeSignatureStrategy() {
    return this->_classScopeParameterTypeSignatureStrategy;
}

TypeTypeSignatureStrategy* TypeSignatureStrategyMap::getTypeTypeSignatureStrategy() {
    return this->_typeTypeSignatureStrategy;
}

PrimitiveTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getPrimitiveTypeTypeSignatureStrategy() {
    return this->_primitiveTypeTypeSignatureStrategy;
}

CustomTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getCustomTypeTypeSignatureStrategy() {
    return this->_customTypeTypeSignatureStrategy;
}

ArrayTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayTypeTypeSignatureStrategy() {
    return this->_arrayTypeTypeSignatureStrategy;
}

TupleTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getTupleTypeTypeSignatureStrategy() {
    return this->_tupleTypeTypeSignatureStrategy;
}

RefTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getRefTypeTypeSignatureStrategy() {
    return this->_refTypeTypeSignatureStrategy;
}

FunctionTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionTypeTypeSignatureStrategy() {
    return this->_functionTypeTypeSignatureStrategy;
}

ProcedureTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getProcedureTypeTypeSignatureStrategy() {
    return this->_procedureTypeTypeSignatureStrategy;
}

ThisTypeTypeSignatureStrategy* TypeSignatureStrategyMap::getThisTypeTypeSignatureStrategy() {
    return this->_thisTypeTypeSignatureStrategy;
}

EnumKeyValueTypeSignatureStrategy* TypeSignatureStrategyMap::getEnumKeyValueTypeSignatureStrategy() {
    return this->_enumKeyValueTypeSignatureStrategy;
}

EnumTypeSignatureStrategy* TypeSignatureStrategyMap::getEnumTypeSignatureStrategy() {
    return this->_enumTypeSignatureStrategy;
}

VariableTypeSignatureStrategy* TypeSignatureStrategyMap::getVariableTypeSignatureStrategy() {
    return this->_variableTypeSignatureStrategy;
}

ClassTypeSignatureStrategy* TypeSignatureStrategyMap::getClassTypeSignatureStrategy() {
    return this->_classTypeSignatureStrategy;
}

ClassPropertyTypeSignatureStrategy* TypeSignatureStrategyMap::getClassPropertyTypeSignatureStrategy() {
    return this->_classPropertyTypeSignatureStrategy;
}

ClassConstructorTypeSignatureStrategy* TypeSignatureStrategyMap::getClassConstructorTypeSignatureStrategy() {
    return this->_classConstructorTypeSignatureStrategy;
}

ClassMethodTypeSignatureStrategy* TypeSignatureStrategyMap::getClassMethodTypeSignatureStrategy() {
    return this->_classMethodTypeSignatureStrategy;
}

ParameterListItemTypeSignatureStrategy* TypeSignatureStrategyMap::getParameterListItemTypeSignatureStrategy() {
    return this->_parameterListItemTypeSignatureStrategy;
}

ParameterListTypeSignatureStrategy* TypeSignatureStrategyMap::getParameterListTypeSignatureStrategy() {
    return this->_parameterListTypeSignatureStrategy;
}

FunctionTypeSignatureStrategy* TypeSignatureStrategyMap::getFunctionTypeSignatureStrategy() {
    return this->_functionTypeSignatureStrategy;
}

ProcedureTypeSignatureStrategy* TypeSignatureStrategyMap::getProcedureTypeSignatureStrategy() {
    return this->_procedureTypeSignatureStrategy;
}

LiteralTypeSignatureStrategy* TypeSignatureStrategyMap::getLiteralTypeSignatureStrategy() {
    return this->_literalTypeSignatureStrategy;
}

AccessModifierTypeSignatureStrategy* TypeSignatureStrategyMap::getAccessModifierTypeSignatureStrategy() {
    return this->_accessModifierTypeSignatureStrategy;
}

VariableAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getVariableAssignmentStatementTypeSignatureStrategy() {
    return this->_variableAssignmentStatementTypeSignatureStrategy;
}

ArrayAccessAssignmentStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getArrayAccessAssignmentStatementTypeSignatureStrategy() {
    return this->_arrayAccessAssignmentStatementTypeSignatureStrategy;
}

BlockTypeSignatureStrategy* TypeSignatureStrategyMap::getBlockTypeSignatureStrategy() {
    return this->_blockTypeSignatureStrategy;
}

ExpressionStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getExpressionStatementTypeSignatureStrategy() {
    return this->_expressionStatementTypeSignatureStrategy;
}
ConditionTypeSignatureStrategy* TypeSignatureStrategyMap::getConditionTypeSignatureStrategy() {
    return this->_conditionTypeSignatureStrategy;
}
ForInStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getForStatementTypeSignatureStrategy() {
    return this->_forStatementTypeSignatureStrategy;
}
WhileStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getWhileStatementTypeSignatureStrategy() {
    return this->_whileStatementTypeSignatureStrategy;
}
TryStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getTryStatementTypeSignatureStrategy() {
    return this->_tryStatementTypeSignatureStrategy;
}
IfStatementTypeSignatureStrategy* TypeSignatureStrategyMap::getIfStatementTypeSignatureStrategy() {
    return this->_ifStatementTypeSignatureStrategy;
}
ImportTypeSignatureStrategy* TypeSignatureStrategyMap::getImportTypeSignatureStrategy() {
    return this->_importTypeSignatureStrategy;
}
ModuleTypeSignatureStrategy* TypeSignatureStrategyMap::getModuleTypeSignatureStrategy() {
    return this->_moduleTypeSignatureStrategy;
}
