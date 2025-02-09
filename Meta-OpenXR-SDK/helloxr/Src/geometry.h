
// geometry.h

namespace Geometry
{

struct Vertex
{
  XrVector3f Position;
  XrVector3f Normal;
  XrVector3f Color;
};

constexpr XrVector3f ColorRed {1, 0, 0};
constexpr XrVector3f ColorHalfRed {0.5, 0, 0};

constexpr XrVector3f ColorGreen {0, 1, 0};
constexpr XrVector3f ColorHalfGreen {0, 0.5, 0};

constexpr XrVector3f ColorBlue {0, 0, 1};
constexpr XrVector3f ColorHalfBlue {0, 0, 0.5};

constexpr XrVector3f ColorYellow {1, 1, 0};
constexpr XrVector3f ColorHalfYellow {0.5, 0.5, 0};

constexpr XrVector3f ColorCyan {0, 1, 1};
constexpr XrVector3f ColorHalfCyan {0, 0.5, 0.5};

constexpr XrVector3f ColorPurple {1, 0, 1};
constexpr XrVector3f ColorHalfPurple {0.5, 0, 0.5};

constexpr XrVector3f ColorBlack {0, 0, 0};
constexpr XrVector3f ColorWhite {1, 1, 1};

constexpr XrVector3f ColorDarkGrey {0.25, 0.25, 0.25};
constexpr XrVector3f ColorGrey {0.5, 0.5, 0.5};
constexpr XrVector3f ColorLightGrey {0.75, 0.75, 0.75};

// Vertices for a 1x1x1 meter cube. (Left/Right, Top/Bottom, Front/Back)
#if 0
constexpr XrVector3f PNNN {-0.5, -0.5, -0.5};
constexpr XrVector3f PNNP {-0.5, -0.5, 0.5};
constexpr XrVector3f PNPN {-0.5, 0.5, -0.5};
constexpr XrVector3f PNPP {-0.5, 0.5, 0.5};
constexpr XrVector3f PPNN {0.5, -0.5, -0.5};
constexpr XrVector3f PPNP {0.5, -0.5, 0.5};
constexpr XrVector3f PPPN {0.5, 0.5, -0.5};
constexpr XrVector3f PPPP {0.5, 0.5, 0.5};
#else
constexpr XrVector3f PNNN {-1.0 / 6.0, -1.0 / 6.0, 0.0};
constexpr XrVector3f PNNP {-1.0 / 6.0, -1.0 / 6.0, -2.0};
constexpr XrVector3f PNPN {-1.0 / 6.0, 1.0 / 6.0, 0.0};
constexpr XrVector3f PNPP {-1.0 / 6.0, 1.0 / 6.0, -2.0};
constexpr XrVector3f PPNN {1.0 / 6.0, -1.0 / 6.0, 0.0};
constexpr XrVector3f PPNP {1.0 / 6.0, -1.0 / 6.0, -2.0};
constexpr XrVector3f PPPN {1.0 / 6.0, 1.0 / 6.0, 0.0};
constexpr XrVector3f PPPP {1.0 / 6.0, 1.0 / 6.0, -2.0};
#endif

constexpr float N3RD {0.57735026918962576450914878050196};

constexpr XrVector3f NNNN {-N3RD, -N3RD, -N3RD};
constexpr XrVector3f NNNP {-N3RD, -N3RD, N3RD};
constexpr XrVector3f NNPN {-N3RD, N3RD, -N3RD};
constexpr XrVector3f NNPP {-N3RD, N3RD, N3RD};
constexpr XrVector3f NPNN {N3RD, -N3RD, -N3RD};
constexpr XrVector3f NPNP {N3RD, -N3RD, N3RD};
constexpr XrVector3f NPPN {N3RD, N3RD, -N3RD};
constexpr XrVector3f NPPP {N3RD, N3RD, N3RD};

#if 0
constexpr XrVector3f PZZN {0, 0, -0.5};
constexpr XrVector3f PZZP {0, 0, 0.5};

constexpr XrVector3f PZNZ {0, -0.5, 0};
constexpr XrVector3f PZPZ {0, 0.5, 0};

constexpr XrVector3f PNZZ {-0.5, 0, 0};
constexpr XrVector3f PPZZ {0.5, 0, 0};
#else
constexpr XrVector3f PZZN {0.0, 0.0, 0.0};
constexpr XrVector3f PZZP {0.0, 0.0, -2.0};

constexpr XrVector3f PZNZ {0.0, -1.0 / 6.0, -1.0};
constexpr XrVector3f PZPZ {0.0, 1.0 / 6.0, -1.0};

constexpr XrVector3f PNZZ {-1.0 / 6.0, 0.0, -1.0};
constexpr XrVector3f PPZZ {1.0 / 6.0, 0.0, -1.0};
#endif

constexpr XrVector3f NNZZ {-1, 0, 0};
constexpr XrVector3f NPZZ {1, 0, 0};

constexpr XrVector3f NZNZ {0, -1, 0};
constexpr XrVector3f NZPZ {0, 1, 0};

constexpr XrVector3f NZZN {0, 0, -1};
constexpr XrVector3f NZZP {0, 0, 1};

// {-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5}
//
// {-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5}, {-0.5, 0, 0}, {-0.5, 0, 0}, {-0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5}

constexpr Vertex c_cubeVertices[] =
{
  { {-1.0 / 2.0, -1.0 / 2.0, -2.0}, NNPN, ColorDarkGrey}, { {1.0 / 2.0, -1.0 / 2.0, -2.0}, NNZZ, ColorDarkGrey}, { {0, 0, -3.0}, NZZP, ColorGrey}, // 3
  { {1.0 / 2.0, -1.0 / 2.0, -2.0}, NNPN, ColorDarkGrey}, { {1.0 / 2.0, 1.0 / 2.0, -2.0}, NNZZ, ColorDarkGrey}, { {0, 0, -3.0}, NZZP, ColorGrey}, // 6
  { {1.0 / 2.0, 1.0 / 2.0, -2.0}, NNPN, ColorDarkGrey}, { {-1.0 / 2.0, 1.0 / 2.0, -2.0}, NNZZ, ColorDarkGrey}, { {0, 0, -3.0}, NZZP, ColorGrey}, // 9
  { {-1.0 / 2.0, 1.0 / 2.0, -2.0}, NNPN, ColorDarkGrey}, { {-1.0 / 2.0, -1.0 / 2.0, -2.0}, NNZZ, ColorDarkGrey}, { {0, 0, -3.0}, NZZP, ColorGrey}, // 12

  { {-1.0 / 6.0, -1.0 / 2.0, -2.0}, NNPN, ColorGrey}, { {-1.0 / 2.0, -1.0 / 2.0, -2.0}, NNZZ, ColorGrey}, { {-1.0 / 2.0, 1.0 / 6.0, -2.0}, NZZP, ColorHalfBlue}, // 15
  { {-1.0 / 2.0, 1.0 / 6.0, -2.0}, NNPN, ColorHalfBlue}, { {-1.0 / 6.0, 1.0 / 6.0, -2.0}, NNZZ, ColorHalfBlue}, { {-1.0 / 6.0, -1.0 / 2.0, -2.0}, NZZP, ColorGrey}, // 18

  { {-1.0 / 2.0, 1.0 / 6.0, -2.0}, NNPN, ColorGrey}, { {-1.0 / 2.0, 1.0 / 2.0, -2.0}, NNZZ, ColorGrey}, { {1.0 / 6.0, 1.0 / 2.0, -2.0}, NZZP, ColorHalfYellow}, // 21
  { {1.0 / 6.0, 1.0 / 2.0, -2.0}, NNPN, ColorHalfYellow}, { {1.0 / 6.0, 1.0 / 6.0, -2.0}, NNZZ, ColorHalfYellow}, { {-1.0 / 2.0, 1.0 / 6.0, -2.0}, NZZP, ColorGrey}, // 24

  { {1.0 / 6.0, 1.0 / 2.0, -2.0}, NNPN, ColorGrey}, { {1.0 / 2.0, 1.0 / 2.0, -2.0}, NNZZ, ColorGrey}, { {1.0 / 2.0, -1.0 / 6.0, -2.0}, NZZP, ColorHalfCyan}, // 27
  { {1.0 / 2.0, -1.0 / 6.0, -2.0}, NNPN, ColorHalfCyan}, { {1.0 / 6.0, -1.0 / 6.0, -2.0}, NNZZ, ColorHalfCyan}, { {1.0 / 6.0, 1.0 / 2.0, -2.0}, NZZP, ColorGrey}, // 30

  { {1.0 / 2.0, -1.0 / 6.0, -2.0}, NNPN, ColorGrey}, { {1.0 / 2.0, -1.0 / 2.0, -2.0}, NNZZ, ColorGrey}, { {-1.0 / 6.0, -1.0 / 2.0, -2.0}, NZZP, ColorHalfPurple}, // 33
  { {-1.0 / 6.0, -1.0 / 2.0, -2.0}, NNPN, ColorHalfPurple}, { {-1.0 / 6.0, -1.0 / 6.0, -2.0}, NNZZ, ColorHalfPurple}, { {1.0 / 2.0, -1.0 / 6.0, -2.0}, NZZP, ColorGrey}, // 36

  // -X
  {PNNN, NNNN, ColorHalfBlue}, {PNZZ, NNZZ, ColorGrey}, {PNPN, NNPN, ColorHalfGreen}, {PNPN, NNPN, ColorHalfGreen}, {PNZZ, NNZZ, ColorGrey}, {PNPP, NNPP, ColorHalfRed}, // 42
  {PNPP, NNPP, ColorHalfRed}, {PNZZ, NNZZ, ColorGrey}, {PNNP, NNNP, ColorHalfYellow}, {PNNP, NNNP, ColorHalfYellow}, {PNZZ, NNZZ, ColorGrey}, {PNNN, NNNN, ColorHalfBlue}, // 48

  // +X
  {PPNN, NPNN, ColorHalfYellow}, {PPZZ, NPZZ, ColorGrey}, {PPNP, NPNP, ColorHalfYellow}, {PPNP, NPNP, ColorHalfYellow}, {PPZZ, NPZZ, ColorGrey}, {PPPP, NPPP, ColorHalfYellow}, // 54
  {PPPP, NPPP, ColorHalfYellow}, {PPZZ, NPZZ, ColorGrey}, {PPPN, NPPN, ColorHalfYellow}, {PPPN, NPPN, ColorHalfYellow}, {PPZZ, NPZZ, ColorGrey}, {PPNN, NPNN, ColorHalfYellow}, // 60

  // -Y
  {PNNN, NNNN, ColorDarkGrey}, {PZNZ, NZNZ, ColorGrey}, {PNNP, NNNP, ColorDarkGrey}, {PNNP, NNNP, ColorDarkGrey}, {PZNZ, NZNZ, ColorGrey}, {PPNP, NPNP, ColorDarkGrey}, // 66
  {PPNP, NPNP, ColorDarkGrey}, {PZNZ, NZNZ, ColorGrey}, {PPNN, NPNN, ColorDarkGrey}, {PPNN, NPNN, ColorDarkGrey}, {PZNZ, NZNZ, ColorGrey}, {PNNN, NNNN, ColorDarkGrey}, // 72

  // +Y
  {PNPP, NNPP, ColorLightGrey}, {PZPZ, NZPZ, ColorGrey}, {PNPN, NNPN, ColorLightGrey}, {PNPN, NNPN, ColorLightGrey}, {PZPZ, NZPZ, ColorGrey}, {PPPN, NPPN, ColorLightGrey}, // 78
  {PPPN, NPPN, ColorLightGrey}, {PZPZ, NZPZ, ColorGrey}, {PPPP, NPPP, ColorLightGrey}, {PPPP, NPPP, ColorLightGrey}, {PZPZ, NZPZ, ColorGrey}, {PNPP, NNPP, ColorLightGrey}, // 84

  // -Z
  {PNPN, NNPN, ColorHalfCyan}, {PZZN, NZZN, ColorGrey}, {PNNN, NNNN, ColorHalfCyan}, {PNNN, NNNN, ColorHalfCyan}, {PZZN, NZZN, ColorGrey}, {PPNN, NPNN, ColorHalfCyan}, // 90
  {PPNN, NPNN, ColorHalfCyan}, {PZZN, NZZN, ColorGrey}, {PPPN, NPPN, ColorHalfCyan}, {PPPN, NPPN, ColorHalfCyan}, {PZZN, NZZN, ColorGrey}, {PNPN, NNPN, ColorHalfCyan}, // 96

  // +Z
  {PNNP, NNNP, ColorHalfYellow}, {PZZP, NZZP, ColorGrey}, {PNPP, NNPP, ColorHalfYellow}, {PNPP, NNPP, ColorHalfYellow}, {PZZP, NZZP, ColorGrey}, {PPPP, NPPP, ColorHalfYellow}, // 102
  {PPPP, NPPP, ColorHalfYellow}, {PZZP, NZZP, ColorGrey}, {PPNP, NPNP, ColorHalfYellow}, {PPNP, NPNP, ColorHalfYellow}, {PZZP, NZZP, ColorGrey}, {PNNP, NNNP, ColorHalfYellow} // 108
};

// Winding order is clockwise. Each side uses a different color.
constexpr unsigned short c_cubeIndices[] =
{
  0,  1,  2,  3,  4,  5, // -X
  6,  7,  8,  9,  10, 11,

  12, 13, 14, 15, 16, 17, // +X
  18, 19, 20, 21, 22, 23,

  24, 25, 26, 27, 28, 29, // -Y
  30, 31, 32, 33, 34, 35,

  36, 37, 38, 39, 40, 41, // +Y
  42, 43, 44, 45, 46, 47,

  48, 49, 50, 51, 52, 53, // -Z
  54, 55, 56, 57, 58, 59,

  60, 61, 62, 63, 64, 65, // +Z
  66, 67, 68, 69, 70, 71,

  72, 73, 74,
  75, 76, 77,

  78, 79, 80,
  81, 82, 83,

  84, 85, 86,
  87, 88, 89,

  90, 91, 92,
  93, 94, 95,

  96, 97, 98,
  99, 100, 101,

  102, 103, 104,
  105, 106, 107
};

#if 0
constexpr Vertex c_cubeVertices[] =
{
  // -X
  {PNPN, NNPN, ColorDarkGrey}, {PNZZ, NNZZ, ColorLightGrey}, {PNNN, NNNN, ColorDarkGrey}, {PNNN, NNNN, ColorDarkGrey}, {PNZZ, NNZZ, ColorLightGrey}, {PNNP, NNNP, ColorDarkGrey},
  {PNPN, NNPN, ColorDarkGrey}, {PNPP, NNPP, ColorDarkGrey}, {PNZZ, NNZZ, ColorLightGrey}, {PNZZ, NNZZ, ColorLightGrey}, {PNPP, NNPP, ColorDarkGrey}, {PNNP, NNNP, ColorDarkGrey},

  // +X
  {PPPN, NPPN, ColorHalfBlue}, {PPNN, NPNN, ColorHalfBlue}, {PPZZ, NPZZ, ColorLightGrey}, {PPZZ, NPZZ, ColorLightGrey}, {PPNN, NPNN, ColorHalfBlue}, {PPNP, NPNP, ColorHalfBlue},
  {PPPN, NPPN, ColorHalfBlue}, {PPZZ, NPZZ, ColorLightGrey}, {PPPP, NPPP, ColorHalfBlue}, {PPPP, NPPP, ColorHalfBlue}, {PPZZ, NPZZ, ColorLightGrey}, {PPNP, NPNP, ColorHalfBlue},

  // -Y
  {PNNN, NNNN, ColorHalfGreen}, {PNNP, NNNP, ColorHalfGreen}, {PZNZ, NZNZ, ColorLightGrey}, {PZNZ, NZNZ, ColorLightGrey}, {PNNP, NNNP, ColorHalfGreen}, {PPNP, NPNP, ColorHalfGreen},
  {PNNN, NNNN, ColorHalfGreen}, {PZNZ, NZNZ, ColorLightGrey}, {PPNN, NPNN, ColorHalfGreen}, {PPNN, NPNN, ColorHalfGreen}, {PZNZ, NZNZ, ColorLightGrey}, {PPNP, NPNP, ColorHalfGreen},

  // +Y
  {PNPN, NNPN, ColorHalfRed}, {PPPN, NPPN, ColorHalfRed}, {PZPZ, NZPZ, ColorLightGrey}, {PZPZ, NZPZ, ColorLightGrey}, {PPPN, NPPN, ColorHalfRed}, {PPPP, NPPP, ColorHalfRed},
  {PNPN, NNPN, ColorHalfRed}, {PZPZ, NZPZ, ColorLightGrey}, {PNPP, NNPP, ColorHalfRed}, {PNPP, NNPP, ColorHalfRed}, {PZPZ, NZPZ, ColorLightGrey}, {PPPP, NPPP, ColorHalfRed},

  // -Z
  {PNNN, NNNN, ColorHalfCyan}, {PPNN, NPNN, ColorHalfCyan}, {PZZN, NZZN, ColorLightGrey}, {PZZN, NZZN, ColorLightGrey}, {PPNN, NPNN, ColorHalfCyan}, {PPPN, NPPN, ColorHalfCyan},
  {PNNN, NNNN, ColorHalfCyan}, {PZZN, NZZN, ColorLightGrey}, {PNPN, NNPN, ColorHalfCyan}, {PNPN, NNPN, ColorHalfCyan}, {PZZN, NZZN, ColorLightGrey}, {PPPN, NPPN, ColorHalfCyan},

  // +Z
  {PNNP, NNNP, ColorHalfYellow}, {PNPP, NNPP, ColorHalfYellow}, {PZZP, NZZP, ColorLightGrey}, {PZZP, NZZP, ColorLightGrey}, {PNPP, NNPP, ColorHalfYellow}, {PPPP, NPPP, ColorHalfYellow},
  {PNNP, NNNP, ColorHalfYellow}, {PZZP, NZZP, ColorLightGrey}, {PPNP, NPNP, ColorHalfYellow}, {PPNP, NPNP, ColorHalfYellow}, {PZZP, NZZP, ColorLightGrey}, {PPPP, NPPP, ColorHalfYellow}
};
#endif

//#define CUBE_SIDE(V1, V2, V3, V4, V5, V6, COLOR) \
//  {V1, COLOR}, {V2, COLOR}, {V3, COLOR}, {V4, COLOR}, {V5, COLOR}, {V6, COLOR}

#if 0
constexpr Vertex c_cubeVertices[] =
{
  // -X
  {LTB, DarkRed}, {LBF, DarkRed}, {LBB, DarkRed}, {LTB, DarkRed}, {LTF, DarkRed}, {LBF, DarkRed},

  // +X
  {RTB, Red}, {RBB, Red}, {RBF, Red}, {RTB, Red}, {RBF, Red}, {RTF, Red},

  // -Y
  {LBB, DarkGreen}, {LBF, DarkGreen}, {RBF, DarkGreen}, {LBB, DarkGreen}, {RBF, DarkGreen}, {RBB, DarkGreen},

  // +Y
  {LTB, Green}, {RTB, Green}, {RTF, Green}, {LTB, Green}, {RTF, Green}, {LTF, Green},

  // -Z
  {LBB, DarkBlue}, {RBB, DarkBlue}, {RTB, DarkBlue}, {LBB, DarkBlue}, {RTB, DarkBlue}, {LTB, DarkBlue},

  // +Z
  {LBF, Blue}, {LTF, Blue}, {RTF, Blue}, {LBF, Blue}, {RTF, Blue}, {RBF, Blue}
};
#endif

#if 0
vec4(0.0, 0.0, 0.0, 1.0),
vec4(0.0, 0.0, 0.0, 1.0),
vec4(1.0, 1.0, 1.0, 1.0),
vec4(0.0, 0.0, 0.0, 1.0),
vec4(1.0, 1.0, 1.0, 1.0),
vec4(0.0, 0.0, 0.0, 1.0),

vec4(0.79, 0.79, 0.79, 1.0),
vec4(0.25, 0.25, 0.25, 1.0),
vec4(0.25, 0.25, 0.25, 1.0),
vec4(0.79, 0.79, 0.79, 1.0),
vec4(0.25, 0.25, 0.25, 1.0),
vec4(0.25, 0.25, 0.25, 1.0),

vec4(0.0, 1.0, 0.0, 1.0),
vec4(1.0, 0.0, 0.0, 1.0),
vec4(0.0, 1.0, 0.0, 1.0),
vec4(0.0, 1.0, 0.0, 1.0),
vec4(0.0, 1.0, 0.0, 1.0),
vec4(0.0, 0.0, 1.0, 1.0),

vec4(1.0, 0.0, 0.0, 1.0),
vec4(0.0, 1.0, 0.0, 1.0),
vec4(0.0, 0.0, 1.0, 1.0),
vec4(1.0, 0.0, 0.0, 1.0),
vec4(0.0, 0.0, 1.0, 1.0),
vec4(0.0, 1.0, 0.0, 1.0),

vec4(0.0, 0.54, 0.54, 1.0),
vec4(0.0, 0.54, 0.54, 1.0),
vec4(0.54, 0.54, 0.54, 1.0),
vec4(0.0, 0.54, 0.54, 1.0),
vec4(0.54, 0.54, 0.54, 1.0),
vec4(0.0, 0.54, 0.54, 1.0),

vec4(0.54, 0.54, 0.0, 1.0),
vec4(0.54, 0.54, 0.0, 1.0),
vec4(0.54, 0.54, 0.54, 1.0),
vec4(0.54, 0.54, 0.0, 1.0),
vec4(0.54, 0.54, 0.54, 1.0),
vec4(0.54, 0.54, 0.0, 1.0)
#endif

#if 0
// Winding order is clockwise. Each side uses a different color.
constexpr unsigned short c_cubeIndices[] =
{
  0,  1,  2,  3,  4,  5, // -X
  6,  7,  8,  9,  10, 11,

  12, 13, 14, 15, 16, 17, // +X
  18, 19, 20, 21, 22, 23,

  24, 25, 26, 27, 28, 29, // -Y
  30, 31, 32, 33, 34, 35,

  36, 37, 38, 39, 40, 41, // +Y
  42, 43, 44, 45, 46, 47,

  48, 49, 50, 51, 52, 53, // -Z
  54, 55, 56, 57, 58, 59,

  60, 61, 62, 63, 64, 65, // +Z
  66, 67, 68, 69, 70, 71
};
#endif

} // namespace Geometry
