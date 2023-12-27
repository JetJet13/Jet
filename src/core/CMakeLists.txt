add_library(jet-core
        ./lexeme/lexeme.h
        ./lexeme/lexeme.cpp

        ./symbol/symbol.h
        ./symbol/symbol.cpp

        ./symbol/symbol-types/int-symbol.h
        ./symbol/symbol-types/int-symbol.cpp

)

target_link_libraries(jet-core
        PRIVATE jet-shared
)