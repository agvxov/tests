// @BAKE g++ -o $*.out $@ -std=c++23 -lraylib -Wall -Wpedantic -ggdb
// NOTE: draft version 2 is inside the git history of neuroplex
#include <stdint.h>
#include <assert.h>
#include <vector>
#include <map>
#include <memory>
#include <raylib.h>
#include <chad/dyrect.h>
#include <chad/XXX.h>

using namespace std;

class Goy;
typedef void font_t;

using drawing_fn = void (*)(Rectangle r, Goy * self);
using sizing_fn = Rectangle (*)(Rectangle r, Goy * self);
using on_hover_fn = void(*)();
using on_click_fn = void(*)();

#define SIZING_FN [](Rectangle r, Goy * self) -> Rectangle
#define DRAWING_FN [](Rectangle r, Goy * self) -> void

struct text_style_t {
    Color color = BLACK;
    font_t * font = nullptr;

    float rotation = 0.0f;

    float font_size = 24.0f;
    float letter_spacing = 1.0f;
    float line_spacing = 1.0f;
};

struct goy_event_t {
    sizing_fn sizing_function = SIZING_FN{ return r; };
    drawing_fn drawing_function = DRAWING_FN{;};

    on_hover_fn on_hover = [](){;};
    on_click_fn on_click = [](){;};
};

struct goy_input_t {
    bool is_primary_down = false;
    Vector2 mouse_position;
};

map<string, Goy*> goy_registry;
struct Tag {
    const char * s;
};

class Goy {
  protected:
    Goy() = default;
  public:
    std::vector<std::unique_ptr<Goy>> children;

    Rectangle rectangle_proto;
    Rectangle rectangle;

    goy_event_t event_handlers;

    bool is_hidden  = false;
    bool is_hovered = false;
    bool is_clicked = false;

    string tag;

    template<typename T>
    void add_child(T&& arg) {
        if constexpr (std::is_same_v<std::decay_t<T>, Tag>) {
            tag = arg.s;
        } else {
            children.push_back(std::make_unique<std::decay_t<T>>(std::forward<T>(arg)));
        }
    }

    virtual void resize_proto(Rectangle r) final {
        rectangle = event_handlers.sizing_function(r, this);

        for (auto & i : children) {
            i->resize(rectangle);
        }
    }

    virtual void resize(Rectangle r) {
        resize_proto(r);
    }

    virtual void input_proto(goy_input_t input) final {
        if (CheckCollisionPointRec(input.mouse_position, rectangle)) {
            is_hovered = true;
            event_handlers.on_hover();
            if (input.is_primary_down) {
                is_clicked = true;
                event_handlers.on_click();
            }
        } else {
            is_hovered = false;
            is_clicked = false;
        }

        for (auto & i : children) {
            i->input_proto(input);
        }
    }

    virtual void draw_proto(void) {
        if (is_hidden) {
            return;
        }

        draw();
        event_handlers.drawing_function(rectangle, this);

        for (auto & i : children) {
            i->draw_proto();
        }
    }

    virtual void draw(void) = 0;
};

void fill_goy_registry(Goy * root) {
    assert(root);

    goy_registry[root->tag] = root;

    for (auto & c : root->children) {
        fill_goy_registry(c.get());
    }
}

class Rect : public Goy {
  public:
    Color color;

    Rect(Color color_) {
        color = color_;
    }

    Rect(goy_event_t h, Color color_) {
        event_handlers = h;
        color = color_;
    }

    void draw(void) override {
        DrawRectangleRec(
            rectangle,
            color
        );
    }
};

class Tex : public Goy {
  public:
    const char * s;
    Texture texture;

    Tex(const char * s_) {
        s = s_;
    }

    void resize(Rectangle r) override {
        texture = LoadTexture(s);
        resize_proto(r);
    }

    void draw(void) override {
        DrawTexturePro(
            texture,
            { 0, 0, (float)texture.width, (float)texture.height },
            rectangle_proto,
            { 0, 0 },
            0.0f,
            WHITE
        );
    }
};

class Panel : public Goy {
  public:
    using Goy::resize;

    template<typename... Ts>
    Panel(goy_event_t fns, Ts&&... args) {
        event_handlers = fns;
        (add_child(std::forward<Ts>(args)), ...);
    }

    void resize(void) {
        resize_proto(get_unit_rect());
    }

    void draw_proto(void) override {
        if (is_hidden) {
            return;
        }

        event_handlers.drawing_function(rectangle, this);

        for (auto & i : children) {
            i->draw_proto();
        }
    }

    void draw(void) override {
        draw_proto();
    }

    void input(void) {
        goy_input_t i;
        i.mouse_position = GetMousePosition();
        i.is_primary_down = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        input_proto(i);
    }
};

class Window : public Goy {
  public:
    using Goy::resize;

    Vector2 scroll_offset = {0,100};

    template<typename... Ts>
    Window(goy_event_t fns, Ts&&... args) {
        event_handlers = fns;
        (add_child(std::forward<Ts>(args)), ...);
    }

    void resize(void) { // XXX
        for (auto & i : children) {
            i->resize(rectangle);
        }
        event_handlers.sizing_function(rectangle, this);
    }

    void draw_proto(void) override {
        if (is_hidden) {
            return;
        }

        BeginScissorMode(
            (int)rectangle.x,
            (int)rectangle.y,
            (int)rectangle.width,
            (int)rectangle.height
        );

        Camera2D cam = { 0 };
        cam.offset = { 0, 0 };
        cam.target = scroll_offset;
        cam.rotation = 0.0f;
        cam.zoom = 1.0f;

        BeginMode2D(cam);
            event_handlers.drawing_function(rectangle, this);

            for (auto & i : children) {
                i->draw_proto();
            }
        EndMode2D();
        EndScissorMode();
    }

