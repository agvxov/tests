class Actor_management_system : public Entity {
  public:
    vector<Actor> actors;

    void update(void) override {
        for (auto & i : actors) {
            i.update();
        }
    }

    void draw(void) override {
        for (auto & i : actors) {
            i.draw();
        }
    }
};
