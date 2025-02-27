
// anag.cpp

// define this in only *one* .cc
#define TINYOBJLOADER_IMPLEMENTATION

// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust triangulation. Requires C++11
#define TINYOBJLOADER_USE_MAPBOX_EARCUT

#define GEOMETRY_H_IMPLEMENTATION 1

#define TINYGLTF_IMPLEMENTATION 1
#define TINYGLTF_ANDROID_LOAD_FROM_ASSETS 1
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.

#include "header.h"

void AnagTestTinyObjLoader()
{
  if(Geometry::gModelsIndicesDynamicData)
    return;

  tinyobj::ObjReaderConfig reader_config;

  tinyobj::ObjReader reader;

  int objFileSize = 0;
  char* objFileBuffer = (char*)AnagLoadFileBlah(OBJ_FILENAME, &objFileSize);

  int mtlFileSize = 0;
  char* mtlFileBuffer = (char*)AnagLoadFileBlah(OBJ_MTL_FILENAME, &mtlFileSize);

  if( !reader.ParseFromString(objFileBuffer, mtlFileBuffer, reader_config) )
  {
    if( !reader.Error().empty() )
    {
        std::cerr << "TinyObjReader: " << reader.Error();
    }

    //exit(1);
  }

  if( !reader.Warning().empty() )
  {
    std::cout << "TinyObjReader: " << reader.Warning();
  }

  const tinyobj::attrib_t& attrib = reader.GetAttrib();
  const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();
  const std::vector<tinyobj::material_t>& materials = reader.GetMaterials();

  size_t shapes_size = 0;
  size_t indices_size = 0;
  size_t attrib_vertices_size = 0;
  size_t num_face = 0;

  shapes_size = shapes.size();
  Log::Write(Log::Level::Info, Fmt("shapes_size %i\n", (int)shapes_size) );

  uint32_t object_shapes_index[] = OBJ_SHAPES_INDEX;

  int32_t object_with_texture[] = OBJ_WITH_TEXTURE;

  int32_t object_with_material[] = OBJ_WITH_MATERIAL;

  for(size_t s_index = 0; shapes_size > 0 && s_index < countof(object_shapes_index); s_index++)
  {
    size_t s = object_shapes_index[s_index];

    indices_size += shapes[s].mesh.indices.size();

    num_face += shapes[s].mesh.num_face_vertices.size();
  }

  if(shapes_size > 0)
  {
    Log::Write(Log::Level::Info, Fmt("indices_size %i\n", (int)indices_size) );

    attrib_vertices_size = attrib.vertices.size() / 3;
    Log::Write(Log::Level::Info, Fmt("attrib_vertices_size %i\n", (int)attrib_vertices_size) );

    Log::Write(Log::Level::Info, Fmt("num_face %i\n", (int)num_face) );
  }

  attrib_vertices_size = 3 * num_face;

#if 0
uint32_t gModelsVerticesDynamicCountOf = 0;
GeometryVertex* gModelsVerticesDynamicData = nullptr;

uint32_t gModelsIndicesDynamicCountOf = 0;
uint32_t* gModelsIndicesDynamicData = nullptr;

// constexpr GeometryVertex gModelsVerticesStaticData[];
// constexpr uint32_t gModelsIndicesStaticData[];

// uint32_t gModelsIndexCount[];
// uint32_t gModelsIndexFirst[];

struct GeometryVertex
{
  XrVector3f Position;
  XrVector3f Normal;
  XrVector3f Color;
  XrVector2f Texture;
  int32_t Index;
};
#endif

  uint32_t numModelsIdiciesStaticCountOf = sizeof(Geometry::gModelsIndicesStaticData) / sizeof(Geometry::gModelsIndicesStaticData[0] );
  Geometry::gModelsIndicesDynamicCountOf = numModelsIdiciesStaticCountOf + 3 * num_face;

  uint32_t numModelsVerticiesStaticCountOf = sizeof(Geometry::gModelsVerticesStaticData) / sizeof(Geometry::gModelsVerticesStaticData[0] );
  Geometry::gModelsVerticesDynamicCountOf = numModelsVerticiesStaticCountOf + attrib_vertices_size;

  Geometry::gModelsIndicesDynamicData = (uint32_t*)calloc(Geometry::gModelsIndicesDynamicCountOf, sizeof(uint32_t) );
  memcpy(Geometry::gModelsIndicesDynamicData, Geometry::gModelsIndicesStaticData, sizeof(Geometry::gModelsIndicesStaticData) );

  Geometry::gModelsVerticesDynamicData = (GeometryVertex*)calloc(Geometry::gModelsVerticesDynamicCountOf, sizeof(GeometryVertex) );
  memcpy(Geometry::gModelsVerticesDynamicData, Geometry::gModelsVerticesStaticData, sizeof(Geometry::gModelsVerticesStaticData) );

  //XrVector3f* normalData = (XrVector3f*)calloc(num_face, sizeof(XrVector3f) );

  Geometry::gModelsIndexFirst[256] = numModelsIdiciesStaticCountOf;
  Geometry::gModelsIndexCount[256] = 3 * num_face;

  tinyobj::real_t texture = 0.0;

  tinyobj::real_t color = 0.0;

  size_t index_offset_all_shapes = 0;

  float pxMin = 0.0;
  float pxMax = 0.0;

  float pyMin = 0.0;
  float pyMax = 0.0;

  float pzMin = 0.0;
  float pzMax = 0.0;

  float pxCen = 0.0;
  float pyCen = 0.0;
  float pzCen = 0.0;

  // Loop over shapes
  for(size_t s_index = 0; shapes_size > 0 && s_index < countof(object_shapes_index); s_index++)
  {
    size_t si = object_shapes_index[s_index];

    int32_t ti = object_with_texture[s_index];

    int32_t mi = object_with_material[s_index];

    // Loop over faces(polygon)
    size_t index_offset_per_shape = 0;
    for(size_t f = 0; f < shapes[si].mesh.num_face_vertices.size(); f++)
    {
      size_t fv = size_t(shapes[si].mesh.num_face_vertices[f] );

      if(fv != 3)
        Log::Write(Log::Level::Info, Fmt("fv!=3 %i\n", (int)fv) );

      // Loop over vertices in the face.
      for(size_t v = 0; v < fv; v++)
      {
        // access to vertex
        tinyobj::index_t idx = shapes[si].mesh.indices[index_offset_per_shape + v];

        tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
        tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
        tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

        if(OBJ_ROTATE)
        {
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.x = vy/*vx*/;
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y = vz/*vy*/;
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.z = vx/*vz*/;
        }
        else
        {
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.x = vx;
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y = vy;
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.z = vz;
        }

        if( !index_offset_all_shapes)
        {
          pxMin = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.x;
          pxMax = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.x;

          pyMin = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y;
          pyMax = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y;

          pzMin = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y;
          pzMax = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y;
        }
        else
        {
          if(Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.x < pxMin)
            pxMin = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.x;

          if(Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.x > pxMax)
            pxMax = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.x;

          if(Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y < pyMin)
            pyMin = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y;

          if(Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y > pyMax)
            pyMax = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.y;

          if(Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.z < pzMin)
            pzMin = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.z;

          if(Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.z > pzMax)
            pzMax = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Position.z;
        }

        // Check if `normal_index` is zero or positive. negative = no normal data
        if(idx.normal_index >= 0)
        {
          tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
          tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
          tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];

          if(OBJ_NORMAL_NEGATIVE)
          {
            nx = -nx;
            ny = -ny;
            nz = -nz;
          }

          if(OBJ_ROTATE)
          {
            Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Normal.x = ny;
            Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Normal.y = nz;
            Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Normal.z = nx;
          }
          else
          {
            Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Normal.x = nx;
            Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Normal.y = ny;
            Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Normal.z = nz;
          }
        }

        // Check if `texcoord_index` is zero or positive. negative = no texcoord data
        if(idx.texcoord_index >= 0 && ti >= 0)
        {
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Index = ti;

          tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
          tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];

          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Texture.x = tx;

          if(OBJ_IMAGE_FLIP_Y)
            Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Texture.y = 1.0 - ty;
          else
            Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Texture.y = ty;

          texture += tx;
          texture += ty;
        }
        else
        {
          //Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Index = -1;
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Index = 0;

          //Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Texture.x = -1.0;
          //Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Texture.y = -1.0;
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Texture.x = 0.0;
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Texture.y = 0.0;

          //Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.x = 1.0;
          //Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.y = 1.0;
          //Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.z = 1.0;
        }

        // Optional: vertex colors
        tinyobj::real_t red = attrib.colors[3 * size_t(idx.vertex_index) + 0];
        tinyobj::real_t green = attrib.colors[3 * size_t(idx.vertex_index) + 1];
        tinyobj::real_t blue  = attrib.colors[3 * size_t(idx.vertex_index) + 2];

        Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.x = red;
        Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.y = green;
        Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.z = blue;

        color += red;
        color += green;
        color += blue;

        if(mi >= 0)
        {
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.x = materials[mi].diffuse[0];
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.y = materials[mi].diffuse[1];
          Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + v/*idx.vertex_index*/].Color.z = materials[mi].diffuse[2];
        }

        Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf + v] = index_offset_all_shapes + v/*idx.vertex_index*/;
      }

#if 1
      // invert clockwise/counter-clockwise direction
      {
        uint32_t index0 = Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf];

        Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf] =
          Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf + 2];

        Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf + 2] = index0;
      }
#endif

#if 0
      // try out some kind of cell shading crap
      {
        uint32_t index0 = Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf];
        uint32_t index1 = Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf + 1];
        uint32_t index2 = Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf + 2];

        float u0 = (Geometry::gModelsVerticesDynamicData[index1].Texture.x - Geometry::gModelsVerticesDynamicData[index0].Texture.x) / 2.0 + Geometry::gModelsVerticesDynamicData[index0].Texture.x;

        float v0 = (Geometry::gModelsVerticesDynamicData[index1].Texture.y - Geometry::gModelsVerticesDynamicData[index0].Texture.y) / 2.0 + Geometry::gModelsVerticesDynamicData[index0].Texture.y;

        float u1 = (Geometry::gModelsVerticesDynamicData[index2].Texture.x - u0) / 2.0 + u0;

        float v1 = (Geometry::gModelsVerticesDynamicData[index2].Texture.y - v0) / 2.0 + v0;

        Geometry::gModelsVerticesDynamicData[index0].Texture.x = u1;
        Geometry::gModelsVerticesDynamicData[index0].Texture.y = v1;

        Geometry::gModelsVerticesDynamicData[index1].Texture.x = u1;
        Geometry::gModelsVerticesDynamicData[index1].Texture.y = v1;

        Geometry::gModelsVerticesDynamicData[index2].Texture.x = u1;
        Geometry::gModelsVerticesDynamicData[index2].Texture.y = v1;
      }
#endif

      index_offset_per_shape += fv;

      index_offset_all_shapes += fv;

      numModelsIdiciesStaticCountOf += 3;

      numModelsVerticiesStaticCountOf += 3;

      // per-face material
      shapes[si].mesh.material_ids[f];
    }
  }

  pxCen = (pxMin + pxMax) / 2.0;
  pyCen = (pyMin + pyMax) / 2.0;
  pzCen = (pzMin + pzMax) / 2.0;

  if(numModelsIdiciesStaticCountOf != Geometry::gModelsIndicesDynamicCountOf)
    Log::Write(Log::Level::Info, Fmt("numModelsIdiciesStaticCountOf blah\n") );

  numModelsIdiciesStaticCountOf = Geometry::gModelsIndicesDynamicCountOf - 3 * num_face;

  if(numModelsVerticiesStaticCountOf != Geometry::gModelsVerticesDynamicCountOf)
    Log::Write(Log::Level::Info, Fmt("numModelsVerticiesStaticCountOf blah\n") );

  numModelsVerticiesStaticCountOf = Geometry::gModelsVerticesDynamicCountOf - 3 * num_face;

  // if the color of all vertices are black, change to white
  if(fabs(color) <= 1E-5)
  {
    for(int index = numModelsVerticiesStaticCountOf; index < Geometry::gModelsVerticesDynamicCountOf; index++)
    {
      Geometry::gModelsVerticesDynamicData[index].Color.x = 1.0;
      Geometry::gModelsVerticesDynamicData[index].Color.y = 1.0;
      Geometry::gModelsVerticesDynamicData[index].Color.z = 1.0;
    }
  }

#if 0
  // set texture coordinates for all vertices before model to negative
  for(int index = 0; index < numModelsVerticiesStaticCountOf; index++)
  {
    Geometry::gModelsVerticesDynamicData[index].Texture.x = -1.0;
    Geometry::gModelsVerticesDynamicData[index].Texture.y = -1.0;
  }
#endif

#if 0
  // if the texture coordinates of all vertices is zero, change to negative
  if(fabs(texture) <= 1E-5)
  {
    for(int index = numModelsVerticiesStaticCountOf; index < Geometry::gModelsVerticesDynamicCountOf; index++)
    {
      Geometry::gModelsVerticesDynamicData[index].Texture.x = -1.0;
      Geometry::gModelsVerticesDynamicData[index].Texture.y = -1.0;
    }
  }
#endif

// center and scale
  for(int index = 0; index < 3 * num_face; index++)
  {
    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + index].Position.x -= pxCen;
    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + index].Position.y -= pyCen;
    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + index].Position.z -= pzCen;

    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + index].Position.x /= OBJ_SCALE;
    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + index].Position.y /= OBJ_SCALE;
    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + index].Position.z /= OBJ_SCALE;
  }

// recalculate normals
#if 1
  for(int index = 0; index < num_face; index++)
  {
    uint32_t vertexIndex0 = Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf + 3 * index];
    uint32_t vertexIndex1 = Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf + 3 * index + 1];
    uint32_t vertexIndex2 = Geometry::gModelsIndicesDynamicData[numModelsIdiciesStaticCountOf + 3 * index + 2];

    XrVector3f vertex0 = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + vertexIndex0].Position;
    XrVector3f vertex1 = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + vertexIndex1].Position;
    XrVector3f vertex2 = Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + vertexIndex2].Position;

    XrVector3f rhs = {vertex2.x - vertex1.x, vertex2.y - vertex1.y, vertex2.z - vertex1.z};
    XrVector3f_Blah_Normalize( &rhs);

    XrVector3f lhs = {vertex0.x - vertex1.x, vertex0.y - vertex1.y, vertex0.z - vertex1.z};
    XrVector3f_Blah_Normalize( &lhs);

    XrVector3f normal = {0.0, 0.0, 0.0};
    XrVector3f_Cross( &normal, &lhs, &rhs);

    //float area = XrVector3f_Length( &normal) / 2.0;

    XrVector3f_Blah_Normalize( &normal);

    //normalData[index].x += area * normal.x;
    //normalData[index].y += area * normal.y;
    //normalData[index].z += area * normal.z;

    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + 3 * index + 0].Normal = normal;
    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + 3 * index + 1].Normal = normal;
    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + 3 * index + 2].Normal = normal;
  }

#if 0
  for(int index = 0; index < attrib_vertices_size; index++)
  {
    XrVector3f_Blah_Normalize( &normalData[index] );

    Geometry::gModelsVerticesDynamicData[numModelsVerticiesStaticCountOf + index].Normal = normalData[index];
  }
#endif

#endif

  //free(normalData);
  //normalData = 0;
}

JNIEnv* gEnvironment = nullptr;

struct android_app* gApplication = nullptr;

void AnagShowHelpBlah()
{
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.graphicsPlugin OpenGLES | Vulkan");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.formFactor Hmd | Handheld");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.viewConfiguration Stereo | Mono");
  Log::Write(Log::Level::Info, "adb shell setprop debug.xr.blendMode Opaque | Additive | AlphaBlend");
}

bool AnagUpdateOptionsFromSystemProperties()
{
  // options.GraphicsPlugin
  // nop

  char value[PROP_VALUE_MAX] = {};

  if(__system_property_get("debug.xr.graphicsPlugin", value) != 0)
  {
    // options.GraphicsPlugin
    // nop
  }

  if(__system_property_get("debug.xr.formFactor", value) != 0)
  {
    // options.FormFactor
    // nop
  }

  if(__system_property_get("debug.xr.viewConfiguration", value) != 0)
  {
    // options.ViewConfiguration
    // nop
  }

  if(__system_property_get("debug.xr.blendMode", value) != 0)
  {
    // options.EnvironmentBlendMode
    // nop
  }

  // options
  // nop

  return true;
}

// todo

extern "C" {

struct AAssetManager;

/**
 * Given a Dalvik AssetManager object, obtain the corresponding native AAssetManager
 * object.  Note that the caller is responsible for obtaining and holding a VM reference
 * to the jobject to prevent its being garbage collected while the native object is
 * in use.
 */
AAssetManager* AAssetManager_fromJava(JNIEnv* environment, jobject assetManager);

AAsset* AAssetManager_open(AAssetManager* mgr, const char* filename, int mode);

}

unsigned char* AnagLoadFileBlah(const char* fileName, int* fileSize)
{
  AAssetManager* manager = gApplication->activity->assetManager;

  AAsset* asset = AAssetManager_open(manager, fileName, AASSET_MODE_UNKNOWN);

  if(NULL == asset)
  {
    Log::Write(Log::Level::Info, Fmt("BlahLoadFile fail %s\n", fileName) );
    return 0;
  }

  long size = AAsset_getLength(asset);

  unsigned char* buffer = (unsigned char*)calloc(size, sizeof(unsigned char) );

  AAsset_read(asset, buffer, size);

  AAsset_close(asset);

  Log::Write(Log::Level::Info, Fmt("BlahLoadFile yay %s %i\n", fileName, (int)size) );

  if(fileSize)
    *fileSize = (int)size;

  return buffer;
}

/**
 * Process the next main command.
 */
void anag_app_handle_cmd(struct android_app* app, int32_t cmd)
{
  AndroidAppState* appState = (AndroidAppState*)app->userData;

  switch(cmd)
  {

  // There is no APP_CMD_CREATE. The ANativeActivity creates the
  // application thread from onCreate(). The application thread
  // then calls android_main().
  case APP_CMD_START:
  {
    Log::Write(Log::Level::Info, "APP_CMD_START");
    Log::Write(Log::Level::Info, "anagOnStart()");
    break;
  }

  case APP_CMD_RESUME:
  {
    Log::Write(Log::Level::Info, "anagOnResume()");
    Log::Write(Log::Level::Info, "APP_CMD_RESUME");
    appState->Resumed = true;
    break;
  }

  case APP_CMD_PAUSE:
  {
    Log::Write(Log::Level::Info, "anagOnPause()");
    Log::Write(Log::Level::Info, "APP_CMD_PAUSE");
    appState->Resumed = false;
    break;
  }

  case APP_CMD_STOP:
  {
    Log::Write(Log::Level::Info, "anagOnStop()");
    Log::Write(Log::Level::Info, "APP_CMD_STOP");
    break;
  }

  case APP_CMD_DESTROY:
  {
    Log::Write(Log::Level::Info, "anagOnDestroy()");
    Log::Write(Log::Level::Info, "APP_CMD_DESTROY");
    appState->NativeWindow = NULL;
    break;
  }

  case APP_CMD_INIT_WINDOW:
  {
    Log::Write(Log::Level::Info, "surfaceCreated()");
    Log::Write(Log::Level::Info, "APP_CMD_INIT_WINDOW");
    appState->NativeWindow = app->window;
    break;
  }

  case APP_CMD_TERM_WINDOW:
  {
    Log::Write(Log::Level::Info, "surfaceDestroyed()");
    Log::Write(Log::Level::Info, "APP_CMD_TERM_WINDOW");
    appState->NativeWindow = NULL;
    break;
  }

  }
}

//struct XrInstanceCreateInfoAndroidKHR
//{
//  XrStructureType type;
//  const void* next;
//  void* applicationVM;
//  void* applicationActivity;
//};

XrInstanceCreateInfoAndroidKHR instanceCreateInfoAndroid {XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR, 0, 0, 0};

void anag_free_saved_state(struct android_app* app)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);

  if(app->savedState)
  {
    free(app->savedState);
    app->savedState = 0;

    app->savedStateSize = 0;
  }

  pthread_mutex_unlock( &app->mutex);
}

int8_t anag_android_app_read_cmd(struct android_app* app)
{
  int8_t cmd = 0;

  if( !app)
    return -1;

  if(read(app->msgread, &cmd, sizeof(cmd) ) != sizeof(cmd) )
  {
    ANAG_LOGE("No data on command pipe!");
    return -1;
  }

  if(cmd == APP_CMD_SAVE_STATE)
    anag_free_saved_state(app);

  return cmd;
}

void anag_print_cur_config(struct android_app* app)
{
  char lang[2] = {0};
  char country[2] = {0};

  if( !app)
    return;

  AConfiguration_getLanguage(app->config, lang);
  AConfiguration_getCountry(app->config, country);

  ANAG_LOGV("Config: mcc=%d mnc=%d lang=%c%c cnt=%c%c orien=%d touch=%d dens=%d "
    "keys=%d nav=%d keysHid=%d navHid=%d sdk=%d size=%d long=%d "
    "modetype=%d modenight=%d",
    AConfiguration_getMcc(app->config),
    AConfiguration_getMnc(app->config),
    lang[0], lang[1], country[0], country[1],
    AConfiguration_getOrientation(app->config),
    AConfiguration_getTouchscreen(app->config),
    AConfiguration_getDensity(app->config),
    AConfiguration_getKeyboard(app->config),
    AConfiguration_getNavigation(app->config),
    AConfiguration_getKeysHidden(app->config),
    AConfiguration_getNavHidden(app->config),
    AConfiguration_getSdkVersion(app->config),
    AConfiguration_getScreenSize(app->config),
    AConfiguration_getScreenLong(app->config),
    AConfiguration_getUiModeType(app->config),
    AConfiguration_getUiModeNight(app->config) );
}

