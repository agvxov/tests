// @BAKE g++ -o $*.out $@ -ggdb
#include <stddef.h>

template<typename T>
class weak_pointer_monostate {
    ~weak_pointer_monostate() { ; }
  public:
    T * data;
    bool is_valid;
    size_t reference_count;

    explicit
    weak_pointer_monostate(T * d)
    : data(d)
    , is_valid(true)
    , reference_count(0)
    { ; }

    void sanity_check() {
        if (not is_valid
        &&  not reference_count) {
            delete this;
        }
    }
};

template<typename T>
class weak_pointer {
    weak_pointer_monostate<T> * ms;

    void grab() {
        if (ms) {
            ++(ms->reference_count);
        }
    }

    void drop() {
        if (ms) {
            --(ms->reference_count);
            ms->sanity_check();
        }
    }

  public:
    weak_pointer()
    : ms(nullptr)
    { ; }

    explicit
    weak_pointer(weak_pointer_monostate<T> * ms_) {
        ms = ms_;
        grab();
    }

    weak_pointer(const weak_pointer& wp)
    : ms(wp.ms)
    { grab(); }

    weak_pointer(weak_pointer&& wp)
    : ms(wp.ms)
    { wp.ms = nullptr; }

    weak_pointer& operator=(const weak_pointer& wp) {
        if (this != &wp) {
            drop();
            ms = wp.ms;
            grab();
        }
        return *this;
    }

    weak_pointer& operator=(weak_pointer&& wp) {
        if (this != &wp) {
            drop();
            ms = wp.ms;
            wp.ms = nullptr;
        }
        return *this;
    }

    ~weak_pointer() {
        drop();
    }

    void * deref() {
        return ms->is_valid
            ? ms->data
            : nullptr
        ;
    }

    T * operator->() const {
        return deref();
    }

    T & operator*() const {
        return *deref();
    }

    explicit operator bool() const {
        return deref() != nullptr;
    }
};

template<typename T>
class enable_weak_pointer {
  private:
    weak_pointer_monostate<T> * ms;
  public:
    enable_weak_pointer()
    : ms(new weak_pointer_monostate<T>(static_cast<T*>(this)))
    { ; }

    enable_weak_pointer(enable_weak_pointer&& wp)
    : ms(wp.ms)
    {
        if (ms) {
          ms->data = static_cast<T*>(this);
          o.ms = nullptr;
        }
    }

    enable_weak_pointer(const enable_weak_pointer&)            = delete;
    enable_weak_pointer& operator=(const enable_weak_pointer&) = delete;

    ~enable_weak_pointer() {
        ms->is_valid = false;
        ms->sanity_check();
    }

    weak_pointer<T> make_weak_pointer() {
        return weak_pointer<T>(ms);
    }
};

class A : public enable_weak_pointer<A> {
  public:
    int i;
};

signed main(void) {
    {
        A a;
        weak_pointer<A> wp = a.make_weak_pointer();
        ++(((A*)wp.deref())->i);
    }

    weak_pointer<A> wp;
    {
        A a;
        wp = a.make_weak_pointer();
    }
    if (wp.deref()) {
        ++(((A*)wp.deref())->i);
    }

    return 0;
}
