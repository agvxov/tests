/* Commands are intentionally not type checked,
 *  to cut down on devtime.
 */

class Cursor_command {
    /* Convention:
     *  > hover
     *  > inspect
     *  > take
     *  > use *
     */
  public:
    string name;
    Vector2 position;
};

class Command {
    /* Convention:
     *  > indicate
     *  > say *
     */
  public:
    using Arg = std::variant<std::string, int, Texture2D>;
    vector<Arg> argv;

    Command(initializer_list<Arg> l)
    : argv(l)
    {}
};

bool is_null_command(Command c) {
    return get<string>(c.argv[0]) == "";
}

class Command_queue : public Entity {
  public:
    vector<Command> prev_queue;
    vector<Command> next_queue;

    void issue_command(Command c) {
        next_queue.push_back(c);
    }

    Command exists(string s) {
        for (auto & i : prev_queue) {
            if (get<string>(i.argv[0]) == s) {
                return i;
            }
        }
        return {""};
    }

    void update(void) override {
        prev_queue = next_queue;
        next_queue.clear();
    }
};
