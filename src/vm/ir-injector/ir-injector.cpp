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
#include "ir-injector-strategies/class-instance-ir-injector-strategy/class-instance-ir-injector-strategy.h"
#include "ir-injector-strategies/class-property-assignment-ir-injector-strategy/class-property-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/class-property-ref-value-assignment-ir-injector-strategy/class-property-ref-value-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/ref-value-assignment-ir-injector-strategy/ref-value-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/variable-assignment-ir-injector-strategy/variable-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/array-access-assignment-ir-injector-strategy/array-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/object-access-assignment-ir-injector-strategy/object-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/tuple-access-assignment-ir-injector-strategy/tuple-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/module-access-assignment-ir-injector-strategy/module-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/class-static-property-assignment-ir-injector-strategy/class-static-property-assignment-ir-injector-strategy.h"
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
#include "ir-injector-strategies/class-ir-injector-strategy/class-ir-injector-strategy.h"
#include "../../shared/utils/logger/logger.h"


IRInjector::IRInjector() {
    _injectorMap = std::unordered_map<TypeSource, std::shared_ptr<IRInjectorStrategy>, std::hash<int>>();
    _stringIRInjector = std::make_shared<StringIRInjectorStrategy>();
    _literalIRInjector = std::make_shared<LiteralIRInjectorStrategy>();
    _arrayIRInjector =  std::make_shared<ArrayIRInjectorStrategy>();
    _structIRInjector = std::make_shared<StructIRInjectorStrategy>();
    _tupleIRInjector = std::make_shared<TupleIRInjectorStrategy>();
    _pointerIRInjector = std::make_shared<PointerIRInjectorStrategy>();
    _voidIRInjector = std::make_shared<VoidIRInjectorStrategy>();
    _refIRInjector = std::make_shared<RefIRInjectorStrategy>();
    _lambdaIRInjector = std::make_shared<LambdaIRInjectorStrategy>();
    _enumIRInjector = std::make_shared<EnumIRInjectorStrategy>();
    _newClassInstanceIRInjectorStrategy = std::make_shared<NewClassInstanceIRInjectorStrategy>();
    _classInstanceIRInjectorStrategy = std::make_shared<ClassInstanceIRInjectorStrategy>();
    _variableIRInjector = new VariableIRInjectorStrategy();
    _functionReturnIRInjector = new FunctionReturnIRInjectorStrategy();
    _variableAssignmentIRInjectorStrategy = new VariableAssignmentIRInjectorStrategy();
    _arrayAccessAssignmentIRInjectorStrategy = new ArrayAccessAssignmentIRInjectorStrategy();
    _objectAccessAssignmentIRInjectorStrategy = new ObjectAccessAssignmentIRInjectorStrategy();
    _tupleAccessAssignmentIRInjectorStrategy = new TupleAccessAssignmentIRInjectorStrategy();
    _moduleAccessAssignmentIRInjectorStrategy = new ModuleAccessAssignmentIRInjectorStrategy();
    _classStaticPropertyAssignmentIRInjectorStrategy = new ClassStaticPropertyAssignmentIRInjectorStrategy();
    _classPropertyAssignmentIRInjectorStrategy = new ClassPropertyAssignmentIRInjectorStrategy();
    _classPropertyRefValueAssignmentIRInjectorStrategy = new ClassPropertyRefValueAssignmentIRInjectorStrategy();
    _refValueAssignmentIRInjectorStrategy = new RefValueAssignmentIRInjectorStrategy();
    _ifStatementIRInjectorStrategy = new IfStatementIRInjectorStrategy();
    _whileStatementIRInjectorStrategy = new WhileStatementIRInjectorStrategy();
    _forInStatementIRInjectorStrategy = new ForInStatementIRInjectorStrategy();
    _expressionStatementIRInjectorStrategy = new ExpressionStatementIRInjectorStrategy();
    _printStatementIRInjectorStrategy = new PrintStatementIRInjectorStrategy();
    _procedureDeclarationIRInjectorStrategy = new ProcedureDeclarationIRInjectorStrategy();
    _functionDeclarationIRInjectorStrategy = new FunctionDeclarationIRInjectorStrategy();
    _typeValueIRInjectorStrategy = new TypeValueIRInjectorStrategy();
    _blockIRInjectorStrategy = new BlockIRInjectorStrategy();
    _classIRInjectorStrategy = new ClassIRInjectorStrategy();
    this->init();
}

void IRInjector::init() {
    _injectorMap[ARRAY_TYPE_SOURCE] = _arrayIRInjector;
    _injectorMap[STRUCT_TYPE_SOURCE] = _structIRInjector;
    _injectorMap[STRING_LITERAL_TYPE_SOURCE] = _stringIRInjector;
    _injectorMap[INT_LITERAL_TYPE_SOURCE] = _literalIRInjector;
    _injectorMap[FLOAT_LITERAL_TYPE_SOURCE] = _literalIRInjector;
    _injectorMap[BOOL_LITERAL_TYPE_SOURCE] = _literalIRInjector;
    _injectorMap[CHAR_LITERAL_TYPE_SOURCE] = _literalIRInjector;
    _injectorMap[LITERAL_TYPE_SOURCE] = _literalIRInjector;
    _injectorMap[TUPLE_TYPE_SOURCE] = _tupleIRInjector;
    _injectorMap[POINTER_TYPE_SOURCE] = _pointerIRInjector;
    _injectorMap[REF_TYPE_SOURCE] = _refIRInjector;
    _injectorMap[LAMBDA_TYPE_SOURCE] = _lambdaIRInjector;
    _injectorMap[LAMBDA_EXPRESSION_TYPE_SOURCE] = _lambdaIRInjector;
    _injectorMap[ENUM_TYPE_SOURCE] = _enumIRInjector;
    _injectorMap[NEW_CLASS_INSTANCE_TYPE_SOURCE] = _newClassInstanceIRInjectorStrategy;
    _injectorMap[CLASS_INSTANCE_TYPE_SOURCE] = _classInstanceIRInjectorStrategy;
    _injectorMap[VOID_TYPE_SOURCE] = _voidIRInjector;
}

