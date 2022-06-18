#include "headers/Material.h"
#pragma once
// généré depuis http://devernay.free.fr/cours/opengl/materials.html
// https://regex101.com/r/Ni1WLx/1

float ambiant_emerald[3] = { 0.0215f, 0.1745f, 0.0215f };
float diffuse_emerald[3] = { 0.07568f, 0.61424f, 0.07568f };
float specular_emerald[3] = { 0.633f, 0.727811f, 0.633f };
Material emerald = { ambiant_emerald , diffuse_emerald, specular_emerald, 0.6f * 128.0f };

float ambiant_jade[3] = { 0.135f, 0.2225f, 0.1575f };
float diffuse_jade[3] = { 0.54f, 0.89f, 0.63f };
float specular_jade[3] = { 0.316228f, 0.316228f, 0.316228f };
Material jade = { ambiant_jade , diffuse_jade, specular_jade, 0.1f * 128.0f };

float ambiant_obsidian[3] = { 0.05375f, 0.05f, 0.06625f };
float diffuse_obsidian[3] = { 0.18275f, 0.17f, 0.22525f };
float specular_obsidian[3] = { 0.332741f, 0.328634f, 0.346435f };
Material obsidian = { ambiant_obsidian , diffuse_obsidian, specular_obsidian, 0.3f * 128.0f };

float ambiant_pearl[3] = { 0.25f, 0.20725f, 0.20725f };
float diffuse_pearl[3] = { 1.f, 0.829f, 0.829f };
float specular_pearl[3] = { 0.296648f, 0.296648f, 0.296648f };
Material pearl = { ambiant_pearl , diffuse_pearl, specular_pearl, 0.088f * 128.0f };

float ambiant_ruby[3] = { 0.1745f, 0.01175f, 0.01175f };
float diffuse_ruby[3] = { 0.61424f, 0.04136f, 0.04136f };
float specular_ruby[3] = { 0.727811f, 0.626959f, 0.626959f };
Material ruby = { ambiant_ruby , diffuse_ruby, specular_ruby, 0.6f * 128.0f };

float ambiant_turquoise[3] = { 0.1f, 0.18725f, 0.1745f };
float diffuse_turquoise[3] = { 0.396f, 0.74151f, 0.69102f };
float specular_turquoise[3] = { 0.297254f, 0.30829f, 0.306678f };
Material turquoise = { ambiant_turquoise , diffuse_turquoise, specular_turquoise, 0.1f * 128.0f };

float ambiant_brass[3] = { 0.329412f, 0.223529f, 0.027451f };
float diffuse_brass[3] = { 0.780392f, 0.568627f, 0.113725f };
float specular_brass[3] = { 0.992157f, 0.941176f, 0.807843f };
Material brass = { ambiant_brass , diffuse_brass, specular_brass, 0.21794872f * 128.0f };

float ambiant_bronze[3] = { 0.2125f, 0.1275f, 0.054f };
float diffuse_bronze[3] = { 0.714f, 0.4284f, 0.18144f };
float specular_bronze[3] = { 0.393548f, 0.271906f, 0.166721f };
Material bronze = { ambiant_bronze , diffuse_bronze, specular_bronze, 0.2f * 128.0f };

float ambiant_chrome[3] = { 0.25f, 0.25f, 0.25f };
float diffuse_chrome[3] = { 0.4f, 0.4f, 0.4f };
float specular_chrome[3] = { 0.774597f, 0.774597f, 0.774597f };
Material chrome = { ambiant_chrome , diffuse_chrome, specular_chrome, 0.6f * 128.0f };

float ambiant_copper[3] = { 0.19125f, 0.0735f, 0.0225f };
float diffuse_copper[3] = { 0.7038f, 0.27048f, 0.0828f };
float specular_copper[3] = { 0.256777f, 0.137622f, 0.086014f };
Material copper = { ambiant_copper , diffuse_copper, specular_copper, 0.1f * 128.0f };

float ambiant_gold[3] = { 0.24725f, 0.1995f, 0.0745f };
float diffuse_gold[3] = { 0.75164f, 0.60648f, 0.22648f };
float specular_gold[3] = { 0.628281f, 0.555802f, 0.366065f };
Material gold = { ambiant_gold , diffuse_gold, specular_gold, 0.4f * 128.0f };

float ambiant_silver[3] = { 0.19225f, 0.19225f, 0.19225f };
float diffuse_silver[3] = { 0.50754f, 0.50754f, 0.50754f };
float specular_silver[3] = { 0.508273f, 0.508273f, 0.508273f };
Material silver = { ambiant_silver , diffuse_silver, specular_silver, 0.4f * 128.0f };

