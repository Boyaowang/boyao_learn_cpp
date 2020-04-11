namespace Metaprogramming {

template <unsigned A, unsigned B>
struct EqualityCheck {
    enum PerformCheck {
        CheckResult = (A == B)
    };
};

struct EnableIfDummy { };

template <bool> struct EnableIfHelper;
template <> struct EnableIfHelper<true> {
    typedef EnableIfDummy type;
};

template <> struct EnableIfHelper<false> {
    typedef void * type;
};

template <unsigned A, unsigned B>
struct EnableIfEqual : public EnableIfHelper<EqualityCheck<A, B>::CheckResult> { };

}
