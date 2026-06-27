#pragma once
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <cstddef>


template<typename T>
class State_machine {
  public:
    typedef int (*handler_t)(T * self, int state, int event);

    int n_states_;
    handler_t default_handler;

    // event-string → per-state handler array
    unordered_map<string, vector<handler_t>> table_;

    T * self;
    int state;

    State_machine(T* self_, int n_states)
        : self(self_),
          state(0),
          n_states_(n_states),
          default_handler(nullptr)
    {
        if (n_states_ < 0) {
            throw invalid_argument("n_states must be positive");
        }
    }

    // ensure event exists; allocate array if needed
    vector<handler_t>& ensure_event(const char* command) {
        auto it = table_.find(command);
        if (it != table_.end()) return it->second;

        // create vector: one handler per state
        vector<handler_t> arr(n_states_, default_handler);
        return table_.emplace(command, move(arr)).first->second;
    }

    // set handler for (state, event-string)
    void set_handler(int s, const char* command, handler_t h) {
        if (s < 0 || s >= n_states_)
            throw out_of_range("state out of range");

        auto& arr = ensure_event(command);
        arr[s] = h;
    }

    // get handler for (state, event-string)
    handler_t at(int s, const char* command) const {
        if (s < 0 || s >= n_states_)
            throw out_of_range("state out of range");

        auto it = table_.find(command);
        if (it == table_.end()) return default_handler;

        return it->second[s];
    }

    // call handler and update state
    void step(const char * command) {
        auto it = table_.find(command);
        handler_t h = (it == table_.end()) ? default_handler : it->second[state];

        if (!h) { return; }

        int new_state = h(self, state, 0);
        if (new_state < 0 || new_state >= n_states_) {
            throw runtime_error("handler returned invalid state");
        }

        state = new_state;
    }
};