float ambiant_black_plastic[3] = { 0.0f, 0.0f, 0.0f };
float diffuse_black_plastic[3] = { 0.01f, 0.01f, 0.01f };
float specular_black_plastic[3] = { 0.50f, 0.50f, 0.50f };
Material black_plastic = { ambiant_black_plastic , diffuse_black_plastic, specular_black_plastic, .25f * 128.0f };

float ambiant_cyan_plastic[3] = { 0.0f, 0.1f, 0.06f };
float diffuse_cyan_plastic[3] = { 0.0f, 0.50980392f, 0.50980392f };
float specular_cyan_plastic[3] = { 0.50196078f, 0.50196078f, 0.50196078f };
Material cyan_plastic = { ambiant_cyan_plastic , diffuse_cyan_plastic, specular_cyan_plastic, .25f * 128.0f };

float ambiant_green_plastic[3] = { 0.0f, 0.0f, 0.0f };
float diffuse_green_plastic[3] = { 0.1f, 0.35f, 0.1f };
float specular_green_plastic[3] = { 0.45f, 0.55f, 0.45f };
Material green_plastic = { ambiant_green_plastic , diffuse_green_plastic, specular_green_plastic, .25f * 128.0f };

float ambiant_red_plastic[3] = { 0.0f, 0.0f, 0.0f };
float diffuse_red_plastic[3] = { 0.5f, 0.0f, 0.0f };
float specular_red_plastic[3] = { 0.7f, 0.6f, 0.6f };
Material red_plastic = { ambiant_red_plastic , diffuse_red_plastic, specular_red_plastic, .25f * 128.0f };

float ambiant_white_plastic[3] = { 0.0f, 0.0f, 0.0f };
float diffuse_white_plastic[3] = { 0.55f, 0.55f, 0.55f };
float specular_white_plastic[3] = { 0.70f, 0.70f, 0.70f };
Material white_plastic = { ambiant_white_plastic , diffuse_white_plastic, specular_white_plastic, .25f * 128.0f };

float ambiant_yellow_plastic[3] = { 0.0f, 0.0f, 0.0f };
float diffuse_yellow_plastic[3] = { 0.5f, 0.5f, 0.0f };
float specular_yellow_plastic[3] = { 0.60f, 0.60f, 0.50f };
Material yellow_plastic = { ambiant_yellow_plastic , diffuse_yellow_plastic, specular_yellow_plastic, .25f * 128.0f };

float ambiant_black_rubber[3] = { 0.02f, 0.02f, 0.02f };
float diffuse_black_rubber[3] = { 0.01f, 0.01f, 0.01f };
float specular_black_rubber[3] = { 0.4f, 0.4f, 0.4f };
Material black_rubber = { ambiant_black_rubber , diffuse_black_rubber, specular_black_rubber, .078125f * 128.0f };

float ambiant_cyan_rubber[3] = { 0.0f, 0.05f, 0.05f };
float diffuse_cyan_rubber[3] = { 0.4f, 0.5f, 0.5f };
float specular_cyan_rubber[3] = { 0.04f, 0.7f, 0.7f };
Material cyan_rubber = { ambiant_cyan_rubber , diffuse_cyan_rubber, specular_cyan_rubber, .078125f * 128.0f };

float ambiant_green_rubber[3] = { 0.0f, 0.05f, 0.0f };
float diffuse_green_rubber[3] = { 0.4f, 0.5f, 0.4f };
float specular_green_rubber[3] = { 0.04f, 0.7f, 0.04f };
Material green_rubber = { ambiant_green_rubber , diffuse_green_rubber, specular_green_rubber, .078125f * 128.0f };

float ambiant_red_rubber[3] = { 0.05f, 0.0f, 0.0f };
float diffuse_red_rubber[3] = { 0.5f, 0.4f, 0.4f };
float specular_red_rubber[3] = { 0.7f, 0.04f, 0.04f };
Material red_rubber = { ambiant_red_rubber , diffuse_red_rubber, specular_red_rubber, .078125f * 128.0f };

float ambiant_white_rubber[3] = { 0.05f, 0.05f, 0.05f };
float diffuse_white_rubber[3] = { 0.5f, 0.5f, 0.5f };
float specular_white_rubber[3] = { 0.7f, 0.7f, 0.7f };
Material white_rubber = { ambiant_white_rubber , diffuse_white_rubber, specular_white_rubber, .078125f * 128.0f };

float ambiant_yellow_rubber[3] = { 0.05f, 0.05f, 0.0f };
float diffuse_yellow_rubber[3] = { 0.5f, 0.5f, 0.4f };
float specular_yellow_rubber[3] = { 0.7f, 0.7f, 0.04f };
Material yellow_rubber = { ambiant_yellow_rubber , diffuse_yellow_rubber, specular_yellow_rubber, .078125f * 128.0f };

