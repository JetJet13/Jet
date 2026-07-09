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
#include "ir-injector-strategies/array-access-ref-assignment-ir-injector-strategy/array-access-ref-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/object-access-assignment-ir-injector-strategy/object-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/object-access-ref-assignment-ir-injector-strategy/object-access-ref-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/tuple-access-assignment-ir-injector-strategy/tuple-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/tuple-access-ref-assignment-ir-injector-strategy/tuple-access-ref-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/module-access-assignment-ir-injector-strategy/module-access-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/module-access-ref-assignment-ir-injector-strategy/module-access-ref-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/class-static-property-assignment-ir-injector-strategy/class-static-property-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/class-static-property-ref-assignment-ir-injector-strategy/class-static-property-ref-assignment-ir-injector-strategy.h"
#include "ir-injector-strategies/if-statement-ir-injector-strategy/if-statement-ir-injector-strategy.h"
#include "ir-injector-strategies/while-statement-ir-injector-strategy/while-statement-ir-injector-strategy.h"
#include "ir-injector-strategies/for-in-statement-ir-injector-strategy/for-in-statement-ir-injector-strategy.h"
#include "ir-injector-strategies/expression-statement-ir-injector-strategy/expression-statement-ir-injector-strategy.h"
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
    _variableIRInjector = std::make_shared<VariableIRInjectorStrategy>();
    _functionReturnIRInjector = std::make_shared<FunctionReturnIRInjectorStrategy>();
    _variableAssignmentIRInjectorStrategy = std::make_shared<VariableAssignmentIRInjectorStrategy>();
    _arrayAccessAssignmentIRInjectorStrategy = std::make_shared<ArrayAccessAssignmentIRInjectorStrategy>();
    _arrayAccessRefAssignmentIRInjectorStrategy = std::make_shared<ArrayAccessRefAssignmentIRInjectorStrategy>();
    _objectAccessAssignmentIRInjectorStrategy = std::make_shared<ObjectAccessAssignmentIRInjectorStrategy>();
    _objectAccessRefAssignmentIRInjectorStrategy = std::make_shared<ObjectAccessRefAssignmentIRInjectorStrategy>();
    _tupleAccessAssignmentIRInjectorStrategy = std::make_shared<TupleAccessAssignmentIRInjectorStrategy>();
    _tupleAccessRefAssignmentIRInjectorStrategy = std::make_shared<TupleAccessRefAssignmentIRInjectorStrategy>();
    _moduleAccessAssignmentIRInjectorStrategy = std::make_shared<ModuleAccessAssignmentIRInjectorStrategy>();
    _moduleAccessRefAssignmentIRInjectorStrategy = std::make_shared<ModuleAccessRefAssignmentIRInjectorStrategy>();
    _classStaticPropertyAssignmentIRInjectorStrategy = std::make_shared<ClassStaticPropertyAssignmentIRInjectorStrategy>();
    _classStaticPropertyRefAssignmentIRInjectorStrategy = std::make_shared<ClassStaticPropertyRefAssignmentIRInjectorStrategy>();
    _classPropertyAssignmentIRInjectorStrategy = std::make_shared<ClassPropertyAssignmentIRInjectorStrategy>();
    _classPropertyRefValueAssignmentIRInjectorStrategy = std::make_shared<ClassPropertyRefValueAssignmentIRInjectorStrategy>();
    _refValueAssignmentIRInjectorStrategy = std::make_shared<RefValueAssignmentIRInjectorStrategy>();
    _ifStatementIRInjectorStrategy = std::make_shared<IfStatementIRInjectorStrategy>();
    _whileStatementIRInjectorStrategy = std::make_shared<WhileStatementIRInjectorStrategy>();
    _forInStatementIRInjectorStrategy = std::make_shared<ForInStatementIRInjectorStrategy>();
    _expressionStatementIRInjectorStrategy = std::make_shared<ExpressionStatementIRInjectorStrategy>();
    _procedureDeclarationIRInjectorStrategy = std::make_shared<ProcedureDeclarationIRInjectorStrategy>();
    _functionDeclarationIRInjectorStrategy = std::make_shared<FunctionDeclarationIRInjectorStrategy>();
    _typeValueIRInjectorStrategy = std::make_shared<TypeValueIRInjectorStrategy>();
    _blockIRInjectorStrategy = std::make_shared<BlockIRInjectorStrategy>();
    _classIRInjectorStrategy = std::make_shared<ClassIRInjectorStrategy>();
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

std::pair<TypeSource, std::shared_ptr<IRInjectorStrategy>> IRInjector::insert(TypeSource typeSignature, std::shared_ptr<IRInjectorStrategy> injector) {
    return std::pair { typeSignature, injector };
}

void IRInjector::inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRNode> irNode, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irNode->isDeclaration()) {
        this->inject(irBlock, std::dynamic_pointer_cast<IRDeclarationNode>(irNode), irModule, scope);
    } else if (irNode->isStatement()) {
        this->inject(irBlock, std::dynamic_pointer_cast<IRStatementNode>(irNode), irModule, scope);
    }
}

