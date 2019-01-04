#include <functional>
#include <iostream>
#include <utility>

namespace geometry {
    struct Point {
        int x = 0;
        int y = 0;
    };

    Point operator+(const Point& lhs, const Point& rhs);
    bool operator==(const Point& lhs, const Point& rhs);

    std::ostream& operator<<(std::ostream& os, const Point& point);

    struct Hash
    {
        std::size_t operator()(geometry::Point const& point) const noexcept
        {
            const std::size_t h1 ( std::hash<int>{}(point.x) );
            const std::size_t h2 ( std::hash<int>{}(point.y) );
            return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
        }
    };
} // namespace geometry

// custom specialization of std::hash can be injected in namespace std
namespace std
{
} // namespace std