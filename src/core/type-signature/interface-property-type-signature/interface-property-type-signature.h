//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_INTERFACE_PROPERTY_TYPE_SIGNATURE_H
#define JETLANG_INTERFACE_PROPERTY_TYPE_SIGNATURE_H

#include <vector>
#include "../type-signature.h"

class InterfacePropertyTypeSignature : public TypeSignature {
private:
    std::string _name;
    std::shared_ptr<TypeSignature> _type;
public:
    InterfacePropertyTypeSignature(std::string name, std::shared_ptr<TypeSignature> type);
    std::string getName();
    std::shared_ptr<TypeSignature> getTypeSignature();
    void setType(std::shared_ptr<TypeSignature> typeSignature);
    std::string toDetailString() override;
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(std::shared_ptr<TypeSignature> otherType) override;
    bool isEquivalentTo(std::shared_ptr<TypeSignature> otherType) override;
    void print() override;
};

#endif //JETLANG_INTERFACE_PROPERTY_TYPE_SIGNATURE_H
