#include <vector>
#include <algorithm>
#include <iterator>
#include <type_traits>

template<typename Container>
class DeferredErase {
public:
    using container_type = Container;
    using size_type = typename Container::size_type;
    using iterator = typename Container::iterator;

    explicit DeferredErase(Container &c) : c_(&c) {}

    // Mark by iterator (works in O(1) for random-access containers like std::vector)
    void mark(iterator it) {
        // distance on random-access iterators is O(1); check at compile time if desired
        static_assert(std::is_same<typename std::iterator_traits<iterator>::iterator_category,
                                   std::random_access_iterator_tag>::value,
                      "mark(it) requires random-access iterator (vector-like)");
        size_type idx = static_cast<size_type>(std::distance(c_->begin(), it));
        marks_.push_back(idx);
    }

    // Mark by index directly
    void mark_index(size_type idx) { marks_.push_back(idx); }

    // Execute erasure: sort, unique, build contiguous ranges, erase ranges from back to front
    void execute() {
        if (marks_.empty()) return;
        std::sort(marks_.begin(), marks_.end());
        marks_.erase(std::unique(marks_.begin(), marks_.end()), marks_.end());

        // collapse contiguous indices into ranges [start, end]
        std::vector<std::pair<size_type, size_type>> ranges;
        size_type start = marks_[0];
        size_type prev  = start;
        for (size_t i = 1; i < marks_.size(); ++i) {
            if (marks_[i] == prev + 1) {
                prev = marks_[i];
            } else {
                ranges.emplace_back(start, prev);
                start = prev = marks_[i];
            }
        }
        ranges.emplace_back(start, prev);

        // erase ranges in reverse order (so later indices removed first)
        for (auto it = ranges.rbegin(); it != ranges.rend(); ++it) {
            size_type s = it->first;
            size_type e = it->second;
            // erase [begin+s, begin+e+1)
            c_->erase(c_->begin() + static_cast<std::ptrdiff_t>(s),
                     c_->begin() + static_cast<std::ptrdiff_t>(e + 1));
        }
        marks_.clear();
    }

    ~DeferredErase() {
        execute();
    }

private:
    Container *c_;
    std::vector<size_type> marks_;
};
