//
// Created by Johny Georges on 2024-06-15.
//

#include "ir-strategy-map.h"
#include "./literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h"
#include "./literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h"
#include "./literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h"
#include "./literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h"
#include "./literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h"
#include "./expression-ir-strategies/literal-expression-ir-strategy/literal-expression-ir-strategy.h"
#include "./expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h"
#include "./expression-ir-strategies/concat-expression-ir-strategy/concat-expression-ir-strategy.h"
#include "./expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-access-expression-ir-strategy/array-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/array-access-invocation-expression-ir-strategy/array-access-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.h"
#include "./expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-expression-ir-strategy/tuple-expression-ir-strategy.h"
#include "./expression-ir-strategies/this-expression-ir-strategy/this-expression-ir-strategy.h"
#include "./expression-ir-strategies/identifier-expression-ir-strategy/identifier-expression-ir-strategy.h"
#include "./expression-ir-strategies/object-access-expression-ir-strategy/object-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/object-access-invocation-expression-ir-strategy/object-access-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-access-expression-ir-strategy/tuple-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-access-invocation-expression-ir-strategy/tuple-access-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/function-invocation-expression-ir-strategy/function-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/lambda-expression-ir-strategy/lambda-expression-ir-strategy.h"
#include "./expression-ir-strategies/module-access-expression-ir-strategy/module-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/class-property-access-expression-ir-strategy/class-property-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/class-method-invocation-expression-ir-strategy/class-method-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/new-class-instance-expression-ir-strategy/new-class-instance-expression-ir-strategy.h"
#include "./expression-ir-strategies/ref-expression-ir-strategy/ref-expression-ir-strategy.h"
#include "./expression-ir-strategies/dref-expression-ir-strategy/dref-expression-ir-strategy.h"
#include "./expression-statement-ir-strategy/expression-statement-ir-strategy.h"
#include "./class-property-assignment-statement-ir-strategy/class-property-assignment-statement-ir-strategy.h"
#include "./class-property-ref-value-assignment-statement-ir-strategy/class-property-ref-value-assignment-statement-ir-strategy.h"
#include "./ref-value-assignment-statement-ir-strategy/ref-value-assignment-statement-ir-strategy.h"
#include "./variable-assignment-statement-ir-strategy/variable-assignment-statement-ir-strategy.h"
#include "./array-access-assignment-statement-ir-strategy/array-access-assignment-statement-ir-strategy.h"
#include "./array-access-ref-assignment-statement-ir-strategy/array-access-ref-assignment-statement-ir-strategy.h"
#include "./object-access-assignment-statement-ir-strategy/object-access-assignment-statement-ir-strategy.h"
#include "./object-access-ref-assignment-statement-ir-strategy/object-access-ref-assignment-statement-ir-strategy.h"
#include "./tuple-access-assignment-statement-ir-strategy/tuple-access-assignment-statement-ir-strategy.h"
#include "./tuple-access-ref-assignment-statement-ir-strategy/tuple-access-ref-assignment-statement-ir-strategy.h"
#include "./module-access-assignment-statement-ir-strategy/module-access-assignment-statement-ir-strategy.h"
#include "./module-access-ref-assignment-statement-ir-strategy/module-access-ref-assignment-statement-ir-strategy.h"
#include "./variable-declaration-ir-strategy/variable-declaration-ir-strategy.h"
#include "./function-declaration-ir-strategy/function-declaration-ir-strategy.h"
#include "./function-parameter-list-ir-strategy/function-parameter-list-ir-strategy.h"
#include "./function-return-expression-ir-strategy/function-return-expression-ir-strategy.h"
#include "./procedure-declaration-ir-strategy/procedure-declaration-ir-strategy.h"
#include "./enum-declaration-ir-strategy/enum-declaration-ir-strategy.h"
#include "./interface-type-declaration-ir-strategy/interface-type-declaration-ir-strategy.h"
#include "./custom-type-declaration-ir-strategy/custom-type-declaration-ir-strategy.h"
#include "./module-declaration-ir-strategy/module-declaration-ir-strategy.h"
#include "./import-single-module-declaration-ir-strategy/import-single-module-declaration-ir-strategy.h"
#include "./class-declaration-ir-strategy/class-declaration-ir-strategy.h"
#include "./if-statement-ir-strategy/if-statement-ir-strategy.h"
#include "./while-statement-ir-strategy/while-statement-ir-strategy.h"
#include "./for-in-statement-ir-strategy/for-in-statement-ir-strategy.h"
#include "./type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/literal-type-signature-ir-strategy/literal-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-type-signature-ir-strategy/class-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/new-class-instance-type-signature-ir-strategy/new-class-instance-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-instance-type-signature-ir-strategy/class-instance-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/enum-type-signature-ir-strategy/enum-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/interface-type-signature-ir-strategy/interface-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/function-type-signature-ir-strategy/function-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/lambda-type-signature-ir-strategy/lambda-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/invocable-type-signature-ir-strategies/procedure-type-signature-ir-strategy/procedure-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-list-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/parameter-list-type-signature-ir-strategy/parameter-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/struct-type-signature-ir-strategy/struct-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/tuple-type-signature-ir-strategy/tuple-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/enum-access-type-signature-ir-strategy/enum-access-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/module-type-signature-ir-strategy/module-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/pointer-type-signature-ir-strategy/pointer-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/ref-type-signature-ir-strategy/ref-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/function-invocation-type-signature-ir-strategy/function-invocation-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-method-type-signature-ir-strategy/class-method-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/class-property-type-signature-ir-strategy/class-property-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/lambda-scope-type-signature-ir-strategy/lambda-scope-type-signature-ir-strategy.h"
#include "./type-signature-ir-strategies/void-type-signature-ir-strategy/void-type-signature-ir-strategy.h"

