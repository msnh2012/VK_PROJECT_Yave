#ifndef DEBUG_GLSL
#define DEBUG_GLSL

// 4 * 5 bitmaps
#define CHAR_MINUS      1792
#define CHAR_DOT        2
#define CHAR_COLON      8224

#define CHAR_A          481109
#define CHAR_E          464663
#define CHAR_G          463191
#define CHAR_P          481041
#define CHAR_M          357717
#define CHAR_V          349522
#define CHAR_X          348757

#define CHAR_0          480599
#define CHAR_1          139810
#define CHAR_2          476951
#define CHAR_3          476999
#define CHAR_4          350020
#define CHAR_5          464711
#define CHAR_6          464727
#define CHAR_7          476228
#define CHAR_8          481111
#define CHAR_9          481095


// https://www.shadertoy.com/view/4sBSWW
float print_char(vec2 pos, uint char_bits) {
    if(pos.x < 0.0 || pos.y < 0.0 || pos.x >= 1.0 || pos.y >= 1.0) {
        return 0.0;
    }

    const uint bits = uint(pos.x * 4.0) | (uint((1.0 - pos.y) * 5.0) << 2);
    return ((char_bits / (1 << bits)) & 0x01) != 0 ? 1.0 : 0.0;
}




uint digit_bits(int x) {
    if(x < 0 || x > 9) {
        return 0;
    }
    const uint bits[10] = {CHAR_0, CHAR_1, CHAR_2, CHAR_3, CHAR_4, CHAR_5, CHAR_6, CHAR_7, CHAR_8, CHAR_9};
    return bits[x];
}

float print_value(vec2 pos, float value, float max_digits, float decimals) {
    if(pos.y < 0.0 || pos.y >= 1.0) {
        return 0.0;
    }

    const bool is_neg = (value < 0.0);
    value = abs(value);

    const float digits = log2(abs(value)) / log2(10.0);
    const float max_index = max(floor(digits), 0.0);
    float index = max_digits - floor(pos.x);
    uint char_bits = 0;
    if(index > -decimals - 1.01) {
        if(index > max_index) {
            if(is_neg && index < max_index + 1.5) {
                char_bits = CHAR_MINUS;
            }
        } else {
            if(index == -1.0) {
                if(decimals > 0.0) {
                    char_bits = CHAR_DOT;
                }
            } else {
                float reduced_range_value = value;
                if(index < 0.0) {
                    reduced_range_value = fract(value);
                    index += 1.0;
                }
                const float digit_value = abs(reduced_range_value / pow(10.0, index));
                char_bits = digit_bits(int(floor(mod(digit_value, 10.0))));
            }
        }
    }

    return print_char(vec2(fract(pos.x), pos.y), char_bits);
}

float print_value(vec2 coord, vec2 px_coord, vec2 font_size, float value, float max_digits, float decimals) {
    const vec2 uv = (coord - px_coord) / font_size;
    return print_value(uv, value, max_digits, decimals);
}

float print_char(vec2 coord, vec2 px_coord, vec2 font_size, uint char_bits) {
    const vec2 uv = (coord - px_coord) / font_size;
    return print_char(uv, char_bits);
}


#if 1
vec2 _font_size = vec2(8.0, 15.0);
vec2 _coord = vec2(0.0, 0.0);
vec2 _px_coord = vec2(0.0, 0.0);
float _print = 0.0;

void putc(uint char_bits) {
    _print += print_char(_coord, _px_coord, _font_size, char_bits);
    _px_coord.x += _font_size.x;
}

void putc(uint a, uint b) {
    putc(a);
    putc(b);
}

void putc(uint a, uint b, uint c) {
    putc(a, b);
    putc(c);
}

void putc(uint a, uint b, uint c, uint d) {
    putc(a, b, c);
    putc(d);
}

void putf(float value, float max_digits, float decimals) {
    _print += print_value(_coord, _px_coord, _font_size, value, max_digits, decimals);
    _px_coord.x += _font_size.x * (max_digits + decimals);
}

void next_line() {
    _px_coord.x = 0.0;
    _px_coord.y += _font_size.y;
}

float print() {
    return _print;
}
#endif

#endif

