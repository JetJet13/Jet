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
#include "./expression-ir-strategies/identifier-expression-ir-strategy/identifier-expression-ir-strategy.h"
#include "./expression-ir-strategies/object-access-expression-ir-strategy/object-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/object-access-invocation-expression-ir-strategy/object-access-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-access-expression-ir-strategy/tuple-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/tuple-access-invocation-expression-ir-strategy/tuple-access-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/function-invocation-expression-ir-strategy/function-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/lambda-expression-ir-strategy/lambda-expression-ir-strategy.h"
#include "./expression-ir-strategies/class-property-access-expression-ir-strategy/class-property-access-expression-ir-strategy.h"
#include "./expression-ir-strategies/class-method-invocation-expression-ir-strategy/class-method-invocation-expression-ir-strategy.h"
#include "./expression-ir-strategies/new-class-instance-expression-ir-strategy/new-class-instance-expression-ir-strategy.h"
#include "./expression-ir-strategies/ref-expression-ir-strategy/ref-expression-ir-strategy.h"
#include "./expression-ir-strategies/dref-expression-ir-strategy/dref-expression-ir-strategy.h"
#include "./expression-ir-strategies/sref-expression-ir-strategy/sref-expression-ir-strategy.h"
#include "./expression-statement-ir-strategy/expression-statement-ir-strategy.h"
#include "./print-statement-ir-strategy/print-statement-ir-strategy.h"
#include "./class-property-assignment-statement-ir-strategy/class-property-assignment-statement-ir-strategy.h"
#include "./class-property-ref-value-assignment-statement-ir-strategy/class-property-ref-value-assignment-statement-ir-strategy.h"
#include "./ref-value-assignment-statement-ir-strategy/ref-value-assignment-statement-ir-strategy.h"
#include "./variable-assignment-statement-ir-strategy/variable-assignment-statement-ir-strategy.h"
#include "./array-access-assignment-statement-ir-strategy/array-access-assignment-statement-ir-strategy.h"
#include "./object-access-assignment-statement-ir-strategy/object-access-assignment-statement-ir-strategy.h"
#include "./tuple-access-assignment-statement-ir-strategy/tuple-access-assignment-statement-ir-strategy.h"
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
    _intLiteralIRStrategy = new IntLiteralIRStrategy();
    _floatLiteralIRStrategy = new FloatLiteralIRStrategy();
    _charLiteralIRStrategy = new CharLiteralIRStrategy();
    _stringLiteralIRStrategy = new StringLiteralIRStrategy();
    _boolLiteralIRStrategy = new BoolLiteralIRStrategy();
    _literalExpressionIRStrategy = new LiteralExpressionIRStrategy();
    _binaryExpressionIRStrategy = new BinaryExpressionIRStrategy();
    _concatExpressionIRStrategy = new ConcatExpressionIRStrategy();
    _logicalExpressionIRStrategy = new LogicalExpressionIRStrategy();
    _arrayExpressionIRStrategy = new ArrayExpressionIRStrategy();
    _structExpressionIRStrategy = new StructExpressionIRStrategy();
    _arrayAccessExpressionIRStrategy = new ArrayAccessExpressionIRStrategy();
    _arrayAccessInvocationExpressionIRStrategy = new ArrayAccessInvocationExpressionIRStrategy();
    _unaryExpressionIRStrategy = new UnaryExpressionIRStrategy();
    _tupleExpressionIRStrategy = new TupleExpressionIRStrategy();
    _identifierExpressionIRStrategy = new IdentifierExpressionIRStrategy();
    _variableDeclarationIRStrategy = new VariableDeclarationIRStrategy();
    _functionDeclarationIRStrategy = new FunctionDeclarationIRStrategy();
    _functionParameterListIRStrategy = new FunctionParameterListIRStrategy();
    _functionReturnExpressionIRStrategy = new FunctionReturnExpressionIRStrategy();
    _procedureDeclarationIRStrategy = new ProcedureDeclarationIRStrategy();
    _enumDeclarationIRStrategy = new EnumDeclarationIRStrategy();
    _interfaceTypeDeclarationIRStrategy = new InterfaceTypeDeclarationIRStrategy();
    _customTypeDeclarationIRStrategy = new CustomTypeDeclarationIRStrategy();
    _moduleDeclarationIRStrategy = new ModuleDeclarationIRStrategy();
    _importSingleModuleDeclarationIRStrategy = new ImportSingleModuleDeclarationIRStrategy();
    _objectAccessExpressionIRStrategy = new ObjectAccessExpressionIRStrategy();
    _objectAccessInvocationExpressionIRStrategy = new ObjectAccessInvocationExpressionIRStrategy();
    _tupleAccessExpressionIRStrategy = new TupleAccessExpressionIRStrategy();
    _tupleAccessInvocationExpressionIRStrategy = new TupleAccessInvocationExpressionIRStrategy();
    _functionInvocationExpressionIRStrategy = new FunctionInvocationExpressionIRStrategy();
    _lambdaExpressionIRStrategy = new LambdaExpressionIRStrategy();
    _expressionStatementIRStrategy = new ExpressionStatementIRStrategy();
    _printStatementIRStrategy = new PrintStatementIRStrategy();
    _classDeclarationIRStrategy = new ClassDeclarationIRStrategy();
    _classPropertyAccessExpressionIRStrategy = new ClassPropertyAccessExpressionIRStrategy();
    _classMethodInvocationExpressionIRStrategy = new ClassMethodInvocationExpressionIRStrategy();
    _newClassInstanceExpressionIRStrategy = new NewClassInstanceExpressionIRStrategy();
    _classPropertyAssignmentStatementIRStrategy = new ClassPropertyAssignmentStatementIRStrategy();
    _variableAssignmentStatementIRStrategy = new VariableAssignmentStatementIRStrategy();
    _arrayAccessAssignmentStatementIRStrategy = new ArrayAccessAssignmentStatementIRStrategy();
    _objectAccessAssignmentStatementIRStrategy = new ObjectAccessAssignmentStatementIRStrategy();
    _tupleAccessAssignmentStatementIRStrategy = new TupleAccessAssignmentStatementIRStrategy();
    _classPropertyRefValueAssignmentStatementIRStrategy = new ClassPropertyRefValueAssignmentStatementIRStrategy();
    _refValueAssignmentStatementIRStrategy = new RefValueAssignmentStatementIRStrategy();
    _ifStatementIRStrategy = new IfStatementIRStrategy();
    _whileStatementIRStrategy = new WhileStatementIRStrategy();
    _forInStatementIRStrategy = new ForInStatementIRStrategy();
    _refExpressionIRStrategy = new RefExpressionIRStrategy();
    _drefExpressionIRStrategy = new DrefExpressionIRStrategy();
    _srefExpressionIRStrategy = new SrefExpressionIRStrategy();

    _arrayTypeSignatureIRStrategy = new ArrayTypeSignatureIRStrategy();
    _literalTypeSignatureIRStrategy = new LiteralTypeSignatureIRStrategy();
    _classTypeSignatureIRStrategy = new ClassTypeSignatureIRStrategy();
    _enumTypeSignatureIRStrategy = new EnumTypeSignatureIRStrategy();
    _interfaceTypeSignatureIRStrategy = new InterfaceTypeSignatureIRStrategy();
    _functionTypeSignatureIRStrategy = new FunctionTypeSignatureIRStrategy();
    _lambdaTypeSignatureIRStrategy = new LambdaTypeSignatureIRStrategy();
    _procedureTypeSignatureIRStrategy = new ProcedureTypeSignatureIRStrategy();
    _parameterListTypeSignatureIRStrategy = new ParameterListTypeSignatureIRStrategy();
    _parameterTypeSignatureIRStrategy = new ParameterTypeSignatureIRStrategy();
    _structTypeSignatureIRStrategy = new StructTypeSignatureIRStrategy();
    _tupleTypeSignatureIRStrategy = new TupleTypeSignatureIRStrategy();
    _enumAccessTypeSignatureIRStrategy = new EnumAccessTypeSignatureIRStrategy();
    _moduleTypeSignatureStrategy = new ModuleTypeSignatureIRStrategy();
    _pointerTypeSignatureStrategy = new PointerTypeSignatureIRStrategy();
    _refTypeSignatureStrategy = new RefTypeSignatureIRStrategy();
    _functionInvocationTypeSignatureIRStrategy = new FunctionInvocationTypeSignatureIRStrategy();
    _classMethodTypeSignatureIRStrategy = new ClassMethodTypeSignatureIRStrategy();
    _classPropertyTypeSignatureIRStrategy = new ClassPropertyTypeSignatureIRStrategy();
    _newClassInstanceTypeSignatureIRStrategy = new NewClassInstanceTypeSignatureIRStrategy();
    _classInstanceTypeSignatureIRStrategy = new ClassInstanceTypeSignatureIRStrategy();
    _lambdaScopeTypeSignatureIRStrategy = new LambdaScopeTypeSignatureIRStrategy();
    _voidTypeSignatureIRStrategy = new VoidTypeSignatureIRStrategy();
}

