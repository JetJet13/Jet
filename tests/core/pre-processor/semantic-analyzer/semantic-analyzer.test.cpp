//
// Created by Johny Georges on 2024-05-13.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/token/token-table.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/shared/utils/logger/logger.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/dependency-graph/dependency-graph.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/type-signature-lookup-table/type-signature-lookup-table.h"
#include "../../../../src/core/pre-processor/semantic-analyzer/semantic-analyzer.h"
#include "resources/type-signature-factory.h"
#include "../../../../src/core/type-signature/array-type-signature/array-type-signature.h"
#include "../../../../src/core/type-signature/struct-type-signature/struct-type-signature.h"
#include "../../../../src/core/type-signature/enum-type-signature/enum-access-type-signature/enum-access-type-signature.h"
#include "../../../../src/core/type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../../../src/core/type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../../src/core/type-signature/invocable-type-signature/lambda-type-signature/lambda-expression-type-signature/lambda-expression-type-signature.h"
#include "../../../../src/core/type-signature/invocable-type-signature/function-type-signature/function-invocation-type-signature/function-invocation-type-signature.h"
#include "../../../../src/core/type-signature/invocable-type-signature/lambda-type-signature/function-lambda-type-signature/function-lambda-type-signature.h"
#include "../../../../src/core/type-signature/invocable-type-signature/lambda-type-signature/procedure-lambda-type-signature/procedure-lambda-type-signature.h"

auto colorEnumTypeSignature = new EnumTypeSignature(
        TypeSignatureFactory::stringLiteral,
        TypeSignatureMap<LiteralTypeSignature>({
               std::pair("Red", TypeSignatureFactory::stringLiteral),
               std::pair("Blue", TypeSignatureFactory::stringLiteral),
               std::pair("Green", TypeSignatureFactory::stringLiteral),
        }));

auto otherClassTypeSignature = new ClassTypeSignature();
auto myClassTypeSignature = new ClassTypeSignature();

