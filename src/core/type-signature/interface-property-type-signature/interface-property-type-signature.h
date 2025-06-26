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
    TypeSignature* _type;
public:
    InterfacePropertyTypeSignature(std::string name, TypeSignature* type);
    std::string getName();
    TypeSignature* getTypeSignature();
    void setType(TypeSignature* typeSignature);
    std::string toString() override;
    TypeSource getTypeSource() override;
    bool isEqualTo(TypeSignature *otherType) override;
    bool isEquivalentTo(TypeSignature* otherType) override;
    void print() override;
};

#endif //JETLANG_INTERFACE_PROPERTY_TYPE_SIGNATURE_H