std::pair<TypeSource, IRInjectorStrategy*> IRInjector::insert(TypeSource typeSignature, IRInjectorStrategy* injector) {
    return std::pair { typeSignature, injector };
}


void IRInjector::inject(IRBlockNode* irBlock, IRNode* irNode, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irNode->isDeclaration()) {
        this->inject(irBlock, (IRDeclarationNode*)irNode, irModule, scope);
    } else if (irNode->isStatement()) {
        this->inject(irBlock, (IRStatementNode*)irNode, irModule, scope);
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRDeclarationNode* irDeclaration, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
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
    } else if (irDeclaration->is(IR_CLASS_DECLARATION_NODE)) {
        _classIRInjectorStrategy->inject((IRClassDeclarationNode*)irDeclaration, irBlock, this, irModule, scope);
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRStatementNode* irStatement, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    if (irStatement->is(IR_FUNCTION_RETURN_EXPRESSION_NODE)) {
        _functionReturnIRInjector->inject((IRFunctionReturnExpressionNode *) irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE)) {
        _classPropertyAssignmentIRInjectorStrategy->inject((IRClassPropertyAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        _classPropertyRefValueAssignmentIRInjectorStrategy->inject((IRClassPropertyRefValueAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_REF_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        _refValueAssignmentIRInjectorStrategy->inject((IRRefValueAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_VARIABLE_ASSIGNMENT_STATEMENT_NODE)) {
        _variableAssignmentIRInjectorStrategy->inject((IRVariableAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _arrayAccessAssignmentIRInjectorStrategy->inject((IRArrayAccessAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _objectAccessAssignmentIRInjectorStrategy->inject((IRObjectAccessAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _tupleAccessAssignmentIRInjectorStrategy->inject((IRTupleAccessAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _moduleAccessAssignmentIRInjectorStrategy->inject((IRModuleAccessAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
    } else if (irStatement->is(IR_CLASS_STATIC_PROPERTY_ASSIGNMENT_STATEMENT_NODE)) {
        _classStaticPropertyAssignmentIRInjectorStrategy->inject((IRClassStaticPropertyAssignmentStatementNode*)irStatement, irBlock, this, irModule, scope);
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
    } else {
        throw std::invalid_argument("unable to find injector for statement " + std::to_string(irStatement->getNodeType()));
    }
}

void IRInjector::inject(IRBlockNode* irBlock, IRBlockNode* irNode, std::shared_ptr<IRModuleNode> irModule) {
    _blockIRInjectorStrategy->inject(irNode, irBlock, this, irModule);
}

llvm::Value* IRInjector::inject(IRBlockNode* irBlock, IRType* irType, std::shared_ptr<IRModuleNode> irModule) {
    return _typeValueIRInjectorStrategy->inject(irType, irBlock, this, irModule);
}

llvm::Value* IRInjector::inject(IRBlockNode* irBlock, IRExpressionNode* irExpression, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto injector = _injectorMap.find(irExpression->getInjectorTypeSource());
    if (injector == _injectorMap.end()) {
        irExpression->getTypeSignature()->print();
        Logger::log(irExpression->toString());
        throw std::invalid_argument("unable to find injector for expression with type signature: " + std::to_string(irExpression->getInjectorTypeSource()));
    }
    if (irExpression->needsToBeFreed()) {
        Logger::log("found ir-expression that needs to be freed!", irExpression->toString(), irExpression->isAssigned());
        irBlock->addExpressionToFree(irExpression);
    }
    return injector->second.get()->inject(irExpression, irBlock, this, irOperation, irModule, scope);
}

void IRInjector::injectVoidReturnType(IRBlockNode* irBlock) {
    irBlock->getBuilder()->get()->CreateRet(irBlock->getBuilder()->get()->getInt64(0));
}

llvm::Value* IRInjector::injectStringGlobalVariable(IRBlockNode* irBlock, std::string id, std::string rawString, std::shared_ptr<IRModuleNode> irModule) {
    auto existingStringGlobalVariable = irModule->getModule()->get()->getGlobalVariable(id);
    if (existingStringGlobalVariable != nullptr) {
        return existingStringGlobalVariable;
    }
    auto irString = llvm::ConstantDataArray::getString(irModule.get()->getModule()->get()->getContext(), rawString);
    auto stringGlobalVariable = new llvm::GlobalVariable(
            *irModule->getModule()->get(),
            irString->getType(),
            true,
            llvm::GlobalValue::LinkOnceAnyLinkage,
            irString,
            id
    );
    return stringGlobalVariable;
}

llvm::AllocaInst* IRInjector::injectRawString(IRBlockNode* irBlock, std::string rawString) {
    auto irString = llvm::ConstantDataArray::getString(irBlock->getBuilder()->get()->getContext(), rawString);
    auto alloca = irBlock->getBuilder()->get()->CreateAlloca(irString->getType());
    irBlock->getBuilder()->get()->CreateStore(irString, alloca);
    return alloca;
}
