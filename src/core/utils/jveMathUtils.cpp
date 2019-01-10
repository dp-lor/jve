

#include "jveMathUtils.h"


int
jveMathUtils::getGreatestCommonDivisor(
    const int  a,
    const int  b,
    const bool euclid
)
{
    // euclid
    if (euclid) {
        int _a = a;
        int _b = b;
        int _s;

        if (_a < _b) {
            _s = _a;
            _a = _b;
            _b = _s;
        }
        while (0 != _b) {
            _s = _b;
            _b = _a % _b;
            _a = _s;
        }

        return _a;
    // recursive
    } else {
        return (0 == b) ? a : getGreatestCommonDivisor(b, a % b);
    }
}


