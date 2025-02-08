
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
constexpr XrVector3f PNNN {-0.5, -0.5, -0.5};
constexpr XrVector3f PNNP {-0.5, -0.5, 0.5};
constexpr XrVector3f PNPN {-0.5, 0.5, -0.5};
constexpr XrVector3f PNPP {-0.5, 0.5, 0.5};
constexpr XrVector3f PPNN {0.5, -0.5, -0.5};
constexpr XrVector3f PPNP {0.5, -0.5, 0.5};
constexpr XrVector3f PPPN {0.5, 0.5, -0.5};
constexpr XrVector3f PPPP {0.5, 0.5, 0.5};

constexpr float N3RD {0.57735026918962576450914878050196};

constexpr XrVector3f NNNN {-N3RD, -N3RD, -N3RD};
constexpr XrVector3f NNNP {-N3RD, -N3RD, N3RD};
constexpr XrVector3f NNPN {-N3RD, N3RD, -N3RD};
constexpr XrVector3f NNPP {-N3RD, N3RD, N3RD};
constexpr XrVector3f NPNN {N3RD, -N3RD, -N3RD};
constexpr XrVector3f NPNP {N3RD, -N3RD, N3RD};
constexpr XrVector3f NPPN {N3RD, N3RD, -N3RD};
constexpr XrVector3f NPPP {N3RD, N3RD, N3RD};

constexpr XrVector3f PZZN {0, 0, -0.5};
constexpr XrVector3f PZZP {0, 0, 0.5};

constexpr XrVector3f PZNZ {0, -0.5, 0};
constexpr XrVector3f PZPZ {0, 0.5, 0};

constexpr XrVector3f PNZZ {-0.5, 0, 0};
constexpr XrVector3f PPZZ {0.5, 0, 0};

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

} // namespace Geometry
