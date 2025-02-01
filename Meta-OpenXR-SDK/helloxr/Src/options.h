
// options.h

inline XrFormFactor GetXrFormFactor(const std::string& formFactorStr)
{
  if(EqualsIgnoreCase(formFactorStr, "Hmd") )
  {
    return XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;
  }

  if(EqualsIgnoreCase(formFactorStr, "Handheld") )
  {
    return XR_FORM_FACTOR_HANDHELD_DISPLAY;
  }

  throw std::invalid_argument(Fmt("Unknown form factor '%s'", formFactorStr.c_str() ) );
}

inline XrViewConfigurationType GetXrViewConfigurationType(const std::string& viewConfigurationStr)
{
  if(EqualsIgnoreCase(viewConfigurationStr, "Mono") )
  {
    return XR_VIEW_CONFIGURATION_TYPE_PRIMARY_MONO;
  }

  if(EqualsIgnoreCase(viewConfigurationStr, "Stereo") )
  {
    return XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO;
  }

  throw std::invalid_argument(Fmt("Unknown view configuration '%s'", viewConfigurationStr.c_str() ) );
}

inline XrEnvironmentBlendMode GetXrEnvironmentBlendMode(const std::string& environmentBlendModeStr)
{
  if(EqualsIgnoreCase(environmentBlendModeStr, "Opaque") )
  {
    return XR_ENVIRONMENT_BLEND_MODE_OPAQUE;
  }

  if(EqualsIgnoreCase(environmentBlendModeStr, "Additive") )
  {
    return XR_ENVIRONMENT_BLEND_MODE_ADDITIVE;
  }

  if(EqualsIgnoreCase(environmentBlendModeStr, "AlphaBlend") )
  {
    return XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND;
  }

  throw std::invalid_argument(Fmt("Unknown environment blend mode '%s'", environmentBlendModeStr.c_str() ) );
}

inline const char* GetXrEnvironmentBlendModeStr(XrEnvironmentBlendMode environmentBlendMode)
{
  switch(environmentBlendMode)
  {

  case XR_ENVIRONMENT_BLEND_MODE_OPAQUE:
    return "Opaque";

  case XR_ENVIRONMENT_BLEND_MODE_ADDITIVE:
    return "Additive";

  case XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND:
    return "AlphaBlend";

  default:
    throw std::invalid_argument(Fmt("Unknown environment blend mode '%s'", to_string(environmentBlendMode) ) );

  }
}

inline void Options_SetEnvironmentBlendMode(XrEnvironmentBlendMode /*environmentBlendMode*/)
{
  // environmentBlendMode
  // nop
}

inline void _operator_assign(std::array<float, 4>& lhs, const float rhs[4] )
{
  lhs[0] = rhs[0];
  lhs[1] = rhs[1];
  lhs[2] = rhs[2];
  lhs[3] = rhs[3];
}

inline void _operator_assign(float lhs[4], const std::array<float, 4>& rhs)
{
  lhs[0] = rhs[0];
  lhs[1] = rhs[1];
  lhs[2] = rhs[2];
  lhs[3] = rhs[3];
}

inline void _operator_assign(float lhs[4], float rhs)
{
  lhs[0] = rhs;
  lhs[1] = rhs;
  lhs[2] = rhs;
  lhs[3] = rhs;
}

inline void _operator_assign(std::array<float, 4>& lhs, float rhs)
{
  lhs[0] = rhs;
  lhs[1] = rhs;
  lhs[2] = rhs;
  lhs[3] = rhs;
}

constexpr char gOptions_GraphicsPlugin[] {'V', 'u', 'l', 'k', 'a', 'n', 0};

constexpr char gOptions_StringFormFactor[] {'H', 'm', 'd', 0};

constexpr char gOptions_StringViewConfigurationType[] {'S', 't', 'e', 'r', 'e', 'o', 0};

constexpr char gOptions_StringEnvironmentBlendMode[] {'O', 'p', 'a', 'q', 'u', 'e', 0};

constexpr char gOptions_AppSpace[] {'L', 'o', 'c', 'a', 'l', 0};

constexpr XrFormFactor gOptions_XrFormFactor {XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY};

constexpr XrViewConfigurationType gOptions_XrViewConfigurationType {XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO};

//XR_ENVIRONMENT_BLEND_MODE_OPAQUE
//XR_ENVIRONMENT_BLEND_MODE_ADDITIVE
//XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND
constexpr XrEnvironmentBlendMode gOptions_XrEnvironmentBlendMode {XR_ENVIRONMENT_BLEND_MODE_OPAQUE/*XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND*/};

constexpr float gOptions_SlateGrey[4] {0.184313729f, 0.309803933f, 0.309803933f, 1.0f};
constexpr float gOptions_Grey[4] {0.5f, 0.5f, 0.5f, 1.0f};
constexpr float gOptions_TransparentBlack[4] {0.0f, 0.0f, 0.0f, 0.0f};
constexpr float gOptions_Black[4] {0.0f, 0.0f, 0.0f, 1.0f};

// gOptions_BackgroundClearColor = gOptions_TransparentBlack
constexpr float gOptions_BackgroundClearColor[4] {0.0f, 0.0f, 0.0f, 0.0f};
