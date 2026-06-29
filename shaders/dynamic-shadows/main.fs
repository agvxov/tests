#version 330

uniform int W;
uniform int H;

uniform sampler2D texture0;

uniform vec2 u_light_pos;
uniform float u_radius;
uniform vec4 u_obelisk;

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

float falloff(float d, float radius) {
    float x = d / radius;
    return exp(-x * x * 3.0);
}

float sign2d(vec2 p1, vec2 p2, vec2 p3) {
    return (p1.x - p3.x) * (p2.y - p3.y)
         - (p2.x - p3.x) * (p1.y - p3.y);
}

bool point_in_triangle(vec2 p, vec2 a, vec2 b, vec2 c) {
    float d1 = sign2d(p, a, b);
    float d2 = sign2d(p, b, c);
    float d3 = sign2d(p, c, a);

    bool has_neg = (d1 < 0.0)
                || (d2 < 0.0)
                || (d3 < 0.0)
    ;

    bool has_pos = (d1 > 0.0)
                || (d2 > 0.0)
                || (d3 > 0.0)
    ;

    return !(has_neg && has_pos);
}

bool point_in_quad(
  vec2 p,
  vec2 a,
  vec2 b,
  vec2 c,
  vec2 d
) {
    return point_in_triangle(p, a, b, c)
        || point_in_triangle(p, b, d, c)
    ;
}

void main()
{
    vec4 t = texture(texture0, fragTexCoord);

    vec2 pixel_pos = vec2(
        gl_FragCoord.x,
        H - gl_FragCoord.y
    );

    vec3 color = t.rgb;

    float d = distance(pixel_pos, u_light_pos);

    float brightness = falloff(d, u_radius);
    brightness = pow(brightness, 2.0);
    brightness = clamp(brightness, 0.0, 1.0);

    //---

    vec2 rect_min = u_obelisk.xy;
    vec2 rect_max = rect_min + u_obelisk.zw;

    bool inside_rect = pixel_pos.x >= rect_min.x
                    && pixel_pos.x <= rect_max.x
                    && pixel_pos.y >= rect_min.y
                    && pixel_pos.y <= rect_max.y
    ;

    if (inside_rect) {
        color *= brightness;
        finalColor = vec4(color, t.a);
        return;
    }

    vec2 center = rect_min + u_obelisk.zw * 0.5;

    vec2 dir = normalize(center - u_light_pos);

    vec2 a;
    vec2 b;

    if (abs(dir.x) > abs(dir.y)) {
        if (dir.x > 0.0) {
            // left face
            a = vec2(rect_min.x, rect_min.y);
            b = vec2(rect_min.x, rect_max.y);
        } else {
            // right face
            a = vec2(rect_max.x, rect_min.y);
            b = vec2(rect_max.x, rect_max.y);
        }
    } else {
        if (dir.y > 0.0) {
            // top face
            a = vec2(rect_min.x, rect_min.y);
            b = vec2(rect_max.x, rect_min.y);
        } else {
            // bottom face
            a = vec2(rect_min.x, rect_max.y);
            b = vec2(rect_max.x, rect_max.y);
        }
    }

    //---

    float shadow_len = 2000.0;

    vec2 a2 = a + normalize(a - u_light_pos) * shadow_len;

    vec2 b2 = b + normalize(b - u_light_pos) * shadow_len;

    bool shadowed = point_in_quad(
        pixel_pos,
        a,
        b,
        a2,
        b2
    );

    if (shadowed) {
        brightness = 0.0;
    }

    color *= brightness;
    finalColor = vec4(color, t.a);
}
