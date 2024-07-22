// @BAKE $@ -o $*.out

#if 1
class Rect {
    int _w, _h, _area;
public:
    void set_w(int w) {
        _w = w;
        area = _w * _h;
    }
    void set_h(int h) {
        _h = h;
        area = _w * _h;
    }
    int area() {
        return _area;
    }
};
#else
class Rect {
public:
    int w, h;
    int area() {
        return w * h;
    }
};
#endif

signed main() { ; }