IRStrategyMap::IRStrategyMap() {
    _intLiteralIRStrategy = std::make_unique<IntLiteralIRStrategy>();
    _floatLiteralIRStrategy = std::make_unique<FloatLiteralIRStrategy>();
    _charLiteralIRStrategy = std::make_unique<CharLiteralIRStrategy>();
    _stringLiteralIRStrategy = std::make_unique<StringLiteralIRStrategy>();
    _boolLiteralIRStrategy = std::make_unique<BoolLiteralIRStrategy>();
    _literalExpressionIRStrategy = std::make_unique<LiteralExpressionIRStrategy>();
    _binaryExpressionIRStrategy = std::make_unique<BinaryExpressionIRStrategy>();
    _concatExpressionIRStrategy = std::make_unique<ConcatExpressionIRStrategy>();
    _logicalExpressionIRStrategy = std::make_unique<LogicalExpressionIRStrategy>();
    _arrayExpressionIRStrategy = std::make_unique<ArrayExpressionIRStrategy>();
    _structExpressionIRStrategy = std::make_unique<StructExpressionIRStrategy>();
    _arrayAccessExpressionIRStrategy = std::make_unique<ArrayAccessExpressionIRStrategy>();
    _arrayAccessInvocationExpressionIRStrategy = std::make_unique<ArrayAccessInvocationExpressionIRStrategy>();
    _unaryExpressionIRStrategy = std::make_unique<UnaryExpressionIRStrategy>();
    _tupleExpressionIRStrategy = std::make_unique<TupleExpressionIRStrategy>();
    _thisExpressionIRStrategy = std::make_unique<ThisExpressionIRStrategy>();
    _identifierExpressionIRStrategy = std::make_unique<IdentifierExpressionIRStrategy>();
    _variableDeclarationIRStrategy = std::make_unique<VariableDeclarationIRStrategy>();
    _functionDeclarationIRStrategy = std::make_unique<FunctionDeclarationIRStrategy>();
    _functionParameterListIRStrategy = std::make_unique<FunctionParameterListIRStrategy>();
    _functionReturnExpressionIRStrategy = std::make_unique<FunctionReturnExpressionIRStrategy>();
    _procedureDeclarationIRStrategy = std::make_unique<ProcedureDeclarationIRStrategy>();
    _enumDeclarationIRStrategy = std::make_unique<EnumDeclarationIRStrategy>();
    _interfaceTypeDeclarationIRStrategy = std::make_unique<InterfaceTypeDeclarationIRStrategy>();
    _customTypeDeclarationIRStrategy = std::make_unique<CustomTypeDeclarationIRStrategy>();
    _moduleDeclarationIRStrategy = std::make_unique<ModuleDeclarationIRStrategy>();
    _importSingleModuleDeclarationIRStrategy = std::make_unique<ImportSingleModuleDeclarationIRStrategy>();
    _objectAccessExpressionIRStrategy = std::make_unique<ObjectAccessExpressionIRStrategy>();
    _objectAccessInvocationExpressionIRStrategy = std::make_unique<ObjectAccessInvocationExpressionIRStrategy>();
    _tupleAccessExpressionIRStrategy = std::make_unique<TupleAccessExpressionIRStrategy>();
    _tupleAccessInvocationExpressionIRStrategy = std::make_unique<TupleAccessInvocationExpressionIRStrategy>();
    _functionInvocationExpressionIRStrategy = std::make_unique<FunctionInvocationExpressionIRStrategy>();
    _lambdaExpressionIRStrategy = std::make_unique<LambdaExpressionIRStrategy>();
    _moduleAccessExpressionIRStrategy = std::make_unique<ModuleAccessExpressionIRStrategy>();
    _expressionStatementIRStrategy = std::make_unique<ExpressionStatementIRStrategy>();
    _classDeclarationIRStrategy = std::make_unique<ClassDeclarationIRStrategy>();
    _classPropertyAccessExpressionIRStrategy = std::make_unique<ClassPropertyAccessExpressionIRStrategy>();
    _classMethodInvocationExpressionIRStrategy = std::make_unique<ClassMethodInvocationExpressionIRStrategy>();
    _newClassInstanceExpressionIRStrategy = std::make_unique<NewClassInstanceExpressionIRStrategy>();
    _classPropertyAssignmentStatementIRStrategy = std::make_unique<ClassPropertyAssignmentStatementIRStrategy>();
    _variableAssignmentStatementIRStrategy = std::make_unique<VariableAssignmentStatementIRStrategy>();
    _arrayAccessAssignmentStatementIRStrategy = std::make_unique<ArrayAccessAssignmentStatementIRStrategy>();
    _arrayAccessRefAssignmentStatementIRStrategy = std::make_unique<ArrayAccessRefAssignmentStatementIRStrategy>();
    _objectAccessAssignmentStatementIRStrategy = std::make_unique<ObjectAccessAssignmentStatementIRStrategy>();
    _objectAccessRefAssignmentStatementIRStrategy = std::make_unique<ObjectAccessRefAssignmentStatementIRStrategy>();
    _tupleAccessAssignmentStatementIRStrategy = std::make_unique<TupleAccessAssignmentStatementIRStrategy>();
    _tupleAccessRefAssignmentStatementIRStrategy = std::make_unique<TupleAccessRefAssignmentStatementIRStrategy>();
    _moduleAccessAssignmentStatementIRStrategy = std::make_unique<ModuleAccessAssignmentStatementIRStrategy>();
    _moduleAccessRefAssignmentStatementIRStrategy = std::make_unique<ModuleAccessRefAssignmentStatementIRStrategy>();
    _classPropertyRefValueAssignmentStatementIRStrategy = std::make_unique<ClassPropertyRefValueAssignmentStatementIRStrategy>();
    _refValueAssignmentStatementIRStrategy = std::make_unique<RefValueAssignmentStatementIRStrategy>();
    _ifStatementIRStrategy = std::make_unique<IfStatementIRStrategy>();
    _whileStatementIRStrategy = std::make_unique<WhileStatementIRStrategy>();
    _forInStatementIRStrategy = std::make_unique<ForInStatementIRStrategy>();
    _refExpressionIRStrategy = std::make_unique<RefExpressionIRStrategy>();
    _drefExpressionIRStrategy = std::make_unique<DrefExpressionIRStrategy>();

    _arrayTypeSignatureIRStrategy = std::make_unique<ArrayTypeSignatureIRStrategy>();
    _literalTypeSignatureIRStrategy = std::make_unique<LiteralTypeSignatureIRStrategy>();
    _classTypeSignatureIRStrategy = std::make_unique<ClassTypeSignatureIRStrategy>();
    _enumTypeSignatureIRStrategy = std::make_unique<EnumTypeSignatureIRStrategy>();
    _interfaceTypeSignatureIRStrategy = std::make_unique<InterfaceTypeSignatureIRStrategy>();
    _functionTypeSignatureIRStrategy = std::make_unique<FunctionTypeSignatureIRStrategy>();
    _lambdaTypeSignatureIRStrategy = std::make_unique<LambdaTypeSignatureIRStrategy>();
    _procedureTypeSignatureIRStrategy = std::make_unique<ProcedureTypeSignatureIRStrategy>();
    _parameterListTypeSignatureIRStrategy = std::make_unique<ParameterListTypeSignatureIRStrategy>();
    _parameterTypeSignatureIRStrategy = std::make_unique<ParameterTypeSignatureIRStrategy>();
    _structTypeSignatureIRStrategy = std::make_unique<StructTypeSignatureIRStrategy>();
    _tupleTypeSignatureIRStrategy = std::make_unique<TupleTypeSignatureIRStrategy>();
    _enumAccessTypeSignatureIRStrategy = std::make_unique<EnumAccessTypeSignatureIRStrategy>();
    _moduleTypeSignatureStrategy = std::make_unique<ModuleTypeSignatureIRStrategy>();
    _pointerTypeSignatureStrategy = std::make_unique<PointerTypeSignatureIRStrategy>();
    _refTypeSignatureStrategy = std::make_unique<RefTypeSignatureIRStrategy>();
    _functionInvocationTypeSignatureIRStrategy = std::make_unique<FunctionInvocationTypeSignatureIRStrategy>();
    _classMethodTypeSignatureIRStrategy = std::make_unique<ClassMethodTypeSignatureIRStrategy>();
    _classPropertyTypeSignatureIRStrategy = std::make_unique<ClassPropertyTypeSignatureIRStrategy>();
    _newClassInstanceTypeSignatureIRStrategy = std::make_unique<NewClassInstanceTypeSignatureIRStrategy>();
    _classInstanceTypeSignatureIRStrategy = std::make_unique<ClassInstanceTypeSignatureIRStrategy>();
    _lambdaScopeTypeSignatureIRStrategy = std::make_unique<LambdaScopeTypeSignatureIRStrategy>();
    _voidTypeSignatureIRStrategy = std::make_unique<VoidTypeSignatureIRStrategy>();
}

