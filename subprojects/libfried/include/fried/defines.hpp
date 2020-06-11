#pragma once

#define NON_COPYABLE(cls) \
    cls(const cls&) = delete; \
    cls& operator=(const cls&) = delete

#define NON_MOVEABLE(cls) \
    cls(cls&&) = delete; \
    cls& operator=(cls&&) = delete

#define ALWAYS_INLINE_LAMBDA __attribute__((always_inline))
#define ALWAYS_INLINE inline __attribute__((always_inline))

#define CONCATENATE_IMPL(s1, s2) s1##s2
#define CONCATENATE(s1, s2) CONCATENATE_IMPL(s1, s2)

#ifdef __COUNTER__
#define ANONYMOUS_VARIABLE(pref) CONCATENATE(pref, __COUNTER__)
#else
#define ANONYMOUS_VARIABLE(pref) CONCATENATE(pref, __LINE__)
#endif

#define FRD_PREDICT(expr, value, _probability) __builtin_expect_with_probability(expr, value, ({ \
                                                    constexpr double probability = _probability; \
                                                    static_assert(0.0 <= probability);           \
                                                    static_assert(probability <= 1.0);           \
                                                    probability;                                 \
                                               }))

#define FRD_PREDICT_TRUE(expr, probability)  FRD_PREDICT(!!(expr), 1, probability)
#define FRD_PREDICT_FALSE(expr, probability) FRD_PREDICT(!!(expr), 0, probability)

#define FRD_LIKELY(expr)   FRD_PREDICT_TRUE(expr, 1.0)
#define FRD_UNLIKELY(expr) FRD_PREDICT_FALSE(expr, 1.0)

#define B_ASSERT(expr) \
    ({ \
        bool _bool = (expr); \
        if (FRD_UNLIKELY(!_bool)) { \
            std::fprintf(stderr, "Bool assertion failed | %s:%d\n", __PRETTY_FUNCTION__, __LINE__); \
            exit(-1); \
        } \
    })
