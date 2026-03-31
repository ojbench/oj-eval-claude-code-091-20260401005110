#ifndef ESET_HPP
#define ESET_HPP

#include <set>
#include <utility>
#include <algorithm>

template<class Key, class Compare = std::less<Key>>
class ESet {
private:
    std::set<Key, Compare> data;

public:
    using iterator = typename std::set<Key, Compare>::iterator;
    using const_iterator = typename std::set<Key, Compare>::const_iterator;

    ESet() = default;
    ~ESet() = default;

    ESet(const ESet& other) : data(other.data) {}

    ESet& operator=(const ESet& other) {
        if (this != &other) {
            data = other.data;
        }
        return *this;
    }

    ESet(ESet&& other) noexcept : data(std::move(other.data)) {}

    ESet& operator=(ESet&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    template<class... Args>
    std::pair<iterator, bool> emplace(Args&&... args) {
        return data.emplace(std::forward<Args>(args)...);
    }

    size_t erase(const Key& key) {
        return data.erase(key);
    }

    iterator find(const Key& key) const {
        return const_cast<std::set<Key, Compare>&>(data).find(key);
    }

    size_t range(const Key& l, const Key& r) const {
        if (Compare()(r, l)) return 0;
        auto it_l = data.lower_bound(l);
        auto it_r = data.upper_bound(r);
        return std::distance(it_l, it_r);
    }

    size_t size() const noexcept {
        return data.size();
    }

    iterator lower_bound(const Key& key) const {
        return const_cast<std::set<Key, Compare>&>(data).lower_bound(key);
    }

    iterator upper_bound(const Key& key) const {
        return const_cast<std::set<Key, Compare>&>(data).upper_bound(key);
    }

    iterator begin() const noexcept {
        return const_cast<std::set<Key, Compare>&>(data).begin();
    }

    iterator end() const noexcept {
        return const_cast<std::set<Key, Compare>&>(data).end();
    }
};

#endif // ESET_HPP