IntLiteralIRStrategy* IRStrategyMap::getIntLiteralIRStrategy() {
    return _intLiteralIRStrategy.get();
}

FloatLiteralIRStrategy* IRStrategyMap::getFloatLiteralIRStrategy() {
    return _floatLiteralIRStrategy.get();
}

CharLiteralIRStrategy* IRStrategyMap::getCharLiteralIRStrategy() {
    return _charLiteralIRStrategy.get();
}

StringLiteralIRStrategy* IRStrategyMap::getStringLiteralIRStrategy() {
    return _stringLiteralIRStrategy.get();
}

BoolLiteralIRStrategy* IRStrategyMap::getBoolLiteralIRStrategy() {
    return _boolLiteralIRStrategy.get();
}

LiteralExpressionIRStrategy* IRStrategyMap::getLiteralExpressionIRStrategy() {
    return _literalExpressionIRStrategy.get();
}

BinaryExpressionIRStrategy* IRStrategyMap::getBinaryExpressionIRStrategy() {
    return _binaryExpressionIRStrategy.get();
}

ConcatExpressionIRStrategy* IRStrategyMap::getConcatExpressionIRStrategy() {
    return _concatExpressionIRStrategy.get();
}

LogicalExpressionIRStrategy* IRStrategyMap::getLogicalExpressionIRStrategy() {
    return _logicalExpressionIRStrategy.get();
}

