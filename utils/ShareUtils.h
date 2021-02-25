#ifndef __EXTERNAL_SHAREUTILS_H__
#define __EXTERNAL_SHAREUTILS_H__

#include <memory>

namespace ShareUtils {
    template<typename T>
    std::shared_ptr<T> make_shared_array(size_t size) {
        return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
    }

#if __cplusplus <= 201103L

    template<typename T, typename... Args>
    inline typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    make_unique(Args &&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template<typename T>
    typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, std::unique_ptr<T>>::type
    make_unique(size_t size) {
        using remove_extent_t = typename std::remove_extent<T>::type;
        return std::unique_ptr<T>(new remove_extent_t[size]());
    }

    // Disable std::make_unique for arrays of known bound
    template<typename T, typename... Args>
    inline typename std::enable_if<std::extent<T>::value != 0, void>::type
    make_unique(Args &&...) = delete;

#else
    using std::make_unique;
#endif
}


#endif //__EXTERNAL_SHAREUTILS_H__
