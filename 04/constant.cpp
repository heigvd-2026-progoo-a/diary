

class C {
    int radius;
    C(int radius) {
        setRadius(radius);
    }

    void setRadius(int r) { if (radius >= 0) this->radius = r; }
};