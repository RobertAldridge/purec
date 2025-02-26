
// anag.h

#define ANAG_LOGI(...) do{ __android_log_print(ANDROID_LOG_INFO, "threaded_app", __VA_ARGS__); }while(0)
#define ANAG_LOGE(...) do{ __android_log_print(ANDROID_LOG_ERROR, "threaded_app", __VA_ARGS__); }while(0)

#ifndef NDEBUG
#define ANAG_LOGV(...) do{ __android_log_print(ANDROID_LOG_VERBOSE, "threaded_app", __VA_ARGS__); }while(0)
#else
#define ANAG_LOGV(...) do{ /*nop*/; }while(0)
#endif

#if 1
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "stardew_farm.obj"
#define OBJ_MTL_FILENAME "stardew_farm.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "stardew_farm.png"}

#define OBJ_SCALE 256.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {1}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "neo_tokyo.obj"
#define OBJ_MTL_FILENAME "neo_tokyo.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "neo_tokyo.png"}

#define OBJ_SCALE 256.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE true

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "viking_room.obj"
#define OBJ_MTL_FILENAME "viking_room.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "viking_room.png"}

#define OBJ_SCALE 2.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE true

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "room_07.obj"
#define OBJ_MTL_FILENAME "room_07.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "room_07.png"}

#define OBJ_SCALE 128.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "woman_posing.obj"
#define OBJ_MTL_FILENAME "woman_posing.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "woman_posing.png"}

#define OBJ_SCALE 4.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {1, 2, 3}

#define OBJ_WITH_TEXTURE  {1, 1, 2}

#define OBJ_WITH_MATERIAL {-1, -1, -1}

#define OBJ_FILENAME "chiku-sus-tetas-pose.obj"
#define OBJ_MTL_FILENAME "chiku-sus-tetas-pose.mtl"

#define OBJ_TEXTURE_COUNT 3
#define OBJ_TEXTURE_FILENAME {"white.png", "chiku-sus-tetas-pose_chikufnia.png", "chiku-sus-tetas-pose_chicaClothesTex_baseColor.png"}

#define OBJ_SCALE 64.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2, 3, 4, 5, 6, 7, 8}

#define OBJ_WITH_TEXTURE  {1, 1, 1, 1, 1, 1, 1, 0, 0}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1, -1, -1, -1, -1, -1}

#define OBJ_FILENAME "chiku-nsfw-pose.obj"
#define OBJ_MTL_FILENAME "chiku-nsfw-pose.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"chiku-nsfw-pose_chiku_baseColor.png", "chiku-nsfw-pose_chiku_props_texture.png"}

#define OBJ_SCALE 64.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// texture issue (and only one shape); honda-shadow-rs-2010
#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "honda-shadow-rs-2010.obj"
#define OBJ_MTL_FILENAME "honda-shadow-rs-2010.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "honda-shadow-rs-2010.png"}

#define OBJ_SCALE 2.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// hair is not textured correctly; sexy-goblin
#if 0
#define OBJ_SHAPES_INDEX  {0, 3}

#define OBJ_WITH_TEXTURE  {2, 2}

#define OBJ_WITH_MATERIAL {-1, -1}

#define OBJ_FILENAME "sexy-goblin.obj"
#define OBJ_MTL_FILENAME "sexy-goblin.mtl"

#define OBJ_TEXTURE_COUNT 3
#define OBJ_TEXTURE_FILENAME {"white.png", "sexy-goblin_hair.png", "sexy-goblin_skin_panties.png"}

#define OBJ_SCALE 8.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// texture is for scene not body; sadmeal
#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2}

#define OBJ_WITH_TEXTURE  {2, 1, 3}

#define OBJ_WITH_MATERIAL {-1, -1, -1}

#define OBJ_FILENAME "sadmeal.obj"
#define OBJ_MTL_FILENAME "sadmeal.mtl"

#define OBJ_TEXTURE_COUNT 4
#define OBJ_TEXTURE_FILENAME {"white.png", "sadmeal_clothes_color.png", "sadmeal_face_color.png", "sadmeal_scene_color.png"}

#define OBJ_SCALE 8.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2, 3}

#define OBJ_WITH_TEXTURE  {2, 1, 3, 4}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1}

#define OBJ_FILENAME "anime-girl-model-3.obj"
#define OBJ_MTL_FILENAME "anime-girl-model-3.mtl"

