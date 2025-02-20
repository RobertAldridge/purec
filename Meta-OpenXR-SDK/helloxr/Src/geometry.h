
// geometry.h

struct GeometryVertex
{
  XrVector3f Position;
  XrVector3f Normal;
  XrVector3f Color;
  XrVector2f Texture;
};

namespace Geometry
{

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

#if defined(GEOMETRY_H_IMPLEMENTATION)
uint32_t gModelsVerticesDynamicCountOf = 0;
GeometryVertex* gModelsVerticesDynamicData = nullptr;

uint32_t gModelsIndicesDynamicCountOf = 0;
uint32_t* gModelsIndicesDynamicData = nullptr;
#else
extern uint32_t gModelsVerticesDynamicCountOf;
extern GeometryVertex* gModelsVerticesDynamicData;

extern uint32_t gModelsIndicesDynamicCountOf;
extern uint32_t* gModelsIndicesDynamicData;
#endif

// constexpr GeometryVertex gModelsVerticesStaticData[];
// constexpr uint32_t gModelsIndicesStaticData[];

// uint32_t gModelsIndexCount[];
// uint32_t gModelsIndexFirst[];

constexpr GeometryVertex gModelsVerticesStaticData[] =
{

// 0

// arrow model start
  {APN2N2N2, NNNZ, ColorDarkGrey}, {APP2N2N2, NPNZ, ColorDarkGrey}, {APZZN3, NZZN, ColorLightGrey}, // 3
  {APP2N2N2, NPNZ, ColorDarkGrey}, {APP2P2N2, NPPZ, ColorDarkGrey}, {APZZN3, NZZN, ColorLightGrey}, // 6
  {APP2P2N2, NPPZ, ColorDarkGrey}, {APN2P2N2, NNPZ, ColorDarkGrey}, {APZZN3, NZZN, ColorLightGrey}, // 9
  {APN2P2N2, NNPZ, ColorDarkGrey}, {APN2N2N2, NNNZ, ColorDarkGrey}, {APZZN3, NZZN, ColorLightGrey}, // 12

  {APN6N2N2, NZZP, ColorGrey}, {APN2N2N2, NZZP, ColorGrey}, {APN2P6N2, NZZP, ColorHalfBlue}, // 15
  {APN2P6N2, NZZP, ColorHalfBlue}, {APN6P6N2, NZZP, ColorHalfBlue}, {APN6N2N2, NZZP, ColorGrey}, // 18

  {APN2P6N2, NZZP, ColorGrey}, {APN2P2N2, NZZP, ColorGrey}, {APP6P2N2, NZZP, ColorHalfYellow}, // 21
  {APP6P2N2, NZZP, ColorHalfYellow}, {APP6P6N2, NZZP, ColorHalfYellow}, {APN2P6N2, NZZP, ColorGrey}, // 24

  {APP6P2N2, NZZP, ColorGrey}, {APP2P2N2, NZZP, ColorGrey}, {APP2N6N2, NZZP, ColorHalfCyan}, // 27
  {APP2N6N2, NZZP, ColorHalfCyan}, {APP6N6N2, NZZP, ColorHalfCyan}, {APP6P2N2, NZZP, ColorGrey}, // 30

  {APP2N6N2, NZZP, ColorGrey}, {APP2N2N2, NZZP, ColorGrey}, {APN6N2N2, NZZP, ColorQuarterPurple}, // 33
  {APN6N2N2, NZZP, ColorQuarterPurple}, {APN6N6N2, NZZP, ColorQuarterPurple}, {APP2N6N2, NZZP, ColorGrey}, // 36

  // -X
  {APNNN, NNNZ, ColorHalfBlue}, {APNZZ, NNZZ, ColorGrey}, {APNPN, NNPZ, ColorHalfGreen}, {APNPN, NNPZ, ColorHalfGreen}, {APNZZ, NNZZ, ColorGrey}, {APN6P6N2, NNPZ, ColorHalfRed}, // 42
  {APN6P6N2, NNPZ, ColorHalfRed}, {APNZZ, NNZZ, ColorGrey}, {APN6N6N2, NNNZ, ColorHalfYellow}, {APN6N6N2, NNNZ, ColorHalfYellow}, {APNZZ, NNZZ, ColorGrey}, {APNNN, NNNZ, ColorHalfBlue}, // 48

  // +X
  {APPNN, NPNZ, ColorHalfBlah}, {APPZZ, NPZZ, ColorGrey}, {APP6N6N2, NPNZ, ColorHalfBlah}, {APP6N6N2, NPNZ, ColorHalfBlah}, {APPZZ, NPZZ, ColorGrey}, {APP6P6N2, NPPZ, ColorHalfBlah}, // 54
  {APP6P6N2, NPPZ, ColorHalfBlah}, {APPZZ, NPZZ, ColorGrey}, {APPPN, NPPZ, ColorHalfBlah}, {APPPN, NPPZ, ColorHalfBlah}, {APPZZ, NPZZ, ColorGrey}, {APPNN, NPNZ, ColorHalfBlah}, // 60

  // -Y
  {APNNN, NNNZ, ColorHalfGreen}, {APZNZ, NZNZ, ColorGrey}, {APN6N6N2, NNNZ, ColorHalfGreen}, {APN6N6N2, NNNZ, ColorHalfGreen}, {APZNZ, NZNZ, ColorGrey}, {APP6N6N2, NPNZ, ColorHalfGreen}, // 66
  {APP6N6N2, NPNZ, ColorHalfGreen}, {APZNZ, NZNZ, ColorGrey}, {APPNN, NPNZ, ColorHalfGreen}, {APPNN, NPNZ, ColorHalfGreen}, {APZNZ, NZNZ, ColorGrey}, {APNNN, NNNZ, ColorHalfGreen}, // 72

  // +Y
  {APN6P6N2, NNPZ, ColorHalfOrange}, {APZPZ, NZPZ, ColorGrey}, {APNPN, NNPZ, ColorHalfOrange}, {APNPN, NNPZ, ColorHalfOrange}, {APZPZ, NZPZ, ColorGrey}, {APPPN, NPPZ, ColorHalfOrange}, // 78
  {APPPN, NPPZ, ColorHalfOrange}, {APZPZ, NZPZ, ColorGrey}, {APP6P6N2, NPPZ, ColorHalfOrange}, {APP6P6N2, NPPZ, ColorHalfOrange}, {APZPZ, NZPZ, ColorGrey}, {APN6P6N2, NNPZ, ColorHalfOrange}, // 84

  // -Z
  {APNPN, NZZP, ColorDarkGrey}, {APZZN, NZZP, ColorLightGrey}, {APNNN, NZZP, ColorDarkGrey}, {APNNN, NZZP, ColorDarkGrey}, {APZZN, NZZP, ColorLightGrey}, {APPNN, NZZP, ColorDarkGrey}, // 90
  {APPNN, NZZP, ColorDarkGrey}, {APZZN, NZZP, ColorLightGrey}, {APPPN, NZZP, ColorDarkGrey}, {APPPN, NZZP, ColorDarkGrey}, {APZZN, NZZP, ColorLightGrey}, {APNPN, NZZP, ColorDarkGrey}, // 96
// arrow model finish

// 96

// cube model start
  // -X
  {CPNPN, NNPN, ColorQuarterPurple}, {CPNZZ, NNZZ, ColorGrey}, {CPNNN, NNNN, ColorQuarterPurple}, {CPNPP, NNPP, ColorQuarterPurple}, {CPNZZ, NNZZ, ColorGrey}, {CPNPN, NNPN, ColorQuarterPurple}, // 102
  {CPNNP, NNNP, ColorQuarterPurple}, {CPNZZ, NNZZ, ColorGrey}, {CPNPP, NNPP, ColorQuarterPurple}, {CPNNN, NNNN, ColorQuarterPurple}, {CPNZZ, NNZZ, ColorGrey}, {CPNNP, NNNP, ColorQuarterPurple}, // 108

  // +X
  {CPPNP, NPNP, ColorHalfYellow, {0.0, 1.0} }, {CPPZZ, NPZZ, ColorGrey, {1.0, 0.0} }, {CPPNN, NPNN, ColorHalfYellow, {1.0, 1.0} }, {CPPPP, NPPP, ColorHalfYellow}, {CPPZZ, NPZZ, ColorGrey}, {CPPNP, NPNP, ColorHalfYellow}, // 114
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
  {CPPNP, NPNP, ColorHalfYellow}, {CPZZP, NZZP, ColorGrey}, {CPPPP, NPPP, ColorHalfRed}, {CPNNP, NNNP, ColorHalfBlue}, {CPZZP, NZZP, ColorGrey}, {CPPNP, NPNP, ColorHalfYellow}, // 168
// cube model finish

// 168

#if 0
// Z
v -5.182320 3.884983 0.255283
v -5.182320 2.284983 0.255283
v -5.182320 1.884983 0.255283
v -6.382320 3.884983 0.255283
v -6.382320 1.884983 0.255283
v -5.182320 3.400541 0.255283
v -6.382320 2.369425 0.255283
v -6.382320 3.484983 0.255283
v -5.982320 1.884983 0.255283
v -5.582320 3.884983 0.255283
v -5.582320 3.484983 0.255283
v -5.982320 2.284983 0.255283
v -5.182320 3.884983 -0.044717
v -5.182320 2.284983 -0.044717
v -5.182320 1.884983 -0.044717
v -6.382320 3.884983 -0.044717
v -6.382320 1.884983 -0.044717
v -5.182320 3.400541 -0.044717
v -6.382320 2.369425 -0.044717
v -6.382320 3.484983 -0.044717
v -5.982320 1.884983 -0.044717
v -5.582320 3.884983 -0.044717
v -5.582320 3.484983 -0.044717
v -5.982320 2.284983 -0.044717

// Z
vn 0.0, 0.0, 1.0
vn 0.0, 0.0, -1.0
vn -1.0, 0.0, 0.0
vn 0.0, -1.0, 0.0
vn 1.0, 0.0, 0.0
vn 0.0, 1.0, 0.0
vn -0.8126, 0.5828, 0.0
vn 0.8126, -0.5828, 0.0

// Z
vt 0.214291 0.726181
#endif

// 'Z' start
{ {-5.182320, 3.884983, 0.255283}, NZZP, ColorWhite}, // 1
{ {-5.182320, 2.284983, 0.255283}, NZZP, ColorWhite}, // 2
{ {-5.182320, 1.884983, 0.255283}, NZZP, ColorWhite}, // 3
{ {-6.382320, 3.884983, 0.255283}, NZPZ, ColorWhite}, // 4
{ {-6.382320, 1.884983, 0.255283}, NZZP, ColorWhite}, // 5
{ {-5.182320, 3.400541, 0.255283}, NZZP, ColorWhite}, // 6
{ {-6.382320, 2.369425, 0.255283}, NZZP, ColorWhite}, // 7
{ {-6.382320, 3.484983, 0.255283}, NZZP, ColorWhite}, // 8
{ {-5.982320, 1.884983, 0.255283}, NZZP, ColorWhite}, // 9
{ {-5.582320, 3.884983, 0.255283}, NZZP, ColorWhite}, // 10
{ {-5.582320, 3.484983, 0.255283}, NZZP, ColorWhite}, // 11
{ {-5.982320, 2.284983, 0.255283}, NZZP, ColorWhite}, // 12
{ {-5.182320, 3.884983, -0.044717}, NZZN, ColorWhite}, // 13
{ {-5.182320, 2.284983, -0.044717}, NPZZ, ColorWhite}, // 14
{ {-5.182320, 1.884983, -0.044717}, NPZZ, ColorWhite}, // 15
{ {-6.382320, 3.884983, -0.044717}, NZZN, ColorWhite}, // 16
{ {-6.382320, 1.884983, -0.044717}, NZZN, ColorWhite}, // 17
{ {-5.182320, 3.400541, -0.044717}, NPZZ, ColorWhite}, // 18
{ {-6.382320, 2.369425, -0.044717}, NZZN, ColorWhite}, // 19
{ {-6.382320, 3.484983, -0.044717}, NZZN, ColorWhite}, // 20
{ {-5.982320, 1.884983, -0.044717}, NZNZ, ColorWhite}, // 21
{ {-5.582320, 3.884983, -0.044717}, NZPZ, ColorWhite}, // 22
{ {-5.582320, 3.484983, -0.044717}, NZZN, ColorWhite}, // 23
{ {-5.982320, 2.284983, -0.044717}, NZPZ, ColorWhite}, // 24
// 'Z' finish

// 192

// smiley front start
/*0*/   { {1.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*1*/   { {2.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*2*/   { {3.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*3*/   { {4.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*4*/   { {5.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*5*/   { {6.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*6*/   { {7.0, 0.0, 0.0}, NZPZ, ColorWhite},

/*7*/   { {0.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*8*/   { {1.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*9*/   { {2.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*10*/  { {3.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*11*/  { {4.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*12*/  { {5.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*13*/  { {6.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*14*/  { {7.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*15*/  { {8.0, 0.0, -1.0}, NZPZ, ColorWhite},

/*16*/  { {0.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*17*/  { {1.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*18*/  { {2.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*19*/  { {3.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*20*/  { {4.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*21*/  { {5.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*22*/  { {6.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*23*/  { {7.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*24*/  { {8.0, 0.0, -2.0}, NZPZ, ColorWhite},

/*25*/  { {0.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*26*/  { {1.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*27*/  { {2.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*28*/  { {3.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*29*/  { {4.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*30*/  { {5.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*31*/  { {6.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*32*/  { {7.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*33*/  { {8.0, 0.0, -3.0}, NZPZ, ColorWhite},

/*34*/  { {0.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*35*/  { {1.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*36*/  { {2.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*37*/  { {3.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*38*/  { {4.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*39*/  { {5.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*40*/  { {6.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*41*/  { {7.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*42*/  { {8.0, 0.0, -4.0}, NZPZ, ColorWhite},

/*43*/  { {0.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*44*/  { {1.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*45*/  { {2.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*46*/  { {3.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*47*/  { {5.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*48*/  { {6.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*49*/  { {7.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*50*/  { {8.0, 0.0, -5.0}, NZPZ, ColorWhite},

/*51*/  { {0.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*52*/  { {1.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*53*/  { {2.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*54*/  { {3.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*55*/  { {5.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*56*/  { {6.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*57*/  { {7.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*58*/  { {8.0, 0.0, -6.0}, NZPZ, ColorWhite},

/*59*/  { {0.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*60*/  { {1.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*61*/  { {2.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*62*/  { {6.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*63*/  { {7.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*64*/  { {8.0, 0.0, -7.0}, NZPZ, ColorWhite},

/*65*/  { {0.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*66*/  { {1.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*67*/  { {2.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*68*/  { {3.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*69*/  { {4.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*70*/  { {5.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*71*/  { {6.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*72*/  { {7.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*73*/  { {8.0, 0.0, -8.0}, NZPZ, ColorWhite},

/*74*/  { {1.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*75*/  { {2.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*76*/  { {3.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*77*/  { {4.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*78*/  { {5.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*79*/  { {6.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*80*/  { {7.0, 0.0, -9.0}, NZPZ, ColorWhite},
// smiley front finish

// [0, 80] is 81

// 273

// smiley back start
/*0*/   { {1.0, -1.0, 0.0}, NZNZ, ColorWhite},
/*1*/   { {2.0, -1.0, 0.0}, NZNZ, ColorWhite},
/*2*/   { {3.0, -1.0, 0.0}, NZNZ, ColorWhite},
/*3*/   { {4.0, -1.0, 0.0}, NZNZ, ColorWhite},
/*4*/   { {5.0, -1.0, 0.0}, NZNZ, ColorWhite},
/*5*/   { {6.0, -1.0, 0.0}, NZNZ, ColorWhite},
/*6*/   { {7.0, -1.0, 0.0}, NZNZ, ColorWhite},

/*7*/   { {0.0, -1.0, -1.0}, NZNZ, ColorWhite},
/*8*/   { {1.0, -1.0, -1.0}, NZNZ, ColorWhite},
/*9*/   { {2.0, -1.0, -1.0}, NZNZ, ColorWhite},
/*10*/  { {3.0, -1.0, -1.0}, NZNZ, ColorWhite},
/*11*/  { {4.0, -1.0, -1.0}, NZNZ, ColorWhite},
/*12*/  { {5.0, -1.0, -1.0}, NZNZ, ColorWhite},
/*13*/  { {6.0, -1.0, -1.0}, NZNZ, ColorWhite},
/*14*/  { {7.0, -1.0, -1.0}, NZNZ, ColorWhite},
/*15*/  { {8.0, -1.0, -1.0}, NZNZ, ColorWhite},

/*16*/  { {0.0, -1.0, -2.0}, NZNZ, ColorWhite},
/*17*/  { {1.0, -1.0, -2.0}, NZNZ, ColorWhite},
/*18*/  { {2.0, -1.0, -2.0}, NZNZ, ColorWhite},
/*19*/  { {3.0, -1.0, -2.0}, NZNZ, ColorWhite},
/*20*/  { {4.0, -1.0, -2.0}, NZNZ, ColorWhite},
/*21*/  { {5.0, -1.0, -2.0}, NZNZ, ColorWhite},
/*22*/  { {6.0, -1.0, -2.0}, NZNZ, ColorWhite},
/*23*/  { {7.0, -1.0, -2.0}, NZNZ, ColorWhite},
/*24*/  { {8.0, -1.0, -2.0}, NZNZ, ColorWhite},

/*25*/  { {0.0, -1.0, -3.0}, NZNZ, ColorWhite},
/*26*/  { {1.0, -1.0, -3.0}, NZNZ, ColorWhite},
/*27*/  { {2.0, -1.0, -3.0}, NZNZ, ColorWhite},
/*28*/  { {3.0, -1.0, -3.0}, NZNZ, ColorWhite},
/*29*/  { {4.0, -1.0, -3.0}, NZNZ, ColorWhite},
/*30*/  { {5.0, -1.0, -3.0}, NZNZ, ColorWhite},
/*31*/  { {6.0, -1.0, -3.0}, NZNZ, ColorWhite},
/*32*/  { {7.0, -1.0, -3.0}, NZNZ, ColorWhite},
/*33*/  { {8.0, -1.0, -3.0}, NZNZ, ColorWhite},

/*34*/  { {0.0, -1.0, -4.0}, NZNZ, ColorWhite},
/*35*/  { {1.0, -1.0, -4.0}, NZNZ, ColorWhite},
/*36*/  { {2.0, -1.0, -4.0}, NZNZ, ColorWhite},
/*37*/  { {3.0, -1.0, -4.0}, NZNZ, ColorWhite},
/*38*/  { {4.0, -1.0, -4.0}, NZNZ, ColorWhite},
/*39*/  { {5.0, -1.0, -4.0}, NZNZ, ColorWhite},
/*40*/  { {6.0, -1.0, -4.0}, NZNZ, ColorWhite},
/*41*/  { {7.0, -1.0, -4.0}, NZNZ, ColorWhite},
/*42*/  { {8.0, -1.0, -4.0}, NZNZ, ColorWhite},

/*43*/  { {0.0, -1.0, -5.0}, NZNZ, ColorWhite},
/*44*/  { {1.0, -1.0, -5.0}, NZNZ, ColorWhite},
/*45*/  { {2.0, -1.0, -5.0}, NZNZ, ColorWhite},
/*46*/  { {3.0, -1.0, -5.0}, NZNZ, ColorWhite},
/*47*/  { {5.0, -1.0, -5.0}, NZNZ, ColorWhite},
/*48*/  { {6.0, -1.0, -5.0}, NZNZ, ColorWhite},
/*49*/  { {7.0, -1.0, -5.0}, NZNZ, ColorWhite},
/*50*/  { {8.0, -1.0, -5.0}, NZNZ, ColorWhite},

/*51*/  { {0.0, -1.0, -6.0}, NZNZ, ColorWhite},
/*52*/  { {1.0, -1.0, -6.0}, NZNZ, ColorWhite},
/*53*/  { {2.0, -1.0, -6.0}, NZNZ, ColorWhite},
/*54*/  { {3.0, -1.0, -6.0}, NZNZ, ColorWhite},
/*55*/  { {5.0, -1.0, -6.0}, NZNZ, ColorWhite},
/*56*/  { {6.0, -1.0, -6.0}, NZNZ, ColorWhite},
/*57*/  { {7.0, -1.0, -6.0}, NZNZ, ColorWhite},
/*58*/  { {8.0, -1.0, -6.0}, NZNZ, ColorWhite},

/*59*/  { {0.0, -1.0, -7.0}, NZNZ, ColorWhite},
/*60*/  { {1.0, -1.0, -7.0}, NZNZ, ColorWhite},
/*61*/  { {2.0, -1.0, -7.0}, NZNZ, ColorWhite},
/*62*/  { {6.0, -1.0, -7.0}, NZNZ, ColorWhite},
/*63*/  { {7.0, -1.0, -7.0}, NZNZ, ColorWhite},
/*64*/  { {8.0, -1.0, -7.0}, NZNZ, ColorWhite},

/*65*/  { {0.0, -1.0, -8.0}, NZNZ, ColorWhite},
/*66*/  { {1.0, -1.0, -8.0}, NZNZ, ColorWhite},
/*67*/  { {2.0, -1.0, -8.0}, NZNZ, ColorWhite},
/*68*/  { {3.0, -1.0, -8.0}, NZNZ, ColorWhite},
/*69*/  { {4.0, -1.0, -8.0}, NZNZ, ColorWhite},
/*70*/  { {5.0, -1.0, -8.0}, NZNZ, ColorWhite},
/*71*/  { {6.0, -1.0, -8.0}, NZNZ, ColorWhite},
/*72*/  { {7.0, -1.0, -8.0}, NZNZ, ColorWhite},
/*73*/  { {8.0, -1.0, -8.0}, NZNZ, ColorWhite},

/*74*/  { {1.0, -1.0, -9.0}, NZNZ, ColorWhite},
/*75*/  { {2.0, -1.0, -9.0}, NZNZ, ColorWhite},
/*76*/  { {3.0, -1.0, -9.0}, NZNZ, ColorWhite},
/*77*/  { {4.0, -1.0, -9.0}, NZNZ, ColorWhite},
/*78*/  { {5.0, -1.0, -9.0}, NZNZ, ColorWhite},
/*79*/  { {6.0, -1.0, -9.0}, NZNZ, ColorWhite},
/*80*/  { {7.0, -1.0, -9.0}, NZNZ, ColorWhite},
// smiley back finish

// [0, 80] is 81

// 354

// any character white front start
/*0*/   { {0.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*1*/   { {1.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*2*/   { {2.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*3*/   { {3.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*4*/   { {4.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*5*/   { {5.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*6*/   { {6.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*7*/   { {7.0, 0.0, 0.0}, NZPZ, ColorWhite},
/*8*/   { {8.0, 0.0, 0.0}, NZPZ, ColorWhite},

/*9*/   { {0.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*10*/  { {1.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*11*/  { {2.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*12*/  { {3.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*13*/  { {4.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*14*/  { {5.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*15*/  { {6.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*16*/  { {7.0, 0.0, -1.0}, NZPZ, ColorWhite},
/*17*/  { {8.0, 0.0, -1.0}, NZPZ, ColorWhite},

/*18*/  { {0.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*19*/  { {1.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*20*/  { {2.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*21*/  { {3.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*22*/  { {4.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*23*/  { {5.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*24*/  { {6.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*25*/  { {7.0, 0.0, -2.0}, NZPZ, ColorWhite},
/*26*/  { {8.0, 0.0, -2.0}, NZPZ, ColorWhite},

/*27*/  { {0.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*28*/  { {1.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*29*/  { {2.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*30*/  { {3.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*31*/  { {4.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*32*/  { {5.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*33*/  { {6.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*34*/  { {7.0, 0.0, -3.0}, NZPZ, ColorWhite},
/*35*/  { {8.0, 0.0, -3.0}, NZPZ, ColorWhite},

/*36*/  { {0.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*37*/  { {1.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*38*/  { {2.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*39*/  { {3.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*40*/  { {4.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*41*/  { {5.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*42*/  { {6.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*43*/  { {7.0, 0.0, -4.0}, NZPZ, ColorWhite},
/*44*/  { {8.0, 0.0, -4.0}, NZPZ, ColorWhite},

/*45*/  { {0.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*46*/  { {1.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*47*/  { {2.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*48*/  { {3.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*49*/  { {4.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*50*/  { {5.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*51*/  { {6.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*52*/  { {7.0, 0.0, -5.0}, NZPZ, ColorWhite},
/*53*/  { {8.0, 0.0, -5.0}, NZPZ, ColorWhite},

/*54*/  { {0.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*55*/  { {1.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*56*/  { {2.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*57*/  { {3.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*58*/  { {4.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*59*/  { {5.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*60*/  { {6.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*61*/  { {7.0, 0.0, -6.0}, NZPZ, ColorWhite},
/*62*/  { {8.0, 0.0, -6.0}, NZPZ, ColorWhite},

/*63*/  { {0.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*64*/  { {1.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*65*/  { {2.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*66*/  { {3.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*67*/  { {4.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*68*/  { {5.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*69*/  { {6.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*70*/  { {7.0, 0.0, -7.0}, NZPZ, ColorWhite},
/*71*/  { {8.0, 0.0, -7.0}, NZPZ, ColorWhite},

/*72*/  { {0.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*73*/  { {1.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*74*/  { {2.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*75*/  { {3.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*76*/  { {4.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*77*/  { {5.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*78*/  { {6.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*79*/  { {7.0, 0.0, -8.0}, NZPZ, ColorWhite},
/*80*/  { {8.0, 0.0, -8.0}, NZPZ, ColorWhite},

/*81*/  { {0.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*82*/  { {1.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*83*/  { {2.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*84*/  { {3.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*85*/  { {4.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*86*/  { {5.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*87*/  { {6.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*88*/  { {7.0, 0.0, -9.0}, NZPZ, ColorWhite},
/*89*/  { {8.0, 0.0, -9.0}, NZPZ, ColorWhite},

/*90*/  { {0.0, 0.0, -10.0}, NZPZ, ColorWhite},
/*91*/  { {1.0, 0.0, -10.0}, NZPZ, ColorWhite},
/*92*/  { {2.0, 0.0, -10.0}, NZPZ, ColorWhite},
/*93*/  { {3.0, 0.0, -10.0}, NZPZ, ColorWhite},
/*94*/  { {4.0, 0.0, -10.0}, NZPZ, ColorWhite},
/*95*/  { {5.0, 0.0, -10.0}, NZPZ, ColorWhite},
/*96*/  { {6.0, 0.0, -10.0}, NZPZ, ColorWhite},
/*97*/  { {7.0, 0.0, -10.0}, NZPZ, ColorWhite},
/*98*/  { {8.0, 0.0, -10.0}, NZPZ, ColorWhite},

/*99*/  { {0.0, 0.0, -11.0}, NZPZ, ColorWhite},
/*100*/ { {1.0, 0.0, -11.0}, NZPZ, ColorWhite},
/*101*/ { {2.0, 0.0, -11.0}, NZPZ, ColorWhite},
/*102*/ { {3.0, 0.0, -11.0}, NZPZ, ColorWhite},
/*103*/ { {4.0, 0.0, -11.0}, NZPZ, ColorWhite},
/*104*/ { {5.0, 0.0, -11.0}, NZPZ, ColorWhite},
/*105*/ { {6.0, 0.0, -11.0}, NZPZ, ColorWhite},
/*106*/ { {7.0, 0.0, -11.0}, NZPZ, ColorWhite},
/*107*/ { {8.0, 0.0, -11.0}, NZPZ, ColorWhite},

/*108*/ { {0.0, 0.0, -12.0}, NZPZ, ColorWhite},
/*109*/ { {1.0, 0.0, -12.0}, NZPZ, ColorWhite},
/*110*/ { {2.0, 0.0, -12.0}, NZPZ, ColorWhite},
/*111*/ { {3.0, 0.0, -12.0}, NZPZ, ColorWhite},
/*112*/ { {4.0, 0.0, -12.0}, NZPZ, ColorWhite},
/*113*/ { {5.0, 0.0, -12.0}, NZPZ, ColorWhite},
/*114*/ { {6.0, 0.0, -12.0}, NZPZ, ColorWhite},
/*115*/ { {7.0, 0.0, -12.0}, NZPZ, ColorWhite},
/*116*/ { {8.0, 0.0, -12.0}, NZPZ, ColorWhite},
// any character white front finish

// [0, 116] is 117

// 471

// any character white quad middle front start
/*0*/   { {0.5, 0.0, -0.5}, NZPZ, ColorWhite},
/*1*/   { {1.5, 0.0, -0.5}, NZPZ, ColorWhite},
/*2*/   { {2.5, 0.0, -0.5}, NZPZ, ColorWhite},
/*3*/   { {3.5, 0.0, -0.5}, NZPZ, ColorWhite},
/*4*/   { {4.5, 0.0, -0.5}, NZPZ, ColorWhite},
/*5*/   { {5.5, 0.0, -0.5}, NZPZ, ColorWhite},
/*6*/   { {6.5, 0.0, -0.5}, NZPZ, ColorWhite},
/*7*/   { {7.5, 0.0, -0.5}, NZPZ, ColorWhite},

/*8*/   { {0.5, 0.0, -1.5}, NZPZ, ColorWhite},
/*9*/   { {1.5, 0.0, -1.5}, NZPZ, ColorWhite},
/*10*/  { {2.5, 0.0, -1.5}, NZPZ, ColorWhite},
/*11*/  { {3.5, 0.0, -1.5}, NZPZ, ColorWhite},
/*12*/  { {4.5, 0.0, -1.5}, NZPZ, ColorWhite},
/*13*/  { {5.5, 0.0, -1.5}, NZPZ, ColorWhite},
/*14*/  { {6.5, 0.0, -1.5}, NZPZ, ColorWhite},
/*15*/  { {7.5, 0.0, -1.5}, NZPZ, ColorWhite},

/*16*/  { {0.5, 0.0, -2.5}, NZPZ, ColorWhite},
/*17*/  { {1.5, 0.0, -2.5}, NZPZ, ColorWhite},
/*18*/  { {2.5, 0.0, -2.5}, NZPZ, ColorWhite},
/*19*/  { {3.5, 0.0, -2.5}, NZPZ, ColorWhite},
/*20*/  { {4.5, 0.0, -2.5}, NZPZ, ColorWhite},
/*21*/  { {5.5, 0.0, -2.5}, NZPZ, ColorWhite},
/*22*/  { {6.5, 0.0, -2.5}, NZPZ, ColorWhite},
/*23*/  { {7.5, 0.0, -2.5}, NZPZ, ColorWhite},

/*24*/  { {0.5, 0.0, -3.5}, NZPZ, ColorWhite},
/*25*/  { {1.5, 0.0, -3.5}, NZPZ, ColorWhite},
/*26*/  { {2.5, 0.0, -3.5}, NZPZ, ColorWhite},
/*27*/  { {3.5, 0.0, -3.5}, NZPZ, ColorWhite},
/*28*/  { {4.5, 0.0, -3.5}, NZPZ, ColorWhite},
/*29*/  { {5.5, 0.0, -3.5}, NZPZ, ColorWhite},
/*30*/  { {6.5, 0.0, -3.5}, NZPZ, ColorWhite},
/*31*/  { {7.5, 0.0, -3.5}, NZPZ, ColorWhite},

/*32*/  { {0.5, 0.0, -4.5}, NZPZ, ColorWhite},
/*33*/  { {1.5, 0.0, -4.5}, NZPZ, ColorWhite},
/*34*/  { {2.5, 0.0, -4.5}, NZPZ, ColorWhite},
/*35*/  { {3.5, 0.0, -4.5}, NZPZ, ColorWhite},
/*36*/  { {4.5, 0.0, -4.5}, NZPZ, ColorWhite},
/*37*/  { {5.5, 0.0, -4.5}, NZPZ, ColorWhite},
/*38*/  { {6.5, 0.0, -4.5}, NZPZ, ColorWhite},
/*39*/  { {7.5, 0.0, -4.5}, NZPZ, ColorWhite},

/*40*/  { {0.5, 0.0, -5.5}, NZPZ, ColorWhite},
/*41*/  { {1.5, 0.0, -5.5}, NZPZ, ColorWhite},
/*42*/  { {2.5, 0.0, -5.5}, NZPZ, ColorWhite},
/*43*/  { {3.5, 0.0, -5.5}, NZPZ, ColorWhite},
/*44*/  { {4.5, 0.0, -5.5}, NZPZ, ColorWhite},
/*45*/  { {5.5, 0.0, -5.5}, NZPZ, ColorWhite},
/*46*/  { {6.5, 0.0, -5.5}, NZPZ, ColorWhite},
/*47*/  { {7.5, 0.0, -5.5}, NZPZ, ColorWhite},

/*48*/  { {0.5, 0.0, -6.5}, NZPZ, ColorWhite},
/*49*/  { {1.5, 0.0, -6.5}, NZPZ, ColorWhite},
/*50*/  { {2.5, 0.0, -6.5}, NZPZ, ColorWhite},
/*51*/  { {3.5, 0.0, -6.5}, NZPZ, ColorWhite},
/*52*/  { {4.5, 0.0, -6.5}, NZPZ, ColorWhite},
/*53*/  { {5.5, 0.0, -6.5}, NZPZ, ColorWhite},
/*54*/  { {6.5, 0.0, -6.5}, NZPZ, ColorWhite},
/*55*/  { {7.5, 0.0, -6.5}, NZPZ, ColorWhite},

/*56*/  { {0.5, 0.0, -7.5}, NZPZ, ColorWhite},
/*57*/  { {1.5, 0.0, -7.5}, NZPZ, ColorWhite},
/*58*/  { {2.5, 0.0, -7.5}, NZPZ, ColorWhite},
/*59*/  { {3.5, 0.0, -7.5}, NZPZ, ColorWhite},
/*60*/  { {4.5, 0.0, -7.5}, NZPZ, ColorWhite},
/*61*/  { {5.5, 0.0, -7.5}, NZPZ, ColorWhite},
/*62*/  { {6.5, 0.0, -7.5}, NZPZ, ColorWhite},
/*63*/  { {7.5, 0.0, -7.5}, NZPZ, ColorWhite},

/*64*/  { {0.5, 0.0, -8.5}, NZPZ, ColorWhite},
/*65*/  { {1.5, 0.0, -8.5}, NZPZ, ColorWhite},
/*66*/  { {2.5, 0.0, -8.5}, NZPZ, ColorWhite},
/*67*/  { {3.5, 0.0, -8.5}, NZPZ, ColorWhite},
/*68*/  { {4.5, 0.0, -8.5}, NZPZ, ColorWhite},
/*69*/  { {5.5, 0.0, -8.5}, NZPZ, ColorWhite},
/*70*/  { {6.5, 0.0, -8.5}, NZPZ, ColorWhite},
/*71*/  { {7.5, 0.0, -8.5}, NZPZ, ColorWhite},

/*72*/  { {0.5, 0.0, -9.5}, NZPZ, ColorWhite},
/*73*/  { {1.5, 0.0, -9.5}, NZPZ, ColorWhite},
/*74*/  { {2.5, 0.0, -9.5}, NZPZ, ColorWhite},
/*75*/  { {3.5, 0.0, -9.5}, NZPZ, ColorWhite},
/*76*/  { {4.5, 0.0, -9.5}, NZPZ, ColorWhite},
/*77*/  { {5.5, 0.0, -9.5}, NZPZ, ColorWhite},
/*78*/  { {6.5, 0.0, -9.5}, NZPZ, ColorWhite},
/*79*/  { {7.5, 0.0, -9.5}, NZPZ, ColorWhite},

/*80*/  { {0.5, 0.0, -10.5}, NZPZ, ColorWhite},
/*81*/  { {1.5, 0.0, -10.5}, NZPZ, ColorWhite},
/*82*/  { {2.5, 0.0, -10.5}, NZPZ, ColorWhite},
/*83*/  { {3.5, 0.0, -10.5}, NZPZ, ColorWhite},
/*84*/  { {4.5, 0.0, -10.5}, NZPZ, ColorWhite},
/*85*/  { {5.5, 0.0, -10.5}, NZPZ, ColorWhite},
/*86*/  { {6.5, 0.0, -10.5}, NZPZ, ColorWhite},
/*87*/  { {7.5, 0.0, -10.5}, NZPZ, ColorWhite},

/*88*/  { {0.5, 0.0, -11.5}, NZPZ, ColorWhite},
/*89*/  { {1.5, 0.0, -11.5}, NZPZ, ColorWhite},
/*90*/  { {2.5, 0.0, -11.5}, NZPZ, ColorWhite},
/*91*/  { {3.5, 0.0, -11.5}, NZPZ, ColorWhite},
/*92*/  { {4.5, 0.0, -11.5}, NZPZ, ColorWhite},
/*93*/  { {5.5, 0.0, -11.5}, NZPZ, ColorWhite},
/*94*/  { {6.5, 0.0, -11.5}, NZPZ, ColorWhite},
/*95*/  { {7.5, 0.0, -11.5}, NZPZ, ColorWhite},
// any character white quad middle front finish

// [0, 95] is 96

// 567

// any character white back start
/*0*/   { {0.0, -2.0, 0.0}, NZNZ, ColorWhite},
/*1*/   { {1.0, -2.0, 0.0}, NZNZ, ColorWhite},
/*2*/   { {2.0, -2.0, 0.0}, NZNZ, ColorWhite},
/*3*/   { {3.0, -2.0, 0.0}, NZNZ, ColorWhite},
/*4*/   { {4.0, -2.0, 0.0}, NZNZ, ColorWhite},
/*5*/   { {5.0, -2.0, 0.0}, NZNZ, ColorWhite},
/*6*/   { {6.0, -2.0, 0.0}, NZNZ, ColorWhite},
/*7*/   { {7.0, -2.0, 0.0}, NZNZ, ColorWhite},
/*8*/   { {8.0, -2.0, 0.0}, NZNZ, ColorWhite},

/*9*/   { {0.0, -2.0, -1.0}, NZNZ, ColorWhite},
/*10*/  { {1.0, -2.0, -1.0}, NZNZ, ColorWhite},
/*11*/  { {2.0, -2.0, -1.0}, NZNZ, ColorWhite},
/*12*/  { {3.0, -2.0, -1.0}, NZNZ, ColorWhite},
/*13*/  { {4.0, -2.0, -1.0}, NZNZ, ColorWhite},
/*14*/  { {5.0, -2.0, -1.0}, NZNZ, ColorWhite},
/*15*/  { {6.0, -2.0, -1.0}, NZNZ, ColorWhite},
/*16*/  { {7.0, -2.0, -1.0}, NZNZ, ColorWhite},
/*17*/  { {8.0, -2.0, -1.0}, NZNZ, ColorWhite},

/*18*/  { {0.0, -2.0, -2.0}, NZNZ, ColorWhite},
/*19*/  { {1.0, -2.0, -2.0}, NZNZ, ColorWhite},
/*20*/  { {2.0, -2.0, -2.0}, NZNZ, ColorWhite},
/*21*/  { {3.0, -2.0, -2.0}, NZNZ, ColorWhite},
/*22*/  { {4.0, -2.0, -2.0}, NZNZ, ColorWhite},
/*23*/  { {5.0, -2.0, -2.0}, NZNZ, ColorWhite},
/*24*/  { {6.0, -2.0, -2.0}, NZNZ, ColorWhite},
/*25*/  { {7.0, -2.0, -2.0}, NZNZ, ColorWhite},
/*26*/  { {8.0, -2.0, -2.0}, NZNZ, ColorWhite},

/*27*/  { {0.0, -2.0, -3.0}, NZNZ, ColorWhite},
/*28*/  { {1.0, -2.0, -3.0}, NZNZ, ColorWhite},
/*29*/  { {2.0, -2.0, -3.0}, NZNZ, ColorWhite},
/*30*/  { {3.0, -2.0, -3.0}, NZNZ, ColorWhite},
/*31*/  { {4.0, -2.0, -3.0}, NZNZ, ColorWhite},
/*32*/  { {5.0, -2.0, -3.0}, NZNZ, ColorWhite},
/*33*/  { {6.0, -2.0, -3.0}, NZNZ, ColorWhite},
/*34*/  { {7.0, -2.0, -3.0}, NZNZ, ColorWhite},
/*35*/  { {8.0, -2.0, -3.0}, NZNZ, ColorWhite},

/*36*/  { {0.0, -2.0, -4.0}, NZNZ, ColorWhite},
/*37*/  { {1.0, -2.0, -4.0}, NZNZ, ColorWhite},
/*38*/  { {2.0, -2.0, -4.0}, NZNZ, ColorWhite},
/*39*/  { {3.0, -2.0, -4.0}, NZNZ, ColorWhite},
/*40*/  { {4.0, -2.0, -4.0}, NZNZ, ColorWhite},
/*41*/  { {5.0, -2.0, -4.0}, NZNZ, ColorWhite},
/*42*/  { {6.0, -2.0, -4.0}, NZNZ, ColorWhite},
/*43*/  { {7.0, -2.0, -4.0}, NZNZ, ColorWhite},
/*44*/  { {8.0, -2.0, -4.0}, NZNZ, ColorWhite},

/*45*/  { {0.0, -2.0, -5.0}, NZNZ, ColorWhite},
/*46*/  { {1.0, -2.0, -5.0}, NZNZ, ColorWhite},
/*47*/  { {2.0, -2.0, -5.0}, NZNZ, ColorWhite},
/*48*/  { {3.0, -2.0, -5.0}, NZNZ, ColorWhite},
/*49*/  { {4.0, -2.0, -5.0}, NZNZ, ColorWhite},
/*50*/  { {5.0, -2.0, -5.0}, NZNZ, ColorWhite},
/*51*/  { {6.0, -2.0, -5.0}, NZNZ, ColorWhite},
/*52*/  { {7.0, -2.0, -5.0}, NZNZ, ColorWhite},
/*53*/  { {8.0, -2.0, -5.0}, NZNZ, ColorWhite},

/*54*/  { {0.0, -2.0, -6.0}, NZNZ, ColorWhite},
/*55*/  { {1.0, -2.0, -6.0}, NZNZ, ColorWhite},
/*56*/  { {2.0, -2.0, -6.0}, NZNZ, ColorWhite},
/*57*/  { {3.0, -2.0, -6.0}, NZNZ, ColorWhite},
/*58*/  { {4.0, -2.0, -6.0}, NZNZ, ColorWhite},
/*59*/  { {5.0, -2.0, -6.0}, NZNZ, ColorWhite},
/*60*/  { {6.0, -2.0, -6.0}, NZNZ, ColorWhite},
/*61*/  { {7.0, -2.0, -6.0}, NZNZ, ColorWhite},
/*62*/  { {8.0, -2.0, -6.0}, NZNZ, ColorWhite},

/*63*/  { {0.0, -2.0, -7.0}, NZNZ, ColorWhite},
/*64*/  { {1.0, -2.0, -7.0}, NZNZ, ColorWhite},
/*65*/  { {2.0, -2.0, -7.0}, NZNZ, ColorWhite},
/*66*/  { {3.0, -2.0, -7.0}, NZNZ, ColorWhite},
/*67*/  { {4.0, -2.0, -7.0}, NZNZ, ColorWhite},
/*68*/  { {5.0, -2.0, -7.0}, NZNZ, ColorWhite},
/*69*/  { {6.0, -2.0, -7.0}, NZNZ, ColorWhite},
/*70*/  { {7.0, -2.0, -7.0}, NZNZ, ColorWhite},
/*71*/  { {8.0, -2.0, -7.0}, NZNZ, ColorWhite},

/*72*/  { {0.0, -2.0, -8.0}, NZNZ, ColorWhite},
/*73*/  { {1.0, -2.0, -8.0}, NZNZ, ColorWhite},
/*74*/  { {2.0, -2.0, -8.0}, NZNZ, ColorWhite},
/*75*/  { {3.0, -2.0, -8.0}, NZNZ, ColorWhite},
/*76*/  { {4.0, -2.0, -8.0}, NZNZ, ColorWhite},
/*77*/  { {5.0, -2.0, -8.0}, NZNZ, ColorWhite},
/*78*/  { {6.0, -2.0, -8.0}, NZNZ, ColorWhite},
/*79*/  { {7.0, -2.0, -8.0}, NZNZ, ColorWhite},
/*80*/  { {8.0, -2.0, -8.0}, NZNZ, ColorWhite},

/*81*/  { {0.0, -2.0, -9.0}, NZNZ, ColorWhite},
/*82*/  { {1.0, -2.0, -9.0}, NZNZ, ColorWhite},
/*83*/  { {2.0, -2.0, -9.0}, NZNZ, ColorWhite},
/*84*/  { {3.0, -2.0, -9.0}, NZNZ, ColorWhite},
/*85*/  { {4.0, -2.0, -9.0}, NZNZ, ColorWhite},
/*86*/  { {5.0, -2.0, -9.0}, NZNZ, ColorWhite},
/*87*/  { {6.0, -2.0, -9.0}, NZNZ, ColorWhite},
/*88*/  { {7.0, -2.0, -9.0}, NZNZ, ColorWhite},
/*89*/  { {8.0, -2.0, -9.0}, NZNZ, ColorWhite},

/*90*/  { {0.0, -2.0, -10.0}, NZNZ, ColorWhite},
/*91*/  { {1.0, -2.0, -10.0}, NZNZ, ColorWhite},
/*92*/  { {2.0, -2.0, -10.0}, NZNZ, ColorWhite},
/*93*/  { {3.0, -2.0, -10.0}, NZNZ, ColorWhite},
/*94*/  { {4.0, -2.0, -10.0}, NZNZ, ColorWhite},
/*95*/  { {5.0, -2.0, -10.0}, NZNZ, ColorWhite},
/*96*/  { {6.0, -2.0, -10.0}, NZNZ, ColorWhite},
/*97*/  { {7.0, -2.0, -10.0}, NZNZ, ColorWhite},
/*98*/  { {8.0, -2.0, -10.0}, NZNZ, ColorWhite},

/*99*/  { {0.0, -2.0, -11.0}, NZNZ, ColorWhite},
/*100*/ { {1.0, -2.0, -11.0}, NZNZ, ColorWhite},
/*101*/ { {2.0, -2.0, -11.0}, NZNZ, ColorWhite},
/*102*/ { {3.0, -2.0, -11.0}, NZNZ, ColorWhite},
/*103*/ { {4.0, -2.0, -11.0}, NZNZ, ColorWhite},
/*104*/ { {5.0, -2.0, -11.0}, NZNZ, ColorWhite},
/*105*/ { {6.0, -2.0, -11.0}, NZNZ, ColorWhite},
/*106*/ { {7.0, -2.0, -11.0}, NZNZ, ColorWhite},
/*107*/ { {8.0, -2.0, -11.0}, NZNZ, ColorWhite},

/*108*/ { {0.0, -2.0, -12.0}, NZNZ, ColorWhite},
/*109*/ { {1.0, -2.0, -12.0}, NZNZ, ColorWhite},
/*110*/ { {2.0, -2.0, -12.0}, NZNZ, ColorWhite},
/*111*/ { {3.0, -2.0, -12.0}, NZNZ, ColorWhite},
/*112*/ { {4.0, -2.0, -12.0}, NZNZ, ColorWhite},
/*113*/ { {5.0, -2.0, -12.0}, NZNZ, ColorWhite},
/*114*/ { {6.0, -2.0, -12.0}, NZNZ, ColorWhite},
/*115*/ { {7.0, -2.0, -12.0}, NZNZ, ColorWhite},
/*116*/ { {8.0, -2.0, -12.0}, NZNZ, ColorWhite},
// any character white back finish

// [0, 116] is 117

// 684

// any character white quad middle back start
/*0*/   { {0.5, -2.0, -0.5}, NZNZ, ColorWhite},
/*1*/   { {1.5, -2.0, -0.5}, NZNZ, ColorWhite},
/*2*/   { {2.5, -2.0, -0.5}, NZNZ, ColorWhite},
/*3*/   { {3.5, -2.0, -0.5}, NZNZ, ColorWhite},
/*4*/   { {4.5, -2.0, -0.5}, NZNZ, ColorWhite},
/*5*/   { {5.5, -2.0, -0.5}, NZNZ, ColorWhite},
/*6*/   { {6.5, -2.0, -0.5}, NZNZ, ColorWhite},
/*7*/   { {7.5, -2.0, -0.5}, NZNZ, ColorWhite},

/*8*/   { {0.5, -2.0, -1.5}, NZNZ, ColorWhite},
/*9*/   { {1.5, -2.0, -1.5}, NZNZ, ColorWhite},
/*10*/  { {2.5, -2.0, -1.5}, NZNZ, ColorWhite},
/*11*/  { {3.5, -2.0, -1.5}, NZNZ, ColorWhite},
/*12*/  { {4.5, -2.0, -1.5}, NZNZ, ColorWhite},
/*13*/  { {5.5, -2.0, -1.5}, NZNZ, ColorWhite},
/*14*/  { {6.5, -2.0, -1.5}, NZNZ, ColorWhite},
/*15*/  { {7.5, -2.0, -1.5}, NZNZ, ColorWhite},

/*16*/  { {0.5, -2.0, -2.5}, NZNZ, ColorWhite},
/*17*/  { {1.5, -2.0, -2.5}, NZNZ, ColorWhite},
/*18*/  { {2.5, -2.0, -2.5}, NZNZ, ColorWhite},
/*19*/  { {3.5, -2.0, -2.5}, NZNZ, ColorWhite},
/*20*/  { {4.5, -2.0, -2.5}, NZNZ, ColorWhite},
/*21*/  { {5.5, -2.0, -2.5}, NZNZ, ColorWhite},
/*22*/  { {6.5, -2.0, -2.5}, NZNZ, ColorWhite},
/*23*/  { {7.5, -2.0, -2.5}, NZNZ, ColorWhite},

/*24*/  { {0.5, -2.0, -3.5}, NZNZ, ColorWhite},
/*25*/  { {1.5, -2.0, -3.5}, NZNZ, ColorWhite},
/*26*/  { {2.5, -2.0, -3.5}, NZNZ, ColorWhite},
/*27*/  { {3.5, -2.0, -3.5}, NZNZ, ColorWhite},
/*28*/  { {4.5, -2.0, -3.5}, NZNZ, ColorWhite},
/*29*/  { {5.5, -2.0, -3.5}, NZNZ, ColorWhite},
/*30*/  { {6.5, -2.0, -3.5}, NZNZ, ColorWhite},
/*31*/  { {7.5, -2.0, -3.5}, NZNZ, ColorWhite},

/*32*/  { {0.5, -2.0, -4.5}, NZNZ, ColorWhite},
/*33*/  { {1.5, -2.0, -4.5}, NZNZ, ColorWhite},
/*34*/  { {2.5, -2.0, -4.5}, NZNZ, ColorWhite},
/*35*/  { {3.5, -2.0, -4.5}, NZNZ, ColorWhite},
/*36*/  { {4.5, -2.0, -4.5}, NZNZ, ColorWhite},
/*37*/  { {5.5, -2.0, -4.5}, NZNZ, ColorWhite},
/*38*/  { {6.5, -2.0, -4.5}, NZNZ, ColorWhite},
/*39*/  { {7.5, -2.0, -4.5}, NZNZ, ColorWhite},

/*40*/  { {0.5, -2.0, -5.5}, NZNZ, ColorWhite},
/*41*/  { {1.5, -2.0, -5.5}, NZNZ, ColorWhite},
/*42*/  { {2.5, -2.0, -5.5}, NZNZ, ColorWhite},
/*43*/  { {3.5, -2.0, -5.5}, NZNZ, ColorWhite},
/*44*/  { {4.5, -2.0, -5.5}, NZNZ, ColorWhite},
/*45*/  { {5.5, -2.0, -5.5}, NZNZ, ColorWhite},
/*46*/  { {6.5, -2.0, -5.5}, NZNZ, ColorWhite},
/*47*/  { {7.5, -2.0, -5.5}, NZNZ, ColorWhite},

/*48*/  { {0.5, -2.0, -6.5}, NZNZ, ColorWhite},
/*49*/  { {1.5, -2.0, -6.5}, NZNZ, ColorWhite},
/*50*/  { {2.5, -2.0, -6.5}, NZNZ, ColorWhite},
/*51*/  { {3.5, -2.0, -6.5}, NZNZ, ColorWhite},
/*52*/  { {4.5, -2.0, -6.5}, NZNZ, ColorWhite},
/*53*/  { {5.5, -2.0, -6.5}, NZNZ, ColorWhite},
/*54*/  { {6.5, -2.0, -6.5}, NZNZ, ColorWhite},
/*55*/  { {7.5, -2.0, -6.5}, NZNZ, ColorWhite},

/*56*/  { {0.5, -2.0, -7.5}, NZNZ, ColorWhite},
/*57*/  { {1.5, -2.0, -7.5}, NZNZ, ColorWhite},
/*58*/  { {2.5, -2.0, -7.5}, NZNZ, ColorWhite},
/*59*/  { {3.5, -2.0, -7.5}, NZNZ, ColorWhite},
/*60*/  { {4.5, -2.0, -7.5}, NZNZ, ColorWhite},
/*61*/  { {5.5, -2.0, -7.5}, NZNZ, ColorWhite},
/*62*/  { {6.5, -2.0, -7.5}, NZNZ, ColorWhite},
/*63*/  { {7.5, -2.0, -7.5}, NZNZ, ColorWhite},

/*64*/  { {0.5, -2.0, -8.5}, NZNZ, ColorWhite},
/*65*/  { {1.5, -2.0, -8.5}, NZNZ, ColorWhite},
/*66*/  { {2.5, -2.0, -8.5}, NZNZ, ColorWhite},
/*67*/  { {3.5, -2.0, -8.5}, NZNZ, ColorWhite},
/*68*/  { {4.5, -2.0, -8.5}, NZNZ, ColorWhite},
/*69*/  { {5.5, -2.0, -8.5}, NZNZ, ColorWhite},
/*70*/  { {6.5, -2.0, -8.5}, NZNZ, ColorWhite},
/*71*/  { {7.5, -2.0, -8.5}, NZNZ, ColorWhite},

/*72*/  { {0.5, -2.0, -9.5}, NZNZ, ColorWhite},
/*73*/  { {1.5, -2.0, -9.5}, NZNZ, ColorWhite},
/*74*/  { {2.5, -2.0, -9.5}, NZNZ, ColorWhite},
/*75*/  { {3.5, -2.0, -9.5}, NZNZ, ColorWhite},
/*76*/  { {4.5, -2.0, -9.5}, NZNZ, ColorWhite},
/*77*/  { {5.5, -2.0, -9.5}, NZNZ, ColorWhite},
/*78*/  { {6.5, -2.0, -9.5}, NZNZ, ColorWhite},
/*79*/  { {7.5, -2.0, -9.5}, NZNZ, ColorWhite},

/*80*/  { {0.5, -2.0, -10.5}, NZNZ, ColorWhite},
/*81*/  { {1.5, -2.0, -10.5}, NZNZ, ColorWhite},
/*82*/  { {2.5, -2.0, -10.5}, NZNZ, ColorWhite},
/*83*/  { {3.5, -2.0, -10.5}, NZNZ, ColorWhite},
/*84*/  { {4.5, -2.0, -10.5}, NZNZ, ColorWhite},
/*85*/  { {5.5, -2.0, -10.5}, NZNZ, ColorWhite},
/*86*/  { {6.5, -2.0, -10.5}, NZNZ, ColorWhite},
/*87*/  { {7.5, -2.0, -10.5}, NZNZ, ColorWhite},

/*88*/  { {0.5, -2.0, -11.5}, NZNZ, ColorWhite},
/*89*/  { {1.5, -2.0, -11.5}, NZNZ, ColorWhite},
/*90*/  { {2.5, -2.0, -11.5}, NZNZ, ColorWhite},
/*91*/  { {3.5, -2.0, -11.5}, NZNZ, ColorWhite},
/*92*/  { {4.5, -2.0, -11.5}, NZNZ, ColorWhite},
/*93*/  { {5.5, -2.0, -11.5}, NZNZ, ColorWhite},
/*94*/  { {6.5, -2.0, -11.5}, NZNZ, ColorWhite},
/*95*/  { {7.5, -2.0, -11.5}, NZNZ, ColorWhite},
// any character white quad middle back finish

// [0, 95] is 96

// 780

// any character white left front start
/*0*/   { {0.0, 0.0, 0.0}, NNZZ, ColorWhite},
/*1*/   { {1.0, 0.0, 0.0}, NNZZ, ColorWhite},
/*2*/   { {2.0, 0.0, 0.0}, NNZZ, ColorWhite},
/*3*/   { {3.0, 0.0, 0.0}, NNZZ, ColorWhite},
/*4*/   { {4.0, 0.0, 0.0}, NNZZ, ColorWhite},
/*5*/   { {5.0, 0.0, 0.0}, NNZZ, ColorWhite},
/*6*/   { {6.0, 0.0, 0.0}, NNZZ, ColorWhite},
/*7*/   { {7.0, 0.0, 0.0}, NNZZ, ColorWhite},
/*8*/   { {8.0, 0.0, 0.0}, NNZZ, ColorWhite},

/*9*/   { {0.0, 0.0, -1.0}, NNZZ, ColorWhite},
/*10*/  { {1.0, 0.0, -1.0}, NNZZ, ColorWhite},
/*11*/  { {2.0, 0.0, -1.0}, NNZZ, ColorWhite},
/*12*/  { {3.0, 0.0, -1.0}, NNZZ, ColorWhite},
/*13*/  { {4.0, 0.0, -1.0}, NNZZ, ColorWhite},
/*14*/  { {5.0, 0.0, -1.0}, NNZZ, ColorWhite},
/*15*/  { {6.0, 0.0, -1.0}, NNZZ, ColorWhite},
/*16*/  { {7.0, 0.0, -1.0}, NNZZ, ColorWhite},
/*17*/  { {8.0, 0.0, -1.0}, NNZZ, ColorWhite},

/*18*/  { {0.0, 0.0, -2.0}, NNZZ, ColorWhite},
/*19*/  { {1.0, 0.0, -2.0}, NNZZ, ColorWhite},
/*20*/  { {2.0, 0.0, -2.0}, NNZZ, ColorWhite},
/*21*/  { {3.0, 0.0, -2.0}, NNZZ, ColorWhite},
/*22*/  { {4.0, 0.0, -2.0}, NNZZ, ColorWhite},
/*23*/  { {5.0, 0.0, -2.0}, NNZZ, ColorWhite},
/*24*/  { {6.0, 0.0, -2.0}, NNZZ, ColorWhite},
/*25*/  { {7.0, 0.0, -2.0}, NNZZ, ColorWhite},
/*26*/  { {8.0, 0.0, -2.0}, NNZZ, ColorWhite},

/*27*/  { {0.0, 0.0, -3.0}, NNZZ, ColorWhite},
/*28*/  { {1.0, 0.0, -3.0}, NNZZ, ColorWhite},
/*29*/  { {2.0, 0.0, -3.0}, NNZZ, ColorWhite},
/*30*/  { {3.0, 0.0, -3.0}, NNZZ, ColorWhite},
/*31*/  { {4.0, 0.0, -3.0}, NNZZ, ColorWhite},
/*32*/  { {5.0, 0.0, -3.0}, NNZZ, ColorWhite},
/*33*/  { {6.0, 0.0, -3.0}, NNZZ, ColorWhite},
/*34*/  { {7.0, 0.0, -3.0}, NNZZ, ColorWhite},
/*35*/  { {8.0, 0.0, -3.0}, NNZZ, ColorWhite},

/*36*/  { {0.0, 0.0, -4.0}, NNZZ, ColorWhite},
/*37*/  { {1.0, 0.0, -4.0}, NNZZ, ColorWhite},
/*38*/  { {2.0, 0.0, -4.0}, NNZZ, ColorWhite},
/*39*/  { {3.0, 0.0, -4.0}, NNZZ, ColorWhite},
/*40*/  { {4.0, 0.0, -4.0}, NNZZ, ColorWhite},
/*41*/  { {5.0, 0.0, -4.0}, NNZZ, ColorWhite},
/*42*/  { {6.0, 0.0, -4.0}, NNZZ, ColorWhite},
/*43*/  { {7.0, 0.0, -4.0}, NNZZ, ColorWhite},
/*44*/  { {8.0, 0.0, -4.0}, NNZZ, ColorWhite},

/*45*/  { {0.0, 0.0, -5.0}, NNZZ, ColorWhite},
/*46*/  { {1.0, 0.0, -5.0}, NNZZ, ColorWhite},
/*47*/  { {2.0, 0.0, -5.0}, NNZZ, ColorWhite},
/*48*/  { {3.0, 0.0, -5.0}, NNZZ, ColorWhite},
/*49*/  { {4.0, 0.0, -5.0}, NNZZ, ColorWhite},
/*50*/  { {5.0, 0.0, -5.0}, NNZZ, ColorWhite},
/*51*/  { {6.0, 0.0, -5.0}, NNZZ, ColorWhite},
/*52*/  { {7.0, 0.0, -5.0}, NNZZ, ColorWhite},
/*53*/  { {8.0, 0.0, -5.0}, NNZZ, ColorWhite},

/*54*/  { {0.0, 0.0, -6.0}, NNZZ, ColorWhite},
/*55*/  { {1.0, 0.0, -6.0}, NNZZ, ColorWhite},
/*56*/  { {2.0, 0.0, -6.0}, NNZZ, ColorWhite},
/*57*/  { {3.0, 0.0, -6.0}, NNZZ, ColorWhite},
/*58*/  { {4.0, 0.0, -6.0}, NNZZ, ColorWhite},
/*59*/  { {5.0, 0.0, -6.0}, NNZZ, ColorWhite},
/*60*/  { {6.0, 0.0, -6.0}, NNZZ, ColorWhite},
/*61*/  { {7.0, 0.0, -6.0}, NNZZ, ColorWhite},
/*62*/  { {8.0, 0.0, -6.0}, NNZZ, ColorWhite},

/*63*/  { {0.0, 0.0, -7.0}, NNZZ, ColorWhite},
/*64*/  { {1.0, 0.0, -7.0}, NNZZ, ColorWhite},
/*65*/  { {2.0, 0.0, -7.0}, NNZZ, ColorWhite},
/*66*/  { {3.0, 0.0, -7.0}, NNZZ, ColorWhite},
/*67*/  { {4.0, 0.0, -7.0}, NNZZ, ColorWhite},
/*68*/  { {5.0, 0.0, -7.0}, NNZZ, ColorWhite},
/*69*/  { {6.0, 0.0, -7.0}, NNZZ, ColorWhite},
/*70*/  { {7.0, 0.0, -7.0}, NNZZ, ColorWhite},
/*71*/  { {8.0, 0.0, -7.0}, NNZZ, ColorWhite},

/*72*/  { {0.0, 0.0, -8.0}, NNZZ, ColorWhite},
/*73*/  { {1.0, 0.0, -8.0}, NNZZ, ColorWhite},
/*74*/  { {2.0, 0.0, -8.0}, NNZZ, ColorWhite},
/*75*/  { {3.0, 0.0, -8.0}, NNZZ, ColorWhite},
/*76*/  { {4.0, 0.0, -8.0}, NNZZ, ColorWhite},
/*77*/  { {5.0, 0.0, -8.0}, NNZZ, ColorWhite},
/*78*/  { {6.0, 0.0, -8.0}, NNZZ, ColorWhite},
/*79*/  { {7.0, 0.0, -8.0}, NNZZ, ColorWhite},
/*80*/  { {8.0, 0.0, -8.0}, NNZZ, ColorWhite},

/*81*/  { {0.0, 0.0, -9.0}, NNZZ, ColorWhite},
/*82*/  { {1.0, 0.0, -9.0}, NNZZ, ColorWhite},
/*83*/  { {2.0, 0.0, -9.0}, NNZZ, ColorWhite},
/*84*/  { {3.0, 0.0, -9.0}, NNZZ, ColorWhite},
/*85*/  { {4.0, 0.0, -9.0}, NNZZ, ColorWhite},
/*86*/  { {5.0, 0.0, -9.0}, NNZZ, ColorWhite},
/*87*/  { {6.0, 0.0, -9.0}, NNZZ, ColorWhite},
/*88*/  { {7.0, 0.0, -9.0}, NNZZ, ColorWhite},
/*89*/  { {8.0, 0.0, -9.0}, NNZZ, ColorWhite},

/*90*/  { {0.0, 0.0, -10.0}, NNZZ, ColorWhite},
/*91*/  { {1.0, 0.0, -10.0}, NNZZ, ColorWhite},
/*92*/  { {2.0, 0.0, -10.0}, NNZZ, ColorWhite},
/*93*/  { {3.0, 0.0, -10.0}, NNZZ, ColorWhite},
/*94*/  { {4.0, 0.0, -10.0}, NNZZ, ColorWhite},
/*95*/  { {5.0, 0.0, -10.0}, NNZZ, ColorWhite},
/*96*/  { {6.0, 0.0, -10.0}, NNZZ, ColorWhite},
/*97*/  { {7.0, 0.0, -10.0}, NNZZ, ColorWhite},
/*98*/  { {8.0, 0.0, -10.0}, NNZZ, ColorWhite},

/*99*/  { {0.0, 0.0, -11.0}, NNZZ, ColorWhite},
/*100*/ { {1.0, 0.0, -11.0}, NNZZ, ColorWhite},
/*101*/ { {2.0, 0.0, -11.0}, NNZZ, ColorWhite},
/*102*/ { {3.0, 0.0, -11.0}, NNZZ, ColorWhite},
/*103*/ { {4.0, 0.0, -11.0}, NNZZ, ColorWhite},
/*104*/ { {5.0, 0.0, -11.0}, NNZZ, ColorWhite},
/*105*/ { {6.0, 0.0, -11.0}, NNZZ, ColorWhite},
/*106*/ { {7.0, 0.0, -11.0}, NNZZ, ColorWhite},
/*107*/ { {8.0, 0.0, -11.0}, NNZZ, ColorWhite},

/*108*/ { {0.0, 0.0, -12.0}, NNZZ, ColorWhite},
/*109*/ { {1.0, 0.0, -12.0}, NNZZ, ColorWhite},
/*110*/ { {2.0, 0.0, -12.0}, NNZZ, ColorWhite},
/*111*/ { {3.0, 0.0, -12.0}, NNZZ, ColorWhite},
/*112*/ { {4.0, 0.0, -12.0}, NNZZ, ColorWhite},
/*113*/ { {5.0, 0.0, -12.0}, NNZZ, ColorWhite},
/*114*/ { {6.0, 0.0, -12.0}, NNZZ, ColorWhite},
/*115*/ { {7.0, 0.0, -12.0}, NNZZ, ColorWhite},
/*116*/ { {8.0, 0.0, -12.0}, NNZZ, ColorWhite},
// any character white left front finish

// [0, 116] is 117

// 897

// any character white left back start
/*0*/   { {0.0, -2.0, 0.0}, NNZZ, ColorWhite},
/*1*/   { {1.0, -2.0, 0.0}, NNZZ, ColorWhite},
/*2*/   { {2.0, -2.0, 0.0}, NNZZ, ColorWhite},
/*3*/   { {3.0, -2.0, 0.0}, NNZZ, ColorWhite},
/*4*/   { {4.0, -2.0, 0.0}, NNZZ, ColorWhite},
/*5*/   { {5.0, -2.0, 0.0}, NNZZ, ColorWhite},
/*6*/   { {6.0, -2.0, 0.0}, NNZZ, ColorWhite},
/*7*/   { {7.0, -2.0, 0.0}, NNZZ, ColorWhite},
/*8*/   { {8.0, -2.0, 0.0}, NNZZ, ColorWhite},

/*9*/   { {0.0, -2.0, -1.0}, NNZZ, ColorWhite},
/*10*/  { {1.0, -2.0, -1.0}, NNZZ, ColorWhite},
/*11*/  { {2.0, -2.0, -1.0}, NNZZ, ColorWhite},
/*12*/  { {3.0, -2.0, -1.0}, NNZZ, ColorWhite},
/*13*/  { {4.0, -2.0, -1.0}, NNZZ, ColorWhite},
/*14*/  { {5.0, -2.0, -1.0}, NNZZ, ColorWhite},
/*15*/  { {6.0, -2.0, -1.0}, NNZZ, ColorWhite},
/*16*/  { {7.0, -2.0, -1.0}, NNZZ, ColorWhite},
/*17*/  { {8.0, -2.0, -1.0}, NNZZ, ColorWhite},

/*18*/  { {0.0, -2.0, -2.0}, NNZZ, ColorWhite},
/*19*/  { {1.0, -2.0, -2.0}, NNZZ, ColorWhite},
/*20*/  { {2.0, -2.0, -2.0}, NNZZ, ColorWhite},
/*21*/  { {3.0, -2.0, -2.0}, NNZZ, ColorWhite},
/*22*/  { {4.0, -2.0, -2.0}, NNZZ, ColorWhite},
/*23*/  { {5.0, -2.0, -2.0}, NNZZ, ColorWhite},
/*24*/  { {6.0, -2.0, -2.0}, NNZZ, ColorWhite},
/*25*/  { {7.0, -2.0, -2.0}, NNZZ, ColorWhite},
/*26*/  { {8.0, -2.0, -2.0}, NNZZ, ColorWhite},

/*27*/  { {0.0, -2.0, -3.0}, NNZZ, ColorWhite},
/*28*/  { {1.0, -2.0, -3.0}, NNZZ, ColorWhite},
/*29*/  { {2.0, -2.0, -3.0}, NNZZ, ColorWhite},
/*30*/  { {3.0, -2.0, -3.0}, NNZZ, ColorWhite},
/*31*/  { {4.0, -2.0, -3.0}, NNZZ, ColorWhite},
/*32*/  { {5.0, -2.0, -3.0}, NNZZ, ColorWhite},
/*33*/  { {6.0, -2.0, -3.0}, NNZZ, ColorWhite},
/*34*/  { {7.0, -2.0, -3.0}, NNZZ, ColorWhite},
/*35*/  { {8.0, -2.0, -3.0}, NNZZ, ColorWhite},

/*36*/  { {0.0, -2.0, -4.0}, NNZZ, ColorWhite},
/*37*/  { {1.0, -2.0, -4.0}, NNZZ, ColorWhite},
/*38*/  { {2.0, -2.0, -4.0}, NNZZ, ColorWhite},
/*39*/  { {3.0, -2.0, -4.0}, NNZZ, ColorWhite},
/*40*/  { {4.0, -2.0, -4.0}, NNZZ, ColorWhite},
/*41*/  { {5.0, -2.0, -4.0}, NNZZ, ColorWhite},
/*42*/  { {6.0, -2.0, -4.0}, NNZZ, ColorWhite},
/*43*/  { {7.0, -2.0, -4.0}, NNZZ, ColorWhite},
/*44*/  { {8.0, -2.0, -4.0}, NNZZ, ColorWhite},

/*45*/  { {0.0, -2.0, -5.0}, NNZZ, ColorWhite},
/*46*/  { {1.0, -2.0, -5.0}, NNZZ, ColorWhite},
/*47*/  { {2.0, -2.0, -5.0}, NNZZ, ColorWhite},
/*48*/  { {3.0, -2.0, -5.0}, NNZZ, ColorWhite},
/*49*/  { {4.0, -2.0, -5.0}, NNZZ, ColorWhite},
/*50*/  { {5.0, -2.0, -5.0}, NNZZ, ColorWhite},
/*51*/  { {6.0, -2.0, -5.0}, NNZZ, ColorWhite},
/*52*/  { {7.0, -2.0, -5.0}, NNZZ, ColorWhite},
/*53*/  { {8.0, -2.0, -5.0}, NNZZ, ColorWhite},

/*54*/  { {0.0, -2.0, -6.0}, NNZZ, ColorWhite},
/*55*/  { {1.0, -2.0, -6.0}, NNZZ, ColorWhite},
/*56*/  { {2.0, -2.0, -6.0}, NNZZ, ColorWhite},
/*57*/  { {3.0, -2.0, -6.0}, NNZZ, ColorWhite},
/*58*/  { {4.0, -2.0, -6.0}, NNZZ, ColorWhite},
/*59*/  { {5.0, -2.0, -6.0}, NNZZ, ColorWhite},
/*60*/  { {6.0, -2.0, -6.0}, NNZZ, ColorWhite},
/*61*/  { {7.0, -2.0, -6.0}, NNZZ, ColorWhite},
/*62*/  { {8.0, -2.0, -6.0}, NNZZ, ColorWhite},

/*63*/  { {0.0, -2.0, -7.0}, NNZZ, ColorWhite},
/*64*/  { {1.0, -2.0, -7.0}, NNZZ, ColorWhite},
/*65*/  { {2.0, -2.0, -7.0}, NNZZ, ColorWhite},
/*66*/  { {3.0, -2.0, -7.0}, NNZZ, ColorWhite},
/*67*/  { {4.0, -2.0, -7.0}, NNZZ, ColorWhite},
/*68*/  { {5.0, -2.0, -7.0}, NNZZ, ColorWhite},
/*69*/  { {6.0, -2.0, -7.0}, NNZZ, ColorWhite},
/*70*/  { {7.0, -2.0, -7.0}, NNZZ, ColorWhite},
/*71*/  { {8.0, -2.0, -7.0}, NNZZ, ColorWhite},

/*72*/  { {0.0, -2.0, -8.0}, NNZZ, ColorWhite},
/*73*/  { {1.0, -2.0, -8.0}, NNZZ, ColorWhite},
/*74*/  { {2.0, -2.0, -8.0}, NNZZ, ColorWhite},
/*75*/  { {3.0, -2.0, -8.0}, NNZZ, ColorWhite},
/*76*/  { {4.0, -2.0, -8.0}, NNZZ, ColorWhite},
/*77*/  { {5.0, -2.0, -8.0}, NNZZ, ColorWhite},
/*78*/  { {6.0, -2.0, -8.0}, NNZZ, ColorWhite},
/*79*/  { {7.0, -2.0, -8.0}, NNZZ, ColorWhite},
/*80*/  { {8.0, -2.0, -8.0}, NNZZ, ColorWhite},

/*81*/  { {0.0, -2.0, -9.0}, NNZZ, ColorWhite},
/*82*/  { {1.0, -2.0, -9.0}, NNZZ, ColorWhite},
/*83*/  { {2.0, -2.0, -9.0}, NNZZ, ColorWhite},
/*84*/  { {3.0, -2.0, -9.0}, NNZZ, ColorWhite},
/*85*/  { {4.0, -2.0, -9.0}, NNZZ, ColorWhite},
/*86*/  { {5.0, -2.0, -9.0}, NNZZ, ColorWhite},
/*87*/  { {6.0, -2.0, -9.0}, NNZZ, ColorWhite},
/*88*/  { {7.0, -2.0, -9.0}, NNZZ, ColorWhite},
/*89*/  { {8.0, -2.0, -9.0}, NNZZ, ColorWhite},

/*90*/  { {0.0, -2.0, -10.0}, NNZZ, ColorWhite},
/*91*/  { {1.0, -2.0, -10.0}, NNZZ, ColorWhite},
/*92*/  { {2.0, -2.0, -10.0}, NNZZ, ColorWhite},
/*93*/  { {3.0, -2.0, -10.0}, NNZZ, ColorWhite},
/*94*/  { {4.0, -2.0, -10.0}, NNZZ, ColorWhite},
/*95*/  { {5.0, -2.0, -10.0}, NNZZ, ColorWhite},
/*96*/  { {6.0, -2.0, -10.0}, NNZZ, ColorWhite},
/*97*/  { {7.0, -2.0, -10.0}, NNZZ, ColorWhite},
/*98*/  { {8.0, -2.0, -10.0}, NNZZ, ColorWhite},

/*99*/  { {0.0, -2.0, -11.0}, NNZZ, ColorWhite},
/*100*/ { {1.0, -2.0, -11.0}, NNZZ, ColorWhite},
/*101*/ { {2.0, -2.0, -11.0}, NNZZ, ColorWhite},
/*102*/ { {3.0, -2.0, -11.0}, NNZZ, ColorWhite},
/*103*/ { {4.0, -2.0, -11.0}, NNZZ, ColorWhite},
/*104*/ { {5.0, -2.0, -11.0}, NNZZ, ColorWhite},
/*105*/ { {6.0, -2.0, -11.0}, NNZZ, ColorWhite},
/*106*/ { {7.0, -2.0, -11.0}, NNZZ, ColorWhite},
/*107*/ { {8.0, -2.0, -11.0}, NNZZ, ColorWhite},

/*108*/ { {0.0, -2.0, -12.0}, NNZZ, ColorWhite},
/*109*/ { {1.0, -2.0, -12.0}, NNZZ, ColorWhite},
/*110*/ { {2.0, -2.0, -12.0}, NNZZ, ColorWhite},
/*111*/ { {3.0, -2.0, -12.0}, NNZZ, ColorWhite},
/*112*/ { {4.0, -2.0, -12.0}, NNZZ, ColorWhite},
/*113*/ { {5.0, -2.0, -12.0}, NNZZ, ColorWhite},
/*114*/ { {6.0, -2.0, -12.0}, NNZZ, ColorWhite},
/*115*/ { {7.0, -2.0, -12.0}, NNZZ, ColorWhite},
/*116*/ { {8.0, -2.0, -12.0}, NNZZ, ColorWhite},
// any character white left back finish

// [0, 116] is 117

// 1014

// any character white quad middle left start
/*0*/   { {0.0, -1.0, -0.5}, NNZZ, ColorWhite},
/*1*/   { {1.0, -1.0, -0.5}, NNZZ, ColorWhite},
/*2*/   { {2.0, -1.0, -0.5}, NNZZ, ColorWhite},
/*3*/   { {3.0, -1.0, -0.5}, NNZZ, ColorWhite},
/*4*/   { {4.0, -1.0, -0.5}, NNZZ, ColorWhite},
/*5*/   { {5.0, -1.0, -0.5}, NNZZ, ColorWhite},
/*6*/   { {6.0, -1.0, -0.5}, NNZZ, ColorWhite},
/*7*/   { {7.0, -1.0, -0.5}, NNZZ, ColorWhite},

/*8*/   { {0.0, -1.0, -1.5}, NNZZ, ColorWhite},
/*9*/   { {1.0, -1.0, -1.5}, NNZZ, ColorWhite},
/*10*/  { {2.0, -1.0, -1.5}, NNZZ, ColorWhite},
/*11*/  { {3.0, -1.0, -1.5}, NNZZ, ColorWhite},
/*12*/  { {4.0, -1.0, -1.5}, NNZZ, ColorWhite},
/*13*/  { {5.0, -1.0, -1.5}, NNZZ, ColorWhite},
/*14*/  { {6.0, -1.0, -1.5}, NNZZ, ColorWhite},
/*15*/  { {7.0, -1.0, -1.5}, NNZZ, ColorWhite},

/*16*/  { {0.0, -1.0, -2.5}, NNZZ, ColorWhite},
/*17*/  { {1.0, -1.0, -2.5}, NNZZ, ColorWhite},
/*18*/  { {2.0, -1.0, -2.5}, NNZZ, ColorWhite},
/*19*/  { {3.0, -1.0, -2.5}, NNZZ, ColorWhite},
/*20*/  { {4.0, -1.0, -2.5}, NNZZ, ColorWhite},
/*21*/  { {5.0, -1.0, -2.5}, NNZZ, ColorWhite},
/*22*/  { {6.0, -1.0, -2.5}, NNZZ, ColorWhite},
/*23*/  { {7.0, -1.0, -2.5}, NNZZ, ColorWhite},

/*24*/  { {0.0, -1.0, -3.5}, NNZZ, ColorWhite},
/*25*/  { {1.0, -1.0, -3.5}, NNZZ, ColorWhite},
/*26*/  { {2.0, -1.0, -3.5}, NNZZ, ColorWhite},
/*27*/  { {3.0, -1.0, -3.5}, NNZZ, ColorWhite},
/*28*/  { {4.0, -1.0, -3.5}, NNZZ, ColorWhite},
/*29*/  { {5.0, -1.0, -3.5}, NNZZ, ColorWhite},
/*30*/  { {6.0, -1.0, -3.5}, NNZZ, ColorWhite},
/*31*/  { {7.0, -1.0, -3.5}, NNZZ, ColorWhite},

/*32*/  { {0.0, -1.0, -4.5}, NNZZ, ColorWhite},
/*33*/  { {1.0, -1.0, -4.5}, NNZZ, ColorWhite},
/*34*/  { {2.0, -1.0, -4.5}, NNZZ, ColorWhite},
/*35*/  { {3.0, -1.0, -4.5}, NNZZ, ColorWhite},
/*36*/  { {4.0, -1.0, -4.5}, NNZZ, ColorWhite},
/*37*/  { {5.0, -1.0, -4.5}, NNZZ, ColorWhite},
/*38*/  { {6.0, -1.0, -4.5}, NNZZ, ColorWhite},
/*39*/  { {7.0, -1.0, -4.5}, NNZZ, ColorWhite},

/*40*/  { {0.0, -1.0, -5.5}, NNZZ, ColorWhite},
/*41*/  { {1.0, -1.0, -5.5}, NNZZ, ColorWhite},
/*42*/  { {2.0, -1.0, -5.5}, NNZZ, ColorWhite},
/*43*/  { {3.0, -1.0, -5.5}, NNZZ, ColorWhite},
/*44*/  { {4.0, -1.0, -5.5}, NNZZ, ColorWhite},
/*45*/  { {5.0, -1.0, -5.5}, NNZZ, ColorWhite},
/*46*/  { {6.0, -1.0, -5.5}, NNZZ, ColorWhite},
/*47*/  { {7.0, -1.0, -5.5}, NNZZ, ColorWhite},

/*48*/  { {0.0, -1.0, -6.5}, NNZZ, ColorWhite},
/*49*/  { {1.0, -1.0, -6.5}, NNZZ, ColorWhite},
/*50*/  { {2.0, -1.0, -6.5}, NNZZ, ColorWhite},
/*51*/  { {3.0, -1.0, -6.5}, NNZZ, ColorWhite},
/*52*/  { {4.0, -1.0, -6.5}, NNZZ, ColorWhite},
/*53*/  { {5.0, -1.0, -6.5}, NNZZ, ColorWhite},
/*54*/  { {6.0, -1.0, -6.5}, NNZZ, ColorWhite},
/*55*/  { {7.0, -1.0, -6.5}, NNZZ, ColorWhite},

/*56*/  { {0.0, -1.0, -7.5}, NNZZ, ColorWhite},
/*57*/  { {1.0, -1.0, -7.5}, NNZZ, ColorWhite},
/*58*/  { {2.0, -1.0, -7.5}, NNZZ, ColorWhite},
/*59*/  { {3.0, -1.0, -7.5}, NNZZ, ColorWhite},
/*60*/  { {4.0, -1.0, -7.5}, NNZZ, ColorWhite},
/*61*/  { {5.0, -1.0, -7.5}, NNZZ, ColorWhite},
/*62*/  { {6.0, -1.0, -7.5}, NNZZ, ColorWhite},
/*63*/  { {7.0, -1.0, -7.5}, NNZZ, ColorWhite},

/*64*/  { {0.0, -1.0, -8.5}, NNZZ, ColorWhite},
/*65*/  { {1.0, -1.0, -8.5}, NNZZ, ColorWhite},
/*66*/  { {2.0, -1.0, -8.5}, NNZZ, ColorWhite},
/*67*/  { {3.0, -1.0, -8.5}, NNZZ, ColorWhite},
/*68*/  { {4.0, -1.0, -8.5}, NNZZ, ColorWhite},
/*69*/  { {5.0, -1.0, -8.5}, NNZZ, ColorWhite},
/*70*/  { {6.0, -1.0, -8.5}, NNZZ, ColorWhite},
/*71*/  { {7.0, -1.0, -8.5}, NNZZ, ColorWhite},

/*72*/  { {0.0, -1.0, -9.5}, NNZZ, ColorWhite},
/*73*/  { {1.0, -1.0, -9.5}, NNZZ, ColorWhite},
/*74*/  { {2.0, -1.0, -9.5}, NNZZ, ColorWhite},
/*75*/  { {3.0, -1.0, -9.5}, NNZZ, ColorWhite},
/*76*/  { {4.0, -1.0, -9.5}, NNZZ, ColorWhite},
/*77*/  { {5.0, -1.0, -9.5}, NNZZ, ColorWhite},
/*78*/  { {6.0, -1.0, -9.5}, NNZZ, ColorWhite},
/*79*/  { {7.0, -1.0, -9.5}, NNZZ, ColorWhite},

/*80*/  { {0.0, -1.0, -10.5}, NNZZ, ColorWhite},
/*81*/  { {1.0, -1.0, -10.5}, NNZZ, ColorWhite},
/*82*/  { {2.0, -1.0, -10.5}, NNZZ, ColorWhite},
/*83*/  { {3.0, -1.0, -10.5}, NNZZ, ColorWhite},
/*84*/  { {4.0, -1.0, -10.5}, NNZZ, ColorWhite},
/*85*/  { {5.0, -1.0, -10.5}, NNZZ, ColorWhite},
/*86*/  { {6.0, -1.0, -10.5}, NNZZ, ColorWhite},
/*87*/  { {7.0, -1.0, -10.5}, NNZZ, ColorWhite},

/*88*/  { {0.0, -1.0, -11.5}, NNZZ, ColorWhite},
/*89*/  { {1.0, -1.0, -11.5}, NNZZ, ColorWhite},
/*90*/  { {2.0, -1.0, -11.5}, NNZZ, ColorWhite},
/*91*/  { {3.0, -1.0, -11.5}, NNZZ, ColorWhite},
/*92*/  { {4.0, -1.0, -11.5}, NNZZ, ColorWhite},
/*93*/  { {5.0, -1.0, -11.5}, NNZZ, ColorWhite},
/*94*/  { {6.0, -1.0, -11.5}, NNZZ, ColorWhite},
/*95*/  { {7.0, -1.0, -11.5}, NNZZ, ColorWhite},
// any character white quad middle left finish

// [0, 95] is 96

// 1110

// any character white right front start
/*0*/   { {0.0, 0.0, 0.0}, NPZZ, ColorWhite},
/*1*/   { {1.0, 0.0, 0.0}, NPZZ, ColorWhite},
/*2*/   { {2.0, 0.0, 0.0}, NPZZ, ColorWhite},
/*3*/   { {3.0, 0.0, 0.0}, NPZZ, ColorWhite},
/*4*/   { {4.0, 0.0, 0.0}, NPZZ, ColorWhite},
/*5*/   { {5.0, 0.0, 0.0}, NPZZ, ColorWhite},
/*6*/   { {6.0, 0.0, 0.0}, NPZZ, ColorWhite},
/*7*/   { {7.0, 0.0, 0.0}, NPZZ, ColorWhite},
/*8*/   { {8.0, 0.0, 0.0}, NPZZ, ColorWhite},

/*9*/   { {0.0, 0.0, -1.0}, NPZZ, ColorWhite},
/*10*/  { {1.0, 0.0, -1.0}, NPZZ, ColorWhite},
/*11*/  { {2.0, 0.0, -1.0}, NPZZ, ColorWhite},
/*12*/  { {3.0, 0.0, -1.0}, NPZZ, ColorWhite},
/*13*/  { {4.0, 0.0, -1.0}, NPZZ, ColorWhite},
/*14*/  { {5.0, 0.0, -1.0}, NPZZ, ColorWhite},
/*15*/  { {6.0, 0.0, -1.0}, NPZZ, ColorWhite},
/*16*/  { {7.0, 0.0, -1.0}, NPZZ, ColorWhite},
/*17*/  { {8.0, 0.0, -1.0}, NPZZ, ColorWhite},

/*18*/  { {0.0, 0.0, -2.0}, NPZZ, ColorWhite},
/*19*/  { {1.0, 0.0, -2.0}, NPZZ, ColorWhite},
/*20*/  { {2.0, 0.0, -2.0}, NPZZ, ColorWhite},
/*21*/  { {3.0, 0.0, -2.0}, NPZZ, ColorWhite},
/*22*/  { {4.0, 0.0, -2.0}, NPZZ, ColorWhite},
/*23*/  { {5.0, 0.0, -2.0}, NPZZ, ColorWhite},
/*24*/  { {6.0, 0.0, -2.0}, NPZZ, ColorWhite},
/*25*/  { {7.0, 0.0, -2.0}, NPZZ, ColorWhite},
/*26*/  { {8.0, 0.0, -2.0}, NPZZ, ColorWhite},

/*27*/  { {0.0, 0.0, -3.0}, NPZZ, ColorWhite},
/*28*/  { {1.0, 0.0, -3.0}, NPZZ, ColorWhite},
/*29*/  { {2.0, 0.0, -3.0}, NPZZ, ColorWhite},
/*30*/  { {3.0, 0.0, -3.0}, NPZZ, ColorWhite},
/*31*/  { {4.0, 0.0, -3.0}, NPZZ, ColorWhite},
/*32*/  { {5.0, 0.0, -3.0}, NPZZ, ColorWhite},
/*33*/  { {6.0, 0.0, -3.0}, NPZZ, ColorWhite},
/*34*/  { {7.0, 0.0, -3.0}, NPZZ, ColorWhite},
/*35*/  { {8.0, 0.0, -3.0}, NPZZ, ColorWhite},

/*36*/  { {0.0, 0.0, -4.0}, NPZZ, ColorWhite},
/*37*/  { {1.0, 0.0, -4.0}, NPZZ, ColorWhite},
/*38*/  { {2.0, 0.0, -4.0}, NPZZ, ColorWhite},
/*39*/  { {3.0, 0.0, -4.0}, NPZZ, ColorWhite},
/*40*/  { {4.0, 0.0, -4.0}, NPZZ, ColorWhite},
/*41*/  { {5.0, 0.0, -4.0}, NPZZ, ColorWhite},
/*42*/  { {6.0, 0.0, -4.0}, NPZZ, ColorWhite},
/*43*/  { {7.0, 0.0, -4.0}, NPZZ, ColorWhite},
/*44*/  { {8.0, 0.0, -4.0}, NPZZ, ColorWhite},

/*45*/  { {0.0, 0.0, -5.0}, NPZZ, ColorWhite},
/*46*/  { {1.0, 0.0, -5.0}, NPZZ, ColorWhite},
/*47*/  { {2.0, 0.0, -5.0}, NPZZ, ColorWhite},
/*48*/  { {3.0, 0.0, -5.0}, NPZZ, ColorWhite},
/*49*/  { {4.0, 0.0, -5.0}, NPZZ, ColorWhite},
/*50*/  { {5.0, 0.0, -5.0}, NPZZ, ColorWhite},
/*51*/  { {6.0, 0.0, -5.0}, NPZZ, ColorWhite},
/*52*/  { {7.0, 0.0, -5.0}, NPZZ, ColorWhite},
/*53*/  { {8.0, 0.0, -5.0}, NPZZ, ColorWhite},

/*54*/  { {0.0, 0.0, -6.0}, NPZZ, ColorWhite},
/*55*/  { {1.0, 0.0, -6.0}, NPZZ, ColorWhite},
/*56*/  { {2.0, 0.0, -6.0}, NPZZ, ColorWhite},
/*57*/  { {3.0, 0.0, -6.0}, NPZZ, ColorWhite},
/*58*/  { {4.0, 0.0, -6.0}, NPZZ, ColorWhite},
/*59*/  { {5.0, 0.0, -6.0}, NPZZ, ColorWhite},
/*60*/  { {6.0, 0.0, -6.0}, NPZZ, ColorWhite},
/*61*/  { {7.0, 0.0, -6.0}, NPZZ, ColorWhite},
/*62*/  { {8.0, 0.0, -6.0}, NPZZ, ColorWhite},

/*63*/  { {0.0, 0.0, -7.0}, NPZZ, ColorWhite},
/*64*/  { {1.0, 0.0, -7.0}, NPZZ, ColorWhite},
/*65*/  { {2.0, 0.0, -7.0}, NPZZ, ColorWhite},
/*66*/  { {3.0, 0.0, -7.0}, NPZZ, ColorWhite},
/*67*/  { {4.0, 0.0, -7.0}, NPZZ, ColorWhite},
/*68*/  { {5.0, 0.0, -7.0}, NPZZ, ColorWhite},
/*69*/  { {6.0, 0.0, -7.0}, NPZZ, ColorWhite},
/*70*/  { {7.0, 0.0, -7.0}, NPZZ, ColorWhite},
/*71*/  { {8.0, 0.0, -7.0}, NPZZ, ColorWhite},

/*72*/  { {0.0, 0.0, -8.0}, NPZZ, ColorWhite},
/*73*/  { {1.0, 0.0, -8.0}, NPZZ, ColorWhite},
/*74*/  { {2.0, 0.0, -8.0}, NPZZ, ColorWhite},
/*75*/  { {3.0, 0.0, -8.0}, NPZZ, ColorWhite},
/*76*/  { {4.0, 0.0, -8.0}, NPZZ, ColorWhite},
/*77*/  { {5.0, 0.0, -8.0}, NPZZ, ColorWhite},
/*78*/  { {6.0, 0.0, -8.0}, NPZZ, ColorWhite},
/*79*/  { {7.0, 0.0, -8.0}, NPZZ, ColorWhite},
/*80*/  { {8.0, 0.0, -8.0}, NPZZ, ColorWhite},

/*81*/  { {0.0, 0.0, -9.0}, NPZZ, ColorWhite},
/*82*/  { {1.0, 0.0, -9.0}, NPZZ, ColorWhite},
/*83*/  { {2.0, 0.0, -9.0}, NPZZ, ColorWhite},
/*84*/  { {3.0, 0.0, -9.0}, NPZZ, ColorWhite},
/*85*/  { {4.0, 0.0, -9.0}, NPZZ, ColorWhite},
/*86*/  { {5.0, 0.0, -9.0}, NPZZ, ColorWhite},
/*87*/  { {6.0, 0.0, -9.0}, NPZZ, ColorWhite},
/*88*/  { {7.0, 0.0, -9.0}, NPZZ, ColorWhite},
/*89*/  { {8.0, 0.0, -9.0}, NPZZ, ColorWhite},

/*90*/  { {0.0, 0.0, -10.0}, NPZZ, ColorWhite},
/*91*/  { {1.0, 0.0, -10.0}, NPZZ, ColorWhite},
/*92*/  { {2.0, 0.0, -10.0}, NPZZ, ColorWhite},
/*93*/  { {3.0, 0.0, -10.0}, NPZZ, ColorWhite},
/*94*/  { {4.0, 0.0, -10.0}, NPZZ, ColorWhite},
/*95*/  { {5.0, 0.0, -10.0}, NPZZ, ColorWhite},
/*96*/  { {6.0, 0.0, -10.0}, NPZZ, ColorWhite},
/*97*/  { {7.0, 0.0, -10.0}, NPZZ, ColorWhite},
/*98*/  { {8.0, 0.0, -10.0}, NPZZ, ColorWhite},

/*99*/  { {0.0, 0.0, -11.0}, NPZZ, ColorWhite},
/*100*/ { {1.0, 0.0, -11.0}, NPZZ, ColorWhite},
/*101*/ { {2.0, 0.0, -11.0}, NPZZ, ColorWhite},
/*102*/ { {3.0, 0.0, -11.0}, NPZZ, ColorWhite},
/*103*/ { {4.0, 0.0, -11.0}, NPZZ, ColorWhite},
/*104*/ { {5.0, 0.0, -11.0}, NPZZ, ColorWhite},
/*105*/ { {6.0, 0.0, -11.0}, NPZZ, ColorWhite},
/*106*/ { {7.0, 0.0, -11.0}, NPZZ, ColorWhite},
/*107*/ { {8.0, 0.0, -11.0}, NPZZ, ColorWhite},

/*108*/ { {0.0, 0.0, -12.0}, NPZZ, ColorWhite},
/*109*/ { {1.0, 0.0, -12.0}, NPZZ, ColorWhite},
/*110*/ { {2.0, 0.0, -12.0}, NPZZ, ColorWhite},
/*111*/ { {3.0, 0.0, -12.0}, NPZZ, ColorWhite},
/*112*/ { {4.0, 0.0, -12.0}, NPZZ, ColorWhite},
/*113*/ { {5.0, 0.0, -12.0}, NPZZ, ColorWhite},
/*114*/ { {6.0, 0.0, -12.0}, NPZZ, ColorWhite},
/*115*/ { {7.0, 0.0, -12.0}, NPZZ, ColorWhite},
/*116*/ { {8.0, 0.0, -12.0}, NPZZ, ColorWhite},
// any character white right front finish

// [0, 116] is 117

// 1227

// any character white right back start
/*0*/   { {0.0, -2.0, 0.0}, NPZZ, ColorWhite},
/*1*/   { {1.0, -2.0, 0.0}, NPZZ, ColorWhite},
/*2*/   { {2.0, -2.0, 0.0}, NPZZ, ColorWhite},
/*3*/   { {3.0, -2.0, 0.0}, NPZZ, ColorWhite},
/*4*/   { {4.0, -2.0, 0.0}, NPZZ, ColorWhite},
/*5*/   { {5.0, -2.0, 0.0}, NPZZ, ColorWhite},
/*6*/   { {6.0, -2.0, 0.0}, NPZZ, ColorWhite},
/*7*/   { {7.0, -2.0, 0.0}, NPZZ, ColorWhite},
/*8*/   { {8.0, -2.0, 0.0}, NPZZ, ColorWhite},

/*9*/   { {0.0, -2.0, -1.0}, NPZZ, ColorWhite},
/*10*/  { {1.0, -2.0, -1.0}, NPZZ, ColorWhite},
/*11*/  { {2.0, -2.0, -1.0}, NPZZ, ColorWhite},
/*12*/  { {3.0, -2.0, -1.0}, NPZZ, ColorWhite},
/*13*/  { {4.0, -2.0, -1.0}, NPZZ, ColorWhite},
/*14*/  { {5.0, -2.0, -1.0}, NPZZ, ColorWhite},
/*15*/  { {6.0, -2.0, -1.0}, NPZZ, ColorWhite},
/*16*/  { {7.0, -2.0, -1.0}, NPZZ, ColorWhite},
/*17*/  { {8.0, -2.0, -1.0}, NPZZ, ColorWhite},

/*18*/  { {0.0, -2.0, -2.0}, NPZZ, ColorWhite},
/*19*/  { {1.0, -2.0, -2.0}, NPZZ, ColorWhite},
/*20*/  { {2.0, -2.0, -2.0}, NPZZ, ColorWhite},
/*21*/  { {3.0, -2.0, -2.0}, NPZZ, ColorWhite},
/*22*/  { {4.0, -2.0, -2.0}, NPZZ, ColorWhite},
/*23*/  { {5.0, -2.0, -2.0}, NPZZ, ColorWhite},
/*24*/  { {6.0, -2.0, -2.0}, NPZZ, ColorWhite},
/*25*/  { {7.0, -2.0, -2.0}, NPZZ, ColorWhite},
/*26*/  { {8.0, -2.0, -2.0}, NPZZ, ColorWhite},

/*27*/  { {0.0, -2.0, -3.0}, NPZZ, ColorWhite},
/*28*/  { {1.0, -2.0, -3.0}, NPZZ, ColorWhite},
/*29*/  { {2.0, -2.0, -3.0}, NPZZ, ColorWhite},
/*30*/  { {3.0, -2.0, -3.0}, NPZZ, ColorWhite},
/*31*/  { {4.0, -2.0, -3.0}, NPZZ, ColorWhite},
/*32*/  { {5.0, -2.0, -3.0}, NPZZ, ColorWhite},
/*33*/  { {6.0, -2.0, -3.0}, NPZZ, ColorWhite},
/*34*/  { {7.0, -2.0, -3.0}, NPZZ, ColorWhite},
/*35*/  { {8.0, -2.0, -3.0}, NPZZ, ColorWhite},

/*36*/  { {0.0, -2.0, -4.0}, NPZZ, ColorWhite},
/*37*/  { {1.0, -2.0, -4.0}, NPZZ, ColorWhite},
/*38*/  { {2.0, -2.0, -4.0}, NPZZ, ColorWhite},
/*39*/  { {3.0, -2.0, -4.0}, NPZZ, ColorWhite},
/*40*/  { {4.0, -2.0, -4.0}, NPZZ, ColorWhite},
/*41*/  { {5.0, -2.0, -4.0}, NPZZ, ColorWhite},
/*42*/  { {6.0, -2.0, -4.0}, NPZZ, ColorWhite},
/*43*/  { {7.0, -2.0, -4.0}, NPZZ, ColorWhite},
/*44*/  { {8.0, -2.0, -4.0}, NPZZ, ColorWhite},

/*45*/  { {0.0, -2.0, -5.0}, NPZZ, ColorWhite},
/*46*/  { {1.0, -2.0, -5.0}, NPZZ, ColorWhite},
/*47*/  { {2.0, -2.0, -5.0}, NPZZ, ColorWhite},
/*48*/  { {3.0, -2.0, -5.0}, NPZZ, ColorWhite},
/*49*/  { {4.0, -2.0, -5.0}, NPZZ, ColorWhite},
/*50*/  { {5.0, -2.0, -5.0}, NPZZ, ColorWhite},
/*51*/  { {6.0, -2.0, -5.0}, NPZZ, ColorWhite},
/*52*/  { {7.0, -2.0, -5.0}, NPZZ, ColorWhite},
/*53*/  { {8.0, -2.0, -5.0}, NPZZ, ColorWhite},

/*54*/  { {0.0, -2.0, -6.0}, NPZZ, ColorWhite},
/*55*/  { {1.0, -2.0, -6.0}, NPZZ, ColorWhite},
/*56*/  { {2.0, -2.0, -6.0}, NPZZ, ColorWhite},
/*57*/  { {3.0, -2.0, -6.0}, NPZZ, ColorWhite},
/*58*/  { {4.0, -2.0, -6.0}, NPZZ, ColorWhite},
/*59*/  { {5.0, -2.0, -6.0}, NPZZ, ColorWhite},
/*60*/  { {6.0, -2.0, -6.0}, NPZZ, ColorWhite},
/*61*/  { {7.0, -2.0, -6.0}, NPZZ, ColorWhite},
/*62*/  { {8.0, -2.0, -6.0}, NPZZ, ColorWhite},

/*63*/  { {0.0, -2.0, -7.0}, NPZZ, ColorWhite},
/*64*/  { {1.0, -2.0, -7.0}, NPZZ, ColorWhite},
/*65*/  { {2.0, -2.0, -7.0}, NPZZ, ColorWhite},
/*66*/  { {3.0, -2.0, -7.0}, NPZZ, ColorWhite},
/*67*/  { {4.0, -2.0, -7.0}, NPZZ, ColorWhite},
/*68*/  { {5.0, -2.0, -7.0}, NPZZ, ColorWhite},
/*69*/  { {6.0, -2.0, -7.0}, NPZZ, ColorWhite},
/*70*/  { {7.0, -2.0, -7.0}, NPZZ, ColorWhite},
/*71*/  { {8.0, -2.0, -7.0}, NPZZ, ColorWhite},

/*72*/  { {0.0, -2.0, -8.0}, NPZZ, ColorWhite},
/*73*/  { {1.0, -2.0, -8.0}, NPZZ, ColorWhite},
/*74*/  { {2.0, -2.0, -8.0}, NPZZ, ColorWhite},
/*75*/  { {3.0, -2.0, -8.0}, NPZZ, ColorWhite},
/*76*/  { {4.0, -2.0, -8.0}, NPZZ, ColorWhite},
/*77*/  { {5.0, -2.0, -8.0}, NPZZ, ColorWhite},
/*78*/  { {6.0, -2.0, -8.0}, NPZZ, ColorWhite},
/*79*/  { {7.0, -2.0, -8.0}, NPZZ, ColorWhite},
/*80*/  { {8.0, -2.0, -8.0}, NPZZ, ColorWhite},

/*81*/  { {0.0, -2.0, -9.0}, NPZZ, ColorWhite},
/*82*/  { {1.0, -2.0, -9.0}, NPZZ, ColorWhite},
/*83*/  { {2.0, -2.0, -9.0}, NPZZ, ColorWhite},
/*84*/  { {3.0, -2.0, -9.0}, NPZZ, ColorWhite},
/*85*/  { {4.0, -2.0, -9.0}, NPZZ, ColorWhite},
/*86*/  { {5.0, -2.0, -9.0}, NPZZ, ColorWhite},
/*87*/  { {6.0, -2.0, -9.0}, NPZZ, ColorWhite},
/*88*/  { {7.0, -2.0, -9.0}, NPZZ, ColorWhite},
/*89*/  { {8.0, -2.0, -9.0}, NPZZ, ColorWhite},

/*90*/  { {0.0, -2.0, -10.0}, NPZZ, ColorWhite},
/*91*/  { {1.0, -2.0, -10.0}, NPZZ, ColorWhite},
/*92*/  { {2.0, -2.0, -10.0}, NPZZ, ColorWhite},
/*93*/  { {3.0, -2.0, -10.0}, NPZZ, ColorWhite},
/*94*/  { {4.0, -2.0, -10.0}, NPZZ, ColorWhite},
/*95*/  { {5.0, -2.0, -10.0}, NPZZ, ColorWhite},
/*96*/  { {6.0, -2.0, -10.0}, NPZZ, ColorWhite},
/*97*/  { {7.0, -2.0, -10.0}, NPZZ, ColorWhite},
/*98*/  { {8.0, -2.0, -10.0}, NPZZ, ColorWhite},

/*99*/  { {0.0, -2.0, -11.0}, NPZZ, ColorWhite},
/*100*/ { {1.0, -2.0, -11.0}, NPZZ, ColorWhite},
/*101*/ { {2.0, -2.0, -11.0}, NPZZ, ColorWhite},
/*102*/ { {3.0, -2.0, -11.0}, NPZZ, ColorWhite},
/*103*/ { {4.0, -2.0, -11.0}, NPZZ, ColorWhite},
/*104*/ { {5.0, -2.0, -11.0}, NPZZ, ColorWhite},
/*105*/ { {6.0, -2.0, -11.0}, NPZZ, ColorWhite},
/*106*/ { {7.0, -2.0, -11.0}, NPZZ, ColorWhite},
/*107*/ { {8.0, -2.0, -11.0}, NPZZ, ColorWhite},

/*108*/ { {0.0, -2.0, -12.0}, NPZZ, ColorWhite},
/*109*/ { {1.0, -2.0, -12.0}, NPZZ, ColorWhite},
/*110*/ { {2.0, -2.0, -12.0}, NPZZ, ColorWhite},
/*111*/ { {3.0, -2.0, -12.0}, NPZZ, ColorWhite},
/*112*/ { {4.0, -2.0, -12.0}, NPZZ, ColorWhite},
/*113*/ { {5.0, -2.0, -12.0}, NPZZ, ColorWhite},
/*114*/ { {6.0, -2.0, -12.0}, NPZZ, ColorWhite},
/*115*/ { {7.0, -2.0, -12.0}, NPZZ, ColorWhite},
/*116*/ { {8.0, -2.0, -12.0}, NPZZ, ColorWhite},
// any character white right back finish

// [0, 116] is 117

// 1344

// any character white quad middle right start
/*0*/   { {1.0, -1.0, -0.5}, NPZZ, ColorWhite},
/*1*/   { {2.0, -1.0, -0.5}, NPZZ, ColorWhite},
/*2*/   { {3.0, -1.0, -0.5}, NPZZ, ColorWhite},
/*3*/   { {4.0, -1.0, -0.5}, NPZZ, ColorWhite},
/*4*/   { {5.0, -1.0, -0.5}, NPZZ, ColorWhite},
/*5*/   { {6.0, -1.0, -0.5}, NPZZ, ColorWhite},
/*6*/   { {7.0, -1.0, -0.5}, NPZZ, ColorWhite},
/*7*/   { {8.0, -1.0, -0.5}, NPZZ, ColorWhite},

/*8*/   { {1.0, -1.0, -1.5}, NPZZ, ColorWhite},
/*9*/   { {2.0, -1.0, -1.5}, NPZZ, ColorWhite},
/*10*/  { {3.0, -1.0, -1.5}, NPZZ, ColorWhite},
/*11*/  { {4.0, -1.0, -1.5}, NPZZ, ColorWhite},
/*12*/  { {5.0, -1.0, -1.5}, NPZZ, ColorWhite},
/*13*/  { {6.0, -1.0, -1.5}, NPZZ, ColorWhite},
/*14*/  { {7.0, -1.0, -1.5}, NPZZ, ColorWhite},
/*15*/  { {8.0, -1.0, -1.5}, NPZZ, ColorWhite},

/*16*/  { {1.0, -1.0, -2.5}, NPZZ, ColorWhite},
/*17*/  { {2.0, -1.0, -2.5}, NPZZ, ColorWhite},
/*18*/  { {3.0, -1.0, -2.5}, NPZZ, ColorWhite},
/*19*/  { {4.0, -1.0, -2.5}, NPZZ, ColorWhite},
/*20*/  { {5.0, -1.0, -2.5}, NPZZ, ColorWhite},
/*21*/  { {6.0, -1.0, -2.5}, NPZZ, ColorWhite},
/*22*/  { {7.0, -1.0, -2.5}, NPZZ, ColorWhite},
/*23*/  { {8.0, -1.0, -2.5}, NPZZ, ColorWhite},

/*24*/  { {1.0, -1.0, -3.5}, NPZZ, ColorWhite},
/*25*/  { {2.0, -1.0, -3.5}, NPZZ, ColorWhite},
/*26*/  { {3.0, -1.0, -3.5}, NPZZ, ColorWhite},
/*27*/  { {4.0, -1.0, -3.5}, NPZZ, ColorWhite},
/*28*/  { {5.0, -1.0, -3.5}, NPZZ, ColorWhite},
/*29*/  { {6.0, -1.0, -3.5}, NPZZ, ColorWhite},
/*30*/  { {7.0, -1.0, -3.5}, NPZZ, ColorWhite},
/*31*/  { {8.0, -1.0, -3.5}, NPZZ, ColorWhite},

/*32*/  { {1.0, -1.0, -4.5}, NPZZ, ColorWhite},
/*33*/  { {2.0, -1.0, -4.5}, NPZZ, ColorWhite},
/*34*/  { {3.0, -1.0, -4.5}, NPZZ, ColorWhite},
/*35*/  { {4.0, -1.0, -4.5}, NPZZ, ColorWhite},
/*36*/  { {5.0, -1.0, -4.5}, NPZZ, ColorWhite},
/*37*/  { {6.0, -1.0, -4.5}, NPZZ, ColorWhite},
/*38*/  { {7.0, -1.0, -4.5}, NPZZ, ColorWhite},
/*39*/  { {8.0, -1.0, -4.5}, NPZZ, ColorWhite},

/*40*/  { {1.0, -1.0, -5.5}, NPZZ, ColorWhite},
/*41*/  { {2.0, -1.0, -5.5}, NPZZ, ColorWhite},
/*42*/  { {3.0, -1.0, -5.5}, NPZZ, ColorWhite},
/*43*/  { {4.0, -1.0, -5.5}, NPZZ, ColorWhite},
/*44*/  { {5.0, -1.0, -5.5}, NPZZ, ColorWhite},
/*45*/  { {6.0, -1.0, -5.5}, NPZZ, ColorWhite},
/*46*/  { {7.0, -1.0, -5.5}, NPZZ, ColorWhite},
/*47*/  { {8.0, -1.0, -5.5}, NPZZ, ColorWhite},

/*48*/  { {1.0, -1.0, -6.5}, NPZZ, ColorWhite},
/*49*/  { {2.0, -1.0, -6.5}, NPZZ, ColorWhite},
/*50*/  { {3.0, -1.0, -6.5}, NPZZ, ColorWhite},
/*51*/  { {4.0, -1.0, -6.5}, NPZZ, ColorWhite},
/*52*/  { {5.0, -1.0, -6.5}, NPZZ, ColorWhite},
/*53*/  { {6.0, -1.0, -6.5}, NPZZ, ColorWhite},
/*54*/  { {7.0, -1.0, -6.5}, NPZZ, ColorWhite},
/*55*/  { {8.0, -1.0, -6.5}, NPZZ, ColorWhite},

/*56*/  { {1.0, -1.0, -7.5}, NPZZ, ColorWhite},
/*57*/  { {2.0, -1.0, -7.5}, NPZZ, ColorWhite},
/*58*/  { {3.0, -1.0, -7.5}, NPZZ, ColorWhite},
/*59*/  { {4.0, -1.0, -7.5}, NPZZ, ColorWhite},
/*60*/  { {5.0, -1.0, -7.5}, NPZZ, ColorWhite},
/*61*/  { {6.0, -1.0, -7.5}, NPZZ, ColorWhite},
/*62*/  { {7.0, -1.0, -7.5}, NPZZ, ColorWhite},
/*63*/  { {8.0, -1.0, -7.5}, NPZZ, ColorWhite},

/*64*/  { {1.0, -1.0, -8.5}, NPZZ, ColorWhite},
/*65*/  { {2.0, -1.0, -8.5}, NPZZ, ColorWhite},
/*66*/  { {3.0, -1.0, -8.5}, NPZZ, ColorWhite},
/*67*/  { {4.0, -1.0, -8.5}, NPZZ, ColorWhite},
/*68*/  { {5.0, -1.0, -8.5}, NPZZ, ColorWhite},
/*69*/  { {6.0, -1.0, -8.5}, NPZZ, ColorWhite},
/*70*/  { {7.0, -1.0, -8.5}, NPZZ, ColorWhite},
/*71*/  { {8.0, -1.0, -8.5}, NPZZ, ColorWhite},

/*72*/  { {1.0, -1.0, -9.5}, NPZZ, ColorWhite},
/*73*/  { {2.0, -1.0, -9.5}, NPZZ, ColorWhite},
/*74*/  { {3.0, -1.0, -9.5}, NPZZ, ColorWhite},
/*75*/  { {4.0, -1.0, -9.5}, NPZZ, ColorWhite},
/*76*/  { {5.0, -1.0, -9.5}, NPZZ, ColorWhite},
/*77*/  { {6.0, -1.0, -9.5}, NPZZ, ColorWhite},
/*78*/  { {7.0, -1.0, -9.5}, NPZZ, ColorWhite},
/*79*/  { {8.0, -1.0, -9.5}, NPZZ, ColorWhite},

/*80*/  { {1.0, -1.0, -10.5}, NPZZ, ColorWhite},
/*81*/  { {2.0, -1.0, -10.5}, NPZZ, ColorWhite},
/*82*/  { {3.0, -1.0, -10.5}, NPZZ, ColorWhite},
/*83*/  { {4.0, -1.0, -10.5}, NPZZ, ColorWhite},
/*84*/  { {5.0, -1.0, -10.5}, NPZZ, ColorWhite},
/*85*/  { {6.0, -1.0, -10.5}, NPZZ, ColorWhite},
/*86*/  { {7.0, -1.0, -10.5}, NPZZ, ColorWhite},
/*87*/  { {8.0, -1.0, -10.5}, NPZZ, ColorWhite},

/*88*/  { {1.0, -1.0, -11.5}, NPZZ, ColorWhite},
/*89*/  { {2.0, -1.0, -11.5}, NPZZ, ColorWhite},
/*90*/  { {3.0, -1.0, -11.5}, NPZZ, ColorWhite},
/*91*/  { {4.0, -1.0, -11.5}, NPZZ, ColorWhite},
/*92*/  { {5.0, -1.0, -11.5}, NPZZ, ColorWhite},
/*93*/  { {6.0, -1.0, -11.5}, NPZZ, ColorWhite},
/*94*/  { {7.0, -1.0, -11.5}, NPZZ, ColorWhite},
/*95*/  { {8.0, -1.0, -11.5}, NPZZ, ColorWhite},
// any character white quad middle right finish

// [0, 95] is 96

// 1440

// any character white top front start
/*0*/   { {0.0, 0.0, 0.0}, NZZN, ColorWhite},
/*1*/   { {1.0, 0.0, 0.0}, NZZN, ColorWhite},
/*2*/   { {2.0, 0.0, 0.0}, NZZN, ColorWhite},
/*3*/   { {3.0, 0.0, 0.0}, NZZN, ColorWhite},
/*4*/   { {4.0, 0.0, 0.0}, NZZN, ColorWhite},
/*5*/   { {5.0, 0.0, 0.0}, NZZN, ColorWhite},
/*6*/   { {6.0, 0.0, 0.0}, NZZN, ColorWhite},
/*7*/   { {7.0, 0.0, 0.0}, NZZN, ColorWhite},
/*8*/   { {8.0, 0.0, 0.0}, NZZN, ColorWhite},

/*9*/   { {0.0, 0.0, -1.0}, NZZN, ColorWhite},
/*10*/  { {1.0, 0.0, -1.0}, NZZN, ColorWhite},
/*11*/  { {2.0, 0.0, -1.0}, NZZN, ColorWhite},
/*12*/  { {3.0, 0.0, -1.0}, NZZN, ColorWhite},
/*13*/  { {4.0, 0.0, -1.0}, NZZN, ColorWhite},
/*14*/  { {5.0, 0.0, -1.0}, NZZN, ColorWhite},
/*15*/  { {6.0, 0.0, -1.0}, NZZN, ColorWhite},
/*16*/  { {7.0, 0.0, -1.0}, NZZN, ColorWhite},
/*17*/  { {8.0, 0.0, -1.0}, NZZN, ColorWhite},

/*18*/  { {0.0, 0.0, -2.0}, NZZN, ColorWhite},
/*19*/  { {1.0, 0.0, -2.0}, NZZN, ColorWhite},
/*20*/  { {2.0, 0.0, -2.0}, NZZN, ColorWhite},
/*21*/  { {3.0, 0.0, -2.0}, NZZN, ColorWhite},
/*22*/  { {4.0, 0.0, -2.0}, NZZN, ColorWhite},
/*23*/  { {5.0, 0.0, -2.0}, NZZN, ColorWhite},
/*24*/  { {6.0, 0.0, -2.0}, NZZN, ColorWhite},
/*25*/  { {7.0, 0.0, -2.0}, NZZN, ColorWhite},
/*26*/  { {8.0, 0.0, -2.0}, NZZN, ColorWhite},

/*27*/  { {0.0, 0.0, -3.0}, NZZN, ColorWhite},
/*28*/  { {1.0, 0.0, -3.0}, NZZN, ColorWhite},
/*29*/  { {2.0, 0.0, -3.0}, NZZN, ColorWhite},
/*30*/  { {3.0, 0.0, -3.0}, NZZN, ColorWhite},
/*31*/  { {4.0, 0.0, -3.0}, NZZN, ColorWhite},
/*32*/  { {5.0, 0.0, -3.0}, NZZN, ColorWhite},
/*33*/  { {6.0, 0.0, -3.0}, NZZN, ColorWhite},
/*34*/  { {7.0, 0.0, -3.0}, NZZN, ColorWhite},
/*35*/  { {8.0, 0.0, -3.0}, NZZN, ColorWhite},

/*36*/  { {0.0, 0.0, -4.0}, NZZN, ColorWhite},
/*37*/  { {1.0, 0.0, -4.0}, NZZN, ColorWhite},
/*38*/  { {2.0, 0.0, -4.0}, NZZN, ColorWhite},
/*39*/  { {3.0, 0.0, -4.0}, NZZN, ColorWhite},
/*40*/  { {4.0, 0.0, -4.0}, NZZN, ColorWhite},
/*41*/  { {5.0, 0.0, -4.0}, NZZN, ColorWhite},
/*42*/  { {6.0, 0.0, -4.0}, NZZN, ColorWhite},
/*43*/  { {7.0, 0.0, -4.0}, NZZN, ColorWhite},
/*44*/  { {8.0, 0.0, -4.0}, NZZN, ColorWhite},

/*45*/  { {0.0, 0.0, -5.0}, NZZN, ColorWhite},
/*46*/  { {1.0, 0.0, -5.0}, NZZN, ColorWhite},
/*47*/  { {2.0, 0.0, -5.0}, NZZN, ColorWhite},
/*48*/  { {3.0, 0.0, -5.0}, NZZN, ColorWhite},
/*49*/  { {4.0, 0.0, -5.0}, NZZN, ColorWhite},
/*50*/  { {5.0, 0.0, -5.0}, NZZN, ColorWhite},
/*51*/  { {6.0, 0.0, -5.0}, NZZN, ColorWhite},
/*52*/  { {7.0, 0.0, -5.0}, NZZN, ColorWhite},
/*53*/  { {8.0, 0.0, -5.0}, NZZN, ColorWhite},

/*54*/  { {0.0, 0.0, -6.0}, NZZN, ColorWhite},
/*55*/  { {1.0, 0.0, -6.0}, NZZN, ColorWhite},
/*56*/  { {2.0, 0.0, -6.0}, NZZN, ColorWhite},
/*57*/  { {3.0, 0.0, -6.0}, NZZN, ColorWhite},
/*58*/  { {4.0, 0.0, -6.0}, NZZN, ColorWhite},
/*59*/  { {5.0, 0.0, -6.0}, NZZN, ColorWhite},
/*60*/  { {6.0, 0.0, -6.0}, NZZN, ColorWhite},
/*61*/  { {7.0, 0.0, -6.0}, NZZN, ColorWhite},
/*62*/  { {8.0, 0.0, -6.0}, NZZN, ColorWhite},

/*63*/  { {0.0, 0.0, -7.0}, NZZN, ColorWhite},
/*64*/  { {1.0, 0.0, -7.0}, NZZN, ColorWhite},
/*65*/  { {2.0, 0.0, -7.0}, NZZN, ColorWhite},
/*66*/  { {3.0, 0.0, -7.0}, NZZN, ColorWhite},
/*67*/  { {4.0, 0.0, -7.0}, NZZN, ColorWhite},
/*68*/  { {5.0, 0.0, -7.0}, NZZN, ColorWhite},
/*69*/  { {6.0, 0.0, -7.0}, NZZN, ColorWhite},
/*70*/  { {7.0, 0.0, -7.0}, NZZN, ColorWhite},
/*71*/  { {8.0, 0.0, -7.0}, NZZN, ColorWhite},

/*72*/  { {0.0, 0.0, -8.0}, NZZN, ColorWhite},
/*73*/  { {1.0, 0.0, -8.0}, NZZN, ColorWhite},
/*74*/  { {2.0, 0.0, -8.0}, NZZN, ColorWhite},
/*75*/  { {3.0, 0.0, -8.0}, NZZN, ColorWhite},
/*76*/  { {4.0, 0.0, -8.0}, NZZN, ColorWhite},
/*77*/  { {5.0, 0.0, -8.0}, NZZN, ColorWhite},
/*78*/  { {6.0, 0.0, -8.0}, NZZN, ColorWhite},
/*79*/  { {7.0, 0.0, -8.0}, NZZN, ColorWhite},
/*80*/  { {8.0, 0.0, -8.0}, NZZN, ColorWhite},

/*81*/  { {0.0, 0.0, -9.0}, NZZN, ColorWhite},
/*82*/  { {1.0, 0.0, -9.0}, NZZN, ColorWhite},
/*83*/  { {2.0, 0.0, -9.0}, NZZN, ColorWhite},
/*84*/  { {3.0, 0.0, -9.0}, NZZN, ColorWhite},
/*85*/  { {4.0, 0.0, -9.0}, NZZN, ColorWhite},
/*86*/  { {5.0, 0.0, -9.0}, NZZN, ColorWhite},
/*87*/  { {6.0, 0.0, -9.0}, NZZN, ColorWhite},
/*88*/  { {7.0, 0.0, -9.0}, NZZN, ColorWhite},
/*89*/  { {8.0, 0.0, -9.0}, NZZN, ColorWhite},

/*90*/  { {0.0, 0.0, -10.0}, NZZN, ColorWhite},
/*91*/  { {1.0, 0.0, -10.0}, NZZN, ColorWhite},
/*92*/  { {2.0, 0.0, -10.0}, NZZN, ColorWhite},
/*93*/  { {3.0, 0.0, -10.0}, NZZN, ColorWhite},
/*94*/  { {4.0, 0.0, -10.0}, NZZN, ColorWhite},
/*95*/  { {5.0, 0.0, -10.0}, NZZN, ColorWhite},
/*96*/  { {6.0, 0.0, -10.0}, NZZN, ColorWhite},
/*97*/  { {7.0, 0.0, -10.0}, NZZN, ColorWhite},
/*98*/  { {8.0, 0.0, -10.0}, NZZN, ColorWhite},

/*99*/  { {0.0, 0.0, -11.0}, NZZN, ColorWhite},
/*100*/ { {1.0, 0.0, -11.0}, NZZN, ColorWhite},
/*101*/ { {2.0, 0.0, -11.0}, NZZN, ColorWhite},
/*102*/ { {3.0, 0.0, -11.0}, NZZN, ColorWhite},
/*103*/ { {4.0, 0.0, -11.0}, NZZN, ColorWhite},
/*104*/ { {5.0, 0.0, -11.0}, NZZN, ColorWhite},
/*105*/ { {6.0, 0.0, -11.0}, NZZN, ColorWhite},
/*106*/ { {7.0, 0.0, -11.0}, NZZN, ColorWhite},
/*107*/ { {8.0, 0.0, -11.0}, NZZN, ColorWhite},

/*108*/ { {0.0, 0.0, -12.0}, NZZN, ColorWhite},
/*109*/ { {1.0, 0.0, -12.0}, NZZN, ColorWhite},
/*110*/ { {2.0, 0.0, -12.0}, NZZN, ColorWhite},
/*111*/ { {3.0, 0.0, -12.0}, NZZN, ColorWhite},
/*112*/ { {4.0, 0.0, -12.0}, NZZN, ColorWhite},
/*113*/ { {5.0, 0.0, -12.0}, NZZN, ColorWhite},
/*114*/ { {6.0, 0.0, -12.0}, NZZN, ColorWhite},
/*115*/ { {7.0, 0.0, -12.0}, NZZN, ColorWhite},
/*116*/ { {8.0, 0.0, -12.0}, NZZN, ColorWhite},
// any character white top front finish

// [0, 116] is 117

// 1557

// any character white top back start
/*0*/   { {0.0, -2.0, 0.0}, NZZN, ColorWhite},
/*1*/   { {1.0, -2.0, 0.0}, NZZN, ColorWhite},
/*2*/   { {2.0, -2.0, 0.0}, NZZN, ColorWhite},
/*3*/   { {3.0, -2.0, 0.0}, NZZN, ColorWhite},
/*4*/   { {4.0, -2.0, 0.0}, NZZN, ColorWhite},
/*5*/   { {5.0, -2.0, 0.0}, NZZN, ColorWhite},
/*6*/   { {6.0, -2.0, 0.0}, NZZN, ColorWhite},
/*7*/   { {7.0, -2.0, 0.0}, NZZN, ColorWhite},
/*8*/   { {8.0, -2.0, 0.0}, NZZN, ColorWhite},

/*9*/   { {0.0, -2.0, -1.0}, NZZN, ColorWhite},
/*10*/  { {1.0, -2.0, -1.0}, NZZN, ColorWhite},
/*11*/  { {2.0, -2.0, -1.0}, NZZN, ColorWhite},
/*12*/  { {3.0, -2.0, -1.0}, NZZN, ColorWhite},
/*13*/  { {4.0, -2.0, -1.0}, NZZN, ColorWhite},
/*14*/  { {5.0, -2.0, -1.0}, NZZN, ColorWhite},
/*15*/  { {6.0, -2.0, -1.0}, NZZN, ColorWhite},
/*16*/  { {7.0, -2.0, -1.0}, NZZN, ColorWhite},
/*17*/  { {8.0, -2.0, -1.0}, NZZN, ColorWhite},

/*18*/  { {0.0, -2.0, -2.0}, NZZN, ColorWhite},
/*19*/  { {1.0, -2.0, -2.0}, NZZN, ColorWhite},
/*20*/  { {2.0, -2.0, -2.0}, NZZN, ColorWhite},
/*21*/  { {3.0, -2.0, -2.0}, NZZN, ColorWhite},
/*22*/  { {4.0, -2.0, -2.0}, NZZN, ColorWhite},
/*23*/  { {5.0, -2.0, -2.0}, NZZN, ColorWhite},
/*24*/  { {6.0, -2.0, -2.0}, NZZN, ColorWhite},
/*25*/  { {7.0, -2.0, -2.0}, NZZN, ColorWhite},
/*26*/  { {8.0, -2.0, -2.0}, NZZN, ColorWhite},

/*27*/  { {0.0, -2.0, -3.0}, NZZN, ColorWhite},
/*28*/  { {1.0, -2.0, -3.0}, NZZN, ColorWhite},
/*29*/  { {2.0, -2.0, -3.0}, NZZN, ColorWhite},
/*30*/  { {3.0, -2.0, -3.0}, NZZN, ColorWhite},
/*31*/  { {4.0, -2.0, -3.0}, NZZN, ColorWhite},
/*32*/  { {5.0, -2.0, -3.0}, NZZN, ColorWhite},
/*33*/  { {6.0, -2.0, -3.0}, NZZN, ColorWhite},
/*34*/  { {7.0, -2.0, -3.0}, NZZN, ColorWhite},
/*35*/  { {8.0, -2.0, -3.0}, NZZN, ColorWhite},

/*36*/  { {0.0, -2.0, -4.0}, NZZN, ColorWhite},
/*37*/  { {1.0, -2.0, -4.0}, NZZN, ColorWhite},
/*38*/  { {2.0, -2.0, -4.0}, NZZN, ColorWhite},
/*39*/  { {3.0, -2.0, -4.0}, NZZN, ColorWhite},
/*40*/  { {4.0, -2.0, -4.0}, NZZN, ColorWhite},
/*41*/  { {5.0, -2.0, -4.0}, NZZN, ColorWhite},
/*42*/  { {6.0, -2.0, -4.0}, NZZN, ColorWhite},
/*43*/  { {7.0, -2.0, -4.0}, NZZN, ColorWhite},
/*44*/  { {8.0, -2.0, -4.0}, NZZN, ColorWhite},

/*45*/  { {0.0, -2.0, -5.0}, NZZN, ColorWhite},
/*46*/  { {1.0, -2.0, -5.0}, NZZN, ColorWhite},
/*47*/  { {2.0, -2.0, -5.0}, NZZN, ColorWhite},
/*48*/  { {3.0, -2.0, -5.0}, NZZN, ColorWhite},
/*49*/  { {4.0, -2.0, -5.0}, NZZN, ColorWhite},
/*50*/  { {5.0, -2.0, -5.0}, NZZN, ColorWhite},
/*51*/  { {6.0, -2.0, -5.0}, NZZN, ColorWhite},
/*52*/  { {7.0, -2.0, -5.0}, NZZN, ColorWhite},
/*53*/  { {8.0, -2.0, -5.0}, NZZN, ColorWhite},

/*54*/  { {0.0, -2.0, -6.0}, NZZN, ColorWhite},
/*55*/  { {1.0, -2.0, -6.0}, NZZN, ColorWhite},
/*56*/  { {2.0, -2.0, -6.0}, NZZN, ColorWhite},
/*57*/  { {3.0, -2.0, -6.0}, NZZN, ColorWhite},
/*58*/  { {4.0, -2.0, -6.0}, NZZN, ColorWhite},
/*59*/  { {5.0, -2.0, -6.0}, NZZN, ColorWhite},
/*60*/  { {6.0, -2.0, -6.0}, NZZN, ColorWhite},
/*61*/  { {7.0, -2.0, -6.0}, NZZN, ColorWhite},
/*62*/  { {8.0, -2.0, -6.0}, NZZN, ColorWhite},

/*63*/  { {0.0, -2.0, -7.0}, NZZN, ColorWhite},
/*64*/  { {1.0, -2.0, -7.0}, NZZN, ColorWhite},
/*65*/  { {2.0, -2.0, -7.0}, NZZN, ColorWhite},
/*66*/  { {3.0, -2.0, -7.0}, NZZN, ColorWhite},
/*67*/  { {4.0, -2.0, -7.0}, NZZN, ColorWhite},
/*68*/  { {5.0, -2.0, -7.0}, NZZN, ColorWhite},
/*69*/  { {6.0, -2.0, -7.0}, NZZN, ColorWhite},
/*70*/  { {7.0, -2.0, -7.0}, NZZN, ColorWhite},
/*71*/  { {8.0, -2.0, -7.0}, NZZN, ColorWhite},

/*72*/  { {0.0, -2.0, -8.0}, NZZN, ColorWhite},
/*73*/  { {1.0, -2.0, -8.0}, NZZN, ColorWhite},
/*74*/  { {2.0, -2.0, -8.0}, NZZN, ColorWhite},
/*75*/  { {3.0, -2.0, -8.0}, NZZN, ColorWhite},
/*76*/  { {4.0, -2.0, -8.0}, NZZN, ColorWhite},
/*77*/  { {5.0, -2.0, -8.0}, NZZN, ColorWhite},
/*78*/  { {6.0, -2.0, -8.0}, NZZN, ColorWhite},
/*79*/  { {7.0, -2.0, -8.0}, NZZN, ColorWhite},
/*80*/  { {8.0, -2.0, -8.0}, NZZN, ColorWhite},

/*81*/  { {0.0, -2.0, -9.0}, NZZN, ColorWhite},
/*82*/  { {1.0, -2.0, -9.0}, NZZN, ColorWhite},
/*83*/  { {2.0, -2.0, -9.0}, NZZN, ColorWhite},
/*84*/  { {3.0, -2.0, -9.0}, NZZN, ColorWhite},
/*85*/  { {4.0, -2.0, -9.0}, NZZN, ColorWhite},
/*86*/  { {5.0, -2.0, -9.0}, NZZN, ColorWhite},
/*87*/  { {6.0, -2.0, -9.0}, NZZN, ColorWhite},
/*88*/  { {7.0, -2.0, -9.0}, NZZN, ColorWhite},
/*89*/  { {8.0, -2.0, -9.0}, NZZN, ColorWhite},

/*90*/  { {0.0, -2.0, -10.0}, NZZN, ColorWhite},
/*91*/  { {1.0, -2.0, -10.0}, NZZN, ColorWhite},
/*92*/  { {2.0, -2.0, -10.0}, NZZN, ColorWhite},
/*93*/  { {3.0, -2.0, -10.0}, NZZN, ColorWhite},
/*94*/  { {4.0, -2.0, -10.0}, NZZN, ColorWhite},
/*95*/  { {5.0, -2.0, -10.0}, NZZN, ColorWhite},
/*96*/  { {6.0, -2.0, -10.0}, NZZN, ColorWhite},
/*97*/  { {7.0, -2.0, -10.0}, NZZN, ColorWhite},
/*98*/  { {8.0, -2.0, -10.0}, NZZN, ColorWhite},

/*99*/  { {0.0, -2.0, -11.0}, NZZN, ColorWhite},
/*100*/ { {1.0, -2.0, -11.0}, NZZN, ColorWhite},
/*101*/ { {2.0, -2.0, -11.0}, NZZN, ColorWhite},
/*102*/ { {3.0, -2.0, -11.0}, NZZN, ColorWhite},
/*103*/ { {4.0, -2.0, -11.0}, NZZN, ColorWhite},
/*104*/ { {5.0, -2.0, -11.0}, NZZN, ColorWhite},
/*105*/ { {6.0, -2.0, -11.0}, NZZN, ColorWhite},
/*106*/ { {7.0, -2.0, -11.0}, NZZN, ColorWhite},
/*107*/ { {8.0, -2.0, -11.0}, NZZN, ColorWhite},

/*108*/ { {0.0, -2.0, -12.0}, NZZN, ColorWhite},
/*109*/ { {1.0, -2.0, -12.0}, NZZN, ColorWhite},
/*110*/ { {2.0, -2.0, -12.0}, NZZN, ColorWhite},
/*111*/ { {3.0, -2.0, -12.0}, NZZN, ColorWhite},
/*112*/ { {4.0, -2.0, -12.0}, NZZN, ColorWhite},
/*113*/ { {5.0, -2.0, -12.0}, NZZN, ColorWhite},
/*114*/ { {6.0, -2.0, -12.0}, NZZN, ColorWhite},
/*115*/ { {7.0, -2.0, -12.0}, NZZN, ColorWhite},
/*116*/ { {8.0, -2.0, -12.0}, NZZN, ColorWhite},
// any character white top back finish

// [0, 116] is 117

// 1674

// any character white quad middle top start
/*0*/   { {0.5, -1.0, -1.0}, NZZN, ColorWhite},
/*1*/   { {1.5, -1.0, -1.0}, NZZN, ColorWhite},
/*2*/   { {2.5, -1.0, -1.0}, NZZN, ColorWhite},
/*3*/   { {3.5, -1.0, -1.0}, NZZN, ColorWhite},
/*4*/   { {4.5, -1.0, -1.0}, NZZN, ColorWhite},
/*5*/   { {5.5, -1.0, -1.0}, NZZN, ColorWhite},
/*6*/   { {6.5, -1.0, -1.0}, NZZN, ColorWhite},
/*7*/   { {7.5, -1.0, -1.0}, NZZN, ColorWhite},

/*8*/   { {0.5, -1.0, -2.0}, NZZN, ColorWhite},
/*9*/   { {1.5, -1.0, -2.0}, NZZN, ColorWhite},
/*10*/  { {2.5, -1.0, -2.0}, NZZN, ColorWhite},
/*11*/  { {3.5, -1.0, -2.0}, NZZN, ColorWhite},
/*12*/  { {4.5, -1.0, -2.0}, NZZN, ColorWhite},
/*13*/  { {5.5, -1.0, -2.0}, NZZN, ColorWhite},
/*14*/  { {6.5, -1.0, -2.0}, NZZN, ColorWhite},
/*15*/  { {7.5, -1.0, -2.0}, NZZN, ColorWhite},

/*16*/  { {0.5, -1.0, -3.0}, NZZN, ColorWhite},
/*17*/  { {1.5, -1.0, -3.0}, NZZN, ColorWhite},
/*18*/  { {2.5, -1.0, -3.0}, NZZN, ColorWhite},
/*19*/  { {3.5, -1.0, -3.0}, NZZN, ColorWhite},
/*20*/  { {4.5, -1.0, -3.0}, NZZN, ColorWhite},
/*21*/  { {5.5, -1.0, -3.0}, NZZN, ColorWhite},
/*22*/  { {6.5, -1.0, -3.0}, NZZN, ColorWhite},
/*23*/  { {7.5, -1.0, -3.0}, NZZN, ColorWhite},

/*24*/  { {0.5, -1.0, -4.0}, NZZN, ColorWhite},
/*25*/  { {1.5, -1.0, -4.0}, NZZN, ColorWhite},
/*26*/  { {2.5, -1.0, -4.0}, NZZN, ColorWhite},
/*27*/  { {3.5, -1.0, -4.0}, NZZN, ColorWhite},
/*28*/  { {4.5, -1.0, -4.0}, NZZN, ColorWhite},
/*29*/  { {5.5, -1.0, -4.0}, NZZN, ColorWhite},
/*30*/  { {6.5, -1.0, -4.0}, NZZN, ColorWhite},
/*31*/  { {7.5, -1.0, -4.0}, NZZN, ColorWhite},

/*32*/  { {0.5, -1.0, -5.0}, NZZN, ColorWhite},
/*33*/  { {1.5, -1.0, -5.0}, NZZN, ColorWhite},
/*34*/  { {2.5, -1.0, -5.0}, NZZN, ColorWhite},
/*35*/  { {3.5, -1.0, -5.0}, NZZN, ColorWhite},
/*36*/  { {4.5, -1.0, -5.0}, NZZN, ColorWhite},
/*37*/  { {5.5, -1.0, -5.0}, NZZN, ColorWhite},
/*38*/  { {6.5, -1.0, -5.0}, NZZN, ColorWhite},
/*39*/  { {7.5, -1.0, -5.0}, NZZN, ColorWhite},

/*40*/  { {0.5, -1.0, -6.0}, NZZN, ColorWhite},
/*41*/  { {1.5, -1.0, -6.0}, NZZN, ColorWhite},
/*42*/  { {2.5, -1.0, -6.0}, NZZN, ColorWhite},
/*43*/  { {3.5, -1.0, -6.0}, NZZN, ColorWhite},
/*44*/  { {4.5, -1.0, -6.0}, NZZN, ColorWhite},
/*45*/  { {5.5, -1.0, -6.0}, NZZN, ColorWhite},
/*46*/  { {6.5, -1.0, -6.0}, NZZN, ColorWhite},
/*47*/  { {7.5, -1.0, -6.0}, NZZN, ColorWhite},

/*48*/  { {0.5, -1.0, -7.0}, NZZN, ColorWhite},
/*49*/  { {1.5, -1.0, -7.0}, NZZN, ColorWhite},
/*50*/  { {2.5, -1.0, -7.0}, NZZN, ColorWhite},
/*51*/  { {3.5, -1.0, -7.0}, NZZN, ColorWhite},
/*52*/  { {4.5, -1.0, -7.0}, NZZN, ColorWhite},
/*53*/  { {5.5, -1.0, -7.0}, NZZN, ColorWhite},
/*54*/  { {6.5, -1.0, -7.0}, NZZN, ColorWhite},
/*55*/  { {7.5, -1.0, -7.0}, NZZN, ColorWhite},

/*56*/  { {0.5, -1.0, -8.0}, NZZN, ColorWhite},
/*57*/  { {1.5, -1.0, -8.0}, NZZN, ColorWhite},
/*58*/  { {2.5, -1.0, -8.0}, NZZN, ColorWhite},
/*59*/  { {3.5, -1.0, -8.0}, NZZN, ColorWhite},
/*60*/  { {4.5, -1.0, -8.0}, NZZN, ColorWhite},
/*61*/  { {5.5, -1.0, -8.0}, NZZN, ColorWhite},
/*62*/  { {6.5, -1.0, -8.0}, NZZN, ColorWhite},
/*63*/  { {7.5, -1.0, -8.0}, NZZN, ColorWhite},

/*64*/  { {0.5, -1.0, -9.0}, NZZN, ColorWhite},
/*65*/  { {1.5, -1.0, -9.0}, NZZN, ColorWhite},
/*66*/  { {2.5, -1.0, -9.0}, NZZN, ColorWhite},
/*67*/  { {3.5, -1.0, -9.0}, NZZN, ColorWhite},
/*68*/  { {4.5, -1.0, -9.0}, NZZN, ColorWhite},
/*69*/  { {5.5, -1.0, -9.0}, NZZN, ColorWhite},
/*70*/  { {6.5, -1.0, -9.0}, NZZN, ColorWhite},
/*71*/  { {7.5, -1.0, -9.0}, NZZN, ColorWhite},

/*72*/  { {0.5, -1.0, -10.0}, NZZN, ColorWhite},
/*73*/  { {1.5, -1.0, -10.0}, NZZN, ColorWhite},
/*74*/  { {2.5, -1.0, -10.0}, NZZN, ColorWhite},
/*75*/  { {3.5, -1.0, -10.0}, NZZN, ColorWhite},
/*76*/  { {4.5, -1.0, -10.0}, NZZN, ColorWhite},
/*77*/  { {5.5, -1.0, -10.0}, NZZN, ColorWhite},
/*78*/  { {6.5, -1.0, -10.0}, NZZN, ColorWhite},
/*79*/  { {7.5, -1.0, -10.0}, NZZN, ColorWhite},

/*80*/  { {0.5, -1.0, -11.0}, NZZN, ColorWhite},
/*81*/  { {1.5, -1.0, -11.0}, NZZN, ColorWhite},
/*82*/  { {2.5, -1.0, -11.0}, NZZN, ColorWhite},
/*83*/  { {3.5, -1.0, -11.0}, NZZN, ColorWhite},
/*84*/  { {4.5, -1.0, -11.0}, NZZN, ColorWhite},
/*85*/  { {5.5, -1.0, -11.0}, NZZN, ColorWhite},
/*86*/  { {6.5, -1.0, -11.0}, NZZN, ColorWhite},
/*87*/  { {7.5, -1.0, -11.0}, NZZN, ColorWhite},

/*88*/  { {0.5, -1.0, -12.0}, NZZN, ColorWhite},
/*89*/  { {1.5, -1.0, -12.0}, NZZN, ColorWhite},
/*90*/  { {2.5, -1.0, -12.0}, NZZN, ColorWhite},
/*91*/  { {3.5, -1.0, -12.0}, NZZN, ColorWhite},
/*92*/  { {4.5, -1.0, -12.0}, NZZN, ColorWhite},
/*93*/  { {5.5, -1.0, -12.0}, NZZN, ColorWhite},
/*94*/  { {6.5, -1.0, -12.0}, NZZN, ColorWhite},
/*95*/  { {7.5, -1.0, -12.0}, NZZN, ColorWhite},
// any character white quad middle top finish

// [0, 95] is 96

// 1770

// any character white bottom front start
/*0*/   { {0.0, 0.0, 0.0}, NZZP, ColorWhite},
/*1*/   { {1.0, 0.0, 0.0}, NZZP, ColorWhite},
/*2*/   { {2.0, 0.0, 0.0}, NZZP, ColorWhite},
/*3*/   { {3.0, 0.0, 0.0}, NZZP, ColorWhite},
/*4*/   { {4.0, 0.0, 0.0}, NZZP, ColorWhite},
/*5*/   { {5.0, 0.0, 0.0}, NZZP, ColorWhite},
/*6*/   { {6.0, 0.0, 0.0}, NZZP, ColorWhite},
/*7*/   { {7.0, 0.0, 0.0}, NZZP, ColorWhite},
/*8*/   { {8.0, 0.0, 0.0}, NZZP, ColorWhite},

/*9*/   { {0.0, 0.0, -1.0}, NZZP, ColorWhite},
/*10*/  { {1.0, 0.0, -1.0}, NZZP, ColorWhite},
/*11*/  { {2.0, 0.0, -1.0}, NZZP, ColorWhite},
/*12*/  { {3.0, 0.0, -1.0}, NZZP, ColorWhite},
/*13*/  { {4.0, 0.0, -1.0}, NZZP, ColorWhite},
/*14*/  { {5.0, 0.0, -1.0}, NZZP, ColorWhite},
/*15*/  { {6.0, 0.0, -1.0}, NZZP, ColorWhite},
/*16*/  { {7.0, 0.0, -1.0}, NZZP, ColorWhite},
/*17*/  { {8.0, 0.0, -1.0}, NZZP, ColorWhite},

/*18*/  { {0.0, 0.0, -2.0}, NZZP, ColorWhite},
/*19*/  { {1.0, 0.0, -2.0}, NZZP, ColorWhite},
/*20*/  { {2.0, 0.0, -2.0}, NZZP, ColorWhite},
/*21*/  { {3.0, 0.0, -2.0}, NZZP, ColorWhite},
/*22*/  { {4.0, 0.0, -2.0}, NZZP, ColorWhite},
/*23*/  { {5.0, 0.0, -2.0}, NZZP, ColorWhite},
/*24*/  { {6.0, 0.0, -2.0}, NZZP, ColorWhite},
/*25*/  { {7.0, 0.0, -2.0}, NZZP, ColorWhite},
/*26*/  { {8.0, 0.0, -2.0}, NZZP, ColorWhite},

/*27*/  { {0.0, 0.0, -3.0}, NZZP, ColorWhite},
/*28*/  { {1.0, 0.0, -3.0}, NZZP, ColorWhite},
/*29*/  { {2.0, 0.0, -3.0}, NZZP, ColorWhite},
/*30*/  { {3.0, 0.0, -3.0}, NZZP, ColorWhite},
/*31*/  { {4.0, 0.0, -3.0}, NZZP, ColorWhite},
/*32*/  { {5.0, 0.0, -3.0}, NZZP, ColorWhite},
/*33*/  { {6.0, 0.0, -3.0}, NZZP, ColorWhite},
/*34*/  { {7.0, 0.0, -3.0}, NZZP, ColorWhite},
/*35*/  { {8.0, 0.0, -3.0}, NZZP, ColorWhite},

/*36*/  { {0.0, 0.0, -4.0}, NZZP, ColorWhite},
/*37*/  { {1.0, 0.0, -4.0}, NZZP, ColorWhite},
/*38*/  { {2.0, 0.0, -4.0}, NZZP, ColorWhite},
/*39*/  { {3.0, 0.0, -4.0}, NZZP, ColorWhite},
/*40*/  { {4.0, 0.0, -4.0}, NZZP, ColorWhite},
/*41*/  { {5.0, 0.0, -4.0}, NZZP, ColorWhite},
/*42*/  { {6.0, 0.0, -4.0}, NZZP, ColorWhite},
/*43*/  { {7.0, 0.0, -4.0}, NZZP, ColorWhite},
/*44*/  { {8.0, 0.0, -4.0}, NZZP, ColorWhite},

/*45*/  { {0.0, 0.0, -5.0}, NZZP, ColorWhite},
/*46*/  { {1.0, 0.0, -5.0}, NZZP, ColorWhite},
/*47*/  { {2.0, 0.0, -5.0}, NZZP, ColorWhite},
/*48*/  { {3.0, 0.0, -5.0}, NZZP, ColorWhite},
/*49*/  { {4.0, 0.0, -5.0}, NZZP, ColorWhite},
/*50*/  { {5.0, 0.0, -5.0}, NZZP, ColorWhite},
/*51*/  { {6.0, 0.0, -5.0}, NZZP, ColorWhite},
/*52*/  { {7.0, 0.0, -5.0}, NZZP, ColorWhite},
/*53*/  { {8.0, 0.0, -5.0}, NZZP, ColorWhite},

/*54*/  { {0.0, 0.0, -6.0}, NZZP, ColorWhite},
/*55*/  { {1.0, 0.0, -6.0}, NZZP, ColorWhite},
/*56*/  { {2.0, 0.0, -6.0}, NZZP, ColorWhite},
/*57*/  { {3.0, 0.0, -6.0}, NZZP, ColorWhite},
/*58*/  { {4.0, 0.0, -6.0}, NZZP, ColorWhite},
/*59*/  { {5.0, 0.0, -6.0}, NZZP, ColorWhite},
/*60*/  { {6.0, 0.0, -6.0}, NZZP, ColorWhite},
/*61*/  { {7.0, 0.0, -6.0}, NZZP, ColorWhite},
/*62*/  { {8.0, 0.0, -6.0}, NZZP, ColorWhite},

/*63*/  { {0.0, 0.0, -7.0}, NZZP, ColorWhite},
/*64*/  { {1.0, 0.0, -7.0}, NZZP, ColorWhite},
/*65*/  { {2.0, 0.0, -7.0}, NZZP, ColorWhite},
/*66*/  { {3.0, 0.0, -7.0}, NZZP, ColorWhite},
/*67*/  { {4.0, 0.0, -7.0}, NZZP, ColorWhite},
/*68*/  { {5.0, 0.0, -7.0}, NZZP, ColorWhite},
/*69*/  { {6.0, 0.0, -7.0}, NZZP, ColorWhite},
/*70*/  { {7.0, 0.0, -7.0}, NZZP, ColorWhite},
/*71*/  { {8.0, 0.0, -7.0}, NZZP, ColorWhite},

/*72*/  { {0.0, 0.0, -8.0}, NZZP, ColorWhite},
/*73*/  { {1.0, 0.0, -8.0}, NZZP, ColorWhite},
/*74*/  { {2.0, 0.0, -8.0}, NZZP, ColorWhite},
/*75*/  { {3.0, 0.0, -8.0}, NZZP, ColorWhite},
/*76*/  { {4.0, 0.0, -8.0}, NZZP, ColorWhite},
/*77*/  { {5.0, 0.0, -8.0}, NZZP, ColorWhite},
/*78*/  { {6.0, 0.0, -8.0}, NZZP, ColorWhite},
/*79*/  { {7.0, 0.0, -8.0}, NZZP, ColorWhite},
/*80*/  { {8.0, 0.0, -8.0}, NZZP, ColorWhite},

/*81*/  { {0.0, 0.0, -9.0}, NZZP, ColorWhite},
/*82*/  { {1.0, 0.0, -9.0}, NZZP, ColorWhite},
/*83*/  { {2.0, 0.0, -9.0}, NZZP, ColorWhite},
/*84*/  { {3.0, 0.0, -9.0}, NZZP, ColorWhite},
/*85*/  { {4.0, 0.0, -9.0}, NZZP, ColorWhite},
/*86*/  { {5.0, 0.0, -9.0}, NZZP, ColorWhite},
/*87*/  { {6.0, 0.0, -9.0}, NZZP, ColorWhite},
/*88*/  { {7.0, 0.0, -9.0}, NZZP, ColorWhite},
/*89*/  { {8.0, 0.0, -9.0}, NZZP, ColorWhite},

/*90*/  { {0.0, 0.0, -10.0}, NZZP, ColorWhite},
/*91*/  { {1.0, 0.0, -10.0}, NZZP, ColorWhite},
/*92*/  { {2.0, 0.0, -10.0}, NZZP, ColorWhite},
/*93*/  { {3.0, 0.0, -10.0}, NZZP, ColorWhite},
/*94*/  { {4.0, 0.0, -10.0}, NZZP, ColorWhite},
/*95*/  { {5.0, 0.0, -10.0}, NZZP, ColorWhite},
/*96*/  { {6.0, 0.0, -10.0}, NZZP, ColorWhite},
/*97*/  { {7.0, 0.0, -10.0}, NZZP, ColorWhite},
/*98*/  { {8.0, 0.0, -10.0}, NZZP, ColorWhite},

/*99*/  { {0.0, 0.0, -11.0}, NZZP, ColorWhite},
/*100*/ { {1.0, 0.0, -11.0}, NZZP, ColorWhite},
/*101*/ { {2.0, 0.0, -11.0}, NZZP, ColorWhite},
/*102*/ { {3.0, 0.0, -11.0}, NZZP, ColorWhite},
/*103*/ { {4.0, 0.0, -11.0}, NZZP, ColorWhite},
/*104*/ { {5.0, 0.0, -11.0}, NZZP, ColorWhite},
/*105*/ { {6.0, 0.0, -11.0}, NZZP, ColorWhite},
/*106*/ { {7.0, 0.0, -11.0}, NZZP, ColorWhite},
/*107*/ { {8.0, 0.0, -11.0}, NZZP, ColorWhite},

/*108*/ { {0.0, 0.0, -12.0}, NZZP, ColorWhite},
/*109*/ { {1.0, 0.0, -12.0}, NZZP, ColorWhite},
/*110*/ { {2.0, 0.0, -12.0}, NZZP, ColorWhite},
/*111*/ { {3.0, 0.0, -12.0}, NZZP, ColorWhite},
/*112*/ { {4.0, 0.0, -12.0}, NZZP, ColorWhite},
/*113*/ { {5.0, 0.0, -12.0}, NZZP, ColorWhite},
/*114*/ { {6.0, 0.0, -12.0}, NZZP, ColorWhite},
/*115*/ { {7.0, 0.0, -12.0}, NZZP, ColorWhite},
/*116*/ { {8.0, 0.0, -12.0}, NZZP, ColorWhite},
// any character white bottom front finish

// [0, 116] is 117

// 1887

// any character white bottom back start
/*0*/   { {0.0, -2.0, 0.0}, NZZP, ColorWhite},
/*1*/   { {1.0, -2.0, 0.0}, NZZP, ColorWhite},
/*2*/   { {2.0, -2.0, 0.0}, NZZP, ColorWhite},
/*3*/   { {3.0, -2.0, 0.0}, NZZP, ColorWhite},
/*4*/   { {4.0, -2.0, 0.0}, NZZP, ColorWhite},
/*5*/   { {5.0, -2.0, 0.0}, NZZP, ColorWhite},
/*6*/   { {6.0, -2.0, 0.0}, NZZP, ColorWhite},
/*7*/   { {7.0, -2.0, 0.0}, NZZP, ColorWhite},
/*8*/   { {8.0, -2.0, 0.0}, NZZP, ColorWhite},

/*9*/   { {0.0, -2.0, -1.0}, NZZP, ColorWhite},
/*10*/  { {1.0, -2.0, -1.0}, NZZP, ColorWhite},
/*11*/  { {2.0, -2.0, -1.0}, NZZP, ColorWhite},
/*12*/  { {3.0, -2.0, -1.0}, NZZP, ColorWhite},
/*13*/  { {4.0, -2.0, -1.0}, NZZP, ColorWhite},
/*14*/  { {5.0, -2.0, -1.0}, NZZP, ColorWhite},
/*15*/  { {6.0, -2.0, -1.0}, NZZP, ColorWhite},
/*16*/  { {7.0, -2.0, -1.0}, NZZP, ColorWhite},
/*17*/  { {8.0, -2.0, -1.0}, NZZP, ColorWhite},

/*18*/  { {0.0, -2.0, -2.0}, NZZP, ColorWhite},
/*19*/  { {1.0, -2.0, -2.0}, NZZP, ColorWhite},
/*20*/  { {2.0, -2.0, -2.0}, NZZP, ColorWhite},
/*21*/  { {3.0, -2.0, -2.0}, NZZP, ColorWhite},
/*22*/  { {4.0, -2.0, -2.0}, NZZP, ColorWhite},
/*23*/  { {5.0, -2.0, -2.0}, NZZP, ColorWhite},
/*24*/  { {6.0, -2.0, -2.0}, NZZP, ColorWhite},
/*25*/  { {7.0, -2.0, -2.0}, NZZP, ColorWhite},
/*26*/  { {8.0, -2.0, -2.0}, NZZP, ColorWhite},

/*27*/  { {0.0, -2.0, -3.0}, NZZP, ColorWhite},
/*28*/  { {1.0, -2.0, -3.0}, NZZP, ColorWhite},
/*29*/  { {2.0, -2.0, -3.0}, NZZP, ColorWhite},
/*30*/  { {3.0, -2.0, -3.0}, NZZP, ColorWhite},
/*31*/  { {4.0, -2.0, -3.0}, NZZP, ColorWhite},
/*32*/  { {5.0, -2.0, -3.0}, NZZP, ColorWhite},
/*33*/  { {6.0, -2.0, -3.0}, NZZP, ColorWhite},
/*34*/  { {7.0, -2.0, -3.0}, NZZP, ColorWhite},
/*35*/  { {8.0, -2.0, -3.0}, NZZP, ColorWhite},

/*36*/  { {0.0, -2.0, -4.0}, NZZP, ColorWhite},
/*37*/  { {1.0, -2.0, -4.0}, NZZP, ColorWhite},
/*38*/  { {2.0, -2.0, -4.0}, NZZP, ColorWhite},
/*39*/  { {3.0, -2.0, -4.0}, NZZP, ColorWhite},
/*40*/  { {4.0, -2.0, -4.0}, NZZP, ColorWhite},
/*41*/  { {5.0, -2.0, -4.0}, NZZP, ColorWhite},
/*42*/  { {6.0, -2.0, -4.0}, NZZP, ColorWhite},
/*43*/  { {7.0, -2.0, -4.0}, NZZP, ColorWhite},
/*44*/  { {8.0, -2.0, -4.0}, NZZP, ColorWhite},

/*45*/  { {0.0, -2.0, -5.0}, NZZP, ColorWhite},
/*46*/  { {1.0, -2.0, -5.0}, NZZP, ColorWhite},
/*47*/  { {2.0, -2.0, -5.0}, NZZP, ColorWhite},
/*48*/  { {3.0, -2.0, -5.0}, NZZP, ColorWhite},
/*49*/  { {4.0, -2.0, -5.0}, NZZP, ColorWhite},
/*50*/  { {5.0, -2.0, -5.0}, NZZP, ColorWhite},
/*51*/  { {6.0, -2.0, -5.0}, NZZP, ColorWhite},
/*52*/  { {7.0, -2.0, -5.0}, NZZP, ColorWhite},
/*53*/  { {8.0, -2.0, -5.0}, NZZP, ColorWhite},

/*54*/  { {0.0, -2.0, -6.0}, NZZP, ColorWhite},
/*55*/  { {1.0, -2.0, -6.0}, NZZP, ColorWhite},
/*56*/  { {2.0, -2.0, -6.0}, NZZP, ColorWhite},
/*57*/  { {3.0, -2.0, -6.0}, NZZP, ColorWhite},
/*58*/  { {4.0, -2.0, -6.0}, NZZP, ColorWhite},
/*59*/  { {5.0, -2.0, -6.0}, NZZP, ColorWhite},
/*60*/  { {6.0, -2.0, -6.0}, NZZP, ColorWhite},
/*61*/  { {7.0, -2.0, -6.0}, NZZP, ColorWhite},
/*62*/  { {8.0, -2.0, -6.0}, NZZP, ColorWhite},

/*63*/  { {0.0, -2.0, -7.0}, NZZP, ColorWhite},
/*64*/  { {1.0, -2.0, -7.0}, NZZP, ColorWhite},
/*65*/  { {2.0, -2.0, -7.0}, NZZP, ColorWhite},
/*66*/  { {3.0, -2.0, -7.0}, NZZP, ColorWhite},
/*67*/  { {4.0, -2.0, -7.0}, NZZP, ColorWhite},
/*68*/  { {5.0, -2.0, -7.0}, NZZP, ColorWhite},
/*69*/  { {6.0, -2.0, -7.0}, NZZP, ColorWhite},
/*70*/  { {7.0, -2.0, -7.0}, NZZP, ColorWhite},
/*71*/  { {8.0, -2.0, -7.0}, NZZP, ColorWhite},

/*72*/  { {0.0, -2.0, -8.0}, NZZP, ColorWhite},
/*73*/  { {1.0, -2.0, -8.0}, NZZP, ColorWhite},
/*74*/  { {2.0, -2.0, -8.0}, NZZP, ColorWhite},
/*75*/  { {3.0, -2.0, -8.0}, NZZP, ColorWhite},
/*76*/  { {4.0, -2.0, -8.0}, NZZP, ColorWhite},
/*77*/  { {5.0, -2.0, -8.0}, NZZP, ColorWhite},
/*78*/  { {6.0, -2.0, -8.0}, NZZP, ColorWhite},
/*79*/  { {7.0, -2.0, -8.0}, NZZP, ColorWhite},
/*80*/  { {8.0, -2.0, -8.0}, NZZP, ColorWhite},

/*81*/  { {0.0, -2.0, -9.0}, NZZP, ColorWhite},
/*82*/  { {1.0, -2.0, -9.0}, NZZP, ColorWhite},
/*83*/  { {2.0, -2.0, -9.0}, NZZP, ColorWhite},
/*84*/  { {3.0, -2.0, -9.0}, NZZP, ColorWhite},
/*85*/  { {4.0, -2.0, -9.0}, NZZP, ColorWhite},
/*86*/  { {5.0, -2.0, -9.0}, NZZP, ColorWhite},
/*87*/  { {6.0, -2.0, -9.0}, NZZP, ColorWhite},
/*88*/  { {7.0, -2.0, -9.0}, NZZP, ColorWhite},
/*89*/  { {8.0, -2.0, -9.0}, NZZP, ColorWhite},

/*90*/  { {0.0, -2.0, -10.0}, NZZP, ColorWhite},
/*91*/  { {1.0, -2.0, -10.0}, NZZP, ColorWhite},
/*92*/  { {2.0, -2.0, -10.0}, NZZP, ColorWhite},
/*93*/  { {3.0, -2.0, -10.0}, NZZP, ColorWhite},
/*94*/  { {4.0, -2.0, -10.0}, NZZP, ColorWhite},
/*95*/  { {5.0, -2.0, -10.0}, NZZP, ColorWhite},
/*96*/  { {6.0, -2.0, -10.0}, NZZP, ColorWhite},
/*97*/  { {7.0, -2.0, -10.0}, NZZP, ColorWhite},
/*98*/  { {8.0, -2.0, -10.0}, NZZP, ColorWhite},

/*99*/  { {0.0, -2.0, -11.0}, NZZP, ColorWhite},
/*100*/ { {1.0, -2.0, -11.0}, NZZP, ColorWhite},
/*101*/ { {2.0, -2.0, -11.0}, NZZP, ColorWhite},
/*102*/ { {3.0, -2.0, -11.0}, NZZP, ColorWhite},
/*103*/ { {4.0, -2.0, -11.0}, NZZP, ColorWhite},
/*104*/ { {5.0, -2.0, -11.0}, NZZP, ColorWhite},
/*105*/ { {6.0, -2.0, -11.0}, NZZP, ColorWhite},
/*106*/ { {7.0, -2.0, -11.0}, NZZP, ColorWhite},
/*107*/ { {8.0, -2.0, -11.0}, NZZP, ColorWhite},

/*108*/ { {0.0, -2.0, -12.0}, NZZP, ColorWhite},
/*109*/ { {1.0, -2.0, -12.0}, NZZP, ColorWhite},
/*110*/ { {2.0, -2.0, -12.0}, NZZP, ColorWhite},
/*111*/ { {3.0, -2.0, -12.0}, NZZP, ColorWhite},
/*112*/ { {4.0, -2.0, -12.0}, NZZP, ColorWhite},
/*113*/ { {5.0, -2.0, -12.0}, NZZP, ColorWhite},
/*114*/ { {6.0, -2.0, -12.0}, NZZP, ColorWhite},
/*115*/ { {7.0, -2.0, -12.0}, NZZP, ColorWhite},
/*116*/ { {8.0, -2.0, -12.0}, NZZP, ColorWhite},
// any character white bottom back finish

// [0, 116] is 117

// 2004

// any character white quad middle bottom start
/*0*/   { {0.5, -1.0, 0.0}, NZZP, ColorWhite},
/*1*/   { {1.5, -1.0, 0.0}, NZZP, ColorWhite},
/*2*/   { {2.5, -1.0, 0.0}, NZZP, ColorWhite},
/*3*/   { {3.5, -1.0, 0.0}, NZZP, ColorWhite},
/*4*/   { {4.5, -1.0, 0.0}, NZZP, ColorWhite},
/*5*/   { {5.5, -1.0, 0.0}, NZZP, ColorWhite},
/*6*/   { {6.5, -1.0, 0.0}, NZZP, ColorWhite},
/*7*/   { {7.5, -1.0, 0.0}, NZZP, ColorWhite},

/*8*/   { {0.5, -1.0, -1.0}, NZZP, ColorWhite},
/*9*/   { {1.5, -1.0, -1.0}, NZZP, ColorWhite},
/*10*/  { {2.5, -1.0, -1.0}, NZZP, ColorWhite},
/*11*/  { {3.5, -1.0, -1.0}, NZZP, ColorWhite},
/*12*/  { {4.5, -1.0, -1.0}, NZZP, ColorWhite},
/*13*/  { {5.5, -1.0, -1.0}, NZZP, ColorWhite},
/*14*/  { {6.5, -1.0, -1.0}, NZZP, ColorWhite},
/*15*/  { {7.5, -1.0, -1.0}, NZZP, ColorWhite},

/*16*/  { {0.5, -1.0, -2.0}, NZZP, ColorWhite},
/*17*/  { {1.5, -1.0, -2.0}, NZZP, ColorWhite},
/*18*/  { {2.5, -1.0, -2.0}, NZZP, ColorWhite},
/*19*/  { {3.5, -1.0, -2.0}, NZZP, ColorWhite},
/*20*/  { {4.5, -1.0, -2.0}, NZZP, ColorWhite},
/*21*/  { {5.5, -1.0, -2.0}, NZZP, ColorWhite},
/*22*/  { {6.5, -1.0, -2.0}, NZZP, ColorWhite},
/*23*/  { {7.5, -1.0, -2.0}, NZZP, ColorWhite},

/*24*/  { {0.5, -1.0, -3.0}, NZZP, ColorWhite},
/*25*/  { {1.5, -1.0, -3.0}, NZZP, ColorWhite},
/*26*/  { {2.5, -1.0, -3.0}, NZZP, ColorWhite},
/*27*/  { {3.5, -1.0, -3.0}, NZZP, ColorWhite},
/*28*/  { {4.5, -1.0, -3.0}, NZZP, ColorWhite},
/*29*/  { {5.5, -1.0, -3.0}, NZZP, ColorWhite},
/*30*/  { {6.5, -1.0, -3.0}, NZZP, ColorWhite},
/*31*/  { {7.5, -1.0, -3.0}, NZZP, ColorWhite},

/*32*/  { {0.5, -1.0, -4.0}, NZZP, ColorWhite},
/*33*/  { {1.5, -1.0, -4.0}, NZZP, ColorWhite},
/*34*/  { {2.5, -1.0, -4.0}, NZZP, ColorWhite},
/*35*/  { {3.5, -1.0, -4.0}, NZZP, ColorWhite},
/*36*/  { {4.5, -1.0, -4.0}, NZZP, ColorWhite},
/*37*/  { {5.5, -1.0, -4.0}, NZZP, ColorWhite},
/*38*/  { {6.5, -1.0, -4.0}, NZZP, ColorWhite},
/*39*/  { {7.5, -1.0, -4.0}, NZZP, ColorWhite},

/*40*/  { {0.5, -1.0, -5.0}, NZZP, ColorWhite},
/*41*/  { {1.5, -1.0, -5.0}, NZZP, ColorWhite},
/*42*/  { {2.5, -1.0, -5.0}, NZZP, ColorWhite},
/*43*/  { {3.5, -1.0, -5.0}, NZZP, ColorWhite},
/*44*/  { {4.5, -1.0, -5.0}, NZZP, ColorWhite},
/*45*/  { {5.5, -1.0, -5.0}, NZZP, ColorWhite},
/*46*/  { {6.5, -1.0, -5.0}, NZZP, ColorWhite},
/*47*/  { {7.5, -1.0, -5.0}, NZZP, ColorWhite},

/*48*/  { {0.5, -1.0, -6.0}, NZZP, ColorWhite},
/*49*/  { {1.5, -1.0, -6.0}, NZZP, ColorWhite},
/*50*/  { {2.5, -1.0, -6.0}, NZZP, ColorWhite},
/*51*/  { {3.5, -1.0, -6.0}, NZZP, ColorWhite},
/*52*/  { {4.5, -1.0, -6.0}, NZZP, ColorWhite},
/*53*/  { {5.5, -1.0, -6.0}, NZZP, ColorWhite},
/*54*/  { {6.5, -1.0, -6.0}, NZZP, ColorWhite},
/*55*/  { {7.5, -1.0, -6.0}, NZZP, ColorWhite},

/*56*/  { {0.5, -1.0, -7.0}, NZZP, ColorWhite},
/*57*/  { {1.5, -1.0, -7.0}, NZZP, ColorWhite},
/*58*/  { {2.5, -1.0, -7.0}, NZZP, ColorWhite},
/*59*/  { {3.5, -1.0, -7.0}, NZZP, ColorWhite},
/*60*/  { {4.5, -1.0, -7.0}, NZZP, ColorWhite},
/*61*/  { {5.5, -1.0, -7.0}, NZZP, ColorWhite},
/*62*/  { {6.5, -1.0, -7.0}, NZZP, ColorWhite},
/*63*/  { {7.5, -1.0, -7.0}, NZZP, ColorWhite},

/*64*/  { {0.5, -1.0, -8.0}, NZZP, ColorWhite},
/*65*/  { {1.5, -1.0, -8.0}, NZZP, ColorWhite},
/*66*/  { {2.5, -1.0, -8.0}, NZZP, ColorWhite},
/*67*/  { {3.5, -1.0, -8.0}, NZZP, ColorWhite},
/*68*/  { {4.5, -1.0, -8.0}, NZZP, ColorWhite},
/*69*/  { {5.5, -1.0, -8.0}, NZZP, ColorWhite},
/*70*/  { {6.5, -1.0, -8.0}, NZZP, ColorWhite},
/*71*/  { {7.5, -1.0, -8.0}, NZZP, ColorWhite},

/*72*/  { {0.5, -1.0, -9.0}, NZZP, ColorWhite},
/*73*/  { {1.5, -1.0, -9.0}, NZZP, ColorWhite},
/*74*/  { {2.5, -1.0, -9.0}, NZZP, ColorWhite},
/*75*/  { {3.5, -1.0, -9.0}, NZZP, ColorWhite},
/*76*/  { {4.5, -1.0, -9.0}, NZZP, ColorWhite},
/*77*/  { {5.5, -1.0, -9.0}, NZZP, ColorWhite},
/*78*/  { {6.5, -1.0, -9.0}, NZZP, ColorWhite},
/*79*/  { {7.5, -1.0, -9.0}, NZZP, ColorWhite},

/*80*/  { {0.5, -1.0, -10.0}, NZZP, ColorWhite},
/*81*/  { {1.5, -1.0, -10.0}, NZZP, ColorWhite},
/*82*/  { {2.5, -1.0, -10.0}, NZZP, ColorWhite},
/*83*/  { {3.5, -1.0, -10.0}, NZZP, ColorWhite},
/*84*/  { {4.5, -1.0, -10.0}, NZZP, ColorWhite},
/*85*/  { {5.5, -1.0, -10.0}, NZZP, ColorWhite},
/*86*/  { {6.5, -1.0, -10.0}, NZZP, ColorWhite},
/*87*/  { {7.5, -1.0, -10.0}, NZZP, ColorWhite},

/*88*/  { {0.5, -1.0, -11.0}, NZZP, ColorWhite},
/*89*/  { {1.5, -1.0, -11.0}, NZZP, ColorWhite},
/*90*/  { {2.5, -1.0, -11.0}, NZZP, ColorWhite},
/*91*/  { {3.5, -1.0, -11.0}, NZZP, ColorWhite},
/*92*/  { {4.5, -1.0, -11.0}, NZZP, ColorWhite},
/*93*/  { {5.5, -1.0, -11.0}, NZZP, ColorWhite},
/*94*/  { {6.5, -1.0, -11.0}, NZZP, ColorWhite},
/*95*/  { {7.5, -1.0, -11.0}, NZZP, ColorWhite},
// any character white quad middle bottom finish

// [0, 95] is 96

// 2100

#if 0
// any character not white front start
/*0*/   { {0.0, 0.0, 0.0}, NZPZ, ColorGrey},
/*1*/   { {1.0, 0.0, 0.0}, NZPZ, ColorGrey},
/*2*/   { {2.0, 0.0, 0.0}, NZPZ, ColorGrey},
/*3*/   { {3.0, 0.0, 0.0}, NZPZ, ColorGrey},
/*4*/   { {4.0, 0.0, 0.0}, NZPZ, ColorGrey},
/*5*/   { {5.0, 0.0, 0.0}, NZPZ, ColorGrey},
/*6*/   { {6.0, 0.0, 0.0}, NZPZ, ColorGrey},
/*7*/   { {7.0, 0.0, 0.0}, NZPZ, ColorGrey},
/*8*/   { {8.0, 0.0, 0.0}, NZPZ, ColorGrey},

/*9*/   { {0.0, 0.0, -1.0}, NZPZ, ColorGrey},
/*10*/  { {1.0, 0.0, -1.0}, NZPZ, ColorGrey},
/*11*/  { {2.0, 0.0, -1.0}, NZPZ, ColorGrey},
/*12*/  { {3.0, 0.0, -1.0}, NZPZ, ColorGrey},
/*13*/  { {4.0, 0.0, -1.0}, NZPZ, ColorGrey},
/*14*/  { {5.0, 0.0, -1.0}, NZPZ, ColorGrey},
/*15*/  { {6.0, 0.0, -1.0}, NZPZ, ColorGrey},
/*16*/  { {7.0, 0.0, -1.0}, NZPZ, ColorGrey},
/*17*/  { {8.0, 0.0, -1.0}, NZPZ, ColorGrey},

/*18*/  { {0.0, 0.0, -2.0}, NZPZ, ColorGrey},
/*19*/  { {1.0, 0.0, -2.0}, NZPZ, ColorGrey},
/*20*/  { {2.0, 0.0, -2.0}, NZPZ, ColorGrey},
/*21*/  { {3.0, 0.0, -2.0}, NZPZ, ColorGrey},
/*22*/  { {4.0, 0.0, -2.0}, NZPZ, ColorGrey},
/*23*/  { {5.0, 0.0, -2.0}, NZPZ, ColorGrey},
/*24*/  { {6.0, 0.0, -2.0}, NZPZ, ColorGrey},
/*25*/  { {7.0, 0.0, -2.0}, NZPZ, ColorGrey},
/*26*/  { {8.0, 0.0, -2.0}, NZPZ, ColorGrey},

/*27*/  { {0.0, 0.0, -3.0}, NZPZ, ColorGrey},
/*28*/  { {1.0, 0.0, -3.0}, NZPZ, ColorGrey},
/*29*/  { {2.0, 0.0, -3.0}, NZPZ, ColorGrey},
/*30*/  { {3.0, 0.0, -3.0}, NZPZ, ColorGrey},
/*31*/  { {4.0, 0.0, -3.0}, NZPZ, ColorGrey},
/*32*/  { {5.0, 0.0, -3.0}, NZPZ, ColorGrey},
/*33*/  { {6.0, 0.0, -3.0}, NZPZ, ColorGrey},
/*34*/  { {7.0, 0.0, -3.0}, NZPZ, ColorGrey},
/*35*/  { {8.0, 0.0, -3.0}, NZPZ, ColorGrey},

/*36*/  { {0.0, 0.0, -4.0}, NZPZ, ColorGrey},
/*37*/  { {1.0, 0.0, -4.0}, NZPZ, ColorGrey},
/*38*/  { {2.0, 0.0, -4.0}, NZPZ, ColorGrey},
/*39*/  { {3.0, 0.0, -4.0}, NZPZ, ColorGrey},
/*40*/  { {4.0, 0.0, -4.0}, NZPZ, ColorGrey},
/*41*/  { {5.0, 0.0, -4.0}, NZPZ, ColorGrey},
/*42*/  { {6.0, 0.0, -4.0}, NZPZ, ColorGrey},
/*43*/  { {7.0, 0.0, -4.0}, NZPZ, ColorGrey},
/*44*/  { {8.0, 0.0, -4.0}, NZPZ, ColorGrey},

/*45*/  { {0.0, 0.0, -5.0}, NZPZ, ColorGrey},
/*46*/  { {1.0, 0.0, -5.0}, NZPZ, ColorGrey},
/*47*/  { {2.0, 0.0, -5.0}, NZPZ, ColorGrey},
/*48*/  { {3.0, 0.0, -5.0}, NZPZ, ColorGrey},
/*49*/  { {4.0, 0.0, -5.0}, NZPZ, ColorGrey},
/*50*/  { {5.0, 0.0, -5.0}, NZPZ, ColorGrey},
/*51*/  { {6.0, 0.0, -5.0}, NZPZ, ColorGrey},
/*52*/  { {7.0, 0.0, -5.0}, NZPZ, ColorGrey},
/*53*/  { {8.0, 0.0, -5.0}, NZPZ, ColorGrey},

/*54*/  { {0.0, 0.0, -6.0}, NZPZ, ColorGrey},
/*55*/  { {1.0, 0.0, -6.0}, NZPZ, ColorGrey},
/*56*/  { {2.0, 0.0, -6.0}, NZPZ, ColorGrey},
/*57*/  { {3.0, 0.0, -6.0}, NZPZ, ColorGrey},
/*58*/  { {4.0, 0.0, -6.0}, NZPZ, ColorGrey},
/*59*/  { {5.0, 0.0, -6.0}, NZPZ, ColorGrey},
/*60*/  { {6.0, 0.0, -6.0}, NZPZ, ColorGrey},
/*61*/  { {7.0, 0.0, -6.0}, NZPZ, ColorGrey},
/*62*/  { {8.0, 0.0, -6.0}, NZPZ, ColorGrey},

/*63*/  { {0.0, 0.0, -7.0}, NZPZ, ColorGrey},
/*64*/  { {1.0, 0.0, -7.0}, NZPZ, ColorGrey},
/*65*/  { {2.0, 0.0, -7.0}, NZPZ, ColorGrey},
/*66*/  { {3.0, 0.0, -7.0}, NZPZ, ColorGrey},
/*67*/  { {4.0, 0.0, -7.0}, NZPZ, ColorGrey},
/*68*/  { {5.0, 0.0, -7.0}, NZPZ, ColorGrey},
/*69*/  { {6.0, 0.0, -7.0}, NZPZ, ColorGrey},
/*70*/  { {7.0, 0.0, -7.0}, NZPZ, ColorGrey},
/*71*/  { {8.0, 0.0, -7.0}, NZPZ, ColorGrey},

/*72*/  { {0.0, 0.0, -8.0}, NZPZ, ColorGrey},
/*73*/  { {1.0, 0.0, -8.0}, NZPZ, ColorGrey},
/*74*/  { {2.0, 0.0, -8.0}, NZPZ, ColorGrey},
/*75*/  { {3.0, 0.0, -8.0}, NZPZ, ColorGrey},
/*76*/  { {4.0, 0.0, -8.0}, NZPZ, ColorGrey},
/*77*/  { {5.0, 0.0, -8.0}, NZPZ, ColorGrey},
/*78*/  { {6.0, 0.0, -8.0}, NZPZ, ColorGrey},
/*79*/  { {7.0, 0.0, -8.0}, NZPZ, ColorGrey},
/*80*/  { {8.0, 0.0, -8.0}, NZPZ, ColorGrey},

/*81*/  { {0.0, 0.0, -9.0}, NZPZ, ColorGrey},
/*82*/  { {1.0, 0.0, -9.0}, NZPZ, ColorGrey},
/*83*/  { {2.0, 0.0, -9.0}, NZPZ, ColorGrey},
/*84*/  { {3.0, 0.0, -9.0}, NZPZ, ColorGrey},
/*85*/  { {4.0, 0.0, -9.0}, NZPZ, ColorGrey},
/*86*/  { {5.0, 0.0, -9.0}, NZPZ, ColorGrey},
/*87*/  { {6.0, 0.0, -9.0}, NZPZ, ColorGrey},
/*88*/  { {7.0, 0.0, -9.0}, NZPZ, ColorGrey},
/*89*/  { {8.0, 0.0, -9.0}, NZPZ, ColorGrey},

/*90*/  { {0.0, 0.0, -10.0}, NZPZ, ColorGrey},
/*91*/  { {1.0, 0.0, -10.0}, NZPZ, ColorGrey},
/*92*/  { {2.0, 0.0, -10.0}, NZPZ, ColorGrey},
/*93*/  { {3.0, 0.0, -10.0}, NZPZ, ColorGrey},
/*94*/  { {4.0, 0.0, -10.0}, NZPZ, ColorGrey},
/*95*/  { {5.0, 0.0, -10.0}, NZPZ, ColorGrey},
/*96*/  { {6.0, 0.0, -10.0}, NZPZ, ColorGrey},
/*97*/  { {7.0, 0.0, -10.0}, NZPZ, ColorGrey},
/*98*/  { {8.0, 0.0, -10.0}, NZPZ, ColorGrey},

/*99*/  { {0.0, 0.0, -11.0}, NZPZ, ColorGrey},
/*100*/ { {1.0, 0.0, -11.0}, NZPZ, ColorGrey},
/*101*/ { {2.0, 0.0, -11.0}, NZPZ, ColorGrey},
/*102*/ { {3.0, 0.0, -11.0}, NZPZ, ColorGrey},
/*103*/ { {4.0, 0.0, -11.0}, NZPZ, ColorGrey},
/*104*/ { {5.0, 0.0, -11.0}, NZPZ, ColorGrey},
/*105*/ { {6.0, 0.0, -11.0}, NZPZ, ColorGrey},
/*106*/ { {7.0, 0.0, -11.0}, NZPZ, ColorGrey},
/*107*/ { {8.0, 0.0, -11.0}, NZPZ, ColorGrey},

/*108*/ { {0.0, 0.0, -12.0}, NZPZ, ColorGrey},
/*109*/ { {1.0, 0.0, -12.0}, NZPZ, ColorGrey},
/*110*/ { {2.0, 0.0, -12.0}, NZPZ, ColorGrey},
/*111*/ { {3.0, 0.0, -12.0}, NZPZ, ColorGrey},
/*112*/ { {4.0, 0.0, -12.0}, NZPZ, ColorGrey},
/*113*/ { {5.0, 0.0, -12.0}, NZPZ, ColorGrey},
/*114*/ { {6.0, 0.0, -12.0}, NZPZ, ColorGrey},
/*115*/ { {7.0, 0.0, -12.0}, NZPZ, ColorGrey},
/*116*/ { {8.0, 0.0, -12.0}, NZPZ, ColorGrey},
// any character not white front finish

// [0, 116] is 117

// 2217

// any character not white quad middle front start
/*0*/   { {0.5, 0.0, -0.5}, NZPZ, ColorGrey},
/*1*/   { {1.5, 0.0, -0.5}, NZPZ, ColorGrey},
/*2*/   { {2.5, 0.0, -0.5}, NZPZ, ColorGrey},
/*3*/   { {3.5, 0.0, -0.5}, NZPZ, ColorGrey},
/*4*/   { {4.5, 0.0, -0.5}, NZPZ, ColorGrey},
/*5*/   { {5.5, 0.0, -0.5}, NZPZ, ColorGrey},
/*6*/   { {6.5, 0.0, -0.5}, NZPZ, ColorGrey},
/*7*/   { {7.5, 0.0, -0.5}, NZPZ, ColorGrey},

/*8*/   { {0.5, 0.0, -1.5}, NZPZ, ColorGrey},
/*9*/   { {1.5, 0.0, -1.5}, NZPZ, ColorGrey},
/*10*/  { {2.5, 0.0, -1.5}, NZPZ, ColorGrey},
/*11*/  { {3.5, 0.0, -1.5}, NZPZ, ColorGrey},
/*12*/  { {4.5, 0.0, -1.5}, NZPZ, ColorGrey},
/*13*/  { {5.5, 0.0, -1.5}, NZPZ, ColorGrey},
/*14*/  { {6.5, 0.0, -1.5}, NZPZ, ColorGrey},
/*15*/  { {7.5, 0.0, -1.5}, NZPZ, ColorGrey},

/*16*/  { {0.5, 0.0, -2.5}, NZPZ, ColorGrey},
/*17*/  { {1.5, 0.0, -2.5}, NZPZ, ColorGrey},
/*18*/  { {2.5, 0.0, -2.5}, NZPZ, ColorGrey},
/*19*/  { {3.5, 0.0, -2.5}, NZPZ, ColorGrey},
/*20*/  { {4.5, 0.0, -2.5}, NZPZ, ColorGrey},
/*21*/  { {5.5, 0.0, -2.5}, NZPZ, ColorGrey},
/*22*/  { {6.5, 0.0, -2.5}, NZPZ, ColorGrey},
/*23*/  { {7.5, 0.0, -2.5}, NZPZ, ColorGrey},

/*24*/  { {0.5, 0.0, -3.5}, NZPZ, ColorGrey},
/*25*/  { {1.5, 0.0, -3.5}, NZPZ, ColorGrey},
/*26*/  { {2.5, 0.0, -3.5}, NZPZ, ColorGrey},
/*27*/  { {3.5, 0.0, -3.5}, NZPZ, ColorGrey},
/*28*/  { {4.5, 0.0, -3.5}, NZPZ, ColorGrey},
/*29*/  { {5.5, 0.0, -3.5}, NZPZ, ColorGrey},
/*30*/  { {6.5, 0.0, -3.5}, NZPZ, ColorGrey},
/*31*/  { {7.5, 0.0, -3.5}, NZPZ, ColorGrey},

/*32*/  { {0.5, 0.0, -4.5}, NZPZ, ColorGrey},
/*33*/  { {1.5, 0.0, -4.5}, NZPZ, ColorGrey},
/*34*/  { {2.5, 0.0, -4.5}, NZPZ, ColorGrey},
/*35*/  { {3.5, 0.0, -4.5}, NZPZ, ColorGrey},
/*36*/  { {4.5, 0.0, -4.5}, NZPZ, ColorGrey},
/*37*/  { {5.5, 0.0, -4.5}, NZPZ, ColorGrey},
/*38*/  { {6.5, 0.0, -4.5}, NZPZ, ColorGrey},
/*39*/  { {7.5, 0.0, -4.5}, NZPZ, ColorGrey},

/*40*/  { {0.5, 0.0, -5.5}, NZPZ, ColorGrey},
/*41*/  { {1.5, 0.0, -5.5}, NZPZ, ColorGrey},
/*42*/  { {2.5, 0.0, -5.5}, NZPZ, ColorGrey},
/*43*/  { {3.5, 0.0, -5.5}, NZPZ, ColorGrey},
/*44*/  { {4.5, 0.0, -5.5}, NZPZ, ColorGrey},
/*45*/  { {5.5, 0.0, -5.5}, NZPZ, ColorGrey},
/*46*/  { {6.5, 0.0, -5.5}, NZPZ, ColorGrey},
/*47*/  { {7.5, 0.0, -5.5}, NZPZ, ColorGrey},

/*48*/  { {0.5, 0.0, -6.5}, NZPZ, ColorGrey},
/*49*/  { {1.5, 0.0, -6.5}, NZPZ, ColorGrey},
/*50*/  { {2.5, 0.0, -6.5}, NZPZ, ColorGrey},
/*51*/  { {3.5, 0.0, -6.5}, NZPZ, ColorGrey},
/*52*/  { {4.5, 0.0, -6.5}, NZPZ, ColorGrey},
/*53*/  { {5.5, 0.0, -6.5}, NZPZ, ColorGrey},
/*54*/  { {6.5, 0.0, -6.5}, NZPZ, ColorGrey},
/*55*/  { {7.5, 0.0, -6.5}, NZPZ, ColorGrey},

/*56*/  { {0.5, 0.0, -7.5}, NZPZ, ColorGrey},
/*57*/  { {1.5, 0.0, -7.5}, NZPZ, ColorGrey},
/*58*/  { {2.5, 0.0, -7.5}, NZPZ, ColorGrey},
/*59*/  { {3.5, 0.0, -7.5}, NZPZ, ColorGrey},
/*60*/  { {4.5, 0.0, -7.5}, NZPZ, ColorGrey},
/*61*/  { {5.5, 0.0, -7.5}, NZPZ, ColorGrey},
/*62*/  { {6.5, 0.0, -7.5}, NZPZ, ColorGrey},
/*63*/  { {7.5, 0.0, -7.5}, NZPZ, ColorGrey},

/*64*/  { {0.5, 0.0, -8.5}, NZPZ, ColorGrey},
/*65*/  { {1.5, 0.0, -8.5}, NZPZ, ColorGrey},
/*66*/  { {2.5, 0.0, -8.5}, NZPZ, ColorGrey},
/*67*/  { {3.5, 0.0, -8.5}, NZPZ, ColorGrey},
/*68*/  { {4.5, 0.0, -8.5}, NZPZ, ColorGrey},
/*69*/  { {5.5, 0.0, -8.5}, NZPZ, ColorGrey},
/*70*/  { {6.5, 0.0, -8.5}, NZPZ, ColorGrey},
/*71*/  { {7.5, 0.0, -8.5}, NZPZ, ColorGrey},

/*72*/  { {0.5, 0.0, -9.5}, NZPZ, ColorGrey},
/*73*/  { {1.5, 0.0, -9.5}, NZPZ, ColorGrey},
/*74*/  { {2.5, 0.0, -9.5}, NZPZ, ColorGrey},
/*75*/  { {3.5, 0.0, -9.5}, NZPZ, ColorGrey},
/*76*/  { {4.5, 0.0, -9.5}, NZPZ, ColorGrey},
/*77*/  { {5.5, 0.0, -9.5}, NZPZ, ColorGrey},
/*78*/  { {6.5, 0.0, -9.5}, NZPZ, ColorGrey},
/*79*/  { {7.5, 0.0, -9.5}, NZPZ, ColorGrey},

/*80*/  { {0.5, 0.0, -10.5}, NZPZ, ColorGrey},
/*81*/  { {1.5, 0.0, -10.5}, NZPZ, ColorGrey},
/*82*/  { {2.5, 0.0, -10.5}, NZPZ, ColorGrey},
/*83*/  { {3.5, 0.0, -10.5}, NZPZ, ColorGrey},
/*84*/  { {4.5, 0.0, -10.5}, NZPZ, ColorGrey},
/*85*/  { {5.5, 0.0, -10.5}, NZPZ, ColorGrey},
/*86*/  { {6.5, 0.0, -10.5}, NZPZ, ColorGrey},
/*87*/  { {7.5, 0.0, -10.5}, NZPZ, ColorGrey},

/*88*/  { {0.5, 0.0, -11.5}, NZPZ, ColorGrey},
/*89*/  { {1.5, 0.0, -11.5}, NZPZ, ColorGrey},
/*90*/  { {2.5, 0.0, -11.5}, NZPZ, ColorGrey},
/*91*/  { {3.5, 0.0, -11.5}, NZPZ, ColorGrey},
/*92*/  { {4.5, 0.0, -11.5}, NZPZ, ColorGrey},
/*93*/  { {5.5, 0.0, -11.5}, NZPZ, ColorGrey},
/*94*/  { {6.5, 0.0, -11.5}, NZPZ, ColorGrey},
/*95*/  { {7.5, 0.0, -11.5}, NZPZ, ColorGrey},
// any character not white quad middle front finish

// [0, 95] is 96

// 2313

// any character not white back start
/*0*/   { {0.0, -2.0, 0.0}, NZNZ, ColorGrey},
/*1*/   { {1.0, -2.0, 0.0}, NZNZ, ColorGrey},
/*2*/   { {2.0, -2.0, 0.0}, NZNZ, ColorGrey},
/*3*/   { {3.0, -2.0, 0.0}, NZNZ, ColorGrey},
/*4*/   { {4.0, -2.0, 0.0}, NZNZ, ColorGrey},
/*5*/   { {5.0, -2.0, 0.0}, NZNZ, ColorGrey},
/*6*/   { {6.0, -2.0, 0.0}, NZNZ, ColorGrey},
/*7*/   { {7.0, -2.0, 0.0}, NZNZ, ColorGrey},
/*8*/   { {8.0, -2.0, 0.0}, NZNZ, ColorGrey},

/*9*/   { {0.0, -2.0, -1.0}, NZNZ, ColorGrey},
/*10*/  { {1.0, -2.0, -1.0}, NZNZ, ColorGrey},
/*11*/  { {2.0, -2.0, -1.0}, NZNZ, ColorGrey},
/*12*/  { {3.0, -2.0, -1.0}, NZNZ, ColorGrey},
/*13*/  { {4.0, -2.0, -1.0}, NZNZ, ColorGrey},
/*14*/  { {5.0, -2.0, -1.0}, NZNZ, ColorGrey},
/*15*/  { {6.0, -2.0, -1.0}, NZNZ, ColorGrey},
/*16*/  { {7.0, -2.0, -1.0}, NZNZ, ColorGrey},
/*17*/  { {8.0, -2.0, -1.0}, NZNZ, ColorGrey},

/*18*/  { {0.0, -2.0, -2.0}, NZNZ, ColorGrey},
/*19*/  { {1.0, -2.0, -2.0}, NZNZ, ColorGrey},
/*20*/  { {2.0, -2.0, -2.0}, NZNZ, ColorGrey},
/*21*/  { {3.0, -2.0, -2.0}, NZNZ, ColorGrey},
/*22*/  { {4.0, -2.0, -2.0}, NZNZ, ColorGrey},
/*23*/  { {5.0, -2.0, -2.0}, NZNZ, ColorGrey},
/*24*/  { {6.0, -2.0, -2.0}, NZNZ, ColorGrey},
/*25*/  { {7.0, -2.0, -2.0}, NZNZ, ColorGrey},
/*26*/  { {8.0, -2.0, -2.0}, NZNZ, ColorGrey},

/*27*/  { {0.0, -2.0, -3.0}, NZNZ, ColorGrey},
/*28*/  { {1.0, -2.0, -3.0}, NZNZ, ColorGrey},
/*29*/  { {2.0, -2.0, -3.0}, NZNZ, ColorGrey},
/*30*/  { {3.0, -2.0, -3.0}, NZNZ, ColorGrey},
/*31*/  { {4.0, -2.0, -3.0}, NZNZ, ColorGrey},
/*32*/  { {5.0, -2.0, -3.0}, NZNZ, ColorGrey},
/*33*/  { {6.0, -2.0, -3.0}, NZNZ, ColorGrey},
/*34*/  { {7.0, -2.0, -3.0}, NZNZ, ColorGrey},
/*35*/  { {8.0, -2.0, -3.0}, NZNZ, ColorGrey},

/*36*/  { {0.0, -2.0, -4.0}, NZNZ, ColorGrey},
/*37*/  { {1.0, -2.0, -4.0}, NZNZ, ColorGrey},
/*38*/  { {2.0, -2.0, -4.0}, NZNZ, ColorGrey},
/*39*/  { {3.0, -2.0, -4.0}, NZNZ, ColorGrey},
/*40*/  { {4.0, -2.0, -4.0}, NZNZ, ColorGrey},
/*41*/  { {5.0, -2.0, -4.0}, NZNZ, ColorGrey},
/*42*/  { {6.0, -2.0, -4.0}, NZNZ, ColorGrey},
/*43*/  { {7.0, -2.0, -4.0}, NZNZ, ColorGrey},
/*44*/  { {8.0, -2.0, -4.0}, NZNZ, ColorGrey},

/*45*/  { {0.0, -2.0, -5.0}, NZNZ, ColorGrey},
/*46*/  { {1.0, -2.0, -5.0}, NZNZ, ColorGrey},
/*47*/  { {2.0, -2.0, -5.0}, NZNZ, ColorGrey},
/*48*/  { {3.0, -2.0, -5.0}, NZNZ, ColorGrey},
/*49*/  { {4.0, -2.0, -5.0}, NZNZ, ColorGrey},
/*50*/  { {5.0, -2.0, -5.0}, NZNZ, ColorGrey},
/*51*/  { {6.0, -2.0, -5.0}, NZNZ, ColorGrey},
/*52*/  { {7.0, -2.0, -5.0}, NZNZ, ColorGrey},
/*53*/  { {8.0, -2.0, -5.0}, NZNZ, ColorGrey},

/*54*/  { {0.0, -2.0, -6.0}, NZNZ, ColorGrey},
/*55*/  { {1.0, -2.0, -6.0}, NZNZ, ColorGrey},
/*56*/  { {2.0, -2.0, -6.0}, NZNZ, ColorGrey},
/*57*/  { {3.0, -2.0, -6.0}, NZNZ, ColorGrey},
/*58*/  { {4.0, -2.0, -6.0}, NZNZ, ColorGrey},
/*59*/  { {5.0, -2.0, -6.0}, NZNZ, ColorGrey},
/*60*/  { {6.0, -2.0, -6.0}, NZNZ, ColorGrey},
/*61*/  { {7.0, -2.0, -6.0}, NZNZ, ColorGrey},
/*62*/  { {8.0, -2.0, -6.0}, NZNZ, ColorGrey},

/*63*/  { {0.0, -2.0, -7.0}, NZNZ, ColorGrey},
/*64*/  { {1.0, -2.0, -7.0}, NZNZ, ColorGrey},
/*65*/  { {2.0, -2.0, -7.0}, NZNZ, ColorGrey},
/*66*/  { {3.0, -2.0, -7.0}, NZNZ, ColorGrey},
/*67*/  { {4.0, -2.0, -7.0}, NZNZ, ColorGrey},
/*68*/  { {5.0, -2.0, -7.0}, NZNZ, ColorGrey},
/*69*/  { {6.0, -2.0, -7.0}, NZNZ, ColorGrey},
/*70*/  { {7.0, -2.0, -7.0}, NZNZ, ColorGrey},
/*71*/  { {8.0, -2.0, -7.0}, NZNZ, ColorGrey},

/*72*/  { {0.0, -2.0, -8.0}, NZNZ, ColorGrey},
/*73*/  { {1.0, -2.0, -8.0}, NZNZ, ColorGrey},
/*74*/  { {2.0, -2.0, -8.0}, NZNZ, ColorGrey},
/*75*/  { {3.0, -2.0, -8.0}, NZNZ, ColorGrey},
/*76*/  { {4.0, -2.0, -8.0}, NZNZ, ColorGrey},
/*77*/  { {5.0, -2.0, -8.0}, NZNZ, ColorGrey},
/*78*/  { {6.0, -2.0, -8.0}, NZNZ, ColorGrey},
/*79*/  { {7.0, -2.0, -8.0}, NZNZ, ColorGrey},
/*80*/  { {8.0, -2.0, -8.0}, NZNZ, ColorGrey},

/*81*/  { {0.0, -2.0, -9.0}, NZNZ, ColorGrey},
/*82*/  { {1.0, -2.0, -9.0}, NZNZ, ColorGrey},
/*83*/  { {2.0, -2.0, -9.0}, NZNZ, ColorGrey},
/*84*/  { {3.0, -2.0, -9.0}, NZNZ, ColorGrey},
/*85*/  { {4.0, -2.0, -9.0}, NZNZ, ColorGrey},
/*86*/  { {5.0, -2.0, -9.0}, NZNZ, ColorGrey},
/*87*/  { {6.0, -2.0, -9.0}, NZNZ, ColorGrey},
/*88*/  { {7.0, -2.0, -9.0}, NZNZ, ColorGrey},
/*89*/  { {8.0, -2.0, -9.0}, NZNZ, ColorGrey},

/*90*/  { {0.0, -2.0, -10.0}, NZNZ, ColorGrey},
/*91*/  { {1.0, -2.0, -10.0}, NZNZ, ColorGrey},
/*92*/  { {2.0, -2.0, -10.0}, NZNZ, ColorGrey},
/*93*/  { {3.0, -2.0, -10.0}, NZNZ, ColorGrey},
/*94*/  { {4.0, -2.0, -10.0}, NZNZ, ColorGrey},
/*95*/  { {5.0, -2.0, -10.0}, NZNZ, ColorGrey},
/*96*/  { {6.0, -2.0, -10.0}, NZNZ, ColorGrey},
/*97*/  { {7.0, -2.0, -10.0}, NZNZ, ColorGrey},
/*98*/  { {8.0, -2.0, -10.0}, NZNZ, ColorGrey},

/*99*/  { {0.0, -2.0, -11.0}, NZNZ, ColorGrey},
/*100*/ { {1.0, -2.0, -11.0}, NZNZ, ColorGrey},
/*101*/ { {2.0, -2.0, -11.0}, NZNZ, ColorGrey},
/*102*/ { {3.0, -2.0, -11.0}, NZNZ, ColorGrey},
/*103*/ { {4.0, -2.0, -11.0}, NZNZ, ColorGrey},
/*104*/ { {5.0, -2.0, -11.0}, NZNZ, ColorGrey},
/*105*/ { {6.0, -2.0, -11.0}, NZNZ, ColorGrey},
/*106*/ { {7.0, -2.0, -11.0}, NZNZ, ColorGrey},
/*107*/ { {8.0, -2.0, -11.0}, NZNZ, ColorGrey},

/*108*/ { {0.0, -2.0, -12.0}, NZNZ, ColorGrey},
/*109*/ { {1.0, -2.0, -12.0}, NZNZ, ColorGrey},
/*110*/ { {2.0, -2.0, -12.0}, NZNZ, ColorGrey},
/*111*/ { {3.0, -2.0, -12.0}, NZNZ, ColorGrey},
/*112*/ { {4.0, -2.0, -12.0}, NZNZ, ColorGrey},
/*113*/ { {5.0, -2.0, -12.0}, NZNZ, ColorGrey},
/*114*/ { {6.0, -2.0, -12.0}, NZNZ, ColorGrey},
/*115*/ { {7.0, -2.0, -12.0}, NZNZ, ColorGrey},
/*116*/ { {8.0, -2.0, -12.0}, NZNZ, ColorGrey},
// any character not white back finish

// [0, 116] is 117

// 2430

// any character not white quad middle back start
/*0*/   { {0.5, -2.0, -0.5}, NZNZ, ColorGrey},
/*1*/   { {1.5, -2.0, -0.5}, NZNZ, ColorGrey},
/*2*/   { {2.5, -2.0, -0.5}, NZNZ, ColorGrey},
/*3*/   { {3.5, -2.0, -0.5}, NZNZ, ColorGrey},
/*4*/   { {4.5, -2.0, -0.5}, NZNZ, ColorGrey},
/*5*/   { {5.5, -2.0, -0.5}, NZNZ, ColorGrey},
/*6*/   { {6.5, -2.0, -0.5}, NZNZ, ColorGrey},
/*7*/   { {7.5, -2.0, -0.5}, NZNZ, ColorGrey},

/*8*/   { {0.5, -2.0, -1.5}, NZNZ, ColorGrey},
/*9*/   { {1.5, -2.0, -1.5}, NZNZ, ColorGrey},
/*10*/  { {2.5, -2.0, -1.5}, NZNZ, ColorGrey},
/*11*/  { {3.5, -2.0, -1.5}, NZNZ, ColorGrey},
/*12*/  { {4.5, -2.0, -1.5}, NZNZ, ColorGrey},
/*13*/  { {5.5, -2.0, -1.5}, NZNZ, ColorGrey},
/*14*/  { {6.5, -2.0, -1.5}, NZNZ, ColorGrey},
/*15*/  { {7.5, -2.0, -1.5}, NZNZ, ColorGrey},

/*16*/  { {0.5, -2.0, -2.5}, NZNZ, ColorGrey},
/*17*/  { {1.5, -2.0, -2.5}, NZNZ, ColorGrey},
/*18*/  { {2.5, -2.0, -2.5}, NZNZ, ColorGrey},
/*19*/  { {3.5, -2.0, -2.5}, NZNZ, ColorGrey},
/*20*/  { {4.5, -2.0, -2.5}, NZNZ, ColorGrey},
/*21*/  { {5.5, -2.0, -2.5}, NZNZ, ColorGrey},
/*22*/  { {6.5, -2.0, -2.5}, NZNZ, ColorGrey},
/*23*/  { {7.5, -2.0, -2.5}, NZNZ, ColorGrey},

/*24*/  { {0.5, -2.0, -3.5}, NZNZ, ColorGrey},
/*25*/  { {1.5, -2.0, -3.5}, NZNZ, ColorGrey},
/*26*/  { {2.5, -2.0, -3.5}, NZNZ, ColorGrey},
/*27*/  { {3.5, -2.0, -3.5}, NZNZ, ColorGrey},
/*28*/  { {4.5, -2.0, -3.5}, NZNZ, ColorGrey},
/*29*/  { {5.5, -2.0, -3.5}, NZNZ, ColorGrey},
/*30*/  { {6.5, -2.0, -3.5}, NZNZ, ColorGrey},
/*31*/  { {7.5, -2.0, -3.5}, NZNZ, ColorGrey},

/*32*/  { {0.5, -2.0, -4.5}, NZNZ, ColorGrey},
/*33*/  { {1.5, -2.0, -4.5}, NZNZ, ColorGrey},
/*34*/  { {2.5, -2.0, -4.5}, NZNZ, ColorGrey},
/*35*/  { {3.5, -2.0, -4.5}, NZNZ, ColorGrey},
/*36*/  { {4.5, -2.0, -4.5}, NZNZ, ColorGrey},
/*37*/  { {5.5, -2.0, -4.5}, NZNZ, ColorGrey},
/*38*/  { {6.5, -2.0, -4.5}, NZNZ, ColorGrey},
/*39*/  { {7.5, -2.0, -4.5}, NZNZ, ColorGrey},

/*40*/  { {0.5, -2.0, -5.5}, NZNZ, ColorGrey},
/*41*/  { {1.5, -2.0, -5.5}, NZNZ, ColorGrey},
/*42*/  { {2.5, -2.0, -5.5}, NZNZ, ColorGrey},
/*43*/  { {3.5, -2.0, -5.5}, NZNZ, ColorGrey},
/*44*/  { {4.5, -2.0, -5.5}, NZNZ, ColorGrey},
/*45*/  { {5.5, -2.0, -5.5}, NZNZ, ColorGrey},
/*46*/  { {6.5, -2.0, -5.5}, NZNZ, ColorGrey},
/*47*/  { {7.5, -2.0, -5.5}, NZNZ, ColorGrey},

/*48*/  { {0.5, -2.0, -6.5}, NZNZ, ColorGrey},
/*49*/  { {1.5, -2.0, -6.5}, NZNZ, ColorGrey},
/*50*/  { {2.5, -2.0, -6.5}, NZNZ, ColorGrey},
/*51*/  { {3.5, -2.0, -6.5}, NZNZ, ColorGrey},
/*52*/  { {4.5, -2.0, -6.5}, NZNZ, ColorGrey},
/*53*/  { {5.5, -2.0, -6.5}, NZNZ, ColorGrey},
/*54*/  { {6.5, -2.0, -6.5}, NZNZ, ColorGrey},
/*55*/  { {7.5, -2.0, -6.5}, NZNZ, ColorGrey},

/*56*/  { {0.5, -2.0, -7.5}, NZNZ, ColorGrey},
/*57*/  { {1.5, -2.0, -7.5}, NZNZ, ColorGrey},
/*58*/  { {2.5, -2.0, -7.5}, NZNZ, ColorGrey},
/*59*/  { {3.5, -2.0, -7.5}, NZNZ, ColorGrey},
/*60*/  { {4.5, -2.0, -7.5}, NZNZ, ColorGrey},
/*61*/  { {5.5, -2.0, -7.5}, NZNZ, ColorGrey},
/*62*/  { {6.5, -2.0, -7.5}, NZNZ, ColorGrey},
/*63*/  { {7.5, -2.0, -7.5}, NZNZ, ColorGrey},

/*64*/  { {0.5, -2.0, -8.5}, NZNZ, ColorGrey},
/*65*/  { {1.5, -2.0, -8.5}, NZNZ, ColorGrey},
/*66*/  { {2.5, -2.0, -8.5}, NZNZ, ColorGrey},
/*67*/  { {3.5, -2.0, -8.5}, NZNZ, ColorGrey},
/*68*/  { {4.5, -2.0, -8.5}, NZNZ, ColorGrey},
/*69*/  { {5.5, -2.0, -8.5}, NZNZ, ColorGrey},
/*70*/  { {6.5, -2.0, -8.5}, NZNZ, ColorGrey},
/*71*/  { {7.5, -2.0, -8.5}, NZNZ, ColorGrey},

/*72*/  { {0.5, -2.0, -9.5}, NZNZ, ColorGrey},
/*73*/  { {1.5, -2.0, -9.5}, NZNZ, ColorGrey},
/*74*/  { {2.5, -2.0, -9.5}, NZNZ, ColorGrey},
/*75*/  { {3.5, -2.0, -9.5}, NZNZ, ColorGrey},
/*76*/  { {4.5, -2.0, -9.5}, NZNZ, ColorGrey},
/*77*/  { {5.5, -2.0, -9.5}, NZNZ, ColorGrey},
/*78*/  { {6.5, -2.0, -9.5}, NZNZ, ColorGrey},
/*79*/  { {7.5, -2.0, -9.5}, NZNZ, ColorGrey},

/*80*/  { {0.5, -2.0, -10.5}, NZNZ, ColorGrey},
/*81*/  { {1.5, -2.0, -10.5}, NZNZ, ColorGrey},
/*82*/  { {2.5, -2.0, -10.5}, NZNZ, ColorGrey},
/*83*/  { {3.5, -2.0, -10.5}, NZNZ, ColorGrey},
/*84*/  { {4.5, -2.0, -10.5}, NZNZ, ColorGrey},
/*85*/  { {5.5, -2.0, -10.5}, NZNZ, ColorGrey},
/*86*/  { {6.5, -2.0, -10.5}, NZNZ, ColorGrey},
/*87*/  { {7.5, -2.0, -10.5}, NZNZ, ColorGrey},

/*88*/  { {0.5, -2.0, -11.5}, NZNZ, ColorGrey},
/*89*/  { {1.5, -2.0, -11.5}, NZNZ, ColorGrey},
/*90*/  { {2.5, -2.0, -11.5}, NZNZ, ColorGrey},
/*91*/  { {3.5, -2.0, -11.5}, NZNZ, ColorGrey},
/*92*/  { {4.5, -2.0, -11.5}, NZNZ, ColorGrey},
/*93*/  { {5.5, -2.0, -11.5}, NZNZ, ColorGrey},
/*94*/  { {6.5, -2.0, -11.5}, NZNZ, ColorGrey},
/*95*/  { {7.5, -2.0, -11.5}, NZNZ, ColorGrey},
// any character not white quad middle back finish

// [0, 95] is 96

// 2526

// any character not white left front start
/*0*/   { {0.0, 0.0, 0.0}, NNZZ, ColorGrey},
/*1*/   { {1.0, 0.0, 0.0}, NNZZ, ColorGrey},
/*2*/   { {2.0, 0.0, 0.0}, NNZZ, ColorGrey},
/*3*/   { {3.0, 0.0, 0.0}, NNZZ, ColorGrey},
/*4*/   { {4.0, 0.0, 0.0}, NNZZ, ColorGrey},
/*5*/   { {5.0, 0.0, 0.0}, NNZZ, ColorGrey},
/*6*/   { {6.0, 0.0, 0.0}, NNZZ, ColorGrey},
/*7*/   { {7.0, 0.0, 0.0}, NNZZ, ColorGrey},
/*8*/   { {8.0, 0.0, 0.0}, NNZZ, ColorGrey},

/*9*/   { {0.0, 0.0, -1.0}, NNZZ, ColorGrey},
/*10*/  { {1.0, 0.0, -1.0}, NNZZ, ColorGrey},
/*11*/  { {2.0, 0.0, -1.0}, NNZZ, ColorGrey},
/*12*/  { {3.0, 0.0, -1.0}, NNZZ, ColorGrey},
/*13*/  { {4.0, 0.0, -1.0}, NNZZ, ColorGrey},
/*14*/  { {5.0, 0.0, -1.0}, NNZZ, ColorGrey},
/*15*/  { {6.0, 0.0, -1.0}, NNZZ, ColorGrey},
/*16*/  { {7.0, 0.0, -1.0}, NNZZ, ColorGrey},
/*17*/  { {8.0, 0.0, -1.0}, NNZZ, ColorGrey},

/*18*/  { {0.0, 0.0, -2.0}, NNZZ, ColorGrey},
/*19*/  { {1.0, 0.0, -2.0}, NNZZ, ColorGrey},
/*20*/  { {2.0, 0.0, -2.0}, NNZZ, ColorGrey},
/*21*/  { {3.0, 0.0, -2.0}, NNZZ, ColorGrey},
/*22*/  { {4.0, 0.0, -2.0}, NNZZ, ColorGrey},
/*23*/  { {5.0, 0.0, -2.0}, NNZZ, ColorGrey},
/*24*/  { {6.0, 0.0, -2.0}, NNZZ, ColorGrey},
/*25*/  { {7.0, 0.0, -2.0}, NNZZ, ColorGrey},
/*26*/  { {8.0, 0.0, -2.0}, NNZZ, ColorGrey},

/*27*/  { {0.0, 0.0, -3.0}, NNZZ, ColorGrey},
/*28*/  { {1.0, 0.0, -3.0}, NNZZ, ColorGrey},
/*29*/  { {2.0, 0.0, -3.0}, NNZZ, ColorGrey},
/*30*/  { {3.0, 0.0, -3.0}, NNZZ, ColorGrey},
/*31*/  { {4.0, 0.0, -3.0}, NNZZ, ColorGrey},
/*32*/  { {5.0, 0.0, -3.0}, NNZZ, ColorGrey},
/*33*/  { {6.0, 0.0, -3.0}, NNZZ, ColorGrey},
/*34*/  { {7.0, 0.0, -3.0}, NNZZ, ColorGrey},
/*35*/  { {8.0, 0.0, -3.0}, NNZZ, ColorGrey},

/*36*/  { {0.0, 0.0, -4.0}, NNZZ, ColorGrey},
/*37*/  { {1.0, 0.0, -4.0}, NNZZ, ColorGrey},
/*38*/  { {2.0, 0.0, -4.0}, NNZZ, ColorGrey},
/*39*/  { {3.0, 0.0, -4.0}, NNZZ, ColorGrey},
/*40*/  { {4.0, 0.0, -4.0}, NNZZ, ColorGrey},
/*41*/  { {5.0, 0.0, -4.0}, NNZZ, ColorGrey},
/*42*/  { {6.0, 0.0, -4.0}, NNZZ, ColorGrey},
/*43*/  { {7.0, 0.0, -4.0}, NNZZ, ColorGrey},
/*44*/  { {8.0, 0.0, -4.0}, NNZZ, ColorGrey},

/*45*/  { {0.0, 0.0, -5.0}, NNZZ, ColorGrey},
/*46*/  { {1.0, 0.0, -5.0}, NNZZ, ColorGrey},
/*47*/  { {2.0, 0.0, -5.0}, NNZZ, ColorGrey},
/*48*/  { {3.0, 0.0, -5.0}, NNZZ, ColorGrey},
/*49*/  { {4.0, 0.0, -5.0}, NNZZ, ColorGrey},
/*50*/  { {5.0, 0.0, -5.0}, NNZZ, ColorGrey},
/*51*/  { {6.0, 0.0, -5.0}, NNZZ, ColorGrey},
/*52*/  { {7.0, 0.0, -5.0}, NNZZ, ColorGrey},
/*53*/  { {8.0, 0.0, -5.0}, NNZZ, ColorGrey},

/*54*/  { {0.0, 0.0, -6.0}, NNZZ, ColorGrey},
/*55*/  { {1.0, 0.0, -6.0}, NNZZ, ColorGrey},
/*56*/  { {2.0, 0.0, -6.0}, NNZZ, ColorGrey},
/*57*/  { {3.0, 0.0, -6.0}, NNZZ, ColorGrey},
/*58*/  { {4.0, 0.0, -6.0}, NNZZ, ColorGrey},
/*59*/  { {5.0, 0.0, -6.0}, NNZZ, ColorGrey},
/*60*/  { {6.0, 0.0, -6.0}, NNZZ, ColorGrey},
/*61*/  { {7.0, 0.0, -6.0}, NNZZ, ColorGrey},
/*62*/  { {8.0, 0.0, -6.0}, NNZZ, ColorGrey},

/*63*/  { {0.0, 0.0, -7.0}, NNZZ, ColorGrey},
/*64*/  { {1.0, 0.0, -7.0}, NNZZ, ColorGrey},
/*65*/  { {2.0, 0.0, -7.0}, NNZZ, ColorGrey},
/*66*/  { {3.0, 0.0, -7.0}, NNZZ, ColorGrey},
/*67*/  { {4.0, 0.0, -7.0}, NNZZ, ColorGrey},
/*68*/  { {5.0, 0.0, -7.0}, NNZZ, ColorGrey},
/*69*/  { {6.0, 0.0, -7.0}, NNZZ, ColorGrey},
/*70*/  { {7.0, 0.0, -7.0}, NNZZ, ColorGrey},
/*71*/  { {8.0, 0.0, -7.0}, NNZZ, ColorGrey},

/*72*/  { {0.0, 0.0, -8.0}, NNZZ, ColorGrey},
/*73*/  { {1.0, 0.0, -8.0}, NNZZ, ColorGrey},
/*74*/  { {2.0, 0.0, -8.0}, NNZZ, ColorGrey},
/*75*/  { {3.0, 0.0, -8.0}, NNZZ, ColorGrey},
/*76*/  { {4.0, 0.0, -8.0}, NNZZ, ColorGrey},
/*77*/  { {5.0, 0.0, -8.0}, NNZZ, ColorGrey},
/*78*/  { {6.0, 0.0, -8.0}, NNZZ, ColorGrey},
/*79*/  { {7.0, 0.0, -8.0}, NNZZ, ColorGrey},
/*80*/  { {8.0, 0.0, -8.0}, NNZZ, ColorGrey},

/*81*/  { {0.0, 0.0, -9.0}, NNZZ, ColorGrey},
/*82*/  { {1.0, 0.0, -9.0}, NNZZ, ColorGrey},
/*83*/  { {2.0, 0.0, -9.0}, NNZZ, ColorGrey},
/*84*/  { {3.0, 0.0, -9.0}, NNZZ, ColorGrey},
/*85*/  { {4.0, 0.0, -9.0}, NNZZ, ColorGrey},
/*86*/  { {5.0, 0.0, -9.0}, NNZZ, ColorGrey},
/*87*/  { {6.0, 0.0, -9.0}, NNZZ, ColorGrey},
/*88*/  { {7.0, 0.0, -9.0}, NNZZ, ColorGrey},
/*89*/  { {8.0, 0.0, -9.0}, NNZZ, ColorGrey},

/*90*/  { {0.0, 0.0, -10.0}, NNZZ, ColorGrey},
/*91*/  { {1.0, 0.0, -10.0}, NNZZ, ColorGrey},
/*92*/  { {2.0, 0.0, -10.0}, NNZZ, ColorGrey},
/*93*/  { {3.0, 0.0, -10.0}, NNZZ, ColorGrey},
/*94*/  { {4.0, 0.0, -10.0}, NNZZ, ColorGrey},
/*95*/  { {5.0, 0.0, -10.0}, NNZZ, ColorGrey},
/*96*/  { {6.0, 0.0, -10.0}, NNZZ, ColorGrey},
/*97*/  { {7.0, 0.0, -10.0}, NNZZ, ColorGrey},
/*98*/  { {8.0, 0.0, -10.0}, NNZZ, ColorGrey},

/*99*/  { {0.0, 0.0, -11.0}, NNZZ, ColorGrey},
/*100*/ { {1.0, 0.0, -11.0}, NNZZ, ColorGrey},
/*101*/ { {2.0, 0.0, -11.0}, NNZZ, ColorGrey},
/*102*/ { {3.0, 0.0, -11.0}, NNZZ, ColorGrey},
/*103*/ { {4.0, 0.0, -11.0}, NNZZ, ColorGrey},
/*104*/ { {5.0, 0.0, -11.0}, NNZZ, ColorGrey},
/*105*/ { {6.0, 0.0, -11.0}, NNZZ, ColorGrey},
/*106*/ { {7.0, 0.0, -11.0}, NNZZ, ColorGrey},
/*107*/ { {8.0, 0.0, -11.0}, NNZZ, ColorGrey},

/*108*/ { {0.0, 0.0, -12.0}, NNZZ, ColorGrey},
/*109*/ { {1.0, 0.0, -12.0}, NNZZ, ColorGrey},
/*110*/ { {2.0, 0.0, -12.0}, NNZZ, ColorGrey},
/*111*/ { {3.0, 0.0, -12.0}, NNZZ, ColorGrey},
/*112*/ { {4.0, 0.0, -12.0}, NNZZ, ColorGrey},
/*113*/ { {5.0, 0.0, -12.0}, NNZZ, ColorGrey},
/*114*/ { {6.0, 0.0, -12.0}, NNZZ, ColorGrey},
/*115*/ { {7.0, 0.0, -12.0}, NNZZ, ColorGrey},
/*116*/ { {8.0, 0.0, -12.0}, NNZZ, ColorGrey},
// any character not white left front finish

// [0, 116] is 117

// 2643

// any character not white left back start
/*0*/   { {0.0, -2.0, 0.0}, NNZZ, ColorGrey},
/*1*/   { {1.0, -2.0, 0.0}, NNZZ, ColorGrey},
/*2*/   { {2.0, -2.0, 0.0}, NNZZ, ColorGrey},
/*3*/   { {3.0, -2.0, 0.0}, NNZZ, ColorGrey},
/*4*/   { {4.0, -2.0, 0.0}, NNZZ, ColorGrey},
/*5*/   { {5.0, -2.0, 0.0}, NNZZ, ColorGrey},
/*6*/   { {6.0, -2.0, 0.0}, NNZZ, ColorGrey},
/*7*/   { {7.0, -2.0, 0.0}, NNZZ, ColorGrey},
/*8*/   { {8.0, -2.0, 0.0}, NNZZ, ColorGrey},

/*9*/   { {0.0, -2.0, -1.0}, NNZZ, ColorGrey},
/*10*/  { {1.0, -2.0, -1.0}, NNZZ, ColorGrey},
/*11*/  { {2.0, -2.0, -1.0}, NNZZ, ColorGrey},
/*12*/  { {3.0, -2.0, -1.0}, NNZZ, ColorGrey},
/*13*/  { {4.0, -2.0, -1.0}, NNZZ, ColorGrey},
/*14*/  { {5.0, -2.0, -1.0}, NNZZ, ColorGrey},
/*15*/  { {6.0, -2.0, -1.0}, NNZZ, ColorGrey},
/*16*/  { {7.0, -2.0, -1.0}, NNZZ, ColorGrey},
/*17*/  { {8.0, -2.0, -1.0}, NNZZ, ColorGrey},

/*18*/  { {0.0, -2.0, -2.0}, NNZZ, ColorGrey},
/*19*/  { {1.0, -2.0, -2.0}, NNZZ, ColorGrey},
/*20*/  { {2.0, -2.0, -2.0}, NNZZ, ColorGrey},
/*21*/  { {3.0, -2.0, -2.0}, NNZZ, ColorGrey},
/*22*/  { {4.0, -2.0, -2.0}, NNZZ, ColorGrey},
/*23*/  { {5.0, -2.0, -2.0}, NNZZ, ColorGrey},
/*24*/  { {6.0, -2.0, -2.0}, NNZZ, ColorGrey},
/*25*/  { {7.0, -2.0, -2.0}, NNZZ, ColorGrey},
/*26*/  { {8.0, -2.0, -2.0}, NNZZ, ColorGrey},

/*27*/  { {0.0, -2.0, -3.0}, NNZZ, ColorGrey},
/*28*/  { {1.0, -2.0, -3.0}, NNZZ, ColorGrey},
/*29*/  { {2.0, -2.0, -3.0}, NNZZ, ColorGrey},
/*30*/  { {3.0, -2.0, -3.0}, NNZZ, ColorGrey},
/*31*/  { {4.0, -2.0, -3.0}, NNZZ, ColorGrey},
/*32*/  { {5.0, -2.0, -3.0}, NNZZ, ColorGrey},
/*33*/  { {6.0, -2.0, -3.0}, NNZZ, ColorGrey},
/*34*/  { {7.0, -2.0, -3.0}, NNZZ, ColorGrey},
/*35*/  { {8.0, -2.0, -3.0}, NNZZ, ColorGrey},

/*36*/  { {0.0, -2.0, -4.0}, NNZZ, ColorGrey},
/*37*/  { {1.0, -2.0, -4.0}, NNZZ, ColorGrey},
/*38*/  { {2.0, -2.0, -4.0}, NNZZ, ColorGrey},
/*39*/  { {3.0, -2.0, -4.0}, NNZZ, ColorGrey},
/*40*/  { {4.0, -2.0, -4.0}, NNZZ, ColorGrey},
/*41*/  { {5.0, -2.0, -4.0}, NNZZ, ColorGrey},
/*42*/  { {6.0, -2.0, -4.0}, NNZZ, ColorGrey},
/*43*/  { {7.0, -2.0, -4.0}, NNZZ, ColorGrey},
/*44*/  { {8.0, -2.0, -4.0}, NNZZ, ColorGrey},

/*45*/  { {0.0, -2.0, -5.0}, NNZZ, ColorGrey},
/*46*/  { {1.0, -2.0, -5.0}, NNZZ, ColorGrey},
/*47*/  { {2.0, -2.0, -5.0}, NNZZ, ColorGrey},
/*48*/  { {3.0, -2.0, -5.0}, NNZZ, ColorGrey},
/*49*/  { {4.0, -2.0, -5.0}, NNZZ, ColorGrey},
/*50*/  { {5.0, -2.0, -5.0}, NNZZ, ColorGrey},
/*51*/  { {6.0, -2.0, -5.0}, NNZZ, ColorGrey},
/*52*/  { {7.0, -2.0, -5.0}, NNZZ, ColorGrey},
/*53*/  { {8.0, -2.0, -5.0}, NNZZ, ColorGrey},

/*54*/  { {0.0, -2.0, -6.0}, NNZZ, ColorGrey},
/*55*/  { {1.0, -2.0, -6.0}, NNZZ, ColorGrey},
/*56*/  { {2.0, -2.0, -6.0}, NNZZ, ColorGrey},
/*57*/  { {3.0, -2.0, -6.0}, NNZZ, ColorGrey},
/*58*/  { {4.0, -2.0, -6.0}, NNZZ, ColorGrey},
/*59*/  { {5.0, -2.0, -6.0}, NNZZ, ColorGrey},
/*60*/  { {6.0, -2.0, -6.0}, NNZZ, ColorGrey},
/*61*/  { {7.0, -2.0, -6.0}, NNZZ, ColorGrey},
/*62*/  { {8.0, -2.0, -6.0}, NNZZ, ColorGrey},

/*63*/  { {0.0, -2.0, -7.0}, NNZZ, ColorGrey},
/*64*/  { {1.0, -2.0, -7.0}, NNZZ, ColorGrey},
/*65*/  { {2.0, -2.0, -7.0}, NNZZ, ColorGrey},
/*66*/  { {3.0, -2.0, -7.0}, NNZZ, ColorGrey},
/*67*/  { {4.0, -2.0, -7.0}, NNZZ, ColorGrey},
/*68*/  { {5.0, -2.0, -7.0}, NNZZ, ColorGrey},
/*69*/  { {6.0, -2.0, -7.0}, NNZZ, ColorGrey},
/*70*/  { {7.0, -2.0, -7.0}, NNZZ, ColorGrey},
/*71*/  { {8.0, -2.0, -7.0}, NNZZ, ColorGrey},

/*72*/  { {0.0, -2.0, -8.0}, NNZZ, ColorGrey},
/*73*/  { {1.0, -2.0, -8.0}, NNZZ, ColorGrey},
/*74*/  { {2.0, -2.0, -8.0}, NNZZ, ColorGrey},
/*75*/  { {3.0, -2.0, -8.0}, NNZZ, ColorGrey},
/*76*/  { {4.0, -2.0, -8.0}, NNZZ, ColorGrey},
/*77*/  { {5.0, -2.0, -8.0}, NNZZ, ColorGrey},
/*78*/  { {6.0, -2.0, -8.0}, NNZZ, ColorGrey},
/*79*/  { {7.0, -2.0, -8.0}, NNZZ, ColorGrey},
/*80*/  { {8.0, -2.0, -8.0}, NNZZ, ColorGrey},

/*81*/  { {0.0, -2.0, -9.0}, NNZZ, ColorGrey},
/*82*/  { {1.0, -2.0, -9.0}, NNZZ, ColorGrey},
/*83*/  { {2.0, -2.0, -9.0}, NNZZ, ColorGrey},
/*84*/  { {3.0, -2.0, -9.0}, NNZZ, ColorGrey},
/*85*/  { {4.0, -2.0, -9.0}, NNZZ, ColorGrey},
/*86*/  { {5.0, -2.0, -9.0}, NNZZ, ColorGrey},
/*87*/  { {6.0, -2.0, -9.0}, NNZZ, ColorGrey},
/*88*/  { {7.0, -2.0, -9.0}, NNZZ, ColorGrey},
/*89*/  { {8.0, -2.0, -9.0}, NNZZ, ColorGrey},

/*90*/  { {0.0, -2.0, -10.0}, NNZZ, ColorGrey},
/*91*/  { {1.0, -2.0, -10.0}, NNZZ, ColorGrey},
/*92*/  { {2.0, -2.0, -10.0}, NNZZ, ColorGrey},
/*93*/  { {3.0, -2.0, -10.0}, NNZZ, ColorGrey},
/*94*/  { {4.0, -2.0, -10.0}, NNZZ, ColorGrey},
/*95*/  { {5.0, -2.0, -10.0}, NNZZ, ColorGrey},
/*96*/  { {6.0, -2.0, -10.0}, NNZZ, ColorGrey},
/*97*/  { {7.0, -2.0, -10.0}, NNZZ, ColorGrey},
/*98*/  { {8.0, -2.0, -10.0}, NNZZ, ColorGrey},

/*99*/  { {0.0, -2.0, -11.0}, NNZZ, ColorGrey},
/*100*/ { {1.0, -2.0, -11.0}, NNZZ, ColorGrey},
/*101*/ { {2.0, -2.0, -11.0}, NNZZ, ColorGrey},
/*102*/ { {3.0, -2.0, -11.0}, NNZZ, ColorGrey},
/*103*/ { {4.0, -2.0, -11.0}, NNZZ, ColorGrey},
/*104*/ { {5.0, -2.0, -11.0}, NNZZ, ColorGrey},
/*105*/ { {6.0, -2.0, -11.0}, NNZZ, ColorGrey},
/*106*/ { {7.0, -2.0, -11.0}, NNZZ, ColorGrey},
/*107*/ { {8.0, -2.0, -11.0}, NNZZ, ColorGrey},

/*108*/ { {0.0, -2.0, -12.0}, NNZZ, ColorGrey},
/*109*/ { {1.0, -2.0, -12.0}, NNZZ, ColorGrey},
/*110*/ { {2.0, -2.0, -12.0}, NNZZ, ColorGrey},
/*111*/ { {3.0, -2.0, -12.0}, NNZZ, ColorGrey},
/*112*/ { {4.0, -2.0, -12.0}, NNZZ, ColorGrey},
/*113*/ { {5.0, -2.0, -12.0}, NNZZ, ColorGrey},
/*114*/ { {6.0, -2.0, -12.0}, NNZZ, ColorGrey},
/*115*/ { {7.0, -2.0, -12.0}, NNZZ, ColorGrey},
/*116*/ { {8.0, -2.0, -12.0}, NNZZ, ColorGrey},
// any character not white left back finish

// [0, 116] is 117

// 2760

// any character not white quad middle left start
/*0*/   { {0.0, -1.0, -0.5}, NNZZ, ColorGrey},
/*1*/   { {1.0, -1.0, -0.5}, NNZZ, ColorGrey},
/*2*/   { {2.0, -1.0, -0.5}, NNZZ, ColorGrey},
/*3*/   { {3.0, -1.0, -0.5}, NNZZ, ColorGrey},
/*4*/   { {4.0, -1.0, -0.5}, NNZZ, ColorGrey},
/*5*/   { {5.0, -1.0, -0.5}, NNZZ, ColorGrey},
/*6*/   { {6.0, -1.0, -0.5}, NNZZ, ColorGrey},
/*7*/   { {7.0, -1.0, -0.5}, NNZZ, ColorGrey},

/*8*/   { {0.0, -1.0, -1.5}, NNZZ, ColorGrey},
/*9*/   { {1.0, -1.0, -1.5}, NNZZ, ColorGrey},
/*10*/  { {2.0, -1.0, -1.5}, NNZZ, ColorGrey},
/*11*/  { {3.0, -1.0, -1.5}, NNZZ, ColorGrey},
/*12*/  { {4.0, -1.0, -1.5}, NNZZ, ColorGrey},
/*13*/  { {5.0, -1.0, -1.5}, NNZZ, ColorGrey},
/*14*/  { {6.0, -1.0, -1.5}, NNZZ, ColorGrey},
/*15*/  { {7.0, -1.0, -1.5}, NNZZ, ColorGrey},

/*16*/  { {0.0, -1.0, -2.5}, NNZZ, ColorGrey},
/*17*/  { {1.0, -1.0, -2.5}, NNZZ, ColorGrey},
/*18*/  { {2.0, -1.0, -2.5}, NNZZ, ColorGrey},
/*19*/  { {3.0, -1.0, -2.5}, NNZZ, ColorGrey},
/*20*/  { {4.0, -1.0, -2.5}, NNZZ, ColorGrey},
/*21*/  { {5.0, -1.0, -2.5}, NNZZ, ColorGrey},
/*22*/  { {6.0, -1.0, -2.5}, NNZZ, ColorGrey},
/*23*/  { {7.0, -1.0, -2.5}, NNZZ, ColorGrey},

/*24*/  { {0.0, -1.0, -3.5}, NNZZ, ColorGrey},
/*25*/  { {1.0, -1.0, -3.5}, NNZZ, ColorGrey},
/*26*/  { {2.0, -1.0, -3.5}, NNZZ, ColorGrey},
/*27*/  { {3.0, -1.0, -3.5}, NNZZ, ColorGrey},
/*28*/  { {4.0, -1.0, -3.5}, NNZZ, ColorGrey},
/*29*/  { {5.0, -1.0, -3.5}, NNZZ, ColorGrey},
/*30*/  { {6.0, -1.0, -3.5}, NNZZ, ColorGrey},
/*31*/  { {7.0, -1.0, -3.5}, NNZZ, ColorGrey},

/*32*/  { {0.0, -1.0, -4.5}, NNZZ, ColorGrey},
/*33*/  { {1.0, -1.0, -4.5}, NNZZ, ColorGrey},
/*34*/  { {2.0, -1.0, -4.5}, NNZZ, ColorGrey},
/*35*/  { {3.0, -1.0, -4.5}, NNZZ, ColorGrey},
/*36*/  { {4.0, -1.0, -4.5}, NNZZ, ColorGrey},
/*37*/  { {5.0, -1.0, -4.5}, NNZZ, ColorGrey},
/*38*/  { {6.0, -1.0, -4.5}, NNZZ, ColorGrey},
/*39*/  { {7.0, -1.0, -4.5}, NNZZ, ColorGrey},

/*40*/  { {0.0, -1.0, -5.5}, NNZZ, ColorGrey},
/*41*/  { {1.0, -1.0, -5.5}, NNZZ, ColorGrey},
/*42*/  { {2.0, -1.0, -5.5}, NNZZ, ColorGrey},
/*43*/  { {3.0, -1.0, -5.5}, NNZZ, ColorGrey},
/*44*/  { {4.0, -1.0, -5.5}, NNZZ, ColorGrey},
/*45*/  { {5.0, -1.0, -5.5}, NNZZ, ColorGrey},
/*46*/  { {6.0, -1.0, -5.5}, NNZZ, ColorGrey},
/*47*/  { {7.0, -1.0, -5.5}, NNZZ, ColorGrey},

/*48*/  { {0.0, -1.0, -6.5}, NNZZ, ColorGrey},
/*49*/  { {1.0, -1.0, -6.5}, NNZZ, ColorGrey},
/*50*/  { {2.0, -1.0, -6.5}, NNZZ, ColorGrey},
/*51*/  { {3.0, -1.0, -6.5}, NNZZ, ColorGrey},
/*52*/  { {4.0, -1.0, -6.5}, NNZZ, ColorGrey},
/*53*/  { {5.0, -1.0, -6.5}, NNZZ, ColorGrey},
/*54*/  { {6.0, -1.0, -6.5}, NNZZ, ColorGrey},
/*55*/  { {7.0, -1.0, -6.5}, NNZZ, ColorGrey},

/*56*/  { {0.0, -1.0, -7.5}, NNZZ, ColorGrey},
/*57*/  { {1.0, -1.0, -7.5}, NNZZ, ColorGrey},
/*58*/  { {2.0, -1.0, -7.5}, NNZZ, ColorGrey},
/*59*/  { {3.0, -1.0, -7.5}, NNZZ, ColorGrey},
/*60*/  { {4.0, -1.0, -7.5}, NNZZ, ColorGrey},
/*61*/  { {5.0, -1.0, -7.5}, NNZZ, ColorGrey},
/*62*/  { {6.0, -1.0, -7.5}, NNZZ, ColorGrey},
/*63*/  { {7.0, -1.0, -7.5}, NNZZ, ColorGrey},

/*64*/  { {0.0, -1.0, -8.5}, NNZZ, ColorGrey},
/*65*/  { {1.0, -1.0, -8.5}, NNZZ, ColorGrey},
/*66*/  { {2.0, -1.0, -8.5}, NNZZ, ColorGrey},
/*67*/  { {3.0, -1.0, -8.5}, NNZZ, ColorGrey},
/*68*/  { {4.0, -1.0, -8.5}, NNZZ, ColorGrey},
/*69*/  { {5.0, -1.0, -8.5}, NNZZ, ColorGrey},
/*70*/  { {6.0, -1.0, -8.5}, NNZZ, ColorGrey},
/*71*/  { {7.0, -1.0, -8.5}, NNZZ, ColorGrey},

/*72*/  { {0.0, -1.0, -9.5}, NNZZ, ColorGrey},
/*73*/  { {1.0, -1.0, -9.5}, NNZZ, ColorGrey},
/*74*/  { {2.0, -1.0, -9.5}, NNZZ, ColorGrey},
/*75*/  { {3.0, -1.0, -9.5}, NNZZ, ColorGrey},
/*76*/  { {4.0, -1.0, -9.5}, NNZZ, ColorGrey},
/*77*/  { {5.0, -1.0, -9.5}, NNZZ, ColorGrey},
/*78*/  { {6.0, -1.0, -9.5}, NNZZ, ColorGrey},
/*79*/  { {7.0, -1.0, -9.5}, NNZZ, ColorGrey},

/*80*/  { {0.0, -1.0, -10.5}, NNZZ, ColorGrey},
/*81*/  { {1.0, -1.0, -10.5}, NNZZ, ColorGrey},
/*82*/  { {2.0, -1.0, -10.5}, NNZZ, ColorGrey},
/*83*/  { {3.0, -1.0, -10.5}, NNZZ, ColorGrey},
/*84*/  { {4.0, -1.0, -10.5}, NNZZ, ColorGrey},
/*85*/  { {5.0, -1.0, -10.5}, NNZZ, ColorGrey},
/*86*/  { {6.0, -1.0, -10.5}, NNZZ, ColorGrey},
/*87*/  { {7.0, -1.0, -10.5}, NNZZ, ColorGrey},

/*88*/  { {0.0, -1.0, -11.5}, NNZZ, ColorGrey},
/*89*/  { {1.0, -1.0, -11.5}, NNZZ, ColorGrey},
/*90*/  { {2.0, -1.0, -11.5}, NNZZ, ColorGrey},
/*91*/  { {3.0, -1.0, -11.5}, NNZZ, ColorGrey},
/*92*/  { {4.0, -1.0, -11.5}, NNZZ, ColorGrey},
/*93*/  { {5.0, -1.0, -11.5}, NNZZ, ColorGrey},
/*94*/  { {6.0, -1.0, -11.5}, NNZZ, ColorGrey},
/*95*/  { {7.0, -1.0, -11.5}, NNZZ, ColorGrey},
// any character not white quad middle left finish

// [0, 95] is 96

// 2856

// any character not white right front start
/*0*/   { {0.0, 0.0, 0.0}, NPZZ, ColorGrey},
/*1*/   { {1.0, 0.0, 0.0}, NPZZ, ColorGrey},
/*2*/   { {2.0, 0.0, 0.0}, NPZZ, ColorGrey},
/*3*/   { {3.0, 0.0, 0.0}, NPZZ, ColorGrey},
/*4*/   { {4.0, 0.0, 0.0}, NPZZ, ColorGrey},
/*5*/   { {5.0, 0.0, 0.0}, NPZZ, ColorGrey},
/*6*/   { {6.0, 0.0, 0.0}, NPZZ, ColorGrey},
/*7*/   { {7.0, 0.0, 0.0}, NPZZ, ColorGrey},
/*8*/   { {8.0, 0.0, 0.0}, NPZZ, ColorGrey},

/*9*/   { {0.0, 0.0, -1.0}, NPZZ, ColorGrey},
/*10*/  { {1.0, 0.0, -1.0}, NPZZ, ColorGrey},
/*11*/  { {2.0, 0.0, -1.0}, NPZZ, ColorGrey},
/*12*/  { {3.0, 0.0, -1.0}, NPZZ, ColorGrey},
/*13*/  { {4.0, 0.0, -1.0}, NPZZ, ColorGrey},
/*14*/  { {5.0, 0.0, -1.0}, NPZZ, ColorGrey},
/*15*/  { {6.0, 0.0, -1.0}, NPZZ, ColorGrey},
/*16*/  { {7.0, 0.0, -1.0}, NPZZ, ColorGrey},
/*17*/  { {8.0, 0.0, -1.0}, NPZZ, ColorGrey},

/*18*/  { {0.0, 0.0, -2.0}, NPZZ, ColorGrey},
/*19*/  { {1.0, 0.0, -2.0}, NPZZ, ColorGrey},
/*20*/  { {2.0, 0.0, -2.0}, NPZZ, ColorGrey},
/*21*/  { {3.0, 0.0, -2.0}, NPZZ, ColorGrey},
/*22*/  { {4.0, 0.0, -2.0}, NPZZ, ColorGrey},
/*23*/  { {5.0, 0.0, -2.0}, NPZZ, ColorGrey},
/*24*/  { {6.0, 0.0, -2.0}, NPZZ, ColorGrey},
/*25*/  { {7.0, 0.0, -2.0}, NPZZ, ColorGrey},
/*26*/  { {8.0, 0.0, -2.0}, NPZZ, ColorGrey},

/*27*/  { {0.0, 0.0, -3.0}, NPZZ, ColorGrey},
/*28*/  { {1.0, 0.0, -3.0}, NPZZ, ColorGrey},
/*29*/  { {2.0, 0.0, -3.0}, NPZZ, ColorGrey},
/*30*/  { {3.0, 0.0, -3.0}, NPZZ, ColorGrey},
/*31*/  { {4.0, 0.0, -3.0}, NPZZ, ColorGrey},
/*32*/  { {5.0, 0.0, -3.0}, NPZZ, ColorGrey},
/*33*/  { {6.0, 0.0, -3.0}, NPZZ, ColorGrey},
/*34*/  { {7.0, 0.0, -3.0}, NPZZ, ColorGrey},
/*35*/  { {8.0, 0.0, -3.0}, NPZZ, ColorGrey},

/*36*/  { {0.0, 0.0, -4.0}, NPZZ, ColorGrey},
/*37*/  { {1.0, 0.0, -4.0}, NPZZ, ColorGrey},
/*38*/  { {2.0, 0.0, -4.0}, NPZZ, ColorGrey},
/*39*/  { {3.0, 0.0, -4.0}, NPZZ, ColorGrey},
/*40*/  { {4.0, 0.0, -4.0}, NPZZ, ColorGrey},
/*41*/  { {5.0, 0.0, -4.0}, NPZZ, ColorGrey},
/*42*/  { {6.0, 0.0, -4.0}, NPZZ, ColorGrey},
/*43*/  { {7.0, 0.0, -4.0}, NPZZ, ColorGrey},
/*44*/  { {8.0, 0.0, -4.0}, NPZZ, ColorGrey},

/*45*/  { {0.0, 0.0, -5.0}, NPZZ, ColorGrey},
/*46*/  { {1.0, 0.0, -5.0}, NPZZ, ColorGrey},
/*47*/  { {2.0, 0.0, -5.0}, NPZZ, ColorGrey},
/*48*/  { {3.0, 0.0, -5.0}, NPZZ, ColorGrey},
/*49*/  { {4.0, 0.0, -5.0}, NPZZ, ColorGrey},
/*50*/  { {5.0, 0.0, -5.0}, NPZZ, ColorGrey},
/*51*/  { {6.0, 0.0, -5.0}, NPZZ, ColorGrey},
/*52*/  { {7.0, 0.0, -5.0}, NPZZ, ColorGrey},
/*53*/  { {8.0, 0.0, -5.0}, NPZZ, ColorGrey},

/*54*/  { {0.0, 0.0, -6.0}, NPZZ, ColorGrey},
/*55*/  { {1.0, 0.0, -6.0}, NPZZ, ColorGrey},
/*56*/  { {2.0, 0.0, -6.0}, NPZZ, ColorGrey},
/*57*/  { {3.0, 0.0, -6.0}, NPZZ, ColorGrey},
/*58*/  { {4.0, 0.0, -6.0}, NPZZ, ColorGrey},
/*59*/  { {5.0, 0.0, -6.0}, NPZZ, ColorGrey},
/*60*/  { {6.0, 0.0, -6.0}, NPZZ, ColorGrey},
/*61*/  { {7.0, 0.0, -6.0}, NPZZ, ColorGrey},
/*62*/  { {8.0, 0.0, -6.0}, NPZZ, ColorGrey},

/*63*/  { {0.0, 0.0, -7.0}, NPZZ, ColorGrey},
/*64*/  { {1.0, 0.0, -7.0}, NPZZ, ColorGrey},
/*65*/  { {2.0, 0.0, -7.0}, NPZZ, ColorGrey},
/*66*/  { {3.0, 0.0, -7.0}, NPZZ, ColorGrey},
/*67*/  { {4.0, 0.0, -7.0}, NPZZ, ColorGrey},
/*68*/  { {5.0, 0.0, -7.0}, NPZZ, ColorGrey},
/*69*/  { {6.0, 0.0, -7.0}, NPZZ, ColorGrey},
/*70*/  { {7.0, 0.0, -7.0}, NPZZ, ColorGrey},
/*71*/  { {8.0, 0.0, -7.0}, NPZZ, ColorGrey},

/*72*/  { {0.0, 0.0, -8.0}, NPZZ, ColorGrey},
/*73*/  { {1.0, 0.0, -8.0}, NPZZ, ColorGrey},
/*74*/  { {2.0, 0.0, -8.0}, NPZZ, ColorGrey},
/*75*/  { {3.0, 0.0, -8.0}, NPZZ, ColorGrey},
/*76*/  { {4.0, 0.0, -8.0}, NPZZ, ColorGrey},
/*77*/  { {5.0, 0.0, -8.0}, NPZZ, ColorGrey},
/*78*/  { {6.0, 0.0, -8.0}, NPZZ, ColorGrey},
/*79*/  { {7.0, 0.0, -8.0}, NPZZ, ColorGrey},
/*80*/  { {8.0, 0.0, -8.0}, NPZZ, ColorGrey},

/*81*/  { {0.0, 0.0, -9.0}, NPZZ, ColorGrey},
/*82*/  { {1.0, 0.0, -9.0}, NPZZ, ColorGrey},
/*83*/  { {2.0, 0.0, -9.0}, NPZZ, ColorGrey},
/*84*/  { {3.0, 0.0, -9.0}, NPZZ, ColorGrey},
/*85*/  { {4.0, 0.0, -9.0}, NPZZ, ColorGrey},
/*86*/  { {5.0, 0.0, -9.0}, NPZZ, ColorGrey},
/*87*/  { {6.0, 0.0, -9.0}, NPZZ, ColorGrey},
/*88*/  { {7.0, 0.0, -9.0}, NPZZ, ColorGrey},
/*89*/  { {8.0, 0.0, -9.0}, NPZZ, ColorGrey},

/*90*/  { {0.0, 0.0, -10.0}, NPZZ, ColorGrey},
/*91*/  { {1.0, 0.0, -10.0}, NPZZ, ColorGrey},
/*92*/  { {2.0, 0.0, -10.0}, NPZZ, ColorGrey},
/*93*/  { {3.0, 0.0, -10.0}, NPZZ, ColorGrey},
/*94*/  { {4.0, 0.0, -10.0}, NPZZ, ColorGrey},
/*95*/  { {5.0, 0.0, -10.0}, NPZZ, ColorGrey},
/*96*/  { {6.0, 0.0, -10.0}, NPZZ, ColorGrey},
/*97*/  { {7.0, 0.0, -10.0}, NPZZ, ColorGrey},
/*98*/  { {8.0, 0.0, -10.0}, NPZZ, ColorGrey},

/*99*/  { {0.0, 0.0, -11.0}, NPZZ, ColorGrey},
/*100*/ { {1.0, 0.0, -11.0}, NPZZ, ColorGrey},
/*101*/ { {2.0, 0.0, -11.0}, NPZZ, ColorGrey},
/*102*/ { {3.0, 0.0, -11.0}, NPZZ, ColorGrey},
/*103*/ { {4.0, 0.0, -11.0}, NPZZ, ColorGrey},
/*104*/ { {5.0, 0.0, -11.0}, NPZZ, ColorGrey},
/*105*/ { {6.0, 0.0, -11.0}, NPZZ, ColorGrey},
/*106*/ { {7.0, 0.0, -11.0}, NPZZ, ColorGrey},
/*107*/ { {8.0, 0.0, -11.0}, NPZZ, ColorGrey},

/*108*/ { {0.0, 0.0, -12.0}, NPZZ, ColorGrey},
/*109*/ { {1.0, 0.0, -12.0}, NPZZ, ColorGrey},
/*110*/ { {2.0, 0.0, -12.0}, NPZZ, ColorGrey},
/*111*/ { {3.0, 0.0, -12.0}, NPZZ, ColorGrey},
/*112*/ { {4.0, 0.0, -12.0}, NPZZ, ColorGrey},
/*113*/ { {5.0, 0.0, -12.0}, NPZZ, ColorGrey},
/*114*/ { {6.0, 0.0, -12.0}, NPZZ, ColorGrey},
/*115*/ { {7.0, 0.0, -12.0}, NPZZ, ColorGrey},
/*116*/ { {8.0, 0.0, -12.0}, NPZZ, ColorGrey},
// any character not white right front finish

// [0, 116] is 117

// 2973

// any character not white right back start
/*0*/   { {0.0, -2.0, 0.0}, NPZZ, ColorGrey},
/*1*/   { {1.0, -2.0, 0.0}, NPZZ, ColorGrey},
/*2*/   { {2.0, -2.0, 0.0}, NPZZ, ColorGrey},
/*3*/   { {3.0, -2.0, 0.0}, NPZZ, ColorGrey},
/*4*/   { {4.0, -2.0, 0.0}, NPZZ, ColorGrey},
/*5*/   { {5.0, -2.0, 0.0}, NPZZ, ColorGrey},
/*6*/   { {6.0, -2.0, 0.0}, NPZZ, ColorGrey},
/*7*/   { {7.0, -2.0, 0.0}, NPZZ, ColorGrey},
/*8*/   { {8.0, -2.0, 0.0}, NPZZ, ColorGrey},

/*9*/   { {0.0, -2.0, -1.0}, NPZZ, ColorGrey},
/*10*/  { {1.0, -2.0, -1.0}, NPZZ, ColorGrey},
/*11*/  { {2.0, -2.0, -1.0}, NPZZ, ColorGrey},
/*12*/  { {3.0, -2.0, -1.0}, NPZZ, ColorGrey},
/*13*/  { {4.0, -2.0, -1.0}, NPZZ, ColorGrey},
/*14*/  { {5.0, -2.0, -1.0}, NPZZ, ColorGrey},
/*15*/  { {6.0, -2.0, -1.0}, NPZZ, ColorGrey},
/*16*/  { {7.0, -2.0, -1.0}, NPZZ, ColorGrey},
/*17*/  { {8.0, -2.0, -1.0}, NPZZ, ColorGrey},

/*18*/  { {0.0, -2.0, -2.0}, NPZZ, ColorGrey},
/*19*/  { {1.0, -2.0, -2.0}, NPZZ, ColorGrey},
/*20*/  { {2.0, -2.0, -2.0}, NPZZ, ColorGrey},
/*21*/  { {3.0, -2.0, -2.0}, NPZZ, ColorGrey},
/*22*/  { {4.0, -2.0, -2.0}, NPZZ, ColorGrey},
/*23*/  { {5.0, -2.0, -2.0}, NPZZ, ColorGrey},
/*24*/  { {6.0, -2.0, -2.0}, NPZZ, ColorGrey},
/*25*/  { {7.0, -2.0, -2.0}, NPZZ, ColorGrey},
/*26*/  { {8.0, -2.0, -2.0}, NPZZ, ColorGrey},

/*27*/  { {0.0, -2.0, -3.0}, NPZZ, ColorGrey},
/*28*/  { {1.0, -2.0, -3.0}, NPZZ, ColorGrey},
/*29*/  { {2.0, -2.0, -3.0}, NPZZ, ColorGrey},
/*30*/  { {3.0, -2.0, -3.0}, NPZZ, ColorGrey},
/*31*/  { {4.0, -2.0, -3.0}, NPZZ, ColorGrey},
/*32*/  { {5.0, -2.0, -3.0}, NPZZ, ColorGrey},
/*33*/  { {6.0, -2.0, -3.0}, NPZZ, ColorGrey},
/*34*/  { {7.0, -2.0, -3.0}, NPZZ, ColorGrey},
/*35*/  { {8.0, -2.0, -3.0}, NPZZ, ColorGrey},

/*36*/  { {0.0, -2.0, -4.0}, NPZZ, ColorGrey},
/*37*/  { {1.0, -2.0, -4.0}, NPZZ, ColorGrey},
/*38*/  { {2.0, -2.0, -4.0}, NPZZ, ColorGrey},
/*39*/  { {3.0, -2.0, -4.0}, NPZZ, ColorGrey},
/*40*/  { {4.0, -2.0, -4.0}, NPZZ, ColorGrey},
/*41*/  { {5.0, -2.0, -4.0}, NPZZ, ColorGrey},
/*42*/  { {6.0, -2.0, -4.0}, NPZZ, ColorGrey},
/*43*/  { {7.0, -2.0, -4.0}, NPZZ, ColorGrey},
/*44*/  { {8.0, -2.0, -4.0}, NPZZ, ColorGrey},

/*45*/  { {0.0, -2.0, -5.0}, NPZZ, ColorGrey},
/*46*/  { {1.0, -2.0, -5.0}, NPZZ, ColorGrey},
/*47*/  { {2.0, -2.0, -5.0}, NPZZ, ColorGrey},
/*48*/  { {3.0, -2.0, -5.0}, NPZZ, ColorGrey},
/*49*/  { {4.0, -2.0, -5.0}, NPZZ, ColorGrey},
/*50*/  { {5.0, -2.0, -5.0}, NPZZ, ColorGrey},
/*51*/  { {6.0, -2.0, -5.0}, NPZZ, ColorGrey},
/*52*/  { {7.0, -2.0, -5.0}, NPZZ, ColorGrey},
/*53*/  { {8.0, -2.0, -5.0}, NPZZ, ColorGrey},

/*54*/  { {0.0, -2.0, -6.0}, NPZZ, ColorGrey},
/*55*/  { {1.0, -2.0, -6.0}, NPZZ, ColorGrey},
/*56*/  { {2.0, -2.0, -6.0}, NPZZ, ColorGrey},
/*57*/  { {3.0, -2.0, -6.0}, NPZZ, ColorGrey},
/*58*/  { {4.0, -2.0, -6.0}, NPZZ, ColorGrey},
/*59*/  { {5.0, -2.0, -6.0}, NPZZ, ColorGrey},
/*60*/  { {6.0, -2.0, -6.0}, NPZZ, ColorGrey},
/*61*/  { {7.0, -2.0, -6.0}, NPZZ, ColorGrey},
/*62*/  { {8.0, -2.0, -6.0}, NPZZ, ColorGrey},

/*63*/  { {0.0, -2.0, -7.0}, NPZZ, ColorGrey},
/*64*/  { {1.0, -2.0, -7.0}, NPZZ, ColorGrey},
/*65*/  { {2.0, -2.0, -7.0}, NPZZ, ColorGrey},
/*66*/  { {3.0, -2.0, -7.0}, NPZZ, ColorGrey},
/*67*/  { {4.0, -2.0, -7.0}, NPZZ, ColorGrey},
/*68*/  { {5.0, -2.0, -7.0}, NPZZ, ColorGrey},
/*69*/  { {6.0, -2.0, -7.0}, NPZZ, ColorGrey},
/*70*/  { {7.0, -2.0, -7.0}, NPZZ, ColorGrey},
/*71*/  { {8.0, -2.0, -7.0}, NPZZ, ColorGrey},

/*72*/  { {0.0, -2.0, -8.0}, NPZZ, ColorGrey},
/*73*/  { {1.0, -2.0, -8.0}, NPZZ, ColorGrey},
/*74*/  { {2.0, -2.0, -8.0}, NPZZ, ColorGrey},
/*75*/  { {3.0, -2.0, -8.0}, NPZZ, ColorGrey},
/*76*/  { {4.0, -2.0, -8.0}, NPZZ, ColorGrey},
/*77*/  { {5.0, -2.0, -8.0}, NPZZ, ColorGrey},
/*78*/  { {6.0, -2.0, -8.0}, NPZZ, ColorGrey},
/*79*/  { {7.0, -2.0, -8.0}, NPZZ, ColorGrey},
/*80*/  { {8.0, -2.0, -8.0}, NPZZ, ColorGrey},

/*81*/  { {0.0, -2.0, -9.0}, NPZZ, ColorGrey},
/*82*/  { {1.0, -2.0, -9.0}, NPZZ, ColorGrey},
/*83*/  { {2.0, -2.0, -9.0}, NPZZ, ColorGrey},
/*84*/  { {3.0, -2.0, -9.0}, NPZZ, ColorGrey},
/*85*/  { {4.0, -2.0, -9.0}, NPZZ, ColorGrey},
/*86*/  { {5.0, -2.0, -9.0}, NPZZ, ColorGrey},
/*87*/  { {6.0, -2.0, -9.0}, NPZZ, ColorGrey},
/*88*/  { {7.0, -2.0, -9.0}, NPZZ, ColorGrey},
/*89*/  { {8.0, -2.0, -9.0}, NPZZ, ColorGrey},

/*90*/  { {0.0, -2.0, -10.0}, NPZZ, ColorGrey},
/*91*/  { {1.0, -2.0, -10.0}, NPZZ, ColorGrey},
/*92*/  { {2.0, -2.0, -10.0}, NPZZ, ColorGrey},
/*93*/  { {3.0, -2.0, -10.0}, NPZZ, ColorGrey},
/*94*/  { {4.0, -2.0, -10.0}, NPZZ, ColorGrey},
/*95*/  { {5.0, -2.0, -10.0}, NPZZ, ColorGrey},
/*96*/  { {6.0, -2.0, -10.0}, NPZZ, ColorGrey},
/*97*/  { {7.0, -2.0, -10.0}, NPZZ, ColorGrey},
/*98*/  { {8.0, -2.0, -10.0}, NPZZ, ColorGrey},

/*99*/  { {0.0, -2.0, -11.0}, NPZZ, ColorGrey},
/*100*/ { {1.0, -2.0, -11.0}, NPZZ, ColorGrey},
/*101*/ { {2.0, -2.0, -11.0}, NPZZ, ColorGrey},
/*102*/ { {3.0, -2.0, -11.0}, NPZZ, ColorGrey},
/*103*/ { {4.0, -2.0, -11.0}, NPZZ, ColorGrey},
/*104*/ { {5.0, -2.0, -11.0}, NPZZ, ColorGrey},
/*105*/ { {6.0, -2.0, -11.0}, NPZZ, ColorGrey},
/*106*/ { {7.0, -2.0, -11.0}, NPZZ, ColorGrey},
/*107*/ { {8.0, -2.0, -11.0}, NPZZ, ColorGrey},

/*108*/ { {0.0, -2.0, -12.0}, NPZZ, ColorGrey},
/*109*/ { {1.0, -2.0, -12.0}, NPZZ, ColorGrey},
/*110*/ { {2.0, -2.0, -12.0}, NPZZ, ColorGrey},
/*111*/ { {3.0, -2.0, -12.0}, NPZZ, ColorGrey},
/*112*/ { {4.0, -2.0, -12.0}, NPZZ, ColorGrey},
/*113*/ { {5.0, -2.0, -12.0}, NPZZ, ColorGrey},
/*114*/ { {6.0, -2.0, -12.0}, NPZZ, ColorGrey},
/*115*/ { {7.0, -2.0, -12.0}, NPZZ, ColorGrey},
/*116*/ { {8.0, -2.0, -12.0}, NPZZ, ColorGrey},
// any character not white right back finish

// [0, 116] is 117

// 3090

// any character not white quad middle right start
/*0*/   { {1.0, -1.0, -0.5}, NPZZ, ColorGrey},
/*1*/   { {2.0, -1.0, -0.5}, NPZZ, ColorGrey},
/*2*/   { {3.0, -1.0, -0.5}, NPZZ, ColorGrey},
/*3*/   { {4.0, -1.0, -0.5}, NPZZ, ColorGrey},
/*4*/   { {5.0, -1.0, -0.5}, NPZZ, ColorGrey},
/*5*/   { {6.0, -1.0, -0.5}, NPZZ, ColorGrey},
/*6*/   { {7.0, -1.0, -0.5}, NPZZ, ColorGrey},
/*7*/   { {8.0, -1.0, -0.5}, NPZZ, ColorGrey},

/*8*/   { {1.0, -1.0, -1.5}, NPZZ, ColorGrey},
/*9*/   { {2.0, -1.0, -1.5}, NPZZ, ColorGrey},
/*10*/  { {3.0, -1.0, -1.5}, NPZZ, ColorGrey},
/*11*/  { {4.0, -1.0, -1.5}, NPZZ, ColorGrey},
/*12*/  { {5.0, -1.0, -1.5}, NPZZ, ColorGrey},
/*13*/  { {6.0, -1.0, -1.5}, NPZZ, ColorGrey},
/*14*/  { {7.0, -1.0, -1.5}, NPZZ, ColorGrey},
/*15*/  { {8.0, -1.0, -1.5}, NPZZ, ColorGrey},

/*16*/  { {1.0, -1.0, -2.5}, NPZZ, ColorGrey},
/*17*/  { {2.0, -1.0, -2.5}, NPZZ, ColorGrey},
/*18*/  { {3.0, -1.0, -2.5}, NPZZ, ColorGrey},
/*19*/  { {4.0, -1.0, -2.5}, NPZZ, ColorGrey},
/*20*/  { {5.0, -1.0, -2.5}, NPZZ, ColorGrey},
/*21*/  { {6.0, -1.0, -2.5}, NPZZ, ColorGrey},
/*22*/  { {7.0, -1.0, -2.5}, NPZZ, ColorGrey},
/*23*/  { {8.0, -1.0, -2.5}, NPZZ, ColorGrey},

/*24*/  { {1.0, -1.0, -3.5}, NPZZ, ColorGrey},
/*25*/  { {2.0, -1.0, -3.5}, NPZZ, ColorGrey},
/*26*/  { {3.0, -1.0, -3.5}, NPZZ, ColorGrey},
/*27*/  { {4.0, -1.0, -3.5}, NPZZ, ColorGrey},
/*28*/  { {5.0, -1.0, -3.5}, NPZZ, ColorGrey},
/*29*/  { {6.0, -1.0, -3.5}, NPZZ, ColorGrey},
/*30*/  { {7.0, -1.0, -3.5}, NPZZ, ColorGrey},
/*31*/  { {8.0, -1.0, -3.5}, NPZZ, ColorGrey},

/*32*/  { {1.0, -1.0, -4.5}, NPZZ, ColorGrey},
/*33*/  { {2.0, -1.0, -4.5}, NPZZ, ColorGrey},
/*34*/  { {3.0, -1.0, -4.5}, NPZZ, ColorGrey},
/*35*/  { {4.0, -1.0, -4.5}, NPZZ, ColorGrey},
/*36*/  { {5.0, -1.0, -4.5}, NPZZ, ColorGrey},
/*37*/  { {6.0, -1.0, -4.5}, NPZZ, ColorGrey},
/*38*/  { {7.0, -1.0, -4.5}, NPZZ, ColorGrey},
/*39*/  { {8.0, -1.0, -4.5}, NPZZ, ColorGrey},

/*40*/  { {1.0, -1.0, -5.5}, NPZZ, ColorGrey},
/*41*/  { {2.0, -1.0, -5.5}, NPZZ, ColorGrey},
/*42*/  { {3.0, -1.0, -5.5}, NPZZ, ColorGrey},
/*43*/  { {4.0, -1.0, -5.5}, NPZZ, ColorGrey},
/*44*/  { {5.0, -1.0, -5.5}, NPZZ, ColorGrey},
/*45*/  { {6.0, -1.0, -5.5}, NPZZ, ColorGrey},
/*46*/  { {7.0, -1.0, -5.5}, NPZZ, ColorGrey},
/*47*/  { {8.0, -1.0, -5.5}, NPZZ, ColorGrey},

/*48*/  { {1.0, -1.0, -6.5}, NPZZ, ColorGrey},
/*49*/  { {2.0, -1.0, -6.5}, NPZZ, ColorGrey},
/*50*/  { {3.0, -1.0, -6.5}, NPZZ, ColorGrey},
/*51*/  { {4.0, -1.0, -6.5}, NPZZ, ColorGrey},
/*52*/  { {5.0, -1.0, -6.5}, NPZZ, ColorGrey},
/*53*/  { {6.0, -1.0, -6.5}, NPZZ, ColorGrey},
/*54*/  { {7.0, -1.0, -6.5}, NPZZ, ColorGrey},
/*55*/  { {8.0, -1.0, -6.5}, NPZZ, ColorGrey},

/*56*/  { {1.0, -1.0, -7.5}, NPZZ, ColorGrey},
/*57*/  { {2.0, -1.0, -7.5}, NPZZ, ColorGrey},
/*58*/  { {3.0, -1.0, -7.5}, NPZZ, ColorGrey},
/*59*/  { {4.0, -1.0, -7.5}, NPZZ, ColorGrey},
/*60*/  { {5.0, -1.0, -7.5}, NPZZ, ColorGrey},
/*61*/  { {6.0, -1.0, -7.5}, NPZZ, ColorGrey},
/*62*/  { {7.0, -1.0, -7.5}, NPZZ, ColorGrey},
/*63*/  { {8.0, -1.0, -7.5}, NPZZ, ColorGrey},

/*64*/  { {1.0, -1.0, -8.5}, NPZZ, ColorGrey},
/*65*/  { {2.0, -1.0, -8.5}, NPZZ, ColorGrey},
/*66*/  { {3.0, -1.0, -8.5}, NPZZ, ColorGrey},
/*67*/  { {4.0, -1.0, -8.5}, NPZZ, ColorGrey},
/*68*/  { {5.0, -1.0, -8.5}, NPZZ, ColorGrey},
/*69*/  { {6.0, -1.0, -8.5}, NPZZ, ColorGrey},
/*70*/  { {7.0, -1.0, -8.5}, NPZZ, ColorGrey},
/*71*/  { {8.0, -1.0, -8.5}, NPZZ, ColorGrey},

/*72*/  { {1.0, -1.0, -9.5}, NPZZ, ColorGrey},
/*73*/  { {2.0, -1.0, -9.5}, NPZZ, ColorGrey},
/*74*/  { {3.0, -1.0, -9.5}, NPZZ, ColorGrey},
/*75*/  { {4.0, -1.0, -9.5}, NPZZ, ColorGrey},
/*76*/  { {5.0, -1.0, -9.5}, NPZZ, ColorGrey},
/*77*/  { {6.0, -1.0, -9.5}, NPZZ, ColorGrey},
/*78*/  { {7.0, -1.0, -9.5}, NPZZ, ColorGrey},
/*79*/  { {8.0, -1.0, -9.5}, NPZZ, ColorGrey},

/*80*/  { {1.0, -1.0, -10.5}, NPZZ, ColorGrey},
/*81*/  { {2.0, -1.0, -10.5}, NPZZ, ColorGrey},
/*82*/  { {3.0, -1.0, -10.5}, NPZZ, ColorGrey},
/*83*/  { {4.0, -1.0, -10.5}, NPZZ, ColorGrey},
/*84*/  { {5.0, -1.0, -10.5}, NPZZ, ColorGrey},
/*85*/  { {6.0, -1.0, -10.5}, NPZZ, ColorGrey},
/*86*/  { {7.0, -1.0, -10.5}, NPZZ, ColorGrey},
/*87*/  { {8.0, -1.0, -10.5}, NPZZ, ColorGrey},

/*88*/  { {1.0, -1.0, -11.5}, NPZZ, ColorGrey},
/*89*/  { {2.0, -1.0, -11.5}, NPZZ, ColorGrey},
/*90*/  { {3.0, -1.0, -11.5}, NPZZ, ColorGrey},
/*91*/  { {4.0, -1.0, -11.5}, NPZZ, ColorGrey},
/*92*/  { {5.0, -1.0, -11.5}, NPZZ, ColorGrey},
/*93*/  { {6.0, -1.0, -11.5}, NPZZ, ColorGrey},
/*94*/  { {7.0, -1.0, -11.5}, NPZZ, ColorGrey},
/*95*/  { {8.0, -1.0, -11.5}, NPZZ, ColorGrey},
// any character not white quad middle right finish

// [0, 95] is 96

// 3186

// any character not white top front start
/*0*/   { {0.0, 0.0, 0.0}, NZZN, ColorGrey},
/*1*/   { {1.0, 0.0, 0.0}, NZZN, ColorGrey},
/*2*/   { {2.0, 0.0, 0.0}, NZZN, ColorGrey},
/*3*/   { {3.0, 0.0, 0.0}, NZZN, ColorGrey},
/*4*/   { {4.0, 0.0, 0.0}, NZZN, ColorGrey},
/*5*/   { {5.0, 0.0, 0.0}, NZZN, ColorGrey},
/*6*/   { {6.0, 0.0, 0.0}, NZZN, ColorGrey},
/*7*/   { {7.0, 0.0, 0.0}, NZZN, ColorGrey},
/*8*/   { {8.0, 0.0, 0.0}, NZZN, ColorGrey},

/*9*/   { {0.0, 0.0, -1.0}, NZZN, ColorGrey},
/*10*/  { {1.0, 0.0, -1.0}, NZZN, ColorGrey},
/*11*/  { {2.0, 0.0, -1.0}, NZZN, ColorGrey},
/*12*/  { {3.0, 0.0, -1.0}, NZZN, ColorGrey},
/*13*/  { {4.0, 0.0, -1.0}, NZZN, ColorGrey},
/*14*/  { {5.0, 0.0, -1.0}, NZZN, ColorGrey},
/*15*/  { {6.0, 0.0, -1.0}, NZZN, ColorGrey},
/*16*/  { {7.0, 0.0, -1.0}, NZZN, ColorGrey},
/*17*/  { {8.0, 0.0, -1.0}, NZZN, ColorGrey},

/*18*/  { {0.0, 0.0, -2.0}, NZZN, ColorGrey},
/*19*/  { {1.0, 0.0, -2.0}, NZZN, ColorGrey},
/*20*/  { {2.0, 0.0, -2.0}, NZZN, ColorGrey},
/*21*/  { {3.0, 0.0, -2.0}, NZZN, ColorGrey},
/*22*/  { {4.0, 0.0, -2.0}, NZZN, ColorGrey},
/*23*/  { {5.0, 0.0, -2.0}, NZZN, ColorGrey},
/*24*/  { {6.0, 0.0, -2.0}, NZZN, ColorGrey},
/*25*/  { {7.0, 0.0, -2.0}, NZZN, ColorGrey},
/*26*/  { {8.0, 0.0, -2.0}, NZZN, ColorGrey},

/*27*/  { {0.0, 0.0, -3.0}, NZZN, ColorGrey},
/*28*/  { {1.0, 0.0, -3.0}, NZZN, ColorGrey},
/*29*/  { {2.0, 0.0, -3.0}, NZZN, ColorGrey},
/*30*/  { {3.0, 0.0, -3.0}, NZZN, ColorGrey},
/*31*/  { {4.0, 0.0, -3.0}, NZZN, ColorGrey},
/*32*/  { {5.0, 0.0, -3.0}, NZZN, ColorGrey},
/*33*/  { {6.0, 0.0, -3.0}, NZZN, ColorGrey},
/*34*/  { {7.0, 0.0, -3.0}, NZZN, ColorGrey},
/*35*/  { {8.0, 0.0, -3.0}, NZZN, ColorGrey},

/*36*/  { {0.0, 0.0, -4.0}, NZZN, ColorGrey},
/*37*/  { {1.0, 0.0, -4.0}, NZZN, ColorGrey},
/*38*/  { {2.0, 0.0, -4.0}, NZZN, ColorGrey},
/*39*/  { {3.0, 0.0, -4.0}, NZZN, ColorGrey},
/*40*/  { {4.0, 0.0, -4.0}, NZZN, ColorGrey},
/*41*/  { {5.0, 0.0, -4.0}, NZZN, ColorGrey},
/*42*/  { {6.0, 0.0, -4.0}, NZZN, ColorGrey},
/*43*/  { {7.0, 0.0, -4.0}, NZZN, ColorGrey},
/*44*/  { {8.0, 0.0, -4.0}, NZZN, ColorGrey},

/*45*/  { {0.0, 0.0, -5.0}, NZZN, ColorGrey},
/*46*/  { {1.0, 0.0, -5.0}, NZZN, ColorGrey},
/*47*/  { {2.0, 0.0, -5.0}, NZZN, ColorGrey},
/*48*/  { {3.0, 0.0, -5.0}, NZZN, ColorGrey},
/*49*/  { {4.0, 0.0, -5.0}, NZZN, ColorGrey},
/*50*/  { {5.0, 0.0, -5.0}, NZZN, ColorGrey},
/*51*/  { {6.0, 0.0, -5.0}, NZZN, ColorGrey},
/*52*/  { {7.0, 0.0, -5.0}, NZZN, ColorGrey},
/*53*/  { {8.0, 0.0, -5.0}, NZZN, ColorGrey},

/*54*/  { {0.0, 0.0, -6.0}, NZZN, ColorGrey},
/*55*/  { {1.0, 0.0, -6.0}, NZZN, ColorGrey},
/*56*/  { {2.0, 0.0, -6.0}, NZZN, ColorGrey},
/*57*/  { {3.0, 0.0, -6.0}, NZZN, ColorGrey},
/*58*/  { {4.0, 0.0, -6.0}, NZZN, ColorGrey},
/*59*/  { {5.0, 0.0, -6.0}, NZZN, ColorGrey},
/*60*/  { {6.0, 0.0, -6.0}, NZZN, ColorGrey},
/*61*/  { {7.0, 0.0, -6.0}, NZZN, ColorGrey},
/*62*/  { {8.0, 0.0, -6.0}, NZZN, ColorGrey},

/*63*/  { {0.0, 0.0, -7.0}, NZZN, ColorGrey},
/*64*/  { {1.0, 0.0, -7.0}, NZZN, ColorGrey},
/*65*/  { {2.0, 0.0, -7.0}, NZZN, ColorGrey},
/*66*/  { {3.0, 0.0, -7.0}, NZZN, ColorGrey},
/*67*/  { {4.0, 0.0, -7.0}, NZZN, ColorGrey},
/*68*/  { {5.0, 0.0, -7.0}, NZZN, ColorGrey},
/*69*/  { {6.0, 0.0, -7.0}, NZZN, ColorGrey},
/*70*/  { {7.0, 0.0, -7.0}, NZZN, ColorGrey},
/*71*/  { {8.0, 0.0, -7.0}, NZZN, ColorGrey},

/*72*/  { {0.0, 0.0, -8.0}, NZZN, ColorGrey},
/*73*/  { {1.0, 0.0, -8.0}, NZZN, ColorGrey},
/*74*/  { {2.0, 0.0, -8.0}, NZZN, ColorGrey},
/*75*/  { {3.0, 0.0, -8.0}, NZZN, ColorGrey},
/*76*/  { {4.0, 0.0, -8.0}, NZZN, ColorGrey},
/*77*/  { {5.0, 0.0, -8.0}, NZZN, ColorGrey},
/*78*/  { {6.0, 0.0, -8.0}, NZZN, ColorGrey},
/*79*/  { {7.0, 0.0, -8.0}, NZZN, ColorGrey},
/*80*/  { {8.0, 0.0, -8.0}, NZZN, ColorGrey},

/*81*/  { {0.0, 0.0, -9.0}, NZZN, ColorGrey},
/*82*/  { {1.0, 0.0, -9.0}, NZZN, ColorGrey},
/*83*/  { {2.0, 0.0, -9.0}, NZZN, ColorGrey},
/*84*/  { {3.0, 0.0, -9.0}, NZZN, ColorGrey},
/*85*/  { {4.0, 0.0, -9.0}, NZZN, ColorGrey},
/*86*/  { {5.0, 0.0, -9.0}, NZZN, ColorGrey},
/*87*/  { {6.0, 0.0, -9.0}, NZZN, ColorGrey},
/*88*/  { {7.0, 0.0, -9.0}, NZZN, ColorGrey},
/*89*/  { {8.0, 0.0, -9.0}, NZZN, ColorGrey},

/*90*/  { {0.0, 0.0, -10.0}, NZZN, ColorGrey},
/*91*/  { {1.0, 0.0, -10.0}, NZZN, ColorGrey},
/*92*/  { {2.0, 0.0, -10.0}, NZZN, ColorGrey},
/*93*/  { {3.0, 0.0, -10.0}, NZZN, ColorGrey},
/*94*/  { {4.0, 0.0, -10.0}, NZZN, ColorGrey},
/*95*/  { {5.0, 0.0, -10.0}, NZZN, ColorGrey},
/*96*/  { {6.0, 0.0, -10.0}, NZZN, ColorGrey},
/*97*/  { {7.0, 0.0, -10.0}, NZZN, ColorGrey},
/*98*/  { {8.0, 0.0, -10.0}, NZZN, ColorGrey},

/*99*/  { {0.0, 0.0, -11.0}, NZZN, ColorGrey},
/*100*/ { {1.0, 0.0, -11.0}, NZZN, ColorGrey},
/*101*/ { {2.0, 0.0, -11.0}, NZZN, ColorGrey},
/*102*/ { {3.0, 0.0, -11.0}, NZZN, ColorGrey},
/*103*/ { {4.0, 0.0, -11.0}, NZZN, ColorGrey},
/*104*/ { {5.0, 0.0, -11.0}, NZZN, ColorGrey},
/*105*/ { {6.0, 0.0, -11.0}, NZZN, ColorGrey},
/*106*/ { {7.0, 0.0, -11.0}, NZZN, ColorGrey},
/*107*/ { {8.0, 0.0, -11.0}, NZZN, ColorGrey},

/*108*/ { {0.0, 0.0, -12.0}, NZZN, ColorGrey},
/*109*/ { {1.0, 0.0, -12.0}, NZZN, ColorGrey},
/*110*/ { {2.0, 0.0, -12.0}, NZZN, ColorGrey},
/*111*/ { {3.0, 0.0, -12.0}, NZZN, ColorGrey},
/*112*/ { {4.0, 0.0, -12.0}, NZZN, ColorGrey},
/*113*/ { {5.0, 0.0, -12.0}, NZZN, ColorGrey},
/*114*/ { {6.0, 0.0, -12.0}, NZZN, ColorGrey},
/*115*/ { {7.0, 0.0, -12.0}, NZZN, ColorGrey},
/*116*/ { {8.0, 0.0, -12.0}, NZZN, ColorGrey},
// any character not white top front finish

// [0, 116] is 117

// 3303

// any character not white top back start
/*0*/   { {0.0, -2.0, 0.0}, NZZN, ColorGrey},
/*1*/   { {1.0, -2.0, 0.0}, NZZN, ColorGrey},
/*2*/   { {2.0, -2.0, 0.0}, NZZN, ColorGrey},
/*3*/   { {3.0, -2.0, 0.0}, NZZN, ColorGrey},
/*4*/   { {4.0, -2.0, 0.0}, NZZN, ColorGrey},
/*5*/   { {5.0, -2.0, 0.0}, NZZN, ColorGrey},
/*6*/   { {6.0, -2.0, 0.0}, NZZN, ColorGrey},
/*7*/   { {7.0, -2.0, 0.0}, NZZN, ColorGrey},
/*8*/   { {8.0, -2.0, 0.0}, NZZN, ColorGrey},

/*9*/   { {0.0, -2.0, -1.0}, NZZN, ColorGrey},
/*10*/  { {1.0, -2.0, -1.0}, NZZN, ColorGrey},
/*11*/  { {2.0, -2.0, -1.0}, NZZN, ColorGrey},
/*12*/  { {3.0, -2.0, -1.0}, NZZN, ColorGrey},
/*13*/  { {4.0, -2.0, -1.0}, NZZN, ColorGrey},
/*14*/  { {5.0, -2.0, -1.0}, NZZN, ColorGrey},
/*15*/  { {6.0, -2.0, -1.0}, NZZN, ColorGrey},
/*16*/  { {7.0, -2.0, -1.0}, NZZN, ColorGrey},
/*17*/  { {8.0, -2.0, -1.0}, NZZN, ColorGrey},

/*18*/  { {0.0, -2.0, -2.0}, NZZN, ColorGrey},
/*19*/  { {1.0, -2.0, -2.0}, NZZN, ColorGrey},
/*20*/  { {2.0, -2.0, -2.0}, NZZN, ColorGrey},
/*21*/  { {3.0, -2.0, -2.0}, NZZN, ColorGrey},
/*22*/  { {4.0, -2.0, -2.0}, NZZN, ColorGrey},
/*23*/  { {5.0, -2.0, -2.0}, NZZN, ColorGrey},
/*24*/  { {6.0, -2.0, -2.0}, NZZN, ColorGrey},
/*25*/  { {7.0, -2.0, -2.0}, NZZN, ColorGrey},
/*26*/  { {8.0, -2.0, -2.0}, NZZN, ColorGrey},

/*27*/  { {0.0, -2.0, -3.0}, NZZN, ColorGrey},
/*28*/  { {1.0, -2.0, -3.0}, NZZN, ColorGrey},
/*29*/  { {2.0, -2.0, -3.0}, NZZN, ColorGrey},
/*30*/  { {3.0, -2.0, -3.0}, NZZN, ColorGrey},
/*31*/  { {4.0, -2.0, -3.0}, NZZN, ColorGrey},
/*32*/  { {5.0, -2.0, -3.0}, NZZN, ColorGrey},
/*33*/  { {6.0, -2.0, -3.0}, NZZN, ColorGrey},
/*34*/  { {7.0, -2.0, -3.0}, NZZN, ColorGrey},
/*35*/  { {8.0, -2.0, -3.0}, NZZN, ColorGrey},

/*36*/  { {0.0, -2.0, -4.0}, NZZN, ColorGrey},
/*37*/  { {1.0, -2.0, -4.0}, NZZN, ColorGrey},
/*38*/  { {2.0, -2.0, -4.0}, NZZN, ColorGrey},
/*39*/  { {3.0, -2.0, -4.0}, NZZN, ColorGrey},
/*40*/  { {4.0, -2.0, -4.0}, NZZN, ColorGrey},
/*41*/  { {5.0, -2.0, -4.0}, NZZN, ColorGrey},
/*42*/  { {6.0, -2.0, -4.0}, NZZN, ColorGrey},
/*43*/  { {7.0, -2.0, -4.0}, NZZN, ColorGrey},
/*44*/  { {8.0, -2.0, -4.0}, NZZN, ColorGrey},

/*45*/  { {0.0, -2.0, -5.0}, NZZN, ColorGrey},
/*46*/  { {1.0, -2.0, -5.0}, NZZN, ColorGrey},
/*47*/  { {2.0, -2.0, -5.0}, NZZN, ColorGrey},
/*48*/  { {3.0, -2.0, -5.0}, NZZN, ColorGrey},
/*49*/  { {4.0, -2.0, -5.0}, NZZN, ColorGrey},
/*50*/  { {5.0, -2.0, -5.0}, NZZN, ColorGrey},
/*51*/  { {6.0, -2.0, -5.0}, NZZN, ColorGrey},
/*52*/  { {7.0, -2.0, -5.0}, NZZN, ColorGrey},
/*53*/  { {8.0, -2.0, -5.0}, NZZN, ColorGrey},

/*54*/  { {0.0, -2.0, -6.0}, NZZN, ColorGrey},
/*55*/  { {1.0, -2.0, -6.0}, NZZN, ColorGrey},
/*56*/  { {2.0, -2.0, -6.0}, NZZN, ColorGrey},
/*57*/  { {3.0, -2.0, -6.0}, NZZN, ColorGrey},
/*58*/  { {4.0, -2.0, -6.0}, NZZN, ColorGrey},
/*59*/  { {5.0, -2.0, -6.0}, NZZN, ColorGrey},
/*60*/  { {6.0, -2.0, -6.0}, NZZN, ColorGrey},
/*61*/  { {7.0, -2.0, -6.0}, NZZN, ColorGrey},
/*62*/  { {8.0, -2.0, -6.0}, NZZN, ColorGrey},

/*63*/  { {0.0, -2.0, -7.0}, NZZN, ColorGrey},
/*64*/  { {1.0, -2.0, -7.0}, NZZN, ColorGrey},
/*65*/  { {2.0, -2.0, -7.0}, NZZN, ColorGrey},
/*66*/  { {3.0, -2.0, -7.0}, NZZN, ColorGrey},
/*67*/  { {4.0, -2.0, -7.0}, NZZN, ColorGrey},
/*68*/  { {5.0, -2.0, -7.0}, NZZN, ColorGrey},
/*69*/  { {6.0, -2.0, -7.0}, NZZN, ColorGrey},
/*70*/  { {7.0, -2.0, -7.0}, NZZN, ColorGrey},
/*71*/  { {8.0, -2.0, -7.0}, NZZN, ColorGrey},

/*72*/  { {0.0, -2.0, -8.0}, NZZN, ColorGrey},
/*73*/  { {1.0, -2.0, -8.0}, NZZN, ColorGrey},
/*74*/  { {2.0, -2.0, -8.0}, NZZN, ColorGrey},
/*75*/  { {3.0, -2.0, -8.0}, NZZN, ColorGrey},
/*76*/  { {4.0, -2.0, -8.0}, NZZN, ColorGrey},
/*77*/  { {5.0, -2.0, -8.0}, NZZN, ColorGrey},
/*78*/  { {6.0, -2.0, -8.0}, NZZN, ColorGrey},
/*79*/  { {7.0, -2.0, -8.0}, NZZN, ColorGrey},
/*80*/  { {8.0, -2.0, -8.0}, NZZN, ColorGrey},

/*81*/  { {0.0, -2.0, -9.0}, NZZN, ColorGrey},
/*82*/  { {1.0, -2.0, -9.0}, NZZN, ColorGrey},
/*83*/  { {2.0, -2.0, -9.0}, NZZN, ColorGrey},
/*84*/  { {3.0, -2.0, -9.0}, NZZN, ColorGrey},
/*85*/  { {4.0, -2.0, -9.0}, NZZN, ColorGrey},
/*86*/  { {5.0, -2.0, -9.0}, NZZN, ColorGrey},
/*87*/  { {6.0, -2.0, -9.0}, NZZN, ColorGrey},
/*88*/  { {7.0, -2.0, -9.0}, NZZN, ColorGrey},
/*89*/  { {8.0, -2.0, -9.0}, NZZN, ColorGrey},

/*90*/  { {0.0, -2.0, -10.0}, NZZN, ColorGrey},
/*91*/  { {1.0, -2.0, -10.0}, NZZN, ColorGrey},
/*92*/  { {2.0, -2.0, -10.0}, NZZN, ColorGrey},
/*93*/  { {3.0, -2.0, -10.0}, NZZN, ColorGrey},
/*94*/  { {4.0, -2.0, -10.0}, NZZN, ColorGrey},
/*95*/  { {5.0, -2.0, -10.0}, NZZN, ColorGrey},
/*96*/  { {6.0, -2.0, -10.0}, NZZN, ColorGrey},
/*97*/  { {7.0, -2.0, -10.0}, NZZN, ColorGrey},
/*98*/  { {8.0, -2.0, -10.0}, NZZN, ColorGrey},

/*99*/  { {0.0, -2.0, -11.0}, NZZN, ColorGrey},
/*100*/ { {1.0, -2.0, -11.0}, NZZN, ColorGrey},
/*101*/ { {2.0, -2.0, -11.0}, NZZN, ColorGrey},
/*102*/ { {3.0, -2.0, -11.0}, NZZN, ColorGrey},
/*103*/ { {4.0, -2.0, -11.0}, NZZN, ColorGrey},
/*104*/ { {5.0, -2.0, -11.0}, NZZN, ColorGrey},
/*105*/ { {6.0, -2.0, -11.0}, NZZN, ColorGrey},
/*106*/ { {7.0, -2.0, -11.0}, NZZN, ColorGrey},
/*107*/ { {8.0, -2.0, -11.0}, NZZN, ColorGrey},

/*108*/ { {0.0, -2.0, -12.0}, NZZN, ColorGrey},
/*109*/ { {1.0, -2.0, -12.0}, NZZN, ColorGrey},
/*110*/ { {2.0, -2.0, -12.0}, NZZN, ColorGrey},
/*111*/ { {3.0, -2.0, -12.0}, NZZN, ColorGrey},
/*112*/ { {4.0, -2.0, -12.0}, NZZN, ColorGrey},
/*113*/ { {5.0, -2.0, -12.0}, NZZN, ColorGrey},
/*114*/ { {6.0, -2.0, -12.0}, NZZN, ColorGrey},
/*115*/ { {7.0, -2.0, -12.0}, NZZN, ColorGrey},
/*116*/ { {8.0, -2.0, -12.0}, NZZN, ColorGrey},
// any character not white top back finish

// [0, 116] is 117

// 3420

// any character not white quad middle top start
/*0*/   { {0.5, -1.0, -1.0}, NZZN, ColorGrey},
/*1*/   { {1.5, -1.0, -1.0}, NZZN, ColorGrey},
/*2*/   { {2.5, -1.0, -1.0}, NZZN, ColorGrey},
/*3*/   { {3.5, -1.0, -1.0}, NZZN, ColorGrey},
/*4*/   { {4.5, -1.0, -1.0}, NZZN, ColorGrey},
/*5*/   { {5.5, -1.0, -1.0}, NZZN, ColorGrey},
/*6*/   { {6.5, -1.0, -1.0}, NZZN, ColorGrey},
/*7*/   { {7.5, -1.0, -1.0}, NZZN, ColorGrey},

/*8*/   { {0.5, -1.0, -2.0}, NZZN, ColorGrey},
/*9*/   { {1.5, -1.0, -2.0}, NZZN, ColorGrey},
/*10*/  { {2.5, -1.0, -2.0}, NZZN, ColorGrey},
/*11*/  { {3.5, -1.0, -2.0}, NZZN, ColorGrey},
/*12*/  { {4.5, -1.0, -2.0}, NZZN, ColorGrey},
/*13*/  { {5.5, -1.0, -2.0}, NZZN, ColorGrey},
/*14*/  { {6.5, -1.0, -2.0}, NZZN, ColorGrey},
/*15*/  { {7.5, -1.0, -2.0}, NZZN, ColorGrey},

/*16*/  { {0.5, -1.0, -3.0}, NZZN, ColorGrey},
/*17*/  { {1.5, -1.0, -3.0}, NZZN, ColorGrey},
/*18*/  { {2.5, -1.0, -3.0}, NZZN, ColorGrey},
/*19*/  { {3.5, -1.0, -3.0}, NZZN, ColorGrey},
/*20*/  { {4.5, -1.0, -3.0}, NZZN, ColorGrey},
/*21*/  { {5.5, -1.0, -3.0}, NZZN, ColorGrey},
/*22*/  { {6.5, -1.0, -3.0}, NZZN, ColorGrey},
/*23*/  { {7.5, -1.0, -3.0}, NZZN, ColorGrey},

/*24*/  { {0.5, -1.0, -4.0}, NZZN, ColorGrey},
/*25*/  { {1.5, -1.0, -4.0}, NZZN, ColorGrey},
/*26*/  { {2.5, -1.0, -4.0}, NZZN, ColorGrey},
/*27*/  { {3.5, -1.0, -4.0}, NZZN, ColorGrey},
/*28*/  { {4.5, -1.0, -4.0}, NZZN, ColorGrey},
/*29*/  { {5.5, -1.0, -4.0}, NZZN, ColorGrey},
/*30*/  { {6.5, -1.0, -4.0}, NZZN, ColorGrey},
/*31*/  { {7.5, -1.0, -4.0}, NZZN, ColorGrey},

/*32*/  { {0.5, -1.0, -5.0}, NZZN, ColorGrey},
/*33*/  { {1.5, -1.0, -5.0}, NZZN, ColorGrey},
/*34*/  { {2.5, -1.0, -5.0}, NZZN, ColorGrey},
/*35*/  { {3.5, -1.0, -5.0}, NZZN, ColorGrey},
/*36*/  { {4.5, -1.0, -5.0}, NZZN, ColorGrey},
/*37*/  { {5.5, -1.0, -5.0}, NZZN, ColorGrey},
/*38*/  { {6.5, -1.0, -5.0}, NZZN, ColorGrey},
/*39*/  { {7.5, -1.0, -5.0}, NZZN, ColorGrey},

/*40*/  { {0.5, -1.0, -6.0}, NZZN, ColorGrey},
/*41*/  { {1.5, -1.0, -6.0}, NZZN, ColorGrey},
/*42*/  { {2.5, -1.0, -6.0}, NZZN, ColorGrey},
/*43*/  { {3.5, -1.0, -6.0}, NZZN, ColorGrey},
/*44*/  { {4.5, -1.0, -6.0}, NZZN, ColorGrey},
/*45*/  { {5.5, -1.0, -6.0}, NZZN, ColorGrey},
/*46*/  { {6.5, -1.0, -6.0}, NZZN, ColorGrey},
/*47*/  { {7.5, -1.0, -6.0}, NZZN, ColorGrey},

/*48*/  { {0.5, -1.0, -7.0}, NZZN, ColorGrey},
/*49*/  { {1.5, -1.0, -7.0}, NZZN, ColorGrey},
/*50*/  { {2.5, -1.0, -7.0}, NZZN, ColorGrey},
/*51*/  { {3.5, -1.0, -7.0}, NZZN, ColorGrey},
/*52*/  { {4.5, -1.0, -7.0}, NZZN, ColorGrey},
/*53*/  { {5.5, -1.0, -7.0}, NZZN, ColorGrey},
/*54*/  { {6.5, -1.0, -7.0}, NZZN, ColorGrey},
/*55*/  { {7.5, -1.0, -7.0}, NZZN, ColorGrey},

/*56*/  { {0.5, -1.0, -8.0}, NZZN, ColorGrey},
/*57*/  { {1.5, -1.0, -8.0}, NZZN, ColorGrey},
/*58*/  { {2.5, -1.0, -8.0}, NZZN, ColorGrey},
/*59*/  { {3.5, -1.0, -8.0}, NZZN, ColorGrey},
/*60*/  { {4.5, -1.0, -8.0}, NZZN, ColorGrey},
/*61*/  { {5.5, -1.0, -8.0}, NZZN, ColorGrey},
/*62*/  { {6.5, -1.0, -8.0}, NZZN, ColorGrey},
/*63*/  { {7.5, -1.0, -8.0}, NZZN, ColorGrey},

/*64*/  { {0.5, -1.0, -9.0}, NZZN, ColorGrey},
/*65*/  { {1.5, -1.0, -9.0}, NZZN, ColorGrey},
/*66*/  { {2.5, -1.0, -9.0}, NZZN, ColorGrey},
/*67*/  { {3.5, -1.0, -9.0}, NZZN, ColorGrey},
/*68*/  { {4.5, -1.0, -9.0}, NZZN, ColorGrey},
/*69*/  { {5.5, -1.0, -9.0}, NZZN, ColorGrey},
/*70*/  { {6.5, -1.0, -9.0}, NZZN, ColorGrey},
/*71*/  { {7.5, -1.0, -9.0}, NZZN, ColorGrey},

/*72*/  { {0.5, -1.0, -10.0}, NZZN, ColorGrey},
/*73*/  { {1.5, -1.0, -10.0}, NZZN, ColorGrey},
/*74*/  { {2.5, -1.0, -10.0}, NZZN, ColorGrey},
/*75*/  { {3.5, -1.0, -10.0}, NZZN, ColorGrey},
/*76*/  { {4.5, -1.0, -10.0}, NZZN, ColorGrey},
/*77*/  { {5.5, -1.0, -10.0}, NZZN, ColorGrey},
/*78*/  { {6.5, -1.0, -10.0}, NZZN, ColorGrey},
/*79*/  { {7.5, -1.0, -10.0}, NZZN, ColorGrey},

/*80*/  { {0.5, -1.0, -11.0}, NZZN, ColorGrey},
/*81*/  { {1.5, -1.0, -11.0}, NZZN, ColorGrey},
/*82*/  { {2.5, -1.0, -11.0}, NZZN, ColorGrey},
/*83*/  { {3.5, -1.0, -11.0}, NZZN, ColorGrey},
/*84*/  { {4.5, -1.0, -11.0}, NZZN, ColorGrey},
/*85*/  { {5.5, -1.0, -11.0}, NZZN, ColorGrey},
/*86*/  { {6.5, -1.0, -11.0}, NZZN, ColorGrey},
/*87*/  { {7.5, -1.0, -11.0}, NZZN, ColorGrey},

/*88*/  { {0.5, -1.0, -12.0}, NZZN, ColorGrey},
/*89*/  { {1.5, -1.0, -12.0}, NZZN, ColorGrey},
/*90*/  { {2.5, -1.0, -12.0}, NZZN, ColorGrey},
/*91*/  { {3.5, -1.0, -12.0}, NZZN, ColorGrey},
/*92*/  { {4.5, -1.0, -12.0}, NZZN, ColorGrey},
/*93*/  { {5.5, -1.0, -12.0}, NZZN, ColorGrey},
/*94*/  { {6.5, -1.0, -12.0}, NZZN, ColorGrey},
/*95*/  { {7.5, -1.0, -12.0}, NZZN, ColorGrey},
// any character not white quad middle top finish

// [0, 95] is 96

// 3516

// any character not white bottom front start
/*0*/   { {0.0, 0.0, 0.0}, NZZP, ColorGrey},
/*1*/   { {1.0, 0.0, 0.0}, NZZP, ColorGrey},
/*2*/   { {2.0, 0.0, 0.0}, NZZP, ColorGrey},
/*3*/   { {3.0, 0.0, 0.0}, NZZP, ColorGrey},
/*4*/   { {4.0, 0.0, 0.0}, NZZP, ColorGrey},
/*5*/   { {5.0, 0.0, 0.0}, NZZP, ColorGrey},
/*6*/   { {6.0, 0.0, 0.0}, NZZP, ColorGrey},
/*7*/   { {7.0, 0.0, 0.0}, NZZP, ColorGrey},
/*8*/   { {8.0, 0.0, 0.0}, NZZP, ColorGrey},

/*9*/   { {0.0, 0.0, -1.0}, NZZP, ColorGrey},
/*10*/  { {1.0, 0.0, -1.0}, NZZP, ColorGrey},
/*11*/  { {2.0, 0.0, -1.0}, NZZP, ColorGrey},
/*12*/  { {3.0, 0.0, -1.0}, NZZP, ColorGrey},
/*13*/  { {4.0, 0.0, -1.0}, NZZP, ColorGrey},
/*14*/  { {5.0, 0.0, -1.0}, NZZP, ColorGrey},
/*15*/  { {6.0, 0.0, -1.0}, NZZP, ColorGrey},
/*16*/  { {7.0, 0.0, -1.0}, NZZP, ColorGrey},
/*17*/  { {8.0, 0.0, -1.0}, NZZP, ColorGrey},

/*18*/  { {0.0, 0.0, -2.0}, NZZP, ColorGrey},
/*19*/  { {1.0, 0.0, -2.0}, NZZP, ColorGrey},
/*20*/  { {2.0, 0.0, -2.0}, NZZP, ColorGrey},
/*21*/  { {3.0, 0.0, -2.0}, NZZP, ColorGrey},
/*22*/  { {4.0, 0.0, -2.0}, NZZP, ColorGrey},
/*23*/  { {5.0, 0.0, -2.0}, NZZP, ColorGrey},
/*24*/  { {6.0, 0.0, -2.0}, NZZP, ColorGrey},
/*25*/  { {7.0, 0.0, -2.0}, NZZP, ColorGrey},
/*26*/  { {8.0, 0.0, -2.0}, NZZP, ColorGrey},

/*27*/  { {0.0, 0.0, -3.0}, NZZP, ColorGrey},
/*28*/  { {1.0, 0.0, -3.0}, NZZP, ColorGrey},
/*29*/  { {2.0, 0.0, -3.0}, NZZP, ColorGrey},
/*30*/  { {3.0, 0.0, -3.0}, NZZP, ColorGrey},
/*31*/  { {4.0, 0.0, -3.0}, NZZP, ColorGrey},
/*32*/  { {5.0, 0.0, -3.0}, NZZP, ColorGrey},
/*33*/  { {6.0, 0.0, -3.0}, NZZP, ColorGrey},
/*34*/  { {7.0, 0.0, -3.0}, NZZP, ColorGrey},
/*35*/  { {8.0, 0.0, -3.0}, NZZP, ColorGrey},

/*36*/  { {0.0, 0.0, -4.0}, NZZP, ColorGrey},
/*37*/  { {1.0, 0.0, -4.0}, NZZP, ColorGrey},
/*38*/  { {2.0, 0.0, -4.0}, NZZP, ColorGrey},
/*39*/  { {3.0, 0.0, -4.0}, NZZP, ColorGrey},
/*40*/  { {4.0, 0.0, -4.0}, NZZP, ColorGrey},
/*41*/  { {5.0, 0.0, -4.0}, NZZP, ColorGrey},
/*42*/  { {6.0, 0.0, -4.0}, NZZP, ColorGrey},
/*43*/  { {7.0, 0.0, -4.0}, NZZP, ColorGrey},
/*44*/  { {8.0, 0.0, -4.0}, NZZP, ColorGrey},

/*45*/  { {0.0, 0.0, -5.0}, NZZP, ColorGrey},
/*46*/  { {1.0, 0.0, -5.0}, NZZP, ColorGrey},
/*47*/  { {2.0, 0.0, -5.0}, NZZP, ColorGrey},
/*48*/  { {3.0, 0.0, -5.0}, NZZP, ColorGrey},
/*49*/  { {4.0, 0.0, -5.0}, NZZP, ColorGrey},
/*50*/  { {5.0, 0.0, -5.0}, NZZP, ColorGrey},
/*51*/  { {6.0, 0.0, -5.0}, NZZP, ColorGrey},
/*52*/  { {7.0, 0.0, -5.0}, NZZP, ColorGrey},
/*53*/  { {8.0, 0.0, -5.0}, NZZP, ColorGrey},

/*54*/  { {0.0, 0.0, -6.0}, NZZP, ColorGrey},
/*55*/  { {1.0, 0.0, -6.0}, NZZP, ColorGrey},
/*56*/  { {2.0, 0.0, -6.0}, NZZP, ColorGrey},
/*57*/  { {3.0, 0.0, -6.0}, NZZP, ColorGrey},
/*58*/  { {4.0, 0.0, -6.0}, NZZP, ColorGrey},
/*59*/  { {5.0, 0.0, -6.0}, NZZP, ColorGrey},
/*60*/  { {6.0, 0.0, -6.0}, NZZP, ColorGrey},
/*61*/  { {7.0, 0.0, -6.0}, NZZP, ColorGrey},
/*62*/  { {8.0, 0.0, -6.0}, NZZP, ColorGrey},

/*63*/  { {0.0, 0.0, -7.0}, NZZP, ColorGrey},
/*64*/  { {1.0, 0.0, -7.0}, NZZP, ColorGrey},
/*65*/  { {2.0, 0.0, -7.0}, NZZP, ColorGrey},
/*66*/  { {3.0, 0.0, -7.0}, NZZP, ColorGrey},
/*67*/  { {4.0, 0.0, -7.0}, NZZP, ColorGrey},
/*68*/  { {5.0, 0.0, -7.0}, NZZP, ColorGrey},
/*69*/  { {6.0, 0.0, -7.0}, NZZP, ColorGrey},
/*70*/  { {7.0, 0.0, -7.0}, NZZP, ColorGrey},
/*71*/  { {8.0, 0.0, -7.0}, NZZP, ColorGrey},

/*72*/  { {0.0, 0.0, -8.0}, NZZP, ColorGrey},
/*73*/  { {1.0, 0.0, -8.0}, NZZP, ColorGrey},
/*74*/  { {2.0, 0.0, -8.0}, NZZP, ColorGrey},
/*75*/  { {3.0, 0.0, -8.0}, NZZP, ColorGrey},
/*76*/  { {4.0, 0.0, -8.0}, NZZP, ColorGrey},
/*77*/  { {5.0, 0.0, -8.0}, NZZP, ColorGrey},
/*78*/  { {6.0, 0.0, -8.0}, NZZP, ColorGrey},
/*79*/  { {7.0, 0.0, -8.0}, NZZP, ColorGrey},
/*80*/  { {8.0, 0.0, -8.0}, NZZP, ColorGrey},

/*81*/  { {0.0, 0.0, -9.0}, NZZP, ColorGrey},
/*82*/  { {1.0, 0.0, -9.0}, NZZP, ColorGrey},
/*83*/  { {2.0, 0.0, -9.0}, NZZP, ColorGrey},
/*84*/  { {3.0, 0.0, -9.0}, NZZP, ColorGrey},
/*85*/  { {4.0, 0.0, -9.0}, NZZP, ColorGrey},
/*86*/  { {5.0, 0.0, -9.0}, NZZP, ColorGrey},
/*87*/  { {6.0, 0.0, -9.0}, NZZP, ColorGrey},
/*88*/  { {7.0, 0.0, -9.0}, NZZP, ColorGrey},
/*89*/  { {8.0, 0.0, -9.0}, NZZP, ColorGrey},

/*90*/  { {0.0, 0.0, -10.0}, NZZP, ColorGrey},
/*91*/  { {1.0, 0.0, -10.0}, NZZP, ColorGrey},
/*92*/  { {2.0, 0.0, -10.0}, NZZP, ColorGrey},
/*93*/  { {3.0, 0.0, -10.0}, NZZP, ColorGrey},
/*94*/  { {4.0, 0.0, -10.0}, NZZP, ColorGrey},
/*95*/  { {5.0, 0.0, -10.0}, NZZP, ColorGrey},
/*96*/  { {6.0, 0.0, -10.0}, NZZP, ColorGrey},
/*97*/  { {7.0, 0.0, -10.0}, NZZP, ColorGrey},
/*98*/  { {8.0, 0.0, -10.0}, NZZP, ColorGrey},

/*99*/  { {0.0, 0.0, -11.0}, NZZP, ColorGrey},
/*100*/ { {1.0, 0.0, -11.0}, NZZP, ColorGrey},
/*101*/ { {2.0, 0.0, -11.0}, NZZP, ColorGrey},
/*102*/ { {3.0, 0.0, -11.0}, NZZP, ColorGrey},
/*103*/ { {4.0, 0.0, -11.0}, NZZP, ColorGrey},
/*104*/ { {5.0, 0.0, -11.0}, NZZP, ColorGrey},
/*105*/ { {6.0, 0.0, -11.0}, NZZP, ColorGrey},
/*106*/ { {7.0, 0.0, -11.0}, NZZP, ColorGrey},
/*107*/ { {8.0, 0.0, -11.0}, NZZP, ColorGrey},

/*108*/ { {0.0, 0.0, -12.0}, NZZP, ColorGrey},
/*109*/ { {1.0, 0.0, -12.0}, NZZP, ColorGrey},
/*110*/ { {2.0, 0.0, -12.0}, NZZP, ColorGrey},
/*111*/ { {3.0, 0.0, -12.0}, NZZP, ColorGrey},
/*112*/ { {4.0, 0.0, -12.0}, NZZP, ColorGrey},
/*113*/ { {5.0, 0.0, -12.0}, NZZP, ColorGrey},
/*114*/ { {6.0, 0.0, -12.0}, NZZP, ColorGrey},
/*115*/ { {7.0, 0.0, -12.0}, NZZP, ColorGrey},
/*116*/ { {8.0, 0.0, -12.0}, NZZP, ColorGrey},
// any character not white bottom front finish

// [0, 116] is 117

// 3633

// any character not white bottom back start
/*0*/   { {0.0, -2.0, 0.0}, NZZP, ColorGrey},
/*1*/   { {1.0, -2.0, 0.0}, NZZP, ColorGrey},
/*2*/   { {2.0, -2.0, 0.0}, NZZP, ColorGrey},
/*3*/   { {3.0, -2.0, 0.0}, NZZP, ColorGrey},
/*4*/   { {4.0, -2.0, 0.0}, NZZP, ColorGrey},
/*5*/   { {5.0, -2.0, 0.0}, NZZP, ColorGrey},
/*6*/   { {6.0, -2.0, 0.0}, NZZP, ColorGrey},
/*7*/   { {7.0, -2.0, 0.0}, NZZP, ColorGrey},
/*8*/   { {8.0, -2.0, 0.0}, NZZP, ColorGrey},

/*9*/   { {0.0, -2.0, -1.0}, NZZP, ColorGrey},
/*10*/  { {1.0, -2.0, -1.0}, NZZP, ColorGrey},
/*11*/  { {2.0, -2.0, -1.0}, NZZP, ColorGrey},
/*12*/  { {3.0, -2.0, -1.0}, NZZP, ColorGrey},
/*13*/  { {4.0, -2.0, -1.0}, NZZP, ColorGrey},
/*14*/  { {5.0, -2.0, -1.0}, NZZP, ColorGrey},
/*15*/  { {6.0, -2.0, -1.0}, NZZP, ColorGrey},
/*16*/  { {7.0, -2.0, -1.0}, NZZP, ColorGrey},
/*17*/  { {8.0, -2.0, -1.0}, NZZP, ColorGrey},

/*18*/  { {0.0, -2.0, -2.0}, NZZP, ColorGrey},
/*19*/  { {1.0, -2.0, -2.0}, NZZP, ColorGrey},
/*20*/  { {2.0, -2.0, -2.0}, NZZP, ColorGrey},
/*21*/  { {3.0, -2.0, -2.0}, NZZP, ColorGrey},
/*22*/  { {4.0, -2.0, -2.0}, NZZP, ColorGrey},
/*23*/  { {5.0, -2.0, -2.0}, NZZP, ColorGrey},
/*24*/  { {6.0, -2.0, -2.0}, NZZP, ColorGrey},
/*25*/  { {7.0, -2.0, -2.0}, NZZP, ColorGrey},
/*26*/  { {8.0, -2.0, -2.0}, NZZP, ColorGrey},

/*27*/  { {0.0, -2.0, -3.0}, NZZP, ColorGrey},
/*28*/  { {1.0, -2.0, -3.0}, NZZP, ColorGrey},
/*29*/  { {2.0, -2.0, -3.0}, NZZP, ColorGrey},
/*30*/  { {3.0, -2.0, -3.0}, NZZP, ColorGrey},
/*31*/  { {4.0, -2.0, -3.0}, NZZP, ColorGrey},
/*32*/  { {5.0, -2.0, -3.0}, NZZP, ColorGrey},
/*33*/  { {6.0, -2.0, -3.0}, NZZP, ColorGrey},
/*34*/  { {7.0, -2.0, -3.0}, NZZP, ColorGrey},
/*35*/  { {8.0, -2.0, -3.0}, NZZP, ColorGrey},

/*36*/  { {0.0, -2.0, -4.0}, NZZP, ColorGrey},
/*37*/  { {1.0, -2.0, -4.0}, NZZP, ColorGrey},
/*38*/  { {2.0, -2.0, -4.0}, NZZP, ColorGrey},
/*39*/  { {3.0, -2.0, -4.0}, NZZP, ColorGrey},
/*40*/  { {4.0, -2.0, -4.0}, NZZP, ColorGrey},
/*41*/  { {5.0, -2.0, -4.0}, NZZP, ColorGrey},
/*42*/  { {6.0, -2.0, -4.0}, NZZP, ColorGrey},
/*43*/  { {7.0, -2.0, -4.0}, NZZP, ColorGrey},
/*44*/  { {8.0, -2.0, -4.0}, NZZP, ColorGrey},

/*45*/  { {0.0, -2.0, -5.0}, NZZP, ColorGrey},
/*46*/  { {1.0, -2.0, -5.0}, NZZP, ColorGrey},
/*47*/  { {2.0, -2.0, -5.0}, NZZP, ColorGrey},
/*48*/  { {3.0, -2.0, -5.0}, NZZP, ColorGrey},
/*49*/  { {4.0, -2.0, -5.0}, NZZP, ColorGrey},
/*50*/  { {5.0, -2.0, -5.0}, NZZP, ColorGrey},
/*51*/  { {6.0, -2.0, -5.0}, NZZP, ColorGrey},
/*52*/  { {7.0, -2.0, -5.0}, NZZP, ColorGrey},
/*53*/  { {8.0, -2.0, -5.0}, NZZP, ColorGrey},

/*54*/  { {0.0, -2.0, -6.0}, NZZP, ColorGrey},
/*55*/  { {1.0, -2.0, -6.0}, NZZP, ColorGrey},
/*56*/  { {2.0, -2.0, -6.0}, NZZP, ColorGrey},
/*57*/  { {3.0, -2.0, -6.0}, NZZP, ColorGrey},
/*58*/  { {4.0, -2.0, -6.0}, NZZP, ColorGrey},
/*59*/  { {5.0, -2.0, -6.0}, NZZP, ColorGrey},
/*60*/  { {6.0, -2.0, -6.0}, NZZP, ColorGrey},
/*61*/  { {7.0, -2.0, -6.0}, NZZP, ColorGrey},
/*62*/  { {8.0, -2.0, -6.0}, NZZP, ColorGrey},

/*63*/  { {0.0, -2.0, -7.0}, NZZP, ColorGrey},
/*64*/  { {1.0, -2.0, -7.0}, NZZP, ColorGrey},
/*65*/  { {2.0, -2.0, -7.0}, NZZP, ColorGrey},
/*66*/  { {3.0, -2.0, -7.0}, NZZP, ColorGrey},
/*67*/  { {4.0, -2.0, -7.0}, NZZP, ColorGrey},
/*68*/  { {5.0, -2.0, -7.0}, NZZP, ColorGrey},
/*69*/  { {6.0, -2.0, -7.0}, NZZP, ColorGrey},
/*70*/  { {7.0, -2.0, -7.0}, NZZP, ColorGrey},
/*71*/  { {8.0, -2.0, -7.0}, NZZP, ColorGrey},

/*72*/  { {0.0, -2.0, -8.0}, NZZP, ColorGrey},
/*73*/  { {1.0, -2.0, -8.0}, NZZP, ColorGrey},
/*74*/  { {2.0, -2.0, -8.0}, NZZP, ColorGrey},
/*75*/  { {3.0, -2.0, -8.0}, NZZP, ColorGrey},
/*76*/  { {4.0, -2.0, -8.0}, NZZP, ColorGrey},
/*77*/  { {5.0, -2.0, -8.0}, NZZP, ColorGrey},
/*78*/  { {6.0, -2.0, -8.0}, NZZP, ColorGrey},
/*79*/  { {7.0, -2.0, -8.0}, NZZP, ColorGrey},
/*80*/  { {8.0, -2.0, -8.0}, NZZP, ColorGrey},

/*81*/  { {0.0, -2.0, -9.0}, NZZP, ColorGrey},
/*82*/  { {1.0, -2.0, -9.0}, NZZP, ColorGrey},
/*83*/  { {2.0, -2.0, -9.0}, NZZP, ColorGrey},
/*84*/  { {3.0, -2.0, -9.0}, NZZP, ColorGrey},
/*85*/  { {4.0, -2.0, -9.0}, NZZP, ColorGrey},
/*86*/  { {5.0, -2.0, -9.0}, NZZP, ColorGrey},
/*87*/  { {6.0, -2.0, -9.0}, NZZP, ColorGrey},
/*88*/  { {7.0, -2.0, -9.0}, NZZP, ColorGrey},
/*89*/  { {8.0, -2.0, -9.0}, NZZP, ColorGrey},

/*90*/  { {0.0, -2.0, -10.0}, NZZP, ColorGrey},
/*91*/  { {1.0, -2.0, -10.0}, NZZP, ColorGrey},
/*92*/  { {2.0, -2.0, -10.0}, NZZP, ColorGrey},
/*93*/  { {3.0, -2.0, -10.0}, NZZP, ColorGrey},
/*94*/  { {4.0, -2.0, -10.0}, NZZP, ColorGrey},
/*95*/  { {5.0, -2.0, -10.0}, NZZP, ColorGrey},
/*96*/  { {6.0, -2.0, -10.0}, NZZP, ColorGrey},
/*97*/  { {7.0, -2.0, -10.0}, NZZP, ColorGrey},
/*98*/  { {8.0, -2.0, -10.0}, NZZP, ColorGrey},

/*99*/  { {0.0, -2.0, -11.0}, NZZP, ColorGrey},
/*100*/ { {1.0, -2.0, -11.0}, NZZP, ColorGrey},
/*101*/ { {2.0, -2.0, -11.0}, NZZP, ColorGrey},
/*102*/ { {3.0, -2.0, -11.0}, NZZP, ColorGrey},
/*103*/ { {4.0, -2.0, -11.0}, NZZP, ColorGrey},
/*104*/ { {5.0, -2.0, -11.0}, NZZP, ColorGrey},
/*105*/ { {6.0, -2.0, -11.0}, NZZP, ColorGrey},
/*106*/ { {7.0, -2.0, -11.0}, NZZP, ColorGrey},
/*107*/ { {8.0, -2.0, -11.0}, NZZP, ColorGrey},

/*108*/ { {0.0, -2.0, -12.0}, NZZP, ColorGrey},
/*109*/ { {1.0, -2.0, -12.0}, NZZP, ColorGrey},
/*110*/ { {2.0, -2.0, -12.0}, NZZP, ColorGrey},
/*111*/ { {3.0, -2.0, -12.0}, NZZP, ColorGrey},
/*112*/ { {4.0, -2.0, -12.0}, NZZP, ColorGrey},
/*113*/ { {5.0, -2.0, -12.0}, NZZP, ColorGrey},
/*114*/ { {6.0, -2.0, -12.0}, NZZP, ColorGrey},
/*115*/ { {7.0, -2.0, -12.0}, NZZP, ColorGrey},
/*116*/ { {8.0, -2.0, -12.0}, NZZP, ColorGrey},
// any character not white bottom back finish

// [0, 116] is 117

// 3750

// any character not white quad middle bottom start
/*0*/   { {0.5, -1.0, 0.0}, NZZP, ColorGrey},
/*1*/   { {1.5, -1.0, 0.0}, NZZP, ColorGrey},
/*2*/   { {2.5, -1.0, 0.0}, NZZP, ColorGrey},
/*3*/   { {3.5, -1.0, 0.0}, NZZP, ColorGrey},
/*4*/   { {4.5, -1.0, 0.0}, NZZP, ColorGrey},
/*5*/   { {5.5, -1.0, 0.0}, NZZP, ColorGrey},
/*6*/   { {6.5, -1.0, 0.0}, NZZP, ColorGrey},
/*7*/   { {7.5, -1.0, 0.0}, NZZP, ColorGrey},

/*8*/   { {0.5, -1.0, -1.0}, NZZP, ColorGrey},
/*9*/   { {1.5, -1.0, -1.0}, NZZP, ColorGrey},
/*10*/  { {2.5, -1.0, -1.0}, NZZP, ColorGrey},
/*11*/  { {3.5, -1.0, -1.0}, NZZP, ColorGrey},
/*12*/  { {4.5, -1.0, -1.0}, NZZP, ColorGrey},
/*13*/  { {5.5, -1.0, -1.0}, NZZP, ColorGrey},
/*14*/  { {6.5, -1.0, -1.0}, NZZP, ColorGrey},
/*15*/  { {7.5, -1.0, -1.0}, NZZP, ColorGrey},

/*16*/  { {0.5, -1.0, -2.0}, NZZP, ColorGrey},
/*17*/  { {1.5, -1.0, -2.0}, NZZP, ColorGrey},
/*18*/  { {2.5, -1.0, -2.0}, NZZP, ColorGrey},
/*19*/  { {3.5, -1.0, -2.0}, NZZP, ColorGrey},
/*20*/  { {4.5, -1.0, -2.0}, NZZP, ColorGrey},
/*21*/  { {5.5, -1.0, -2.0}, NZZP, ColorGrey},
/*22*/  { {6.5, -1.0, -2.0}, NZZP, ColorGrey},
/*23*/  { {7.5, -1.0, -2.0}, NZZP, ColorGrey},

/*24*/  { {0.5, -1.0, -3.0}, NZZP, ColorGrey},
/*25*/  { {1.5, -1.0, -3.0}, NZZP, ColorGrey},
/*26*/  { {2.5, -1.0, -3.0}, NZZP, ColorGrey},
/*27*/  { {3.5, -1.0, -3.0}, NZZP, ColorGrey},
/*28*/  { {4.5, -1.0, -3.0}, NZZP, ColorGrey},
/*29*/  { {5.5, -1.0, -3.0}, NZZP, ColorGrey},
/*30*/  { {6.5, -1.0, -3.0}, NZZP, ColorGrey},
/*31*/  { {7.5, -1.0, -3.0}, NZZP, ColorGrey},

/*32*/  { {0.5, -1.0, -4.0}, NZZP, ColorGrey},
/*33*/  { {1.5, -1.0, -4.0}, NZZP, ColorGrey},
/*34*/  { {2.5, -1.0, -4.0}, NZZP, ColorGrey},
/*35*/  { {3.5, -1.0, -4.0}, NZZP, ColorGrey},
/*36*/  { {4.5, -1.0, -4.0}, NZZP, ColorGrey},
/*37*/  { {5.5, -1.0, -4.0}, NZZP, ColorGrey},
/*38*/  { {6.5, -1.0, -4.0}, NZZP, ColorGrey},
/*39*/  { {7.5, -1.0, -4.0}, NZZP, ColorGrey},

/*40*/  { {0.5, -1.0, -5.0}, NZZP, ColorGrey},
/*41*/  { {1.5, -1.0, -5.0}, NZZP, ColorGrey},
/*42*/  { {2.5, -1.0, -5.0}, NZZP, ColorGrey},
/*43*/  { {3.5, -1.0, -5.0}, NZZP, ColorGrey},
/*44*/  { {4.5, -1.0, -5.0}, NZZP, ColorGrey},
/*45*/  { {5.5, -1.0, -5.0}, NZZP, ColorGrey},
/*46*/  { {6.5, -1.0, -5.0}, NZZP, ColorGrey},
/*47*/  { {7.5, -1.0, -5.0}, NZZP, ColorGrey},

/*48*/  { {0.5, -1.0, -6.0}, NZZP, ColorGrey},
/*49*/  { {1.5, -1.0, -6.0}, NZZP, ColorGrey},
/*50*/  { {2.5, -1.0, -6.0}, NZZP, ColorGrey},
/*51*/  { {3.5, -1.0, -6.0}, NZZP, ColorGrey},
/*52*/  { {4.5, -1.0, -6.0}, NZZP, ColorGrey},
/*53*/  { {5.5, -1.0, -6.0}, NZZP, ColorGrey},
/*54*/  { {6.5, -1.0, -6.0}, NZZP, ColorGrey},
/*55*/  { {7.5, -1.0, -6.0}, NZZP, ColorGrey},

/*56*/  { {0.5, -1.0, -7.0}, NZZP, ColorGrey},
/*57*/  { {1.5, -1.0, -7.0}, NZZP, ColorGrey},
/*58*/  { {2.5, -1.0, -7.0}, NZZP, ColorGrey},
/*59*/  { {3.5, -1.0, -7.0}, NZZP, ColorGrey},
/*60*/  { {4.5, -1.0, -7.0}, NZZP, ColorGrey},
/*61*/  { {5.5, -1.0, -7.0}, NZZP, ColorGrey},
/*62*/  { {6.5, -1.0, -7.0}, NZZP, ColorGrey},
/*63*/  { {7.5, -1.0, -7.0}, NZZP, ColorGrey},

/*64*/  { {0.5, -1.0, -8.0}, NZZP, ColorGrey},
/*65*/  { {1.5, -1.0, -8.0}, NZZP, ColorGrey},
/*66*/  { {2.5, -1.0, -8.0}, NZZP, ColorGrey},
/*67*/  { {3.5, -1.0, -8.0}, NZZP, ColorGrey},
/*68*/  { {4.5, -1.0, -8.0}, NZZP, ColorGrey},
/*69*/  { {5.5, -1.0, -8.0}, NZZP, ColorGrey},
/*70*/  { {6.5, -1.0, -8.0}, NZZP, ColorGrey},
/*71*/  { {7.5, -1.0, -8.0}, NZZP, ColorGrey},

/*72*/  { {0.5, -1.0, -9.0}, NZZP, ColorGrey},
/*73*/  { {1.5, -1.0, -9.0}, NZZP, ColorGrey},
/*74*/  { {2.5, -1.0, -9.0}, NZZP, ColorGrey},
/*75*/  { {3.5, -1.0, -9.0}, NZZP, ColorGrey},
/*76*/  { {4.5, -1.0, -9.0}, NZZP, ColorGrey},
/*77*/  { {5.5, -1.0, -9.0}, NZZP, ColorGrey},
/*78*/  { {6.5, -1.0, -9.0}, NZZP, ColorGrey},
/*79*/  { {7.5, -1.0, -9.0}, NZZP, ColorGrey},

/*80*/  { {0.5, -1.0, -10.0}, NZZP, ColorGrey},
/*81*/  { {1.5, -1.0, -10.0}, NZZP, ColorGrey},
/*82*/  { {2.5, -1.0, -10.0}, NZZP, ColorGrey},
/*83*/  { {3.5, -1.0, -10.0}, NZZP, ColorGrey},
/*84*/  { {4.5, -1.0, -10.0}, NZZP, ColorGrey},
/*85*/  { {5.5, -1.0, -10.0}, NZZP, ColorGrey},
/*86*/  { {6.5, -1.0, -10.0}, NZZP, ColorGrey},
/*87*/  { {7.5, -1.0, -10.0}, NZZP, ColorGrey},

/*88*/  { {0.5, -1.0, -11.0}, NZZP, ColorGrey},
/*89*/  { {1.5, -1.0, -11.0}, NZZP, ColorGrey},
/*90*/  { {2.5, -1.0, -11.0}, NZZP, ColorGrey},
/*91*/  { {3.5, -1.0, -11.0}, NZZP, ColorGrey},
/*92*/  { {4.5, -1.0, -11.0}, NZZP, ColorGrey},
/*93*/  { {5.5, -1.0, -11.0}, NZZP, ColorGrey},
/*94*/  { {6.5, -1.0, -11.0}, NZZP, ColorGrey},
/*95*/  { {7.5, -1.0, -11.0}, NZZP, ColorGrey}
// any character not white quad middle bottom finish

// [0, 95] is 96

// 3846
#endif

};

// winding order is clockwise. each side uses a different color
constexpr uint32_t gModelsIndicesStaticData[] =
{

// 0

// arrow model start
  0, 1, 2, // 3
  1, 4, 2, // 6
  4, 7, 2, // 9
  7, 0, 2, // 12

  12, 13, 14, // 15
  15, 16, 17, // 18

  18, 19, 20, // 21
  21, 22, 23, // 23

  24, 25, 26, // 27
  27, 28, 29, // 30

  30, 31, 32, // 33
  33, 34, 35, // 36

  36, 37, 38, 39, 40, 41, // 42
  42, 43, 44, 45, 46, 47, // 48

  48, 49, 50, 51, 52, 53, // 54
  54, 55, 56, 57, 58, 59, // 60

  60, 61, 62, 63, 64, 65, // 66
  66, 67, 68, 69, 70, 71, // 72

  72, 73, 74, 75, 76, 77, // 78
  78, 79, 80, 81, 82, 83, // 84

  84, 85, 86, 87, 88, 89, // 90
  90, 91, 92, 93, 94, 95, // 96
// arrow model finish

// 96

// cube model start
  96, 97, 98, 99, 97, 96, // 6
  102, 97, 99, 98, 97, 102, // 12

  108, 109, 110, 111, 109, 108, // 18
  114, 109, 111, 110, 109, 114, // 24

  102, 121, 98, 108, 121, 102, // 30
  110, 121, 108, 98, 121, 110, // 36

  96, 133, 99, 114, 133, 96, // 42
  111, 133, 114, 99, 133, 111, // 48

  98, 145, 96, 110, 145, 98, // 54
  114, 145, 110, 96, 145, 114, // 60

  99, 157, 102, 111, 157, 99, // 66
  108, 157, 111, 102, 157, 108, // 72
// cube model finish

// 168

#if 0
f 12/1/1 7/1/1 5/1/1 9/1/1
f 1/1/1 10/1/1 11/1/1 6/1/1
f 2/1/1 12/1/1 9/1/1 3/1/1
f 7/1/1 12/1/1 6/1/1 11/1/1
f 10/1/1 4/1/1 8/1/1 11/1/1
f 24/1/2 21/1/2 17/1/2 19/1/2
f 13/1/2 18/1/2 23/1/2 22/1/2
f 14/1/2 15/1/2 21/1/2 24/1/2
f 19/1/2 23/1/2 18/1/2 24/1/2
f 22/1/2 23/1/2 20/1/2 16/1/2
f 5/1/3 7/1/3 19/1/3 17/1/3
f 9/1/4 5/1/4 17/1/4 21/1/4
f 2/1/5 3/1/5 15/1/5 14/1/5
f 8/1/3 4/1/3 16/1/3 20/1/3
f 10/1/6 1/1/6 13/1/6 22/1/6
f 1/1/5 6/1/5 18/1/5 13/1/5
f 3/1/4 9/1/4 21/1/4 15/1/4
f 4/1/6 10/1/6 22/1/6 16/1/6
f 11/1/4 8/1/4 20/1/4 23/1/4
f 12/1/6 2/1/6 14/1/6 24/1/6
f 7/1/7 11/1/7 23/1/7 19/1/7
f 6/1/8 12/1/8 24/1/8 18/1/8
#endif

#if 0
12/1/1 7/1/1 5/1/1
5/1/1 9/1/1 12/1/1

1/1/1 10/1/1 11/1/1
11/1/1 6/1/1 1/1/1

2/1/1 12/1/1 9/1/1
9/1/1 3/1/1 2/1/1

7/1/1 12/1/1 6/1/1
6/1/1 11/1/1 7/1/1

10/1/1 4/1/1 8/1/1
8/1/1 11/1/1 10/1/1

24/1/2 21/1/2 17/1/2
17/1/2 19/1/2 24/1/2

13/1/2 18/1/2 23/1/2
23/1/2 22/1/2 13/1/2

14/1/2 15/1/2 21/1/2
21/1/2 24/1/2 14/1/2

19/1/2 23/1/2 18/1/2
18/1/2 24/1/2 19/1/2

22/1/2 23/1/2 20/1/2
20/1/2 16/1/2 22/1/2

5/1/3 7/1/3 19/1/3
19/1/3 17/1/3 5/1/3

9/1/4 5/1/4 17/1/4
17/1/4 21/1/4 9/1/4

2/1/5 3/1/5 15/1/5
15/1/5 14/1/5 2/1/5

8/1/3 4/1/3 16/1/3
16/1/3 20/1/3 8/1/3

10/1/6 1/1/6 13/1/6
13/1/6 22/1/6 10/1/6

1/1/5 6/1/5 18/1/5
18/1/5 13/1/5 1/1/5

3/1/4 9/1/4 21/1/4
21/1/4 15/1/4 3/1/4

4/1/6 10/1/6 22/1/6
22/1/6 16/1/6 4/1/6

11/1/4 8/1/4 20/1/4
20/1/4 23/1/4 11/1/4

12/1/6 2/1/6 14/1/6
14/1/6 24/1/6 12/1/6

7/1/7 11/1/7 23/1/7
23/1/7 19/1/7 7/1/7

6/1/8 12/1/8 24/1/8
24/1/8 18/1/8 6/1/8
#endif

// 'Z' start
5, 7, 12, // 3
12, 9, 5, // 6

11, 10, 1, // 9
1, 6, 11, // 12

9, 12, 2, // 15
2, 3, 9, // 18

6, 12, 7, // 21
7, 11, 6, // 24

8, 4, 10, // 27
10, 11, 8, // 30

17, 21, 24, // 33
24, 19, 17, // 36

23, 18, 13, // 39
13, 22, 23, // 42

21, 15, 14, // 45
14, 24, 21, // 48

18, 23, 19, // 51
19, 24, 18, // 54

20, 23, 22, // 57
22, 16, 20, // 60

19, 7, 5, // 63
5, 17, 19, // 66

17, 5, 9, // 69
9, 21, 17, // 72

15, 3, 2, // 75
2, 14, 15, // 78

16, 4, 8, // 81
8, 20, 16, // 84

13, 1, 10, // 87
10, 22, 13, // 90

18, 6, 1, // 93
1, 13, 18, // 96

21, 9, 3, // 99
3, 15, 21, // 102

22, 10, 4, // 105
4, 16, 22, // 108

20, 8, 11, // 111
11, 23, 20, // 114

14, 2, 12, // 117
12, 24, 14, // 120

23, 11, 7, // 123
7, 19, 23, // 126

24, 12, 6, // 129
6, 18, 24, // 132
// 'Z' finish

// 300

// bottom-left
// bottom-right
// top-right
// -
// top-right
// top-left
// bottom-left

// top-right
// bottom-right
// bottom-left
// -
// bottom-left
// top-left
// top-right

// smiley front start

// first row of quads

9, 1, 0,
0, 8, 9, // 6

10, 2, 1,
1, 9, 10, // 12

11, 3, 2,
2, 10, 11, // 18

12, 4, 3,
3, 11, 12, // 24

13, 5, 4,
4, 12, 13, // 30

14, 6, 5,
5, 13, 14, // 36

// second row of quads

17, 8, 7,
7, 16, 17, // 42

18, 9, 8,
8, 17, 18, // 48

23, 14, 13,
13, 22, 23, // 54

24, 15, 14,
14, 23, 24, // 60

// third row of quads

26, 17, 16,
16, 25, 26, // 66

29, 20, 19,
19, 28, 29, // 72

30, 21, 20,
20, 29, 30, // 78

33, 24, 23,
23, 32, 33, // 84

// fourth row of quads

35, 26, 25,
25, 34, 35, // 90

37, 28, 27,
27, 36, 37, // 96

38, 29, 28,
28, 37, 38, // 102

39, 30, 29,
29, 38, 39, // 108

40, 31, 30,
30, 39, 40, // 114

42, 33, 32,
32, 41, 42, // 120

// fifth row of quads

44, 35, 34,
34, 43, 44, // 126

50, 42, 41,
41, 49, 50, // 132

// sixth row of quads

52, 44, 43,
43, 51, 52, // 138

54, 46, 45,
45, 53, 54, // 144

56, 48, 47,
47, 55, 56, // 150

58, 50, 49,
49, 57, 58, // 156

// seventh row of quads

60, 52, 51,
51, 59, 60, // 162

64, 58, 57,
57, 63, 64, // 168

// eighth row of quads

66, 60, 59,
59, 65, 66, // 174

67, 61, 60,
60, 66, 67, // 180

72, 63, 62,
62, 71, 72, // 186

73, 64, 63,
63, 72, 73, // 192

// ninth row of quads

75, 67, 66,
66, 74, 75, // 198

76, 68, 67,
67, 75, 76, // 204

77, 69, 68,
68, 76, 77, // 210

78, 70, 69,
69, 77, 78, // 216

79, 71, 70,
70, 78, 79, // 222

80, 72, 71,
71, 79, 80, // 228

// smiley front finish

// 528

// smiley back start

// first row of quads

0, 1, 9,
9, 8, 0, // 6

1, 2, 10,
10, 9, 1, // 12

2, 3, 11,
11, 10, 2, // 18

3, 4, 12,
12, 11, 3, // 24

4, 5, 13,
13, 12, 4, // 30

5, 6, 14,
14, 13, 5, // 36

// second row of quads

7, 8, 17,
17, 16, 7, // 42

8, 9, 18,
18, 17, 8, // 48

13, 14, 23,
23, 22, 13, // 54

14, 15, 24,
24, 23, 14, // 60

// third row of quads

16, 17, 26,
26, 25, 16, // 66

19, 20, 29,
29, 28, 19, // 72

20, 21, 30,
30, 29, 20, // 78

23, 24, 33,
33, 32, 23, // 84

// fourth row of quads

25, 26, 35,
35, 34, 25, // 90

27, 28, 37,
37, 36, 27, // 96

28, 29, 38,
38, 37, 28, // 102

29, 30, 39,
39, 38, 29, // 108

30, 31, 40,
40, 39, 30, // 114

32, 33, 42,
42, 41, 32, // 120

// fifth row of quads

34, 35, 44,
44, 43, 34, // 126

41, 42, 50,
50, 49, 41, // 132

// sixth row of quads

43, 44, 52,
52, 51, 43, // 138

45, 46, 54,
54, 53, 45, // 144

47, 48, 56,
56, 55, 47, // 150

49, 50, 58,
58, 57, 49, // 156

// seventh row of quads

51, 52, 60,
60, 59, 51, // 162

57, 58, 64,
64, 63, 57, // 168

// eighth row of quads

59, 60, 66,
66, 65, 59, // 174

60, 61, 67,
67, 66, 60, // 180

62, 63, 72,
72, 71, 62, // 186

63, 64, 73,
73, 72, 63, // 192

// ninth row of quads

66, 67, 75,
75, 74, 66, // 198

67, 68, 76,
76, 75, 67, // 204

68, 69, 77,
77, 76, 68, // 210

69, 70, 78,
78, 77, 69, // 216

70, 71, 79,
79, 78, 70, // 222

71, 72, 80,
80, 79, 71, // 228

// smiley back finish

// 756

// smiley left, right, top, bottom start

// first row of quads

7 + 81, 7, 8,
8, 8 + 81, 7 + 81, // 6

8 + 81, 8, 0,
0, 0 + 81, 8 + 81, // 12

1 + 81, 0 + 81, 0,
0, 1, 1 + 81, // 18

2 + 81, 1 + 81, 1,
1, 2, 2 + 81, // 24

3 + 81, 2 + 81, 2,
2, 3, 3 + 81, // 30

4 + 81, 3 + 81, 3,
3, 4, 4 + 81, // 36

5 + 81, 4 + 81, 4,
4, 5, 5 + 81, // 42

6 + 81, 5 + 81, 5,
5, 6, 6 + 81, // 48

6, 14, 14 + 81,
14 + 81, 6 + 81, 6, // 54

14 + 81, 14, 15,
15, 15 + 81, 14 + 81, // 60

// second row of quads

7, 7 + 81, 16 + 81,
16 + 81, 16, 7, // 66

9, 18, 18 + 81,
18 + 81, 9 + 81, 9, // 72

10, 9, 9 + 81,
9 + 81, 10 + 81, 10, // 78

11, 10, 10 + 81,
10 + 81, 11 + 81, 11, // 84

12, 11, 11 + 81,
11 + 81, 12 + 81, 12, // 90

13, 12, 12 + 81,
12 + 81, 13 + 81, 13, // 96

13, 13 + 81, 22 + 81,
22 + 81, 22, 13, // 102

19 + 81, 19, 20,
20, 20 + 81, 19 + 81, // 108

20 + 81, 20, 21,
21, 21 + 81, 20 + 81, // 114

24 + 81, 15 + 81, 15,
15, 24, 24 + 81, // 120

// third row of quads

16, 16 + 81, 25 + 81,
25 + 81, 25, 16, // 126

26 + 81, 17 + 81, 17,
17, 26, 26 + 81, // 132

17, 17 + 81, 18 + 81,
18 + 81, 18, 17, // 138

27 + 81, 27, 28,
28, 28 + 81, 27 + 81, // 144

19 + 81, 28 + 81, 28,
28, 19, 19 + 81, // 150

30, 30 + 81, 21 + 81,
21 + 81, 21, 30, // 156

30 + 81, 30, 31,
31, 31 + 81, 30 + 81, // 162

22, 22 + 81, 23 + 81,
23 + 81, 23, 22, // 168

23, 23 + 81, 32 + 81,
32 + 81, 32, 23, // 174

33 + 81, 24 + 81, 24,
24, 33, 33 + 81, // 180

// fourth row of quads

25, 25 + 81, 34 + 81,
34 + 81, 34, 25, // 186

35 + 81, 26 + 81, 26,
26, 35, 35 + 81, // 192

27, 27 + 81, 36 + 81,
36 + 81, 36, 27, // 198

40 + 81, 31 + 81, 31,
31, 40, 40 + 81, // 204

32, 32 + 81, 41 + 81,
41 + 81, 41, 32, // 210

42 + 81, 33 + 81, 33,
33, 42, 42 + 81, // 216

// fifth row of quads

34, 34 + 81, 43 + 81,
43 + 81, 43, 34, // 222

44 + 81, 35 + 81, 35,
35, 44, 44 + 81, // 228

36, 36 + 81, 37 + 81,
37 + 81, 37, 36, // 234

37, 37 + 81, 38 + 81,
38 + 81, 38, 37, // 240

38, 38 + 81, 39 + 81,
39 + 81, 39, 38, // 246

39, 39 + 81, 40 + 81,
40 + 81, 40, 39, // 252

45 + 81, 45, 46,
46, 46 + 81, 45 + 81, // 258

47 + 81, 47, 48,
48, 48 + 81, 47 + 81, // 264

41, 41 + 81, 49 + 81,
49 + 81, 49, 41, // 270

50 + 81, 42 + 81, 42,
42, 50, 50 + 81, // 276

// sixth row of quads

43, 43 + 81, 51 + 81,
51 + 81, 51, 43, // 282

52 + 81, 44 + 81, 44,
44, 52, 52 + 81, // 288

45, 45 + 81, 53 + 81,
53 + 81, 53, 45, // 294

54 + 81, 46 + 81, 46,
46, 54, 54 + 81, // 300

47, 47 + 81, 55 + 81,
55 + 81, 55, 47, // 306

56 + 81, 48 + 81, 48,
48, 56, 56 + 81, // 312

49, 49 + 81, 57 + 81,
57 + 81, 57, 49, // 318

58 + 81, 50 + 81, 50,
50, 58, 58 + 81, // 324

// seventh row of quads

51, 51 + 81, 59 + 81,
59 + 81, 59, 51, // 330

60 + 81, 52 + 81, 52,
52, 60, 60 + 81, // 336

60 + 81, 60, 61,
61, 61 + 81, 60 + 81, // 342

53, 53 + 81, 54 + 81,
54 + 81, 54, 53, // 348

55, 55 + 81, 56 + 81,
56 + 81, 56, 55, // 354

62 + 81, 62, 63,
63, 63 + 81, 62 + 81, // 360

57, 57 + 81, 63 + 81,
63 + 81, 63, 57, // 366

64 + 81, 58 + 81, 58,
58, 64, 64 + 81, // 372

// eighth row of quads

59, 59 + 81, 65 + 81,
65 + 81, 65, 59, // 378

67 + 81, 61 + 81, 61,
61, 67, 67 + 81, // 384

67 + 81, 67, 68,
68, 68 + 81, 67 + 81, // 390

68 + 81, 68, 69,
69, 69 + 81, 68 + 81, // 396

69 + 81, 69, 70,
70, 70 + 81, 69 + 81, // 402

70 + 81, 70, 71,
71, 71 + 81, 70 + 81, // 408

62, 62 + 81, 71 + 81,
71 + 81, 71, 62, // 414

73 + 81, 64 + 81, 64,
64, 73, 73 + 81, // 420

// ninth row of quads

65, 65 + 81, 66 + 81,
66 + 81, 66, 65, // 426

66, 66 + 81, 74 + 81,
74 + 81, 74, 66, // 432

74, 74 + 81, 75 + 81,
75 + 81, 75, 74, // 438

75, 75 + 81, 76 + 81,
76 + 81, 76, 75, // 444

76, 76 + 81, 77 + 81,
77 + 81, 77, 76, // 450

77, 77 + 81, 78 + 81,
78 + 81, 78, 77, // 456

78, 78 + 81, 79 + 81,
79 + 81, 79, 78, // 462

79, 79 + 81, 80 + 81,
80 + 81, 80, 79, // 468

80, 80 + 81, 72 + 81,
72 + 81, 72, 80, // 474

72, 72 + 81, 73 + 81,
73 + 81, 73, 72, // 480

// smiley left, right, top, bottom finish

// 1236

// 354 - 354 == 0; 2100 - 354 == 1746
// any character front
// [0, 116] is 117

// 471 - 354 == 117
// any character quad middle front
// [0, 95] is 96

// 567 - 354 == 213
// any character back
// [0, 116] is 117

// 684 - 354 == 330
// any character quad middle back
// [0, 95] is 96

// 780 - 354 == 426
// any character left front
// [0, 116] is 117

// 897 - 354 == 543
// any character left back
// [0, 116] is 117

// 1014 - 354 == 660
// any character quad middle left
// [0, 95] is 96

// 1110 - 354 == 756
// any character right front
// [0, 116] is 117

// 1227 - 354 == 873
// any character right back
// [0, 116] is 117

// 1344 - 354 == 990
// any character quad middle right
// [0, 95] is 96

// 1440 - 354 == 1086
// any character top front
// [0, 116] is

// 1557 - 354 == 1203
// any character top back
// [0, 116] is 117

// 1674 - 354 == 1320
// any character quad middle top
// [0, 95] is 96

// 1770 - 354 == 1416
// any character bottom front
// [0, 116] is 117

// 1887 - 354 == 1533
// any character bottom back
// [0, 116] is 117

// 2004 - 354 == 1650
// any character quad middle bottom
// [0, 95] is 96

// 2100 - 354 == 1746

#if 0
// DRAW_PIXEL
#define DP(x, y) \
(x + 9 * y) + 9, (x + 8 * y) + 234, (x + 9 * y), \
(x + 9 * y) + 10, (x + 8 * y) + 234, (x + 9 * y) + 9, \
(x + 9 * y) + 1, (x + 8 * y) + 234, (x + 9 * y) + 10, \
(x + 9 * y), (x + 8 * y) + 234, (x + 9 * y) + 1, \
(x + 9 * y) + 9 + 117, (x + 8 * y) + 330, (x + 9 * y) + 10 + 117, \
(x + 9 * y) + 117, (x + 8 * y) + 330, (x + 9 * y) + 9 + 117, \
(x + 9 * y) + 1 + 117, (x + 8 * y) + 330, (x + 9 * y) + 117, \
(x + 9 * y) + 10 + 117, (x + 8 * y) + 330, (x + 9 * y) + 1 + 117, \
(x + 9 * y) + 9, (x + 8 * y) + 426, (x + 9 * y) + 9 + 117, \
(x + 9 * y), (x + 8 * y) + 426, (x + 9 * y) + 9, \
(x + 9 * y) + 117, (x + 8 * y) + 426, (x + 9 * y), \
(x + 9 * y) + 9 + 117, (x + 8 * y) + 426, (x + 9 * y) + 117, \
(x + 9 * y) + 10, (x + 8 * y) + 522, (x + 9 * y) + 1, \
(x + 9 * y) + 10 + 117, (x + 8 * y) + 522, (x + 9 * y) + 10, \
(x + 9 * y) + 1 + 117, (x + 8 * y) + 522, (x + 9 * y) + 10 + 117, \
(x + 9 * y) + 1, (x + 8 * y) + 522, (x + 9 * y) + 1 + 117, \
(x + 9 * y) + 9 + 1, (x + 8 * y) + 618, (x + 9 * y) + 9 + 1 + 117, \
(x + 9 * y) + 9, (x + 8 * y) + 618, (x + 9 * y) + 9 + 1, \
(x + 9 * y) + 9 + 117, (x + 8 * y) + 618, (x + 9 * y) + 9, \
(x + 9 * y) + 9 + 1 + 117, (x + 8 * y) + 618, (x + 9 * y) + 9 + 117, \
(x + 9 * y) + 1, (x + 8 * y) + 714, (x + 9 * y), \
(x + 9 * y) + 1 + 117, (x + 8 * y) + 714, (x + 9 * y) + 1, \
(x + 9 * y) + 117, (x + 8 * y) + 714, (x + 9 * y) + 1 + 117, \
(x + 9 * y), (x + 8 * y) + 714, (x + 9 * y) + 117

// left

// (x + 9 * y) + 9, (x + 8 * y) + 426, (x + 9 * y) + 9 + 117,
// (x + 9 * y), (x + 8 * y) + 426, (x + 9 * y) + 9,
//
// (x + 9 * y) + 117, (x + 8 * y) + 426, (x + 9 * y),
// (x + 9 * y) + 9 + 117, (x + 8 * y) + 426, (x + 9 * y) + 117

9, 426, 9 + 117,
0, 426, 9, // 6

0 + 117, 426, 0,
9 + 117, 426, 0 + 117, // 12

// front

// (x + 9 * y) + 9, (x + 8 * y) + 234, (x + 9 * y),
// (x + 9 * y) + 10, (x + 8 * y) + 234, (x + 9 * y) + 9,
//
// (x + 9 * y) + 1, (x + 8 * y) + 234, (x + 9 * y) + 10,
// (x + 9 * y), (x + 8 * y) + 234, (x + 9 * y) + 1

9, 234, 0,
10, 234, 9, // 18

1, 234, 10,
0, 234, 1, // 24

// back

// (x + 9 * y) + 9 + 117, (x + 8 * y) + 330, (x + 9 * y) + 10 + 117,
// (x + 9 * y) + 117, (x + 8 * y) + 330, (x + 9 * y) + 9 + 117,
//
// (x + 9 * y) + 1 + 117, (x + 8 * y) + 330, (x + 9 * y) + 117,
// (x + 9 * y) + 10 + 117, (x + 8 * y) + 330, (x + 9 * y) + 1 + 117

9 + 117, 330, 10 + 117,
0 + 117, 330, 9 + 117, // 30

1 + 117, 330, 0 + 117,
10 + 117, 330, 1 + 117, // 36

// bottom

// (x + 9 * y) + 1, (x + 8 * y) + 714, (x + 9 * y),
// (x + 9 * y) + 1 + 117, (x + 8 * y) + 714, (x + 9 * y) + 1,
//
// (x + 9 * y) + 117, (x + 8 * y) + 714, (x + 9 * y) + 1 + 117,
// (x + 9 * y), (x + 8 * y) + 714, (x + 9 * y) + 117

1, 714, 0,
1 + 117, 714, 1, // 42

0 + 117, 714, 1 + 117,
0, 714, 0 + 117, // 48

// top

// (x + 9 * y) + 9 + 1, (x + 8 * y) + 618, (x + 9 * y) + 9 + 1 + 117,
// (x + 9 * y) + 9, (x + 8 * y) + 618, (x + 9 * y) + 9 + 1,
//
// (x + 9 * y) + 9 + 117, (x + 8 * y) + 618, (x + 9 * y) + 9,
// (x + 9 * y) + 9 + 1 + 117, (x + 8 * y) + 618, (x + 9 * y) + 9 + 117

9 + 1, 618, 9 + 1 + 117,
9 + 0, 618, 9 + 1, // 54

9 + 0 + 117, 618, 9 + 0,
9 + 1 + 117, 618, 9 + 0 + 117, // 60

// right

// (x + 9 * y) + 10, (x + 8 * y) + 522, (x + 9 * y) + 1,
// (x + 9 * y) + 10 + 117, (x + 8 * y) + 522, (x + 9 * y) + 10,
//
// (x + 9 * y) + 1 + 117, (x + 8 * y) + 522, (x + 9 * y) + 10 + 117,
// (x + 9 * y) + 1, (x + 8 * y) + 522, (x + 9 * y) + 1 + 117

10, 522, 1,
10 + 117, 522, 10, // 66

1 + 117, 522, 10 + 117,
1, 522, 1 + 117, // 72
#endif

// .XXXXXX. 6 6
// XX....XX 4 10
// X......X 2 12
// X.X..X.X 4 16
// X......X 2 18
// X.XXXX.X 6 24
// X..XX..X 4 28
// .XXXXXX. 6 34

#if 0
/**/      DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8), /**/
DP(0, 7), DP(1, 7), /**/      /**/      /**/      /**/      DP(6, 7), DP(7, 7),
DP(0, 6), /**/      /**/      /**/      /**/      /**/      /**/      DP(7, 6),
DP(0, 5), /**/      DP(2, 5), /**/      /**/      DP(5, 5), /**/      DP(7, 5),
DP(0, 4), /**/      /**/      /**/      /**/      /**/      /**/      DP(7, 4),
DP(0, 3), /**/      DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), /**/      DP(7, 3),
DP(0, 2), /**/      /**/      DP(3, 2), DP(4, 2), /**/      /**/      DP(7, 2),
DP(0, 1), DP(1, 1), /**/      /**/      /**/      /**/      DP(6, 1), DP(7, 1),
/**/      DP(1, 0), DP(2, 0), DP(3, 0), DP(4, 0), DP(5, 0), DP(6, 0)  /**/
#endif

// DRAW_PIXEL

#if 1

#define DP(x, y) \
(x + 9 * y) + 9, (x + 8 * y) + 117, (x + 9 * y), \
(x + 9 * y) + 10, (x + 8 * y) + 117, (x + 9 * y) + 9, \
(x + 9 * y) + 1, (x + 8 * y) + 117, (x + 9 * y) + 10, \
(x + 9 * y), (x + 8 * y) + 117, (x + 9 * y) + 1, \
(x + 9 * y) + 213, (x + 8 * y) + 330, (x + 9 * y) + 222, \
(x + 9 * y) + 222, (x + 8 * y) + 330, (x + 9 * y) + 223, \
(x + 9 * y) + 223, (x + 8 * y) + 330, (x + 9 * y) + 214, \
(x + 9 * y) + 214, (x + 8 * y) + 330, (x + 9 * y) + 213, \
(x + 9 * y) + 426, (x + 8 * y) + 660, (x + 9 * y) + 435, \
(x + 9 * y) + 435, (x + 8 * y) + 660, (x + 9 * y) + 552, \
(x + 9 * y) + 552, (x + 8 * y) + 660, (x + 9 * y) + 543, \
(x + 9 * y) + 543, (x + 8 * y) + 660, (x + 9 * y) + 426, \
(x + 9 * y) + 766, (x + 8 * y) + 990, (x + 9 * y) + 757, \
(x + 9 * y) + 883, (x + 8 * y) + 990, (x + 9 * y) + 766, \
(x + 9 * y) + 874, (x + 8 * y) + 990, (x + 9 * y) + 883, \
(x + 9 * y) + 757, (x + 8 * y) + 990, (x + 9 * y) + 874, \
(x + 9 * y) + 1095, (x + 8 * y) + 1320, (x + 9 * y) + 1096, \
(x + 9 * y) + 1212, (x + 8 * y) + 1320, (x + 9 * y) + 1095, \
(x + 9 * y) + 1213, (x + 8 * y) + 1320, (x + 9 * y) + 1212, \
(x + 9 * y) + 1096, (x + 8 * y) + 1320, (x + 9 * y) + 1213, \
(x + 9 * y) + 1417, (x + 8 * y) + 1650, (x + 9 * y) + 1416, \
(x + 9 * y) + 1416, (x + 8 * y) + 1650, (x + 9 * y) + 1533, \
(x + 9 * y) + 1533, (x + 8 * y) + 1650, (x + 9 * y) + 1534, \
(x + 9 * y) + 1534, (x + 8 * y) + 1650, (x + 9 * y) + 1417

#else

#define DW(x, y) \
(x + 9 * y) + 9, (x + 8 * y) + 117, (x + 9 * y), \
(x + 9 * y) + 10, (x + 8 * y) + 117, (x + 9 * y) + 9, \
(x + 9 * y) + 1, (x + 8 * y) + 117, (x + 9 * y) + 10, \
(x + 9 * y), (x + 8 * y) + 117, (x + 9 * y) + 1, \
(x + 9 * y) + 213, (x + 8 * y) + 330, (x + 9 * y) + 222, \
(x + 9 * y) + 222, (x + 8 * y) + 330, (x + 9 * y) + 223, \
(x + 9 * y) + 223, (x + 8 * y) + 330, (x + 9 * y) + 214, \
(x + 9 * y) + 214, (x + 8 * y) + 330, (x + 9 * y) + 213, \
(x + 9 * y) + 426, (x + 8 * y) + 660, (x + 9 * y) + 435, \
(x + 9 * y) + 435, (x + 8 * y) + 660, (x + 9 * y) + 552, \
(x + 9 * y) + 552, (x + 8 * y) + 660, (x + 9 * y) + 543, \
(x + 9 * y) + 543, (x + 8 * y) + 660, (x + 9 * y) + 426, \
(x + 9 * y) + 766, (x + 8 * y) + 990, (x + 9 * y) + 757, \
(x + 9 * y) + 883, (x + 8 * y) + 990, (x + 9 * y) + 766, \
(x + 9 * y) + 874, (x + 8 * y) + 990, (x + 9 * y) + 883, \
(x + 9 * y) + 757, (x + 8 * y) + 990, (x + 9 * y) + 874, \
(x + 9 * y) + 1095, (x + 8 * y) + 1320, (x + 9 * y) + 1096, \
(x + 9 * y) + 1212, (x + 8 * y) + 1320, (x + 9 * y) + 1095, \
(x + 9 * y) + 1213, (x + 8 * y) + 1320, (x + 9 * y) + 1212, \
(x + 9 * y) + 1096, (x + 8 * y) + 1320, (x + 9 * y) + 1213, \
(x + 9 * y) + 1417, (x + 8 * y) + 1650, (x + 9 * y) + 1416, \
(x + 9 * y) + 1416, (x + 8 * y) + 1650, (x + 9 * y) + 1533, \
(x + 9 * y) + 1533, (x + 8 * y) + 1650, (x + 9 * y) + 1534, \
(x + 9 * y) + 1534, (x + 8 * y) + 1650, (x + 9 * y) + 1417

#define DG(x, y) \
(x + 9 * y) + 9 + 1746, (x + 8 * y) + 117 + 1746, (x + 9 * y) + 1746, \
(x + 9 * y) + 10 + 1746, (x + 8 * y) + 117 + 1746, (x + 9 * y) + 9 + 1746, \
(x + 9 * y) + 1 + 1746, (x + 8 * y) + 117 + 1746, (x + 9 * y) + 10 + 1746, \
(x + 9 * y) + 1746, (x + 8 * y) + 117 + 1746, (x + 9 * y) + 1 + 1746, \
(x + 9 * y) + 213 + 1746, (x + 8 * y) + 330 + 1746, (x + 9 * y) + 222 + 1746, \
(x + 9 * y) + 222 + 1746, (x + 8 * y) + 330 + 1746, (x + 9 * y) + 223 + 1746, \
(x + 9 * y) + 223 + 1746, (x + 8 * y) + 330 + 1746, (x + 9 * y) + 214 + 1746, \
(x + 9 * y) + 214 + 1746, (x + 8 * y) + 330 + 1746, (x + 9 * y) + 213 + 1746, \
(x + 9 * y) + 426 + 1746, (x + 8 * y) + 660 + 1746, (x + 9 * y) + 435 + 1746, \
(x + 9 * y) + 435 + 1746, (x + 8 * y) + 660 + 1746, (x + 9 * y) + 552 + 1746, \
(x + 9 * y) + 552 + 1746, (x + 8 * y) + 660 + 1746, (x + 9 * y) + 543 + 1746, \
(x + 9 * y) + 543 + 1746, (x + 8 * y) + 660 + 1746, (x + 9 * y) + 426 + 1746, \
(x + 9 * y) + 766 + 1746, (x + 8 * y) + 990 + 1746, (x + 9 * y) + 757 + 1746, \
(x + 9 * y) + 883 + 1746, (x + 8 * y) + 990 + 1746, (x + 9 * y) + 766 + 1746, \
(x + 9 * y) + 874 + 1746, (x + 8 * y) + 990 + 1746, (x + 9 * y) + 883 + 1746, \
(x + 9 * y) + 757 + 1746, (x + 8 * y) + 990 + 1746, (x + 9 * y) + 874 + 1746, \
(x + 9 * y) + 1095 + 1746, (x + 8 * y) + 1320 + 1746, (x + 9 * y) + 1096 + 1746, \
(x + 9 * y) + 1212 + 1746, (x + 8 * y) + 1320 + 1746, (x + 9 * y) + 1095 + 1746, \
(x + 9 * y) + 1213 + 1746, (x + 8 * y) + 1320 + 1746, (x + 9 * y) + 1212 + 1746, \
(x + 9 * y) + 1096 + 1746, (x + 8 * y) + 1320 + 1746, (x + 9 * y) + 1213 + 1746, \
(x + 9 * y) + 1417 + 1746, (x + 8 * y) + 1650 + 1746, (x + 9 * y) + 1416 + 1746, \
(x + 9 * y) + 1416 + 1746, (x + 8 * y) + 1650 + 1746, (x + 9 * y) + 1533 + 1746, \
(x + 9 * y) + 1533 + 1746, (x + 8 * y) + 1650 + 1746, (x + 9 * y) + 1534 + 1746, \
(x + 9 * y) + 1534 + 1746, (x + 8 * y) + 1650 + 1746, (x + 9 * y) + 1417 + 1746

#endif

#if 0
// front

// (x + 9 * y) + 9, (x + 8 * y) + 117, (x + 9 * y),
// (x + 9 * y) + 10, (x + 8 * y) + 117, (x + 9 * y) + 9,
//
// (x + 9 * y) + 1, (x + 8 * y) + 117, (x + 9 * y) + 10,
// (x + 9 * y), (x + 8 * y) + 117, (x + 9 * y) + 1

9, 117, 0,
10, 117, 9, // 6

1, 117, 10,
0, 117, 1, // 12

// back

// (x + 9 * y) + 213, (x + 8 * y) + 330, (x + 9 * y) + 222,
// (x + 9 * y) + 222, (x + 8 * y) + 330, (x + 9 * y) + 223,
//
// (x + 9 * y) + 223, (x + 8 * y) + 330, (x + 9 * y) + 214,
// (x + 9 * y) + 214, (x + 8 * y) + 330, (x + 9 * y) + 213

0 + 213, 330, 9 + 213,
9 + 213, 330, 10 + 213, // 18

10 + 213, 330, 1 + 213,
1 + 213, 330, 0 + 213, // 24

// left

// (x + 9 * y) + 426, (x + 8 * y) + 660, (x + 9 * y) + 435,
// (x + 9 * y) + 435, (x + 8 * y) + 660, (x + 9 * y) + 552,
//
// (x + 9 * y) + 552, (x + 8 * y) + 660, (x + 9 * y) + 543,
// (x + 9 * y) + 543, (x + 8 * y) + 660, (x + 9 * y) + 426

0 + 426, 660, 9 + 426,
9 + 426, 660, 9 + 543, // 30

9 + 543, 660, 0 + 543,
0 + 543, 660, 0 + 426, // 36

// right

// (x + 9 * y) + 766, (x + 8 * y) + 990, (x + 9 * y) + 757,
// (x + 9 * y) + 883, (x + 8 * y) + 990, (x + 9 * y) + 766,
//
// (x + 9 * y) + 874, (x + 8 * y) + 990, (x + 9 * y) + 883,
// (x + 9 * y) + 757, (x + 8 * y) + 990, (x + 9 * y) + 874

10 + 756, 990, 1 + 756,
10 + 873, 990, 10 + 756, // 42

1 + 873, 990, 10 + 873,
1 + 756, 990, 1 + 873, // 48

// top

// (x + 9 * y) + 1095, (x + 8 * y) + 1320, (x + 9 * y) + 1096,
// (x + 9 * y) + 1212, (x + 8 * y) + 1320, (x + 9 * y) + 1095,
//
// (x + 9 * y) + 1213, (x + 8 * y) + 1320, (x + 9 * y) + 1212,
// (x + 9 * y) + 1096, (x + 8 * y) + 1320, (x + 9 * y) + 1213

9 + 1086, 1320, 10 + 1086,
9 + 1203, 1320, 9 + 1086, // 54

10 + 1203, 1320, 9 + 1203,
10 + 1086, 1320, 10 + 1203, // 60

// bottom

// (x + 9 * y) + 1417, (x + 8 * y) + 1650, (x + 9 * y) + 1416,
// (x + 9 * y) + 1416, (x + 8 * y) + 1650, (x + 9 * y) + 1533,
//
// (x + 9 * y) + 1533, (x + 8 * y) + 1650, (x + 9 * y) + 1534,
// (x + 9 * y) + 1534, (x + 8 * y) + 1650, (x + 9 * y) + 1417

1 + 1416, 1650, 0 + 1416,
0 + 1416, 1650, 0 + 1533, // 66

0 + 1533, 1650, 1 + 1533,
1 + 1533, 1650, 1 + 1416, // 72
#endif

// 1236

#if 0
// character 0

72 * 0

// ........
// ........
// ........
// ........
// ........
// ........
// ........
// ........
// ........
// ........
// ........
// ........

/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
/*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */  /*     */
#endif

// 1236

#if 1
// 0

// 1
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(6, 9), DP(7, 9),
DP(0, 8), DP(7, 8),
DP(0, 7), DP(2, 7), DP(5, 7), DP(7, 7),
DP(0, 6), DP(7, 6),
DP(0, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(7, 5),
DP(0, 4), DP(3, 4), DP(4, 4), DP(7, 4),
DP(0, 3), DP(1, 3), DP(6, 3), DP(7, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 2
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9), DP(6, 9), DP(7, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8), DP(7, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(6, 7), DP(7, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(0, 5), DP(1, 5), DP(6, 5), DP(7, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3), DP(7, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 3
DP(1, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),
DP(2, 3), DP(3, 3), DP(4, 3),
DP(3, 2),

// 4
DP(3, 10),
DP(2, 9), DP(3, 9), DP(4, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(2, 4), DP(3, 4), DP(4, 4),
DP(3, 3),

// 5
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5), DP(7, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 6
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 7
DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),

// 8
DP(0, 11), DP(1, 11), DP(2, 11), DP(3, 11), DP(4, 11), DP(5, 11), DP(6, 11), DP(7, 11),
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10), DP(7, 10),
DP(0, 9), DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9), DP(6, 9), DP(7, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8), DP(7, 8),
DP(0, 7), DP(1, 7), DP(6, 7), DP(7, 7),
DP(0, 6), DP(7, 6),
DP(0, 5), DP(7, 5),
DP(0, 4), DP(1, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3), DP(7, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2), DP(7, 2),
DP(0, 1), DP(1, 1), DP(2, 1), DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1), DP(7, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0), DP(4, 0), DP(5, 0), DP(6, 0), DP(7, 0),

// 9
DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(6, 6),
DP(1, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3),
DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 10
DP(0, 11), DP(1, 11), DP(2, 11), DP(3, 11), DP(4, 11), DP(5, 11), DP(6, 11), DP(7, 11),
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10), DP(7, 10),
DP(0, 9), DP(1, 9), DP(6, 9), DP(7, 9),
DP(0, 8), DP(7, 8),
DP(0, 7), DP(3, 7), DP(4, 7), DP(7, 7),
DP(0, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(7, 6),
DP(0, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(7, 5),
DP(0, 4), DP(3, 4), DP(4, 4), DP(7, 4),
DP(0, 3), DP(7, 3),
DP(0, 2), DP(1, 2), DP(6, 2), DP(7, 2),
DP(0, 1), DP(1, 1), DP(2, 1), DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1), DP(7, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0), DP(4, 0), DP(5, 0), DP(6, 0), DP(7, 0),

// 11
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(4, 9), DP(5, 9), DP(6, 9),
DP(2, 8), DP(3, 8), DP(4, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 12
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(3, 5), DP(4, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),

// 13
DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10), DP(7, 10),
DP(3, 9), DP(4, 9), DP(7, 9),
DP(3, 8), DP(4, 8), DP(7, 8),
DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2),

// 14
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10), DP(7, 10),
DP(1, 9), DP(2, 9), DP(6, 9), DP(7, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8), DP(7, 8),
DP(1, 7), DP(2, 7), DP(6, 7), DP(7, 7),
DP(1, 6), DP(2, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(6, 5), DP(7, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3), DP(7, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(0, 1), DP(1, 1),

// 15
DP(3, 9), DP(4, 9),
DP(0, 8), DP(1, 8), DP(3, 8), DP(4, 8), DP(6, 8), DP(7, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5), DP(7, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(3, 3), DP(4, 3), DP(6, 3), DP(7, 3),
DP(3, 2), DP(4, 2),

// 16
DP(0, 10),
DP(0, 9), DP(1, 9),
DP(0, 8), DP(1, 8), DP(2, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4), DP(2, 4),
DP(0, 3), DP(1, 3),
DP(0, 2),

// 17
DP(6, 10),
DP(5, 9), DP(6, 9),
DP(4, 8), DP(5, 8), DP(6, 8),
DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(4, 4), DP(5, 4), DP(6, 4),
DP(5, 3), DP(6, 3),
DP(6, 2),

// 18
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(3, 2), DP(4, 2),

// 19
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),

// 20
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10), DP(7, 10),
DP(0, 9), DP(1, 9), DP(3, 9), DP(4, 9), DP(6, 9), DP(7, 9),
DP(0, 8), DP(1, 8), DP(3, 8), DP(4, 8), DP(6, 8), DP(7, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(6, 7), DP(7, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(6, 6), DP(7, 6),
DP(3, 5), DP(4, 5), DP(6, 5), DP(7, 5),
DP(3, 4), DP(4, 4), DP(6, 4), DP(7, 4),
DP(3, 3), DP(4, 3), DP(6, 3), DP(7, 3),
DP(3, 2), DP(4, 2), DP(6, 2), DP(7, 2),

// 21
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(6, 9), DP(7, 9),
DP(2, 8), DP(3, 8),
DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),
DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1),

// 22
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 23
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(3, 2), DP(4, 2),
DP(1, 1), DP(2, 1), DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1),

// 24
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),

// 25
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(3, 2), DP(4, 2),

// 26
DP(3, 8), DP(4, 8),
DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(4, 5), DP(5, 5),
DP(3, 4), DP(4, 4),

// 27
DP(2, 8), DP(3, 8),
DP(1, 7), DP(2, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5),
DP(2, 4), DP(3, 4),

// 28
DP(0, 7), DP(1, 7),
DP(0, 6), DP(1, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),

// 29
DP(2, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(2, 4), DP(5, 4),

// 30
DP(3, 9),
DP(3, 8),
DP(2, 7), DP(3, 7), DP(4, 7),
DP(2, 6), DP(3, 6), DP(4, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 31
DP(0, 9), DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(2, 5), DP(3, 5), DP(4, 5),
DP(2, 4), DP(3, 4), DP(4, 4),
DP(3, 3),
DP(3, 2),

// 32

// 33
DP(2, 10), DP(3, 10),
DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(2, 6), DP(3, 6),
DP(2, 5), DP(3, 5),
DP(2, 3), DP(3, 3),
DP(2, 2), DP(3, 2),

// 34
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(2, 7), DP(5, 7),

// 35
DP(1, 10), DP(2, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(4, 2), DP(5, 2),

// 36
DP(2, 11), DP(3, 11),
DP(2, 10), DP(3, 10),
DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8),
DP(0, 7), DP(1, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(4, 5), DP(5, 5),
DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3),
DP(2, 2), DP(3, 2),
DP(2, 1), DP(3, 1),

// 37
DP(0, 8), DP(1, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(3, 6), DP(4, 6),
DP(2, 5), DP(3, 5),
DP(1, 4), DP(2, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(4, 2), DP(5, 2),

// 38
DP(1, 10), DP(2, 10), DP(3, 10),
DP(0, 9), DP(1, 9), DP(3, 9), DP(4, 9),
DP(0, 8), DP(1, 8), DP(3, 8), DP(4, 8),
DP(1, 7), DP(2, 7), DP(3, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 39
DP(2, 10), DP(3, 10),
DP(2, 9), DP(3, 9),
DP(2, 8), DP(3, 8),
DP(1, 7), DP(2, 7),

// 40
DP(4, 10), DP(5, 10),
DP(3, 9), DP(4, 9),
DP(2, 8), DP(3, 8),
DP(1, 7), DP(2, 7),
DP(1, 6), DP(2, 6),
DP(1, 5), DP(2, 5),
DP(2, 4), DP(3, 4),
DP(3, 3), DP(4, 3),
DP(4, 2), DP(5, 2),

// 41
DP(1, 10), DP(2, 10),
DP(2, 9), DP(3, 9),
DP(3, 8), DP(4, 8),
DP(4, 7), DP(5, 7),
DP(4, 6), DP(5, 6),
DP(4, 5), DP(5, 5),
DP(3, 4), DP(4, 4),
DP(2, 3), DP(3, 3),
DP(1, 2), DP(2, 2),

// 42
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),

// 43
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),

// 44
DP(2, 3), DP(3, 3), DP(4, 3),
DP(2, 2), DP(3, 2), DP(4, 2),
DP(1, 1), DP(2, 1),

// 45
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),

// 46
DP(2, 3), DP(3, 3), DP(4, 3),
DP(2, 2), DP(3, 2), DP(4, 2),

// 47
DP(6, 9),
DP(5, 8), DP(6, 8),
DP(4, 7), DP(5, 7),
DP(3, 6), DP(4, 6),
DP(2, 5), DP(3, 5),
DP(1, 4), DP(2, 4),
DP(0, 3), DP(1, 3),
DP(0, 2),

// 48
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(3, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 49
DP(3, 10),
DP(2, 9), DP(3, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8),
DP(2, 7), DP(3, 7),
DP(2, 6), DP(3, 6),
DP(2, 5), DP(3, 5),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 50
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(4, 7), DP(5, 7),
DP(3, 6), DP(4, 6),
DP(2, 5), DP(3, 5),
DP(1, 4), DP(2, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 51
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(4, 8), DP(5, 8),
DP(4, 7), DP(5, 7),
DP(2, 6), DP(3, 6), DP(4, 6),
DP(4, 5), DP(5, 5),
DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 52
DP(4, 10), DP(5, 10),
DP(3, 9), DP(4, 9), DP(5, 9),
DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(4, 4), DP(5, 4),
DP(4, 3), DP(5, 3),
DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 53
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9),
DP(0, 8), DP(1, 8),
DP(0, 7), DP(1, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(4, 5), DP(5, 5),
DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 54
DP(2, 10), DP(3, 10), DP(4, 10),
DP(1, 9), DP(2, 9),
DP(0, 8), DP(1, 8),
DP(0, 7), DP(1, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 55
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(5, 7), DP(6, 7),
DP(4, 6), DP(5, 6),
DP(3, 5), DP(4, 5),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),
DP(2, 2), DP(3, 2),

// 56
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 57
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(2, 3), DP(3, 3),
DP(1, 2), DP(2, 2), DP(3, 2),

// 58
DP(2, 8), DP(3, 8), DP(4, 8),
DP(2, 7), DP(3, 7), DP(4, 7),
DP(2, 4), DP(3, 4), DP(4, 4),
DP(2, 3), DP(3, 3), DP(4, 3),

// 59
DP(2, 8), DP(3, 8), DP(4, 8),
DP(2, 7), DP(3, 7), DP(4, 7),
DP(2, 4), DP(3, 4), DP(4, 4),
DP(2, 3), DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(2, 1), DP(3, 1),

// 60
DP(4, 10), DP(5, 10),
DP(3, 9), DP(4, 9),
DP(2, 8), DP(3, 8),
DP(1, 7), DP(2, 7),
DP(0, 6), DP(1, 6),
DP(1, 5), DP(2, 5),
DP(2, 4), DP(3, 4),
DP(3, 3), DP(4, 3),
DP(4, 2), DP(5, 2),

// 61
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),

// 62
DP(1, 10), DP(2, 10),
DP(2, 9), DP(3, 9),
DP(3, 8), DP(4, 8),
DP(4, 7), DP(5, 7),
DP(5, 6), DP(6, 6),
DP(4, 5), DP(5, 5),
DP(3, 4), DP(4, 4),
DP(2, 3), DP(3, 3),
DP(1, 2), DP(2, 2),

// 63
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(4, 8), DP(5, 8),
DP(3, 7), DP(4, 7),
DP(2, 6), DP(3, 6),
DP(2, 5), DP(3, 5),
DP(2, 3), DP(3, 3),
DP(2, 2), DP(3, 2),

// 64
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 65
DP(2, 10), DP(3, 10),
DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 66
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 67
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7),
DP(0, 6), DP(1, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 68
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 69
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(6, 9),
DP(1, 8), DP(2, 8),
DP(1, 7), DP(2, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(5, 5),
DP(1, 4), DP(2, 4),
DP(1, 3), DP(2, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 70
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(5, 5),
DP(1, 4), DP(2, 4),
DP(1, 3), DP(2, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2),

// 71
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7),
DP(0, 6), DP(1, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 72
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 73
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9),
DP(2, 8), DP(3, 8),
DP(2, 7), DP(3, 7),
DP(2, 6), DP(3, 6),
DP(2, 5), DP(3, 5),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 74
DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(4, 9), DP(5, 9),
DP(4, 8), DP(5, 8),
DP(4, 7), DP(5, 7),
DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 75
DP(0, 10), DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(1, 5), DP(2, 5), DP(4, 5), DP(5, 5),
DP(1, 4), DP(2, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),

// 76
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10),
DP(1, 9), DP(2, 9),
DP(1, 8), DP(2, 8),
DP(1, 7), DP(2, 7),
DP(1, 6), DP(2, 6),
DP(1, 5), DP(2, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 77
DP(0, 10), DP(1, 10), DP(5, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(3, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(5, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(5, 2), DP(6, 2),

// 78
DP(0, 10), DP(1, 10), DP(5, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(5, 2), DP(6, 2),

// 79
DP(2, 10), DP(3, 10), DP(4, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(2, 2), DP(3, 2), DP(4, 2),

// 80
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4),
DP(1, 3), DP(2, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2),

// 81
DP(2, 10), DP(3, 10), DP(4, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(4, 2), DP(5, 2),
DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1),

// 82
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(4, 5), DP(5, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),

// 83
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7),
DP(1, 6), DP(2, 6), DP(3, 6),
DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 84
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(2, 9), DP(3, 9), DP(5, 9),
DP(2, 8), DP(3, 8),
DP(2, 7), DP(3, 7),
DP(2, 6), DP(3, 6),
DP(2, 5), DP(3, 5),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 85
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 86
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3),
DP(2, 2), DP(3, 2),

// 87
DP(0, 10), DP(1, 10), DP(5, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(3, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(4, 2), DP(5, 2),

// 88
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(2, 6), DP(3, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 89
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(2, 5), DP(3, 5),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 90
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(2, 6), DP(3, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 91
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(2, 9), DP(3, 9),
DP(2, 8), DP(3, 8),
DP(2, 7), DP(3, 7),
DP(2, 6), DP(3, 6),
DP(2, 5), DP(3, 5),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),
DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 92
DP(0, 9),
DP(0, 8), DP(1, 8),
DP(1, 7), DP(2, 7),
DP(2, 6), DP(3, 6),
DP(3, 5), DP(4, 5),
DP(4, 4), DP(5, 4),
DP(5, 3), DP(6, 3),
DP(6, 2),

// 93
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(4, 9), DP(5, 9),
DP(4, 8), DP(5, 8),
DP(4, 7), DP(5, 7),
DP(4, 6), DP(5, 6),
DP(4, 5), DP(5, 5),
DP(4, 4), DP(5, 4),
DP(4, 3), DP(5, 3),
DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 94
DP(3, 11),
DP(2, 10), DP(3, 10), DP(4, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),

// 95
DP(0, 1), DP(1, 1), DP(2, 1), DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1), DP(7, 1),

// 96
DP(2, 11), DP(3, 11),
DP(2, 10), DP(3, 10),
DP(3, 9), DP(4, 9),

// 97
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 98
DP(0, 10), DP(1, 10), DP(2, 10),
DP(1, 9), DP(2, 9),
DP(1, 8), DP(2, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 99
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 100
DP(3, 10), DP(4, 10), DP(5, 10),
DP(4, 9), DP(5, 9),
DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 101
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 102
DP(2, 10), DP(3, 10), DP(4, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8),
DP(1, 7), DP(2, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4),
DP(1, 3), DP(2, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2),

// 103
DP(1, 7), DP(2, 7), DP(3, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(4, 2), DP(5, 2),
DP(0, 1), DP(1, 1), DP(4, 1), DP(5, 1),
DP(1, 0), DP(2, 0), DP(3, 0), DP(4, 0),

// 104
DP(0, 10), DP(1, 10), DP(2, 10),
DP(1, 9), DP(2, 9),
DP(1, 8), DP(2, 8),
DP(1, 7), DP(2, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),

// 105
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 106
DP(4, 10), DP(5, 10),
DP(4, 9), DP(5, 9),
DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(4, 6), DP(5, 6),
DP(4, 5), DP(5, 5),
DP(4, 4), DP(5, 4),
DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),
DP(0, 1), DP(1, 1), DP(4, 1), DP(5, 1),
DP(1, 0), DP(2, 0), DP(3, 0), DP(4, 0),

// 107
DP(0, 10), DP(1, 10), DP(2, 10),
DP(1, 9), DP(2, 9),
DP(1, 8), DP(2, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5),
DP(1, 4), DP(2, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),

// 108
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 109
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(3, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(5, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(3, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(5, 2), DP(6, 2),

// 110
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 111
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 112
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),
DP(1, 1), DP(2, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0),

// 113
DP(1, 7), DP(2, 7), DP(3, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),
DP(4, 1), DP(5, 1),
DP(3, 0), DP(4, 0), DP(5, 0), DP(6, 0),

// 114
DP(0, 7), DP(1, 7), DP(2, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4),
DP(1, 3), DP(2, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2),

// 115
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5),
DP(3, 4), DP(4, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 116
DP(2, 9),
DP(1, 8), DP(2, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(2, 2), DP(3, 2), DP(4, 2),

// 117
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 118
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3),
DP(2, 2), DP(3, 2),

// 119
DP(0, 7), DP(1, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(4, 2), DP(5, 2),

// 120
DP(0, 7), DP(1, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(4, 6), DP(5, 6),
DP(2, 5), DP(3, 5), DP(4, 5),
DP(2, 4), DP(3, 4), DP(4, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(5, 2), DP(6, 2),

// 121
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(4, 2), DP(5, 2),
DP(3, 1), DP(4, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0),

// 122
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(4, 6), DP(5, 6),
DP(3, 5), DP(4, 5),
DP(1, 4), DP(2, 4),
DP(0, 3), DP(1, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 123
DP(3, 10), DP(4, 10), DP(5, 10),
DP(2, 9), DP(3, 9),
DP(2, 8), DP(3, 8),
DP(1, 7), DP(2, 7),
DP(0, 6), DP(1, 6),
DP(1, 5), DP(2, 5),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),
DP(3, 2), DP(4, 2), DP(5, 2),

// 124
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),

// 125
DP(0, 10), DP(1, 10), DP(2, 10),
DP(2, 9), DP(3, 9),
DP(2, 8), DP(3, 8),
DP(3, 7), DP(4, 7),
DP(4, 6), DP(5, 6),
DP(3, 5), DP(4, 5),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),
DP(0, 2), DP(1, 2), DP(2, 2),

// 126
DP(1, 10), DP(2, 10), DP(3, 10), DP(6, 10), DP(7, 10),
DP(0, 9), DP(1, 9), DP(3, 9), DP(4, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8), DP(6, 8),

// 127
DP(3, 8),
DP(2, 7), DP(3, 7), DP(4, 7),
DP(1, 6), DP(2, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(5, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3),

// 128
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7),
DP(0, 6), DP(1, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),
DP(2, 1), DP(3, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0),

// 129
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 130
DP(4, 11), DP(5, 11),
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 131
DP(2, 11), DP(3, 11),
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 132
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 133
DP(0, 11), DP(1, 11),
DP(1, 10), DP(2, 10),
DP(2, 9), DP(3, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 134
DP(2, 11), DP(3, 11), DP(4, 11),
DP(1, 10), DP(2, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(2, 8), DP(3, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 135
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),
DP(2, 1), DP(3, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0),

// 136
DP(2, 11), DP(3, 11),
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 137
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 138
DP(0, 11), DP(1, 11),
DP(1, 10), DP(2, 10),
DP(2, 9), DP(3, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 139
DP(1, 10), DP(2, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 140
DP(3, 11),
DP(2, 10), DP(3, 10), DP(4, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 141
DP(1, 11), DP(2, 11),
DP(2, 10), DP(3, 10),
DP(3, 9), DP(4, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 142
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(2, 8), DP(3, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 143
DP(1, 11), DP(2, 11), DP(3, 11), DP(4, 11),
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 144
DP(4, 11), DP(5, 11),
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(5, 7),
DP(0, 6), DP(1, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 145
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(3, 6), DP(4, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5), DP(7, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(4, 4),
DP(0, 3), DP(1, 3), DP(3, 3), DP(4, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(4, 2), DP(5, 2), DP(6, 2), DP(7, 2),

// 146
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9),
DP(0, 8), DP(1, 8), DP(3, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(4, 4),
DP(0, 3), DP(1, 3), DP(3, 3), DP(4, 3),
DP(0, 2), DP(1, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 147
DP(2, 11), DP(3, 11),
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 148
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 149
DP(0, 11), DP(1, 11),
DP(1, 10), DP(2, 10),
DP(2, 9), DP(3, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 150
DP(2, 11), DP(3, 11),
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 151
DP(0, 11), DP(1, 11),
DP(1, 10), DP(2, 10),
DP(2, 9), DP(3, 9),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 152
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(4, 2), DP(5, 2),
DP(3, 1), DP(4, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0),

// 153
DP(0, 11), DP(1, 11), DP(4, 11), DP(5, 11),
DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 154
DP(0, 11), DP(1, 11), DP(4, 11), DP(5, 11),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 155
DP(2, 10), DP(3, 10),
DP(2, 9), DP(3, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3),
DP(2, 2), DP(3, 2),
DP(2, 1), DP(3, 1),

// 156
DP(2, 11), DP(3, 11), DP(4, 11), DP(5, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9),
DP(1, 8), DP(2, 8),
DP(1, 7), DP(2, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4),
DP(0, 3), DP(1, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 157
DP(0, 11), DP(1, 11), DP(4, 11), DP(5, 11),
DP(0, 10), DP(1, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(2, 5), DP(3, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),
DP(2, 3), DP(3, 3),
DP(2, 2), DP(3, 2),

// 158
DP(0, 11), DP(1, 11), DP(2, 11), DP(3, 11),
DP(0, 10), DP(4, 10),
DP(0, 9), DP(4, 9),
DP(0, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7),
DP(0, 6), DP(4, 6),
DP(0, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(4, 3), DP(5, 3), DP(7, 3),
DP(0, 2), DP(5, 2), DP(6, 2),

// 159
DP(4, 11), DP(5, 11), DP(6, 11),
DP(3, 10), DP(4, 10), DP(6, 10), DP(7, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(0, 3), DP(1, 3), DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2),

// 160
DP(4, 11), DP(5, 11),
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 161
DP(4, 11), DP(5, 11),
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 162
DP(4, 11), DP(5, 11),
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 163
DP(4, 11), DP(5, 11),
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 164
DP(1, 10), DP(2, 10), DP(3, 10), DP(5, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 165
DP(1, 11), DP(2, 11), DP(3, 11), DP(5, 11), DP(6, 11),
DP(0, 10), DP(1, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4), DP(6, 4),
DP(0, 3), DP(1, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(5, 2), DP(6, 2),

// 166
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),

// 167
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5),

// 168
DP(2, 10), DP(3, 10),
DP(2, 9), DP(3, 9),
DP(2, 7), DP(3, 7),
DP(1, 6), DP(2, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 169
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3),

// 170
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(4, 5), DP(5, 5),
DP(4, 4), DP(5, 4),
DP(4, 3), DP(5, 3),

// 171
DP(1, 10), DP(6, 10),
DP(0, 9), DP(1, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7),
DP(2, 6), DP(3, 6),
DP(1, 5), DP(2, 5), DP(4, 5), DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(5, 3), DP(6, 3),
DP(4, 2), DP(5, 2),
DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1), DP(7, 1),

// 172
DP(1, 10), DP(2, 10), DP(6, 10), DP(7, 10),
DP(0, 9), DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(2, 6), DP(3, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(4, 5), DP(5, 5), DP(6, 5), DP(7, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(4, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(2, 3), DP(3, 3), DP(6, 3), DP(7, 3),
DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2), DP(7, 2),
DP(6, 1), DP(7, 1),

// 173
DP(2, 10), DP(3, 10),
DP(2, 9), DP(3, 9),
DP(2, 7), DP(3, 7),
DP(2, 6), DP(3, 6),
DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4),
DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3),
DP(2, 2), DP(3, 2),

// 174
DP(2, 7), DP(3, 7), DP(6, 7), DP(7, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(2, 2), DP(3, 2), DP(6, 2), DP(7, 2),

// 175
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(2, 5), DP(3, 5), DP(6, 5), DP(7, 5),
DP(2, 4), DP(3, 4), DP(6, 4), DP(7, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 176
DP(2, 11), DP(5, 11),
DP(0, 10), DP(3, 10), DP(6, 10),
DP(1, 9), DP(4, 9), DP(7, 9),
DP(2, 8), DP(5, 8),
DP(0, 7), DP(3, 7), DP(6, 7),
DP(1, 6), DP(4, 6), DP(7, 6),
DP(2, 5), DP(5, 5),
DP(0, 4), DP(3, 4), DP(6, 4),
DP(1, 3), DP(4, 3), DP(7, 3),
DP(2, 2), DP(5, 2),
DP(0, 1), DP(3, 1), DP(6, 1),
DP(1, 0), DP(4, 0), DP(7, 0),

// 177
DP(1, 11), DP(3, 11), DP(5, 11), DP(7, 11),
DP(0, 10), DP(2, 10), DP(4, 10), DP(6, 10),
DP(1, 9), DP(3, 9), DP(5, 9), DP(7, 9),
DP(0, 8), DP(2, 8), DP(4, 8), DP(6, 8),
DP(1, 7), DP(3, 7), DP(5, 7), DP(7, 7),
DP(0, 6), DP(2, 6), DP(4, 6), DP(6, 6),
DP(1, 5), DP(3, 5), DP(5, 5), DP(7, 5),
DP(0, 4), DP(2, 4), DP(4, 4), DP(6, 4),
DP(1, 3), DP(3, 3), DP(5, 3), DP(7, 3),
DP(0, 2), DP(2, 2), DP(4, 2), DP(6, 2),
DP(1, 1), DP(3, 1), DP(5, 1), DP(7, 1),
DP(0, 0), DP(2, 0), DP(4, 0), DP(6, 0),

// 178
DP(1, 11), DP(2, 11), DP(4, 11), DP(5, 11), DP(7, 11),
DP(0, 10), DP(1, 10), DP(3, 10), DP(4, 10), DP(6, 10), DP(7, 10),
DP(0, 9), DP(2, 9), DP(3, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(4, 8), DP(5, 8), DP(7, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(6, 7), DP(7, 7),
DP(0, 6), DP(2, 6), DP(3, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(4, 5), DP(5, 5), DP(7, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(4, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(2, 3), DP(3, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(4, 2), DP(5, 2), DP(7, 2),
DP(0, 1), DP(1, 1), DP(3, 1), DP(4, 1), DP(6, 1), DP(7, 1),
DP(0, 0), DP(2, 0), DP(3, 0), DP(5, 0), DP(6, 0),

// 179
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 180
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 181
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 182
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 183
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 184
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 185
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(5, 6), DP(6, 6),
DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 186
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 187
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(5, 6), DP(6, 6),
DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 188
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(5, 6), DP(6, 6),
DP(5, 5), DP(6, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4),

// 189
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),

// 190
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4),

// 191
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 192
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),

// 193
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),

// 194
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 195
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 196
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),

// 197
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 198
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 199
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 200
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(1, 6), DP(2, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),

// 201
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(1, 6), DP(2, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 202
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),

// 203
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 4), DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 204
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(1, 6), DP(2, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 205
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),

// 206
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 4), DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 207
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),

// 208
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),

// 209
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 210
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 211
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),

// 212
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),

// 213
DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 214
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 215
DP(1, 11), DP(2, 11), DP(5, 11), DP(6, 11),
DP(1, 10), DP(2, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),
DP(1, 1), DP(2, 1), DP(5, 1), DP(6, 1),
DP(1, 0), DP(2, 0), DP(5, 0), DP(6, 0),

// 216
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 217
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6),

// 218
DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 219
DP(0, 11), DP(1, 11), DP(2, 11), DP(3, 11), DP(4, 11), DP(5, 11), DP(6, 11), DP(7, 11),
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10), DP(7, 10),
DP(0, 9), DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9), DP(6, 9), DP(7, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8), DP(7, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5), DP(7, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3), DP(7, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2), DP(7, 2),
DP(0, 1), DP(1, 1), DP(2, 1), DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1), DP(7, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0), DP(4, 0), DP(5, 0), DP(6, 0), DP(7, 0),

// 220
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5), DP(6, 5), DP(7, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3), DP(7, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2), DP(6, 2), DP(7, 2),
DP(0, 1), DP(1, 1), DP(2, 1), DP(3, 1), DP(4, 1), DP(5, 1), DP(6, 1), DP(7, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0), DP(4, 0), DP(5, 0), DP(6, 0), DP(7, 0),

// 221
DP(0, 11), DP(1, 11), DP(2, 11), DP(3, 11),
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10),
DP(0, 9), DP(1, 9), DP(2, 9), DP(3, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5),
DP(0, 4), DP(1, 4), DP(2, 4), DP(3, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2),
DP(0, 1), DP(1, 1), DP(2, 1), DP(3, 1),
DP(0, 0), DP(1, 0), DP(2, 0), DP(3, 0),

// 222
DP(4, 11), DP(5, 11), DP(6, 11), DP(7, 11),
DP(4, 10), DP(5, 10), DP(6, 10), DP(7, 10),
DP(4, 9), DP(5, 9), DP(6, 9), DP(7, 9),
DP(4, 8), DP(5, 8), DP(6, 8), DP(7, 8),
DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),
DP(4, 5), DP(5, 5), DP(6, 5), DP(7, 5),
DP(4, 4), DP(5, 4), DP(6, 4), DP(7, 4),
DP(4, 3), DP(5, 3), DP(6, 3), DP(7, 3),
DP(4, 2), DP(5, 2), DP(6, 2), DP(7, 2),
DP(4, 1), DP(5, 1), DP(6, 1), DP(7, 1),
DP(4, 0), DP(5, 0), DP(6, 0), DP(7, 0),

// 223
DP(0, 11), DP(1, 11), DP(2, 11), DP(3, 11), DP(4, 11), DP(5, 11), DP(6, 11), DP(7, 11),
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10), DP(7, 10),
DP(0, 9), DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9), DP(6, 9), DP(7, 9),
DP(0, 8), DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8), DP(6, 8), DP(7, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7), DP(7, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6), DP(7, 6),

// 224
DP(1, 7), DP(2, 7), DP(3, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(3, 6), DP(4, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(3, 3), DP(4, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(5, 2), DP(6, 2),

// 225
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3),
DP(0, 2), DP(1, 2),
DP(1, 1), DP(2, 1),

// 226
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7),
DP(0, 6), DP(1, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4),
DP(0, 3), DP(1, 3),
DP(0, 2), DP(1, 2),

// 227
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10), DP(6, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(4, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(4, 5), DP(5, 5),
DP(1, 4), DP(2, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(5, 2), DP(6, 2),

// 228
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(5, 8),
DP(1, 7), DP(2, 7),
DP(2, 6), DP(3, 6),
DP(1, 5), DP(2, 5),
DP(1, 4), DP(2, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 229
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(4, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 230
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(1, 6), DP(2, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(5, 4), DP(6, 4),
DP(1, 3), DP(2, 3), DP(5, 3), DP(6, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(6, 2), DP(7, 2),
DP(1, 1), DP(2, 1),
DP(0, 0), DP(1, 0),

// 231
DP(1, 8), DP(2, 8), DP(3, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(4, 2), DP(5, 2), DP(6, 2),

// 232
DP(0, 10), DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(2, 9), DP(3, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4),
DP(2, 3), DP(3, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 233
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(0, 9), DP(1, 9), DP(4, 9), DP(5, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 234
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(0, 9), DP(1, 9), DP(5, 9), DP(6, 9),
DP(0, 8), DP(1, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(5, 6), DP(6, 6),
DP(1, 5), DP(2, 5), DP(4, 5), DP(5, 5),
DP(1, 4), DP(2, 4), DP(4, 4), DP(5, 4),
DP(1, 3), DP(2, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(2, 2), DP(4, 2), DP(5, 2), DP(6, 2),

// 235
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9),
DP(2, 8), DP(3, 8),
DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(1, 2), DP(2, 2), DP(3, 2), DP(4, 2),

// 236
DP(1, 8), DP(2, 8), DP(3, 8), DP(5, 8), DP(6, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(6, 7), DP(7, 7),
DP(0, 6), DP(1, 6), DP(3, 6), DP(4, 6), DP(6, 6), DP(7, 6),
DP(0, 5), DP(1, 5), DP(3, 5), DP(4, 5), DP(6, 5), DP(7, 5),
DP(1, 4), DP(2, 4), DP(4, 4), DP(5, 4), DP(6, 4),

// 237
DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(3, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(0, 6), DP(1, 6), DP(3, 6), DP(5, 6), DP(6, 6),
DP(0, 5), DP(1, 5), DP(2, 5), DP(3, 5), DP(5, 5), DP(6, 5),
DP(1, 4), DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3),

// 238
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9),
DP(0, 8), DP(1, 8),
DP(0, 7), DP(1, 7),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5),
DP(0, 4), DP(1, 4),
DP(1, 3), DP(2, 3),
DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 239
DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9),
DP(0, 8), DP(1, 8), DP(4, 8), DP(5, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7),
DP(0, 6), DP(1, 6), DP(4, 6), DP(5, 6),
DP(0, 5), DP(1, 5), DP(4, 5), DP(5, 5),
DP(0, 4), DP(1, 4), DP(4, 4), DP(5, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3),
DP(0, 2), DP(1, 2), DP(4, 2), DP(5, 2),

// 240
DP(0, 9), DP(1, 9), DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),

// 241
DP(2, 9), DP(3, 9),
DP(2, 8), DP(3, 8),
DP(0, 7), DP(1, 7), DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(2, 6), DP(3, 6),
DP(2, 5), DP(3, 5),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),

// 242
DP(1, 10), DP(2, 10),
DP(2, 9), DP(3, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(2, 6), DP(3, 6),
DP(1, 5), DP(2, 5),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),

// 243
DP(3, 10), DP(4, 10),
DP(2, 9), DP(3, 9),
DP(1, 8), DP(2, 8),
DP(1, 7), DP(2, 7),
DP(2, 6), DP(3, 6),
DP(3, 5), DP(4, 5),
DP(0, 3), DP(1, 3), DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),

// 244
DP(4, 9), DP(5, 9), DP(6, 9),
DP(3, 8), DP(4, 8), DP(6, 8), DP(7, 8),
DP(3, 7), DP(4, 7), DP(6, 7), DP(7, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(3, 4), DP(4, 4),
DP(3, 3), DP(4, 3),
DP(3, 2), DP(4, 2),
DP(3, 1), DP(4, 1),
DP(3, 0), DP(4, 0),

// 245
DP(3, 11), DP(4, 11),
DP(3, 10), DP(4, 10),
DP(3, 9), DP(4, 9),
DP(3, 8), DP(4, 8),
DP(3, 7), DP(4, 7),
DP(3, 6), DP(4, 6),
DP(3, 5), DP(4, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(4, 4),
DP(0, 3), DP(1, 3), DP(3, 3), DP(4, 3),
DP(1, 2), DP(2, 2), DP(3, 2),

// 246
DP(2, 9), DP(3, 9),
DP(2, 8), DP(3, 8),
DP(0, 6), DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(2, 4), DP(3, 4),
DP(2, 3), DP(3, 3),

// 247
DP(1, 9), DP(2, 9), DP(3, 9), DP(6, 9), DP(7, 9),
DP(0, 8), DP(1, 8), DP(3, 8), DP(4, 8), DP(6, 8), DP(7, 8),
DP(0, 7), DP(1, 7), DP(4, 7), DP(5, 7), DP(6, 7),
DP(1, 5), DP(2, 5), DP(3, 5), DP(6, 5), DP(7, 5),
DP(0, 4), DP(1, 4), DP(3, 4), DP(4, 4), DP(6, 4), DP(7, 4),
DP(0, 3), DP(1, 3), DP(4, 3), DP(5, 3), DP(6, 3),

// 248
DP(2, 10), DP(3, 10), DP(4, 10), DP(5, 10),
DP(1, 9), DP(2, 9), DP(5, 9), DP(6, 9),
DP(1, 8), DP(2, 8), DP(5, 8), DP(6, 8),
DP(1, 7), DP(2, 7), DP(5, 7), DP(6, 7),
DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),

// 249
DP(3, 7), DP(4, 7), DP(5, 7),
DP(3, 6), DP(4, 6), DP(5, 6),

// 250
DP(3, 6), DP(4, 6),

// 251
DP(5, 10), DP(6, 10), DP(7, 10),
DP(5, 9),
DP(5, 8),
DP(5, 7),
DP(1, 6), DP(5, 6),
DP(1, 5), DP(2, 5), DP(5, 5),
DP(2, 4), DP(3, 4), DP(5, 4),
DP(3, 3), DP(4, 3), DP(5, 3),
DP(4, 2), DP(5, 2),

// 252
DP(0, 10), DP(1, 10), DP(3, 10), DP(4, 10),
DP(1, 9), DP(2, 9), DP(4, 9), DP(5, 9),
DP(1, 8), DP(2, 8), DP(4, 8), DP(5, 8),
DP(1, 7), DP(2, 7), DP(4, 7), DP(5, 7),
DP(1, 6), DP(2, 6), DP(4, 6), DP(5, 6),

// 253
DP(1, 10), DP(2, 10), DP(3, 10), DP(4, 10),
DP(4, 9), DP(5, 9),
DP(3, 8), DP(4, 8),
DP(2, 7), DP(3, 7),
DP(1, 6), DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),

// 254
DP(2, 9), DP(3, 9), DP(4, 9), DP(5, 9),
DP(2, 8), DP(3, 8), DP(4, 8), DP(5, 8),
DP(2, 7), DP(3, 7), DP(4, 7), DP(5, 7),
DP(2, 6), DP(3, 6), DP(4, 6), DP(5, 6),
DP(2, 5), DP(3, 5), DP(4, 5), DP(5, 5),
DP(2, 4), DP(3, 4), DP(4, 4), DP(5, 4),
DP(2, 3), DP(3, 3), DP(4, 3), DP(5, 3),
DP(2, 2), DP(3, 2), DP(4, 2), DP(5, 2),

// 255
#endif

#if 0
// 0
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 1
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DW(6, 9), DW(7, 9),
DW(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DW(7, 8),
DW(0, 7), DG(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DG(6, 7), DW(7, 7),
DW(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DW(7, 6),
DW(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DW(7, 5),
DW(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DW(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DW(6, 3), DW(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 2
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DW(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DW(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DW(6, 7), DW(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DW(6, 5), DW(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DW(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 3
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 4
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 5
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DW(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 6
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 7
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 8
DW(0, 11), DW(1, 11), DW(2, 11), DW(3, 11), DW(4, 11), DW(5, 11), DW(6, 11), DW(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DW(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DW(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DW(6, 7), DW(7, 7),
DW(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DW(7, 6),
DW(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DW(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DW(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DW(7, 2),
DW(0, 1), DW(1, 1), DW(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DW(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DW(4, 0), DW(5, 0), DW(6, 0), DW(7, 0),

// 9
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 10
DW(0, 11), DW(1, 11), DW(2, 11), DW(3, 11), DW(4, 11), DW(5, 11), DW(6, 11), DW(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DW(6, 9), DW(7, 9),
DW(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DW(7, 8),
DW(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DW(7, 7),
DW(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DW(7, 6),
DW(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DW(7, 5),
DW(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DW(7, 4),
DW(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DW(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DW(6, 2), DW(7, 2),
DW(0, 1), DW(1, 1), DW(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DW(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DW(4, 0), DW(5, 0), DW(6, 0), DW(7, 0),

// 11
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 12
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 13
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DW(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DW(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 14
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DW(6, 9), DW(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DW(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DW(6, 5), DW(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DW(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DW(0, 1), DW(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 15
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DW(6, 8), DW(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DW(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DW(6, 3), DW(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 16
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 17
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 18
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 19
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 20
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DW(6, 9), DW(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DW(6, 8), DW(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DW(6, 5), DW(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DW(6, 3), DW(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DW(6, 2), DW(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 21
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DW(6, 9), DW(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 22
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 23
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 24
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 25
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 26
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 27
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 28
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 29
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 30
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 31
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 32
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 33
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 34
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 35
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 36
DG(0, 11), DG(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DW(2, 1), DW(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 37
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 38
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 39
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 40
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 41
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 42
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 43
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 44
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 45
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 46
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 47
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 48
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 49
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 50
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 51
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 52
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 53
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 54
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 55
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 56
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 57
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 58
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 59
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DW(2, 1), DW(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 60
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 61
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 62
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 63
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 64
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 65
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 66
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 67
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 68
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 69
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 70
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 71
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 72
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 73
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 74
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 75
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 76
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 77
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 78
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 79
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 80
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 81
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 82
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 83
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 84
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 85
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 86
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 87
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 88
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 89
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 90
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 91
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 92
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 93
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 94
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 95
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DW(0, 1), DW(1, 1), DW(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DW(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 96
DG(0, 11), DG(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 97
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 98
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 99
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 100
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 101
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 102
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 103
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DW(0, 1), DW(1, 1), DG(2, 1), DG(3, 1), DW(4, 1), DW(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 104
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 105
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 106
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DW(0, 1), DW(1, 1), DG(2, 1), DG(3, 1), DW(4, 1), DW(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 107
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 108
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 109
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 110
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 111
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 112
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 113
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DW(4, 1), DW(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 114
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 115
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 116
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 117
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 118
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 119
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 120
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 121
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 122
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 123
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 124
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 125
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 126
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DW(6, 10), DW(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 127
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 128
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DW(2, 1), DW(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 129
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 130
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 131
DG(0, 11), DG(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 132
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 133
DW(0, 11), DW(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 134
DG(0, 11), DG(1, 11), DW(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 135
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DW(2, 1), DW(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 136
DG(0, 11), DG(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 137
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 138
DW(0, 11), DW(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 139
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 140
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 141
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 142
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 143
DG(0, 11), DW(1, 11), DW(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 144
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 145
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DW(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DW(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 146
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 147
DG(0, 11), DG(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 148
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 149
DW(0, 11), DW(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 150
DG(0, 11), DG(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 151
DW(0, 11), DW(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 152
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 153
DW(0, 11), DW(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 154
DW(0, 11), DW(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 155
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DW(2, 1), DW(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 156
DG(0, 11), DG(1, 11), DW(2, 11), DW(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 157
DW(0, 11), DW(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 158
DW(0, 11), DW(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DW(7, 3),
DW(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 159
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DW(6, 10), DW(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 160
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 161
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 162
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 163
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 164
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 165
DG(0, 11), DW(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 166
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 167
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 168
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 169
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 170
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 171
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DW(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DW(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 172
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DW(6, 10), DW(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DW(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DW(6, 3), DW(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DW(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DW(6, 1), DW(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 173
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 174
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DW(6, 2), DW(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 175
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DW(6, 5), DW(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 176
DG(0, 11), DG(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DW(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DW(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DW(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DG(4, 1), DG(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DG(2, 0), DG(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DW(7, 0),

// 177
DG(0, 11), DW(1, 11), DG(2, 11), DW(3, 11), DG(4, 11), DW(5, 11), DG(6, 11), DW(7, 11),
DW(0, 10), DG(1, 10), DW(2, 10), DG(3, 10), DW(4, 10), DG(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DG(2, 9), DW(3, 9), DG(4, 9), DW(5, 9), DG(6, 9), DW(7, 9),
DW(0, 8), DG(1, 8), DW(2, 8), DG(3, 8), DW(4, 8), DG(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DG(4, 7), DW(5, 7), DG(6, 7), DW(7, 7),
DW(0, 6), DG(1, 6), DW(2, 6), DG(3, 6), DW(4, 6), DG(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DG(4, 5), DW(5, 5), DG(6, 5), DW(7, 5),
DW(0, 4), DG(1, 4), DW(2, 4), DG(3, 4), DW(4, 4), DG(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DG(4, 3), DW(5, 3), DG(6, 3), DW(7, 3),
DW(0, 2), DG(1, 2), DW(2, 2), DG(3, 2), DW(4, 2), DG(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DG(2, 1), DW(3, 1), DG(4, 1), DW(5, 1), DG(6, 1), DW(7, 1),
DW(0, 0), DG(1, 0), DW(2, 0), DG(3, 0), DW(4, 0), DG(5, 0), DW(6, 0), DG(7, 0),

// 178
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DG(6, 11), DW(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DW(6, 10), DW(7, 10),
DW(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DW(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DW(6, 7), DW(7, 7),
DW(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DW(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DW(7, 2),
DW(0, 1), DW(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DW(6, 1), DW(7, 1),
DW(0, 0), DG(1, 0), DW(2, 0), DW(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 179
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 180
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 181
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 182
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 183
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 184
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 185
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 186
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 187
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 188
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 189
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 190
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 191
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 192
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 193
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 194
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 195
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 196
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 197
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 198
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 199
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 200
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 201
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 202
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 203
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 204
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 205
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 206
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 207
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 208
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 209
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 210
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 211
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 212
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 213
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 214
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 215
DG(0, 11), DW(1, 11), DW(2, 11), DG(3, 11), DG(4, 11), DW(5, 11), DW(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DW(5, 1), DW(6, 1), DG(7, 1),
DG(0, 0), DW(1, 0), DW(2, 0), DG(3, 0), DG(4, 0), DW(5, 0), DW(6, 0), DG(7, 0),

// 216
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 217
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 218
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 219
DW(0, 11), DW(1, 11), DW(2, 11), DW(3, 11), DW(4, 11), DW(5, 11), DW(6, 11), DW(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DW(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DW(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DW(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DW(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DW(7, 2),
DW(0, 1), DW(1, 1), DW(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DW(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DW(4, 0), DW(5, 0), DW(6, 0), DW(7, 0),

// 220
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DW(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DW(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DW(7, 2),
DW(0, 1), DW(1, 1), DW(2, 1), DW(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DW(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DW(4, 0), DW(5, 0), DW(6, 0), DW(7, 0),

// 221
DW(0, 11), DW(1, 11), DW(2, 11), DW(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DW(0, 1), DW(1, 1), DW(2, 1), DW(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DW(0, 0), DW(1, 0), DW(2, 0), DW(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 222
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DW(4, 11), DW(5, 11), DW(6, 11), DW(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DW(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DW(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DW(6, 5), DW(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DW(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DW(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DW(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DW(4, 1), DW(5, 1), DW(6, 1), DW(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DW(4, 0), DW(5, 0), DW(6, 0), DW(7, 0),

// 223
DW(0, 11), DW(1, 11), DW(2, 11), DW(3, 11), DW(4, 11), DW(5, 11), DW(6, 11), DW(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DW(7, 9),
DW(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DW(6, 8), DW(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DW(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DW(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 224
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 225
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 226
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 227
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DW(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DG(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 228
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 229
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 230
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DG(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DW(6, 2), DW(7, 2),
DG(0, 1), DW(1, 1), DW(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DW(0, 0), DW(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 231
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 232
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 233
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 234
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DW(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DW(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 235
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 236
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DW(6, 7), DW(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DW(6, 6), DW(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DW(6, 5), DW(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DW(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 237
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DW(3, 6), DG(4, 6), DW(5, 6), DW(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DW(5, 5), DW(6, 5), DG(7, 5),
DG(0, 4), DW(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 238
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DW(1, 3), DW(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 239
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DW(0, 5), DW(1, 5), DG(2, 5), DG(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DG(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DW(0, 2), DW(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 240
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DW(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 241
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DW(0, 7), DW(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 242
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 243
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 244
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DW(6, 8), DW(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DW(6, 7), DW(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DW(3, 2), DW(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DW(3, 1), DW(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DW(3, 0), DW(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 245
DG(0, 11), DG(1, 11), DG(2, 11), DW(3, 11), DW(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DW(3, 9), DW(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DW(3, 5), DW(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DW(1, 2), DW(2, 2), DW(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 246
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DW(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 247
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DW(3, 9), DG(4, 9), DG(5, 9), DW(6, 9), DW(7, 9),
DW(0, 8), DW(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DW(6, 8), DW(7, 8),
DW(0, 7), DW(1, 7), DG(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DW(3, 5), DG(4, 5), DG(5, 5), DW(6, 5), DW(7, 5),
DW(0, 4), DW(1, 4), DG(2, 4), DW(3, 4), DW(4, 4), DG(5, 4), DW(6, 4), DW(7, 4),
DW(0, 3), DW(1, 3), DG(2, 3), DG(3, 3), DW(4, 3), DW(5, 3), DW(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 248
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DW(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DW(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DW(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DW(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 249
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 250
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DW(3, 6), DW(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 251
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DW(5, 10), DW(6, 10), DW(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DW(1, 5), DW(2, 5), DG(3, 5), DG(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DG(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 252
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DW(0, 10), DW(1, 10), DG(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DW(1, 9), DW(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DW(1, 8), DW(2, 8), DG(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DW(1, 7), DW(2, 7), DG(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DG(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 253
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DW(1, 10), DW(2, 10), DW(3, 10), DW(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DW(3, 8), DW(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DW(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 254
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DW(2, 9), DW(3, 9), DW(4, 9), DW(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DW(2, 8), DW(3, 8), DW(4, 8), DW(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DW(2, 7), DW(3, 7), DW(4, 7), DW(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DW(2, 6), DW(3, 6), DW(4, 6), DW(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DW(2, 5), DW(3, 5), DW(4, 5), DW(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DW(2, 4), DW(3, 4), DW(4, 4), DW(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DW(2, 3), DW(3, 3), DW(4, 3), DW(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DW(2, 2), DW(3, 2), DW(4, 2), DW(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0),

// 255
DG(0, 11), DG(1, 11), DG(2, 11), DG(3, 11), DG(4, 11), DG(5, 11), DG(6, 11), DG(7, 11),
DG(0, 10), DG(1, 10), DG(2, 10), DG(3, 10), DG(4, 10), DG(5, 10), DG(6, 10), DG(7, 10),
DG(0, 9), DG(1, 9), DG(2, 9), DG(3, 9), DG(4, 9), DG(5, 9), DG(6, 9), DG(7, 9),
DG(0, 8), DG(1, 8), DG(2, 8), DG(3, 8), DG(4, 8), DG(5, 8), DG(6, 8), DG(7, 8),
DG(0, 7), DG(1, 7), DG(2, 7), DG(3, 7), DG(4, 7), DG(5, 7), DG(6, 7), DG(7, 7),
DG(0, 6), DG(1, 6), DG(2, 6), DG(3, 6), DG(4, 6), DG(5, 6), DG(6, 6), DG(7, 6),
DG(0, 5), DG(1, 5), DG(2, 5), DG(3, 5), DG(4, 5), DG(5, 5), DG(6, 5), DG(7, 5),
DG(0, 4), DG(1, 4), DG(2, 4), DG(3, 4), DG(4, 4), DG(5, 4), DG(6, 4), DG(7, 4),
DG(0, 3), DG(1, 3), DG(2, 3), DG(3, 3), DG(4, 3), DG(5, 3), DG(6, 3), DG(7, 3),
DG(0, 2), DG(1, 2), DG(2, 2), DG(3, 2), DG(4, 2), DG(5, 2), DG(6, 2), DG(7, 2),
DG(0, 1), DG(1, 1), DG(2, 1), DG(3, 1), DG(4, 1), DG(5, 1), DG(6, 1), DG(7, 1),
DG(0, 0), DG(1, 0), DG(2, 0), DG(3, 0), DG(4, 0), DG(5, 0), DG(6, 0), DG(7, 0)
#endif

};

#if defined(GEOMETRY_H_IMPLEMENTATION)
//constexpr uint32_t gModelsAsciiIndexCount[] =
uint32_t gModelsIndexCount[] =
{

#if 1
// 0
0,
// 1
2736,
// 2
4320,
// 3
2736,
// 4
2304,
// 5
2880,
// 6
3168,
// 7
1440,
// 8
5472,
// 9
2304,
// 10
4608,
// 11
2664,
// 12
2304,
// 13
2304,
// 14
3456,
// 15
2880,
// 16
2088,
// 17
2088,
// 18
2160,
// 19
2016,
// 20
3384,
// 21
2880,
// 22
1512,
// 23
2592,
// 24
1728,
// 25
1728,
// 26
1080,
// 27
1080,
// 28
936,
// 29
1440,
// 30
2304,
// 31
2304,
// 32
0,
// 33
1584,
// 34
1008,
// 35
3024,
// 36
2160,
// 37
1440,
// 38
2880,
// 39
576,
// 40
1296,
// 41
1296,
// 42
1728,
// 43
1008,
// 44
576,
// 45
504,
// 46
432,
// 47
1008,
// 48
3240,
// 49
1656,
// 50
2160,
// 51
1944,
// 52
2304,
// 53
2088,
// 54
2160,
// 55
1944,
// 56
2736,
// 57
2160,
// 58
864,
// 59
1152,
// 60
1296,
// 61
864,
// 62
1296,
// 63
1440,
// 64
2880,
// 65
2592,
// 66
2952,
// 67
2160,
// 68
2736,
// 69
2520,
// 70
2376,
// 71
2448,
// 72
2736,
// 73
1584,
// 74
2016,
// 75
2736,
// 76
2160,
// 77
3240,
// 78
3240,
// 79
2448,
// 80
2376,
// 81
2952,
// 82
2880,
// 83
2232,
// 84
1872,
// 85
2592,
// 86
2448,
// 87
2736,
// 88
2448,
// 89
2160,
// 90
2520,
// 91
1584,
// 92
1008,
// 93
1584,
// 94
864,
// 95
576,
// 96
432,
// 97
1728,
// 98
2376,
// 99
1440,
// 100
2376,
// 101
1728,
// 102
1872,
// 103
2304,
// 104
2376,
// 105
1584,
// 106
2016,
// 107
2304,
// 108
1728,
// 109
2160,
// 110
1800,
// 111
1728,
// 112
2304,
// 113
2304,
// 114
1656,
// 115
1440,
// 116
1584,
// 117
1800,
// 118
1584,
// 119
1872,
// 120
1584,
// 121
2016,
// 122
1584,
// 123
1440,
// 124
1152,
// 125
1440,
// 126
1080,
// 127
1656,
// 128
2592,
// 129
2376,
// 130
2160,
// 131
2448,
// 132
2304,
// 133
2160,
// 134
2808,
// 135
1872,
// 136
2376,
// 137
2232,
// 138
2088,
// 139
1872,
// 140
1872,
// 141
1728,
// 142
2304,
// 143
3024,
// 144
2376,
// 145
2376,
// 146
3024,
// 147
2448,
// 148
2304,
// 149
2160,
// 150
2520,
// 151
2232,
// 152
2592,
// 153
2592,
// 154
2592,
// 155
2016,
// 156
2376,
// 157
2736,
// 158
2232,
// 159
2160,
// 160
2160,
// 161
1728,
// 162
2160,
// 163
2232,
// 164
2520,
// 165
3168,
// 166
1800,
// 167
1656,
// 168
1440,
// 169
864,
// 170
864,
// 171
2520,
// 172
3384,
// 173
1584,
// 174
1728,
// 175
1728,
// 176
2304,
// 177
3456,
// 178
4608,
// 179
1728,
// 180
1944,
// 181
2160,
// 182
3528,
// 183
2232,
// 184
1584,
// 185
3312,
// 186
3456,
// 187
2304,
// 188
2304,
// 189
1944,
// 190
1584,
// 191
1224,
// 192
1080,
// 193
1296,
// 194
1440,
// 195
1944,
// 196
576,
// 197
2160,
// 198
2160,
// 199
3528,
// 200
2304,
// 201
2304,
// 202
2160,
// 203
2160,
// 204
3312,
// 205
1152,
// 206
3168,
// 207
1728,
// 208
2016,
// 209
1728,
// 210
2304,
// 211
1944,
// 212
1584,
// 213
1584,
// 214
2232,
// 215
3600,
// 216
2304,
// 217
1080,
// 218
1224,
// 219
6912,
// 220
3456,
// 221
3456,
// 222
3456,
// 223
3456,
// 224
2160,
// 225
2664,
// 226
1872,
// 227
2808,
// 228
2160,
// 229
1800,
// 230
2160,
// 231
1512,
// 232
2592,
// 233
2736,
// 234
2808,
// 235
2304,
// 236
2016,
// 237
2232,
// 238
1872,
// 239
2304,
// 240
1296,
// 241
1440,
// 242
1296,
// 243
1296,
// 244
1800,
// 245
1800,
// 246
1008,
// 247
2304,
// 248
1440,
// 249
432,
// 250
144,
// 251
1368,
// 252
1440,
// 253
1080,
// 254
2304,
// 255
0,
#endif

#if 0
// 0
6912,
// 1
6912,
// 2
6912,
// 3
6912,
// 4
6912,
// 5
6912,
// 6
6912,
// 7
6912,
// 8
6912,
// 9
6912,
// 10
6912,
// 11
6912,
// 12
6912,
// 13
6912,
// 14
6912,
// 15
6912,
// 16
6912,
// 17
6912,
// 18
6912,
// 19
6912,
// 20
6912,
// 21
6912,
// 22
6912,
// 23
6912,
// 24
6912,
// 25
6912,
// 26
6912,
// 27
6912,
// 28
6912,
// 29
6912,
// 30
6912,
// 31
6912,
// 32
6912,
// 33
6912,
// 34
6912,
// 35
6912,
// 36
6912,
// 37
6912,
// 38
6912,
// 39
6912,
// 40
6912,
// 41
6912,
// 42
6912,
// 43
6912,
// 44
6912,
// 45
6912,
// 46
6912,
// 47
6912,
// 48
6912,
// 49
6912,
// 50
6912,
// 51
6912,
// 52
6912,
// 53
6912,
// 54
6912,
// 55
6912,
// 56
6912,
// 57
6912,
// 58
6912,
// 59
6912,
// 60
6912,
// 61
6912,
// 62
6912,
// 63
6912,
// 64
6912,
// 65
6912,
// 66
6912,
// 67
6912,
// 68
6912,
// 69
6912,
// 70
6912,
// 71
6912,
// 72
6912,
// 73
6912,
// 74
6912,
// 75
6912,
// 76
6912,
// 77
6912,
// 78
6912,
// 79
6912,
// 80
6912,
// 81
6912,
// 82
6912,
// 83
6912,
// 84
6912,
// 85
6912,
// 86
6912,
// 87
6912,
// 88
6912,
// 89
6912,
// 90
6912,
// 91
6912,
// 92
6912,
// 93
6912,
// 94
6912,
// 95
6912,
// 96
6912,
// 97
6912,
// 98
6912,
// 99
6912,
// 100
6912,
// 101
6912,
// 102
6912,
// 103
6912,
// 104
6912,
// 105
6912,
// 106
6912,
// 107
6912,
// 108
6912,
// 109
6912,
// 110
6912,
// 111
6912,
// 112
6912,
// 113
6912,
// 114
6912,
// 115
6912,
// 116
6912,
// 117
6912,
// 118
6912,
// 119
6912,
// 120
6912,
// 121
6912,
// 122
6912,
// 123
6912,
// 124
6912,
// 125
6912,
// 126
6912,
// 127
6912,
// 128
6912,
// 129
6912,
// 130
6912,
// 131
6912,
// 132
6912,
// 133
6912,
// 134
6912,
// 135
6912,
// 136
6912,
// 137
6912,
// 138
6912,
// 139
6912,
// 140
6912,
// 141
6912,
// 142
6912,
// 143
6912,
// 144
6912,
// 145
6912,
// 146
6912,
// 147
6912,
// 148
6912,
// 149
6912,
// 150
6912,
// 151
6912,
// 152
6912,
// 153
6912,
// 154
6912,
// 155
6912,
// 156
6912,
// 157
6912,
// 158
6912,
// 159
6912,
// 160
6912,
// 161
6912,
// 162
6912,
// 163
6912,
// 164
6912,
// 165
6912,
// 166
6912,
// 167
6912,
// 168
6912,
// 169
6912,
// 170
6912,
// 171
6912,
// 172
6912,
// 173
6912,
// 174
6912,
// 175
6912,
// 176
6912,
// 177
6912,
// 178
6912,
// 179
6912,
// 180
6912,
// 181
6912,
// 182
6912,
// 183
6912,
// 184
6912,
// 185
6912,
// 186
6912,
// 187
6912,
// 188
6912,
// 189
6912,
// 190
6912,
// 191
6912,
// 192
6912,
// 193
6912,
// 194
6912,
// 195
6912,
// 196
6912,
// 197
6912,
// 198
6912,
// 199
6912,
// 200
6912,
// 201
6912,
// 202
6912,
// 203
6912,
// 204
6912,
// 205
6912,
// 206
6912,
// 207
6912,
// 208
6912,
// 209
6912,
// 210
6912,
// 211
6912,
// 212
6912,
// 213
6912,
// 214
6912,
// 215
6912,
// 216
6912,
// 217
6912,
// 218
6912,
// 219
6912,
// 220
6912,
// 221
6912,
// 222
6912,
// 223
6912,
// 224
6912,
// 225
6912,
// 226
6912,
// 227
6912,
// 228
6912,
// 229
6912,
// 230
6912,
// 231
6912,
// 232
6912,
// 233
6912,
// 234
6912,
// 235
6912,
// 236
6912,
// 237
6912,
// 238
6912,
// 239
6912,
// 240
6912,
// 241
6912,
// 242
6912,
// 243
6912,
// 244
6912,
// 245
6912,
// 246
6912,
// 247
6912,
// 248
6912,
// 249
6912,
// 250
6912,
// 251
6912,
// 252
6912,
// 253
6912,
// 254
6912,
// 255
6912,
#endif

// placeholder for viking_room
0

};

//constexpr uint32_t gModelsAsciiIndexFirst[] =
uint32_t gModelsIndexFirst[] =
{

#if 1
// 0
1236,
// 1
1236,
// 2
3972,
// 3
8292,
// 4
11028,
// 5
13332,
// 6
16212,
// 7
19380,
// 8
20820,
// 9
26292,
// 10
28596,
// 11
33204,
// 12
35868,
// 13
38172,
// 14
40476,
// 15
43932,
// 16
46812,
// 17
48900,
// 18
50988,
// 19
53148,
// 20
55164,
// 21
58548,
// 22
61428,
// 23
62940,
// 24
65532,
// 25
67260,
// 26
68988,
// 27
70068,
// 28
71148,
// 29
72084,
// 30
73524,
// 31
75828,
// 32
78132,
// 33
78132,
// 34
79716,
// 35
80724,
// 36
83748,
// 37
85908,
// 38
87348,
// 39
90228,
// 40
90804,
// 41
92100,
// 42
93396,
// 43
95124,
// 44
96132,
// 45
96708,
// 46
97212,
// 47
97644,
// 48
98652,
// 49
101892,
// 50
103548,
// 51
105708,
// 52
107652,
// 53
109956,
// 54
112044,
// 55
114204,
// 56
116148,
// 57
118884,
// 58
121044,
// 59
121908,
// 60
123060,
// 61
124356,
// 62
125220,
// 63
126516,
// 64
127956,
// 65
130836,
// 66
133428,
// 67
136380,
// 68
138540,
// 69
141276,
// 70
143796,
// 71
146172,
// 72
148620,
// 73
151356,
// 74
152940,
// 75
154956,
// 76
157692,
// 77
159852,
// 78
163092,
// 79
166332,
// 80
168780,
// 81
171156,
// 82
174108,
// 83
176988,
// 84
179220,
// 85
181092,
// 86
183684,
// 87
186132,
// 88
188868,
// 89
191316,
// 90
193476,
// 91
195996,
// 92
197580,
// 93
198588,
// 94
200172,
// 95
201036,
// 96
201612,
// 97
202044,
// 98
203772,
// 99
206148,
// 100
207588,
// 101
209964,
// 102
211692,
// 103
213564,
// 104
215868,
// 105
218244,
// 106
219828,
// 107
221844,
// 108
224148,
// 109
225876,
// 110
228036,
// 111
229836,
// 112
231564,
// 113
233868,
// 114
236172,
// 115
237828,
// 116
239268,
// 117
240852,
// 118
242652,
// 119
244236,
// 120
246108,
// 121
247692,
// 122
249708,
// 123
251292,
// 124
252732,
// 125
253884,
// 126
255324,
// 127
256404,
// 128
258060,
// 129
260652,
// 130
263028,
// 131
265188,
// 132
267636,
// 133
269940,
// 134
272100,
// 135
274908,
// 136
276780,
// 137
279156,
// 138
281388,
// 139
283476,
// 140
285348,
// 141
287220,
// 142
288948,
// 143
291252,
// 144
294276,
// 145
296652,
// 146
299028,
// 147
302052,
// 148
304500,
// 149
306804,
// 150
308964,
// 151
311484,
// 152
313716,
// 153
316308,
// 154
318900,
// 155
321492,
// 156
323508,
// 157
325884,
// 158
328620,
// 159
330852,
// 160
333012,
// 161
335172,
// 162
336900,
// 163
339060,
// 164
341292,
// 165
343812,
// 166
346980,
// 167
348780,
// 168
350436,
// 169
351876,
// 170
352740,
// 171
353604,
// 172
356124,
// 173
359508,
// 174
361092,
// 175
362820,
// 176
364548,
// 177
366852,
// 178
370308,
// 179
374916,
// 180
376644,
// 181
378588,
// 182
380748,
// 183
384276,
// 184
386508,
// 185
388092,
// 186
391404,
// 187
394860,
// 188
397164,
// 189
399468,
// 190
401412,
// 191
402996,
// 192
404220,
// 193
405300,
// 194
406596,
// 195
408036,
// 196
409980,
// 197
410556,
// 198
412716,
// 199
414876,
// 200
418404,
// 201
420708,
// 202
423012,
// 203
425172,
// 204
427332,
// 205
430644,
// 206
431796,
// 207
434964,
// 208
436692,
// 209
438708,
// 210
440436,
// 211
442740,
// 212
444684,
// 213
446268,
// 214
447852,
// 215
450084,
// 216
453684,
// 217
455988,
// 218
457068,
// 219
458292,
// 220
465204,
// 221
468660,
// 222
472116,
// 223
475572,
// 224
479028,
// 225
481188,
// 226
483852,
// 227
485724,
// 228
488532,
// 229
490692,
// 230
492492,
// 231
494652,
// 232
496164,
// 233
498756,
// 234
501492,
// 235
504300,
// 236
506604,
// 237
508620,
// 238
510852,
// 239
512724,
// 240
515028,
// 241
516324,
// 242
517764,
// 243
519060,
// 244
520356,
// 245
522156,
// 246
523956,
// 247
524964,
// 248
527268,
// 249
528708,
// 250
529140,
// 251
529284,
// 252
530652,
// 253
532092,
// 254
533172,
// 255
535476,
#endif

#if 0
// 0
1236,
// 1
8148,
// 2
15060,
// 3
21972,
// 4
28884,
// 5
35796,
// 6
42708,
// 7
49620,
// 8
56532,
// 9
63444,
// 10
70356,
// 11
77268,
// 12
84180,
// 13
91092,
// 14
98004,
// 15
104916,
// 16
111828,
// 17
118740,
// 18
125652,
// 19
132564,
// 20
139476,
// 21
146388,
// 22
153300,
// 23
160212,
// 24
167124,
// 25
174036,
// 26
180948,
// 27
187860,
// 28
194772,
// 29
201684,
// 30
208596,
// 31
215508,
// 32
222420,
// 33
229332,
// 34
236244,
// 35
243156,
// 36
250068,
// 37
256980,
// 38
263892,
// 39
270804,
// 40
277716,
// 41
284628,
// 42
291540,
// 43
298452,
// 44
305364,
// 45
312276,
// 46
319188,
// 47
326100,
// 48
333012,
// 49
339924,
// 50
346836,
// 51
353748,
// 52
360660,
// 53
367572,
// 54
374484,
// 55
381396,
// 56
388308,
// 57
395220,
// 58
402132,
// 59
409044,
// 60
415956,
// 61
422868,
// 62
429780,
// 63
436692,
// 64
443604,
// 65
450516,
// 66
457428,
// 67
464340,
// 68
471252,
// 69
478164,
// 70
485076,
// 71
491988,
// 72
498900,
// 73
505812,
// 74
512724,
// 75
519636,
// 76
526548,
// 77
533460,
// 78
540372,
// 79
547284,
// 80
554196,
// 81
561108,
// 82
568020,
// 83
574932,
// 84
581844,
// 85
588756,
// 86
595668,
// 87
602580,
// 88
609492,
// 89
616404,
// 90
623316,
// 91
630228,
// 92
637140,
// 93
644052,
// 94
650964,
// 95
657876,
// 96
664788,
// 97
671700,
// 98
678612,
// 99
685524,
// 100
692436,
// 101
699348,
// 102
706260,
// 103
713172,
// 104
720084,
// 105
726996,
// 106
733908,
// 107
740820,
// 108
747732,
// 109
754644,
// 110
761556,
// 111
768468,
// 112
775380,
// 113
782292,
// 114
789204,
// 115
796116,
// 116
803028,
// 117
809940,
// 118
816852,
// 119
823764,
// 120
830676,
// 121
837588,
// 122
844500,
// 123
851412,
// 124
858324,
// 125
865236,
// 126
872148,
// 127
879060,
// 128
885972,
// 129
892884,
// 130
899796,
// 131
906708,
// 132
913620,
// 133
920532,
// 134
927444,
// 135
934356,
// 136
941268,
// 137
948180,
// 138
955092,
// 139
962004,
// 140
968916,
// 141
975828,
// 142
982740,
// 143
989652,
// 144
996564,
// 145
1003476,
// 146
1010388,
// 147
1017300,
// 148
1024212,
// 149
1031124,
// 150
1038036,
// 151
1044948,
// 152
1051860,
// 153
1058772,
// 154
1065684,
// 155
1072596,
// 156
1079508,
// 157
1086420,
// 158
1093332,
// 159
1100244,
// 160
1107156,
// 161
1114068,
// 162
1120980,
// 163
1127892,
// 164
1134804,
// 165
1141716,
// 166
1148628,
// 167
1155540,
// 168
1162452,
// 169
1169364,
// 170
1176276,
// 171
1183188,
// 172
1190100,
// 173
1197012,
// 174
1203924,
// 175
1210836,
// 176
1217748,
// 177
1224660,
// 178
1231572,
// 179
1238484,
// 180
1245396,
// 181
1252308,
// 182
1259220,
// 183
1266132,
// 184
1273044,
// 185
1279956,
// 186
1286868,
// 187
1293780,
// 188
1300692,
// 189
1307604,
// 190
1314516,
// 191
1321428,
// 192
1328340,
// 193
1335252,
// 194
1342164,
// 195
1349076,
// 196
1355988,
// 197
1362900,
// 198
1369812,
// 199
1376724,
// 200
1383636,
// 201
1390548,
// 202
1397460,
// 203
1404372,
// 204
1411284,
// 205
1418196,
// 206
1425108,
// 207
1432020,
// 208
1438932,
// 209
1445844,
// 210
1452756,
// 211
1459668,
// 212
1466580,
// 213
1473492,
// 214
1480404,
// 215
1487316,
// 216
1494228,
// 217
1501140,
// 218
1508052,
// 219
1514964,
// 220
1521876,
// 221
1528788,
// 222
1535700,
// 223
1542612,
// 224
1549524,
// 225
1556436,
// 226
1563348,
// 227
1570260,
// 228
1577172,
// 229
1584084,
// 230
1590996,
// 231
1597908,
// 232
1604820,
// 233
1611732,
// 234
1618644,
// 235
1625556,
// 236
1632468,
// 237
1639380,
// 238
1646292,
// 239
1653204,
// 240
1660116,
// 241
1667028,
// 242
1673940,
// 243
1680852,
// 244
1687764,
// 245
1694676,
// 246
1701588,
// 247
1708500,
// 248
1715412,
// 249
1722324,
// 250
1729236,
// 251
1736148,
// 252
1743060,
// 253
1749972,
// 254
1756884,
// 255
1763796,
#endif

// placeholder for viking_room
0

};
#endif

} // namespace Geometry
