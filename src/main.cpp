#include <type_traits>

#include "pack.h"

int main() {
    // packSize
    static_assert(Pack<int, bool, double>::size == 3);
    static_assert(Pack<>::size == 0);

    // type<QueryIndex>
    static_assert(std::is_same_v<Pack<int, bool, double>::type<0>, int>);
    static_assert(std::is_same_v<Pack<int, bool, double>::type<1>, bool>);
    static_assert(std::is_same_v<Pack<int, bool, double>::type<2>, double>);

    // index<QueryType>
    static_assert(Pack<int, bool, double>::index<int> == 0);
    static_assert(Pack<int, bool, double>::index<double> == 2);
    static_assert(Pack<int, bool, double>::index<char> == -1);  // not present

    return 0;
}
