#ifndef _DSU_H_
#define _DSU_H_

#include <vector>
#include <stdexcept>
#include <type_traits>

template <typename T>
class DSU {
private:
    size_t cmptCount_;
    std::vector<T> rank_;
    std::vector<T> parent_;
    std::vector<T> componentSize_;

public:
    DSU();
    DSU(const std::vector<T>& v);
    DSU(const std::vector<T>&& v);
 
    void addElement();
    void construct(const std::vector<T>& v);
    void construct(const std::vector<T>&& v);
 
    T getParent(const T& node);
    T getParent(const T&& node);
 
    bool unite(T& a, T& b);
    bool unite(T&& a, T& b);
    bool unite(T& a, T&& b);
    bool unite(T&& a, T&& b);
 
    inline bool isConnected(const T& a, const T& b);
    inline bool isConnected(const T&& a, const T& b);
    inline bool isConnected(const T& a, const T&& b);
    inline bool isConnected(const T&& a, const T&& b);
 
    inline T getComponentSize(const T& a);
    inline T getComponentSize(const T&& a);

    inline T totalComponents() const;
};
 
/* impl */
template<typename T>
DSU<T>::DSU()
    : DSU({})
{ }
 
template<typename T>
DSU<T>::DSU(const std::vector<T>& v)
{
    static_assert(std::is_integral<T>::value, "TYPE_ERROR: Integral type required to instantiate class 'DSU'\n");
 
    cmptCount_ = v.size();
    rank_.resize(v.size());
    parent_.resize(v.size());
    componentSize_.resize(v.size());
 
    for (size_t i = 0; i < v.size(); ++i)
    {
        rank_[i] = 0;
        parent_[i] = i;
        componentSize_[i] = 1;
    }
}
 
template<typename T>
void DSU<T>::construct(const std::vector<T>& v)
{
    cmptCount_ = v.size();
    rank_.resize(v.size());
    parent_.resize(v.size());
    componentSize_.resize(v.size());
 
    for (size_t i = 0; i < v.size(); ++i)
    {
        rank_[i] = 0;
        parent_[i] = i;
        componentSize_[i] = 1;
    }
}
 
template<typename T>
void DSU<T>::construct(const std::vector<T>&& v)
{
    cmptCount_ = v.size();
    rank_.resize(v.size());
    parent_.resize(v.size());
    componentSize_.resize(v.size());
 
    for (size_t i = 0; i < v.size(); ++i)
    {
        rank_[i] = 0;
        parent_[i] = i;
        componentSize_[i] = 1;
    }
}
 
template<typename T>
void DSU<T>::addElement()
{
    ++cmptCount_;
    rank_.push_back(0);
    parent_.push_back(parent_.size());
    componentSize_.push_back(1);
}
 
template<typename T>
T DSU<T>::getParent(const T& node)
{
    if (parent_[node] == node)
        return node;
    return parent_[node] = getParent(parent_[node]); // path compression
}
 
template<typename T>
T DSU<T>::getParent(const T&& node)
{
    if (parent_[node] == node)
        return node;
    return parent_[node] = getParent(parent_[node]);
}
 
template<typename T>
bool DSU<T>::unite(T& a, T& b)
{
    T x = getParent(a);
    T y = getParent(b);
 
    if (x != y)
    {
        --cmptCount_;
        if ((rank_[x] != rank_[y] && rank_[x] < rank_[y]) || x > y)
            std::swap(x, y);
        parent_[y] = x;
        ++rank_[x];
        componentSize_[x] += componentSize_[y];
        componentSize_[y] = 0;
        return true;
    }
    return false; // a and b are already part of the same component
}
 
template<typename T>
bool DSU<T>::unite(T&& a, T& b)
{
    T x = getParent(a);
    T y = getParent(b);
 
    if (x != y)
    {
        --cmptCount_;
        if ((rank_[x] != rank_[y] && rank_[x] < rank_[y]) || x > y)
            std::swap(x, y);
        parent_[y] = x;
        ++rank_[x];
        componentSize_[x] += componentSize_[y];
        componentSize_[y] = 0;
        return true;
    }
    return false;
}
 
template<typename T>
bool DSU<T>::unite(T& a, T&& b)
{
    T x = getParent(a);
    T y = getParent(b);
 
    if (x != y)
    {
        --cmptCount_;
        if ((rank_[x] != rank_[y] && rank_[x] < rank_[y]) || x > y)
            std::swap(x, y);
        parent_[y] = x;
        ++rank_[x];
        componentSize_[x] += componentSize_[y];
        componentSize_[y] = 0;
        return true;
    }
    return false;
}
 
template<typename T>
bool DSU<T>::unite(T&& a, T&& b)
{
    T x = getParent(a);
    T y = getParent(b);
 
    if (x != y)
    {
        --cmptCount_;
        if ((rank_[x] != rank_[y] && rank_[x] < rank_[y]) || x > y)
            std::swap(x, y);
        parent_[y] = x;
        ++rank_[x];
        componentSize_[x] += componentSize_[y];
        componentSize_[y] = 0;
        return true;
    }
    return false;
}
 
template<typename T>
inline bool DSU<T>::isConnected(const T& a, const T& b)
{
    return getParent(a) == getParent(b);
}
 
template<typename T>
inline bool DSU<T>::isConnected(const T&& a, const T& b)
{
    return getParent(a) == getParent(b);
}
 
template<typename T>
inline bool DSU<T>::isConnected(const T& a, const T&& b)
{
    return getParent(a) == getParent(b);
}
 
template<typename T>
inline bool DSU<T>::isConnected(const T&& a, const T&& b)
{
    return getParent(a) == getParent(b);
}
 
template<typename T>
inline T DSU<T>::getComponentSize(const T& a)
{
    return componentSize_[getParent(a)];
}
 
template <typename T>
inline T DSU<T>::getComponentSize(const T&& a)
{
    return componentSize_[getParent(a)];
}

template <typename T>
inline T DSU<T>::totalComponents() const
{
    return cmptCount_;
}
#endif /* _DSU_H_ */