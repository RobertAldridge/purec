
// geometry.h

namespace Geometry
{

struct Vertex
{
  XrVector3f Position;
  XrVector3f Normal;
  XrVector3f Color;
};

constexpr XrVector3f ColorRed {1.0, 0.0, 0.0};
constexpr XrVector3f ColorHalfRed {0.5, 0.0, 0.0};

constexpr XrVector3f ColorGreen {0.0, 1.0, 0.0};
constexpr XrVector3f ColorHalfGreen {0.0, 0.5, 0.0};

constexpr XrVector3f ColorBlue {0.0, 0.0, 1.0};
constexpr XrVector3f ColorHalfBlue {0.0, 0.0, 0.5};

constexpr XrVector3f ColorYellow {1.0, 1.0, 0.0};
constexpr XrVector3f ColorHalfYellow {0.5, 0.5, 0.0};

constexpr XrVector3f ColorCyan {0.0, 1.0, 1.0};
constexpr XrVector3f ColorHalfCyan {0.0, 0.5, 0.5};

constexpr XrVector3f ColorPurple {1.0, 0.0, 1.0};
constexpr XrVector3f ColorHalfPurple {0.5, 0.0, 0.5};
constexpr XrVector3f ColorQuarterPurple {0.25, 0.0, 0.25};

constexpr XrVector3f ColorOrange {1.0, 0.5, 0.0};
constexpr XrVector3f ColorHalfOrange {0.5, 0.25, 0.0};

constexpr XrVector3f ColorBlah {0.0, 0.5, 1.0};
constexpr XrVector3f ColorHalfBlah {0.0, 0.25, 0.5};

constexpr XrVector3f ColorBlack {0.0, 0.0, 0.0};
constexpr XrVector3f ColorWhite {1.0, 1.0, 1.0};

constexpr XrVector3f ColorDarkGrey {0.25, 0.25, 0.25};
constexpr XrVector3f ColorGrey {0.5, 0.5, 0.5};
constexpr XrVector3f ColorLightGrey {0.75, 0.75, 0.75};

// vertices for a 1x1x1 meter cube (left / right, top / bottom, front / back)

constexpr XrVector3f CPNNN {-0.5, -0.5, -0.5};
constexpr XrVector3f CPNNP {-0.5, -0.5, 0.5};
constexpr XrVector3f CPNPN {-0.5, 0.5, -0.5};
constexpr XrVector3f CPNPP {-0.5, 0.5, 0.5};
constexpr XrVector3f CPPNN {0.5, -0.5, -0.5};
constexpr XrVector3f CPPNP {0.5, -0.5, 0.5};
constexpr XrVector3f CPPPN {0.5, 0.5, -0.5};
constexpr XrVector3f CPPPP {0.5, 0.5, 0.5};

constexpr float N2ND {0.70710678118654752440084436210485};

constexpr float N3RD {0.57735026918962576450914878050196};

constexpr XrVector3f NNNN {-N3RD, -N3RD, -N3RD};
constexpr XrVector3f NNNP {-N3RD, -N3RD, N3RD};
constexpr XrVector3f NNPN {-N3RD, N3RD, -N3RD};
constexpr XrVector3f NNPP {-N3RD, N3RD, N3RD};
constexpr XrVector3f NPNN {N3RD, -N3RD, -N3RD};
constexpr XrVector3f NPNP {N3RD, -N3RD, N3RD};
constexpr XrVector3f NPPN {N3RD, N3RD, -N3RD};
constexpr XrVector3f NPPP {N3RD, N3RD, N3RD};

constexpr XrVector3f NZNN {0.0, -N2ND, -N2ND};
constexpr XrVector3f NZNP {0.0, -N2ND, N2ND};
constexpr XrVector3f NZPN {0.0, N2ND, -N2ND};
constexpr XrVector3f NZPP {0.0, N2ND, N2ND};

constexpr XrVector3f NNZN {-N2ND, 0.0, -N2ND};
constexpr XrVector3f NNZP {-N2ND, 0.0, N2ND};
constexpr XrVector3f NPZN {N2ND, 0.0, -N2ND};
constexpr XrVector3f NPZP {N2ND, 0.0, N2ND};

constexpr XrVector3f NNNZ {-N2ND, -N2ND, 0.0};
constexpr XrVector3f NNPZ {-N2ND, N2ND, 0.0};
constexpr XrVector3f NPNZ {N2ND, -N2ND, 0.0};
constexpr XrVector3f NPPZ {N2ND, N2ND, 0.0};

constexpr XrVector3f NNZZ {-1.0, 0.0, 0.0};
constexpr XrVector3f NPZZ {1.0, 0.0, 0.0};

constexpr XrVector3f NZNZ {0.0, -1.0, 0.0};
constexpr XrVector3f NZPZ {0.0, 1.0, 0.0};

constexpr XrVector3f NZZN {0.0, 0.0, -1.0};
constexpr XrVector3f NZZP {0.0, 0.0, 1.0};

constexpr XrVector3f CPZZN {0.0, 0.0, -0.5};
constexpr XrVector3f CPZZP {0.0, 0.0, 0.5};

constexpr XrVector3f CPZNZ {0.0, -0.5, 0.0};
constexpr XrVector3f CPZPZ {0.0, 0.5, 0.0};

constexpr XrVector3f CPNZZ {-0.5, 0.0, 0.0};
constexpr XrVector3f CPPZZ {0.5, 0.0, 0.0};

constexpr XrVector3f APZZN {0.0, 0.0, 0.0};
constexpr XrVector3f APZZP {0.0, 0.0, -2.0};

constexpr XrVector3f APZNZ {0.0, -1.0 / 6.0, -1.0};
constexpr XrVector3f APZPZ {0.0, 1.0 / 6.0, -1.0};

constexpr XrVector3f APNZZ {-1.0 / 6.0, 0.0, -1.0};
constexpr XrVector3f APPZZ {1.0 / 6.0, 0.0, -1.0};

constexpr XrVector3f APNNN {-1.0 / 6.0, -1.0 / 6.0, 0.0};
constexpr XrVector3f APNPN {-1.0 / 6.0, 1.0 / 6.0, 0.0};
constexpr XrVector3f APPNN {1.0 / 6.0, -1.0 / 6.0, 0.0};
constexpr XrVector3f APPPN {1.0 / 6.0, 1.0 / 6.0, 0.0};

constexpr XrVector3f APN2N2N2 {-1.0 / 2.0, -1.0 / 2.0, -2.0};
constexpr XrVector3f APN2P2N2 {-1.0 / 2.0, 1.0 / 2.0, -2.0};
constexpr XrVector3f APP2N2N2 {1.0 / 2.0, -1.0 / 2.0, -2.0};
constexpr XrVector3f APP2P2N2 {1.0 / 2.0, 1.0 / 2.0, -2.0};

constexpr XrVector3f APZZN3 {0.0, 0.0, -3.0};

constexpr XrVector3f APN2P6N2 {-1.0 / 2.0, 1.0 / 6.0, -2.0};
constexpr XrVector3f APN6N2N2 {-1.0 / 6.0, -1.0 / 2.0, -2.0};
constexpr XrVector3f APN6N6N2 {-1.0 / 6.0, -1.0 / 6.0, -2.0};
constexpr XrVector3f APN6P6N2 {-1.0 / 6.0, 1.0 / 6.0, -2.0};
constexpr XrVector3f APP6N6N2 {1.0 / 6.0, -1.0 / 6.0, -2.0};
constexpr XrVector3f APP6P6N2 {1.0 / 6.0, 1.0 / 6.0, -2.0};
constexpr XrVector3f APP6P2N2 {1.0 / 6.0, 1.0 / 2.0, -2.0};
constexpr XrVector3f APP2N6N2 {1.0 / 2.0, -1.0 / 6.0, -2.0};

constexpr Vertex gModelsVertices[] =
{

// arrow model start
  {APN2N2N2, NNPN, ColorDarkGrey}, {APP2N2N2, NNZZ, ColorDarkGrey}, {APZZN3, NZZP, ColorLightGrey}, // 3
  {APP2N2N2, NNPN, ColorDarkGrey}, {APP2P2N2, NNZZ, ColorDarkGrey}, {APZZN3, NZZP, ColorLightGrey}, // 6
  {APP2P2N2, NNPN, ColorDarkGrey}, {APN2P2N2, NNZZ, ColorDarkGrey}, {APZZN3, NZZP, ColorLightGrey}, // 9
  {APN2P2N2, NNPN, ColorDarkGrey}, {APN2N2N2, NNZZ, ColorDarkGrey}, {APZZN3, NZZP, ColorLightGrey}, // 12

  {APN6N2N2, NNPN, ColorGrey}, {APN2N2N2, NNZZ, ColorGrey}, {APN2P6N2, NZZP, ColorHalfBlue}, // 15
  {APN2P6N2, NNPN, ColorHalfBlue}, {APN6P6N2, NNZZ, ColorHalfBlue}, {APN6N2N2, NZZP, ColorGrey}, // 18

  {APN2P6N2, NNPN, ColorGrey}, {APN2P2N2, NNZZ, ColorGrey}, {APP6P2N2, NZZP, ColorHalfYellow}, // 21
  {APP6P2N2, NNPN, ColorHalfYellow}, {APP6P6N2, NNZZ, ColorHalfYellow}, {APN2P6N2, NZZP, ColorGrey}, // 24

  {APP6P2N2, NNPN, ColorGrey}, {APP2P2N2, NNZZ, ColorGrey}, {APP2N6N2, NZZP, ColorHalfCyan}, // 27
  {APP2N6N2, NNPN, ColorHalfCyan}, {APP6N6N2, NNZZ, ColorHalfCyan}, {APP6P2N2, NZZP, ColorGrey}, // 30

  {APP2N6N2, NNPN, ColorGrey}, {APP2N2N2, NNZZ, ColorGrey}, {APN6N2N2, NZZP, ColorQuarterPurple}, // 33
  {APN6N2N2, NNPN, ColorQuarterPurple}, {APN6N6N2, NNZZ, ColorQuarterPurple}, {APP2N6N2, NZZP, ColorGrey}, // 36

  // -X
  {APNNN, NNNN, ColorHalfBlue}, {APNZZ, NNZZ, ColorGrey}, {APNPN, NNPN, ColorHalfGreen}, {APNPN, NNPN, ColorHalfGreen}, {APNZZ, NNZZ, ColorGrey}, {APN6P6N2, NNPP, ColorHalfRed}, // 42
  {APN6P6N2, NNPP, ColorHalfRed}, {APNZZ, NNZZ, ColorGrey}, {APN6N6N2, NNNP, ColorHalfYellow}, {APN6N6N2, NNNP, ColorHalfYellow}, {APNZZ, NNZZ, ColorGrey}, {APNNN, NNNN, ColorHalfBlue}, // 48

  // +X
  {APPNN, NPNN, ColorHalfBlah}, {APPZZ, NPZZ, ColorGrey}, {APP6N6N2, NPNP, ColorHalfBlah}, {APP6N6N2, NPNP, ColorHalfBlah}, {APPZZ, NPZZ, ColorGrey}, {APP6P6N2, NPPP, ColorHalfBlah}, // 54
  {APP6P6N2, NPPP, ColorHalfBlah}, {APPZZ, NPZZ, ColorGrey}, {APPPN, NPPN, ColorHalfBlah}, {APPPN, NPPN, ColorHalfBlah}, {APPZZ, NPZZ, ColorGrey}, {APPNN, NPNN, ColorHalfBlah}, // 60

  // -Y
  {APNNN, NNNN, ColorHalfGreen}, {APZNZ, NZNZ, ColorGrey}, {APN6N6N2, NNNP, ColorHalfGreen}, {APN6N6N2, NNNP, ColorHalfGreen}, {APZNZ, NZNZ, ColorGrey}, {APP6N6N2, NPNP, ColorHalfGreen}, // 66
  {APP6N6N2, NPNP, ColorHalfGreen}, {APZNZ, NZNZ, ColorGrey}, {APPNN, NPNN, ColorHalfGreen}, {APPNN, NPNN, ColorHalfGreen}, {APZNZ, NZNZ, ColorGrey}, {APNNN, NNNN, ColorHalfGreen}, // 72

  // +Y
  {APN6P6N2, NNPP, ColorHalfOrange}, {APZPZ, NZPZ, ColorGrey}, {APNPN, NNPN, ColorHalfOrange}, {APNPN, NNPN, ColorHalfOrange}, {APZPZ, NZPZ, ColorGrey}, {APPPN, NPPN, ColorHalfOrange}, // 78
  {APPPN, NPPN, ColorHalfOrange}, {APZPZ, NZPZ, ColorGrey}, {APP6P6N2, NPPP, ColorHalfOrange}, {APP6P6N2, NPPP, ColorHalfOrange}, {APZPZ, NZPZ, ColorGrey}, {APN6P6N2, NNPP, ColorHalfOrange}, // 84

  // -Z
  {APNPN, NNPN, ColorDarkGrey}, {APZZN, NZZN, ColorLightGrey}, {APNNN, NNNN, ColorDarkGrey}, {APNNN, NNNN, ColorDarkGrey}, {APZZN, NZZN, ColorLightGrey}, {APPNN, NPNN, ColorDarkGrey}, // 90
  {APPNN, NPNN, ColorDarkGrey}, {APZZN, NZZN, ColorLightGrey}, {APPPN, NPPN, ColorDarkGrey}, {APPPN, NPPN, ColorDarkGrey}, {APZZN, NZZN, ColorLightGrey}, {APNPN, NNPN, ColorDarkGrey}, // 96
// arrow model finish

// cube model start
  // -X
  {CPNPN, NNPN, ColorQuarterPurple}, {CPNZZ, NNZZ, ColorGrey}, {CPNNN, NNNN, ColorQuarterPurple}, {CPNPP, NNPP, ColorQuarterPurple}, {CPNZZ, NNZZ, ColorGrey}, {CPNPN, NNPN, ColorQuarterPurple}, // 102
  {CPNNP, NNNP, ColorQuarterPurple}, {CPNZZ, NNZZ, ColorGrey}, {CPNPP, NNPP, ColorQuarterPurple}, {CPNNN, NNNN, ColorQuarterPurple}, {CPNZZ, NNZZ, ColorGrey}, {CPNNP, NNNP, ColorQuarterPurple}, // 108

  // +X
  {CPPNP, NPNP, ColorHalfYellow}, {CPPZZ, NPZZ, ColorGrey}, {CPPNN, NPNN, ColorHalfYellow}, {CPPPP, NPPP, ColorHalfYellow}, {CPPZZ, NPZZ, ColorGrey}, {CPPNP, NPNP, ColorHalfYellow}, // 114
  {CPPPN, NPPN, ColorHalfYellow}, {CPPZZ, NPZZ, ColorGrey}, {CPPPP, NPPP, ColorHalfYellow}, {CPPNN, NPNN, ColorHalfYellow}, {CPPZZ, NPZZ, ColorGrey}, {CPPPN, NPPN, ColorHalfYellow}, // 120

  // -Y
  {CPNNP, NNNP, ColorHalfOrange}, {CPZNZ, NZNZ, ColorGrey}, {CPNNN, NNNN, ColorHalfOrange}, {CPPNP, NPNP, ColorHalfOrange}, {CPZNZ, NZNZ, ColorGrey}, {CPNNP, NNNP, ColorHalfOrange}, // 126
  {CPPNN, NPNN, ColorHalfOrange}, {CPZNZ, NZNZ, ColorGrey}, {CPPNP, NPNP, ColorHalfOrange}, {CPNNN, NNNN, ColorHalfOrange}, {CPZNZ, NZNZ, ColorGrey}, {CPPNN, NPNN, ColorHalfOrange}, // 132

  // +Y
  {CPNPN, NNPN, ColorDarkGrey}, {CPZPZ, NZPZ, ColorLightGrey}, {CPNPP, NNPP, ColorDarkGrey}, {CPPPN, NPPN, ColorDarkGrey}, {CPZPZ, NZPZ, ColorLightGrey}, {CPNPN, NNPN, ColorDarkGrey}, // 138
  {CPPPP, NPPP, ColorDarkGrey}, {CPZPZ, NZPZ, ColorLightGrey}, {CPPPN, NPPN, ColorDarkGrey}, {CPNPP, NNPP, ColorDarkGrey}, {CPZPZ, NZPZ, ColorLightGrey}, {CPPPP, NPPP, ColorDarkGrey}, // 144

  // -Z
  {CPNNN, NNNN, ColorHalfCyan}, {CPZZN, NZZN, ColorGrey}, {CPNPN, NNPN, ColorHalfCyan}, {CPPNN, NPNN, ColorHalfCyan}, {CPZZN, NZZN, ColorGrey}, {CPNNN, NNNN, ColorHalfCyan}, // 150
  {CPPPN, NPPN, ColorHalfCyan}, {CPZZN, NZZN, ColorGrey}, {CPPNN, NPNN, ColorHalfCyan}, {CPNPN, NNPN, ColorHalfCyan}, {CPZZN, NZZN, ColorGrey}, {CPPPN, NPPN, ColorHalfCyan}, // 156

  // +Z
  {CPNPP, NNPP, ColorHalfGreen}, {CPZZP, NZZP, ColorGrey}, {CPNNP, NNNP, ColorHalfBlue}, {CPPPP, NPPP, ColorHalfRed}, {CPZZP, NZZP, ColorGrey}, {CPNPP, NNPP, ColorHalfGreen}, // 162
  {CPPNP, NPNP, ColorHalfYellow}, {CPZZP, NZZP, ColorGrey}, {CPPPP, NPPP, ColorHalfRed}, {CPNNP, NNNP, ColorHalfBlue}, {CPZZP, NZZP, ColorGrey}, {CPPNP, NPNP, ColorHalfYellow} // 168
// cube model finish

};

// winding order is clockwise. each side uses a different color
constexpr unsigned short gModelsIndices[] =
{

// arrow model start
  0, 1, 2,
  3, 4, 5,
  6, 7, 8,
  9, 10, 11,

  12, 13, 14,
  15, 16, 17,

  18, 19, 20,
  21, 22, 23,

  24, 25, 26,
  27, 28, 29,

  30, 31, 32,
  33, 34, 35,

  36, 37, 38, 39, 40, 41,
  42, 43, 44, 45, 46, 47,

  48, 49, 50, 51, 52, 53,
  54, 55, 56, 57, 58, 59,

  60, 61, 62, 63, 64, 65,
  66, 67, 68, 69, 70, 71,

  72, 73, 74, 75, 76, 77,
  78, 79, 80, 81, 82, 83,

  84, 85, 86, 87, 88, 89,
  90, 91, 92, 93, 94, 95,
// arrow model finish

// cube model start
  96, 97, 98, 99, 100, 101,
  102, 103, 104, 105, 106, 107,

  108, 109, 110, 111, 112, 113,
  114, 115, 116, 117, 118, 119,

  120, 121, 122, 123, 124, 125,
  126, 127, 128, 129, 130, 131,

  132, 133, 134, 135, 136, 137,
  138, 139, 140, 141, 142, 143,

  144, 145, 146, 147, 148, 149,
  150, 151, 152, 153, 154, 155,

  156, 157, 158, 159, 160, 161,
  162, 163, 164, 165, 166, 167
// cube model finish

};

} // namespace Geometry