ArrayExpressionIRStrategy* IRStrategyMap::getArrayExpressionIRStrategy() {
    return _arrayExpressionIRStrategy.get();
}

ArrayAccessExpressionIRStrategy* IRStrategyMap::getArrayAccessExpressionIRStrategy() {
    return _arrayAccessExpressionIRStrategy.get();
}

ArrayAccessInvocationExpressionIRStrategy* IRStrategyMap::getArrayAccessInvocationExpressionIRStrategy() {
    return _arrayAccessInvocationExpressionIRStrategy.get();
}

StructExpressionIRStrategy* IRStrategyMap::getStructExpressionIRStrategy() {
    return _structExpressionIRStrategy.get();
}

UnaryExpressionIRStrategy* IRStrategyMap::getUnaryExpressionIRStrategy() {
    return _unaryExpressionIRStrategy.get();
}

TupleExpressionIRStrategy* IRStrategyMap::getTupleExpressionIRStrategy() {
    return _tupleExpressionIRStrategy.get();
}

ThisExpressionIRStrategy* IRStrategyMap::getThisExpressionIRStrategy() {
    return _thisExpressionIRStrategy.get();
}

IdentifierExpressionIRStrategy* IRStrategyMap::getIdentifierExpressionIRStrategy() {
    return _identifierExpressionIRStrategy.get();
}

