// @BAKE g++ -o $*.out $@ -std=c++20 -Wall
#include <concepts>

template<
    typename T,
    T min_value,
    T max_value
>
class clamped_t {
  public:
    clamped_t(T value = min_value)
        : value_(clamp(value)) {}

    operator T() const {
        return value_;
    }

    clamped_t& operator=(T value) {
        value_ = clamp(value);
        return *this;
    }

    clamped_t& operator+=(T rhs) {
        value_ = clamp(value_ + rhs);
        return *this;
    }

    clamped_t& operator-=(T rhs) {
        value_ = clamp(value_ - rhs);
        return *this;
    }

  private:
    static constexpr
    T clamp(T value) {
        if (value < min_value) {
            return min_value;
        }
        if (value > max_value) {
            return max_value;
        }
        return value;
    }

    T value_;
};

signed main(void) {
    clamped_t<float, 0.0f, 10.0f> a = 3.0f;
    clamped_t<float, 0.0f, 10.0f> b = 5.0f;

    float c = a + b;

    return 0;
}