IntLiteralIRStrategy* IRStrategyMap::getIntLiteralIRStrategy() {
    return _intLiteralIRStrategy;
}

FloatLiteralIRStrategy* IRStrategyMap::getFloatLiteralIRStrategy() {
    return _floatLiteralIRStrategy;
}

CharLiteralIRStrategy* IRStrategyMap::getCharLiteralIRStrategy() {
    return _charLiteralIRStrategy;
}

StringLiteralIRStrategy* IRStrategyMap::getStringLiteralIRStrategy() {
    return _stringLiteralIRStrategy;
}

BoolLiteralIRStrategy* IRStrategyMap::getBoolLiteralIRStrategy() {
    return _boolLiteralIRStrategy;
}

LiteralExpressionIRStrategy* IRStrategyMap::getLiteralExpressionIRStrategy() {
    return _literalExpressionIRStrategy;
}

BinaryExpressionIRStrategy* IRStrategyMap::getBinaryExpressionIRStrategy() {
    return _binaryExpressionIRStrategy;
}

ConcatExpressionIRStrategy* IRStrategyMap::getConcatExpressionIRStrategy() {
    return _concatExpressionIRStrategy;
}

LogicalExpressionIRStrategy* IRStrategyMap::getLogicalExpressionIRStrategy() {
    return _logicalExpressionIRStrategy;
}

