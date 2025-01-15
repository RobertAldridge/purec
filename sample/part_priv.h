// part_priv.h
//
// particle system from Jeff Lander article
// The Ocean Spray in Your Face July 1998 Game Developer
//
// editor Robert Aldridge

// Vectors in homogeneous space...
typedef struct __VECTOR
{
  union
  {
    struct
    {
      float x,y,z,w; // currently w always 1 or 0
    };

    float vector[4];
  };

}VECTOR,*PVECTOR;

typedef struct __COLOR
{
  union
  {
    struct
    {
      float red,green,blue,intensity; // red, green and blue colors ( 0 to 1 float ~ 0 to 255 i32 )
                      // currently intensity always 1 or 0
    };

    struct
    {
      float r,g,b,i;
    };

    float color[4];
  };

}COLOR,*PCOLOR;

typedef enum PFLAGS
{
  PARTICLE_UNBORN=0,
  PARTICLE_ACTIVE,
  PARTICLE_DEAD

}PFLAGS;

typedef struct __PARTICLE // STRUCT FOR SINGLE PARTICLE
{
  VECTOR pos;        // CURRENT POSITION
  VECTOR prevPos;    // PREVIOUS POSITION
  VECTOR velocity;   // CURRENT DIRECTION OF VELOCITY WITH SPEED

  PFLAGS flags;      // PARTICLE FLAGS
  float    life;       // HOW LONG WILL THE PARTICLE LAST AFTER IT IS BORN - IN SECONDS
  COLOR  color;      // CURRENT COLOR OF PARTICLE
  COLOR  prevColor;  // PREVIOUS COLOR OF PARTICLE
  COLOR  deltaColor; // CHANGE OF COLOR OVER TIME

}PARTICLE,*PPARTICLE;

typedef struct __EMITTER // STRUCT FOR PARTICLE SYSTEM
{
  int32_t       id;              // EMITTER ID
  char        name[82];            // EMITTER NAME
  uint8_t padding[2];
  uint32_t       flags;            // EMITTER FLAGS
  float       startTime;           // PARTICLE SYSTEM MOMENT OF CREATION - IN SECONDS
  float       prevTime;              // LAST TIME PARTICLE SYSTEM FUNCTION WAS CALLED
  float       emitterLife;                   // HOW LONG WILL THE PARTICLE SYSTEM LAST - IN SECONDS
  // TRANSFORMATION INFO
  VECTOR    pos,   posVar;         // XYZ POSITION OF PARTICLE SYSTEM ORIGIN
  float       yaw,   yawVar;         // YAW AND VARIATION FOR VELOCITY
  float       pitch, pitchVar;         // PITCH AND VARIATION FOR VELOCITY
  float       speed, speedVar;         // VELOCITY MAGNITUDE AND VARIATION
  // PARTICLE
  PPARTICLE particles;           // PARTICLE POOL - ARRAY OF PARTICLES
  int32_t       totalParticles;                // NUMBER OF PARTICLES IN POOL
  int32_t       numParticles;                  // NUMBER OF PARTICLES CURRENTLY ACTIVE
  int32_t       emitsPerFrame,  emitVar;       // EMITS PER FRAME AND VARIATION
  float       life,           lifeVar;       // LIFETIME OF PARTICLES AND VARIATION
  COLOR     startColor,     startColorVar; // START COLOR OF PARTICLES AND VARIATION
  COLOR     endColor,       endColorVar;   // END COLOR OF PARTICLES AND VARIATION
  // PHYSICS
  VECTOR    gForce,gForceVar;        // GLOBAL GRAVITY, WIND, ETC. AND VARIATION

}EMITTER,*PEMITTER;