std::unordered_map<int, TypeSignature*> generateExpectedTypeSignatures() {

    otherClassTypeSignature
    ->addProperty("OtherClass_property_myIntOne", new ClassPropertyTypeSignature(TypeSignatureFactory::publicAccess, new ClassInstanceTypeSignature(myClassTypeSignature), false, false));

    myClassTypeSignature
    ->addProperty("MyClass_property_myIntOne", new ClassPropertyTypeSignature(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, false))
    ->addProperty("MyClass_property_myIntTwo", new ClassPropertyTypeSignature(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, false))
    ->addProperty("MyClass_property_myIntThree", new ClassPropertyTypeSignature(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, false))
    ->addProperty("MyClass_property_myIntOneConst", new ClassPropertyTypeSignature(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, true))
    ->addProperty("MyClass_property_myIntTwoConst", new ClassPropertyTypeSignature(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, true))
    ->addProperty("MyClass_property_myIntThreeConst", new ClassPropertyTypeSignature(TypeSignatureFactory::publicAccess, TypeSignatureFactory::intLiteral, false, true))
    ->addProperty("MyClass_property_fooOneStatic", new ClassPropertyTypeSignature(TypeSignatureFactory::protectedAccess, TypeSignatureFactory::intLiteral, true, false))
    ->addProperty("MyClass_property_fooTwoStatic", new ClassPropertyTypeSignature(TypeSignatureFactory::protectedAccess, TypeSignatureFactory::intLiteral, true, false))
    ->addProperty("MyClass_property_fooThreeStatic", new ClassPropertyTypeSignature(TypeSignatureFactory::protectedAccess, TypeSignatureFactory::intLiteral, true, false))
    ->addProperty("MyClass_property_mickOneStatic", new ClassPropertyTypeSignature(TypeSignatureFactory::privateAccess, TypeSignatureFactory::boolLiteral, true, true))
    ->addProperty("MyClass_property_mickTwoStatic", new ClassPropertyTypeSignature(TypeSignatureFactory::privateAccess, TypeSignatureFactory::boolLiteral, true, true))
    ->addProperty("MyClass_property_mickThreeStatic", new ClassPropertyTypeSignature(TypeSignatureFactory::privateAccess, TypeSignatureFactory::boolLiteral, true, true))
    ->addProperty("MyClass_property_initMyClass", new ClassPropertyTypeSignature(TypeSignatureFactory::privateAccess, new ClassInstanceTypeSignature(myClassTypeSignature), false, false))
    ->addProperty("MyClass_property_myClassProp", new ClassPropertyTypeSignature(TypeSignatureFactory::privateAccess, new ClassInstanceTypeSignature(myClassTypeSignature), false, false))
    ->addProperty("MyClass_property_otherClass", new ClassPropertyTypeSignature(TypeSignatureFactory::privateAccess, new ClassInstanceTypeSignature(otherClassTypeSignature), false, false))
    ->addConstructor(
        "MyClass_constructor_0",
        new ClassConstructorTypeSignature(
            new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("other", new ClassInstanceTypeSignature(myClassTypeSignature))
    })))
    ->addConstructor(
        "MyClass_constructor_1",
        new ClassConstructorTypeSignature(
            new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("foo", TypeSignatureFactory::intLiteral)
    })))
    ->addMethod(
        "MyClass_method_create",
        new ClassMethodTypeSignature(
            TypeSignatureFactory::publicAccess,
            new ParameterListTypeSignature({
               new ParameterListItemTypeSignature("foo", TypeSignatureFactory::intLiteral)
           }),
           true,
            new ClassInstanceTypeSignature(myClassTypeSignature)
       )
   )
    ->addMethod(
        "MyClass_method_doSomething",
        new ClassMethodTypeSignature(
            TypeSignatureFactory::protectedAccess,
            new ParameterListTypeSignature({
               new ParameterListItemTypeSignature("other", new ClassInstanceTypeSignature(myClassTypeSignature))
            }),
            true,
            new ClassInstanceTypeSignature(myClassTypeSignature)
        )
    )
    ->addMethod(
        "MyClass_method_doSomethingElse",
        new ClassMethodTypeSignature(
            TypeSignatureFactory::privateAccess,
            new ParameterListTypeSignature(),
            true,
            new ClassInstanceTypeSignature(myClassTypeSignature)
        )
    )
    ->addMethod(
        "MyClass_method_isValid",
        new ClassMethodTypeSignature(
            TypeSignatureFactory::publicAccess,
            new ParameterListTypeSignature(),
            false,
            TypeSignatureFactory::boolLiteral
        )
    )
    ->addMethod(
        "MyClass_method_setBar",
        new ClassMethodTypeSignature(
            TypeSignatureFactory::protectedAccess,
            new ParameterListTypeSignature({
                new ParameterListItemTypeSignature("bar", TypeSignatureFactory::boolLiteral)
            }),
            false,
            new ClassInstanceTypeSignature(myClassTypeSignature)
        )
    )
    ->addMethod(
        "MyClass_method_hello",
        new ClassMethodTypeSignature(
            TypeSignatureFactory::privateAccess,
            new ParameterListTypeSignature(),
            false,
            TypeSignatureFactory::stringLiteral
        )
    )
    ->addMethod(
        "MyClass_method_helloBar",
        new ClassMethodTypeSignature(
            TypeSignatureFactory::privateAccess,
            new ParameterListTypeSignature(),
            false
        )
    );


    return {
            {1, TypeSignatureFactory::intLiteral},
            {2, TypeSignatureFactory::floatLiteral},
            {3, TypeSignatureFactory::stringLiteral},
            {4, TypeSignatureFactory::charLiteral},
            {5, TypeSignatureFactory::boolLiteral},
            {6, TypeSignatureFactory::boolLiteral},
            {7, TypeSignatureFactory::intLiteral},
            {8, TypeSignatureFactory::intLiteral},
            {9, TypeSignatureFactory::intLiteral},
            {10, TypeSignatureFactory::intLiteral},
            {11, TypeSignatureFactory::floatLiteral},
            {12, TypeSignatureFactory::intLiteral},
            {13, TypeSignatureFactory::stringLiteral},
            {14, TypeSignatureFactory::intLiteral},
            {15, TypeSignatureFactory::floatLiteral},
            {16, TypeSignatureFactory::intLiteral},
            {17, TypeSignatureFactory::intLiteral},
            {18, TypeSignatureFactory::intLiteral},
            {19, TypeSignatureFactory::floatLiteral},
            {20, TypeSignatureFactory::floatLiteral},
            {21, TypeSignatureFactory::intLiteral},
            {22, TypeSignatureFactory::intLiteral},
            {23, TypeSignatureFactory::intLiteral},
            {24, TypeSignatureFactory::intLiteral},
            {25, TypeSignatureFactory::floatLiteral},
            {26, TypeSignatureFactory::floatLiteral},
            {27, TypeSignatureFactory::intLiteral},
            {28, TypeSignatureFactory::boolLiteral},
            {29, TypeSignatureFactory::boolLiteral},
            {30, TypeSignatureFactory::boolLiteral},
            {31, TypeSignatureFactory::boolLiteral},
            {32, TypeSignatureFactory::boolLiteral},
            {33, TypeSignatureFactory::boolLiteral},
            {34, TypeSignatureFactory::boolLiteral},
            {35, TypeSignatureFactory::boolLiteral},
            {36, TypeSignatureFactory::boolLiteral},
            {37, TypeSignatureFactory::boolLiteral},
            {38, TypeSignatureFactory::boolLiteral},
            {39, TypeSignatureFactory::boolLiteral},
            {40, TypeSignatureFactory::boolLiteral},
            {41, TypeSignatureFactory::boolLiteral},
            {42, TypeSignatureFactory::boolLiteral},
            {43, TypeSignatureFactory::boolLiteral},
            {44, TypeSignatureFactory::boolLiteral},
            {45, TypeSignatureFactory::boolLiteral},
            {46, TypeSignatureFactory::boolLiteral},
            {47, TypeSignatureFactory::boolLiteral},
            {48, TypeSignatureFactory::boolLiteral},
            {49, TypeSignatureFactory::intLiteral},
            {50, TypeSignatureFactory::intLiteral},
            {51, TypeSignatureFactory::intLiteral},
            {52, TypeSignatureFactory::intLiteral},
            {53, TypeSignatureFactory::intLiteral},
            {54, TypeSignatureFactory::boolLiteral},
            {55, TypeSignatureFactory::boolLiteral},
            {56, TypeSignatureFactory::boolLiteral},
            {57, TypeSignatureFactory::boolLiteral},
            {58, TypeSignatureFactory::intLiteral},
            {59, TypeSignatureFactory::boolLiteral},
            {60, TypeSignatureFactory::boolLiteral},
            {61, new ArrayTypeSignature(TypeSignatureFactory::intLiteral)},
            {62, TypeSignatureFactory::intLiteral},
            {63, TypeSignatureFactory::intLiteral},
            {64, new ArrayTypeSignature(new ArrayTypeSignature(TypeSignatureFactory::intLiteral))},
            {65, new ArrayTypeSignature(new ArrayTypeSignature(TypeSignatureFactory::intLiteral))},
            {66, new ArrayTypeSignature(TypeSignatureFactory::intLiteral)},
            {67, TypeSignatureFactory::intLiteral},
            {68, TypeSignatureFactory::intLiteral},
            {69, new StructTypeSignature(
                    TypeSignatureMap<TypeSignature>({
                        std::pair("i", TypeSignatureFactory::intLiteral),
                        std::pair("f", TypeSignatureFactory::floatLiteral),
                        std::pair("world", TypeSignatureFactory::boolLiteral),
                        std::pair("character", TypeSignatureFactory::charLiteral),
                        std::pair("str", TypeSignatureFactory::stringLiteral),
                        std::pair("identifier", TypeSignatureFactory::boolLiteral),
                        std::pair("array", new ArrayTypeSignature(TypeSignatureFactory::intLiteral)),
                        std::pair("arrAccess", TypeSignatureFactory::intLiteral),
                        std::pair("obj", new StructTypeSignature(
                            TypeSignatureMap<TypeSignature>({
                                std::pair("test", TypeSignatureFactory::intLiteral),
                                std::pair("nest", new StructTypeSignature(
                                    TypeSignatureMap<TypeSignature>({
                                        std::pair("value", TypeSignatureFactory::boolLiteral),
                                    })
                                )),
                            })
                        )),
                        std::pair("binary", TypeSignatureFactory::intLiteral),
                        std::pair("logical", TypeSignatureFactory::boolLiteral),
                        std::pair("unary", TypeSignatureFactory::boolLiteral),
                    })
            )},
            {70, TypeSignatureFactory::boolLiteral},
            {71, TypeSignatureFactory::intLiteral},
            {72, TypeSignatureFactory::boolLiteral},
            {73, new ArrayTypeSignature(
                    new StructTypeSignature(
                        TypeSignatureMap({
                             std::pair("hello", TypeSignatureFactory::stringLiteral),
                             std::pair("test", TypeSignatureFactory::intLiteral),
                         })
                    )
            )},
            {74, TypeSignatureFactory::stringLiteral},
            {75, new StructTypeSignature(
                    TypeSignatureMap({
                         std::pair("array",
                               new ArrayTypeSignature(
                                   new StructTypeSignature(
                                       TypeSignatureMap({
                                            std::pair("hello", TypeSignatureFactory::stringLiteral),
                                            std::pair("test", TypeSignatureFactory::intLiteral),
                                       })
                                   )
                               )),
                         std::pair("arrNested", new ArrayTypeSignature(
                             new ArrayTypeSignature(
                                 new StructTypeSignature(
                                     TypeSignatureMap({
                                          std::pair("hello", TypeSignatureFactory::stringLiteral),
                                          std::pair("test", TypeSignatureFactory::intLiteral),
                                     })
                                 )
                             )
                         )),
                   })
            )},
            {76, TypeSignatureFactory::stringLiteral},
            {77, TypeSignatureFactory::stringLiteral},
            {78, new FunctionTypeSignature(
                    new ParameterListTypeSignature({
                       TypeSignatureFactory::createIntParameter("x"),
                       TypeSignatureFactory::createIntParameter("y")
                    }),
                    TypeSignatureFactory::intLiteral
            )},
            {79, new FunctionTypeSignature(
                    new ParameterListTypeSignature(),
                    TypeSignatureFactory::intLiteral
            )},
            {80, new ProcedureTypeSignature(
                    new ParameterListTypeSignature({
                        TypeSignatureFactory::createIntParameter("num")
                    })
            )},
            {81, new ProcedureTypeSignature(
                    new ParameterListTypeSignature()
            )},
            {82, new ProcedureTypeSignature(
                    new ParameterListTypeSignature()
            )},
            {83, new EnumAccessTypeSignature(
                    colorEnumTypeSignature,
                    "Red"
            )},
            {84, colorEnumTypeSignature },
            {85, new EnumTypeSignature(
                    TypeSignatureFactory::charLiteral,
                    TypeSignatureMap<LiteralTypeSignature>({
                       std::pair("Red", TypeSignatureFactory::charLiteral),
                       std::pair("Blue", TypeSignatureFactory::charLiteral),
                       std::pair("Green", TypeSignatureFactory::charLiteral),
                    }))
            },
            {86, new EnumTypeSignature(
                    TypeSignatureFactory::intLiteral,
                    TypeSignatureMap<LiteralTypeSignature>({
                       std::pair("Zero", TypeSignatureFactory::intLiteral),
                       std::pair("One", TypeSignatureFactory::intLiteral),
                       std::pair("Two", TypeSignatureFactory::intLiteral),
                    }))
            },
            {87, TypeSignatureFactory::boolLiteral},
            {88, TypeSignatureFactory::boolLiteral},
            {89, new TupleTypeSignature({
                    TypeSignatureFactory::stringLiteral,
                    TypeSignatureFactory::intLiteral,
                    TypeSignatureFactory::intLiteral
            })},
            {90, new FunctionTypeSignature(
                    new ParameterListTypeSignature(),
                    TypeSignatureFactory::stringLiteral
            )},
            {91, new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature({
                        new ParameterListItemTypeSignature("x", colorEnumTypeSignature)
                    }),
                    colorEnumTypeSignature
            )},
            {92, new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature("x", TypeSignatureFactory::intLiteral),
                       new ParameterListItemTypeSignature("y", TypeSignatureFactory::intLiteral),
                    }),
                    TypeSignatureFactory::boolLiteral
            )},
            {93, new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature({
                        new ParameterListItemTypeSignature("x", TypeSignatureFactory::intLiteral),
                    }),
                    TypeSignatureFactory::intLiteral
            )},
            {94, new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature({
                        new ParameterListItemTypeSignature("x", TypeSignatureFactory::intLiteral),
                    }),
                    new LambdaExpressionTypeSignature(
                            new ParameterListTypeSignature({
                                new ParameterListItemTypeSignature("y", TypeSignatureFactory::intLiteral),
                            }),
                            new LambdaExpressionTypeSignature(
                                new ParameterListTypeSignature({
                                    new ParameterListItemTypeSignature("z", TypeSignatureFactory::intLiteral),
                                }),
                                TypeSignatureFactory::intLiteral
                            ))
            )},
            {95, new FunctionInvocationTypeSignature(
                    new FunctionTypeSignature(
                        new ParameterListTypeSignature(),
                        TypeSignatureFactory::boolLiteral
                    )
            )},
            {96, new FunctionTypeSignature(
                    new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature(
                           "x",
                           TypeSignatureFactory::intLiteral
                       ),
                       new ParameterListItemTypeSignature(
                           "lambda",
                           new FunctionLambdaTypeSignature(
                               { TypeSignatureFactory::intLiteral },
                               TypeSignatureFactory::boolLiteral)
                       ),
                    }),
                    TypeSignatureFactory::boolLiteral
            )},
            {97, new FunctionTypeSignature(
                    new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature(
                           "lambda",
                           new FunctionLambdaTypeSignature(
                               {
                                   TypeSignatureFactory::intLiteral,
                                   TypeSignatureFactory::intLiteral
                               },
                               new FunctionLambdaTypeSignature(
                                   {
                                       TypeSignatureFactory::intLiteral
                                   },
                                   TypeSignatureFactory::boolLiteral
                               )
                           )
                       ),
                    }),
                    TypeSignatureFactory::boolLiteral
            )},
            {98, new FunctionTypeSignature(
                    new ParameterListTypeSignature(),
                    new FunctionLambdaTypeSignature(
                        {},
                        TypeSignatureFactory::intLiteral
                    )
            )},
            {99, new FunctionTypeSignature(
                    new ParameterListTypeSignature(),
                    new FunctionLambdaTypeSignature(
                        { TypeSignatureFactory::intLiteral },
                        TypeSignatureFactory::intLiteral
                    )
            )},
            {100, new FunctionTypeSignature(
                    new ParameterListTypeSignature(),
                    TypeSignatureFactory::boolLiteral
            )},
            {101, new FunctionTypeSignature(
                    new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature(
                           "x",
                           new FunctionLambdaTypeSignature(
                               { TypeSignatureFactory::intLiteral },
                               TypeSignatureFactory::boolLiteral
                           )
                       )
                    }),
                    TypeSignatureFactory::boolLiteral
            )},
            {102, new FunctionTypeSignature(
                    new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature(
                           "x",
                           new ProcedureLambdaTypeSignature(
                               {}
                           )
                       ),
                       new ParameterListItemTypeSignature(
                           "y",
                           new ProcedureLambdaTypeSignature(
                               {
                                   colorEnumTypeSignature
                               }
                           )
                       )
                   }),
                    TypeSignatureFactory::boolLiteral
            )},
            {103, new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature(),
                    TypeSignatureFactory::intLiteral
            )},
            {104, new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature({
                       new ParameterListItemTypeSignature("x", TypeSignatureFactory::intLiteral)
                    })
            )},
            {105, new LambdaExpressionTypeSignature(
                    new ParameterListTypeSignature()
            )},
            {106, TypeSignatureFactory::intLiteral},
            {107, TypeSignatureFactory::floatLiteral},
            {108, TypeSignatureFactory::charLiteral},
            {109, TypeSignatureFactory::stringLiteral},
            {110, TypeSignatureFactory::boolLiteral},
            {111, new ArrayTypeSignature(TypeSignatureFactory::intLiteral)},
            {112, new FunctionLambdaTypeSignature(
                    { TypeSignatureFactory::intLiteral },
                    TypeSignatureFactory::boolLiteral
            )},
            {113, new ProcedureLambdaTypeSignature(
                    { TypeSignatureFactory::intLiteral }
            )},
            {114, new TupleTypeSignature({
                     TypeSignatureFactory::intLiteral,
                     TypeSignatureFactory::intLiteral
            })},
            {115, colorEnumTypeSignature},
            {116, new ClassInstanceTypeSignature(myClassTypeSignature)},
            {117, otherClassTypeSignature},
            {118, myClassTypeSignature}


    };
}