#define OBJ_TEXTURE_COUNT 5
#define OBJ_TEXTURE_FILENAME {"white.png", "anime-girl-model-3_RGB_59d10c6ca0de4a22bfa4dbdc96d9616e_Body.png", "anime-girl-model-3_RGB_782632343fbb4317b1b0c7e18535426a_Cloth.png", "anime-girl-model-3_RGB_a503f10c281a40ccbcdec40277e26e20_Gun.png", "anime-girl-model-3_RGB_bd18134b252943558ae796c6564b9e2c_Hair.png"}

#define OBJ_SCALE 128.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2, 3, 4, 5, 6, 7, 8}

#define OBJ_WITH_TEXTURE  {1, 2, 1, 4, 2, 0, 2, 2, 3}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1, -1, -1, -1, -1, -1}

#define OBJ_FILENAME "lopunny-pose-butt-ass.obj"
#define OBJ_MTL_FILENAME "lopunny-pose-butt-ass.mtl"

#define OBJ_TEXTURE_COUNT 5
#define OBJ_TEXTURE_FILENAME {"white.png", "lopunny-pose-butt-ass_bodyS_diffuse.png", "lopunny-pose-butt-ass_eyeball_l_diffuse.png", "lopunny-pose-butt-ass_head_diffuse.png", "lopunny-pose-butt-ass_material_5_diffuse.png"}

#define OBJ_SCALE 2.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "interior-study.obj"
#define OBJ_MTL_FILENAME "interior-study.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "interior-study.png"}

#define OBJ_SCALE 128.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2}

#define OBJ_WITH_TEXTURE  {2, 2, 1}

#define OBJ_WITH_MATERIAL {-1, -1, -1}

#define OBJ_FILENAME "chiku-se-sienta-su-nalga-en-la-tierra-pose.obj"
#define OBJ_MTL_FILENAME "chiku-se-sienta-su-nalga-en-la-tierra-pose.mtl"

#define OBJ_TEXTURE_COUNT 3
#define OBJ_TEXTURE_FILENAME {"white.png", "chiku-se-sienta-su-nalga-en-la-tierra-pose_chicaClothesTex_baseColor.png", "chiku-se-sienta-su-nalga-en-la-tierra-pose_chikufnia.png"}

#define OBJ_SCALE 64.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2, 3, 4, 5, 6}

#define OBJ_WITH_TEXTURE  {1, 1, 3, 1, 4, 2, 0}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1, -1, -1, -1}

#define OBJ_FILENAME "ankha-pose-butt-naked.obj"
#define OBJ_MTL_FILENAME "ankha-pose-butt-naked.mtl"

#define OBJ_TEXTURE_COUNT 5
#define OBJ_TEXTURE_FILENAME {"white.png", "ankha-pose-butt-naked_accessories_baseColor.png", "ankha-pose-butt-naked_body_baseColor.png", "ankha-pose-butt-naked_hair_baseColor.png", "ankha-pose-butt-naked_snake_baseColor.png"}

#define OBJ_SCALE 8.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 3, 4}

#define OBJ_WITH_TEXTURE  {1, 1, 1, 1}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1}

#define OBJ_FILENAME "momscarada-pose.obj"
#define OBJ_MTL_FILENAME "momscarada-pose.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "momscarada-pose.png"}

#define OBJ_SCALE 2.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// head is not textured; km-pinki
#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}

#define OBJ_WITH_TEXTURE  {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}

#define OBJ_FILENAME "km-pinki.obj"
#define OBJ_MTL_FILENAME "km-pinki.mtl"

#define OBJ_TEXTURE_COUNT 3
#define OBJ_TEXTURE_FILENAME {"white.png", "km-pinki_1000018810.png", "km-pinki_1000018811.png"}

#define OBJ_SCALE 4.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "sword-of-artorias.obj"
#define OBJ_MTL_FILENAME "sword-of-artorias.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "sword-of-artorias.jpg"}

#define OBJ_SCALE 16.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// face messed up because it is using the body texture (the whole model is 1 shape); elf-girl
#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "elf-girl.obj"
#define OBJ_MTL_FILENAME "elf-girl.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "elf-girl.png"}

#define OBJ_SCALE 32.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// texture issues; battle-bus
#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2, 3, 4, 5}

#define OBJ_WITH_TEXTURE  {1, 1, 2, 2, 2, 1}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1, -1, -1}

#define OBJ_FILENAME "battle-bus.obj"
#define OBJ_MTL_FILENAME "battle-bus.mtl"

#define OBJ_TEXTURE_COUNT 3
#define OBJ_TEXTURE_FILENAME {"white.png", "battle-bus_bus17_bus1910_bus_Material__25_BaseColor.png", "battle-bus_bus17_bus1910_bus_Material__26_BaseColor.png"}

