//
// Created by Johny Georges on 2024-08-15.
//

#include "ir-injector.h"
#include "ir-injector-strategies/ir-injector-strategy.h"
#include "ir-injector-strategies/string-ir-injector-strategy/string-ir-injector-strategy.h"
#include "ir-injector-strategies/literal-ir-injector-strategy/literal-ir-injector-strategy.h"
#include "ir-injector-strategies/array-ir-injector-strategy/array-ir-injector-strategy.h"
#include "ir-injector-strategies/struct-ir-injector-strategy/struct-ir-injector-strategy.h"
#include "ir-injector-strategies/tuple-ir-injector-strategy/tuple-ir-injector-strategy.h"
#include "ir-injector-strategies/pointer-ir-injector-strategy/pointer-ir-injector-strategy.h"
#include "ir-injector-strategies/ref-ir-injector-strategy/ref-ir-injector-strategy.h"
#include "ir-injector-strategies/variable-ir-injector-strategy/variable-ir-injector-strategy.h"
#include "ir-injector-strategies/function-return-ir-injector-strategy/function-return-ir-injector-strategy.h"
#include "ir-injector-strategies/function-parameter-ir-injector-strategy/function-parameter-ir-injector-strategy.h"
#include "ir-injector-strategies/module-ir-injector-strategy/module-ir-injector-strategy.h"
#include "ir-injector-strategies/lambda-ir-injector-strategy/lambda-ir-injector-strategy.h"
#include "ir-injector-strategies/enum-ir-injector-strategy/enum-ir-injector-strategy.h"
#include "ir-injector-strategies/new-class-instance-ir-injector-strategy/new-class-instance-ir-injector-strategy.h"
#include "ir-injector-strategies/class-property-assignment-ir-injector-strategy/class-property-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/variable-assignment-ir-injector-strategy/variable-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/array-access-assignment-ir-injector-strategy/array-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/object-access-assignment-ir-injector-strategy/object-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/tuple-access-assignment-ir-injector-strategy/tuple-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/if-statement-ir-injector-strategy/if-statement-ir-injector-strategy.h"
#include "ir-injector-strategies/while-statement-ir-injector-strategy/while-statement-ir-injector-strategy.h"
#include "ir-injector-strategies/for-in-statement-ir-injector-strategy/for-in-statement-ir-injector-strategy.h"
#include "ir-injector-strategies/expression-statement-ir-injector-strategy/expression-statement-ir-injector-strategy.h"
#include "ir-injector-strategies/print-statement-ir-injector-strategy/print-statement-ir-injector-strategy.h"
#include "ir-injector-strategies/procedure-declaration-ir-injector-strategy/procedure-declaration-ir-injector-strategy.h"
#include "ir-injector-strategies/function-declaration-ir-injector-strategy/function-declaration-ir-injector-strategy.h"
#include "ir-injector-strategies/void-ir-injector-strategy/void-ir-injector-strategy.h"
#include "ir-injector-strategies/type-value-ir-injector-strategy/type-value-ir-injector-strategy.h"
#include "ir-injector-strategies/block-ir-injector-strategy/block-ir-injector-strategy.h"
#include "../../shared/utils/logger/logger.h"


