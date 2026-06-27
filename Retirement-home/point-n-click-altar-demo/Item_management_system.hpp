class Item : public Actor {
  public:
    string name;

    Item(string name_, Texture2D tex, Vector2 position, const char * description_)
        : Actor({0,0,0,0}, description_, 0)
        , name(name_)
    {
        texture = tex;
        is_visible = true;
        screen_position.x = position.x;
        screen_position.y = position.y;
        screen_position.width = texture.width;
        screen_position.height = texture.height;
    }

    void draw(void) override {
        if (is_visible) {
            DrawTexture(texture, screen_position.x, screen_position.y, WHITE);
        }

        if (is_developer_mode) {
            DrawRectangle(
                screen_position.x,
                screen_position.y,
                texture.width,
                texture.height,
                Fade(YELLOW, 0.5f)
            );
        }
    }
};

class Item_management_system : public Entity {
  public:
    Item * shadow_hand = nullptr;
    Item * hand = nullptr;
    vector<Item> non_owned_items;
    vector<Item> owned_items;

    const int inventory_slots = 6;

    void draw(void) override {
        for (auto & i : non_owned_items) {
            i.draw();
        }

        DrawTexture(
            rms->get("asset/inventory.png"),
            W - 205,
            140,
            WHITE
        );

        Rectangle slot = {
            W - 170,
            160,
            100,
            100
        };
        for (int i = 0; i < inventory_slots; i++) {
            DrawRectangleRec(slot, BLACK);
            
            if (owned_items.size() > i) {
                Rectangle item_rec = (Rectangle) {
                    .x = 0,
                    .y = 0,
                    .width  = (float)owned_items[i].texture.width,
                    .height = (float)owned_items[i].texture.height,
                };
                item_rec = balance(slot, buoyance(slot, item_rec));

                owned_items[i].screen_position.x = item_rec.x;
                owned_items[i].screen_position.y = item_rec.y;
            }

            slot = slip(after(slot, 1), 20);
        }

        for (auto & i : owned_items) {
            i.draw();
        }
    }

    void update(void) override {
        if (!is_null_command(cq.exists("erase-hand"))
        &&  shadow_hand) {
            auto it = owned_items.begin() + (shadow_hand - owned_items.data());
            owned_items.erase(it);
            shadow_hand = nullptr;
        }

        bool do_reset_hand = false;
        if (hand
        &&  cc.name == "take") {
            cc.name = hand->name;
            do_reset_hand = true;
        }

        DeferredErase de(non_owned_items);
        for (auto it = non_owned_items.begin(); it != non_owned_items.end(); it++) {
            if (!CheckCollisionPointRec(cc.position, it->screen_position)) { continue; }

            if (cc.name == "take") {
                de.mark(it);
                owned_items.push_back(*it);
                cq.issue_command({"say", "I'll take this."});
                PlaySound(arm->get("asset/pickup.mp3"));
            } else {
                it->update();
            }
            goto post_cursor;
        }

        for (auto it = owned_items.begin(); it != owned_items.end(); it++) {
            if (!CheckCollisionPointRec(cc.position, it->screen_position)) { continue; }

            if (cc.name == "take") {
                it->is_visible = false;
                hand = &*it;
            } else {
                it->update();
            }
            goto post_cursor;
        }

        if (do_reset_hand) {
            hand->is_visible = true;
            shadow_hand = hand;
            hand = nullptr;
        }

      post_cursor:
        if (hand) {
            cq.issue_command({"drag", hand->texture});
        }
    }
};