VariableDeclarationIRStrategy* IRStrategyMap::getVariableDeclarationIRStrategy() {
    return _variableDeclarationIRStrategy.get();
}

FunctionDeclarationIRStrategy* IRStrategyMap::getFunctionDeclarationIRStrategy() {
    return _functionDeclarationIRStrategy.get();
}

FunctionParameterListIRStrategy* IRStrategyMap::getFunctionParameterListIRStrategy() {
    return _functionParameterListIRStrategy.get();
}

FunctionReturnExpressionIRStrategy* IRStrategyMap::getFunctionReturnExpressionIRStrategy() {
    return _functionReturnExpressionIRStrategy.get();
}

ProcedureDeclarationIRStrategy* IRStrategyMap::getProcedureDeclarationIRStrategy() {
    return _procedureDeclarationIRStrategy.get();
}

EnumDeclarationIRStrategy* IRStrategyMap::getEnumDeclarationIRStrategy() {
    return _enumDeclarationIRStrategy.get();
}

InterfaceTypeDeclarationIRStrategy* IRStrategyMap::getInterfaceTypeDeclarationIRStrategy() {
    return _interfaceTypeDeclarationIRStrategy.get();
}

CustomTypeDeclarationIRStrategy* IRStrategyMap::getCustomTypeDeclarationIRStrategy() {
    return _customTypeDeclarationIRStrategy.get();
}

ModuleDeclarationIRStrategy* IRStrategyMap::getModuleDeclarationIRStrategy() {
    return _moduleDeclarationIRStrategy.get();
}

ImportSingleModuleDeclarationIRStrategy* IRStrategyMap::getImportSingleModuleDeclarationIRStrategy() {
    return _importSingleModuleDeclarationIRStrategy.get();
}

ObjectAccessExpressionIRStrategy* IRStrategyMap::getObjectAccessExpressionIRStrategy() {
    return _objectAccessExpressionIRStrategy.get();
}

ObjectAccessInvocationExpressionIRStrategy* IRStrategyMap::getObjectAccessInvocationExpressionIRStrategy() {
    return _objectAccessInvocationExpressionIRStrategy.get();
}

TupleAccessExpressionIRStrategy* IRStrategyMap::getTupleAccessExpressionIRStrategy() {
    return _tupleAccessExpressionIRStrategy.get();
}

TupleAccessInvocationExpressionIRStrategy* IRStrategyMap::getTupleAccessInvocationExpressionIRStrategy() {
    return _tupleAccessInvocationExpressionIRStrategy.get();
}

FunctionInvocationExpressionIRStrategy* IRStrategyMap::getFunctionInvocationExpressionIRStrategy() {
    return _functionInvocationExpressionIRStrategy.get();
}

LambdaExpressionIRStrategy* IRStrategyMap::getLambdaExpressionIRStrategy() {
    return _lambdaExpressionIRStrategy.get();
}

ModuleAccessExpressionIRStrategy* IRStrategyMap::getModuleAccessExpressionIRStrategy() {
    return _moduleAccessExpressionIRStrategy.get();
}

ExpressionStatementIRStrategy* IRStrategyMap::getExpressionStatementIRStrategy() {
    return _expressionStatementIRStrategy.get();
}

