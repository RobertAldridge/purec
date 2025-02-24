
/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * Licensed under the Oculus SDK License Agreement (the "License");
 * you may not use the Oculus SDK except in compliance with the License,
 * which is provided at the time of installation or download, or which
 * otherwise accompanies this software in either electronic or hard copy form.
 *
 * You may obtain a copy of the License at
 * https://developer.oculus.com/licenses/oculussdk/
 *
 * Unless required by applicable law or agreed to in writing, the Oculus SDK
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

struct ovrGeometry
{

void Clear();

void CreateCube();

void CreateAxes();

void CreateStage();

void Destroy();

void CreateVAO();

void DestroyVAO();

static constexpr int MAX_VERTEX_ATTRIB_POINTERS = 3;

struct VertexAttribPointer
{
  GLint Index;
  GLint Size;
  GLenum Type;
  GLboolean Normalized;
  GLsizei Stride;
  const GLvoid* Pointer;
};

GLuint VertexBuffer;

GLuint IndexBuffer;

GLuint VertexArrayObject;

int VertexCount;

int IndexCount;

VertexAttribPointer VertexAttribs[MAX_VERTEX_ATTRIB_POINTERS];

};

struct ovrProgram
{

static constexpr int MAX_PROGRAM_UNIFORMS = 8;
static constexpr int MAX_PROGRAM_TEXTURES = 8;

void Clear();

bool Create(const char* vertexSource, const char* fragmentSource);

void Destroy();

GLuint Program;

GLuint VertexShader;

GLuint FragmentShader;

// These will be -1 if not used by the program
GLint UniformLocation[MAX_PROGRAM_UNIFORMS]; // ProgramUniforms[].name

GLint UniformBinding[MAX_PROGRAM_UNIFORMS]; // ProgramUniforms[].name

GLint Textures[MAX_PROGRAM_TEXTURES]; // Texture%i

};

struct ovrFramebuffer
{

void Clear();

bool Create(
  const GLenum colorFormat,
  const int width,
  const int height,
  const int multisamples,
  const int swapChainLength,
  GLuint* colorTextures
);

void Destroy();

void Bind(int element);

void Unbind();

void Resolve();

int Width;

int Height;

int Multisamples;

int SwapChainLength;

struct Element
{
  GLuint ColorTexture;
  GLuint DepthTexture;
  GLuint FrameBufferObject;
};

Element* Elements;

};

struct ovrCubeData
{

ovrCubeData() :
  ColorScale(1.0f, 1.0f, 1.0f, 1.0f),
  ColorBias(0.0f, 0.0f, 0.0f, 0.0f)
{

}

OVR::Vector4f ColorScale;

OVR::Vector4f ColorBias;

OVR::Matrix4f Model;

};

struct ovrScene
{

void Clear();

void Create();

void Destroy();

bool IsCreated();

void SetClearColor(const float* c);

void CreateVAOs();

void DestroyVAOs();

bool CreatedScene;

bool CreatedVAOs;

ovrProgram CubeProgram;

ovrGeometry Cube;

GLuint SceneMatrices;

ovrProgram StageProgram;

ovrGeometry Stage;

ovrProgram AxesProgram;

ovrGeometry Axes;

float ClearColor[4];

std::vector<ovrCubeData> CubeData;

std::vector<XrSpace> SpaceList;

};

struct ovrAppRenderer
{

void Clear();

void Create(
  GLenum format,
  int width,
  int height,
  int numMultiSamples,
  int swapChainLength,
  GLuint* colorTextures
);

void Destroy();

struct FrameIn
{
  int SwapChainIndex;
  OVR::Matrix4f View[NUM_EYES];
  OVR::Matrix4f Proj[NUM_EYES];
  bool HasStage;
  OVR::Posef StagePose;
  OVR::Vector3f StageScale;
};

void RenderFrame(FrameIn frameIn);

ovrFramebuffer Framebuffer;

ovrScene Scene;

};