#define OBJ_SCALE 512.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "trailer.obj"
#define OBJ_MTL_FILENAME "trailer.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "trailer.png"}

#define OBJ_SCALE 256.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2, 3, 4, 5, 6, 7}

#define OBJ_WITH_TEXTURE  {2, 2, 2, 2, 1, 1, 1, 3}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1, -1, -1, -1, -1}

#define OBJ_FILENAME "just-a-girl.obj"
#define OBJ_MTL_FILENAME "just-a-girl.mtl"

#define OBJ_TEXTURE_COUNT 4
#define OBJ_TEXTURE_FILENAME {"white.png", "just-a-girl_body.png", "just-a-girl_head.png", "just-a-girl_all.png"}

#define OBJ_SCALE 128.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// only materials, no textures
#if 0
#define OBJ_SHAPES_INDEX \
{ \
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, \
   32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, \
   64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, \
   96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, \
  128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, \
  160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, \
  192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, \
  224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246 \
}

#define OBJ_WITH_TEXTURE \
{ \
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 \
}

#define OBJ_WITH_MATERIAL \
{ \
   17, 18, 18, 18, 16, 16, 22, 18, 13, 22, 22, 22, 16, 13, 13, 13, 22, 22, 22, 23, 20, 21, 17, 1, 11, 20, 20, 1, 20, 1, 20, 16, \
   20, 11, 20, 1, 11, 11, 22, 13, 13, 13, 13, 13, 13, 13, 18, 18, 13, 13, 13, 22, 13, 13, 18, 18, 18, 18, 17, 16, 18, 18, 18, 18, \
   17, 18, 18, 18, 18, 18, 13, 13, 13, 13, 13, 13, 13, 13, 13, 20, 21, 22, 20, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, \
   21, 21, 17, 18, 21, 18, 13, 13, 16, 13, 13, 13, 13, 13, 16, 13, 13, 13, 17, 17, 21, 21, 16, 16, 13, 13, 13, 13, 13, 13, 13, 13, \
   13, 13, 13, 13, 13, 5, 13, 13, 13, 13, 22, 24, 16, 1, 17, 21, 17, 17, 17, 17, 21, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 16, \
   16, 16, 16, 16, 17, 16, 17, 17, 16, 17, 17, 16, 17, 17, 16, 17, 17, 16, 20, 20, 17, 23, 16, 16, 17, 22, 17, 17, 17, 22, 22, 20, \
   16, 17, 17, 17, 14, 16, 18, 17, 17, 16, 16, 17, 11, 20, 16, 17, 21, 17, 24, 16, 17, 17, 17, 24, 24, 9, 9, 24, 17, 17, 24, 17, \
   21, 19, 17, 15, 17, 17, 24, 17, 20, 22, 22, 17, 17, 23, 15, 17, 17, 17, 17, 16, 16, 16, 16 \
}

#define OBJ_FILENAME "vendels-workshop.obj"
#define OBJ_MTL_FILENAME "vendels-workshop.mtl"

#define OBJ_TEXTURE_COUNT 1
#define OBJ_TEXTURE_FILENAME {"white.png"}

#define OBJ_SCALE 4.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {2, 3, 4, 5, 6, 8, 9, 10}

#define OBJ_WITH_TEXTURE  {1, 1, 1, 1, 1, 2, 2, 1}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1, -1, -1, -1, -1}

#define OBJ_FILENAME "solarfare-butt-pose.obj"
#define OBJ_MTL_FILENAME "solarfare-butt-pose.mtl"

#define OBJ_TEXTURE_COUNT 3
#define OBJ_TEXTURE_FILENAME {"white.png", "solarfare-butt-pose_Skin_baseColor.png", "solarfare-butt-pose_Lamp.001_baseColor.png"}

#define OBJ_SCALE 64.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1}

#define OBJ_WITH_TEXTURE  {1, 2}

#define OBJ_WITH_MATERIAL {-1, -1}

#define OBJ_FILENAME "sea-house.obj"
#define OBJ_MTL_FILENAME "sea-house.mtl"

#define OBJ_TEXTURE_COUNT 3
#define OBJ_TEXTURE_FILENAME {"white.png", "sea-house_sea_11112_sheet_Material__25_color.png", "sea-house_sea_11112_sheet_Material__37_color.png"}

#define OBJ_SCALE 512.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}

#define OBJ_WITH_TEXTURE  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}

#define OBJ_WITH_MATERIAL {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}