void IRInjector::inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRDeclarationNode> irDeclaration, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irDeclaration->is(IR_VARIABLE_DECLARATION_NODE)) {
        _variableIRInjector->inject(std::dynamic_pointer_cast<IRVariableDeclarationNode>(irDeclaration), irBlock, shared_from_this(), irModule, scope);
    } else if (irDeclaration->is(IR_FUNCTION_PARAMETER_DECLARATION_NODE)) {
        _functionParameterIRInjector->inject(std::dynamic_pointer_cast<IRFunctionParameterDeclarationNode>(irDeclaration), irBlock, shared_from_this(), irModule);
    } else if (irDeclaration->is(IR_MODULE_DECLARATION_NODE)) {
        _moduleIRInjector->inject(std::dynamic_pointer_cast<IRModuleDeclarationNode>(irDeclaration), irBlock, shared_from_this(), irModule, scope);
    } else if (irDeclaration->is(IR_PROCEDURE_DECLARATION_NODE)) {
        _procedureDeclarationIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRProcedureDeclarationNode>(irDeclaration), irBlock, shared_from_this(), irModule, scope);
    } else if (irDeclaration->is(IR_FUNCTION_DECLARATION_NODE)) {
        _functionDeclarationIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRFunctionDeclarationNode>(irDeclaration), irBlock, shared_from_this(), irModule, scope);
    } else if (irDeclaration->is(IR_CLASS_DECLARATION_NODE)) {
        _classIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRClassDeclarationNode>(irDeclaration), irBlock, shared_from_this(), irModule, scope);
    }
}

void IRInjector::inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRStatementNode> irStatement, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irStatement->is(IR_FUNCTION_RETURN_EXPRESSION_NODE)) {
        _functionReturnIRInjector->inject(std::dynamic_pointer_cast<IRFunctionReturnExpressionNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE)) {
        _classPropertyAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRClassPropertyAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        _classPropertyRefValueAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRClassPropertyRefValueAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_REF_VALUE_ASSIGNMENT_STATEMENT_NODE)) {
        _refValueAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRRefValueAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_VARIABLE_ASSIGNMENT_STATEMENT_NODE)) {
        _variableAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRVariableAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _arrayAccessAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRArrayAccessAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE)) {
        _arrayAccessRefAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRArrayAccessRefAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _objectAccessAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRObjectAccessAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE)) {
        _objectAccessRefAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRObjectAccessRefAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _tupleAccessAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRTupleAccessAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE)) {
        _tupleAccessRefAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRTupleAccessRefAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE)) {
        _moduleAccessAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRModuleAccessAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE)) {
        _moduleAccessRefAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRModuleAccessRefAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_CLASS_STATIC_PROPERTY_ASSIGNMENT_STATEMENT_NODE)) {
        _classStaticPropertyAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRClassStaticPropertyAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_CLASS_STATIC_PROPERTY_REF_ASSIGNMENT_STATEMENT_NODE)) {
        _classStaticPropertyRefAssignmentIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRClassStaticPropertyRefAssignmentStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_IF_STATEMENT_NODE)) {
        _ifStatementIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRIfStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_WHILE_STATEMENT_NODE)) {
        _whileStatementIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRWhileStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_FOR_IN_STATEMENT_NODE)) {
        _forInStatementIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRForInStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else if (irStatement->is(IR_EXPRESSION_STATEMENT_NODE)) {
        _expressionStatementIRInjectorStrategy->inject(std::dynamic_pointer_cast<IRExpressionStatementNode>(irStatement), irBlock, shared_from_this(), irModule, scope);
    } else {
        throw std::invalid_argument("unable to find injector for statement " + std::to_string(irStatement->getNodeType()));
    }
}

void IRInjector::inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRBlockNode> irNode, std::shared_ptr<IRModuleNode> irModule) {
    _blockIRInjectorStrategy->inject(irNode, irBlock, shared_from_this(), irModule);
}

llvm::Value* IRInjector::inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRType> irType, std::shared_ptr<IRModuleNode> irModule) {
    return _typeValueIRInjectorStrategy->inject(irType, irBlock, shared_from_this(), irModule);
}

llvm::Value* IRInjector::inject(std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
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
    return injector->second.get()->inject(irExpression, irBlock, shared_from_this(), irOperation, irModule, scope);
}

void IRInjector::injectVoidReturnType(std::shared_ptr<IRBlockNode> irBlock) {
    irBlock->getBuilder()->get()->CreateRet(irBlock->getBuilder()->get()->getInt64(0));
}

llvm::Value* IRInjector::injectStringGlobalVariable(std::shared_ptr<IRBlockNode> irBlock, std::string id, std::string rawString, std::shared_ptr<IRModuleNode> irModule) {
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

llvm::AllocaInst* IRInjector::injectRawString(std::shared_ptr<IRBlockNode> irBlock, std::string rawString) {
    auto irString = llvm::ConstantDataArray::getString(irBlock->getBuilder()->get()->getContext(), rawString);
    auto alloca = irBlock->getBuilder()->get()->CreateAlloca(irString->getType());
    irBlock->getBuilder()->get()->CreateStore(irString, alloca);
    return alloca;
}
