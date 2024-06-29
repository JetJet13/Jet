//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"

llvm::Value* ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(ASTArrayAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    auto sourceValue = (llvm::GetElementPtrInst*)irGenerator->generateFor(node->getSource(), scope);
    auto indexValue = (llvm::ConstantInt*)irGenerator->generateFor(node->getIndex()->getIndex(), scope);
    sourceValue->print(llvm::outs());
    indexValue->print(llvm::outs());
    auto loaded = new llvm::LoadInst(sourceValue->getAccessType(), sourceValue, sourceValue->getName(), false, sourceValue->getInsertionPointAfterDef());
//    return llvm::GetElementPtrInst::Create(sourceValue->getSourceElementType()->getArrayElementType(), loaded, { indexValue });
    return llvm::ExtractValueInst::Create(loaded, indexValue->getValue().getActiveBits());
}