    void draw(void) override { ; }
};

class Text : public Goy {
  public:
    text_style_t style;
    string s;

    Text(const char * s_, text_style_t style_ = text_style_t{}) {
        s = s_;
        style = style_;
    }
    Text(sizing_fn sizing_function_, const char * s_, text_style_t style_ = text_style_t{}) {
        event_handlers.sizing_function = sizing_function_;
        s = s_;
        style = style_;
    }
    void resize(Rectangle r) override {
        auto size = get_rectangle_proto();
        rectangle_proto = {r.x,r.y,size.x,size.y};
        resize_proto(r);
    }
    void draw(void) override {
        DrawText(
            s.c_str(),
            rectangle.x,
            rectangle.y,
            style.font_size,
            style.color
        );
    }
    Vector2 get_rectangle_proto(void) {
        return MeasureTextEx(
            GetFontDefault(),
            s.c_str(),
            style.font_size,
            style.letter_spacing
        );
    }
};

class Button : public Goy {
  public:
    Button(goy_event_t fns, Text&& t_) {
        event_handlers = fns;
        add_child(Rect{GRAY});
        add_child(std::move(t_));

        auto & r = *(Rect*)children[0].get();
        r.event_handlers.drawing_function = DRAWING_FN{
            if (self->is_hovered) {
                DrawRectangleRec(
                    r,
                    RED
                );
            }
        };
    }
    void resize(Rectangle r) override {
        rectangle = event_handlers.sizing_function(r, this);

        resize_proto(r);

        auto & t = *(Text*)children[1].get();
        t.rectangle = center(rectangle, t.rectangle_proto);
    }
    void draw(void) { ; }
};

Panel p = Panel{
    {SIZING_FN{
        return get_screen_rect();
    }},
    Panel{
        {SIZING_FN{
            r = dyrect(r,,,,*0.1f);
            return r;
        }},
        Rect{
            BLACK
        },
        Button{
            {SIZING_FN{
                r = dyrect(r,,,*0.5f,);
                r = grow(r, 0.95f);
                return r;
            }},
            Text("In"),
        },
        Button{
            {
                .sizing_function = SIZING_FN{
                    r = dyrect(r,,,*0.5f,);
                    r = rail_step(r, 1);
                    r = grow(r, 0.95f);
                    return r;
                },
                .on_click = [](){
                    XXX;
                },
            },
            Text("Out"),
        },
    },
    Panel{
        {SIZING_FN{
            Rectangle o = r;
            r = dyrect(o,,, *0.35f, *0.5f);
            r = buoyance(o, r);
            return r;
        }},
        Rect{
            GRAY
        },
        Text(
            {SIZING_FN{
                return balance(r, self->rectangle_proto);
            }},
            "Info", { .color = GREEN }
        ),
        Window{
            {
                .sizing_function = SIZING_FN{
                    Rectangle tr = r;
                    tr.height = 30;

                    int k = 0;
                    for (auto & i : self->children) {
                        if (k == 0) { // XXX
                            k = 1;
                            continue;
                        }
                        auto & ii = *(Text*)i.get();
                        ii.is_hidden = true;
                        ii.rectangle = tr;

                        tr = rope_step(tr, 1);
                    }

                    return grow(r, 0.8);
                },
                .drawing_function = DRAWING_FN{
                    for (auto & i : self->children) {
                        i->is_hidden = false;
                        i->draw_proto();
                        i->is_hidden = true;
                    }
                },
            },
            Tag{"scroll_list"},
            Rect{
                {SIZING_FN{
                    return dyrect(r,,,,*100);
                }},
                YELLOW
            },
        },
    },
    Panel{
        {SIZING_FN{
            Rectangle o = r;
            r = dyrect(r,,, *0.6f, *0.2f);
            r = inner_down(o, r);
            r = balance(o, r);
            return r;
        }},
        Rect{
            BLUE
        },
        Panel{
            {
                .sizing_function = SIZING_FN{
                    Rectangle tr = r;
                    tr = dyrect(tr,,,*0.25f,);

                    for (auto & i : self->children) {
                        Rectangle trr = tr;
                        trr.width = trr.height;
                        trr = balance(tr, trr);

                        auto & ii = *(Tex*)i.get();
                        ii.is_hidden = true;
                        ii.rectangle_proto = trr;

                        tr = rail_step(tr, 1);
                    }

                    return r;
                },
                .drawing_function = DRAWING_FN{
                    for (auto & i : self->children) {
                        i->is_hidden = false;
                        i->draw();
                        i->is_hidden = true;
                    }
                }
            },
            Tex{"dog.jpg"},
            Tex{"dog.jpg"},
            Tex{"dog.jpg"},
            Tex{"dog.jpg"},
        },
    },
};

const int W = 600;
const int H = 400;

int main(void) {
    InitWindow(W, H, "Raylib - Hello World");
    SetTargetFPS(60);

    p.resize();
    fill_goy_registry(&p);

    assert(goy_registry.contains("scroll_list"));
    auto & l = *(Window*)goy_registry["scroll_list"];
    for (int i = 0; i < 16; ++i) {
        string s = string("Shalom ") + to_string(i);
        l.add_child(Text{s.c_str(), {.font_size=10}});
    }
    l.resize();

    while (!WindowShouldClose()) {
        p.input();
        BeginDrawing();
            ClearBackground(RAYWHITE);
            p.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