#define OBJ_FILENAME "minecraft-bastion.obj"
#define OBJ_MTL_FILENAME "minecraft-bastion.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "minecraft-bastion.bmp"}

#define OBJ_SCALE 2.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0, 1}

#define OBJ_WITH_TEXTURE  {1, 2}

#define OBJ_WITH_MATERIAL {-1, -1}

#define OBJ_FILENAME "mayan-temple.obj"
#define OBJ_MTL_FILENAME "mayan-temple.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "mayan-temple.jpg", "maya_temple.bmp"}

#define OBJ_SCALE 16.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX \
{ \
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, \
   32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 \
}

#define OBJ_WITH_TEXTURE \
{ \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 \
}

#define OBJ_WITH_MATERIAL \
{ \
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, \
   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 \
}

#define OBJ_FILENAME "a-minecraft-village.obj"
#define OBJ_MTL_FILENAME "a-minecraft-village.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "a-minecraft-village.bmp"}

#define OBJ_SCALE 8.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "minecraft-3d-map-big-village.obj"
#define OBJ_MTL_FILENAME "minecraft-3d-map-big-village.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "minecraft-3d-map-big-village.bmp"}

#define OBJ_SCALE 512.0
#define OBJ_HAND_SCALE 1.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// local coordinate system origin is messed up; girl-sitting
#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "girl-sitting.obj"
#define OBJ_MTL_FILENAME "girl-sitting.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "girl-sitting.jpeg"}

#define OBJ_SCALE 4.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// clothing is using skin texture (there's only one shape)
#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "pride-bonfie-by-tristy-artist.obj"
#define OBJ_MTL_FILENAME "pride-bonfie-by-tristy-artist.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "pride-bonfie-by-tristy-artist.png"}

#define OBJ_SCALE 4.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX  {0}

#define OBJ_WITH_TEXTURE  {1}

#define OBJ_WITH_MATERIAL {-1}

#define OBJ_FILENAME "naked_woman.obj"
#define OBJ_MTL_FILENAME "naked_woman.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "naked_woman.jpeg"}

#define OBJ_SCALE 2.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

// looks good but it's not night time
#if 0
#define OBJ_SHAPES_INDEX \
{ \
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, \
  32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45 \
}

#define OBJ_WITH_TEXTURE \
{ \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 \
}

#define OBJ_WITH_MATERIAL \
{ \
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, \
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 \
}

#define OBJ_FILENAME "plaza_night_time.obj"
#define OBJ_MTL_FILENAME "plaza_night_time.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "plaza_night_time_transparent_diffuse.bmp"}

#define OBJ_SCALE 128.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX \
{ \
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, \
  32 \
}

#define OBJ_WITH_TEXTURE \
{ \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, \
  2 \
}

#define OBJ_WITH_MATERIAL \
{ \
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, \
  -1 \
}

#define OBJ_FILENAME "cathedral.obj"
#define OBJ_MTL_FILENAME "cathedral.mtl"

#define OBJ_TEXTURE_COUNT 3
#define OBJ_TEXTURE_FILENAME {"white.png", "cathedral_base_emissive.jpeg", "cathedral_transparent_emissive.bmp"}

#define OBJ_SCALE 64.0
#define OBJ_HAND_SCALE 2.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

#if 0
#define OBJ_SHAPES_INDEX \
{ \
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 \
}

#define OBJ_WITH_TEXTURE \
{ \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 \
}

#define OBJ_WITH_MATERIAL \
{ \
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 \
}

#define OBJ_FILENAME "monastery_of_batalha-night.obj"
#define OBJ_MTL_FILENAME "monastery_of_batalha-night.mtl"

#define OBJ_TEXTURE_COUNT 2
#define OBJ_TEXTURE_FILENAME {"white.png", "monastery_of_batalha-night_material_baseColor.jpeg"}

#define OBJ_SCALE 128.0
#define OBJ_HAND_SCALE 4.0

#define OBJ_HAND_TRANSLATE_X 0.0
#define OBJ_HAND_TRANSLATE_Y 0.0
#define OBJ_HAND_TRANSLATE_Z 0.0

#define OBJ_ROTATE false

#define OBJ_NORMAL_NEGATIVE false

#define OBJ_IMAGE_FLIP_Y true
#endif

//struct XrInstanceCreateInfoAndroidKHR
//{
//  XrStructureType type;
//  const void* next;
//  void* applicationVM;
//  void* applicationActivity;
//};

struct AndroidAppState
{
  ANativeWindow* NativeWindow = nullptr;
  bool Resumed = false;
};