ArrayExpressionIRStrategy* IRStrategyMap::getArrayExpressionIRStrategy() {
    return _arrayExpressionIRStrategy;
}

ArrayAccessExpressionIRStrategy* IRStrategyMap::getArrayAccessExpressionIRStrategy() {
    return _arrayAccessExpressionIRStrategy;
}

ArrayAccessInvocationExpressionIRStrategy* IRStrategyMap::getArrayAccessInvocationExpressionIRStrategy() {
    return _arrayAccessInvocationExpressionIRStrategy;
}

StructExpressionIRStrategy* IRStrategyMap::getStructExpressionIRStrategy() {
    return _structExpressionIRStrategy;
}

UnaryExpressionIRStrategy* IRStrategyMap::getUnaryExpressionIRStrategy() {
    return _unaryExpressionIRStrategy;
}

TupleExpressionIRStrategy* IRStrategyMap::getTupleExpressionIRStrategy() {
    return _tupleExpressionIRStrategy;
}

IdentifierExpressionIRStrategy* IRStrategyMap::getIdentifierExpressionIRStrategy() {
    return _identifierExpressionIRStrategy;
}

VariableDeclarationIRStrategy* IRStrategyMap::getVariableDeclarationIRStrategy() {
    return _variableDeclarationIRStrategy;
}

FunctionDeclarationIRStrategy* IRStrategyMap::getFunctionDeclarationIRStrategy() {
    return _functionDeclarationIRStrategy;
}

FunctionParameterListIRStrategy* IRStrategyMap::getFunctionParameterListIRStrategy() {
    return _functionParameterListIRStrategy;
}

FunctionReturnExpressionIRStrategy* IRStrategyMap::getFunctionReturnExpressionIRStrategy() {
    return _functionReturnExpressionIRStrategy;
}

ProcedureDeclarationIRStrategy* IRStrategyMap::getProcedureDeclarationIRStrategy() {
    return _procedureDeclarationIRStrategy;
}

EnumDeclarationIRStrategy* IRStrategyMap::getEnumDeclarationIRStrategy() {
    return _enumDeclarationIRStrategy;
}

InterfaceTypeDeclarationIRStrategy* IRStrategyMap::getInterfaceTypeDeclarationIRStrategy() {
    return _interfaceTypeDeclarationIRStrategy;
}

CustomTypeDeclarationIRStrategy* IRStrategyMap::getCustomTypeDeclarationIRStrategy() {
    return _customTypeDeclarationIRStrategy;
}

ModuleDeclarationIRStrategy* IRStrategyMap::getModuleDeclarationIRStrategy() {
    return _moduleDeclarationIRStrategy;
}

