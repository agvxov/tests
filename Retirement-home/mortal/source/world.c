#include "world.h"

// -- ---------------- --
// -- World definition --
// -- ---------------- --
typedef hvec(b2BodyId) body_vector_t;

typedef struct {
    Vector2 world_offset;
    double scale;
} draw_context_t;

typedef struct {
    enum {
        WALL,
    } object_type;
} object_userdata_t;

typedef struct {
    /* The Box2D API does not expose any functions to iterate the bodies of a world,
     *  it expects you to do the book keeping.
     */
    body_vector_t bodies;
} world_userdata_t;

static
b2BodyId MortalWorldAddBody(b2WorldId world, b2BodyDef * bodyDef) {
    b2BodyId body = b2CreateBody(world, &bodyDef);

    world_userdata_t * world_userdata = b2World_GetUserData(world);
    hv_push(world_userdata.bodies, body);
}

static
void CreateMortalWall(b2WorldId world, Rectangle rect) {
    b2Vec2 center = {
        rect.x + rect.width  * 0.5f,
        rect.y + rect.height * 0.5f
    };

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
    shape_def.material.friction = 0.3f;
    shape_def.material.restitution = 0.6f;

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type     = b2_staticBody;
    bodyDef.position = center;
    b2BodyId body = MortalWorldAddBody(world, bodyDef);

    object_userdata_t * user_data = malloc(sizeof(object_userdata_t));
    user_data->object_type = WALL;
    b2Body_SetUserData(body, user_data);

    b2Polygon box = b2MakeBox(
        rect.width  * 0.5f,
        rect.height * 0.5f
    );

    b2CreatePolygonShape(body, &shape_def, &box);
}

b2WorldId CreateMortalWorld(void) {
    b2WorldId r;

    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -9.8f};
    r = b2CreateWorld(&worldDef);

    world_userdata_t * world_userdata = malloc(sizeof(world_userdata_t));
    hv_init(world_userdata.bodies);
    b2World_SetUserData(world, world_userdata);

    CreateMortalWall(
        r,
        (Rectangle) {
            .x = 0,
            .y = 0,
            .width = 10,
            .height = 10,
        }
    );

    return r;
}

// -- ------------- --
// -- World Drawing --
// -- ------------- --
static inline
Vector2 b2Vec2Vector(b2Vec2 v) {
    return (Vector2) {
        .x = v.x,
        .y = v.y,
    };
}

static inline
float transform2pipN(float f, draw_context_t * context) {
    return (float)(f * context->scale);
}

static inline
Vector2 transform2pipV(Vector2 p, draw_context_t * context) {
    return (Vector2) {
        .x = (p.x - context->world_offset.x) * context->scale,
        .y = (p.y - context->world_offset.y) * context->scale,
    };
}

void RaylibDrawPolygon(
  const b2Vec2 * vertices,
  int vertexCount,
  Color color,
  draw_context_t * context
) {
    for (int i = 0; i < vertexCount-1; i++) {
        DrawLineEx(
            transform2pipV(b2Vec2Vector(vertices[i]), context),
            transform2pipV(b2Vec2Vector(vertices[i+1]), context),
            3,
            b2HexToRaylibColor(color)
        );
    }

    DrawLineEx(
        transform2pipV(b2Vec2Vector(vertices[vertexCount-1]), context),
        transform2pipV(b2Vec2Vector(vertices[0]), context),
        3,
        color
    );
}

static
void DrawWall(b2BodyId wall, draw_context_t draw_context) {
    int shapeCount = b2Body_GetShapeCount(wall);
    assert(shapeCount > 0)

    b2ShapeId * shapes = malloc(sizeof(b2ShapeId) * shapeCount);

    int got = b2Body_GetShapes(wall, shapes, shapeCount);

    Color gray = (Color){128, 128, 128, 255};

    for (int si = 0; si < got; ++si) {
        b2ShapeId sid = shapes[si];
        if (!b2Shape_IsValid(sid)) continue;

        assert(b2Shape_GetType(sid) == b2_polygonShape);

        b2Polygon poly = b2Shape_GetPolygon(sid);
        int vc = poly.count;

        assert(vc == 4);

        b2Vec2 *worldVerts = malloc(sizeof(b2Vec2) * vc);

        for (int i = 0; i < vc; ++i) {
            worldVerts[i] = b2Body_GetWorldPoint(wall, poly.vertices[i]);
        }

        RaylibDrawPolygon(worldVerts, vc, gray, &draw_context);

        free(worldVerts);
    }

    free(shapes);
}

void DrawWorld(b2WorldId world, draw_context_t draw_context) {
    world_userdata_t * world_userdata = b2World_GetUserData(world);

    hv_foreach(auto it, world_userdata->bodies) {
        b2BodyId b = h_A(world_userdata->bodies, it);
        object_userdata_t * ud = b2Body_GetUserData(ud);
        switch (ud->object_type) {
            case WALL: {
                DrawWall(b, draw_context_t);
            } break;
            default: {
                TraceLog(LOG_ERROR, "Unknown body encountered.");
            } break;
        }
    }
}
