class Actor : public Entity {
  public:
    Rectangle screen_position;
    bool is_visible;
    Texture2D texture;
    const char * description;
    State_machine<Actor> st;
    #define HANDLER +[](Actor * self, int s, int e) -> int

    Actor(Rectangle rect_, const char * description_, int n_states)
      : screen_position(rect_)
      , is_visible(false)
      , st(this, n_states)
      , description(description_)
    { ; }

    void update(void) {
        if (!CheckCollisionPointRec(cc.position, screen_position)) { return; }

        if (cc.name == "inspect") {
            cq.issue_command({"say", description});
            return;
        } else
        if (cc.name == "hover") {
            cq.issue_command({"indicate"});
            return;
        }

        st.step(cc.name.c_str());
    }

    void draw(void) override {
        if (is_visible) {
            //DrawTexture(texture, screen_position.x, screen_position.y, WHITE);
            DrawTexturePro(
                texture,
                {
                    0,
                    0,
                    (float)texture.width,
                    (float)texture.height
                },
                screen_position,
                {0,0},
                0.0f,
                WHITE
            );
        }

        if (is_developer_mode) {
            DrawRectangle(
                screen_position.x,
                screen_position.y,
                screen_position.width,
                screen_position.height,
                Fade(ORANGE, 0.5f)
            );
        }
    }
};