void anag_android_app_pre_exec_cmd(struct android_app* app, int8_t cmd)
{
  switch(cmd)
  {

  case APP_CMD_INPUT_CHANGED:
  {
    ANAG_LOGV("APP_CMD_INPUT_CHANGED");

    if( !app)
      break;

    pthread_mutex_lock( &app->mutex);

    if(app->inputQueue)
      AInputQueue_detachLooper(app->inputQueue);

    app->inputQueue = app->pendingInputQueue;

    if(app->inputQueue)
    {
      ANAG_LOGV("Attaching input queue to looper");

      AInputQueue_attachLooper(app->inputQueue, app->looper, LOOPER_ID_INPUT, 0, &app->inputPollSource);
    }

    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_INIT_WINDOW:
  {
    ANAG_LOGV("APP_CMD_INIT_WINDOW");

    if( !app)
      break;

    pthread_mutex_lock( &app->mutex);

    app->window = app->pendingWindow;

    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_TERM_WINDOW:
  {
    ANAG_LOGV("APP_CMD_TERM_WINDOW");

    if( !app)
      break;

    pthread_cond_broadcast( &app->cond);
  }
  break;

  case APP_CMD_RESUME:
  case APP_CMD_START:
  case APP_CMD_PAUSE:
  case APP_CMD_STOP:
  {
    ANAG_LOGV("activityState %d", cmd);

    if( !app)
      break;

    pthread_mutex_lock( &app->mutex);

    app->activityState = cmd;

    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_CONFIG_CHANGED:
  {
    ANAG_LOGV("APP_CMD_CONFIG_CHANGED");

    if( !app)
      break;

    if(app->activity)
      AConfiguration_fromAssetManager(app->config, app->activity->assetManager);

    anag_print_cur_config(app);
  }
  break;

  case APP_CMD_DESTROY:
  {
    ANAG_LOGV("APP_CMD_DESTROY");

    if( !app)
      break;

    app->destroyRequested = 1;
  }
  break;

  }
}

void anag_android_app_post_exec_cmd(struct android_app* app, int8_t cmd)
{
  switch(cmd)
  {

  case APP_CMD_TERM_WINDOW:
  {
    ANAG_LOGV("APP_CMD_TERM_WINDOW");

    if( !app)
      return;

    pthread_mutex_lock( &app->mutex);
    app->window = 0;
    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_SAVE_STATE:
  {
    ANAG_LOGV("APP_CMD_SAVE_STATE");

    if( !app)
      return;

    pthread_mutex_lock( &app->mutex);
    app->stateSaved = 1;
    pthread_cond_broadcast( &app->cond);
    pthread_mutex_unlock( &app->mutex);
  }
  break;

  case APP_CMD_RESUME:
  {
    if( !app)
      return;

    anag_free_saved_state(app);
  }
  break;

  }
}

//void anag_app_dummy()
//{
//}

void anag_android_app_destroy(struct android_app* app)
{
  ANAG_LOGV("anag_android_app_destroy!");

  if( !app)
    return;

  anag_free_saved_state(app);
  pthread_mutex_lock( &app->mutex);

  if(app->inputQueue)
    AInputQueue_detachLooper(app->inputQueue);

  AConfiguration_delete(app->config);
  app->destroyed = 1;
  pthread_cond_broadcast( &app->cond);
  pthread_mutex_unlock( &app->mutex);
}

void anag_process_input(struct android_app* app, struct android_poll_source* source)
{
  AInputEvent* event = 0;

  if( !app)
    return;

  while(AInputQueue_getEvent(app->inputQueue, &event) >= 0)
  {
    int32_t handled = 0;

    ANAG_LOGV("New input event: type=%d", AInputEvent_getType(event) );

    if(AInputQueue_preDispatchEvent(app->inputQueue, event) )
      continue;

    if(app->onInputEvent)
      handled = app->onInputEvent(app, event);

    AInputQueue_finishEvent(app->inputQueue, event, handled);
  }
}

void anag_process_cmd(struct android_app* app, struct android_poll_source* source)
{
  int8_t cmd = 0;

  if( !app)
    return;

  cmd = anag_android_app_read_cmd(app);
  anag_android_app_pre_exec_cmd(app, cmd);

  if(app->onAppCmd)
    app->onAppCmd(app, cmd);

  anag_android_app_post_exec_cmd(app, cmd);
}

void* anag_android_app_entry(void* param)
{
  struct android_app* app = 0;
  ALooper* looper = 0;

  app = (struct android_app*)param;

  if( !app)
    return 0;

  gApplication = app;

  app->config = AConfiguration_new();
  AConfiguration_fromAssetManager(app->config, app->activity->assetManager);

  anag_print_cur_config(app);

  app->cmdPollSource.id = LOOPER_ID_MAIN;
  app->cmdPollSource.app = app;
  app->cmdPollSource.process = anag_process_cmd;
  app->inputPollSource.id = LOOPER_ID_INPUT;
  app->inputPollSource.app = app;
  app->inputPollSource.process = anag_process_input;

  looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
  ALooper_addFd(looper, app->msgread, LOOPER_ID_MAIN, ALOOPER_EVENT_INPUT, 0, &app->cmdPollSource);

  app->looper = looper;

  pthread_mutex_lock( &app->mutex);
  app->running = 1;
  pthread_cond_broadcast( &app->cond);
  pthread_mutex_unlock( &app->mutex);

try
{
  app->activity->vm->AttachCurrentThread( &gEnvironment, nullptr);

  AndroidAppState appState = {};

  app->userData = &appState;
  app->onAppCmd = anag_app_handle_cmd;

  AnagUpdateOptionsFromSystemProperties();

  instanceCreateInfoAndroid.applicationVM = app->activity->vm;
  instanceCreateInfoAndroid.applicationActivity = app->activity->clazz;

  bool requestRestart = false;
  bool exitRenderLoop = false;

  // dlsym
  //   xrGetInstanceProcAddr

  // xrGetInstanceProcAddr
  //   xrInitializeLoaderKHR
  //   xrEnumerateInstanceExtensionProperties
  //   xrEnumerateApiLayerProperties
  //   xrCreateInstance

  if(InitOpenXr1() )
    Log::Write(Log::Level::Verbose, "xr 1");

  if(InitVulkan() )
    Log::Write(Log::Level::Verbose, "vk 1");

  // Create graphics API implementation.
  _operator_assign(gVulkanGraphicsPluginStdArray_float_4_clearColor, gOptions_BackgroundClearColor);

  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.type = XR_TYPE_GRAPHICS_BINDING_VULKAN2_KHR;

  // Initialize the OpenXR program.
  // nop

  // Initialize the loader for this platform

  //XrResult result = XR_ERROR_VALIDATION_FAILURE;

  {
    XrLoaderInitInfoAndroidKHR loaderInitInfoAndroid = {XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR};

    loaderInitInfoAndroid.applicationVM = app->activity->vm;
    loaderInitInfoAndroid.applicationContext = app->activity->clazz;

    if(tableXr.InitializeLoaderKHR)
      tableXr.InitializeLoaderKHR( (const XrLoaderInitInfoBaseHeaderKHR*) &loaderInitInfoAndroid);
  }

  {
    // Write out extension properties for a given layer.

    {
      const char* layerName = nullptr;
      int indent = 0;

      uint32_t instanceExtensionCount = 0;

      if(tableXr.EnumerateInstanceExtensionProperties)
      {
        CHECK_XRCMD_CHECK(tableXr.EnumerateInstanceExtensionProperties(
          layerName,
          0,
          &instanceExtensionCount,
          nullptr
        ) );
      }

      std::vector<XrExtensionProperties> extensions(
        instanceExtensionCount,
        {XR_TYPE_EXTENSION_PROPERTIES}
      );

      if(tableXr.EnumerateInstanceExtensionProperties)
      {
        CHECK_XRCMD_CHECK(tableXr.EnumerateInstanceExtensionProperties(
          layerName,
          (uint32_t)extensions.size(),
          &instanceExtensionCount,
          extensions.data()
        ) );
      }

      const std::string indentStr(indent, ' ');

      Log::Write(Log::Level::Verbose, Fmt("%sAvailable Extensions: (%d)", indentStr.c_str(), instanceExtensionCount) );

      for(const XrExtensionProperties& extension : extensions)
      {
        Log::Write(
          Log::Level::Verbose,
          Fmt("%s  Name=%s SpecVersion=%d", indentStr.c_str(), extension.extensionName, extension.extensionVersion)
        );
      }
    }

    // Log non-layer extensions (layerName==nullptr).

#if 0
    const auto logExtensions = [](const char* layerName, int indent = 0 )

    //logExtensions(nullptr);

    // Log layers and any of their extensions.
    {
      uint32_t layerCount = 0;

      if(tableXr.EnumerateApiLayerProperties)
        CHECK_XRCMD_CHECK(tableXr.EnumerateApiLayerProperties(0, &layerCount, nullptr) );

      std::vector<XrApiLayerProperties> layers(layerCount, {XR_TYPE_API_LAYER_PROPERTIES} );

      if(tableXr.EnumerateApiLayerProperties)
        CHECK_XRCMD_CHECK(tableXr.EnumerateApiLayerProperties( (uint32_t)layers.size(), &layerCount, layers.data() ) );

      Log::Write(Log::Level::Info, Fmt("Available Layers: (%d)", layerCount) );

      for(const XrApiLayerProperties& layer : layers)
      {
        Log::Write(
          Log::Level::Verbose,
          Fmt(
            "  Name=%s SpecVersion=%s LayerVersion=%d Description=%s",
            layer.layerName,
            GetXrVersionString(layer.specVersion).c_str(),
            layer.layerVersion,
            layer.description
          )
        );

        logExtensions(layer.layerName, 4);
      }
    }
#endif
  }

  CHECK_CHECK(gXrInstance == XR_NULL_HANDLE);

  {
    // Create union of extensions required by platform and graphics plugins.
    std::vector<const char*> extensions;

    // Transform platform and graphics extension std::strings to C strings.

    const std::vector<std::string> platformExtensions = {XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME};

    std::transform(platformExtensions.begin(), platformExtensions.end(), std::back_inserter(extensions),
    [](const std::string& ext)
    {
      return ext.c_str();
    } );

    const std::vector<std::string> graphicsExtensions = {XR_KHR_VULKAN_ENABLE2_EXTENSION_NAME};

    std::transform(graphicsExtensions.begin(), graphicsExtensions.end(), std::back_inserter(extensions),
    [](const std::string& ext)
    {
      return ext.c_str();
    } );

    XrInstanceCreateInfo createInfo {XR_TYPE_INSTANCE_CREATE_INFO};
    createInfo.next = &instanceCreateInfoAndroid;

    extensions.push_back("XR_EXT_active_action_set_priority");
    extensions.push_back("XR_EXT_composition_layer_inverted_alpha");
    extensions.push_back("XR_EXT_debug_utils");
    extensions.push_back("XR_EXT_hand_interaction");
    extensions.push_back("XR_EXT_hand_joints_motion_range");
    extensions.push_back("XR_EXT_hand_tracking");
    extensions.push_back("XR_EXT_hand_tracking_data_source");
    extensions.push_back("XR_EXT_local_floor");
    extensions.push_back("XR_EXT_performance_settings");
    extensions.push_back("XR_EXT_user_presence");
    extensions.push_back("XR_FB_android_surface_swapchain_create");
    extensions.push_back("XR_FB_body_tracking");
    extensions.push_back("XR_FB_color_space");
    extensions.push_back("XR_FB_common_events");
    extensions.push_back("XR_FB_composition_layer_alpha_blend");
    extensions.push_back("XR_FB_composition_layer_depth_test");
    extensions.push_back("XR_FB_composition_layer_image_layout");
    extensions.push_back("XR_FB_composition_layer_secure_content");
    extensions.push_back("XR_FB_composition_layer_settings");
    extensions.push_back("XR_FB_display_refresh_rate");
    extensions.push_back("XR_FB_face_tracking2");
    extensions.push_back("XR_FB_foveation");
    extensions.push_back("XR_FB_foveation_configuration");
    extensions.push_back("XR_FB_foveation_vulkan");
    extensions.push_back("XR_FB_hand_tracking_aim");
    extensions.push_back("XR_FB_hand_tracking_capsules");
    extensions.push_back("XR_FB_hand_tracking_mesh");
    extensions.push_back("XR_FB_haptic_amplitude_envelope");
    extensions.push_back("XR_FB_haptic_pcm");
    extensions.push_back("XR_FB_passthrough");
    extensions.push_back("XR_FB_scene");
    extensions.push_back("XR_FB_scene_capture");
    extensions.push_back("XR_FB_space_warp");
    extensions.push_back("XR_FB_spatial_entity");
    extensions.push_back("XR_FB_spatial_entity_container");
    extensions.push_back("XR_FB_spatial_entity_query");
    extensions.push_back("XR_FB_spatial_entity_sharing");
    extensions.push_back("XR_FB_spatial_entity_storage");
    extensions.push_back("XR_FB_spatial_entity_storage_batch");
    extensions.push_back("XR_FB_spatial_entity_user");
    extensions.push_back("XR_FB_swapchain_update_state");
    extensions.push_back("XR_FB_swapchain_update_state_android_surface");
    extensions.push_back("XR_FB_swapchain_update_state_opengl_es");
    extensions.push_back("XR_FB_swapchain_update_state_vulkan");
    extensions.push_back("XR_FB_touch_controller_pro");
    extensions.push_back("XR_FB_touch_controller_proximity");
    extensions.push_back("XR_FB_triangle_mesh");
    extensions.push_back("XR_KHR_android_create_instance");
    extensions.push_back("XR_KHR_android_surface_swapchain");
    extensions.push_back("XR_KHR_android_thread_settings");
    extensions.push_back("XR_KHR_composition_layer_color_scale_bias");
    extensions.push_back("XR_KHR_composition_layer_cube");
    extensions.push_back("XR_KHR_composition_layer_cylinder");
    extensions.push_back("XR_KHR_composition_layer_depth");
    extensions.push_back("XR_KHR_composition_layer_equirect2");
    extensions.push_back("XR_KHR_convert_timespec_time");
    extensions.push_back("XR_KHR_opengl_es_enable");
    extensions.push_back("XR_KHR_visibility_mask");
    extensions.push_back("XR_KHR_vulkan_enable");
    extensions.push_back("XR_KHR_vulkan_enable2");
    extensions.push_back("XR_LOGITECH_mx_ink_stylus_interaction");
    extensions.push_back("XR_META_automatic_layer_filter");
    extensions.push_back("XR_META_body_tracking_calibration");
    extensions.push_back("XR_META_body_tracking_fidelity");
    extensions.push_back("XR_META_body_tracking_full_body");
    extensions.push_back("XR_META_boundary_visibility");
    extensions.push_back("XR_META_colocation_discovery");
    extensions.push_back("XR_META_detached_controllers");
    extensions.push_back("XR_META_dynamic_object_keyboard");
    extensions.push_back("XR_META_dynamic_object_tracker");
    extensions.push_back("XR_META_environment_depth");
    extensions.push_back("XR_META_feature_fidelity");
    extensions.push_back("XR_META_hand_tracking_microgestures");
    extensions.push_back("XR_META_hand_tracking_wide_motion_mode");
    extensions.push_back("XR_META_headset_id");
    extensions.push_back("XR_META_passthrough_color_lut");
    extensions.push_back("XR_META_passthrough_layer_resumed_event");
    extensions.push_back("XR_META_passthrough_preferences");
    extensions.push_back("XR_META_performance_metrics");
    extensions.push_back("XR_META_recommended_layer_resolution");
    extensions.push_back("XR_META_simultaneous_hands_and_controllers");
    extensions.push_back("XR_META_spatial_entity_discovery");
    extensions.push_back("XR_META_spatial_entity_group_sharing");
    extensions.push_back("XR_META_spatial_entity_mesh");
    extensions.push_back("XR_META_spatial_entity_persistence");
    extensions.push_back("XR_META_spatial_entity_sharing");
    extensions.push_back("XR_META_touch_controller_plus");
    extensions.push_back("XR_META_virtual_keyboard");
    extensions.push_back("XR_META_vulkan_swapchain_create_info");
    extensions.push_back("XR_MSFT_hand_interaction");
    extensions.push_back("XR_OCULUS_common_reference_spaces");

    createInfo.enabledExtensionCount = (uint32_t)extensions.size();
    createInfo.enabledExtensionNames = extensions.data();

    strcpy(createInfo.applicationInfo.applicationName, "HelloXR");

    createInfo.applicationInfo.apiVersion = 281474976710656/*XR_MAKE_VERSION(1, 1, 43)*/;

    for(int index = 0; index < extensions.size(); index++)
      Log::Write(Log::Level::Info, Fmt("blah %i %s", index, extensions[index] ) );

    if(tableXr.CreateInstance)
      CHECK_XRCMD_CHECK(tableXr.CreateInstance( &createInfo, &gXrInstance) );

    if(InitOpenXr2() )
      Log::Write(Log::Level::Verbose, "xr 2");
  }

  CHECK_CHECK(gXrInstance != XR_NULL_HANDLE);

  XrInstanceProperties instanceProperties {XR_TYPE_INSTANCE_PROPERTIES};

  if(tableXr.GetInstanceProperties)
    CHECK_XRCMD_CHECK(tableXr.GetInstanceProperties(gXrInstance, &instanceProperties) );

  Log::Write(
    Log::Level::Info,
    Fmt(
      "Instance RuntimeName=%s RuntimeVersion=%s",
      instanceProperties.runtimeName,
      GetXrVersionString(instanceProperties.runtimeVersion).c_str()
    )
  );

  CHECK_CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK_CHECK(gXrSystemId == XR_NULL_SYSTEM_ID);

  XrSystemGetInfo systemInfo {XR_TYPE_SYSTEM_GET_INFO};
  systemInfo.formFactor = gOptions_XrFormFactor;

  if(tableXr.GetSystem)
    CHECK_XRCMD_CHECK(tableXr.GetSystem(gXrInstance, &systemInfo, &gXrSystemId) );

  Log::Write(
    Log::Level::Verbose,
    Fmt("Using system %d for form factor %s", gXrSystemId, to_string(gOptions_XrFormFactor) )
  );

  CHECK_CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK_CHECK(gXrSystemId != XR_NULL_SYSTEM_ID);

  XrEnvironmentBlendMode environmentBlendMode = gOptions_XrEnvironmentBlendMode;

  uint32_t countBlendModes = 0;
  bool found = false;

  if(tableXr.EnumerateEnvironmentBlendModes)
  {
    CHECK_XRCMD_CHECK(tableXr.EnumerateEnvironmentBlendModes(
      gXrInstance,
      gXrSystemId,
      gOptions_XrViewConfigurationType,
      0,
      &countBlendModes,
      nullptr
    ) );
  }

  CHECK_CHECK(countBlendModes > 0);

  std::vector<XrEnvironmentBlendMode> blendModes(countBlendModes);

  if(tableXr.EnumerateEnvironmentBlendModes)
  {
    CHECK_XRCMD_CHECK(tableXr.EnumerateEnvironmentBlendModes(
      gXrInstance,
      gXrSystemId,
      gOptions_XrViewConfigurationType,
      countBlendModes,
      &countBlendModes,
      blendModes.data()
    ) );
  }

  for(const auto& blendMode : blendModes)
  {
    if(gOpenXrProgramStdSet_XrEnvironmentBlendMode.count(blendMode) )
    {
      environmentBlendMode = blendMode;
      found = true;
      break;
    }
  }

  if( !found)
    THROW_CHECK("No acceptable blend mode returned from the tableXr.EnumerateEnvironmentBlendModes");

  Options_SetEnvironmentBlendMode(environmentBlendMode);

  AnagUpdateOptionsFromSystemProperties();

  _operator_assign(gVulkanGraphicsPluginStdArray_float_4_clearColor, gOptions_BackgroundClearColor);

  CHECK_CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK_CHECK(gXrSystemId != XR_NULL_SYSTEM_ID);

  uint32_t viewConfigurationTypeCount = 0;

  if(tableXr.EnumerateViewConfigurations)
  {
    CHECK_XRCMD_CHECK(tableXr.EnumerateViewConfigurations(
      gXrInstance,
      gXrSystemId,
      0,
      &viewConfigurationTypeCount,
      nullptr
    ) );
  }

  std::vector<XrViewConfigurationType> viewConfigurationTypes(viewConfigurationTypeCount);

  if(tableXr.EnumerateViewConfigurations)
  {
    CHECK_XRCMD_CHECK(tableXr.EnumerateViewConfigurations(
      gXrInstance,
      gXrSystemId,
      viewConfigurationTypeCount,
      &viewConfigurationTypeCount,
      viewConfigurationTypes.data()
    ) );
  }

  CHECK_CHECK( (uint32_t)viewConfigurationTypes.size() == viewConfigurationTypeCount);

  Log::Write(Log::Level::Info, Fmt("Available View Configuration Types: (%d)", viewConfigurationTypeCount) );

  for(XrViewConfigurationType viewConfigurationType : viewConfigurationTypes)
  {
    Log::Write(
      Log::Level::Verbose,
      Fmt(
        "View Configuration Type: %s %s",
        to_string(viewConfigurationType),
        viewConfigurationType == gOptions_XrViewConfigurationType ? "(Selected)" : ""
      )
    );

    XrViewConfigurationProperties viewConfigProperties {XR_TYPE_VIEW_CONFIGURATION_PROPERTIES};

    if(tableXr.GetViewConfigurationProperties)
    {
      CHECK_XRCMD_CHECK(tableXr.GetViewConfigurationProperties(
        gXrInstance,
        gXrSystemId,
        viewConfigurationType,
        &viewConfigProperties
      ) );
    }

    Log::Write(
      Log::Level::Verbose,
      Fmt("View configuration FovMutable=%s", viewConfigProperties.fovMutable == XR_TRUE ? "True" : "False")
    );

    uint32_t viewCount = 0;

    if(tableXr.EnumerateViewConfigurationViews)
    {
      CHECK_XRCMD_CHECK(tableXr.EnumerateViewConfigurationViews(
        gXrInstance,
        gXrSystemId,
        viewConfigurationType,
        0,
        &viewCount,
        nullptr
      ) );
    }

    if(viewCount > 0)
    {
      std::vector<XrViewConfigurationView> views(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW} );

      if(tableXr.EnumerateViewConfigurationViews)
      {
        CHECK_XRCMD_CHECK(tableXr.EnumerateViewConfigurationViews(
          gXrInstance,
          gXrSystemId,
          viewConfigurationType,
          viewCount,
          &viewCount,
          views.data()
        ) );
      }

      for(uint32_t i = 0; i < views.size(); i++)
      {
        const XrViewConfigurationView& view = views[i];

        Log::Write(
          Log::Level::Verbose,
          Fmt(
            "View [%d]: Recommended Width=%d Height=%d SampleCount=%d",
            i,
            view.recommendedImageRectWidth,
            view.recommendedImageRectHeight,
            view.recommendedSwapchainSampleCount
          )
        );

        Log::Write(
          Log::Level::Verbose,
          Fmt(
            "View [%d]: Maximum Width=%d Height=%d SampleCount=%d",
            i,
            view.maxImageRectWidth,
            view.maxImageRectHeight,
            view.maxSwapchainSampleCount
          )
        );
      }
    }
    else
    {
      Log::Write(Log::Level::Error, Fmt("Empty view configuration type") );
    }

    CHECK_CHECK(gXrInstance != XR_NULL_HANDLE);
    CHECK_CHECK(gXrSystemId != 0);

    uint32_t count = 0;

    if(tableXr.EnumerateEnvironmentBlendModes)
    {
      CHECK_XRCMD_CHECK(tableXr.EnumerateEnvironmentBlendModes(
        gXrInstance,
        gXrSystemId,
        viewConfigurationType,
        0,
        &count,
        nullptr
      ) );
    }

    CHECK_CHECK(count > 0);

    Log::Write(
      Log::Level::Info,
      Fmt("Available Environment Blend Mode count : (%d)", count)
    );

    std::vector<XrEnvironmentBlendMode> blendModes(count);

    if(tableXr.EnumerateEnvironmentBlendModes)
    {
      CHECK_XRCMD_CHECK(tableXr.EnumerateEnvironmentBlendModes(
        gXrInstance,
        gXrSystemId,
        viewConfigurationType,
        count,
        &count,
        blendModes.data()
      ) );
    }

    bool blendModeFound = false;

    for(XrEnvironmentBlendMode mode : blendModes)
    {
      const bool blendModeMatch = (mode == gOptions_XrEnvironmentBlendMode);

      Log::Write(
        Log::Level::Info,
        Fmt(
          "Environment Blend Mode (%s) : %s",
          to_string(mode),
          blendModeMatch ? "(Selected)" : ""
        )
      );

      blendModeFound |= blendModeMatch;
    }

    CHECK_CHECK(blendModeFound);
  }

  // Create the Vulkan device for the adapter associated with the system.
  // Extension function must be loaded by name
  XrGraphicsRequirementsVulkan2KHR graphicsRequirements {XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN2_KHR};

  // CHECK_XRCMD_CHECK(VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(
  //   gXrInstance,
  //   gXrSystemId,
  //   &graphicsRequirements)
  // );
  //
  // XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsRequirements2KHR(
  //   XrInstance instance,
  //   XrSystemId systemId,
  //   XrGraphicsRequirementsVulkan2KHR* graphicsRequirements
  // )
  {
    XrResult resultGraphicsRequirements = XR_ERROR_VALIDATION_FAILURE;

    if(tableXr.GetVulkanGraphicsRequirements2KHR)
    {
      resultGraphicsRequirements = tableXr.GetVulkanGraphicsRequirements2KHR(
        gXrInstance,
        gXrSystemId,
        &graphicsRequirements
      );
    }

    CHECK_XRCMD_CHECK(resultGraphicsRequirements);
  }

  VkResult err = VK_ERROR_OUT_OF_HOST_MEMORY;

  std::vector<const char*> layers;

#if !defined(NDEBUG)
  char* const validationLayerName = nullptr;
  //const char* const validationLayerName = VulkanGraphicsPlugin_VulkanGraphicsPluginGetValidationLayerName();
  //const char* VulkanGraphicsPlugin_VulkanGraphicsPluginGetValidationLayerName()
  {
    uint32_t layerCount = 0;

    if(tableVk.EnumerateInstanceLayerProperties)
      tableVk.EnumerateInstanceLayerProperties( &layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);

    if(tableVk.EnumerateInstanceLayerProperties)
      tableVk.EnumerateInstanceLayerProperties( &layerCount, availableLayers.data() );

    std::vector<const char*> validationLayerNames;
    validationLayerNames.push_back("VK_LAYER_KHRONOS_validation");
    validationLayerNames.push_back("VK_LAYER_LUNARG_standard_validation");

    bool continueForLoop = true;

    // Enable only one validation layer from the list above. Prefer KHRONOS.
    for(auto& validationLayerName : validationLayerNames)
    {
      for(const auto& layerProperties : availableLayers)
      {
        if(0 == strcmp(validationLayerName, layerProperties.layerName) )
        {
          validationLayerName = validationLayerName;
          continueForLoop = false;
        }

        if( !continueForLoop)
          break;
      }

      if( !continueForLoop)
        break;
    }
  }

  if(validationLayerName)
    layers.push_back(validationLayerName);
  else
    Log::Write(Log::Level::Warning, "No validation layers found in the system, skipping");
#endif

  std::vector<const char*> extensions;

  {
    uint32_t extensionCount = 0;

    if(tableVk.EnumerateInstanceExtensionProperties)
      CHECK_VULKANCMD(tableVk.EnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr) );

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);

    if(tableVk.EnumerateInstanceExtensionProperties)
    {
      CHECK_VULKANCMD(tableVk.EnumerateInstanceExtensionProperties(
        nullptr,
        &extensionCount,
        availableExtensions.data()
      ) );
    }

    const auto b = availableExtensions.begin();
    const auto e = availableExtensions.end();

    auto isExtSupported = [&](const char* extName) -> bool
    {
      auto it = std::find_if(b, e, [&](const VkExtensionProperties& properties)
      {
        return (0 == strcmp(extName, properties.extensionName) );
      } );

      return (it != e);
    };

    extensions.push_back("VK_EXT_debug_report");
    extensions.push_back("VK_EXT_debug_utils");
    extensions.push_back("VK_EXT_swapchain_colorspace");
    extensions.push_back("VK_KHR_android_surface");
    extensions.push_back("VK_KHR_device_group_creation");
    extensions.push_back("VK_KHR_external_fence_capabilities");
    extensions.push_back("VK_KHR_external_memory_capabilities");
    extensions.push_back("VK_KHR_external_semaphore_capabilities");
    extensions.push_back("VK_KHR_get_physical_device_properties2");
    extensions.push_back("VK_KHR_get_surface_capabilities2");
    extensions.push_back("VK_KHR_surface");

    // todo add back VK_EXT_debug_report code for compatibility with older systems? (Android)
  }

  VkDebugUtilsMessengerCreateInfoEXT debugInfo {VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};

  debugInfo.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;

#if !defined(NDEBUG)
  debugInfo.messageSeverity |=
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
#endif

  debugInfo.messageType =
    VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  debugInfo.pfnUserCallback = VulkanGraphicsPlugin_debugMessageThunk;
  debugInfo.pUserData = 0;

  VkApplicationInfo appInfo {VK_STRUCTURE_TYPE_APPLICATION_INFO};

  appInfo.pApplicationName = "helloxr";
  appInfo.applicationVersion = 1;
  appInfo.pEngineName = "helloxr";
  appInfo.engineVersion = 1;

  appInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 3, 275);

  VkInstanceCreateInfo instInfo {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};

  instInfo.pNext = &debugInfo;
  instInfo.pApplicationInfo = &appInfo;
  instInfo.enabledLayerCount = (uint32_t)layers.size();
  instInfo.ppEnabledLayerNames = layers.empty() ? nullptr : layers.data();
  instInfo.enabledExtensionCount = (uint32_t)extensions.size();
  instInfo.ppEnabledExtensionNames = extensions.empty() ? nullptr : extensions.data();

  {
    XrVulkanInstanceCreateInfoKHR createInfo {XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR};

    createInfo.systemId = gXrSystemId;

    createInfo.pfnGetInstanceProcAddr = tableVk.GetInstanceProcAddr;

    createInfo.vulkanCreateInfo = &instInfo;
    createInfo.vulkanAllocator = nullptr;

    // CHECK_XRCMD_CHECK(VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanInstanceKHR(
    //   gXrInstance,
    //   &createInfo,
    //   &gVkInstance,
    //   &err
    // ) );
    //
    // CHECK_VULKANCMD(err);
    //
    // XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanInstanceKHR(
    //   XrInstance instance,
    //   const XrVulkanInstanceCreateInfoKHR* createInfo,
    //   VkInstance* vulkanInstance,
    //   VkResult* vulkanResult
    // )
    {
      XrResult result = XR_ERROR_VALIDATION_FAILURE;

      if(tableXr.CreateVulkanInstanceKHR)
        result = tableXr.CreateVulkanInstanceKHR(gXrInstance, &createInfo, &gVkInstance, &err);

      CHECK_XRCMD_CHECK(result);
      CHECK_VULKANCMD(err);
    }
  }

  {
    // typedef VkResult (VKAPI_PTR *PFN_vkEnumerateInstanceExtensionProperties)(
    //   const char* pLayerName,
    //   uint32_t* pPropertyCount,
    //   VkExtensionProperties* pProperties)

    //const auto logExtensions = [](const char* layerName, int indent = 0 )
    {
      const char* layerName = nullptr;
      int indent = 0;

      uint32_t instanceExtensionCount = 0;

      if(tableVk.EnumerateInstanceExtensionProperties)
        CHECK_VULKANCMD(tableVk.EnumerateInstanceExtensionProperties(layerName, &instanceExtensionCount, nullptr) );

#if 0
struct XrExtensionProperties
{
  XrStructureType type;
  void* XR_MAY_ALIAS next;
  char extensionName[XR_MAX_EXTENSION_NAME_SIZE];
  uint32_t extensionVersion;

};

struct VkExtensionProperties
{
  char extensionName[VK_MAX_EXTENSION_NAME_SIZE];
  uint32_t specVersion;

};
#endif

      //std::vector<XrExtensionProperties> extensions(instanceExtensionCount, {XR_TYPE_EXTENSION_PROPERTIES} );
      std::vector<VkExtensionProperties> extensions(instanceExtensionCount,
      {
        {0},
        0
      } );

      if(tableVk.EnumerateInstanceExtensionProperties)
      {
        CHECK_VULKANCMD(tableVk.EnumerateInstanceExtensionProperties(
          layerName,
          &instanceExtensionCount,
          extensions.data()
        ) );
      }

      const std::string indentStr(indent, ' ');

      Log::Write(Log::Level::Verbose, Fmt("%sAvailable Extensions: (%d)", indentStr.c_str(), instanceExtensionCount) );

      for(const VkExtensionProperties& extension : extensions)
      {
        Log::Write(
          Log::Level::Verbose,
          Fmt("%s  Name=%s SpecVersion=%d", indentStr.c_str(), extension.extensionName, extension.specVersion)
        );
      }
    };
  }

  if(tableVk.GetInstanceProcAddr)
  {
    gVulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT =
      (PFN_vkCreateDebugUtilsMessengerEXT)tableVk.GetInstanceProcAddr(gVkInstance, "vkCreateDebugUtilsMessengerEXT");
  }

  if(gVulkanGraphicsPluginVkCreateDebugUtilsMessengerEXT != nullptr && tableVk.CreateDebugUtilsMessengerEXT)
  {
    CHECK_VULKANCMD(tableVk.CreateDebugUtilsMessengerEXT(
      gVkInstance,
      &debugInfo,
      nullptr,
      &gVulkanGraphicsPluginVkDebugUtilsMessenger)
    );
  }

  {
    XrVulkanGraphicsDeviceGetInfoKHR deviceGetInfo {XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR};

    deviceGetInfo.systemId = gXrSystemId;
    deviceGetInfo.vulkanInstance = gVkInstance;

    // CHECK_XRCMD_CHECK(VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(
    //   gXrInstance,
    //   &deviceGetInfo,
    //   &gVkPhysicalDevice
    // ) );
    //
    // XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginGetVulkanGraphicsDevice2KHR(
    //   XrInstance instance,
    //   const XrVulkanGraphicsDeviceGetInfoKHR* getInfo,
    //   VkPhysicalDevice* vulkanPhysicalDevice
    // )
    {
      XrResult result = XR_ERROR_VALIDATION_FAILURE;

      if(tableXr.GetVulkanGraphicsDevice2KHR)
        result = tableXr.GetVulkanGraphicsDevice2KHR(gXrInstance, &deviceGetInfo, &gVkPhysicalDevice);

      CHECK_XRCMD_CHECK(result);
    }
  }

  VkDeviceQueueCreateInfo queueInfo {VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO};

  float queuePriorities = 0;
  queueInfo.queueCount = 1;
  queueInfo.pQueuePriorities = &queuePriorities;

  uint32_t queueFamilyCount = 0;

  if(tableVk.GetPhysicalDeviceQueueFamilyProperties)
    tableVk.GetPhysicalDeviceQueueFamilyProperties(gVkPhysicalDevice, &queueFamilyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilyProps(queueFamilyCount);

  if(tableVk.GetPhysicalDeviceQueueFamilyProperties)
    tableVk.GetPhysicalDeviceQueueFamilyProperties(gVkPhysicalDevice, &queueFamilyCount, &queueFamilyProps[0] );

  for(uint32_t i = 0; i < queueFamilyCount; ++i)
  {
    // Only need graphics (not presentation) for draw queue
    if(queueFamilyProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      gVulkanGraphicsPluginQueueFamilyIndex = queueInfo.queueFamilyIndex = i;
      break;
    }
  }

  std::vector<const char*> deviceExtensions;

  VkPhysicalDeviceFeatures features {};
  // todo
  features.samplerAnisotropy = VK_TRUE;

  VkDeviceCreateInfo deviceInfo {VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO};
  deviceInfo.queueCreateInfoCount = 1;
  deviceInfo.pQueueCreateInfos = &queueInfo;
  deviceInfo.enabledLayerCount = 0;
  deviceInfo.ppEnabledLayerNames = nullptr;
  deviceInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
  deviceInfo.ppEnabledExtensionNames = deviceExtensions.empty() ? nullptr : deviceExtensions.data();
  deviceInfo.pEnabledFeatures = &features;

  XrVulkanDeviceCreateInfoKHR deviceCreateInfo {XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR};

  deviceCreateInfo.systemId = gXrSystemId;

  deviceCreateInfo.pfnGetInstanceProcAddr = tableVk.GetInstanceProcAddr;

  deviceCreateInfo.vulkanCreateInfo = &deviceInfo;
  deviceCreateInfo.vulkanPhysicalDevice = gVkPhysicalDevice;
  deviceCreateInfo.vulkanAllocator = nullptr;

  // CHECK_XRCMD_CHECK(VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanDeviceKHR(
  //   gXrInstance,
  //   &deviceCreateInfo,
  //   &gVkDevice,
  //   &err
  // ) );
  //
  // CHECK_VULKANCMD(err);
  //
  // XrResult VulkanGraphicsPlugin_VulkanGraphicsPluginCreateVulkanDeviceKHR(
  //   XrInstance instance,
  //   const XrVulkanDeviceCreateInfoKHR* createInfo,
  //   VkDevice* vulkanDevice,
  //   VkResult* vulkanResult
  // )
  {
    XrResult result = XR_ERROR_VALIDATION_FAILURE;

    if(tableXr.CreateVulkanDeviceKHR)
      result = tableXr.CreateVulkanDeviceKHR(gXrInstance, &deviceCreateInfo, &gVkDevice, &err);

    CHECK_XRCMD_CHECK(result);
    CHECK_VULKANCMD(err);
  }

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
  gVulkanGraphicsPluginVulkanDebugObjectNamer.Init(gVkInstance, gVkDevice);
#endif

  if(tableVk.GetDeviceQueue)
    tableVk.GetDeviceQueue(gVkDevice, queueInfo.queueFamilyIndex, 0, &gVulkanGraphicsPluginVkQueue);

  //MemoryAllocator_MemoryAllocatorInit(gVkPhysicalDevice);
  if(tableVk.GetPhysicalDeviceMemoryProperties)
    tableVk.GetPhysicalDeviceMemoryProperties(gVkPhysicalDevice, &gMemoryAllocatorMemoryProperties);

  std::vector<uint32_t> vertexSPIRV;
  // compile a shader to a SPIR-V binary
  //
  // auto vertexSPIRV = VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader(
  //   "vertex",
  //   shaderc_glsl_default_vertex_shader,
  //   VertexShaderGlsl
  // );
  //
  // std::vector<uint32_t> VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader(
  //   const std::string& name,
  //   shaderc_shader_kind kind,
  //   const std::string& source
  // )
  {
    const std::string name("vertex");
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    options.SetOptimizationLevel(shaderc_optimization_level_size);

    shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(
      VertexShaderGlsl,
      shaderc_glsl_default_vertex_shader,
      name.c_str(),
      options
    );

    if(module.GetCompilationStatus() != shaderc_compilation_status_success)
    {
      Log::Write(
        Log::Level::Error,
        Fmt("Shader %s compilation failed: %s", name.c_str(), module.GetErrorMessage().c_str() )
      );

      vertexSPIRV = std::vector<uint32_t>();
    }
    else
    {
      vertexSPIRV = {module.cbegin(), module.cend() };
    }
  }

  std::vector<uint32_t> fragmentSPIRV;
  // compile a shader to a SPIR-V binary
  //
  // auto fragmentSPIRV = VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader(
  //   "fragment",
  //   shaderc_glsl_default_fragment_shader,
  //   FragmentShaderGlsl
  // );
  //
  // std::vector<uint32_t> VulkanGraphicsPlugin_VulkanGraphicsPluginCompileGlslShader(
  //   const std::string& name,
  //   shaderc_shader_kind kind,
  //   const std::string& source
  // )
  {
    const std::string name("fragment");
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    options.SetOptimizationLevel(shaderc_optimization_level_size);

    shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(
      FragmentShaderGlsl,
      shaderc_glsl_default_fragment_shader,
      name.c_str(),
      options
    );

    if(module.GetCompilationStatus() != shaderc_compilation_status_success)
    {
      Log::Write(
        Log::Level::Error,
        Fmt("Shader %s compilation failed: %s", name.c_str(), module.GetErrorMessage().c_str() )
      );

      fragmentSPIRV = std::vector<uint32_t>();
    }
    else
    {
      fragmentSPIRV = {module.cbegin(), module.cend() };
    }
  }

  if(vertexSPIRV.empty() ) THROW_CHECK("Failed to compile vertex shader");

  if(fragmentSPIRV.empty() ) THROW_CHECK("Failed to compile fragment shader");

  // ShaderProgram_ShaderProgramInit(gVkDevice);
  // nop

  // ShaderProgram_ShaderProgramLoadVertexShader(vertexSPIRV);
  // ShaderProgram_ShaderProgramLoad(0, vertexSPIRV);

  // ShaderProgram_ShaderProgramLoadFragmentShader(fragmentSPIRV);
  // ShaderProgram_ShaderProgramLoad(1, fragmentSPIRV);

  // void ShaderProgram_ShaderProgramLoad(uint32_t whichShaderInfo, const std::vector<uint32_t>& code)

  {
    VkShaderModuleCreateInfo modInfo {VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};

    auto& si = gShaderProgramShaderInfo[0];
    si.pName = "main";
    std::string name;

    si.stage = VK_SHADER_STAGE_VERTEX_BIT;
    name = "vertex";

    modInfo.codeSize = vertexSPIRV.size() * sizeof(vertexSPIRV[0] );
    modInfo.pCode = &vertexSPIRV[0];
    CHECK_MSG( (modInfo.codeSize > 0) && modInfo.pCode, Fmt("Invalid %s shader ", name.c_str() ) );

    if(tableVk.CreateShaderModule)
      CHECK_VULKANCMD(tableVk.CreateShaderModule(gVkDevice, &modInfo, nullptr, &si.module) );

    Log::Write(Log::Level::Info, Fmt("Loaded %s shader", name.c_str() ) );
  }

  {
    VkShaderModuleCreateInfo modInfo {VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO};

    auto& si = gShaderProgramShaderInfo[1];
    si.pName = "main";
    std::string name;

    si.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    name = "fragment";

    modInfo.codeSize = fragmentSPIRV.size() * sizeof(fragmentSPIRV[0] );
    modInfo.pCode = &fragmentSPIRV[0];
    CHECK_MSG( (modInfo.codeSize > 0) && modInfo.pCode, Fmt("Invalid %s shader ", name.c_str() ) );

    if(tableVk.CreateShaderModule)
      CHECK_VULKANCMD(tableVk.CreateShaderModule(gVkDevice, &modInfo, nullptr, &si.module) );

    Log::Write(Log::Level::Info, Fmt("Loaded %s shader", name.c_str() ) );
  }

  // Semaphore to block on draw complete
  VkSemaphoreCreateInfo semInfo {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};

  if(tableVk.CreateSemaphore)
    CHECK_VULKANCMD(tableVk.CreateSemaphore(gVkDevice, &semInfo, nullptr, &gVulkanGraphicsPluginVkSemaphoreDrawDone) );

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
  CHECK_VULKANCMD(gVulkanGraphicsPluginVulkanDebugObjectNamer.SetName(
    VK_OBJECT_TYPE_SEMAPHORE,
    (uint64_t)gVulkanGraphicsPluginVkSemaphoreDrawDone,
    "helloxr draw done semaphore"
  ) );
#endif

  bool CmdBuffer_CmdBufferInit_Result = false;
  // CmdBuffer_CmdBufferInit(
  //   gVulkanGraphicsPluginVulkanDebugObjectNamer,
  //   gVkDevice,
  //   gVulkanGraphicsPluginQueueFamilyIndex
  // )
  //
  // bool CmdBuffer_CmdBufferInit(
  //   const VulkanDebugObjectNamer& namer,
  //   VkDevice device,
  //   uint32_t queueFamilyIndex
  // )
  do
  {
    //CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Undefined);
    if(gCmdBufferState != CmdBufferStateEnum::Undefined)
    {
      Log::Write(
        Log::Level::Error,
        std::string("Expecting state CmdBufferStateEnum::Undefined from ") +
          __FUNCTION__ +
          ", in " +
          CmdBuffer_CmdBufferStateString(gCmdBufferState)
      );

      break;
    }

    // Create a command pool to allocate our command buffer from
    VkCommandPoolCreateInfo cmdPoolInfo {VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO};
    cmdPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    cmdPoolInfo.queueFamilyIndex = gVulkanGraphicsPluginQueueFamilyIndex;

    if(tableVk.CreateCommandPool)
      CHECK_VULKANCMD(tableVk.CreateCommandPool(gVkDevice, &cmdPoolInfo, nullptr, &gCmdBufferPool) );

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
    CHECK_VULKANCMD(gVulkanGraphicsPluginVulkanDebugObjectNamer.SetName(
      VK_OBJECT_TYPE_COMMAND_POOL,
      (uint64_t)gCmdBufferPool,
      "helloxr command pool"
    ) );
#endif

    // Create the command buffer from the command pool
    VkCommandBufferAllocateInfo cmd {VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
    cmd.commandPool = gCmdBufferPool;
    cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd.commandBufferCount = 1;

    if(tableVk.AllocateCommandBuffers)
      CHECK_VULKANCMD(tableVk.AllocateCommandBuffers(gVkDevice, &cmd, &gCmdBufferBuffer) );

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
    CHECK_VULKANCMD(gVulkanGraphicsPluginVulkanDebugObjectNamer.SetName(
      VK_OBJECT_TYPE_COMMAND_BUFFER,
      (uint64_t)gCmdBufferBuffer,
      "helloxr command buffer"
    ) );
#endif

    VkFenceCreateInfo fenceInfo {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};

    if(tableVk.CreateFence)
      CHECK_VULKANCMD(tableVk.CreateFence(gVkDevice, &fenceInfo, nullptr, &gCmdBufferExecFence) );

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
    CHECK_VULKANCMD(gVulkanGraphicsPluginVulkanDebugObjectNamer.SetName(
      VK_OBJECT_TYPE_FENCE,
      (uint64_t)gCmdBufferExecFence,
      "helloxr fence"
    ) );
#endif

    gCmdBufferState = CmdBufferStateEnum::Initialized;

    CmdBuffer_CmdBufferInit_Result = true;

  }while(0);

  if( !CmdBuffer_CmdBufferInit_Result)
    THROW_CHECK("Failed to create command buffer");

  //gVkPipelineLayout.PipelineLayoutCreate(gVkDevice);
  //PipelineLayout_PipelineLayoutCreate(gVkDevice);
  //void PipelineLayout_PipelineLayoutCreate(VkDevice device)
  {
    // MVP matrix is a push_constant
    VkPushConstantRange pcr = {};
    pcr.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    pcr.offset = 0;
    pcr.size = 4 * 4 * sizeof(float);

    //VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo {VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
    //
    //pipelineLayoutCreateInfo.pushConstantRangeCount = 1;
    //pipelineLayoutCreateInfo.pPushConstantRanges = &pcr;

    // texture 1 of 4 start
    {
      const VkDescriptorSetLayoutBinding descriptorSetLayoutBinding =
      {
        .binding = 2,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .descriptorCount = OBJ_TEXTURE_COUNT,
        .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
        .pImmutableSamplers = nullptr
      };

      const VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo =
      {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .pNext = nullptr,
        .bindingCount = 1,
        .pBindings = &descriptorSetLayoutBinding
      };

      if(tableVk.CreateDescriptorSetLayout)
      {
        tableVk.CreateDescriptorSetLayout(
          gVkDevice,
          &descriptorSetLayoutCreateInfo,
          nullptr,
          &gTextureVkDescriptorSetLayout
        );
      }

      VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo =
      {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext = nullptr,
        .setLayoutCount = 1,
        .pSetLayouts = &gTextureVkDescriptorSetLayout,
        .pushConstantRangeCount = 1,
        .pPushConstantRanges = &pcr
      };

      if(tableVk.CreatePipelineLayout)
        tableVk.CreatePipelineLayout(gVkDevice, &pipelineLayoutCreateInfo, nullptr, &gVkPipelineLayout);
    }
    // texture 1 of 4 finish

    //if(tableVk.CreatePipelineLayout)
    //{
    //  CHECK_VULKANCMD(tableVk.CreatePipelineLayout(
    //    gVkDevice,
    //    &pipelineLayoutCreateInfo,
    //    nullptr,
    //    &gVkPipelineLayout
    //  ) );
    //}
  }

  static_assert(sizeof(GeometryVertex) == 48, "Unexpected GeometryVertex size");

  gVertexBufferBaseAttrDesc =
  {
    {0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GeometryVertex, Position) },

    {1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GeometryVertex, Normal) },

    {2, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GeometryVertex, Color) },

    {3, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(GeometryVertex, Texture) },

    {4, 0, VK_FORMAT_R32_SINT, offsetof(GeometryVertex, Index) }
  };

  AnagTestTinyObjLoader();

  //VertexBuffer_VertexBufferCreate(Geometry::gModelsIndicesDynamicCountOf, Geometry::gModelsVerticesDynamicCountOf);
  //bool VertexBuffer_VertexBufferCreate(uint32_t idxCount, uint32_t vtxCount)
  {
    VkBufferCreateInfo bufInfo {VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO};

    bufInfo.usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    bufInfo.size = sizeof(uint32_t) * Geometry::gModelsIndicesDynamicCountOf;

    if(tableVk.CreateBuffer)
      CHECK_VULKANCMD(tableVk.CreateBuffer(gVkDevice, &bufInfo, nullptr, &gVertexBufferBaseIdxBuf) );

    //VertexBufferBase_VertexBufferBaseAllocateBufferMemory(gVertexBufferBaseIdxBuf, &gVertexBufferBaseIdxMem);
    //void VertexBufferBase_VertexBufferBaseAllocateBufferMemory(VkBuffer buf, VkDeviceMemory* mem)
    {
      VkMemoryRequirements memReqs = {};

      if(tableVk.GetBufferMemoryRequirements)
        tableVk.GetBufferMemoryRequirements(gVkDevice, gVertexBufferBaseIdxBuf, &memReqs);

// MemoryAllocator_MemoryAllocatorAllocate
      // MemoryAllocator_MemoryAllocatorAllocate(memReqs, &gVertexBufferBaseIdxMem);
      //
      // void MemoryAllocator_MemoryAllocatorAllocate(
      //   VkMemoryRequirements const& memReqs,
      //   VkDeviceMemory* mem,
      //   VkFlags flags = MemoryAllocator_m_memoryAllocatorDefaultFlags,
      //   void* pNext = nullptr
      // );
      //
      // void MemoryAllocator_MemoryAllocatorAllocate(
      //   VkMemoryRequirements const& memReqs,
      //   VkDeviceMemory* mem,
      //   VkFlags flags,
      //   void* pNext
      // )
      {
        bool foundMemoryAvailability = false;

        // Search memtypes to find first offset with those properties
        for(uint32_t offsetMemory = 0; offsetMemory < gMemoryAllocatorMemoryProperties.memoryTypeCount; offsetMemory++)
        {
          if(memReqs.memoryTypeBits & (1 << offsetMemory) )
          {
            // Type is available, does it match user properties?
            if(
              (gMemoryAllocatorMemoryProperties.memoryTypes[offsetMemory].propertyFlags &
                MemoryAllocator_m_memoryAllocatorDefaultFlags
              ) ==
                MemoryAllocator_m_memoryAllocatorDefaultFlags
            )
            {
              VkMemoryAllocateInfo memAlloc {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr};

              memAlloc.allocationSize = memReqs.size;
              memAlloc.memoryTypeIndex = offsetMemory;

              if(tableVk.AllocateMemory)
                CHECK_VULKANCMD(tableVk.AllocateMemory(gVkDevice, &memAlloc, nullptr, &gVertexBufferBaseIdxMem) );

              foundMemoryAvailability = true;

              break;
            }
          }
        }

        if( !foundMemoryAvailability)
          THROW_CHECK("Memory format not supported");
      }
// MemoryAllocator_MemoryAllocatorAllocate

    }

    if(tableVk.BindBufferMemory)
      CHECK_VULKANCMD(tableVk.BindBufferMemory(gVkDevice, gVertexBufferBaseIdxBuf, gVertexBufferBaseIdxMem, 0) );

    bufInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufInfo.size = sizeof(GeometryVertex) * Geometry::gModelsVerticesDynamicCountOf;

    if(tableVk.CreateBuffer)
      CHECK_VULKANCMD(tableVk.CreateBuffer(gVkDevice, &bufInfo, nullptr, &gVertexBufferBaseVtxBuf) );

    //VertexBufferBase_VertexBufferBaseAllocateBufferMemory(gVertexBufferBaseVtxBuf, &gVertexBufferBaseVtxMem);
    //void VertexBufferBase_VertexBufferBaseAllocateBufferMemory(VkBuffer buf, VkDeviceMemory* mem)
    {
      VkMemoryRequirements memReqs = {};

      if(tableVk.GetBufferMemoryRequirements)
        tableVk.GetBufferMemoryRequirements(gVkDevice, gVertexBufferBaseVtxBuf, &memReqs);

// MemoryAllocator_MemoryAllocatorAllocate
      // MemoryAllocator_MemoryAllocatorAllocate(memReqs, &gVertexBufferBaseVtxMem);
      //
      // void MemoryAllocator_MemoryAllocatorAllocate(
      //   VkMemoryRequirements const& memReqs,
      //   VkDeviceMemory* mem,
      //   VkFlags flags = MemoryAllocator_m_memoryAllocatorDefaultFlags,
      //   void* pNext = nullptr
      // );
      //
      // void MemoryAllocator_MemoryAllocatorAllocate(
      //   VkMemoryRequirements const& memReqs,
      //   VkDeviceMemory* mem,
      //   VkFlags flags,
      //   void* pNext
      // )
      {
        bool foundMemoryAvailability = false;

        // Search memtypes to find first offset with those properties
        for(uint32_t offsetMemory = 0; offsetMemory < gMemoryAllocatorMemoryProperties.memoryTypeCount; offsetMemory++)
        {
          if(memReqs.memoryTypeBits & (1 << offsetMemory) )
          {
            // Type is available, does it match user properties?
            if(
              (gMemoryAllocatorMemoryProperties.memoryTypes[offsetMemory].propertyFlags &
                MemoryAllocator_m_memoryAllocatorDefaultFlags
              ) ==
                MemoryAllocator_m_memoryAllocatorDefaultFlags
            )
            {
              VkMemoryAllocateInfo memAlloc {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr};

              memAlloc.allocationSize = memReqs.size;
              memAlloc.memoryTypeIndex = offsetMemory;

              if(tableVk.AllocateMemory)
                CHECK_VULKANCMD(tableVk.AllocateMemory(gVkDevice, &memAlloc, nullptr, &gVertexBufferBaseVtxMem) );

              foundMemoryAvailability = true;

              break;
            }
          }
        }

        if( !foundMemoryAvailability)
          THROW_CHECK("Memory format not supported");
      }
// MemoryAllocator_MemoryAllocatorAllocate

    }

    if(tableVk.BindBufferMemory)
      CHECK_VULKANCMD(tableVk.BindBufferMemory(gVkDevice, gVertexBufferBaseVtxBuf, gVertexBufferBaseVtxMem, 0) );

    gVertexBufferBaseBindDesc.binding = 0;
    gVertexBufferBaseBindDesc.stride = sizeof(GeometryVertex);
    gVertexBufferBaseBindDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    gVertexBufferBaseCount = {Geometry::gModelsIndicesDynamicCountOf, Geometry::gModelsVerticesDynamicCountOf};

    //return true;
  }

  //VertexBuffer_VertexBufferUpdateIndices(Geometry::gModelsIndicesDynamicData, Geometry::gModelsIndicesDynamicCountOf, 0);
  //void VertexBuffer_VertexBufferUpdateIndices(const uint32_t* data, uint32_t elements, uint32_t offset)
  {
    uint32_t offset = 0;
    uint32_t* map = nullptr;

    if(tableVk.MapMemory)
    {
      CHECK_VULKANCMD(tableVk.MapMemory(
        gVkDevice,
        gVertexBufferBaseIdxMem,
        sizeof(map[0] ) * offset,
        sizeof(map[0] ) * Geometry::gModelsIndicesDynamicCountOf,
        0,
        (void**) &map
      ) );
    }

    for(size_t i = 0; i < Geometry::gModelsIndicesDynamicCountOf; ++i)
      map[i] = Geometry::gModelsIndicesDynamicData[i];

    if(tableVk.UnmapMemory)
      tableVk.UnmapMemory(gVkDevice, gVertexBufferBaseIdxMem);
  }

  //VertexBuffer_VertexBufferUpdateVertices(Geometry::gModelsVerticesDynamicData, Geometry::gModelsVerticesDynamicCountOf, 0);
  //void VertexBuffer_VertexBufferUpdateVertices(const GeometryVertex* data, uint32_t elements, uint32_t offset)
  {
    uint32_t offset = 0;
    GeometryVertex* map = nullptr;

    if(tableVk.MapMemory)
    {
      CHECK_VULKANCMD(tableVk.MapMemory(
        gVkDevice,
        gVertexBufferBaseVtxMem,
        sizeof(map[0] ) * offset,
        sizeof(map[0] ) * Geometry::gModelsVerticesDynamicCountOf,
        0,
        (void**) &map
      ) );
    }

    for(size_t i = 0; i < Geometry::gModelsVerticesDynamicCountOf; ++i)
      map[i] = Geometry::gModelsVerticesDynamicData[i];

    if(tableVk.UnmapMemory)
      tableVk.UnmapMemory(gVkDevice, gVertexBufferBaseVtxMem);
  }

  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.instance = gVkInstance;
  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.physicalDevice = gVkPhysicalDevice;
  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.device = gVkDevice;
  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.queueFamilyIndex = queueInfo.queueFamilyIndex;
  gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR.queueIndex = 0;

  CHECK_CHECK(gXrInstance != XR_NULL_HANDLE);
  CHECK_CHECK(gXrSession == XR_NULL_HANDLE);

  {
    Log::Write(Log::Level::Verbose, Fmt("Creating session...") );

    XrSessionCreateInfo createInfo {XR_TYPE_SESSION_CREATE_INFO};

    createInfo.next = reinterpret_cast<const XrBaseInStructure*>( &gVulkanGraphicsPluginXrGraphicsBindingVulkan2KHR);
    createInfo.systemId = gXrSystemId;

    if(tableXr.CreateSession)
      CHECK_XRCMD_CHECK(tableXr.CreateSession(gXrInstance, &createInfo, &gXrSession) );
  }

  CHECK_CHECK(gXrSession != XR_NULL_HANDLE);

  // texture 2 of 4 start
  if(gTextureVkDescriptorSetLayout == VK_NULL_HANDLE)
  {
    /*VulkanTutorialCreateDescriptorSetLayout(gTextureVkDescriptorSetLayout);*/
  }

  if(gTextureBlahVk[0].sampler == VK_NULL_HANDLE && gTextureVkDescriptorSetLayout != VK_NULL_HANDLE)
  {
    const char* object_image_filename[] = OBJ_TEXTURE_FILENAME;

    for(uint32_t indexTexture = 0; indexTexture < OBJ_TEXTURE_COUNT; indexTexture++)
    {
      gTextureBlahVk[indexTexture].fileName = object_image_filename[indexTexture];

      VulkanTutorialCreateTextureImage(
        gVulkanGraphicsPluginVkQueue,
        gCmdBufferPool,
        gTextureBlahVk[indexTexture]
      );

      if(gTextureBlahVk[indexTexture].image != VK_NULL_HANDLE && gTextureBlahVk[indexTexture].deviceMemory != VK_NULL_HANDLE)
        Log::Write(Log::Level::Info, Fmt("VulkanTutorialCreateTextureImage success\n") );
      else
        Log::Write(Log::Level::Info, Fmt("VulkanTutorialCreateTextureImage failure\n") );

      gTextureBlahVk[indexTexture].imageView = VulkanTutorialCreateImageView(
        gTextureBlahVk[indexTexture].image,
        VK_FORMAT_R8G8B8A8_SRGB,
        VK_IMAGE_ASPECT_COLOR_BIT
      );

      VulkanTutorialCreateTextureSampler(gTextureBlahVk[indexTexture].sampler);
    }
  }

  if(
    gTextureVkDescriptorSet == VK_NULL_HANDLE &&
    gTextureBlahVk[0].sampler != VK_NULL_HANDLE &&
    gTextureVkDescriptorSetLayout != VK_NULL_HANDLE
  )
  {
    /*VulkanTutorialUpdateDescriptorSets(
        gTextureVkImageView,
        gTextureVkSampler,
        gTextureVkDescriptorSetLayout,
        gTextureVkDescriptorPool,
        gTextureVkDescriptorSet
    );*/
  }
  // texture 2 of 4 finish

  uint32_t spaceCount = 0;

  if(tableXr.EnumerateReferenceSpaces)
    CHECK_XRCMD_CHECK(tableXr.EnumerateReferenceSpaces(gXrSession, 0, &spaceCount, nullptr) );

  std::vector<XrReferenceSpaceType> spaces(spaceCount);

  if(tableXr.EnumerateReferenceSpaces)
    CHECK_XRCMD_CHECK(tableXr.EnumerateReferenceSpaces(gXrSession, spaceCount, &spaceCount, spaces.data() ) );

  Log::Write(Log::Level::Info, Fmt("Available reference spaces: %d", spaceCount) );

  for(XrReferenceSpaceType space : spaces)
    Log::Write(Log::Level::Verbose, Fmt("  Name: %s", to_string(space) ) );

  // Create an action set.
  {
    XrActionSetCreateInfo actionSetInfo {XR_TYPE_ACTION_SET_CREATE_INFO};
    strncpy(actionSetInfo.actionSetName, "gameplay", sizeof(actionSetInfo.actionSetName) );
    strncpy(actionSetInfo.localizedActionSetName, "Gameplay", sizeof(actionSetInfo.localizedActionSetName) );
    actionSetInfo.priority = 0;

    if(tableXr.CreateActionSet)
    {
      CHECK_XRCMD_CHECK(tableXr.CreateActionSet(
        gXrInstance,
        &actionSetInfo,
        &gOpenXrProgramInputState_InputState_actionSet
      ) );
    }
  }

  // Get the XrPath for the left and right hands - we will use them as subaction paths.

  if(tableXr.StringToPath)
  {
    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left",
      &gOpenXrProgramInputState_InputState_handSubactionPath[Side_LEFT]
    ) );
  }

  if(tableXr.StringToPath)
  {
    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right",
      &gOpenXrProgramInputState_InputState_handSubactionPath[Side_RIGHT]
    ) );
  }

  // Create actions.
  {
    {
      // Create an input action for grabbing objects with the left and right hands.
      XrActionCreateInfo actionInfo {XR_TYPE_ACTION_CREATE_INFO};
      actionInfo.actionType = XR_ACTION_TYPE_FLOAT_INPUT;
      strncpy(actionInfo.actionName, "grab_object", sizeof(actionInfo.actionName) );
      strncpy(actionInfo.localizedActionName, "Grab Object", sizeof(actionInfo.localizedActionName) );
      actionInfo.countSubactionPaths = uint32_t(gOpenXrProgramInputState_InputState_handSubactionPath.size() );
      actionInfo.subactionPaths = gOpenXrProgramInputState_InputState_handSubactionPath.data();

      if(tableXr.CreateAction)
      {
        CHECK_XRCMD_CHECK(tableXr.CreateAction(
          gOpenXrProgramInputState_InputState_actionSet,
          &actionInfo,
          &gOpenXrProgramInputState_InputState_grabAction
        ) );
      }
    }

    {
      XrActionCreateInfo actionInfo {XR_TYPE_ACTION_CREATE_INFO};
      actionInfo.actionType = XR_ACTION_TYPE_FLOAT_INPUT;
      strncpy(actionInfo.actionName, "trigger_object", sizeof(actionInfo.actionName) );
      strncpy(actionInfo.localizedActionName, "Trigger Object", sizeof(actionInfo.localizedActionName) );
      actionInfo.countSubactionPaths = uint32_t(gOpenXrProgramInputState_InputState_handSubactionPath.size() );
      actionInfo.subactionPaths = gOpenXrProgramInputState_InputState_handSubactionPath.data();

      if(tableXr.CreateAction)
      {
        CHECK_XRCMD_CHECK(tableXr.CreateAction(
          gOpenXrProgramInputState_InputState_actionSet,
          &actionInfo,
          &gOpenXrProgramInputState_InputState_triggerAction
        ) );
      }
    }

    {
      // Create an input action getting the left and right hand poses.
      XrActionCreateInfo actionInfo {XR_TYPE_ACTION_CREATE_INFO};
      actionInfo.actionType = XR_ACTION_TYPE_POSE_INPUT;
      strncpy(actionInfo.actionName, "hand_pose", sizeof(actionInfo.actionName) );
      strncpy(actionInfo.localizedActionName, "Hand OpenXrProgram_Pose", sizeof(actionInfo.localizedActionName) );
      actionInfo.countSubactionPaths = uint32_t(gOpenXrProgramInputState_InputState_handSubactionPath.size() );
      actionInfo.subactionPaths = gOpenXrProgramInputState_InputState_handSubactionPath.data();

      if(tableXr.CreateAction)
      {
        CHECK_XRCMD_CHECK(tableXr.CreateAction(
          gOpenXrProgramInputState_InputState_actionSet,
          &actionInfo,
          &gOpenXrProgramInputState_InputState_poseAction
        ) );
      }
    }

    {
      // Create output actions for vibrating the left and right controller.
      XrActionCreateInfo actionInfo {XR_TYPE_ACTION_CREATE_INFO};
      actionInfo.actionType = XR_ACTION_TYPE_VIBRATION_OUTPUT;
      strncpy(actionInfo.actionName, "vibrate_hand", sizeof(actionInfo.actionName) );
      strncpy(actionInfo.localizedActionName, "Vibrate Hand", sizeof(actionInfo.localizedActionName) );
      actionInfo.countSubactionPaths = uint32_t(gOpenXrProgramInputState_InputState_handSubactionPath.size() );
      actionInfo.subactionPaths = gOpenXrProgramInputState_InputState_handSubactionPath.data();

      if(tableXr.CreateAction)
      {
        CHECK_XRCMD_CHECK(tableXr.CreateAction(
          gOpenXrProgramInputState_InputState_actionSet,
          &actionInfo,
          &gOpenXrProgramInputState_InputState_vibrateAction
        ) );
      }
    }

    {
      // Create input actions for quitting the session using the left and right controller.
      // Since it doesn't matter which hand did this, we do not specify subaction paths for it.
      // We will just suggest bindings for both hands, where possible.
      XrActionCreateInfo actionInfo {XR_TYPE_ACTION_CREATE_INFO};
      actionInfo.actionType = XR_ACTION_TYPE_BOOLEAN_INPUT;
      strncpy(actionInfo.actionName, "quit_session", sizeof(actionInfo.actionName) );
      strncpy(actionInfo.localizedActionName, "Quit Session", sizeof(actionInfo.localizedActionName) );
      actionInfo.countSubactionPaths = 0;
      actionInfo.subactionPaths = nullptr;

      if(tableXr.CreateAction)
      {
        CHECK_XRCMD_CHECK(tableXr.CreateAction(
          gOpenXrProgramInputState_InputState_actionSet,
          &actionInfo,
          &gOpenXrProgramInputState_InputState_quitAction
        ) );
      }
    }
  }

  std::array<XrPath, Side_COUNT> selectPath;
  std::array<XrPath, Side_COUNT> squeezeValuePath;
  std::array<XrPath, Side_COUNT> squeezeForcePath;
  std::array<XrPath, Side_COUNT> squeezeClickPath;
  std::array<XrPath, Side_COUNT> posePath;
  std::array<XrPath, Side_COUNT> hapticPath;
  std::array<XrPath, Side_COUNT> menuClickPath;
  std::array<XrPath, Side_COUNT> bClickPath;
  std::array<XrPath, Side_COUNT> triggerValuePath;

  if(tableXr.StringToPath)
  {
    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/input/select/click",
      &selectPath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/input/select/click",
      &selectPath[Side_RIGHT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/input/squeeze/value",
      &squeezeValuePath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/input/squeeze/value",
      &squeezeValuePath[Side_RIGHT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/input/squeeze/force",
      &squeezeForcePath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/input/squeeze/force",
      &squeezeForcePath[Side_RIGHT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/input/squeeze/click",
      &squeezeClickPath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/input/squeeze/click",
      &squeezeClickPath[Side_RIGHT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/input/grip/pose",
      &posePath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/input/grip/pose",
      &posePath[Side_RIGHT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/output/haptic",
      &hapticPath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/output/haptic",
      &hapticPath[Side_RIGHT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/input/menu/click",
      &menuClickPath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/input/menu/click",
      &menuClickPath[Side_RIGHT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/input/b/click",
      &bClickPath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/input/b/click",
      &bClickPath[Side_RIGHT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/left/input/trigger/value",
      &triggerValuePath[Side_LEFT]
    ) );

    CHECK_XRCMD_CHECK(tableXr.StringToPath(
      gXrInstance,
      "/user/hand/right/input/trigger/value",
      &triggerValuePath[Side_RIGHT]
    ) );
  }

  // Suggest bindings for KHR Simple.
  {
    XrPath khrSimpleInteractionProfilePath;

    if(tableXr.StringToPath)
    {
      CHECK_XRCMD_CHECK(tableXr.StringToPath(
        gXrInstance,
        "/interaction_profiles/khr/simple_controller",
        &khrSimpleInteractionProfilePath)
      );
    }

    // fall back to a click input for the grab action
    std::vector<XrActionSuggestedBinding> bindings
    {
      {
        {gOpenXrProgramInputState_InputState_grabAction, selectPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_grabAction, selectPath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_quitAction, menuClickPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_quitAction, menuClickPath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_RIGHT] }
      }
    };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = khrSimpleInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD_CHECK(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  // Suggest bindings for the Oculus Touch.
  {
    XrPath oculusTouchInteractionProfilePath;

    if(tableXr.StringToPath)
    {
      CHECK_XRCMD_CHECK(tableXr.StringToPath(
        gXrInstance,
        "/interaction_profiles/oculus/touch_controller",
        &oculusTouchInteractionProfilePath)
      );
    }

    std::vector<XrActionSuggestedBinding> bindings
    {
      {
        {gOpenXrProgramInputState_InputState_grabAction, squeezeValuePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_grabAction, squeezeValuePath[Side_RIGHT] },

        {gOpenXrProgramInputState_InputState_triggerAction, triggerValuePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_triggerAction, triggerValuePath[Side_RIGHT] },

        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_quitAction, menuClickPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_RIGHT] }
      }
    };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = oculusTouchInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD_CHECK(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  // Suggest bindings for the Vive Controller.
  {
    XrPath viveControllerInteractionProfilePath;

    if(tableXr.StringToPath)
    {
      CHECK_XRCMD_CHECK(tableXr.StringToPath(
        gXrInstance,
        "/interaction_profiles/htc/vive_controller",
        &viveControllerInteractionProfilePath
      ) );
    }

    std::vector<XrActionSuggestedBinding> bindings
    {
      {
        {gOpenXrProgramInputState_InputState_grabAction, triggerValuePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_grabAction, triggerValuePath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_quitAction, menuClickPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_quitAction, menuClickPath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_RIGHT] }
      }
    };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = viveControllerInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD_CHECK(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  // Suggest bindings for the Valve Index Controller.
  {
    XrPath indexControllerInteractionProfilePath;

    if(tableXr.StringToPath)
    {
      CHECK_XRCMD_CHECK(tableXr.StringToPath(
        gXrInstance,
        "/interaction_profiles/valve/index_controller",
        &indexControllerInteractionProfilePath
      ) );
    }

    std::vector<XrActionSuggestedBinding> bindings
    {
      {
        {gOpenXrProgramInputState_InputState_grabAction, squeezeForcePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_grabAction, squeezeForcePath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_quitAction, bClickPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_quitAction, bClickPath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_RIGHT] }
      }
    };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = indexControllerInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD_CHECK(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  // Suggest bindings for the Microsoft Mixed Reality Motion Controller.
  {
    XrPath microsoftMixedRealityInteractionProfilePath;

    if(tableXr.StringToPath)
    {
      CHECK_XRCMD_CHECK(tableXr.StringToPath(
        gXrInstance,
        "/interaction_profiles/microsoft/motion_controller",
        &microsoftMixedRealityInteractionProfilePath
      ) );
    }

    std::vector<XrActionSuggestedBinding> bindings
    {
      {
        {gOpenXrProgramInputState_InputState_grabAction, squeezeClickPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_grabAction, squeezeClickPath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_poseAction, posePath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_quitAction, menuClickPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_quitAction, menuClickPath[Side_RIGHT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_LEFT] },
        {gOpenXrProgramInputState_InputState_vibrateAction, hapticPath[Side_RIGHT] }
      }
    };

    XrInteractionProfileSuggestedBinding suggestedBindings {XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING};

    suggestedBindings.interactionProfile = microsoftMixedRealityInteractionProfilePath;
    suggestedBindings.suggestedBindings = bindings.data();
    suggestedBindings.countSuggestedBindings = (uint32_t)bindings.size();

    if(tableXr.SuggestInteractionProfileBindings)
      CHECK_XRCMD_CHECK(tableXr.SuggestInteractionProfileBindings(gXrInstance, &suggestedBindings) );
  }

  XrActionSpaceCreateInfo actionSpaceInfo {XR_TYPE_ACTION_SPACE_CREATE_INFO};

  actionSpaceInfo.action = gOpenXrProgramInputState_InputState_poseAction;
  actionSpaceInfo.poseInActionSpace.orientation.w = 1.f;
  actionSpaceInfo.subactionPath = gOpenXrProgramInputState_InputState_handSubactionPath[Side_LEFT];

  if(tableXr.CreateActionSpace)
  {
    CHECK_XRCMD_CHECK(tableXr.CreateActionSpace(
      gXrSession,
      &actionSpaceInfo,
      &gOpenXrProgramInputState_InputState_handSpace[Side_LEFT]
    ) );
  }

  actionSpaceInfo.subactionPath = gOpenXrProgramInputState_InputState_handSubactionPath[Side_RIGHT];

  if(tableXr.CreateActionSpace)
  {
    CHECK_XRCMD_CHECK(tableXr.CreateActionSpace(
      gXrSession,
      &actionSpaceInfo,
      &gOpenXrProgramInputState_InputState_handSpace[Side_RIGHT]
    ) );
  }

  XrSessionActionSetsAttachInfo attachInfo {XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO};
  attachInfo.countActionSets = 1;
  attachInfo.actionSets = &gOpenXrProgramInputState_InputState_actionSet;

  if(tableXr.AttachSessionActionSets)
    CHECK_XRCMD_CHECK(tableXr.AttachSessionActionSets(gXrSession, &attachInfo) );

  CHECK_CHECK(gXrSession != XR_NULL_HANDLE);

  std::string visualizedSpaces[] =
  {
    "ViewFront",
    "Local",
    "Stage",
    "StageLeft",
    "StageRight",
    "StageLeftRotated",
    "StageRightRotated"
  };

  for(const auto& visualizedSpace : visualizedSpaces)
  {
    XrReferenceSpaceCreateInfo referenceSpaceCreateInfo = GetXrReferenceSpaceCreateInfo(visualizedSpace);

    XrSpace space;

    XrResult res = XR_ERROR_VALIDATION_FAILURE;

    if(tableXr.CreateReferenceSpace)
      res = tableXr.CreateReferenceSpace(gXrSession, &referenceSpaceCreateInfo, &space);

    if(XR_SUCCEEDED(res) )
    {
      gOpenXrProgramStdVector_XrSpace.push_back(space);
    }
    else
    {
      Log::Write(
        Log::Level::Warning,
        Fmt("Failed to create reference space %s with error %d", visualizedSpace.c_str(), res)
      );
    }
  }

  {
    XrReferenceSpaceCreateInfo referenceSpaceCreateInfo = GetXrReferenceSpaceCreateInfo(gOptions_AppSpace);

    if(tableXr.CreateReferenceSpace)
      CHECK_XRCMD_CHECK(tableXr.CreateReferenceSpace(gXrSession, &referenceSpaceCreateInfo, &gOpenXrProgramXrSpace) );
  }

  CHECK_CHECK(gXrSession != XR_NULL_HANDLE);
  CHECK_CHECK(gOpenXrProgramStdVector_Swapchain.empty() );
  CHECK_CHECK(gOpenXrProgramStdVector_XrViewConfigurationView.empty() );

  // Read graphics properties for preferred swapchain length and logging.
  XrSystemProperties systemProperties {XR_TYPE_SYSTEM_PROPERTIES};

  if(tableXr.GetSystemProperties)
    CHECK_XRCMD_CHECK(tableXr.GetSystemProperties(gXrInstance, gXrSystemId, &systemProperties) );

  // Log system properties.
  Log::Write(
    Log::Level::Info,
    Fmt("System Properties: Name=%s VendorId=%d", systemProperties.systemName, systemProperties.vendorId)
  );

  Log::Write(
    Log::Level::Info,
    Fmt(
      "System Graphics Properties: MaxWidth=%d MaxHeight=%d MaxLayers=%d",
      systemProperties.graphicsProperties.maxSwapchainImageWidth,
      systemProperties.graphicsProperties.maxSwapchainImageHeight,
      systemProperties.graphicsProperties.maxLayerCount
    )
  );

  Log::Write(
    Log::Level::Info,
    Fmt(
      "System Tracking Properties: OrientationTracking=%s PositionTracking=%s",
      systemProperties.trackingProperties.orientationTracking == XR_TRUE ? "True" : "False",
      systemProperties.trackingProperties.positionTracking == XR_TRUE ? "True" : "False"
    )
  );

  // Note: No other view configurations exist at the time this code was written. If this
  // condition is not met, the project will need to be audited to see how support should be
  // added.
  CHECK_MSG(
    gOptions_XrViewConfigurationType == XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
    "Unsupported view configuration type"
  );

  // Query and cache view configuration views.
  uint32_t viewCount = 0;

  if(tableXr.EnumerateViewConfigurationViews)
  {
    CHECK_XRCMD_CHECK(tableXr.EnumerateViewConfigurationViews(
      gXrInstance,
      gXrSystemId,
      gOptions_XrViewConfigurationType,
      0,
      &viewCount,
      nullptr
    ) );
  }

  gOpenXrProgramStdVector_XrViewConfigurationView.resize(viewCount, {XR_TYPE_VIEW_CONFIGURATION_VIEW} );

  if(tableXr.EnumerateViewConfigurationViews)
  {
    CHECK_XRCMD_CHECK(tableXr.EnumerateViewConfigurationViews(
      gXrInstance,
      gXrSystemId,
      gOptions_XrViewConfigurationType,
      viewCount,
      &viewCount,
      gOpenXrProgramStdVector_XrViewConfigurationView.data()
    ) );
  }

  // Create and cache view buffer for xrLocateViews later
  gOpenXrProgramStdVector_XrView.resize(viewCount, {XR_TYPE_VIEW} );

  // Create the swapchain and get the images.
  if(viewCount > 0)
  {
    // Select a swapchain format.
    uint32_t swapchainFormatCount = 0;

    if(tableXr.EnumerateSwapchainFormats)
      CHECK_XRCMD_CHECK(tableXr.EnumerateSwapchainFormats(gXrSession, 0, &swapchainFormatCount, nullptr) );

    std::vector<int64_t> swapchainFormats(swapchainFormatCount);

    if(tableXr.EnumerateSwapchainFormats)
    {
      CHECK_XRCMD_CHECK(tableXr.EnumerateSwapchainFormats(
        gXrSession,
        (uint32_t)swapchainFormats.size(),
        &swapchainFormatCount,
        swapchainFormats.data()
      ) );
    }

    CHECK_CHECK(swapchainFormatCount == swapchainFormats.size() );

    // gOpenXrProgramColorSwapchainFormat = VulkanGraphicsPlugin_VulkanGraphicsPluginSelectColorSwapchainFormat(
    //   swapchainFormats
    // );
    //
    // int64_t VulkanGraphicsPlugin_VulkanGraphicsPluginSelectColorSwapchainFormat(
    //   const std::vector<int64_t>& runtimeFormats
    // )
    {
      // List of supported color swapchain formats.
      constexpr int64_t SupportedColorSwapchainFormats[] =
      {
        VK_FORMAT_B8G8R8A8_SRGB,
        VK_FORMAT_R8G8B8A8_SRGB,
        VK_FORMAT_B8G8R8A8_UNORM,
        VK_FORMAT_R8G8B8A8_UNORM
      };

      auto swapchainFormatIt = std::find_first_of(
        swapchainFormats.begin(),
        swapchainFormats.end(),
        std::begin(SupportedColorSwapchainFormats),
        std::end(SupportedColorSwapchainFormats)
      );

      if(swapchainFormatIt == swapchainFormats.end() )
        THROW_CHECK("No runtime swapchain format supported for color swapchain");

      gOpenXrProgramColorSwapchainFormat = *swapchainFormatIt;
    }

    // Print swapchain formats and the selected one
    {
      std::string swapchainFormatsString;

      for(int64_t format : swapchainFormats)
      {
        const bool selected = (format == gOpenXrProgramColorSwapchainFormat);

        swapchainFormatsString += " ";

        if(selected)
          swapchainFormatsString += "[";

        swapchainFormatsString += std::to_string(format);

        if(selected)
          swapchainFormatsString += "]";
      }

      Log::Write(Log::Level::Verbose, Fmt("Swapchain Formats: %s", swapchainFormatsString.c_str() ) );
    }

    // Create a swapchain for each view
    for(uint32_t i = 0; i < viewCount; i++)
    {
      const XrViewConfigurationView& vp = gOpenXrProgramStdVector_XrViewConfigurationView[i];

      Log::Write(
        Log::Level::Info,
        Fmt(
          "Creating swapchain for view %d with dimensions Width=%d Height=%d SampleCount=%d",
          i,
          vp.recommendedImageRectWidth,
          vp.recommendedImageRectHeight,
          vp.recommendedSwapchainSampleCount
        )
      );

      // Create the swapchain.
      XrSwapchainCreateInfo swapchainCreateInfo {XR_TYPE_SWAPCHAIN_CREATE_INFO};
      swapchainCreateInfo.arraySize = 1;
      swapchainCreateInfo.format = gOpenXrProgramColorSwapchainFormat;
      swapchainCreateInfo.width = vp.recommendedImageRectWidth;
      swapchainCreateInfo.height = vp.recommendedImageRectHeight;
      swapchainCreateInfo.mipCount = 1;
      swapchainCreateInfo.faceCount = 1;
      swapchainCreateInfo.sampleCount = VK_SAMPLE_COUNT_1_BIT;
      swapchainCreateInfo.usageFlags = XR_SWAPCHAIN_USAGE_SAMPLED_BIT | XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
      Swapchain swapchain;
      swapchain.width = swapchainCreateInfo.width;
      swapchain.height = swapchainCreateInfo.height;

      if(tableXr.CreateSwapchain)
        CHECK_XRCMD_CHECK(tableXr.CreateSwapchain(gXrSession, &swapchainCreateInfo, &swapchain.handle) );

      gOpenXrProgramStdVector_Swapchain.push_back(swapchain);

      uint32_t imageCount = 0;

      if(tableXr.EnumerateSwapchainImages)
        CHECK_XRCMD_CHECK(tableXr.EnumerateSwapchainImages(swapchain.handle, 0, &imageCount, nullptr) );

      std::vector<XrSwapchainImageBaseHeader*> swapchainImages;
      // XXX This should really just return XrSwapchainImageBaseHeader*
      //
      // std::vector<XrSwapchainImageBaseHeader*> swapchainImages =
      //   VulkanGraphicsPlugin_VulkanGraphicsPluginAllocateSwapchainImageStructs(imageCount, swapchainCreateInfo);
      //
      // std::vector<XrSwapchainImageBaseHeader*>
      // VulkanGraphicsPlugin_VulkanGraphicsPluginAllocateSwapchainImageStructs(
      //   uint32_t capacity,
      //   const XrSwapchainCreateInfo& swapchainCreateInfo
      // )
      {
        uint32_t capacity = imageCount;

        int indice = gVulkanGraphicsPluginStdList_SwapchainImageContext.size();

        // Allocate and initialize the buffer of image structs (must be sequential in memory for
        // xrEnumerateSwapchainImages).
        //
        // Return back an array of pointers to each swapchain image struct so the consumer doesn't need to know the
        // type/size.
        //
        // Keep the buffer alive by adding it into the list of buffers.

        // SwapchainImageContext_SwapchainImageContext_Constructor(
        //   indice,
        //   VulkanGraphicsPlugin_VulkanGraphicsPluginGetSwapchainImageType(),
        //   gVulkanGraphicsPluginVulkanDebugObjectNamer
        // );
        //
        // void SwapchainImageContext_SwapchainImageContext_Constructor(
        //   int index,
        //   XrStructureType swapchainImageType,
        //   VulkanDebugObjectNamer& namer
        // )
        {
          XrStructureType swapchainImageType = XR_TYPE_SWAPCHAIN_IMAGE_VULKAN2_KHR;

          m_swapchainImageContextSwapchainImages.resize(indice + 1);
          m_swapchainImageContextStdVector_renderTargetColorImage.resize(indice + 1);
          m_swapchainImageContextStdVector_renderTargetDepthImage.resize(indice + 1);
          m_swapchainImageContextStdVector_renderTargetColorView.resize(indice + 1);
          m_swapchainImageContextStdVector_renderTargetDepthView.resize(indice + 1);
          m_swapchainImageContextStdVector_renderTargetFrameBuffer.resize(indice + 1);
          m_swapchainImageContextSize.resize(indice + 1);
          m_swapchainImageContext_depthBufferDepthMemory.resize(indice + 1);
          m_swapchainImageContext_depthBufferDepthImage.resize(indice + 1);
          m_swapchainImageContext_depthBufferVkImageLayout.resize(indice + 1);
          m_swapchainImageContext_renderPassColorFmt.resize(indice + 1);
          m_swapchainImageContext_renderPassDepthFmt.resize(indice + 1);
          m_swapchainImageContext_renderPassPass.resize(indice + 1);
          m_swapchainImageContextPipe_pipelinePipe.resize(indice + 1);
          m_swapchainImageContextPipe_pipelineTopology.resize(indice + 1);
          m_swapchainImageContextPipe_pipelineDynamicStateEnables.resize(indice + 1);
          m_swapchainImageContextSwapchainImageType.resize(indice + 1);

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
          m_swapchainImageContextNamer.resize(indice + 1);
#endif

          //m_swapchainImageContextSwapchainImages[indice].push_back( {swapchainImageType, 0, 0} );
          //m_swapchainImageContextStdVector_renderTargetColorImage[indice].push_back(VK_NULL_HANDLE);
          //m_swapchainImageContextStdVector_renderTargetDepthImage[indice].push_back(VK_NULL_HANDLE);
          //m_swapchainImageContextStdVector_renderTargetColorView[indice].push_back(VK_NULL_HANDLE);
          //m_swapchainImageContextStdVector_renderTargetDepthView[indice].push_back(VK_NULL_HANDLE);
          //m_swapchainImageContextStdVector_renderTargetFrameBuffer[indice].push_back(VK_NULL_HANDLE);
          m_swapchainImageContextSize[indice] = {640, 480};
          m_swapchainImageContext_depthBufferDepthMemory[indice] = VK_NULL_HANDLE;
          m_swapchainImageContext_depthBufferDepthImage[indice] = VK_NULL_HANDLE;
          m_swapchainImageContext_depthBufferVkImageLayout[indice] = VK_IMAGE_LAYOUT_UNDEFINED;
          m_swapchainImageContext_renderPassColorFmt[indice] = VK_FORMAT_B8G8R8A8_SRGB;
          m_swapchainImageContext_renderPassDepthFmt[indice] = VK_FORMAT_D32_SFLOAT;
          m_swapchainImageContext_renderPassPass[indice] = VK_NULL_HANDLE;
          m_swapchainImageContextPipe_pipelinePipe[indice] = VK_NULL_HANDLE;
          m_swapchainImageContextPipe_pipelineTopology[indice] = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
          //m_swapchainImageContextPipe_pipelineDynamicStateEnables[indice].push_back(VK_DYNAMIC_STATE_MAX_ENUM);
          m_swapchainImageContextSwapchainImageType[indice] = swapchainImageType;

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
          m_swapchainImageContextNamer[indice] = gVulkanGraphicsPluginVulkanDebugObjectNamer;
#endif
        }

        //gVulkanGraphicsPluginStdList_SwapchainImageContext.push_back(
        //  new SwapchainImageContext(VulkanGraphicsPluginGetSwapchainImageType() )
        //);
        gVulkanGraphicsPluginStdList_SwapchainImageContext.push_back(indice);

        //SwapchainImageContext* swapchainImageContext = gVulkanGraphicsPluginStdList_SwapchainImageContext[indice];

        //std::vector<XrSwapchainImageBaseHeader*> bases = swapchainImageContext->SwapchainImageContextCreate(
        //  gVulkanGraphicsPluginVulkanDebugObjectNamer,
        //  gVkDevice,
        //  capacity,
        //  swapchainCreateInfo,
        //  m_vulkanGraphicsPluginShaderProgram,
        //  m_vulkanGraphicsPluginVertexBuffer_GeometryVertex_DrawBuffer
        //);

        std::vector<XrSwapchainImageBaseHeader*> bases;
        // std::vector<XrSwapchainImageBaseHeader*> bases = SwapchainImageContext_SwapchainImageContextCreate(
        //   indice,
        //   gVulkanGraphicsPluginVulkanDebugObjectNamer,
        //   gVkDevice,
        //   capacity,
        //   swapchainCreateInfo
        // );
        //
        // std::vector<XrSwapchainImageBaseHeader*> SwapchainImageContext_SwapchainImageContextCreate(
        //   int index,
        //   const VulkanDebugObjectNamer& namer,
        //   VkDevice device,
        //   uint32_t capacity,
        //   const XrSwapchainCreateInfo& swapchainCreateInfo
        // )
        {
#if defined(VULKAN_DEBUG_OBJECT_NAMER)
          m_swapchainImageContextNamer[indice] = gVulkanGraphicsPluginVulkanDebugObjectNamer;
#endif

          m_swapchainImageContextSize[indice] = {swapchainCreateInfo.width, swapchainCreateInfo.height};
          VkFormat colorFormat = (VkFormat)swapchainCreateInfo.format;
          VkFormat depthFormat = VK_FORMAT_D32_SFLOAT;

          // SwapchainImageContext_SwapchainImageContext_DepthBufferCreate(
          //   indice,
          //   m_swapchainImageContextNamer[indice],
          //   gVkDevice,
          //   depthFormat,
          //   swapchainCreateInfo
          // );
          //
          // void SwapchainImageContext_SwapchainImageContext_DepthBufferCreate(
          //   int index,
          //   const VulkanDebugObjectNamer& namer,
          //   VkDevice device,
          //   VkFormat depthFormat,
          //   const XrSwapchainCreateInfo& swapchainCreateInfo
          // )
          {
            VkExtent2D size = {swapchainCreateInfo.width, swapchainCreateInfo.height};

            // Create a D32 depthbuffer
            VkImageCreateInfo imageInfo {VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO};
            imageInfo.imageType = VK_IMAGE_TYPE_2D;
            imageInfo.extent.width = size.width;
            imageInfo.extent.height = size.height;
            imageInfo.extent.depth = 1;
            imageInfo.mipLevels = 1;
            imageInfo.arrayLayers = 1;
            imageInfo.format = depthFormat;
            imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
            imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
            imageInfo.samples = (VkSampleCountFlagBits)swapchainCreateInfo.sampleCount;
            imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

            if(tableVk.CreateImage)
            {
              CHECK_VULKANCMD(tableVk.CreateImage(
                gVkDevice,
                &imageInfo,
                nullptr,
                &m_swapchainImageContext_depthBufferDepthImage[indice]
              ) );
            }

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
            CHECK_VULKANCMD(m_swapchainImageContextNamer[indice].SetName(
              VK_OBJECT_TYPE_IMAGE,
              (uint64_t)m_swapchainImageContext_depthBufferDepthImage[indice],
              "helloxr fallback depth image"
            ) );
#endif

            VkMemoryRequirements memRequirements {};

            if(tableVk.GetImageMemoryRequirements)
            {
              tableVk.GetImageMemoryRequirements(
                gVkDevice,
                m_swapchainImageContext_depthBufferDepthImage[indice],
                &memRequirements
              );
            }

// MemoryAllocator_MemoryAllocatorAllocate
            // MemoryAllocator_MemoryAllocatorAllocate(
            //   memRequirements,
            //   &m_swapchainImageContext_depthBufferDepthMemory[indice],
            //   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
            // );
            //
            // void MemoryAllocator_MemoryAllocatorAllocate(
            //   VkMemoryRequirements const& memReqs,
            //   VkDeviceMemory* mem,
            //   VkFlags flags = MemoryAllocator_m_memoryAllocatorDefaultFlags,
            //   void* pNext = nullptr
            // );
            //
            // void MemoryAllocator_MemoryAllocatorAllocate(
            //   VkMemoryRequirements const& memReqs,
            //   VkDeviceMemory* mem,
            //   VkFlags flags,
            //   void* pNext
            // )
            {
              bool foundMemoryAvailability = false;

              // Search memtypes to find first offset with those properties
              for(
                uint32_t offsetMemory = 0;
                offsetMemory < gMemoryAllocatorMemoryProperties.memoryTypeCount;
                offsetMemory++
              )
              {
                if(memRequirements.memoryTypeBits & (1 << offsetMemory) )
                {
                  // Type is available, does it match user properties?
                  if(
                    (gMemoryAllocatorMemoryProperties.memoryTypes[offsetMemory].propertyFlags &
                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT/*flags*/
                    ) ==
                      VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT/*flags*/
                  )
                  {
                    VkMemoryAllocateInfo memAlloc {VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, nullptr/*pNext*/};

                    memAlloc.allocationSize = memRequirements.size;
                    memAlloc.memoryTypeIndex = offsetMemory;

                    if(tableVk.AllocateMemory)
                    {
                      CHECK_VULKANCMD(tableVk.AllocateMemory(
                        gVkDevice,
                        &memAlloc,
                        nullptr,
                        &m_swapchainImageContext_depthBufferDepthMemory[indice]/*mem*/
                      ) );
                    }

                    foundMemoryAvailability = true;

                    break;
                  }
                }
              }

              if( !foundMemoryAvailability)
                THROW_CHECK("Memory format not supported");
            }
// MemoryAllocator_MemoryAllocatorAllocate

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
            CHECK_VULKANCMD(m_swapchainImageContextNamer[indice].SetName(
              VK_OBJECT_TYPE_DEVICE_MEMORY,
              (uint64_t)m_swapchainImageContext_depthBufferDepthMemory[indice],
              "helloxr fallback depth image memory"
            ) );
#endif

            if(tableVk.BindImageMemory)
            {
              CHECK_VULKANCMD(tableVk.BindImageMemory(
                gVkDevice,
                m_swapchainImageContext_depthBufferDepthImage[indice],
                m_swapchainImageContext_depthBufferDepthMemory[indice],
                0
              ) );
            }
          }

          // SwapchainImageContext_SwapchainImageContext_RenderPassCreate(
          //   indice,
          //   m_swapchainImageContextNamer[indice],
          //   gVkDevice,
          //   colorFormat,
          //   depthFormat
          // );
          //
          // bool SwapchainImageContext_SwapchainImageContext_RenderPassCreate(
          //   int index,
          //   const VulkanDebugObjectNamer& namer,
          //   VkDevice device,
          //   VkFormat aColorFmt,
          //   VkFormat aDepthFmt
          // )
          {
            m_swapchainImageContext_renderPassColorFmt[indice] = colorFormat;
            m_swapchainImageContext_renderPassDepthFmt[indice] = depthFormat;

            VkSubpassDescription subpass = {};
            subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

            VkAttachmentReference colorRef = {0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
            VkAttachmentReference depthRef = {1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

            std::array<VkAttachmentDescription, 2> at = {};

            VkRenderPassCreateInfo rpInfo {VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
            rpInfo.attachmentCount = 0;
            rpInfo.pAttachments = at.data();
            rpInfo.subpassCount = 1;
            rpInfo.pSubpasses = &subpass;

            if(m_swapchainImageContext_renderPassColorFmt[indice] != VK_FORMAT_UNDEFINED)
            {
              colorRef.attachment = rpInfo.attachmentCount++;

              at[colorRef.attachment].format = m_swapchainImageContext_renderPassColorFmt[indice];
              at[colorRef.attachment].samples = VK_SAMPLE_COUNT_1_BIT;
              at[colorRef.attachment].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
              at[colorRef.attachment].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
              at[colorRef.attachment].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
              at[colorRef.attachment].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
              at[colorRef.attachment].initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
              at[colorRef.attachment].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

              subpass.colorAttachmentCount = 1;
              subpass.pColorAttachments = &colorRef;
            }

            if(m_swapchainImageContext_renderPassDepthFmt[indice] != VK_FORMAT_UNDEFINED)
            {
              depthRef.attachment = rpInfo.attachmentCount++;

              at[depthRef.attachment].format = m_swapchainImageContext_renderPassDepthFmt[indice];
              at[depthRef.attachment].samples = VK_SAMPLE_COUNT_1_BIT;
              at[depthRef.attachment].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
              at[depthRef.attachment].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
              at[depthRef.attachment].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
              at[depthRef.attachment].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
              at[depthRef.attachment].initialLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
              at[depthRef.attachment].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

              subpass.pDepthStencilAttachment = &depthRef;
            }

            if(tableVk.CreateRenderPass)
            {
              CHECK_VULKANCMD(tableVk.CreateRenderPass(
                gVkDevice,
                &rpInfo,
                nullptr,
                &m_swapchainImageContext_renderPassPass[indice]
              ) );
            }

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
            CHECK_VULKANCMD(m_swapchainImageContextNamer[indice].SetName(
              VK_OBJECT_TYPE_RENDER_PASS,
              (uint64_t)m_swapchainImageContext_renderPassPass[indice],
              "helloxr render pass"
            ) );
#endif

            //return true;
          }

          // SwapchainImageContext_SwapchainImageContext_PipelineCreate(
          //   indice,
          //   gVkDevice,
          //   m_swapchainImageContextSize[indice]
          // );
          //
          // void SwapchainImageContext_SwapchainImageContext_PipelineCreate(
          //   int index,
          //   VkDevice device,
          //   VkExtent2D size
          // )
          {
            VkPipelineDynamicStateCreateInfo dynamicState {VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};

            dynamicState.dynamicStateCount =
              (uint32_t)m_swapchainImageContextPipe_pipelineDynamicStateEnables[indice].size();

            dynamicState.pDynamicStates = m_swapchainImageContextPipe_pipelineDynamicStateEnables[indice].data();

            VkPipelineVertexInputStateCreateInfo vi {VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
            vi.vertexBindingDescriptionCount = 1;
            vi.pVertexBindingDescriptions = &gVertexBufferBaseBindDesc;
            vi.vertexAttributeDescriptionCount = (uint32_t)gVertexBufferBaseAttrDesc.size();
            vi.pVertexAttributeDescriptions = gVertexBufferBaseAttrDesc.data();

            VkPipelineInputAssemblyStateCreateInfo ia {VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
            ia.primitiveRestartEnable = VK_FALSE;
            ia.topology = m_swapchainImageContextPipe_pipelineTopology[indice];

            VkPipelineRasterizationStateCreateInfo rs {VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
            rs.polygonMode = VK_POLYGON_MODE_FILL;
            rs.cullMode = VK_CULL_MODE_BACK_BIT;
            rs.frontFace = VK_FRONT_FACE_CLOCKWISE;
            rs.depthClampEnable = VK_FALSE;
            rs.rasterizerDiscardEnable = VK_FALSE;
            rs.depthBiasEnable = VK_FALSE;
            rs.depthBiasConstantFactor = 0;
            rs.depthBiasClamp = 0;
            rs.depthBiasSlopeFactor = 0;
            rs.lineWidth = 1.0f;

#if 0
            VkPipelineColorBlendAttachmentState attachState {};
            attachState.blendEnable = 0;
            attachState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
            attachState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
            attachState.colorBlendOp = VK_BLEND_OP_ADD;
            attachState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
            attachState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
            attachState.alphaBlendOp = VK_BLEND_OP_ADD;
#else
            VkPipelineColorBlendAttachmentState attachState {};
            attachState.blendEnable = 1; // todo
            attachState.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
            attachState.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
            attachState.colorBlendOp = VK_BLEND_OP_ADD;
            //attachState.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
            //attachState.dstAlphaBlendFactor = VK_BLEND_FACTOR_DST_ALPHA;
            attachState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
            attachState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
            attachState.alphaBlendOp = VK_BLEND_OP_MAX;
#endif

            attachState.colorWriteMask =
              VK_COLOR_COMPONENT_R_BIT |
              VK_COLOR_COMPONENT_G_BIT |
              VK_COLOR_COMPONENT_B_BIT |
              VK_COLOR_COMPONENT_A_BIT;

            VkPipelineColorBlendStateCreateInfo cb {VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
            cb.attachmentCount = 1;
            cb.pAttachments = &attachState;
            cb.logicOpEnable = VK_FALSE;
            cb.logicOp = VK_LOGIC_OP_NO_OP;
#if 0
            _operator_assign(cb.blendConstants, 1.0f);
#endif

            VkRect2D scissor =
            {
              {0, 0},
              m_swapchainImageContextSize[indice]
            };

#if defined(ORIGIN_BOTTOM_LEFT)
            // Flipped view so origin is bottom-left like GL (requires VK_KHR_maintenance1)
            VkViewport viewport =
            {
              0.0f,
              (float)m_swapchainImageContextSize[indice].height,
              (float)m_swapchainImageContextSize[indice].width,
              -(float)m_swapchainImageContextSize[indice].height,
              0.0f,
              1.0f
            };
#else
            // Will invert y after projection
            VkViewport viewport =
            {
              0.0f,
              0.0f,
              (float)m_swapchainImageContextSize[indice].width,
              (float)m_swapchainImageContextSize[indice].height,
              0.0f,
              1.0f
            };
#endif

            VkPipelineViewportStateCreateInfo vp {VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
            vp.viewportCount = 1;
            vp.pViewports = &viewport;
            vp.scissorCount = 1;
            vp.pScissors = &scissor;

            VkPipelineDepthStencilStateCreateInfo ds {VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};
            ds.depthTestEnable = VK_TRUE;
            ds.depthWriteEnable = VK_TRUE;
            ds.depthCompareOp = VK_COMPARE_OP_LESS;
            ds.depthBoundsTestEnable = VK_FALSE;
            ds.stencilTestEnable = VK_FALSE;
            ds.front.failOp = VK_STENCIL_OP_KEEP;
            ds.front.passOp = VK_STENCIL_OP_KEEP;
            ds.front.depthFailOp = VK_STENCIL_OP_KEEP;
            ds.front.compareOp = VK_COMPARE_OP_ALWAYS;
            ds.back = ds.front;
            ds.minDepthBounds = 0.0f;
            ds.maxDepthBounds = 1.0f;

            VkPipelineMultisampleStateCreateInfo ms {VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
            ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

            VkGraphicsPipelineCreateInfo pipeInfo {VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
            pipeInfo.stageCount = (uint32_t)gShaderProgramShaderInfo.size();
            pipeInfo.pStages = gShaderProgramShaderInfo.data();
            pipeInfo.pVertexInputState = &vi;
            pipeInfo.pInputAssemblyState = &ia;
            pipeInfo.pTessellationState = nullptr;
            pipeInfo.pViewportState = &vp;
            pipeInfo.pRasterizationState = &rs;
            pipeInfo.pMultisampleState = &ms;
            pipeInfo.pDepthStencilState = &ds;
            pipeInfo.pColorBlendState = &cb;

            if(dynamicState.dynamicStateCount > 0)
              pipeInfo.pDynamicState = &dynamicState;

            pipeInfo.layout = gVkPipelineLayout;
            pipeInfo.renderPass = m_swapchainImageContext_renderPassPass[indice];
            pipeInfo.subpass = 0;

#if 0
            struct VkBindBufferMemoryInfo
            {
              VkStructureType sType;
              const void* pNext;
              VkBuffer buffer;
              VkDeviceMemory memory;
              VkDeviceSize memoryOffset;
            };

            struct VkGraphicsPipelineCreateInfo
            {
              VkStructureType sType;
              const void* pNext;
              VkPipelineCreateFlags flags;
              uint32_t stageCount;
              const VkPipelineShaderStageCreateInfo* pStages;
              const VkPipelineVertexInputStateCreateInfo* pVertexInputState;
              const VkPipelineInputAssemblyStateCreateInfo* pInputAssemblyState;
              const VkPipelineTessellationStateCreateInfo* pTessellationState;
              const VkPipelineViewportStateCreateInfo* pViewportState;
              const VkPipelineRasterizationStateCreateInfo* pRasterizationState;
              const VkPipelineMultisampleStateCreateInfo* pMultisampleState;
              const VkPipelineDepthStencilStateCreateInfo* pDepthStencilState;
              const VkPipelineColorBlendStateCreateInfo* pColorBlendState;
              const VkPipelineDynamicStateCreateInfo* pDynamicState;
              VkPipelineLayout layout;
              VkRenderPass renderPass;
              uint32_t subpass;
              VkPipeline basePipelineHandle;
              int32_t basePipelineIndex;
            };
#endif

// VkResult vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines);
            if(tableVk.CreateGraphicsPipelines)
            {
              CHECK_VULKANCMD(tableVk.CreateGraphicsPipelines(
                gVkDevice,
                VK_NULL_HANDLE,
                1,
                &pipeInfo,
                nullptr,
                &m_swapchainImageContextPipe_pipelinePipe[indice]
              ) );
            }
          }

          // texture 3 of 4 start
          //VkResult CreateDescriptorSet()
          {
            const VkDescriptorPoolSize descriptorPoolSize =
            {
              .type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
              .descriptorCount = OBJ_TEXTURE_COUNT
            };

            const VkDescriptorPoolCreateInfo descriptorPoolCreateInfo =
            {
              .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
              .pNext = nullptr,
              .maxSets = 1,
              .poolSizeCount = 1,
              .pPoolSizes = &descriptorPoolSize
            };

            tableVk.CreateDescriptorPool(gVkDevice, &descriptorPoolCreateInfo, nullptr, &gTextureVkDescriptorPool);

            VkDescriptorSetAllocateInfo descriptorSetAllocateInfo =
            {
              .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
              .pNext = nullptr,
              .descriptorPool = gTextureVkDescriptorPool,
              .descriptorSetCount = 1,
              .pSetLayouts = &gTextureVkDescriptorSetLayout
            };

            tableVk.AllocateDescriptorSets(gVkDevice, &descriptorSetAllocateInfo, &gTextureVkDescriptorSet);

            VkDescriptorImageInfo descriptorImageInfo[OBJ_TEXTURE_COUNT];
            memset(descriptorImageInfo, 0, sizeof(VkDescriptorImageInfo) * OBJ_TEXTURE_COUNT);

            for(int32_t index = 0; index < OBJ_TEXTURE_COUNT; index++)
            {
              descriptorImageInfo[index].sampler = gTextureBlahVk[index].sampler;
              descriptorImageInfo[index].imageView = gTextureBlahVk[index].imageView;
              descriptorImageInfo[index].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL/*VK_IMAGE_LAYOUT_GENERAL*/;
            }

            VkWriteDescriptorSet writeDescriptorSet =
            {
              .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
              .pNext = nullptr,
              .dstSet = gTextureVkDescriptorSet,
              .dstBinding = 2,
              .dstArrayElement = 0,
              .descriptorCount = OBJ_TEXTURE_COUNT,
              .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
              .pImageInfo = descriptorImageInfo,
              .pBufferInfo = nullptr,
              .pTexelBufferView = nullptr
            };

            tableVk.UpdateDescriptorSets(gVkDevice, 1, &writeDescriptorSet, 0, nullptr);

            //return VK_SUCCESS;
          }
          // texture 3 of 4 finish

          m_swapchainImageContextSwapchainImages[indice].resize(capacity);

          m_swapchainImageContextStdVector_renderTargetColorImage[indice].resize(capacity);
          m_swapchainImageContextStdVector_renderTargetDepthImage[indice].resize(capacity);
          m_swapchainImageContextStdVector_renderTargetColorView[indice].resize(capacity);
          m_swapchainImageContextStdVector_renderTargetDepthView[indice].resize(capacity);
          m_swapchainImageContextStdVector_renderTargetFrameBuffer[indice].resize(capacity);

          //std::vector<XrSwapchainImageBaseHeader*> bases(capacity);
          bases.resize(capacity);

          for(uint32_t renderTarget = 0; renderTarget < capacity; renderTarget++)
          {
            m_swapchainImageContextSwapchainImages[indice][renderTarget] =
            {
              m_swapchainImageContextSwapchainImageType[indice]
            };

            bases[renderTarget] =
              reinterpret_cast<XrSwapchainImageBaseHeader*>(
                &m_swapchainImageContextSwapchainImages[indice][renderTarget]
              );
          }

          //return bases;
        }

        // Map every swapchainImage base pointer to this context
        for(auto& base : bases)
          gVulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext[base] = indice;

        swapchainImages = bases;
      }

      if(tableXr.EnumerateSwapchainImages)
      {
        CHECK_XRCMD_CHECK(tableXr.EnumerateSwapchainImages(
          swapchain.handle,
          imageCount,
          &imageCount,
          swapchainImages[0]
        ) );
      }

      gOpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader.insert(
        std::make_pair(swapchain.handle, std::move(swapchainImages) )
      );
    }
  }

  while(app->destroyRequested == 0)
  {
    bool result = false;

    // Read all pending events.
    for(;;)
    {
      int events = 0;
      struct android_poll_source* source = 0;

      // If the timeout is zero, returns immediately without blocking.
      // If the timeout is negative, waits indefinitely until an event appears.
      const int timeoutMilliseconds =
        ( !appState.Resumed && !gOpenXrProgramSessionRunning && app->destroyRequested == 0) ? -1 : 0;

      if(ALooper_pollOnce(timeoutMilliseconds, nullptr, &events, (void**)&source) < 0)
        break;

      // Process this event.
      if(source != nullptr)
        source->process(app, source);
    }

    // OpenXrProgramPollEvents

    exitRenderLoop = false;
    requestRestart = false;

    while( !exitRenderLoop)
    {
      XrEventDataBaseHeader* event = nullptr;

      XrEventDataBaseHeader* baseHeader = reinterpret_cast<XrEventDataBaseHeader*>( &gOpenXrProgramXrEventDataBuffer);
      *baseHeader = {XR_TYPE_EVENT_DATA_BUFFER};

      XrResult xr = XR_ERROR_VALIDATION_FAILURE;

      if(tableXr.PollEvent)
        xr = tableXr.PollEvent(gXrInstance, &gOpenXrProgramXrEventDataBuffer);

      if(xr == XR_SUCCESS)
      {
        if(baseHeader->type == XR_TYPE_EVENT_DATA_EVENTS_LOST)
        {
          const XrEventDataEventsLost* const eventsLost = reinterpret_cast<const XrEventDataEventsLost*>(baseHeader);
          Log::Write(Log::Level::Warning, Fmt("%d events lost", eventsLost->lostEventCount) );
        }

        event = baseHeader;
      }
      else if(xr != XR_EVENT_UNAVAILABLE)
      {
        THROW_XR_CHECK(xr, "xrPollEvent");
      }

      if( !event)
        break;

      switch(event->type)
      {

      case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING:
      {
        const auto& instanceLossPending = *reinterpret_cast<const XrEventDataInstanceLossPending*>(event);
        Log::Write(Log::Level::Warning, Fmt("XrEventDataInstanceLossPending by %lld", instanceLossPending.lossTime) );
        exitRenderLoop = true;
        requestRestart = true;
        break;
      }

      case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED:
      {
        auto sessionStateChangedEvent = *reinterpret_cast<const XrEventDataSessionStateChanged*>(event);

        const XrSessionState oldState = gOpenXrProgramXrSessionState;
        gOpenXrProgramXrSessionState = sessionStateChangedEvent.state;

        Log::Write(
          Log::Level::Info,
          Fmt(
            "XrEventDataSessionStateChanged: state %s->%s session=%lld time=%lld",
            to_string(oldState),
            to_string(gOpenXrProgramXrSessionState),
            sessionStateChangedEvent.session,
            sessionStateChangedEvent.time
          )
        );

        if(sessionStateChangedEvent.session != XR_NULL_HANDLE && sessionStateChangedEvent.session != gXrSession)
        {
          Log::Write(Log::Level::Error, "XrEventDataSessionStateChanged for unknown session");
          break;
        }

        switch(gOpenXrProgramXrSessionState)
        {

        case XR_SESSION_STATE_READY:
        {
          CHECK_CHECK(gXrSession != XR_NULL_HANDLE);

          XrSessionBeginInfo sessionBeginInfo {XR_TYPE_SESSION_BEGIN_INFO};

          sessionBeginInfo.primaryViewConfigurationType = gOptions_XrViewConfigurationType;

          if(tableXr.BeginSession)
            CHECK_XRCMD_CHECK(tableXr.BeginSession(gXrSession, &sessionBeginInfo) );

          gOpenXrProgramSessionRunning = true;

          if(tableXr.PerfSettingsSetPerformanceLevelEXT)
          {

            tableXr.PerfSettingsSetPerformanceLevelEXT(
              gXrSession,
              XR_PERF_SETTINGS_DOMAIN_CPU_EXT,
              XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT
            );

            tableXr.PerfSettingsSetPerformanceLevelEXT(
              gXrSession,
              XR_PERF_SETTINGS_DOMAIN_CPU_EXT,
              XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT
            );

            tableXr.PerfSettingsSetPerformanceLevelEXT(
              gXrSession,
              XR_PERF_SETTINGS_DOMAIN_CPU_EXT,
              XR_PERF_SETTINGS_LEVEL_BOOST_EXT
            );

            tableXr.PerfSettingsSetPerformanceLevelEXT(
              gXrSession,
              XR_PERF_SETTINGS_DOMAIN_GPU_EXT,
              XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT
            );

            tableXr.PerfSettingsSetPerformanceLevelEXT(
              gXrSession,
              XR_PERF_SETTINGS_DOMAIN_GPU_EXT,
              XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT
            );

            tableXr.PerfSettingsSetPerformanceLevelEXT(
              gXrSession,
              XR_PERF_SETTINGS_DOMAIN_GPU_EXT,
              XR_PERF_SETTINGS_LEVEL_BOOST_EXT
            );
          }

          if(tableXr.SetAndroidApplicationThreadKHR)
          {
            CHECK_XRCMD_CHECK(tableXr.SetAndroidApplicationThreadKHR(
              gXrSession,
              XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR,
              gettid()
            ) );

            CHECK_XRCMD_CHECK(tableXr.SetAndroidApplicationThreadKHR(
              gXrSession,
              XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR,
              gettid()
            ) );
          }

          break;
        }

        case XR_SESSION_STATE_STOPPING:
        {
          CHECK_CHECK(gXrSession != XR_NULL_HANDLE);
          gOpenXrProgramSessionRunning = false;

          if(tableXr.EndSession)
            CHECK_XRCMD_CHECK(tableXr.EndSession(gXrSession) );

          break;
        }

        case XR_SESSION_STATE_EXITING:
        {
          exitRenderLoop = true;
          requestRestart = false;
          break;
        }

        case XR_SESSION_STATE_LOSS_PENDING:
        {
          exitRenderLoop = true;
          requestRestart = true;
          break;
        }

        default:
        {
        }
        break;

        }
      }
      break;

      case XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED:
      {
        const int actionSourceNameCount = 5;

        XrAction gOpenXrProgramInputState_InputState_ActionBlah[actionSourceNameCount] =
        {
          gOpenXrProgramInputState_InputState_grabAction,
          gOpenXrProgramInputState_InputState_triggerAction,
          gOpenXrProgramInputState_InputState_quitAction,
          gOpenXrProgramInputState_InputState_poseAction,
          gOpenXrProgramInputState_InputState_vibrateAction
        };

        const std::string actionName[actionSourceNameCount] = {
          "Grab",
          "Trigger",
          "Quit",
          "Pose",
          "Vibrate"
        };

        //void OpenXrProgram_OpenXrProgramLogActionSourceName(XrAction action, const std::string& actionName)
        for(int actionSourceNameIndex = 0; actionSourceNameIndex < actionSourceNameCount; actionSourceNameIndex++)
        {
          XrBoundSourcesForActionEnumerateInfo getInfo = {XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO};

          getInfo.action = gOpenXrProgramInputState_InputState_ActionBlah[actionSourceNameIndex];

          uint32_t pathCount = 0;

          if(tableXr.EnumerateBoundSourcesForAction)
            CHECK_XRCMD_CHECK(tableXr.EnumerateBoundSourcesForAction(gXrSession, &getInfo, 0, &pathCount, nullptr) );

          std::vector<XrPath> paths(pathCount);

          if(tableXr.EnumerateBoundSourcesForAction)
          {
            CHECK_XRCMD_CHECK(tableXr.EnumerateBoundSourcesForAction(
              gXrSession,
              &getInfo,
              uint32_t(paths.size() ),
              &pathCount, paths.data()
            ) );
          }

          std::string sourceName;

          for(uint32_t pathIndex = 0; pathIndex < pathCount; ++pathIndex)
          {
            constexpr XrInputSourceLocalizedNameFlags all =
              XR_INPUT_SOURCE_LOCALIZED_NAME_USER_PATH_BIT |
              XR_INPUT_SOURCE_LOCALIZED_NAME_INTERACTION_PROFILE_BIT |
              XR_INPUT_SOURCE_LOCALIZED_NAME_COMPONENT_BIT;

            XrInputSourceLocalizedNameGetInfo nameInfo = {XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO};

            nameInfo.sourcePath = paths[pathIndex];
            nameInfo.whichComponents = all;

            uint32_t size = 0;

            if(tableXr.GetInputSourceLocalizedName)
              CHECK_XRCMD_CHECK(tableXr.GetInputSourceLocalizedName(gXrSession, &nameInfo, 0, &size, nullptr) );

            if(size < 1)
              continue;

            std::vector<char> grabSource(size);

            if(tableXr.GetInputSourceLocalizedName)
            {
              CHECK_XRCMD_CHECK(tableXr.GetInputSourceLocalizedName(
                gXrSession,
                &nameInfo,
                uint32_t(grabSource.size() ),
                &size,
                grabSource.data()
              ) );
            }

            if( !sourceName.empty() )
              sourceName += " and ";

            sourceName += "'";
            sourceName += std::string(grabSource.data(), size - 1);

            sourceName += "'";
          }

          Log::Write(
            Log::Level::Info,
            Fmt(
              "%s action is bound to %s",
              actionName[actionSourceNameIndex].c_str(),
              ( ( !sourceName.empty() ) ? sourceName.c_str() : "nothing")
            )
          );
        }
      }
      break;

      case XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING:
      default:
      {
        Log::Write(Log::Level::Verbose, Fmt("Ignoring event type %d", event->type) );
      }
      break;

      }
    }

    if(exitRenderLoop)
    {
      ANativeActivity_finish(app->activity);
      continue;
    }

    if( !gOpenXrProgramSessionRunning)
    {
      // Throttle loop since xrWaitFrame won't be called.
      std::this_thread::sleep_for(std::chrono::milliseconds(250) );
      continue;
    }

    // OpenXrProgramPollActions

    gOpenXrProgramInputState_InputState_handActive = {XR_FALSE, XR_FALSE};

    // Sync actions
    const XrActiveActionSet activeActionSet {gOpenXrProgramInputState_InputState_actionSet, XR_NULL_PATH};

    XrActionsSyncInfo syncInfo {XR_TYPE_ACTIONS_SYNC_INFO};
    syncInfo.countActiveActionSets = 1;
    syncInfo.activeActionSets = &activeActionSet;

    if(tableXr.SyncActions)
      CHECK_XRCMD_CHECK(tableXr.SyncActions(gXrSession, &syncInfo) );

    // Get pose and grab action state and start haptic vibrate when hand is 90% squeezed.
    for(auto hand : {Side_LEFT, Side_RIGHT} )
    {
      XrActionStateFloat grabValue {XR_TYPE_ACTION_STATE_FLOAT};
      {
        XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO};
        getInfo.action = gOpenXrProgramInputState_InputState_grabAction;
        getInfo.subactionPath = gOpenXrProgramInputState_InputState_handSubactionPath[hand];

        if(tableXr.GetActionStateFloat)
          CHECK_XRCMD_CHECK(tableXr.GetActionStateFloat(gXrSession, &getInfo, &grabValue) );
      }

      XrActionStateFloat triggerValue {XR_TYPE_ACTION_STATE_FLOAT};
      {
        XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO};
        getInfo.action = gOpenXrProgramInputState_InputState_triggerAction;
        getInfo.subactionPath = gOpenXrProgramInputState_InputState_handSubactionPath[hand];

        if(tableXr.GetActionStateFloat)
          CHECK_XRCMD_CHECK(tableXr.GetActionStateFloat(gXrSession, &getInfo, &triggerValue) );
      }

      if(grabValue.isActive == XR_TRUE || triggerValue.isActive == XR_TRUE)
      {
        // Scale the rendered hand by 1.0f (open) to 2.0f (fully squeezed)

        gOpenXrProgramInputState_InputState_handScale[hand] = 1.0f;

        if(grabValue.isActive)
          gOpenXrProgramInputState_InputState_handScale[hand] *= 1.0 + 1.0 * grabValue.currentState;

        if(triggerValue.isActive)
          gOpenXrProgramInputState_InputState_handScale[hand] *= 1.0 + 1.0 * triggerValue.currentState;

        if(grabValue.currentState > 0.9f)
        {
          XrHapticVibration vibration {XR_TYPE_HAPTIC_VIBRATION};
          vibration.amplitude = 0.5;
          vibration.duration = XR_MIN_HAPTIC_DURATION;
          vibration.frequency = XR_FREQUENCY_UNSPECIFIED;

          XrHapticActionInfo hapticActionInfo {XR_TYPE_HAPTIC_ACTION_INFO};
          hapticActionInfo.action = gOpenXrProgramInputState_InputState_vibrateAction;
          hapticActionInfo.subactionPath = gOpenXrProgramInputState_InputState_handSubactionPath[hand];

// turn off haptic feedback for now (it's annoying)
#if 0
          if(tableXr.ApplyHapticFeedback)
          {
            CHECK_XRCMD_CHECK(tableXr.ApplyHapticFeedback(
              gXrSession,
              &hapticActionInfo,
              (XrHapticBaseHeader*) &vibration
            ) );
          }
#endif

        }
      }

      XrActionStatePose poseState {XR_TYPE_ACTION_STATE_POSE};
      {
        XrActionStateGetInfo getInfo {XR_TYPE_ACTION_STATE_GET_INFO};
        getInfo.action = gOpenXrProgramInputState_InputState_poseAction;
        getInfo.subactionPath = gOpenXrProgramInputState_InputState_handSubactionPath[hand];

        if(tableXr.GetActionStatePose)
          CHECK_XRCMD_CHECK(tableXr.GetActionStatePose(gXrSession, &getInfo, &poseState) );
      }

      gOpenXrProgramInputState_InputState_handActive[hand] = poseState.isActive;
    }

    // There were no subaction paths specified for the quit action, because we don't care which hand did it.
    XrActionStateGetInfo getInfo
    {
      XR_TYPE_ACTION_STATE_GET_INFO,
      nullptr,
      gOpenXrProgramInputState_InputState_quitAction,
      XR_NULL_PATH
    };

    XrActionStateBoolean quitValue {XR_TYPE_ACTION_STATE_BOOLEAN};

    if(tableXr.GetActionStateBoolean)
      CHECK_XRCMD_CHECK(tableXr.GetActionStateBoolean(gXrSession, &getInfo, &quitValue) );

    if(
      quitValue.isActive == XR_TRUE &&
      quitValue.changedSinceLastSync == XR_TRUE &&
      quitValue.currentState == XR_TRUE &&
      tableXr.RequestExitSession
    )
    {
      CHECK_XRCMD_CHECK(tableXr.RequestExitSession(gXrSession) );
    }

    // OpenXrProgramRenderFrame

    CHECK_CHECK(gXrSession != XR_NULL_HANDLE);

    XrFrameWaitInfo frameWaitInfo {XR_TYPE_FRAME_WAIT_INFO};
    XrFrameState frameState {XR_TYPE_FRAME_STATE};

    if(tableXr.WaitFrame)
      CHECK_XRCMD_CHECK(tableXr.WaitFrame(gXrSession, &frameWaitInfo, &frameState) );

    XrFrameBeginInfo frameBeginInfo {XR_TYPE_FRAME_BEGIN_INFO};

    if(tableXr.BeginFrame)
      CHECK_XRCMD_CHECK(tableXr.BeginFrame(gXrSession, &frameBeginInfo) );

    std::vector<XrCompositionLayerBaseHeader*> layers_vector;
    XrCompositionLayerProjection layer {XR_TYPE_COMPOSITION_LAYER_PROJECTION};
    std::vector<XrCompositionLayerProjectionView> projectionLayerViews;

    if(frameState.shouldRender == XR_TRUE)
    {
      XrTime predictedDisplayTime = frameState.predictedDisplayTime;

      //bool renderLayerResult = OpenXrProgram_OpenXrProgramRenderLayer(
      //  frameState.predictedDisplayTime,
      //  projectionLayerViews,
      //  layer
      //);
      bool renderLayerResult = false;

      //bool OpenXrProgram_OpenXrProgramRenderLayer(
      //  XrTime predictedDisplayTime,
      //  std::vector<XrCompositionLayerProjectionView>& projectionLayerViews,
      //  XrCompositionLayerProjection& layer
      //)

      do
      {
        XrResult renderLayerXrResult = XR_ERROR_VALIDATION_FAILURE;

        XrViewState renderLayerViewState {XR_TYPE_VIEW_STATE};
        uint32_t renderLayerViewCapacityInput = (uint32_t)gOpenXrProgramStdVector_XrView.size();
        uint32_t renderLayerViewCountOutput = 0;

        XrViewLocateInfo viewLocateInfo {XR_TYPE_VIEW_LOCATE_INFO};
        viewLocateInfo.viewConfigurationType = gOptions_XrViewConfigurationType;
        viewLocateInfo.displayTime = predictedDisplayTime;
        viewLocateInfo.space = gOpenXrProgramXrSpace;

        if(tableXr.LocateViews)
        {
          renderLayerXrResult = tableXr.LocateViews(
            gXrSession,
            &viewLocateInfo,
            &renderLayerViewState,
            renderLayerViewCapacityInput,
            &renderLayerViewCountOutput,
            gOpenXrProgramStdVector_XrView.data()
          );

          CHECK_XRRESULT(renderLayerXrResult, "xrLocateViews");
        }

        if(
          (renderLayerViewState.viewStateFlags & XR_VIEW_STATE_POSITION_VALID_BIT) == 0 ||
          (renderLayerViewState.viewStateFlags & XR_VIEW_STATE_ORIENTATION_VALID_BIT) == 0
        )
        {
          break; // There is no valid tracking poses for the views.
        }

        CHECK_CHECK(renderLayerViewCountOutput == renderLayerViewCapacityInput);
        CHECK_CHECK(renderLayerViewCountOutput == gOpenXrProgramStdVector_XrViewConfigurationView.size() );
        CHECK_CHECK(renderLayerViewCountOutput == gOpenXrProgramStdVector_Swapchain.size() );

        projectionLayerViews.resize(renderLayerViewCountOutput);

        // For each locatable space that we want to visualize, render a model.  The scale base is ~25cm
        std::vector<Model> models;

        for(XrSpace visualizedSpace : gOpenXrProgramStdVector_XrSpace)
        {
          XrSpaceLocation spaceLocation {XR_TYPE_SPACE_LOCATION};

          if(tableXr.LocateSpace)
          {
            renderLayerXrResult = tableXr.LocateSpace(
              visualizedSpace,
              gOpenXrProgramXrSpace,
              predictedDisplayTime,
              &spaceLocation
            );

            CHECK_XRRESULT(renderLayerXrResult, "xrLocateSpace");
          }

          if(XR_UNQUALIFIED_SUCCESS(renderLayerXrResult) )
          {
            if(
              (spaceLocation.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0 &&
              (spaceLocation.locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT) != 0
            )
            {
#if 0
              //models.push_back(Model {257, spaceLocation.pose, {0.25f, 0.25f, 0.25f} } );
              models.push_back(Model {256, spaceLocation.pose, {0.25f, 0.25f, 0.25f} } );
#endif
            }
          }
          else
          {
            Log::Write(
              Log::Level::Verbose,
              Fmt("Unable to locate a visualized reference space in app space: %d", renderLayerXrResult)
            );
          }
        }

        // Render a model scaled by grabAction for each hand. Note renderHand will only be
        // true when the application has focus.  The scale base is ~10cm
        for(auto hand : {Side_LEFT, Side_RIGHT} )
        {
          XrSpaceLocation spaceLocation {XR_TYPE_SPACE_LOCATION};

          if(tableXr.LocateSpace)
          {
            renderLayerXrResult = tableXr.LocateSpace(
              gOpenXrProgramInputState_InputState_handSpace[hand],
              gOpenXrProgramXrSpace,
              predictedDisplayTime,
              &spaceLocation
            );

            CHECK_XRRESULT(renderLayerXrResult, "xrLocateSpace");
          }

          if(XR_UNQUALIFIED_SUCCESS(renderLayerXrResult) )
          {
            if(
              (spaceLocation.locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT) != 0 &&
              (spaceLocation.locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT) != 0
            )
            {
#if 0
              float scale = (0.125 / 32.0) * gOpenXrProgramInputState_InputState_handScale[hand];

              //char testString[] = "omg Hello World!";
              //char countOfTestString = strlen(testString);

              spaceLocation.pose.position.x -= 8.0 * (8.0 * scale);

              spaceLocation.pose.position.y += 8.0 * (1.5 * 8.0 * scale);

              for(uint32_t indexCharacter = 0; indexCharacter < 256; indexCharacter++)
              {
                //if(hand == Side_LEFT)
                {
                  // R o   b  e  r  t   [heart] T a  r a
                  // 7 12  10 11 13 14     6    8 9 13 9

                  //if(indexCharacter == 1 || indexCharacter == 33)
                  //  spaceLocation.pose.position.x -= 8.0 * scale;

                  if(indexCharacter && (indexCharacter % 16) == 0)
                  {
                    spaceLocation.pose.position.x -= 16.0 * (8.0 * scale);

                    spaceLocation.pose.position.y -= 1.5 * 8.0 * scale;
                  }

                  models.push_back(Model {indexCharacter/*testString[indexCharacter]*/, spaceLocation.pose, {scale, scale, scale} } );

                  spaceLocation.pose.position.x += 8.0 * scale;
                }
                //else
                //{
                  //models.push_back(Model {256, spaceLocation.pose, {scale, scale, scale} } );
                //  models.push_back(Model {260, spaceLocation.pose, {scale, scale, scale} } );
                //}
              }
#else
              float scale = gOpenXrProgramInputState_InputState_handScale[hand] / OBJ_HAND_SCALE;

              spaceLocation.pose.position.x += OBJ_HAND_TRANSLATE_X;
              spaceLocation.pose.position.y += OBJ_HAND_TRANSLATE_Y;
              spaceLocation.pose.position.z += OBJ_HAND_TRANSLATE_Z;

              models.push_back(Model {256, spaceLocation.pose, {scale, scale, scale} } );
#endif
            }
          }
          else
          {
            // Tracking loss is expected when the hand is not active so only log a message
            // if the hand is active.
            if(gOpenXrProgramInputState_InputState_handActive[hand] == XR_TRUE)
            {
              const char* handName[] = {"left", "right"};

              Log::Write(
                Log::Level::Verbose,
                Fmt("Unable to locate %s hand action space in app space: %d", handName[hand], renderLayerXrResult)
              );
            }
          }
        }

        // Render view to the appropriate part of the swapchain image.
        for(uint32_t i = 0; i < renderLayerViewCountOutput; i++)
        {
          // Each view has a separate swapchain which is acquired, rendered to, and released.
          const Swapchain viewSwapchain = gOpenXrProgramStdVector_Swapchain[i];

          XrSwapchainImageAcquireInfo acquireInfo {XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO};

          uint32_t swapchainImageIndex = 0;

          if(tableXr.AcquireSwapchainImage)
            CHECK_XRCMD_CHECK(tableXr.AcquireSwapchainImage(viewSwapchain.handle, &acquireInfo, &swapchainImageIndex) );

          XrSwapchainImageWaitInfo waitInfo {XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO};
          waitInfo.timeout = XR_INFINITE_DURATION;

          if(tableXr.WaitSwapchainImage)
            CHECK_XRCMD_CHECK(tableXr.WaitSwapchainImage(viewSwapchain.handle, &waitInfo) );

          projectionLayerViews[i] = {XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW};
          projectionLayerViews[i].pose = gOpenXrProgramStdVector_XrView[i].pose;
          projectionLayerViews[i].fov = gOpenXrProgramStdVector_XrView[i].fov;
          projectionLayerViews[i].subImage.swapchain = viewSwapchain.handle;
          projectionLayerViews[i].subImage.imageRect.offset = {0, 0};
          projectionLayerViews[i].subImage.imageRect.extent = {viewSwapchain.width, viewSwapchain.height};

          const XrSwapchainImageBaseHeader* const swapchainImage =
            gOpenXrProgramStdMap_XrSwapchain_StdVectorXrSwapchainImageBaseHeader
              [viewSwapchain.handle][swapchainImageIndex];

          // void VulkanGraphicsPlugin_VulkanGraphicsPluginRenderView(
          //   const XrCompositionLayerProjectionView& layerView,
          //   const XrSwapchainImageBaseHeader* swapchainImage,
          //   int64_t /*swapchainFormat*/, const std::vector<Model>& models)
          //
          // VulkanGraphicsPlugin_VulkanGraphicsPluginRenderView(
          //   projectionLayerViews[i],
          //   swapchainImage,
          //   gOpenXrProgramColorSwapchainFormat,
          //   models
          // );
          {
            CHECK_CHECK(projectionLayerViews[i].subImage.imageArrayIndex == 0); // Texture arrays not supported.

            int swapchainContextIndex =
              gVulkanGraphicsPluginStdMap_XrSwapchainImageBaseHeader_SwapchainImageContext[swapchainImage];

            uint32_t renderTarget = 0;
            // uint32_t renderTarget = SwapchainImageContext_SwapchainImageContextImageIndex(
            //   swapchainContextIndex,
            //   swapchainImage
            // );
            //
            // uint32_t SwapchainImageContext_SwapchainImageContextImageIndex(
            //   int index,
            //   const XrSwapchainImageBaseHeader* swapchainImageHeader
            // )
            {
              auto p = reinterpret_cast<const XrSwapchainImageVulkan2KHR*>(swapchainImage);
              renderTarget = (uint32_t)(p - &m_swapchainImageContextSwapchainImages[swapchainContextIndex][0] );
            }

            // XXX Should double-buffer the command buffers, for now just flush
            //
            // CmdBuffer_CmdBufferWait();
            //
            // bool CmdBuffer_CmdBufferWait()
            do
            {
              // Waiting on a not-in-flight command buffer is a no-op
              if(gCmdBufferState == CmdBufferStateEnum::Initialized)
                break;

              //CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Executing);
              if(gCmdBufferState != CmdBufferStateEnum::Executing)
              {
                Log::Write(
                  Log::Level::Error,
                  std::string("Expecting state CmdBufferStateEnum::Executing from ") +
                    __FUNCTION__ +
                    ", in " +
                    CmdBuffer_CmdBufferStateString(gCmdBufferState)
                );

                break;
              }

              const uint32_t timeoutNs = 1 * 1000 * 1000 * 1000;

              for(int wompa = 0; wompa < 5; ++wompa)
              {
                VkResult res = VK_ERROR_OUT_OF_HOST_MEMORY;

                if(tableVk.WaitForFences)
                  res = tableVk.WaitForFences(gVkDevice, 1, &gCmdBufferExecFence, VK_TRUE, timeoutNs);

                if(res == VK_SUCCESS)
                {
                  // Buffer can be executed multiple times...
                  gCmdBufferState = CmdBufferStateEnum::Executable;
                  break;
                }

                Log::Write(Log::Level::Info, "Waiting for CmdBuffer fence timed out, retrying...");
              }

              //return false;

            }while(0);

            //CmdBuffer_CmdBufferReset();
            //bool CmdBuffer_CmdBufferReset()
            do
            {
              if(gCmdBufferState != CmdBufferStateEnum::Initialized)
              {
                //CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Executable);
                if(gCmdBufferState != CmdBufferStateEnum::Executable)
                {
                  Log::Write(
                    Log::Level::Error,
                    std::string("Expecting state CmdBufferStateEnum::Executable from ") +
                      __FUNCTION__ +
                      ", in " +
                      CmdBuffer_CmdBufferStateString(gCmdBufferState)
                  );

                  break;
                }

                if(tableVk.ResetFences)
                  CHECK_VULKANCMD(tableVk.ResetFences(gVkDevice, 1, &gCmdBufferExecFence) );

                if(tableVk.ResetCommandBuffer)
                  CHECK_VULKANCMD(tableVk.ResetCommandBuffer(gCmdBufferBuffer, 0) );

                gCmdBufferState = CmdBufferStateEnum::Initialized;
              }

            }while(0);

            //CmdBuffer_CmdBufferBegin();
            //bool CmdBuffer_CmdBufferBegin()
            do
            {
              //CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Initialized);
              if(gCmdBufferState != CmdBufferStateEnum::Initialized)
              {
                Log::Write(
                  Log::Level::Error,
                  std::string("Expecting state CmdBufferStateEnum::Initialized from ") +
                    __FUNCTION__ +
                    ", in " +
                    CmdBuffer_CmdBufferStateString(gCmdBufferState)
                );

                break;
              }

              VkCommandBufferBeginInfo cmdBeginInfo {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};

              if(tableVk.BeginCommandBuffer)
                CHECK_VULKANCMD(tableVk.BeginCommandBuffer(gCmdBufferBuffer, &cmdBeginInfo) );

              gCmdBufferState = CmdBufferStateEnum::Recording;

              //return true;

            }while(0);

            // Ensure depth is in the right layout
            //
            // SwapchainImageContext_SwapchainImageContext_DepthBufferTransitionImageLayout(
            //   swapchainContextIndex,
            //   VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
            // );
            //
            // void SwapchainImageContext_SwapchainImageContext_DepthBufferTransitionImageLayout(
            //   int index,
            //   VkImageLayout newLayout
            // )
            do
            {
              VkImageLayout newLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

              if(newLayout == m_swapchainImageContext_depthBufferVkImageLayout[swapchainContextIndex] )
                break;

              VkImageMemoryBarrier depthBarrier {VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER};
              depthBarrier.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
              depthBarrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
              depthBarrier.oldLayout = m_swapchainImageContext_depthBufferVkImageLayout[swapchainContextIndex];
              depthBarrier.newLayout = newLayout;
              depthBarrier.image = m_swapchainImageContext_depthBufferDepthImage[swapchainContextIndex];

              depthBarrier.subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1};

              if(tableVk.CmdPipelineBarrier)
              {
                tableVk.CmdPipelineBarrier(
                  gCmdBufferBuffer,
                  VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
                  VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
                  0,
                  0,
                  nullptr,
                  0,
                  nullptr,
                  1,
                  &depthBarrier
                );
              }

              m_swapchainImageContext_depthBufferVkImageLayout[swapchainContextIndex] = newLayout;

            }while(0);

            // Bind and clear eye render target
            static std::array<VkClearValue, 2> clearValues;

            _operator_assign(clearValues[0].color.float32, gVulkanGraphicsPluginStdArray_float_4_clearColor);
            clearValues[1].depthStencil.depth = 1.0f;
            clearValues[1].depthStencil.stencil = 0;

            VkRenderPassBeginInfo renderPassBeginInfo {VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};

            renderPassBeginInfo.clearValueCount = (uint32_t)clearValues.size();
            renderPassBeginInfo.pClearValues = clearValues.data();

            // SwapchainImageContext_SwapchainImageContextBindRenderTarget(
            //   swapchainContextIndex,
            //   renderTarget,
            //   &renderPassBeginInfo
            // );
            //
            // void SwapchainImageContext_SwapchainImageContextBindRenderTarget(
            //   int index,
            //   uint32_t renderTarget,
            //   VkRenderPassBeginInfo* renderPassBeginInfo
            // )
            {
              if(
                m_swapchainImageContextStdVector_renderTargetFrameBuffer[swapchainContextIndex][renderTarget] ==
                  VK_NULL_HANDLE
              )
              // SwapchainImageContext_SwapchainImageContext_RenderTargetCreate(
              //   swapchainContextIndex,
              //   renderTarget,
              //   m_swapchainImageContextNamer[swapchainContextIndex],
              //   gVkDevice,
              //   m_swapchainImageContextSwapchainImages[swapchainContextIndex][renderTarget].image,
              //   m_swapchainImageContext_depthBufferDepthImage[swapchainContextIndex],
              //   m_swapchainImageContextSize[swapchainContextIndex]
              // );
              //
              // void SwapchainImageContext_SwapchainImageContext_RenderTargetCreate(
              //   int index,
              //   int renderTarget,
              //   const VulkanDebugObjectNamer& namer,
              //   VkDevice device,
              //   VkImage aColorImage,
              //   VkImage aDepthImage,
              //   VkExtent2D size
              // )
              do
              {
                m_swapchainImageContextStdVector_renderTargetColorImage[swapchainContextIndex][renderTarget] =
                  m_swapchainImageContextSwapchainImages[swapchainContextIndex][renderTarget].image;

                m_swapchainImageContextStdVector_renderTargetDepthImage[swapchainContextIndex][renderTarget] =
                  m_swapchainImageContext_depthBufferDepthImage[swapchainContextIndex];

                std::array<VkImageView, 2> attachments {};

                uint32_t attachmentCount = 0;

                // Create color image view
                if(
                  m_swapchainImageContextStdVector_renderTargetColorImage[swapchainContextIndex][renderTarget] !=
                    VK_NULL_HANDLE
                )
                {
                  VkImageViewCreateInfo colorViewInfo {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};

                  colorViewInfo.image =
                    m_swapchainImageContextStdVector_renderTargetColorImage[swapchainContextIndex][renderTarget];

                  colorViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                  colorViewInfo.format = m_swapchainImageContext_renderPassColorFmt[swapchainContextIndex];
                  colorViewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
                  colorViewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
                  colorViewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
                  colorViewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
                  colorViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                  colorViewInfo.subresourceRange.baseMipLevel = 0;
                  colorViewInfo.subresourceRange.levelCount = 1;
                  colorViewInfo.subresourceRange.baseArrayLayer = 0;
                  colorViewInfo.subresourceRange.layerCount = 1;

                  if(tableVk.CreateImageView)
                  {
                    VkImageView renderTargetColorView {VK_NULL_HANDLE};

                    CHECK_VULKANCMD(tableVk.CreateImageView(
                      gVkDevice,
                      &colorViewInfo,
                      nullptr,
                      &renderTargetColorView
                    ) );

                    m_swapchainImageContextStdVector_renderTargetColorView[swapchainContextIndex][renderTarget] =
                      renderTargetColorView;
                  }

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
                  CHECK_VULKANCMD(m_swapchainImageContextNamer[swapchainContextIndex].SetName(
                    VK_OBJECT_TYPE_IMAGE_VIEW,
                    (uint64_t)m_swapchainImageContextStdVector_renderTargetColorView
                      [swapchainContextIndex][renderTarget],
                    "helloxr color image view"
                  ) );
#endif

                  attachments[attachmentCount++] =
                    m_swapchainImageContextStdVector_renderTargetColorView[swapchainContextIndex][renderTarget];
                }

                // Create depth image view
                if(
                  m_swapchainImageContextStdVector_renderTargetDepthImage[swapchainContextIndex][renderTarget] !=
                    VK_NULL_HANDLE
                )
                {
                  VkImageViewCreateInfo depthViewInfo {VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};

                  depthViewInfo.image =
                    m_swapchainImageContextStdVector_renderTargetDepthImage[swapchainContextIndex][renderTarget];

                  depthViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                  depthViewInfo.format = m_swapchainImageContext_renderPassDepthFmt[swapchainContextIndex];
                  depthViewInfo.components.r = VK_COMPONENT_SWIZZLE_R;
                  depthViewInfo.components.g = VK_COMPONENT_SWIZZLE_G;
                  depthViewInfo.components.b = VK_COMPONENT_SWIZZLE_B;
                  depthViewInfo.components.a = VK_COMPONENT_SWIZZLE_A;
                  depthViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
                  depthViewInfo.subresourceRange.baseMipLevel = 0;
                  depthViewInfo.subresourceRange.levelCount = 1;
                  depthViewInfo.subresourceRange.baseArrayLayer = 0;
                  depthViewInfo.subresourceRange.layerCount = 1;

                  if(tableVk.CreateImageView)
                  {
                    VkImageView renderTargetDepthView {VK_NULL_HANDLE};

                    CHECK_VULKANCMD(tableVk.CreateImageView(
                      gVkDevice,
                      &depthViewInfo,
                      nullptr,
                      &renderTargetDepthView
                    ) );

                    m_swapchainImageContextStdVector_renderTargetDepthView[swapchainContextIndex][renderTarget] =
                      renderTargetDepthView;
                  }

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
                  CHECK_VULKANCMD(m_swapchainImageContextNamer[swapchainContextIndex].SetName(
                    VK_OBJECT_TYPE_IMAGE_VIEW,
                    (uint64_t)m_swapchainImageContextStdVector_renderTargetDepthView
                      [swapchainContextIndex][renderTarget],
                    "helloxr depth image view"
                  ) );
#endif

                  attachments[attachmentCount++] =
                    m_swapchainImageContextStdVector_renderTargetDepthView[swapchainContextIndex][renderTarget];
                }

                VkFramebufferCreateInfo fbInfo {VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};

                fbInfo.renderPass = m_swapchainImageContext_renderPassPass[swapchainContextIndex];
                fbInfo.attachmentCount = attachmentCount;
                fbInfo.pAttachments = attachments.data();
                fbInfo.width = m_swapchainImageContextSize[swapchainContextIndex].width;
                fbInfo.height = m_swapchainImageContextSize[swapchainContextIndex].height;
                fbInfo.layers = 1;

                if(tableVk.CreateFramebuffer)
                {
                  VkFramebuffer renderTargetFrameBuffer {VK_NULL_HANDLE};

                  CHECK_VULKANCMD(tableVk.CreateFramebuffer(gVkDevice, &fbInfo, nullptr, &renderTargetFrameBuffer) );

                  m_swapchainImageContextStdVector_renderTargetFrameBuffer[swapchainContextIndex][renderTarget] =
                    renderTargetFrameBuffer;
                }

#if defined(VULKAN_DEBUG_OBJECT_NAMER)
                CHECK_VULKANCMD(m_swapchainImageContextNamer[swapchainContextIndex].SetName(
                  VK_OBJECT_TYPE_FRAMEBUFFER,
                  (uint64_t)m_swapchainImageContextStdVector_renderTargetFrameBuffer
                    [swapchainContextIndex][renderTarget],
                  "helloxr framebuffer"
                ) );
#endif

              }while(0);

              renderPassBeginInfo.renderPass = m_swapchainImageContext_renderPassPass[swapchainContextIndex];

              renderPassBeginInfo.framebuffer =
                m_swapchainImageContextStdVector_renderTargetFrameBuffer[swapchainContextIndex][renderTarget];

              renderPassBeginInfo.renderArea.offset = {0, 0};

              renderPassBeginInfo.renderArea.extent = m_swapchainImageContextSize[swapchainContextIndex];
            }

            // todo

            if(tableVk.CmdBeginRenderPass)
              tableVk.CmdBeginRenderPass(gCmdBufferBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

            if(tableVk.CmdBindPipeline)
            {
              tableVk.CmdBindPipeline(
                gCmdBufferBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                m_swapchainImageContextPipe_pipelinePipe[swapchainContextIndex]
              );
            }

            // texture 4 of 4 start
            if(tableVk.CmdBindDescriptorSets)
            {
              tableVk.CmdBindDescriptorSets(
                gCmdBufferBuffer,
                VK_PIPELINE_BIND_POINT_GRAPHICS,
                gVkPipelineLayout,
                0,
                1,
                &gTextureVkDescriptorSet,
                0,
                nullptr
              );
            }
            // texture 4 of 4 finish

            // Bind indice and vertex buffers
            if(tableVk.CmdBindIndexBuffer)
              tableVk.CmdBindIndexBuffer(gCmdBufferBuffer, gVertexBufferBaseIdxBuf, 0, VK_INDEX_TYPE_UINT32);

            VkDeviceSize offset = 0;

            if(tableVk.CmdBindVertexBuffers)
              tableVk.CmdBindVertexBuffers(gCmdBufferBuffer, 0, 1, &gVertexBufferBaseVtxBuf, &offset);

            // Compute the view-projection transform.
            // Note all matrixes (including OpenXR's) are column-major, right-handed.
            const auto& pose = projectionLayerViews[i].pose;

            XrMatrix4x4f projectionMatrix;
            XrMatrix4x4f_CreateProjectionFov( &projectionMatrix, GRAPHICS_VULKAN, projectionLayerViews[i].fov, 0.05f, 100.0f);

            XrMatrix4x4f toView;
            XrMatrix4x4f_CreateFromRigidTransform( &toView, &pose);

            XrMatrix4x4f viewMatrix;
            XrMatrix4x4f_InvertRigidBody( &viewMatrix, &toView);

            XrMatrix4x4f viewProjectionMatrix;
            XrMatrix4x4f_Multiply( &viewProjectionMatrix, &projectionMatrix, &viewMatrix);

            bool foundHeart = false;

            // render each model
            for(const Model& model : models)
            {
              // compute the model-view-projection transform and push it
              XrMatrix4x4f blahModelMatrix;

              XrMatrix4x4f_CreateTranslationRotationScale(
                &blahModelMatrix,
                &model.Pose.position,
                &model.Pose.orientation,
                &model.Scale
              );

              XrMatrix4x4f modelViewProjectionMatrix;
              XrMatrix4x4f_Multiply( &modelViewProjectionMatrix, &viewProjectionMatrix, &blahModelMatrix);

              XrMatrix4x4f modelViewMatrix;
              XrMatrix4x4f_Multiply( &modelViewMatrix, &viewMatrix, &blahModelMatrix);

              // void XrMatrix4x4f_Invert(XrMatrix4x4f* result, const XrMatrix4x4f* src)
              //
              // void XrMatrix4x4f_Transpose(XrMatrix4x4f* result, const XrMatrix4x4f* src)
              //
              // transpose(inverse(mat3(viewMatrix) ) )
              //
              // inverse_viewMatrix
              //
              // transpose_inverse_viewMatrix

              XrMatrix4x4f inverse_modelViewMatrix;
              XrMatrix4x4f_Invert( &inverse_modelViewMatrix, &modelViewMatrix);

              XrMatrix4x4f transpose_inverse_modelViewMatrix;
              XrMatrix4x4f_Transpose( &transpose_inverse_modelViewMatrix, &inverse_modelViewMatrix);

              MatrixCmdPushConstants cmdPushConstants {modelViewProjectionMatrix, transpose_inverse_modelViewMatrix, modelViewMatrix};

#if 0
              if( !foundHeart && model.whoAmI != 6)
              {
                cmdPushConstants.modelColor.x = 0.529;
                cmdPushConstants.modelColor.y = 0.808;
                cmdPushConstants.modelColor.z = 0.922;
              }
              else if( !foundHeart && model.whoAmI == 6)
              {
                cmdPushConstants.modelColor.x = 1.0;
                cmdPushConstants.modelColor.y = 0.0;
                cmdPushConstants.modelColor.z = 0.0;

                foundHeart = true;
              }
              else if(foundHeart)
              {
                cmdPushConstants.modelColor.x = 143.0 / 255.0;
                cmdPushConstants.modelColor.y = 0.0;
                cmdPushConstants.modelColor.z = 1.0;

                foundHeart = true;
              }
#else
              cmdPushConstants.modelColor.x = 1.0;
              cmdPushConstants.modelColor.y = 1.0;
              cmdPushConstants.modelColor.z = 1.0;
#endif

              if(tableVk.CmdPushConstants)
              {
                tableVk.CmdPushConstants(
                  gCmdBufferBuffer,
                  gVkPipelineLayout,
                  VK_SHADER_STAGE_VERTEX_BIT,
                  0,
                  sizeof(MatrixCmdPushConstants),
                  &cmdPushConstants
                );
              }

              // draw the model

// void vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance);

              if(tableVk.CmdDrawIndexed)
              {
                // arrow 0 96
                if(model.whoAmI == 257)
                  tableVk.CmdDrawIndexed(gCmdBufferBuffer, 96/*gVertexBufferBaseCount.idx*//*indexCount*/, 1/*instanceCount*/, 0/*firstIndex*/, 0/*vertexOffset*/, 0/*firstInstance*/);

                // cube 96 72
                if(model.whoAmI == 258)
                  tableVk.CmdDrawIndexed(gCmdBufferBuffer, 72/*gVertexBufferBaseCount.idx*//*indexCount*/, 1/*instanceCount*/, 96/*firstIndex*/, 0/*vertexOffset*/, 0/*firstInstance*/);

                // 'Z'
                if(model.whoAmI == 259)
                  tableVk.CmdDrawIndexed(gCmdBufferBuffer, 132/*gVertexBufferBaseCount.idx*//*indexCount*/, 1/*instanceCount*/, 168/*firstIndex*/, 167/*vertexOffset*/, 0/*firstInstance*/);

                if(model.whoAmI == 260)
                {
                  tableVk.CmdDrawIndexed(gCmdBufferBuffer, 228/*gVertexBufferBaseCount.idx*//*indexCount*/, 1/*instanceCount*/, 300/*firstIndex*/, 192/*vertexOffset*/, 0/*firstInstance*/);

                  tableVk.CmdDrawIndexed(gCmdBufferBuffer, 228/*gVertexBufferBaseCount.idx*//*indexCount*/, 1/*instanceCount*/, 528/*firstIndex*/, 273/*vertexOffset*/, 0/*firstInstance*/);

                  tableVk.CmdDrawIndexed(gCmdBufferBuffer, 480/*gVertexBufferBaseCount.idx*//*indexCount*/, 1/*instanceCount*/, 756/*firstIndex*/, 192/*vertexOffset*/, 0/*firstInstance*/);
                }

                if(model.whoAmI >= 0 && model.whoAmI <= 255)
                {
                  tableVk.CmdDrawIndexed(gCmdBufferBuffer, Geometry::gModelsIndexCount[model.whoAmI]/*gVertexBufferBaseCount.idx*//*indexCount*/, 1/*instanceCount*/, Geometry::gModelsIndexFirst[model.whoAmI]/*firstIndex*/, 354/*vertexOffset*/, 0/*firstInstance*/);
                }

                if(model.whoAmI == 256)
                {
                  uint32_t numModelsVerticiesStaticCountOf = sizeof(Geometry::gModelsVerticesStaticData) / sizeof(Geometry::gModelsVerticesStaticData[0] );

                  tableVk.CmdDrawIndexed(gCmdBufferBuffer, Geometry::gModelsIndexCount[model.whoAmI]/*gVertexBufferBaseCount.idx*//*indexCount*/, 1/*instanceCount*/, Geometry::gModelsIndexFirst[model.whoAmI]/*firstIndex*/, numModelsVerticiesStaticCountOf/*vertexOffset*/, 0/*firstInstance*/);
                }
              }
            }

            if(tableVk.CmdEndRenderPass)
              tableVk.CmdEndRenderPass(gCmdBufferBuffer);

            //CmdBuffer_CmdBufferEnd();
            //bool CmdBuffer_CmdBufferEnd()
            do
            {
              //CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Recording);
              if(gCmdBufferState != CmdBufferStateEnum::Recording)
              {
                Log::Write(
                  Log::Level::Error,
                  std::string("Expecting state CmdBufferStateEnum::Recording from ") +
                    __FUNCTION__ +
                    ", in " +
                    CmdBuffer_CmdBufferStateString(gCmdBufferState)
                );

                break;
              }

              if(tableVk.EndCommandBuffer)
                CHECK_VULKANCMD(tableVk.EndCommandBuffer(gCmdBufferBuffer) );

              gCmdBufferState = CmdBufferStateEnum::Executable;

            }while(0);

            //CmdBuffer_CmdBufferExec(gVulkanGraphicsPluginVkQueue);
            //bool CmdBuffer_CmdBufferExec(VkQueue queue)
            do
            {
              //CHECK_VULKANCMDBUFFERSTATE(CmdBufferStateEnum::Executable);
              if(gCmdBufferState != CmdBufferStateEnum::Executable)
              {
                Log::Write(
                  Log::Level::Error,
                  std::string("Expecting state CmdBufferStateEnum::Executable from ") +
                    __FUNCTION__ +
                    ", in " +
                    CmdBuffer_CmdBufferStateString(gCmdBufferState)
                );

                break;
              }

              VkSubmitInfo submitInfo {VK_STRUCTURE_TYPE_SUBMIT_INFO};

              submitInfo.commandBufferCount = 1;
              submitInfo.pCommandBuffers = &gCmdBufferBuffer;

              if(tableVk.QueueSubmit)
              {
                CHECK_VULKANCMD(tableVk.QueueSubmit(
                  gVulkanGraphicsPluginVkQueue,
                  1,
                  &submitInfo,
                  gCmdBufferExecFence
                ) );
              }

              gCmdBufferState = CmdBufferStateEnum::Executing;

              //return true;

            }while(0);
          }

          XrSwapchainImageReleaseInfo releaseInfo {XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO};

          if(tableXr.ReleaseSwapchainImage)
            CHECK_XRCMD_CHECK(tableXr.ReleaseSwapchainImage(viewSwapchain.handle, &releaseInfo) );
        }

        layer.space = gOpenXrProgramXrSpace;

        layer.layerFlags =
          gOptions_XrEnvironmentBlendMode == XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND ?
            XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT | XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT :
            0;

        layer.viewCount = (uint32_t)projectionLayerViews.size();

        layer.views = projectionLayerViews.data();

        renderLayerResult = true;

      }while(0);

      if(gPassthroughFeature == XR_NULL_HANDLE && renderLayerResult)
        layers_vector.push_back(reinterpret_cast<XrCompositionLayerBaseHeader*>( &layer) );
    }

#if 0
XR_TYPE_COMPOSITION_LAYER_PROJECTION = 35,
XR_TYPE_COMPOSITION_LAYER_QUAD = 36,
XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW = 48,
XR_TYPE_COMPOSITION_LAYER_CUBE_KHR = 1000006000,
XR_TYPE_COMPOSITION_LAYER_DEPTH_INFO_KHR = 1000010000,
XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR = 1000017000,
XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR = 1000018000,
XR_TYPE_COMPOSITION_LAYER_COLOR_SCALE_BIAS_KHR = 1000034000,
XR_TYPE_COMPOSITION_LAYER_IMAGE_LAYOUT_FB = 1000040000,
XR_TYPE_COMPOSITION_LAYER_ALPHA_BLEND_FB = 1000041001,
XR_TYPE_COMPOSITION_LAYER_REPROJECTION_INFO_MSFT = 1000066000,
XR_TYPE_COMPOSITION_LAYER_REPROJECTION_PLANE_OVERRIDE_MSFT = 1000066001,
XR_TYPE_COMPOSITION_LAYER_SECURE_CONTENT_FB = 1000072000,
XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR = 1000091000,
XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB = 1000118003,
XR_TYPE_COMPOSITION_LAYER_SPACE_WARP_INFO_FB = 1000171000,
XR_TYPE_COMPOSITION_LAYER_SETTINGS_FB = 1000204000,
XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_FB = 1000212000,
XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC = 1000317004,
#endif

    if(gPassthroughFeature == XR_NULL_HANDLE || gEnvironmentDepthProviderMETA == XR_NULL_HANDLE)
    {
      XrFrameEndInfo frameEndInfo {XR_TYPE_FRAME_END_INFO};
      frameEndInfo.displayTime = frameState.predictedDisplayTime;
      frameEndInfo.environmentBlendMode = gOptions_XrEnvironmentBlendMode;
      frameEndInfo.layerCount = (uint32_t)layers_vector.size();
      frameEndInfo.layers = layers_vector.data();

      if(tableXr.EndFrame)
        CHECK_XRCMD_CHECK(tableXr.EndFrame(gXrSession, &frameEndInfo) );
    }
    else
    {
      //std::vector<XrCompositionLayerProjectionView> projectionLayerViews;
      //projectionLayerViews.resize(renderLayerViewCountOutput);
      //projectionLayerViews[i] = {XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW};
      //projectionLayerViews[i].pose = gOpenXrProgramStdVector_XrView[i].pose;
      //projectionLayerViews[i].fov = gOpenXrProgramStdVector_XrView[i].fov;
      //projectionLayerViews[i].subImage.swapchain = viewSwapchain.handle;
      //projectionLayerViews[i].subImage.imageRect.offset = {0, 0};
      //projectionLayerViews[i].subImage.imageRect.extent = {viewSwapchain.width, viewSwapchain.height};

      //VulkanGraphicsPlugin_VulkanGraphicsPluginRenderView(
      //  projectionLayerViews[i],
      //  swapchainImage,
      //  gOpenXrProgramColorSwapchainFormat,
      //  models
      //);

      //XrCompositionLayerProjection layer {XR_TYPE_COMPOSITION_LAYER_PROJECTION};

      //layer.space = gOpenXrProgramXrSpace;

      //layer.layerFlags =
      //  gOptions_XrEnvironmentBlendMode == XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND ?
      //    XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT | XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT :
      //    0;

      //layer.viewCount = (uint32_t)projectionLayerViews.size();

      //layer.views = projectionLayerViews.data();

      //layers_vector.push_back(reinterpret_cast<XrCompositionLayerBaseHeader*>( &layer) );

      XrEnvironmentDepthImageAcquireInfoMETA environmentDepthImageAcquireInfoMETA
      {
        XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META
      };

      environmentDepthImageAcquireInfoMETA.next = 0;
      environmentDepthImageAcquireInfoMETA.space = gOpenXrProgramXrSpace;
      environmentDepthImageAcquireInfoMETA.displayTime = frameState.predictedDisplayTime;

      XrEnvironmentDepthImageMETA environmentDepthImageMETA {XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META};
      environmentDepthImageMETA.next = 0;

      environmentDepthImageMETA.views[0].type = XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META;
      environmentDepthImageMETA.views[1].type = XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META;

      // XrResult xrAcquireEnvironmentDepthImageMETA(
      //   XrEnvironmentDepthProviderMETA environmentDepthProvider,
      //   const XrEnvironmentDepthImageAcquireInfoMETA* acquireInfo,
      //   XrEnvironmentDepthImageMETA* environmentDepthImage
      // );

      //gAcquireEnvironmentDepthImageMETA(
      //  gEnvironmentDepthProviderMETA,
      //  &environmentDepthImageAcquireInfoMETA,
      //  &environmentDepthImageMETA
      //);

#if 0
      XrEnvironmentDepthImageAcquireInfoMETA environmentDepthAcquireInfo
      {
        XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META
      };

      environmentDepthAcquireInfo.space = app.LocalSpace;
      environmentDepthAcquireInfo.displayTime = frameState.predictedDisplayTime;

      XrEnvironmentDepthImageMETA environmentDepthImage
      {
        XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META
      };

      environmentDepthImage.views[0].type = XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META;
      environmentDepthImage.views[1].type = XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META;

      const XrResult acquireResult = xrAcquireEnvironmentDepthImageMETA(
        app.EnvironmentDepthProvider,
        &environmentDepthAcquireInfo,
        &environmentDepthImage
      );

      if(acquireResult == XR_SUCCESS)
      {
        frameIn.HasDepth = true;

        frameIn.DepthTexture = environmentDepthTextures.at(environmentDepthImage.swapchainIndex);

        frameIn.DepthNearZ = environmentDepthImage.nearZ;
        frameIn.DepthFarZ = environmentDepthImage.farZ;

        for(int eye = 0; eye < kNumEyes; ++eye)
        {
          const XrPosef xfLocalFromDepthEye = environmentDepthImage.views[eye].pose;

          XrPosef xfDepthEyeFromLocal;
          XrPosef_Invert( &xfDepthEyeFromLocal, &xfLocalFromDepthEye);

          XrMatrix4x4f viewMat;
          XrMatrix4x4f_CreateFromRigidTransform( &viewMat, &xfDepthEyeFromLocal);

          XrMatrix4x4f projectionMat;
          XrMatrix4x4f_CreateProjectionFov(
            &projectionMat,
            GRAPHICS_OPENGL_ES,
            environmentDepthImage.views[eye].fov,
            environmentDepthImage.nearZ,
            std::isfinite(environmentDepthImage.farZ) ? environmentDepthImage.farZ : 0
          );

          frameIn.DepthViewMatrices[eye] = OvrFromXr(viewMat);
          frameIn.DepthProjectionMatrices[eye] = OvrFromXr(projectionMat);
        }
      }
      else
      {
        ALOGE("No depth image received. Result = %d", acquireResult);
        frameIn.HasDepth = false;
      }

      app.appRenderer.RenderFrame(frameIn);
#endif

      // struct XrEnvironmentDepthImageAcquireInfoMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrSpace space;
      //   XrTime displayTime;
      // };

      // struct XrEnvironmentDepthImageMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   uint32_t swapchainIndex;
      //   float nearZ;
      //   float farZ;
      //   XrEnvironmentDepthImageViewMETA views[2];
      // };

      // struct XrEnvironmentDepthImageViewMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrFovf fov;
      //   XrPosef pose;
      // };

      // The nearZ and farZ are the near and far planes defined in an OpenGL projection matrix, and are needed to
      // convert the depth map’s pixel values into metric distances. The format and convention is the same as for
      // regular OpenGL depth textures.

      // There is a special case you should be aware of: when farZ = inf, you can use an infinite projection matrix as
      // described in Tightening the Precision of Perspective Rendering (see section 3.2: Infinite projection).

      // When farZ == inf, the bottom-right 2x2 quadrant of the 4x4 projection matrix is defined as:

      // [ -1   -2 * nearZ ]
      // [ -1    0         ]

      // zNear zFar infinity

      // Building a projection matrix using common OpenGL helpers and ignoring this special case will introduce NaN
      // values on its coefficients.

      // Note that the display time and pose of the acquired depth map is likely not the same as the estimated display
      // time and pose for the your app’s frame. To compute the depth of your rendered fragments, you must therefore
      // project the fragments 3D coordinates into the depth map using the provided pose and field-of-view (fov). For an
      // example, see the XrSamples / XrPassthroughOcclusion sample where this method is used to render a scene with
      // Depth API based occlusions.

      // struct XrOffset2Di
      // {
      //   int32_t x;
      //   int32_t y;
      // };

      // struct XrExtent2Di
      // {
      //   int32_t width;
      //   int32_t height;
      // };

      // struct XrExtent2Df
      // {
      //   float width;
      //   float height;
      // };

      // struct XrQuaternionf
      // {
      //   float x;
      //   float y;
      //   float z;
      //   float w;
      // };

      // struct XrVector3f
      // {
      //   float x;
      //   float y;
      //   float z;
      // };

      // struct XrFovf
      // {
      //   float angleLeft;
      //   float angleRight;
      //   float angleUp;
      //   float angleDown;
      // };

      // struct XrRect2Di
      // {
      //   XrOffset2Di offset;
      //   XrExtent2Di extent;
      // };

      // struct XrPosef
      // {
      //   XrQuaternionf orientation;
      //   XrVector3f position;
      // };

      // struct XrSwapchainSubImage
      // {
      //   XrSwapchain swapchain; // void*
      //   XrRect2Di imageRect;
      //   uint32_t imageArrayIndex;
      // };

      // struct XrCompositionLayerProjectionView
      // {
      //   XrStructureType type; // int
      //   const void* next;
      //   XrPosef pose;
      //   XrFovf fov;
      //   XrSwapchainSubImage subImage;
      // };

      // struct XrCompositionLayerProjection
      // {
      //   XrStructureType type; // int
      //   const void* next;
      //   XrCompositionLayerFlags layerFlags; // uint64_t
      //   XrSpace space; // void*
      //   uint32_t viewCount;
      //   const XrCompositionLayerProjectionView* views;
      // };

      // struct XrCompositionLayerQuad
      // {
      //   XrStructureType type; // int
      //   const void* XR_MAY_ALIAS next;
      //   XrCompositionLayerFlags layerFlags; // uint64_t
      //   XrSpace space; // void*
      //   XrEyeVisibility eyeVisibility; // int
      //   XrSwapchainSubImage subImage;
      //   XrPosef pose;
      //   XrExtent2Df size;
      // };

#if 0
      XrCompositionLayerProjectionView environmentDepthXrCompositionLayerProjectionView[2] = {};

      XrCompositionLayerProjection environmentDepthXrCompositionLayerProjection =
      {
        XR_TYPE_COMPOSITION_LAYER_PROJECTION
      };

      environmentDepthXrCompositionLayerProjection.next = 0;

      environmentDepthXrCompositionLayerProjection.layerFlags =
        XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT |
        XR_COMPOSITION_LAYER_CORRECT_CHROMATIC_ABERRATION_BIT |
        XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT;

      environmentDepthXrCompositionLayerProjection.space = gOpenXrProgramXrSpace;

      environmentDepthXrCompositionLayerProjection.viewCount = 2;

      environmentDepthXrCompositionLayerProjection.views = environmentDepthXrCompositionLayerProjectionView;

      for(int index = 0; index < 2; index++)
      {
        environmentDepthXrCompositionLayerProjectionView[index].type = XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW;
        environmentDepthXrCompositionLayerProjectionView[index].next = 0;
        environmentDepthXrCompositionLayerProjectionView[index].pose = environmentDepthImageMETA.views[index].pose;
        environmentDepthXrCompositionLayerProjectionView[index].fov = environmentDepthImageMETA.views[index].fov;

        environmentDepthXrCompositionLayerProjectionView[index].subImage.swapchain =
          (XrSwapchain)gEnvironmentDepthImages[index];

        environmentDepthXrCompositionLayerProjectionView[index].subImage.imageRect.offset.x = 0;

        environmentDepthXrCompositionLayerProjectionView[index].subImage.imageRect.offset.y = 0;

        environmentDepthXrCompositionLayerProjectionView[index].subImage.imageRect.extent.width =
          gEnvironmentDepthSwapchainStateMETA.width;

        environmentDepthXrCompositionLayerProjectionView[index].subImage.imageRect.extent.height =
          gEnvironmentDepthSwapchainStateMETA.height;

        environmentDepthXrCompositionLayerProjectionView[index].subImage.imageArrayIndex = index;
      }
#endif

      XrCompositionLayerPassthroughFB passthroughCompLayer = {XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB};
      passthroughCompLayer.layerHandle = gPassthroughLayer;
      passthroughCompLayer.flags = XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT;
      passthroughCompLayer.space = XR_NULL_HANDLE;

      layer.layerFlags = XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT;

      // XrResult xrAcquireEnvironmentDepthImageMETA(
      //   XrEnvironmentDepthProviderMETA environmentDepthProvider,
      //   const XrEnvironmentDepthImageAcquireInfoMETA* acquireInfo,
      //   XrEnvironmentDepthImageMETA* environmentDepthImage
      // );

      // if(tableXr.AcquireEnvironmentDepthImageMETA)
      // {
      //   tableXr.AcquireEnvironmentDepthImageMETA(
      //     gEnvironmentDepthProviderMETA,
      //     &environmentDepthImageAcquireInfoMETA,
      //     &environmentDepthImageMETA
      //   );
      // }

      // struct XrEnvironmentDepthImageAcquireInfoMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrSpace space;
      //   XrTime displayTime;
      // };

      // struct XrEnvironmentDepthImageMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   uint32_t swapchainIndex;
      //   float nearZ;
      //   float farZ;
      //   XrEnvironmentDepthImageViewMETA views[2];
      // };

      // struct XrEnvironmentDepthImageViewMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrFovf fov;
      //   XrPosef pose;
      // };

      const int kLayerCount = 2;

      const XrCompositionLayerBaseHeader* layers_array[kLayerCount] = {
        (const XrCompositionLayerBaseHeader*) &passthroughCompLayer,
        //(const XrCompositionLayerBaseHeader*) &environmentDepthXrCompositionLayerProjection,
        (const XrCompositionLayerBaseHeader*) &layer/*applicationCompLayer*/
      };

      XrFrameEndInfo frameEndInfo = {XR_TYPE_FRAME_END_INFO};
      frameEndInfo.displayTime = frameState.predictedDisplayTime;
      frameEndInfo.environmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
      frameEndInfo.layerCount = kLayerCount;
      frameEndInfo.layers = layers_array;

      if(tableXr.EndFrame)
        CHECK_XRCMD_CHECK(tableXr.EndFrame(gXrSession, &frameEndInfo) );
    }

    //XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT | XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT

    if(gPassthroughFeature == XR_NULL_HANDLE)
    {
      XrPassthroughCreateInfoFB passthroughCreateInfo = {XR_TYPE_PASSTHROUGH_CREATE_INFO_FB};
      passthroughCreateInfo.flags = XR_PASSTHROUGH_IS_RUNNING_AT_CREATION_BIT_FB;

      result = XR_ERROR_VALIDATION_FAILURE;
      if(tableXr.CreatePassthroughFB)
        result = tableXr.CreatePassthroughFB(gXrSession, &passthroughCreateInfo, &gPassthroughFeature);

      if(XR_FAILED(result) )
        Log::Write(Log::Level::Info, Fmt("failed to create the passthrough feature") );
      else
        Log::Write(Log::Level::Info, Fmt("created the passthrough feature") );

      // Create and run passthrough layer

      XrPassthroughLayerCreateInfoFB layerCreateInfo = {XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB};
      layerCreateInfo.passthrough = gPassthroughFeature;
      layerCreateInfo.purpose = XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB;
      layerCreateInfo.flags = XR_PASSTHROUGH_IS_RUNNING_AT_CREATION_BIT_FB;

      result = XR_ERROR_VALIDATION_FAILURE;
      if(tableXr.CreatePassthroughLayerFB)
        result = tableXr.CreatePassthroughLayerFB(gXrSession, &layerCreateInfo, &gPassthroughLayer);

      if(XR_FAILED(result) )
        Log::Write(Log::Level::Info, Fmt("failed to create and start a passthrough layer") );
      else
        Log::Write(Log::Level::Info, Fmt("created and started a passthrough layer") );
    }

    if(gEnvironmentDepthProviderMETA == XR_NULL_HANDLE)
    {
////////////////////////////////////////////////////////////////////////////////
      // OpenXR Depth API Overview

      // Health and Safety Recommendation: While building mixed reality experiences, we highly recommend that you
      // evaluate your content to offer your users a comfortable and safe experience. Please refer to the Health and
      // Safety and Design guidelines before designing and developing your app using Depth.

////////////////////////////////////////////////////////////////////////////////
      // Overview

////////////////////////////////////////////////////////////////////////////////
      // What is Depth API?

      // The Depth API provides real-time depth maps that apps can use to sense the environment. Primarily, it enhances
      // mixed reality (MR) by allowing virtual objects to be occluded by real-world objects and surfaces, which makes
      // them appear integrated into the actual environment. Occlusion is crucial because it prevents virtual content
      // from appearing as a layer over the real world, which can disrupt immersion.

////////////////////////////////////////////////////////////////////////////////
      // Why use Depth API?

      // The Scene Model enables the creation of room-scale, mixed reality experiences featuring realistic occlusion.
      // However, it cannot handle occlusion for objects that are dynamically moving within the user’s view, such as
      // hands, limbs, other people, and pets. To achieve realistic occlusion with these dynamic elements, you must also
      // use the Depth API.

////////////////////////////////////////////////////////////////////////////////
      // Requesting user permission

      // An app that wants to use Depth API needs to request and be granted spatial data permission
      // (com.oculus.permission.USE_SCENE) before accessing any of the functions in the XR_META_environment_depth
      // extension. See the Spatial Data Permission guide for how to set up the app and how to request this permission.

////////////////////////////////////////////////////////////////////////////////
      // Enabling the extension

      // The Depth API is defined in the XR_META_environment_depth OpenXR extension. All extensions should be explicitly
      // listed when creating an XrInstance. Include XR_META_ENVIRONMENT_DEPTH_EXTENSION_NAME in this list to enable the
      // Depth API extension:

      // std::vector<const char*> extensions = {XR_META_ENVIRONMENT_DEPTH_EXTENSION_NAME};
      //
      // XrInstanceCreateInfo instanceCreateInfo = {XR_TYPE_INSTANCE_CREATE_INFO};
      // instanceCreateInfo.enabledExtensionCount = extensions.size();
      // instanceCreateInfo.enabledExtensionNames = extensions.data();
      //
      // XrInstance instance = XR_NULL_HANDLE;
      // xrCreateInstance( &instanceCreateInfo, &instance);

      // For more details, see SampleXrFramework/Src/XrApp.cpp.

      // Note that this feature is not supported by all runtimes and devices so the app must first call
      // xrGetSystemProperties to query for a XrSystemEnvironmentDepthPropertiesMETA struct and check that
      // supportsEnvironmentDepth is true.

////////////////////////////////////////////////////////////////////////////////
      // Getting the extension function pointers

      // You must retrieve pointers to all the functions in the extension before calling them. For more details, see
      // xrGetInstanceProcAddr in the OpenXR spec.

      // The following snippet initializes all the available functions:

////////////////////////////////////////////////////////////////////////////////
      // Creating a depth provider

      // You can create a depth provider by using the xrCreateEnvironmentDepthProviderMETA function.
      // This function creates and returns a XrEnvironmentDepthProvider handle to a depth provider instance.
      // Maximum one depth provider is allowed to exist per app at any given time.
      // The handle is unique per process and cannot be shared across processes.

      // XrResult xrCreateEnvironmentDepthProviderMETA(
      //   XrSession session,
      //   const XrEnvironmentDepthProviderCreateInfoMETA* createInfo,
      //   XrEnvironmentDepthProviderMETA* environmentDepthProvider
      // );

      // To call this function, you must pass a XrEnvironmentDepthProviderCreateInfoMETA struct containing creation
      // flags. Currently createFlags must be zero, but it might be extended in the future.

      // struct XrEnvironmentDepthProviderCreateInfoMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrEnvironmentDepthProviderCreateFlagsMETA createFlags;
      // };

      gEnvironmentDepthProviderCreateInfoMETA.type = XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META;
      gEnvironmentDepthProviderCreateInfoMETA.next = nullptr;
      gEnvironmentDepthProviderCreateInfoMETA.createFlags = 0;

      gEnvironmentDepthProviderMETA = XR_NULL_HANDLE;

      XrResult result = XR_ERROR_VALIDATION_FAILURE;

      if(tableXr.CreateEnvironmentDepthProviderMETA)
      {
        result = tableXr.CreateEnvironmentDepthProviderMETA(
          gXrSession,
          &gEnvironmentDepthProviderCreateInfoMETA,
          &gEnvironmentDepthProviderMETA
        );
      }

      if(XR_FAILED(result) )
        Log::Write(Log::Level::Info, Fmt("failed CreateEnvironmentDepthProviderMETA") );
      else
        Log::Write(Log::Level::Info, Fmt("succeeded CreateEnvironmentDepthProviderMETA") );

      // To free up all the resources used by the depth provider, you can destroy it by calling
      // xrDestroyEnvironmentDepthProviderMETA

      // XrResult xrDestroyEnvironmentDepthProviderMETA(XrEnvironmentDepthProviderMETA environmentDepthProvider);

////////////////////////////////////////////////////////////////////////////////
      // Toggling hand removal

      // The Depth API supports removing hands from depth maps and replacing them with estimated background depth.
      // Removing hands can be useful for example if the app prefers to use Tracked Hands for hand occlusions instead of
      // the depth maps.

      // Note that this feature is not supported by all runtimes and devices so the app must first call
      // xrGetSystemProperties to query for a XrSystemEnvironmentDepthPropertiesMETA struct and check that
      // supportsHandRemoval is true.

      // Hand removal can be enabled or disabled at any time by calling the xrSetEnvironmentDepthHandRemovalMETA
      // function:

      // XrResult xrSetEnvironmentDepthHandRemovalMETA(
      //   XrEnvironmentDepthProviderMETA environmentDepthProvider,
      //   const XrEnvironmentDepthHandRemovalSetInfoMETA* setInfo
      // );

      // The function takes a XrEnvironmentDepthHandRemovalSetInfoMETA argument which is defined as:

      // struct XrEnvironmentDepthHandRemovalSetInfoMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrBool32 enabled;
      // };

      gEnvironmentDepthHandRemovalSetInfoMETA.type = XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META;
      gEnvironmentDepthHandRemovalSetInfoMETA.next = nullptr;
      gEnvironmentDepthHandRemovalSetInfoMETA.enabled = true;

      result = XR_ERROR_VALIDATION_FAILURE;
      if(tableXr.SetEnvironmentDepthHandRemovalMETA)
      {
        result = tableXr.SetEnvironmentDepthHandRemovalMETA(
          gEnvironmentDepthProviderMETA,
          &gEnvironmentDepthHandRemovalSetInfoMETA
        );
      }

////////////////////////////////////////////////////////////////////////////////
      // Creating and enumerating a depth swapchain

      // Depth maps are provided to the app through a special “readable swapchain” type XrEnvironmentDepthSwapchainMETA.
      // This type is similar to XrSwapchain but supports a different set of operations and is intended to be read
      // instead of written to by the app

      // Create the swapchain by calling xrCreateEnvironmentDepthSwapchainMETA:

      // XrResult xrCreateEnvironmentDepthSwapchainMETA(
      //   XrEnvironmentDepthProviderMETA environmentDepthProvider,
      //   const XrEnvironmentDepthSwapchainCreateInfoMETA* createInfo,
      //   XrEnvironmentDepthSwapchainMETA* swapchain
      // );

      // This function takes a XrEnvironmentDepthSwapchainCreateInfoMETA struct specifying options for creating the
      // swapchain:

      // struct XrEnvironmentDepthSwapchainCreateInfoMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrEnvironmentDepthSwapchainCreateFlagsMETA createFlags;
      // };

      // Currently createFlags must be zero, but it might be extended in the future.

      gEnvironmentDepthSwapchainCreateInfoMETA.type = XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_CREATE_INFO_META;
      gEnvironmentDepthSwapchainCreateInfoMETA.next = nullptr;
      gEnvironmentDepthSwapchainCreateInfoMETA.createFlags = 0;

      gEnvironmentDepthSwapchainMETA = XR_NULL_HANDLE;

      if(tableXr.CreateEnvironmentDepthSwapchainMETA)
      {
        tableXr.CreateEnvironmentDepthSwapchainMETA(
          gEnvironmentDepthProviderMETA,
          &gEnvironmentDepthSwapchainCreateInfoMETA,
          &gEnvironmentDepthSwapchainMETA
        );
      }

      // Once the swapchain is created the resolution can be queried by calling xrGetEnvironmentDepthSwapchainStateMETA:

      // XrResult xrGetEnvironmentDepthSwapchainStateMETA(
      //   XrEnvironmentDepthSwapchainMETA swapchain,
      //   XrEnvironmentDepthSwapchainStateMETA* state
      // );

      // The returned XrEnvironmentDepthSwapchainStateMETA is defined as:

      // struct XrEnvironmentDepthSwapchainStateMETA
      // {
      //   XrStructureType type;
      //   void* XR_MAY_ALIAS next;
      //   uint32_t width;
      //   uint32_t height;
      // };

      gEnvironmentDepthSwapchainStateMETA.type = XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_STATE_META;
      gEnvironmentDepthSwapchainStateMETA.next = nullptr;
      gEnvironmentDepthSwapchainStateMETA.width = 0;
      gEnvironmentDepthSwapchainStateMETA.height = 0;

      if(tableXr.GetEnvironmentDepthSwapchainStateMETA)
      {
        tableXr.GetEnvironmentDepthSwapchainStateMETA(
          gEnvironmentDepthSwapchainMETA,
          &gEnvironmentDepthSwapchainStateMETA
        );
      }

      // In the same way as for a regular XrSwapchain, the XrEnvironmentDepthSwapchainMETA needs to be “enumerated” into
      // a graphics API specific array of texture handles. This is done by calling
      // xrEnumerateEnvironmentDepthSwapchainImagesMETA that has the same semantics as xrEnumerateSwapchainImages:

      // XrResult xrEnumerateEnvironmentDepthSwapchainImagesMETA(
      //   XrEnvironmentDepthSwapchainMETA swapchain,
      //   uint32_t imageCapacityInput,
      //   uint32_t* imageCountOutput,
      //   XrSwapchainImageBaseHeader* images
      // );

      //struct XrSwapchainImageBaseHeader
      //{
      //  XrStructureType type;
      //  void* XR_MAY_ALIAS next;
      //};

      gEnvironmentDepthSwapChainLength = 0;

      if(tableXr.EnumerateEnvironmentDepthSwapchainImagesMETA)
      {
        tableXr.EnumerateEnvironmentDepthSwapchainImagesMETA(
          gEnvironmentDepthSwapchainMETA,
          0,
          &gEnvironmentDepthSwapChainLength,
          nullptr
        );
      }

      //struct XrSwapchainImageVulkanKHR
      //{
      //  XrStructureType type;
      //  void* XR_MAY_ALIAS next;
      //  VkImage image;
      //};

      gEnvironmentDepthImages.clear();

      for(int index = 0; index < gEnvironmentDepthSwapChainLength; index++)
      {
        XrSwapchainImageVulkanKHR swapchainImageVulkanKHR = {XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR, 0, VK_NULL_HANDLE};
        gEnvironmentDepthImages.push_back(swapchainImageVulkanKHR);
      }

      if(tableXr.EnumerateEnvironmentDepthSwapchainImagesMETA)
      {
        tableXr.EnumerateEnvironmentDepthSwapchainImagesMETA(
          gEnvironmentDepthSwapchainMETA,
          gEnvironmentDepthSwapChainLength,
          &gEnvironmentDepthSwapChainLength,
          (XrSwapchainImageBaseHeader*)gEnvironmentDepthImages.data()
        );
      }

      gEnvironmentDepthTextures.clear();

      for(int index = 0; index < gEnvironmentDepthSwapChainLength; index++)
        gEnvironmentDepthTextures.push_back(gEnvironmentDepthImages[index].image);

      // To free up all the resources used by the swapchain, you can destroy it by calling
      // xrDestroyEnvironmentDepthSwapchainMETA:

      // XrResult xrDestroyEnvironmentDepthSwapchainMETA(XrEnvironmentDepthSwapchainMETA swapchain);

////////////////////////////////////////////////////////////////////////////////
      // Starting and stopping the depth provider

      // The depth provider is created in a stopped state by default.
      // To start the asynchronous generation of depth maps, you need to call xrStartEnvironmentDepthProviderMETA:

      // XrResult xrStartEnvironmentDepthProviderMETA(XrEnvironmentDepthProviderMETA environmentDepthProvider);

      if(tableXr.StartEnvironmentDepthProviderMETA)
        tableXr.StartEnvironmentDepthProviderMETA(gEnvironmentDepthProviderMETA);

      // To stop the asynchronous generation of depth maps, call xrStopEnvironmentDepthProviderMETA:

      // XrResult xrStopEnvironmentDepthProviderMETA(XrEnvironmentDepthProviderMETA environmentDepthProvider);

////////////////////////////////////////////////////////////////////////////////
      // Acquiring depth maps

      // Depth maps should only be accessed between the xrBeginFrame and xrEndFrame calls.  To acquire a lock on the
      // latest available depth map in the swapchain, as well as retrieve metadata needed to parse the depth, apps need
      // to call xrAcquireEnvironmentDepthImageMETA. Once a depth swapchain has been acquired it is locked for the
      // entire duration of the frame. You shouldn’t call xrAcquireEnvironmentDepthImageMETA more than once per frame.

      // XrResult xrAcquireEnvironmentDepthImageMETA(
      //   XrEnvironmentDepthProviderMETA environmentDepthProvider,
      //   const XrEnvironmentDepthImageAcquireInfoMETA* acquireInfo,
      //   XrEnvironmentDepthImageMETA* environmentDepthImage
      // );

      // This function takes an XrEnvironmentDepthImageAcquireInfoMETA struct that needs to be populated with some
      // required parameters:

      // struct XrEnvironmentDepthImageAcquireInfoMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrSpace space;
      //   XrTime displayTime;
      // };

#if 0
      XrEnvironmentDepthImageAcquireInfoMETA environmentDepthImageAcquireInfoMETA
      {
        XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META
      };

      environmentDepthImageAcquireInfoMETA.next = 0;
      environmentDepthImageAcquireInfoMETA.space = gOpenXrProgramXrSpace;
      environmentDepthImageAcquireInfoMETA.displayTime = frameState.predictedDisplayTime;

      XrEnvironmentDepthImageMETA environmentDepthImageMETA {XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META};
      environmentDepthImageMETA.next = 0;

      environmentDepthImageMETA.views[0].type = XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META;
      environmentDepthImageMETA.views[1].type = XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META;

      gAcquireEnvironmentDepthImageMETA(
        gEnvironmentDepthProviderMETA,
        &environmentDepthImageAcquireInfoMETA,
        &environmentDepthImageMETA
      );
#endif

      // The space field should be set to the XrSpace you want the space to be of the returned pose which the depth map
      // was rendered from. The displayTime field should be set to the displayTime of the current rendered frame as it’s
      // used to compute the pose in case it is time dependent.

      // The information about the now locked swapchain image is returned the XrEnvironmentDepthImageMETA struct defined
      // as:

      // struct XrEnvironmentDepthImageMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   uint32_t swapchainIndex;
      //   float nearZ;
      //   float farZ;
      //   XrEnvironmentDepthImageViewMETA views[2];
      // };

      // struct XrEnvironmentDepthImageViewMETA
      // {
      //   XrStructureType type;
      //   const void* XR_MAY_ALIAS next;
      //   XrFovf fov;
      //   XrPosef pose;
      // };

      // The nearZ and farZ are the near and far planes defined in an OpenGL projection matrix, and are needed to
      // convert the depth map’s pixel values into metric distances. The format and convention is the same as for
      // regular OpenGL depth textures.

      // There is a special case you should be aware of: when farZ = inf, you can use an infinite projection matrix as
      // described in Tightening the Precision of Perspective Rendering (see section 3.2: Infinite projection).

      // When farZ == inf, the bottom-right 2x2 quadrant of the 4x4 projection matrix is defined as:

      // [ -1   -2 * nearZ ]
      // [ -1    0         ]

      // zNear zFar infinity

      // Building a projection matrix using common OpenGL helpers and ignoring this special case will introduce NaN
      // values on its coefficients.

      // Note that the display time and pose of the acquired depth map is likely not the same as the estimated display
      // time and pose for the your app’s frame. To compute the depth of your rendered fragments, you must therefore
      // project the fragments 3D coordinates into the depth map using the provided pose and field-of-view (fov). For an
      // example, see the XrSamples / XrPassthroughOcclusion sample where this method is used to render a scene with
      // Depth API based occlusions.
    }

    //Log::Write(Log::Level::Info, Fmt("number of render layers %i", layers.size() ) );
  }

  app->activity->vm->DetachCurrentThread();
}
catch(const std::exception& ex)
{
  Log::Write(Log::Level::Error, ex.what() );
}
catch(...)
{
  Log::Write(Log::Level::Error, "Unknown Error");
}

  anag_android_app_destroy(app);

  return 0;
}

struct android_app* anag_android_app_create(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
  struct android_app* app = 0;
  int msgpipe[2] = {0};

  app = (struct android_app*)calloc(1, sizeof(struct android_app) );
  if( !app)
    return 0;

  app->activity = activity;

  pthread_mutex_init( &app->mutex, 0);
  pthread_cond_init( &app->cond, 0);

  if(savedState)
  {
    app->savedState = calloc(1, savedStateSize);
    if( !app->savedState)
    {
      free(app);
      app = 0;

      return 0;
    }

    app->savedStateSize = savedStateSize;

    if(app->savedState)
      memcpy(app->savedState, savedState, savedStateSize);
  }

  if(pipe(msgpipe) )
  {
    ANAG_LOGE("could not create pipe: %s", strerror(errno) );

    free(app->savedState);
    app->savedState = 0;

    free(app);
    app = 0;

    return 0;
  }

  app->msgread = msgpipe[0];
  app->msgwrite = msgpipe[1];

  pthread_attr_t attr;
  memset( &attr, 0, sizeof(pthread_attr_t) );

  pthread_attr_init( &attr);
  pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED);
  pthread_create( &app->thread, &attr, anag_android_app_entry, app);

  pthread_mutex_lock( &app->mutex);

  while( !app->running)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);

  return app;
}

void anag_android_app_write_cmd(struct android_app* app, int8_t cmd)
{
  if( !app)
    return;

  if(write(app->msgwrite, &cmd, sizeof(cmd) ) != sizeof(cmd) )
  {
    ANAG_LOGE("Failure writing app cmd: %s", strerror(errno) );
  }
}

void anag_android_app_set_input(struct android_app* app, AInputQueue* inputQueue)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  app->pendingInputQueue = inputQueue;
  anag_android_app_write_cmd(app, APP_CMD_INPUT_CHANGED);

  while(app->inputQueue != app->pendingInputQueue)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

void anag_android_app_set_window(struct android_app* app, ANativeWindow* window)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);

  if(app->pendingWindow)
    anag_android_app_write_cmd(app, APP_CMD_TERM_WINDOW);

  app->pendingWindow = window;

  if(window)
    anag_android_app_write_cmd(app, APP_CMD_INIT_WINDOW);

  while(app->window != app->pendingWindow)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

void anag_android_app_set_activity_state(struct android_app* app, int8_t cmd)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  anag_android_app_write_cmd(app, cmd);

  while(app->activityState != cmd)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);
}

void anag_android_app_free(struct android_app* app)
{
  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);
  anag_android_app_write_cmd(app, APP_CMD_DESTROY);

  while( !app->destroyed)
    pthread_cond_wait( &app->cond, &app->mutex);

  pthread_mutex_unlock( &app->mutex);

  close(app->msgread);
  close(app->msgwrite);
  pthread_cond_destroy( &app->cond);
  pthread_mutex_destroy( &app->mutex);

  free(app);
  app = 0;
}

struct android_app* AnagToApp(ANativeActivity* activity)
{
  struct android_app* app = 0;

  if( !activity)
    return 0;

  app = (struct android_app*)activity->instance;

  return app;
}

void anagOnDestroy(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Destroy: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_free(app);
}

void anagOnStart(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Start: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_activity_state(app, APP_CMD_START);
}

void anagOnResume(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Resume: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_activity_state(app, APP_CMD_RESUME);
}

void* anagOnSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
  struct android_app* app = 0;
  void* savedState = 0;

  ANAG_LOGV("SaveInstanceState: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return 0;

  pthread_mutex_lock( &app->mutex);
  app->stateSaved = 0;
  anag_android_app_write_cmd(app, APP_CMD_SAVE_STATE);

  while( !app->stateSaved)
    pthread_cond_wait( &app->cond, &app->mutex);

  if(app->savedState)
  {
    savedState = app->savedState;
    *outLen = app->savedStateSize;
    app->savedState = 0;
    app->savedStateSize = 0;
  }

  pthread_mutex_unlock( &app->mutex);

  return savedState;
}

void anagOnPause(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Pause: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_activity_state(app, APP_CMD_PAUSE);
}

void anagOnStop(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("Stop: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_activity_state(app, APP_CMD_STOP);
}

void anagOnConfigurationChanged(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("ConfigurationChanged: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(app, APP_CMD_CONFIG_CHANGED);
}

void anagOnContentRectChanged(ANativeActivity* activity, const ARect* r)
{
  struct android_app* app = 0;

  if(r)
    ANAG_LOGV("ContentRectChanged: l=%d, t=%d, r=%d, b=%d", r->left, r->top, r->right, r->bottom);

  app = AnagToApp(activity);

  if( !app)
    return;

  pthread_mutex_lock( &app->mutex);

  if(r)
    app->contentRect = *r;
  else
    memset( &app->contentRect, 0, sizeof(ARect) );

  pthread_mutex_unlock( &app->mutex);

  anag_android_app_write_cmd(app, APP_CMD_CONTENT_RECT_CHANGED);
}

void anagOnLowMemory(ANativeActivity* activity)
{
  struct android_app* app = 0;

  ANAG_LOGV("LowMemory: %p", activity);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(app, APP_CMD_LOW_MEMORY);
}

void anagOnWindowFocusChanged(ANativeActivity* activity, int focused)
{
  struct android_app* app = 0;

  ANAG_LOGV("WindowFocusChanged: %p -- %d", activity, focused);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(app, focused ? APP_CMD_GAINED_FOCUS : APP_CMD_LOST_FOCUS);
}

void anagOnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  ANAG_LOGV("NativeWindowCreated: %p -- %p", activity, window);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_window(app, window);
}

void anagOnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  ANAG_LOGV("NativeWindowDestroyed: %p -- %p", activity, window);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_window(app, 0);
}

void anagOnNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  ANAG_LOGV("NativeWindowRedrawNeeded: %p -- %p", activity, window);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(AnagToApp(activity), APP_CMD_WINDOW_REDRAW_NEEDED);
}

void anagOnNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
  struct android_app* app = 0;

  ANAG_LOGV("NativeWindowResized: %p -- %p", activity, window);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_write_cmd(app, APP_CMD_WINDOW_RESIZED);
}

void anagOnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
  struct android_app* app = 0;

  ANAG_LOGV("InputQueueCreated: %p -- %p", activity, queue);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_input(app, queue);
}

void anagOnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
  struct android_app* app = 0;

  ANAG_LOGV("InputQueueDestroyed: %p -- %p", activity, queue);

  app = AnagToApp(activity);

  if( !app)
    return;

  anag_android_app_set_input(app, 0);
}

extern "C" __attribute__ ( (visibility ("default") ) ) void ANativeActivity_onCreate(
  ANativeActivity* activity,
  void* savedState,
  size_t savedStateSize
)
{
  ANAG_LOGV("Creating: %p", activity);

  if( !activity)
    return;

  if(activity->callbacks)
  {
    activity->callbacks->onConfigurationChanged = anagOnConfigurationChanged;
    activity->callbacks->onContentRectChanged = anagOnContentRectChanged;
    activity->callbacks->onDestroy = anagOnDestroy;
    activity->callbacks->onInputQueueCreated = anagOnInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = anagOnInputQueueDestroyed;
    activity->callbacks->onLowMemory = anagOnLowMemory;
    activity->callbacks->onNativeWindowCreated = anagOnNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = anagOnNativeWindowDestroyed;
    activity->callbacks->onNativeWindowRedrawNeeded = anagOnNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowResized = anagOnNativeWindowResized;
    activity->callbacks->onPause = anagOnPause;
    activity->callbacks->onResume = anagOnResume;
    activity->callbacks->onSaveInstanceState = anagOnSaveInstanceState;
    activity->callbacks->onStart = anagOnStart;
    activity->callbacks->onStop = anagOnStop;
    activity->callbacks->onWindowFocusChanged = anagOnWindowFocusChanged;
  }

  activity->instance = anag_android_app_create(activity, savedState, savedStateSize);
}
