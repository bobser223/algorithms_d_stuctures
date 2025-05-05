//
// Created by Volodymyr Avvakumov on 04.05.2025.
//

#ifndef ALG_D_SRUCT_COOL_BOOL_H
#define ALG_D_SRUCT_COOL_BOOL_H

#endif //ALG_D_SRUCT_COOL_BOOL_H

#define maybe \
    ([]() -> bool {                        \
        static std::random_device rd;      \
        static std::mt19937 gen(rd());     \
        static std::bernoulli_distribution flip(0.5); \
        return flip(gen);                  \
    }())