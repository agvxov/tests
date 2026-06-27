class Effect_management_system : public Entity {
  public:
    class Text_bouble {
      public:
        string text;
        double text_creation;
        Rectangle text_bouble = {0,0,0,0};
        double fade_timeout  = 2.0;
        double solid_timeout = 2.0;

        Text_bouble() {
            text_creation = -100;
        }

        Text_bouble(const char * s, Rectangle position)
        : text(s),
          text_bouble(position)
        {
            text_creation = GetTime();
        }

        bool is_expired(void) {
            double t  = GetTime();
            double dt = t - text_creation;
            return dt >= solid_timeout + fade_timeout;
        }

        void draw(void) {
            if (is_expired()) { return; }

            double t  = GetTime();
            double dt = t - text_creation;
            unsigned char alpha;

            if (dt <= solid_timeout) {
                alpha = 255;
            } else {
                double fd = dt - solid_timeout;
                double ratio = fd / fade_timeout;
                if (ratio < 0) ratio = 0;
                if (ratio > 1) ratio = 1;
                alpha = (unsigned char)(255.0 * (1.0 - ratio));
            }

            Color bubbleCol = { 50, 50, 50,    (unsigned char)alpha };
            Color textCol   = { 255, 255, 255, (unsigned char)alpha };

            DrawRectangleRec(text_bouble, bubbleCol);

            float fontSize = 20.0f;
            float x        = text_bouble.x + 20;
            float y        = text_bouble.y + 20;

            DrawText(text.c_str(), (int)x, (int)y, (int)fontSize, textCol);
        }
    };

    Text_bouble main_bouble;
    vector<Text_bouble> event_boubles;

    Actor * screamer;

    bool is_indicating = false;

    Effect_management_system() {
        main_bouble.text_bouble = { 472, 872, 300, 100 };
    }

    void draw_text_boubles(void) {
        main_bouble.draw();
        for (auto & i : event_boubles) {
            i.draw();
        }
    }

    void draw_cursor(void) {
        Texture2D cursor_texture = is_null_command(cq.exists("indicate"))
            ? rms->get("asset/Cursor1.png")
            : rms->get("asset/Cursor2.png")
        ;
        DrawTexture(cursor_texture, GetMouseX(), GetMouseY(), WHITE);
    }

    void update(void) override {
        do {
            Command c = cq.exists("say");

            if (is_null_command(c)) { break; }

            main_bouble.text_creation = GetTime();
            main_bouble.text = get<string>(c.argv[1]);
        } while (0);

        do {
            Command c = cq.exists("screamer");

            if (is_null_command(c)) { break; }

            screamer = new Actor(
                (Rectangle) {
                    .x      = 0,
                    .y      = 0,
                    .width  = H,
                    .height = W,
                },
                "",
                0
            );
            screamer->texture = rms->get("asset/daemon.png");
            screamer->is_visible = true;
            
            PlaySound(arm->get("asset/screamer.mp3"));
        } while (0);
    }

    void draw(void) override {
        draw_text_boubles();

        if (is_developer_mode) {
            Rectangle slot;

            slot = {0, 0, 130, 40};
            DrawRectangleRec(slot, BLACK);
            DrawText(TextFormat("%dx%d", GetMouseX(), GetMouseY()), 10, 10, 20, WHITE);

            // XXX shitty subsystem
            slot.width = 300;
            for (auto & i : cq.prev_queue) {
                slot = after(slot, 1);

                Text_bouble tb(
                    get<string>(i.argv[0]).c_str(),
                    slot
                );

                bool found_slot = false;
                for (auto & i : event_boubles) {
                    if (i.is_expired()) {
                        i = tb;
                        found_slot = true;
                        break;
                    }
                }
                if (!found_slot) {
                    event_boubles.push_back(tb);
                }
            }
        }

        do {
            Command c = cq.exists("drag");

            if (is_null_command(c)) { break; }

            DrawTexture(
                get<Texture2D>(c.argv[1]),
                GetMouseX(),
                GetMouseY(),
                WHITE
            );
        } while (0);

        draw_cursor();

        if (screamer) {
            screamer->draw();
        }
    }
};
