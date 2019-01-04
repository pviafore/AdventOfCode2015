#ifndef ALGO_H_
#define ALGO_H_

#include <algorithm>
#include <vector>

namespace algo {
    template<typename Container1, typename Container2>
    auto zip(Container1 container1, Container2 container2) {
        auto iter1 = container1.begin();
        auto iter2 = container2.begin();

        using TypePair = std::pair<typename decltype(iter1)::value_type, typename decltype(iter2)::value_type>;
        std::vector<TypePair> out;
        while(iter1 != container1.end() && iter2 != container2.end()) {
            out.emplace_back(*iter1++, *iter2++);
        }
        return out;
    }  

    template <typename Container, typename FilterFunction>
    auto find_matching_pairs(Container container, FilterFunction filterOperation) {
        using ContainerType = typename decltype(container.begin())::value_type; 
        std::vector<std::pair<ContainerType, ContainerType>> out;
        for (auto iter1 = container.begin(); iter1 != container.end(); ++iter1) {
            for(auto iter2 = iter1+1; iter2 != container.end(); ++iter2) {
                if (filterOperation(*iter1, *iter2)){
                    out.emplace_back(*iter1, *iter2);
                } 
                if (filterOperation(*iter2, *iter1)) {
                    out.emplace_back(*iter2, *iter1);
                }
            }
        }
        return out;
    }

    template <typename Container, typename Function>
    auto map(const Container& container, Function rowOperation) {
        using ContainerType = typename decltype(container.begin())::value_type; 
        using ReturnType = typename std::invoke_result_t<decltype(rowOperation), ContainerType>;
        std::vector<ReturnType> v;
        std::transform(container.begin(), container.end(), std::back_inserter(v), rowOperation);
        return v;
    }

    template <typename InputIterator>
    auto range(InputIterator start, InputIterator end, int step=1) {
        std::vector<typename InputIterator::value_type> v;
        for(auto r = start; r < end; r += step) {
            v.push_back(*r);
        }
        return v;
    }

    template <typename Container, typename InputIterator, typename Function>
    auto apply_cyclically(Container &container, InputIterator current, size_t numberOfTimes, Function operation) {
        while(numberOfTimes-- != 0) {
            if(current == container.end()) {
                current = container.begin();
            }

            operation(*current);
            current++;
        }
    }

    template <typename Container, typename Predicate>
    auto erase_if(Container& container, const Predicate & predicate) {
        auto it = container.begin();
        while(it!=container.end()) {
            if(predicate(*it)) {
                it = container.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    template <typename Number=unsigned int>
    auto getNumericRange(Number start, Number end) {
        std::vector<int> range;
        for(int i = start; i < end; ++i ){ 
            range.push_back(i);
        }
        return range;
    }

    template <typename Container>
    auto enumerate(const Container& container, unsigned int start=0) {
        using Pair = std::pair<typename Container::value_type, unsigned int>;
        std::vector<Pair> pairs;
        for(const auto& v: container) {
            pairs.emplace_back(v, start++);
        }
        return pairs;
    }
}

#endif