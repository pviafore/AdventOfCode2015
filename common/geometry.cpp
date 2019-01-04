#include "geometry.h"

namespace geometry {
    Point operator+(const Point& lhs, const Point& rhs){ 
        return Point { lhs.x + rhs.x, lhs.y + rhs.y };
    }

    bool operator==(const Point& lhs, const Point& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "Point x=" << point.x << " y=" << point.y;
        return os;
    }
} // namespace geometry