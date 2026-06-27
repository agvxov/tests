class Background_managment_system : public Entity {
    void draw(void) {
        DrawTexture(rms->get("asset/background.png"), 0, 0, WHITE);
    }
};
