#include <memory>

namespace OGRID
{
	template <typename T>
	using SCOPE = std::unique_ptr<T>;
	template <typename T, typename... Args>
	constexpr SCOPE<T> NEWSCOPE(Args &&...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using REF = std::shared_ptr<T>;
	template <typename T, typename... Args>
	constexpr REF<T> NEWREF(Args &&...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#ifdef OGRID_COMPILER_MSVC
#define CLI_ASSERT(x, ...)                                   \
	{                                                        \
		if (!(x))                                            \
		{                                                    \
			CLI_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__debugbreak();                                  \
		}                                                    \
	}
#elif OGRID_COMPILER_CLANG || OGRID_COMPILER_GNU
#define CLI_ASSERT(x, ...)                                   \
	{                                                        \
		if (!(x))                                            \
		{                                                    \
			CLI_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__builtin_trap();                                \
		}                                                    \
	}
#endif

#ifdef OGRID_ENABLE_DEBUG_LOG
#define DEBUG_ASSERT(x, ...)                                   \
	{                                                          \
		if (!(x))                                              \
		{                                                      \
			DEBUG_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); \
			__debugbreak();                                    \
		}                                                      \
	}
#else
#define DEBUG_ASSERT(x, ...)
#endif