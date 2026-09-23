//
// Created by Johny Georges on 2024-12-31.
//

#ifndef JETLANG_IR_NEW_CLASS_INSTANCE_TYPE_H
#define JETLANG_IR_NEW_CLASS_INSTANCE_TYPE_H

#include "ir-type.h"
#include "ir-class-type.h"
#include "ir-struct-ref-type.h"

class IRNewClassInstanceType : public IRType {
private:
    std::shared_ptr<IRStructRefType> _irClassInstancePropertiesType;
    std::shared_ptr<IRClassType> _irClassType;
    std::string _constructorId;
public:
    IRNewClassInstanceType(std::shared_ptr<IRClassType> irClassType, std::string constructorId, std::shared_ptr<IRStructRefType> irClassInstancePropertiesType);
    std::shared_ptr<IRStructRefType> getIRClassPropertiesType();
    std::shared_ptr<IRClassType> getIRClassType();
    std::shared_ptr<IRFunctionType> getIRConstructorType();
    std::string getIRMethodName(std::string methodName);
    std::string getIRPropertyName(std::string propertyName);
    uint64_t getIndexForProperty(std::string propertyName);
    std::shared_ptr<IRType> getIRTypeForProperty(std::string propertyName);
    std::optional<std::shared_ptr<IRFunctionType>> getIRTypeForMethod(std::string methodName);
    uint64_t getSizeInBytes() override;
    llvm::StructType* getType() override;
    bool containsTypeThatRequiresFreeing() override;
    bool isNewClassInstanceType() override;
    llvm::Align getAlignment() override;
    std::shared_ptr<IRType> clone() override;
    void print() override;
};

#endif //JETLANG_IR_NEW_CLASS_INSTANCE_TYPE_H