ClassDeclarationIRStrategy* IRStrategyMap::getClassDeclarationIRStrategy() {
    return _classDeclarationIRStrategy.get();
}

ClassPropertyAccessExpressionIRStrategy* IRStrategyMap::getClassPropertyAccessExpressionIRStrategy() {
    return _classPropertyAccessExpressionIRStrategy.get();
}

ClassMethodInvocationExpressionIRStrategy* IRStrategyMap::getClassMethodInvocationExpressionIRStrategy() {
    return _classMethodInvocationExpressionIRStrategy.get();
}

NewClassInstanceExpressionIRStrategy* IRStrategyMap::getNewClassInstanceExpressionIRStrategy() {
    return _newClassInstanceExpressionIRStrategy.get();
}

ClassPropertyAssignmentStatementIRStrategy* IRStrategyMap::getClassPropertyAssignmentStatementIRStrategy() {
    return _classPropertyAssignmentStatementIRStrategy.get();
}

VariableAssignmentStatementIRStrategy* IRStrategyMap::getVariableAssignmentStatementIRStrategy() {
    return _variableAssignmentStatementIRStrategy.get();
}

ArrayAccessAssignmentStatementIRStrategy* IRStrategyMap::getArrayAccessAssignmentStatementIRStrategy() {
    return _arrayAccessAssignmentStatementIRStrategy.get();
}

ArrayAccessRefAssignmentStatementIRStrategy* IRStrategyMap::getArrayAccessRefAssignmentStatementIRStrategy() {
    return _arrayAccessRefAssignmentStatementIRStrategy.get();
}

ObjectAccessAssignmentStatementIRStrategy* IRStrategyMap::getObjectAccessAssignmentStatementIRStrategy() {
    return _objectAccessAssignmentStatementIRStrategy.get();
}

ObjectAccessRefAssignmentStatementIRStrategy* IRStrategyMap::getObjectAccessRefAssignmentStatementIRStrategy() {
    return _objectAccessRefAssignmentStatementIRStrategy.get();
}

TupleAccessAssignmentStatementIRStrategy* IRStrategyMap::getTupleAccessAssignmentStatementIRStrategy() {
    return _tupleAccessAssignmentStatementIRStrategy.get();
}

TupleAccessRefAssignmentStatementIRStrategy* IRStrategyMap::getTupleAccessRefAssignmentStatementIRStrategy() {
    return _tupleAccessRefAssignmentStatementIRStrategy.get();
}

ModuleAccessAssignmentStatementIRStrategy* IRStrategyMap::getModuleAccessAssignmentStatementIRStrategy() {
    return _moduleAccessAssignmentStatementIRStrategy.get();
}

ModuleAccessRefAssignmentStatementIRStrategy* IRStrategyMap::getModuleAccessRefAssignmentStatementIRStrategy() {
    return _moduleAccessRefAssignmentStatementIRStrategy.get();
}

ClassPropertyRefValueAssignmentStatementIRStrategy* IRStrategyMap::getClassPropertyRefValueAssignmentStatementIRStrategy() {
    return _classPropertyRefValueAssignmentStatementIRStrategy.get();
}

RefValueAssignmentStatementIRStrategy* IRStrategyMap::getRefValueAssignmentStatementIRStrategy() {
    return _refValueAssignmentStatementIRStrategy.get();
}

IfStatementIRStrategy* IRStrategyMap::getIfStatementIRStrategy() {
    return _ifStatementIRStrategy.get();
}

WhileStatementIRStrategy* IRStrategyMap::getWhileStatementIRStrategy() {
    return _whileStatementIRStrategy.get();
}

ForInStatementIRStrategy* IRStrategyMap::getForInStatementIRStrategy() {
    return _forInStatementIRStrategy.get();
}

RefExpressionIRStrategy* IRStrategyMap::getRefExpressionIRStrategy() {
    return _refExpressionIRStrategy.get();
}

DrefExpressionIRStrategy* IRStrategyMap::getDrefExpressionIRStrategy() {
    return _drefExpressionIRStrategy.get();
}

ArrayTypeSignatureIRStrategy* IRStrategyMap::getArrayTypeSignatureIRStrategy() {
    return _arrayTypeSignatureIRStrategy.get();
}

