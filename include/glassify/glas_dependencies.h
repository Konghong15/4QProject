#pragma once
#include "glas_decl.h"

/**
 * Whenever a reflected type requires another type to be reflected as well we can use a glas::AddDependency struct to add that type to the reflection system.
 * Example: std::vector<int> also needs int to be reflected to function correctly.
 */

namespace glas
{
	template <typename T>
	struct AddDependency {};

#ifdef _VECTOR_
	template <typename T>
	struct AddDependency<std::vector<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _ARRAY_
	template <typename T, size_t size>
	struct AddDependency<std::array<T, size>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _DEQUE_
	template <typename T>
	struct AddDependency<std::deque<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _FORWARD_LIST_
	template <typename T>
	struct AddDependency<std::forward_list<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _LIST_
	template <typename T>
	struct AddDependency<std::list<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _SET_
	template <typename T>
	struct AddDependency<std::set<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};

	template <typename T>
	struct AddDependency<std::multiset<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _UNORDERED_SET_
	template <typename T>
	struct AddDependency<std::unordered_set<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};

	template <typename T>
	struct AddDependency<std::unordered_multiset<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _MAP_
	template <typename Key, typename Value>
	struct AddDependency<std::map<Key, Value>>
	{
		inline static GlasAutoRegisterTypeOnce<Key> RegisterKey{};
		inline static GlasAutoRegisterTypeOnce<Value> RegisterValue{};
	};

	template <typename Key, typename Value>
	struct AddDependency<std::multimap<Key, Value>>
	{
		inline static GlasAutoRegisterTypeOnce<Key> RegisterKey{};
		inline static GlasAutoRegisterTypeOnce<Value> RegisterValue{};
	};
#endif

#ifdef _UNORDERED_MAP_
	template <typename Key, typename Value>
	struct AddDependency<std::unordered_map<Key, Value>>
	{
		inline static GlasAutoRegisterTypeOnce<Key> RegisterKey{};
		inline static GlasAutoRegisterTypeOnce<Value> RegisterValue{};
	};

	template <typename Key, typename Value>
	struct AddDependency<std::unordered_multimap<Key, Value>>
	{
		inline static GlasAutoRegisterTypeOnce<Key> RegisterKey{};
		inline static GlasAutoRegisterTypeOnce<Value> RegisterValue{};
	};
#endif

#ifdef _MEMORY_
	template <typename T>
	struct AddDependency<std::unique_ptr<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _OPTIONAL_
	template <typename T>
	struct AddDependency<std::optional<T>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterValue{};
	};
#endif

#ifdef _UTILITY_
	template <typename T1, typename T2>
	struct AddDependency<std::pair<T1, T2>>
	{
		inline static GlasAutoRegisterTypeOnce<T1> RegisterT1{};
		inline static GlasAutoRegisterTypeOnce<T2> RegisterT2{};
	};

	template <typename T, typename... Ts>
	struct AddDependency<std::tuple<T, Ts...>> : private AddDependency<std::tuple<Ts...>>
	{
		inline static GlasAutoRegisterTypeOnce<T> RegisterType{};
	};
#endif
}