IRInjector::IRInjector() {
    _injectorMap = std::unordered_map<TypeSource, IRInjectorStrategy*, std::hash<int>>();
    _stringIRInjector = new StringIRInjectorStrategy();
    _literalIRInjector = new LiteralIRInjectorStrategy();
    _arrayIRInjector = new ArrayIRInjectorStrategy();
    _structIRInjector = new StructIRInjectorStrategy();
    _tupleIRInjector = new TupleIRInjectorStrategy();
    _pointerIRInjector = new PointerIRInjectorStrategy();
    _voidIRInjector = new VoidIRInjectorStrategy();
    _refIRInjector = new RefIRInjectorStrategy();
    _variableIRInjector = new VariableIRInjectorStrategy();
    _lambdaIRInjector = new LambdaIRInjectorStrategy();
    _enumIRInjector = new EnumIRInjectorStrategy();
    _functionReturnIRInjector = new FunctionReturnIRInjectorStrategy();
    _newClassInstanceIRInjectorStrategy = new NewClassInstanceIRInjectorStrategy();
    _variableAssignmentIRInjectorStrategy = new VariableAssignmentIRInjectorStrategy();
    _arrayAccessAssignmentIRInjectorStrategy = new ArrayAccessAssignmentIRInjectorStrategy();
    _objectAccessAssignmentIRInjectorStrategy = new ObjectAccessAssignmentIRInjectorStrategy();
    _tupleAccessAssignmentIRInjectorStrategy = new TupleAccessAssignmentIRInjectorStrategy();
    _classPropertyAssignmentIRInjectorStrategy = new ClassPropertyAssignmentIRInjectorStrategy();
    _ifStatementIRInjectorStrategy = new IfStatementIRInjectorStrategy();
    _whileStatementIRInjectorStrategy = new WhileStatementIRInjectorStrategy();
    _forInStatementIRInjectorStrategy = new ForInStatementIRInjectorStrategy();
    _expressionStatementIRInjectorStrategy = new ExpressionStatementIRInjectorStrategy();
    _printStatementIRInjectorStrategy = new PrintStatementIRInjectorStrategy();
    _procedureDeclarationIRInjectorStrategy = new ProcedureDeclarationIRInjectorStrategy();
    _functionDeclarationIRInjectorStrategy = new FunctionDeclarationIRInjectorStrategy();
    _typeValueIRInjectorStrategy = new TypeValueIRInjectorStrategy();
    _blockIRInjectorStrategy = new BlockIRInjectorStrategy();
    this->init();
}

