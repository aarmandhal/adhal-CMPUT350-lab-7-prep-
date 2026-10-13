#ifndef PACK_H
#define PACK_H

// Helper namespace for pack utilities
namespace pack_detail {

// constexpr int packSize = sizeof...(Args);
template <typename... Args>
constexpr int packSize = sizeof...(Args);

// --- _packIndexToType ---
template <int QueryIndex, typename... Args>
struct _packIndexToType {
    static_assert(QueryIndex >= 0 && QueryIndex < packSize<Args...>, "Index out of bounds");
};

// Base case: QueryIndex is 0, return the first type
template <typename T, typename... Ts>
struct _packIndexToType<0, T, Ts...> {
    using type = T;
};

// Recursive case: decrement the index and recurse on the rest of the pack
template <int QueryIndex, typename T, typename... Ts>
struct _packIndexToType<QueryIndex, T, Ts...> {
    using type = typename _packIndexToType<QueryIndex - 1, Ts...>::type;
};

// Alias for _packIndexToType
template <int QueryIndex, typename... Args>
using packIndexToType = typename _packIndexToType<QueryIndex, Args...>::type;

// --- _packTypeToIndex ---
template <int Accumulated, typename QueryType, typename... Args>
constexpr int _packTypeToIndex = -1;

// Base case: QueryType is found, return the accumulated index
template <int Accumulated, typename QueryType, typename... Ts>
constexpr int _packTypeToIndex<Accumulated, QueryType, QueryType, Ts...> = Accumulated;

// Recursive case: increment the accumulated index and recurse on the rest of the pack
template <int Accumulated, typename QueryType, typename T, typename... Ts>
constexpr int _packTypeToIndex<Accumulated, QueryType, T, Ts...> =
    _packTypeToIndex<Accumulated + 1, QueryType, Ts...>;

// Alias for _packTypeToIndex
template <typename QueryType, typename... Args>
constexpr int packTypeToIndex = _packTypeToIndex<0, QueryType, Args...>;

}  // namespace pack_detail

// Public interface
template <typename... Ts>

// Struct that contains the pack utilities
struct Pack {
    // Size of the pack
    static constexpr int size = pack_detail::packSize<Ts...>;

    // Get the type at a specific index
    template <int QueryIndex>
    using type = pack_detail::packIndexToType<QueryIndex, Ts...>;

    // Get the index of a specific type
    template <typename QueryType>
    constexpr static int index = pack_detail::packTypeToIndex<QueryType, Ts...>;
};

#endif  // PACK_H