TEST_CASE( "should print the expected type signatures" ) {
    std::string filePath = "./semantic-analyzer-test-file.jet";
    auto tokenTable = new TokenTable();
    auto reservedKeywords = new ReservedKeywords();
    auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
    auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
    auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
    auto dependencyGraph = new DependencyGraph();
    auto typeSignatureLookupTable = new TypeSignatureLookupTable();
    auto semanticAnalyzer = SemanticAnalyzer(dependencyGraph);
    auto typeCheckerResult = semanticAnalyzer.analyze(fileNodeResult, typeSignatureLookupTable);
    auto expectedTypeSignatures = generateExpectedTypeSignatures();
    Logger::log("===== TEST LOGS =====");
    typeSignatureLookupTable->dump();
    for (int i = 0; i < 118; i++) {
        auto declaration = fileNodeResult->getBody()->at(i);
        auto typeSignature = typeSignatureLookupTable->find(declaration->getId());
        Logger::log("=====", i + 1, declaration->toString(), "=====");
        Logger::log("ID -", declaration->getId());
        typeSignature->print();
        Logger::log("RESULT =", typeSignature->isEqualTo(expectedTypeSignatures[i + 1]));
        REQUIRE(typeSignature->isEqualTo(expectedTypeSignatures[i + 1]));
        Logger::log("====================================");
    }
    typeCheckerResult.print();
}