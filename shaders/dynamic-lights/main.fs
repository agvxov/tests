#version 330

uniform int W;
uniform int H;

uniform sampler2D texture0;
uniform vec2 u_light_pos;
uniform float u_radius;

uniform vec2 u_lamps[3];
uniform float u_lamp_colors[3*3];

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

//float falloff(float d, float radius) {
//    return max(0.0, 1.0 - d / radius);
//}

float falloff(float d, float radius) {
    float r;
    float x = d / radius;
    r = exp(-x * x * 3.0);
    return r;
}

void main() {
    vec4 t = texture(texture0, fragTexCoord);

    vec2 pixel_pos = vec2(
        gl_FragCoord.x,
        H - gl_FragCoord.y
    );

    vec3 color = t.rgb;

    float d   = distance(pixel_pos, u_light_pos);
    float g_b = falloff(d, u_radius);

    for (int i = 0; i < 3; ++i) {
        float d = distance(pixel_pos, u_lamps[i]);
        float b = falloff(d, u_radius);
        b *= 0.9;
        g_b += b;
        color += b * vec3(u_lamp_colors[i*3], u_lamp_colors[i*3+1], u_lamp_colors[i*3+2]);
    }

    g_b = pow(g_b, 2);
    g_b = clamp(g_b, 0.0, 1.0);

    color = color * g_b;

    finalColor = vec4(color, t.a);
}
