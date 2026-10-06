

struct Point {
    double x, y;


    Point add(Point &other) {
        return Point(x + other.x, y + other.y);
    }

    Point operator+(Point &other) {
        return Point(x + other.x, y + other.y);
    }

    Point operator*(double s) {
        return Point(x * s, y * s);
    }
};

int main() {
    Point p(1,2);
    Point q(3,4);
    Point z;
    z = p.add(q);
    z = (p + q) * 42
}