ImportSingleModuleDeclarationIRStrategy* IRStrategyMap::getImportSingleModuleDeclarationIRStrategy() {
    return _importSingleModuleDeclarationIRStrategy;
}

ObjectAccessExpressionIRStrategy* IRStrategyMap::getObjectAccessExpressionIRStrategy() {
    return _objectAccessExpressionIRStrategy;
}

ObjectAccessInvocationExpressionIRStrategy* IRStrategyMap::getObjectAccessInvocationExpressionIRStrategy() {
    return _objectAccessInvocationExpressionIRStrategy;
}

TupleAccessExpressionIRStrategy* IRStrategyMap::getTupleAccessExpressionIRStrategy() {
    return _tupleAccessExpressionIRStrategy;
}

TupleAccessInvocationExpressionIRStrategy* IRStrategyMap::getTupleAccessInvocationExpressionIRStrategy() {
    return _tupleAccessInvocationExpressionIRStrategy;
}

FunctionInvocationExpressionIRStrategy* IRStrategyMap::getFunctionInvocationExpressionIRStrategy() {
    return _functionInvocationExpressionIRStrategy;
}

LambdaExpressionIRStrategy* IRStrategyMap::getLambdaExpressionIRStrategy() {
    return _lambdaExpressionIRStrategy;
}

ExpressionStatementIRStrategy* IRStrategyMap::getExpressionStatementIRStrategy() {
    return _expressionStatementIRStrategy;
}

PrintStatementIRStrategy* IRStrategyMap::getPrintStatementIRStrategy() {
    return _printStatementIRStrategy;
}

ClassDeclarationIRStrategy* IRStrategyMap::getClassDeclarationIRStrategy() {
    return _classDeclarationIRStrategy;
}

ClassPropertyAccessExpressionIRStrategy* IRStrategyMap::getClassPropertyAccessExpressionIRStrategy() {
    return _classPropertyAccessExpressionIRStrategy;
}

ClassMethodInvocationExpressionIRStrategy* IRStrategyMap::getClassMethodInvocationExpressionIRStrategy() {
    return _classMethodInvocationExpressionIRStrategy;
}

NewClassInstanceExpressionIRStrategy* IRStrategyMap::getNewClassInstanceExpressionIRStrategy() {
    return _newClassInstanceExpressionIRStrategy;
}

ClassPropertyAssignmentStatementIRStrategy* IRStrategyMap::getClassPropertyAssignmentStatementIRStrategy() {
    return _classPropertyAssignmentStatementIRStrategy;
}

VariableAssignmentStatementIRStrategy* IRStrategyMap::getVariableAssignmentStatementIRStrategy() {
    return _variableAssignmentStatementIRStrategy;
}

ArrayAccessAssignmentStatementIRStrategy* IRStrategyMap::getArrayAccessAssignmentStatementIRStrategy() {
    return _arrayAccessAssignmentStatementIRStrategy;
}

ObjectAccessAssignmentStatementIRStrategy* IRStrategyMap::getObjectAccessAssignmentStatementIRStrategy() {
    return _objectAccessAssignmentStatementIRStrategy;
}

TupleAccessAssignmentStatementIRStrategy* IRStrategyMap::getTupleAccessAssignmentStatementIRStrategy() {
    return _tupleAccessAssignmentStatementIRStrategy;
}

ClassPropertyRefValueAssignmentStatementIRStrategy* IRStrategyMap::getClassPropertyRefValueAssignmentStatementIRStrategy() {
    return _classPropertyRefValueAssignmentStatementIRStrategy;
}

RefValueAssignmentStatementIRStrategy* IRStrategyMap::getRefValueAssignmentStatementIRStrategy() {
    return _refValueAssignmentStatementIRStrategy;
}

IfStatementIRStrategy* IRStrategyMap::getIfStatementIRStrategy() {
    return _ifStatementIRStrategy;
}

WhileStatementIRStrategy* IRStrategyMap::getWhileStatementIRStrategy() {
    return _whileStatementIRStrategy;
}

ForInStatementIRStrategy* IRStrategyMap::getForInStatementIRStrategy() {
    return _forInStatementIRStrategy;
}

RefExpressionIRStrategy* IRStrategyMap::getRefExpressionIRStrategy() {
    return _refExpressionIRStrategy;
}

DrefExpressionIRStrategy* IRStrategyMap::getDrefExpressionIRStrategy() {
    return _drefExpressionIRStrategy;
}