struct android_app;

struct android_poll_source
{
  int32_t id;

  struct android_app* app;

  void (*process)(struct android_app* app, struct android_poll_source* source);
};

struct android_app
{
  void* userData;

  void (*onAppCmd)(struct android_app* app, int32_t cmd);

  int32_t (*onInputEvent)(struct android_app* app, AInputEvent* event);

  ANativeActivity* activity;

  AConfiguration* config;

  void* savedState;
  size_t savedStateSize;

  ALooper* looper;

  AInputQueue* inputQueue;

  ANativeWindow* window;

  ARect contentRect;

  int activityState;

  int destroyRequested;

  pthread_mutex_t mutex;
  pthread_cond_t cond;

  int msgread;
  int msgwrite;

  pthread_t thread;

  struct android_poll_source cmdPollSource;
  struct android_poll_source inputPollSource;

  int running;
  int stateSaved;
  int destroyed;
  int redrawNeeded;

  AInputQueue* pendingInputQueue;
  ANativeWindow* pendingWindow;
  ARect pendingContentRect;
};

enum
{
  LOOPER_ID_MAIN = 1,
  LOOPER_ID_INPUT = 2,
  LOOPER_ID_USER = 3
};

enum
{
  APP_CMD_INPUT_CHANGED,
  APP_CMD_INIT_WINDOW,
  APP_CMD_TERM_WINDOW,
  APP_CMD_WINDOW_RESIZED,
  APP_CMD_WINDOW_REDRAW_NEEDED,
  APP_CMD_CONTENT_RECT_CHANGED,
  APP_CMD_GAINED_FOCUS,
  APP_CMD_LOST_FOCUS,
  APP_CMD_CONFIG_CHANGED,
  APP_CMD_LOW_MEMORY,
  APP_CMD_START,
  APP_CMD_RESUME,
  APP_CMD_SAVE_STATE,
  APP_CMD_PAUSE,
  APP_CMD_STOP,
  APP_CMD_DESTROY
};

extern JNIEnv* gEnvironment;

extern struct android_app* gApplication;

void AnagShowHelpBlah();

bool AnagUpdateOptionsFromSystemProperties();

unsigned char* AnagLoadFileBlah(const char* fileName, int* fileSize);

/**
 * Process the next main command.
 */
void anag_app_handle_cmd(struct android_app* app, int32_t cmd);

void anag_free_saved_state(struct android_app* app);

int8_t anag_android_app_read_cmd(struct android_app* app);

void anag_print_cur_config(struct android_app* app);

void anag_android_app_pre_exec_cmd(struct android_app* app, int8_t cmd);

void anag_android_app_post_exec_cmd(struct android_app* app, int8_t cmd);

//void anag_app_dummy();

void anag_android_app_destroy(struct android_app* app);

void anag_process_input(struct android_app* app, struct android_poll_source* source);

void anag_process_cmd(struct android_app* app, struct android_poll_source* source);

void* anag_android_app_entry(void* param);

struct android_app* anag_android_app_create(ANativeActivity* activity, void* savedState, size_t savedStateSize);

void anag_android_app_write_cmd(struct android_app* app, int8_t cmd);

void anag_android_app_set_input(struct android_app* app, AInputQueue* inputQueue);

void anag_android_app_set_window(struct android_app* app, ANativeWindow* window);

void anag_android_app_set_activity_state(struct android_app* app, int8_t cmd);

void anag_android_app_free(struct android_app* app);

struct android_app* AnagToApp(ANativeActivity* activity);

void anagOnDestroy(ANativeActivity* activity);

void anagOnStart(ANativeActivity* activity);

void anagOnResume(ANativeActivity* activity);

void* anagOnSaveInstanceState(ANativeActivity* activity, size_t* outLen);

void anagOnPause(ANativeActivity* activity);

void anagOnStop(ANativeActivity* activity);

void anagOnConfigurationChanged(ANativeActivity* activity);

void anagOnContentRectChanged(ANativeActivity* activity, const ARect* r);

void anagOnLowMemory(ANativeActivity* activity);

void anagOnWindowFocusChanged(ANativeActivity* activity, int focused);

void anagOnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);

void anagOnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);

void anagOnNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window);

void anagOnNativeWindowResized(ANativeActivity* activity, ANativeWindow* window);

void anagOnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);

void anagOnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);

extern "C" __attribute__ ( (visibility ("default") ) ) void ANativeActivity_onCreate(
  ANativeActivity* activity,
  void* savedState,
  size_t savedStateSize
);
