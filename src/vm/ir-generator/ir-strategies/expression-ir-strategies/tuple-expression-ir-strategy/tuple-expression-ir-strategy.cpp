//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"

IRTupleExpressionNode* TupleExpressionIRStrategy::generate(ASTTupleExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule) {
    auto tupleValueTypes = std::vector<llvm::Type*>();
    auto tupleValues = std::vector<IRExpressionNode*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        auto irNode = irGenerator->generateFor(tupleItem->getItem(), scope, irModule);
        tupleValueTypes.push_back(irNode->getType());
        tupleValues.push_back(irNode);
    }

    return new IRTupleExpressionNode(
            node,
            llvm::ConstantStruct::get(llvm::StructType::get(**context, tupleValueTypes)),
            irGenerator->generateTypeFor(node->getTypeSignature()),
            tupleValues
    );
}