SrefExpressionIRStrategy* IRStrategyMap::getSrefExpressionIRStrategy() {
    return _srefExpressionIRStrategy;
}

ArrayTypeSignatureIRStrategy* IRStrategyMap::getArrayTypeSignatureIRStrategy() {
    return _arrayTypeSignatureIRStrategy;
}

LiteralTypeSignatureIRStrategy* IRStrategyMap::getLiteralTypeSignatureIRStrategy() {
    return _literalTypeSignatureIRStrategy;
}

ClassTypeSignatureIRStrategy* IRStrategyMap::getClassTypeSignatureIRStrategy() {
    return _classTypeSignatureIRStrategy;
}

EnumTypeSignatureIRStrategy* IRStrategyMap::getEnumTypeSignatureIRStrategy() {
    return _enumTypeSignatureIRStrategy;
}

InterfaceTypeSignatureIRStrategy* IRStrategyMap::getInterfaceTypeSignatureIRStrategy() {
    return _interfaceTypeSignatureIRStrategy;
}

FunctionTypeSignatureIRStrategy* IRStrategyMap::getFunctionTypeSignatureIRStrategy() {
    return _functionTypeSignatureIRStrategy;
}

LambdaTypeSignatureIRStrategy* IRStrategyMap::getLambdaTypeSignatureIRStrategy() {
    return _lambdaTypeSignatureIRStrategy;
}

ProcedureTypeSignatureIRStrategy* IRStrategyMap::getProcedureTypeSignatureIRStrategy() {
    return _procedureTypeSignatureIRStrategy;
}

ParameterListTypeSignatureIRStrategy* IRStrategyMap::getParameterListTypeSignatureIRStrategy() {
    return _parameterListTypeSignatureIRStrategy;
}

ParameterTypeSignatureIRStrategy* IRStrategyMap::getParameterTypeSignatureIRStrategy() {
    return _parameterTypeSignatureIRStrategy;
}

StructTypeSignatureIRStrategy* IRStrategyMap::getStructTypeSignatureIRStrategy() {
    return _structTypeSignatureIRStrategy;
}

TupleTypeSignatureIRStrategy* IRStrategyMap::getTupleTypeSignatureIRStrategy() {
    return _tupleTypeSignatureIRStrategy;
}

EnumAccessTypeSignatureIRStrategy* IRStrategyMap::getEnumAccessTypeSignatureIRStrategy() {
    return _enumAccessTypeSignatureIRStrategy;
}

ModuleTypeSignatureIRStrategy* IRStrategyMap::getModuleTypeSignatureIRStrategy() {
    return _moduleTypeSignatureStrategy;
}

PointerTypeSignatureIRStrategy* IRStrategyMap::getPointerTypeSignatureIRStrategy() {
    return _pointerTypeSignatureStrategy;
}

RefTypeSignatureIRStrategy* IRStrategyMap::getRefTypeSignatureIRStrategy() {
    return _refTypeSignatureStrategy;
}

FunctionInvocationTypeSignatureIRStrategy* IRStrategyMap::getFunctionInvocationTypeSignatureIRStrategy() {
    return _functionInvocationTypeSignatureIRStrategy;
}

ClassMethodTypeSignatureIRStrategy* IRStrategyMap::getClassMethodTypeSignatureIRStrategy() {
    return _classMethodTypeSignatureIRStrategy;
}

ClassPropertyTypeSignatureIRStrategy* IRStrategyMap::getClassPropertyTypeSignatureIRStrategy() {
    return _classPropertyTypeSignatureIRStrategy;
}

NewClassInstanceTypeSignatureIRStrategy* IRStrategyMap::getNewClassInstanceTypeSignatureIRStrategy() {
    return _newClassInstanceTypeSignatureIRStrategy;
}

ClassInstanceTypeSignatureIRStrategy* IRStrategyMap::getClassInstanceTypeSignatureIRStrategy() {
    return _classInstanceTypeSignatureIRStrategy;
}

LambdaScopeTypeSignatureIRStrategy* IRStrategyMap::getLambdaScopeTypeSignatureIRStrategy() {
    return _lambdaScopeTypeSignatureIRStrategy;
}

VoidTypeSignatureIRStrategy* IRStrategyMap::getVoidTypeSignatureIRStrategy() {
    return _voidTypeSignatureIRStrategy;
}