void IRInjector::init() {
    _injectorMap.insert(this->insert(ARRAY_TYPE_SOURCE, _arrayIRInjector));
    _injectorMap.insert(this->insert(STRUCT_TYPE_SOURCE, _structIRInjector));
    _injectorMap.insert(this->insert(STRING_LITERAL_TYPE_SOURCE, _stringIRInjector));
    _injectorMap.insert(this->insert(INT_LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(FLOAT_LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(BOOL_LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(CHAR_LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(LITERAL_TYPE_SOURCE, _literalIRInjector));
    _injectorMap.insert(this->insert(TUPLE_TYPE_SOURCE, _tupleIRInjector));
    _injectorMap.insert(this->insert(POINTER_TYPE_SOURCE, _pointerIRInjector));
    _injectorMap.insert(this->insert(REF_TYPE_SOURCE, _refIRInjector));
    _injectorMap.insert(this->insert(LAMBDA_TYPE_SOURCE, _lambdaIRInjector));
    _injectorMap.insert(this->insert(LAMBDA_EXPRESSION_TYPE_SOURCE, _lambdaIRInjector));
    _injectorMap.insert(this->insert(ENUM_TYPE_SOURCE, _enumIRInjector));
    _injectorMap.insert(this->insert(CLASS_INSTANCE_TYPE_SOURCE, _newClassInstanceIRInjectorStrategy));
    _injectorMap.insert(this->insert(VOID_TYPE_SOURCE, _voidIRInjector));
}

std::pair<TypeSource, IRInjectorStrategy*> IRInjector::insert(TypeSource typeSignature, IRInjectorStrategy* injector) {
    return std::pair { typeSignature, injector };
}


void IRInjector::inject(IRBlockNode* irBlock, IRNode* irNode, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irNode->isDeclaration()) {
        this->inject(irBlock, (IRDeclarationNode*)irNode, irModule, scope);
    } else if (irNode->isStatement()) {
        this->inject(irBlock, (IRStatementNode*)irNode, irModule, scope);
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irDeclaration->is(IR_VARIABLE_DECLARATION_NODE)) {
        _variableIRInjector->inject((IRVariableDeclarationNode*)irDeclaration, irBlock, this, irModule, scope);
    } else if (irDeclaration->is(IR_FUNCTION_PARAMETER_DECLARATION_NODE)) {
        _functionParameterIRInjector->inject((IRFunctionParameterDeclarationNode*)irDeclaration, irBlock, this, irModule);
    } else if (irDeclaration->is(IR_MODULE_DECLARATION_NODE)) {
        _moduleIRInjector->inject((IRModuleDeclarationNode*)irDeclaration, irBlock, this, irModule, scope);
    } else if (irDeclaration->is(IR_PROCEDURE_DECLARATION_NODE)) {
        _procedureDeclarationIRInjectorStrategy->inject((IRProcedureDeclarationNode*)irDeclaration, irBlock, this, irModule, scope);
    } else if (irDeclaration->is(IR_FUNCTION_DECLARATION_NODE)) {
        _functionDeclarationIRInjectorStrategy->inject((IRFunctionDeclarationNode*)irDeclaration, irBlock, this, irModule, scope);
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRStatementNode* irStatement, IRModuleNode* irModule, IRLookupTable* scope) {
    if (irStatement->is(IR_FUNCTION_RETURN_EXPRESSION_NODE)) {
        _functionReturnIRInjector->inject((IRFunctionReturnExpressionNode *) irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE)) {
        _classPropertyAssignmentIRInjectorStrategy->inject((IRClassPropertyAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_VARIABLE_ASSIGNMENT_STATEMENT_NODE)) {
        _variableAssignmentIRInjectorStrategy->inject((IRVariableAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _arrayAccessAssignmentIRInjectorStrategy->inject((IRArrayAccessAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _objectAccessAssignmentIRInjectorStrategy->inject((IRObjectAccessAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _tupleAccessAssignmentIRInjectorStrategy->inject((IRTupleAccessAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_IF_STATEMENT_NODE)) {
        _ifStatementIRInjectorStrategy->inject((IRIfStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_WHILE_STATEMENT_NODE)) {
        _whileStatementIRInjectorStrategy->inject((IRWhileStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_FOR_IN_STATEMENT_NODE)) {
        _forInStatementIRInjectorStrategy->inject((IRForInStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_EXPRESSION_STATEMENT_NODE)) {
        _expressionStatementIRInjectorStrategy->inject((IRExpressionStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_PRINT_STATEMENT_NODE)) {
        _printStatementIRInjectorStrategy->inject((IRPrintStatementNode*)irStatement, irBlock, this, irModule, scope);
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRBlockNode* irNode, IRModuleNode* irModule, IRLookupTable* scope) {
    _blockIRInjectorStrategy->inject(irNode, irBlock, this, irModule, scope);
}

llvm::Value* IRInjector::inject(IRBlockNode* irBlock, IRType* irType) {
    if (irBlock->containsInstruction(irType->getValue())) {

        return irType->getValue()->getValue();
    }
    return _typeValueIRInjectorStrategy->inject(irType, irBlock);
}

llvm::Value* IRInjector::inject(IRBlockNode* irBlock, IRExpressionNode* irExpression, IROperation* irOperation, IRModuleNode* irModule, IRLookupTable* scope) {
    auto injector = _injectorMap.find(irExpression->getInjectorTypeSource());
    if (injector == _injectorMap.end()) {
        irExpression->getTypeSignature()->print();
        throw std::invalid_argument("unable to find injector for expression with type signature: " + std::to_string(irExpression->getInjectorTypeSource()));
    }
    return injector->second->inject(irExpression, irBlock, this, irOperation, irModule, scope);
}

void IRInjector::injectVoidReturnType(IRBlockNode* irBlock) {
    irBlock->getBuilder()->get()->CreateRet(irBlock->getBuilder()->get()->getInt64(0));
}