LiteralTypeSignatureIRStrategy* IRStrategyMap::getLiteralTypeSignatureIRStrategy() {
    return _literalTypeSignatureIRStrategy.get();
}

ClassTypeSignatureIRStrategy* IRStrategyMap::getClassTypeSignatureIRStrategy() {
    return _classTypeSignatureIRStrategy.get();
}

EnumTypeSignatureIRStrategy* IRStrategyMap::getEnumTypeSignatureIRStrategy() {
    return _enumTypeSignatureIRStrategy.get();
}

InterfaceTypeSignatureIRStrategy* IRStrategyMap::getInterfaceTypeSignatureIRStrategy() {
    return _interfaceTypeSignatureIRStrategy.get();
}

FunctionTypeSignatureIRStrategy* IRStrategyMap::getFunctionTypeSignatureIRStrategy() {
    return _functionTypeSignatureIRStrategy.get();
}

LambdaTypeSignatureIRStrategy* IRStrategyMap::getLambdaTypeSignatureIRStrategy() {
    return _lambdaTypeSignatureIRStrategy.get();
}

ProcedureTypeSignatureIRStrategy* IRStrategyMap::getProcedureTypeSignatureIRStrategy() {
    return _procedureTypeSignatureIRStrategy.get();
}

ParameterListTypeSignatureIRStrategy* IRStrategyMap::getParameterListTypeSignatureIRStrategy() {
    return _parameterListTypeSignatureIRStrategy.get();
}

ParameterTypeSignatureIRStrategy* IRStrategyMap::getParameterTypeSignatureIRStrategy() {
    return _parameterTypeSignatureIRStrategy.get();
}

StructTypeSignatureIRStrategy* IRStrategyMap::getStructTypeSignatureIRStrategy() {
    return _structTypeSignatureIRStrategy.get();
}

TupleTypeSignatureIRStrategy* IRStrategyMap::getTupleTypeSignatureIRStrategy() {
    return _tupleTypeSignatureIRStrategy.get();
}

EnumAccessTypeSignatureIRStrategy* IRStrategyMap::getEnumAccessTypeSignatureIRStrategy() {
    return _enumAccessTypeSignatureIRStrategy.get();
}

ModuleTypeSignatureIRStrategy* IRStrategyMap::getModuleTypeSignatureIRStrategy() {
    return _moduleTypeSignatureStrategy.get();
}

PointerTypeSignatureIRStrategy* IRStrategyMap::getPointerTypeSignatureIRStrategy() {
    return _pointerTypeSignatureStrategy.get();
}

RefTypeSignatureIRStrategy* IRStrategyMap::getRefTypeSignatureIRStrategy() {
    return _refTypeSignatureStrategy.get();
}

FunctionInvocationTypeSignatureIRStrategy* IRStrategyMap::getFunctionInvocationTypeSignatureIRStrategy() {
    return _functionInvocationTypeSignatureIRStrategy.get();
}

ClassMethodTypeSignatureIRStrategy* IRStrategyMap::getClassMethodTypeSignatureIRStrategy() {
    return _classMethodTypeSignatureIRStrategy.get();
}

ClassPropertyTypeSignatureIRStrategy* IRStrategyMap::getClassPropertyTypeSignatureIRStrategy() {
    return _classPropertyTypeSignatureIRStrategy.get();
}

NewClassInstanceTypeSignatureIRStrategy* IRStrategyMap::getNewClassInstanceTypeSignatureIRStrategy() {
    return _newClassInstanceTypeSignatureIRStrategy.get();
}

ClassInstanceTypeSignatureIRStrategy* IRStrategyMap::getClassInstanceTypeSignatureIRStrategy() {
    return _classInstanceTypeSignatureIRStrategy.get();
}

LambdaScopeTypeSignatureIRStrategy* IRStrategyMap::getLambdaScopeTypeSignatureIRStrategy() {
    return _lambdaScopeTypeSignatureIRStrategy.get();
}

VoidTypeSignatureIRStrategy* IRStrategyMap::getVoidTypeSignatureIRStrategy() {
    return _voidTypeSignatureIRStrategy.get();
}