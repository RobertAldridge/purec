
// emitter.cpp
//
// particle system from Jeff Lander article
// The Ocean Spray in Your Face July 1998 Game Developer
//
// editor Robert Aldridge

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include "video.h"

#include "emitter.h"

// vectors in homogeneous space...
struct VECTOR
{
  union
  {
    struct
    {
      float x;
      float y;
      float z;

      // currently w always 1 or 0
      float w;
    };

    float vector[4];
  };
};

struct COLOR
{
  union
  {
    struct
    {
      // red, green and blue colors (0 to 1 float ~ 0 to 255 int32_t)
      float red;
      float green;
      float blue;

      // currently intensity always 1 or 0
      float intensity;
    };

    struct
    {
      float r;
      float g;
      float b;

      float i;
    };

    float color[4];
  };

};

enum PFLAGS
{
  PARTICLE_UNBORN = 0,
  PARTICLE_ACTIVE,
  PARTICLE_DEAD
};

// struct for single particle
struct PARTICLE
{
  // current position
  VECTOR pos;

  // previous position
  VECTOR prevPos;

  // current direction of velocity with speed
  VECTOR velocity;

  // particle flags
  PFLAGS flags;

  // how long will the particle last after it is born - in seconds
  float life;

  // current color of particle
  COLOR color;

  // previous color of particle
  COLOR prevColor;

  // change of color over time
  COLOR deltaColor;
};

// struct for particle system
struct EMITTER
{
  int32_t id; // EMITTER ID

  char name[82]; // EMITTER NAME

  uint8_t padding[2];

  // emitter flags
  uint32_t flags;

  // particle system moment of creation - in seconds
  float startTime;

  // last time particle system function was called
  float prevTime;

  // how long will the particle system last - in seconds
  float emitterLife;

  // transformation info

  // xyz position of particle system origin
  VECTOR pos;
  VECTOR posVar;

  // yaw and variation for velocity
  float yaw;
  float yawVar;

  // pitch and variation for velocity
  float pitch;
  float pitchVar;

  // velocity magnitude and variation
  float speed;
  float speedVar;

  // particle

  // particle pool - array of particles
  PARTICLE* particles;

  // number of particles in pool
  int32_t totalParticles;

  // number of particles currently active
  int32_t numParticles;

  // emits per frame and variation
  int32_t emitsPerFrame;
  int32_t emitVar;

  // lifetime of particles and variation
  float life;
  float lifeVar;

  // start color of particles and variation
  COLOR startColor;
  COLOR startColorVar;

  // end color of particles and variation
  COLOR endColor;
  COLOR endColorVar;

  // physics

  // global gravity, wind, etc. and variation
  VECTOR gForce;
  VECTOR gForceVar;
};

// calculates float between -1 and 1
#define RND() ( (float)rand() / ( (float)(RAND_MAX >> 1) ) - 1)

#define ROTATE(PITCH, YAW, DIRECTION) \
do \
{ \
  (DIRECTION).x = (float)( -sin(YAW) * cos(PITCH) ); \
  (DIRECTION).y = (float)(sin(PITCH) ); \
  (DIRECTION).z = (float)(cos(PITCH) * cos(YAW) ); \
  (DIRECTION).w = 0; \
\
}while(0)

#define ANTI_ALIAS_BIT 1
#define INFINITE_LIFE_BIT 2
#define PHYSICS_BIT 4
#define REGENERATE_BIT 8

static int32_t id;

static uint8_t __LinearFrameBufferGetBitDepth();

static uint8_t** __LinearFrameBufferGetBackBufferArray();

// creates dynamic memory for a particle system structure
// creates dynamic memory for the particles of that system
//
// if emitterLife <= 0 then the lifetime of the particle system is infinite
//
// initializes and returns the dynamically allocated particle system
EMITTER* CreateParticleSystem
(
  // emitter name
  char* name,

  // current time in seconds
  float currentTime,

  // how long will the particle system last - in seconds
  float emitterLife,

  // transformation info

  // xyz position of particle system origin and variation
  float posX, float posY, float posZ,
  float posVarX, float posVarY, float posVarZ,

  // yaw and variation for velocity
  float yaw,
  float yawVar,

  // pitch and variation for velocity
  float pitch,
  float pitchVar,

  // velocity magnitude and variation
  float speed,
  float speedVar,

  // particle

  // total emitted at any time
  int32_t numParticles,

  // emits per frame and variation
  int32_t emitsPerFrame,
  int32_t emitVar,

  // lifetime of particles and variation
  float life,
  float lifeVar,

  // start color of particles and variation
  float startColorR, float startColorG, float startColorB,
  float startColorVarR, float startColorVarG, float startColorVarB,

  // end color of particles and variation
  float endColorR, float endColorG, float endColorB,
  float endColorVarR, float endColorVarG, float endColorVarB,

  // physics

  // global gravity, wind, etc. and variation
  float gForceX, float gForceY, float gForceZ,
  float gForceVarX, float gForceVarY, float gForceVarZ
)
{
  EMITTER* particleSystem = (EMITTER*)calloc(1, sizeof(EMITTER) );
  if( !particleSystem)
    goto label_return;

  particleSystem->particles = (PARTICLE*)calloc(1, sizeof(PARTICLE) * numParticles);
  if( !particleSystem->particles)
  {
    free(particleSystem);
    particleSystem = 0;
    goto label_return;
  }

  particleSystem->id = id++;

  strcpy(particleSystem->name, name);

  if(emitterLife <= 0)
    particleSystem->flags |= INFINITE_LIFE_BIT;
  else
    particleSystem->emitterLife = emitterLife;

  assert(emitsPerFrame > 0 && life > 0 && numParticles > 0);

  particleSystem->startTime = currentTime;
  particleSystem->prevTime = currentTime;
  particleSystem->pos.x = posX;
  particleSystem->pos.y = posY;
  particleSystem->pos.z = posZ;
  particleSystem->pos.w = 1;
  particleSystem->posVar.x = posVarX;
  particleSystem->posVar.y = posVarY;
  particleSystem->posVar.z = posVarZ;
  particleSystem->posVar.w = 0;
  particleSystem->yaw = yaw;
  particleSystem->yawVar = yawVar;
  particleSystem->pitch = pitch;
  particleSystem->pitchVar = pitchVar;
  particleSystem->speed = speed;
  particleSystem->speedVar = speedVar;
  particleSystem->totalParticles = numParticles;
  particleSystem->numParticles = 0;
  particleSystem->emitsPerFrame = emitsPerFrame;
  particleSystem->emitVar = emitVar;
  particleSystem->life = life;
  particleSystem->lifeVar = lifeVar;
  particleSystem->startColor.r = startColorR;
  particleSystem->startColor.g = startColorG;
  particleSystem->startColor.b = startColorB;
  particleSystem->startColor.i = 1;
  particleSystem->startColorVar.r = startColorVarR;
  particleSystem->startColorVar.g = startColorVarG;
  particleSystem->startColorVar.b = startColorVarB;
  particleSystem->startColorVar.i = 0;
  particleSystem->endColor.r = endColorR;
  particleSystem->endColor.g = endColorG;
  particleSystem->endColor.b = endColorB;
  particleSystem->endColor.i = 1;
  particleSystem->endColorVar.r = endColorVarR;
  particleSystem->endColorVar.g = endColorVarG;
  particleSystem->endColorVar.b = endColorVarB;
  particleSystem->endColorVar.i = 0;
  particleSystem->gForce.x = gForceX;
  particleSystem->gForce.y = gForceY;
  particleSystem->gForce.z = gForceZ;
  particleSystem->gForce.w = 0;
  particleSystem->gForceVar.x = gForceVarX;
  particleSystem->gForceVar.y = gForceVarY;
  particleSystem->gForceVar.z = gForceVarZ;
  particleSystem->gForceVar.w = 0;

label_return:
  return particleSystem;
}

// initializes the particles of a particle system
//
// if the particles have already been activated, they are reset
//
// if the particle system has died, it will be destroyed and nulled out
void ActivateParticleSystem
(
  // previously created particle system
  EMITTER** _particleSystem,

  // current time in seconds
  float currentTime,

  // if not set to 0, particles will be shaded lines
  //
  // if set to 0, particles will be colored points
  uint8_t antiAlias,

  // if not set to 0, acceleration will be integrated
  // into particles
  //
  // if set to 0, only velocity will be taken
  // into account
  uint8_t physics,

  // if not set to 0, dead particles will be
  // regenerated
  //
  // if set to 0, dead particles will not be
  // regenerated
  uint8_t regeneration
)
{
  float deltaTime = 0;

  float pitch = 0;
  float yaw = 0;

  float speed = 0;
  float speed_y_factor = 0;

  uint32_t totalParticles = 0;

  COLOR start;
  COLOR end;

  EMITTER* particleSystem = 0;

  PARTICLE* particle = 0;

  memset( &start, 0, sizeof(COLOR) );
  memset( &end, 0, sizeof(COLOR) );

  if( !_particleSystem || !_particleSystem[0] || !_particleSystem[0]->particles)
    goto label_return;

  particleSystem = _particleSystem[0];

  deltaTime = currentTime - particleSystem->prevTime;

  particleSystem->prevTime = currentTime;

  if( !(particleSystem->flags & INFINITE_LIFE_BIT) )
  {
    particleSystem->emitterLife -= deltaTime;

    if(particleSystem->emitterLife <= 0)
    {
      TerminateParticleSystem(_particleSystem);
      goto label_num;
    }
  }

  if(antiAlias)
    particleSystem->flags |= ANTI_ALIAS_BIT;
  else
    particleSystem->flags &= ~ANTI_ALIAS_BIT;

  if(physics)
    particleSystem->flags |= PHYSICS_BIT;
  else
    particleSystem->flags &= ~PHYSICS_BIT;

  if(regeneration)
    particleSystem->flags |= REGENERATE_BIT;
  else
    particleSystem->flags &= ~REGENERATE_BIT;

  particle = particleSystem->particles;

  totalParticles = (uint32_t)particleSystem->totalParticles;

  speed_y_factor = (float)__LinearFrameBufferGetHeight() / (float)__LinearFrameBufferGetWidth();

  do
  {
    // set particle starting position to origin of particle system
    particle->prevPos.x = particle->pos.x = particleSystem->pos.x + (particleSystem->posVar.x * RND() );
    particle->prevPos.y = particle->pos.y = particleSystem->pos.y + (particleSystem->posVar.y * RND() );
    particle->prevPos.z = particle->pos.z = particleSystem->pos.z + (particleSystem->posVar.z * RND() );
    particle->prevPos.w = particle->pos.w = particleSystem->pos.w + (particleSystem->posVar.w * RND() );

    // set particle starting velocity vector
    yaw = particleSystem->yaw + (particleSystem->yawVar * RND() );

    pitch = particleSystem->pitch + (particleSystem->pitchVar * RND() );

    ROTATE(pitch, yaw, particle->velocity);

    speed = particleSystem->speed + (particleSystem->speedVar * RND() );

    particle->velocity.x *= speed;
    particle->velocity.y *= speed * speed_y_factor;
    particle->velocity.z *= speed;

    // set particle flags
    particle->flags = PARTICLE_UNBORN;

    // calculate lifetime of particle
    particle->life = particleSystem->life + (particleSystem->lifeVar * RND() );

    // calculate colors
    start.r = particleSystem->startColor.r + (particleSystem->startColorVar.r * RND() );
    start.g = particleSystem->startColor.g + (particleSystem->startColorVar.g * RND() );
    start.b = particleSystem->startColor.b + (particleSystem->startColorVar.b * RND() );
    start.i = particleSystem->startColor.i + (particleSystem->startColorVar.i * RND() );

    end.r = particleSystem->endColor.r + (particleSystem->endColorVar.r * RND() );
    end.g = particleSystem->endColor.g + (particleSystem->endColorVar.g * RND() );
    end.b = particleSystem->endColor.b + (particleSystem->endColorVar.b * RND() );
    end.i = particleSystem->endColor.i + (particleSystem->endColorVar.i * RND() );

    particle->prevColor.r = particle->color.r = start.r;
    particle->prevColor.g = particle->color.g = start.g;
    particle->prevColor.b = particle->color.b = start.b;
    particle->prevColor.i = particle->color.i = start.i;

    // color change per second
    particle->deltaColor.r = (end.r - start.r) / particle->life;
    particle->deltaColor.g = (end.g - start.g) / particle->life;
    particle->deltaColor.b = (end.b - start.b) / particle->life;
    particle->deltaColor.i = (end.i - start.i) / particle->life;

    ++particle;

  }while( --totalParticles);

label_num:

label_return:
  return;
}

// updates the particles of a particle system
//
// if the particle system has died, it will be destroyed and nulled out
extern void
UpdateParticleSystem
(
  // previously created particle system
  EMITTER** _particleSystem,

  // current time in seconds
  float currentTime,

  // if not set to 0, the new gforce vector will be
  // permanently applied to the particle system
  //
  // if set to 0, new gforce is ignored
  uint8_t gForce,

  // global gravity, wind, etc. and variation
  float gForceX, float gForceY, float gForceZ,
  float gForceVarX, float gForceVarY, float gForceVarZ
)
{
  float deltaTime = 0;

  float pitch = 0;
  float yaw = 0;

  float speed = 0;
  float speed_y_factor = 0;

  float ax = 0;
  float ay = 0;
  float az = 0;
  float aw = 0;

  float t = 0;

  uint32_t totalParticles = 0;

  int32_t emitsPerFrame = 0;

  COLOR start;
  COLOR end;

  EMITTER* particleSystem = 0;
  PARTICLE* particle = 0;

  memset( &start, 0, sizeof(COLOR) );
  memset( &end, 0, sizeof(COLOR) );

  if( !_particleSystem || !_particleSystem[0] || !_particleSystem[0]->particles)
    goto label_return;

  particleSystem = *_particleSystem;

  deltaTime = currentTime - particleSystem->prevTime;

  particleSystem->prevTime = currentTime;

  if( !(particleSystem->flags & INFINITE_LIFE_BIT) )
  {
    particleSystem->emitterLife -= deltaTime;

    if(particleSystem->emitterLife <= 0)
    {
      TerminateParticleSystem(_particleSystem);
      goto label_num;
    }
  }

  if(gForce)
  {
    particleSystem->gForce.x = gForceX;
    particleSystem->gForce.y = gForceY;
    particleSystem->gForce.z = gForceZ;

    particleSystem->gForceVar.x = gForceVarX;
    particleSystem->gForceVar.y = gForceVarY;
    particleSystem->gForceVar.z = gForceVarZ;
  }

  particle = particleSystem->particles;

  totalParticles = (uint32_t)particleSystem->totalParticles;

  emitsPerFrame  = (int32_t)( (float)particleSystem->emitsPerFrame + (float)particleSystem->emitVar * RND() );

  speed_y_factor = ( (float)__LinearFrameBufferGetHeight() / (float)__LinearFrameBufferGetWidth() );

  ax = particleSystem->gForce.x + (particleSystem->gForceVar.x * RND() );
  ay = particleSystem->gForce.y + (particleSystem->gForceVar.y * RND() );
  az = particleSystem->gForce.z + (particleSystem->gForceVar.z * RND() );
  aw = particleSystem->gForce.w + (particleSystem->gForceVar.w * RND() );

  particleSystem->numParticles = 0;

  do
  {
    if(particle->flags == PARTICLE_ACTIVE)
    {
      // save old position for anti_aliasing
      particle->prevPos.x = particle->pos.x;
      particle->prevPos.y = particle->pos.y;
      particle->prevPos.z = particle->pos.z;
      particle->prevPos.w = particle->pos.w;

      // calculate new position
      if(particleSystem->flags & PHYSICS_BIT)
      {
        // integrate acceleration and velocity to find new position
        // r(t) = a * t^2 / 2 + v0 * t + r0
        t = (float)( (deltaTime * deltaTime) * 0.5);

        particle->pos.x += particle->velocity.x * deltaTime + ax * t;
        particle->pos.y += particle->velocity.y * deltaTime + ay * t;
        particle->pos.z += particle->velocity.z * deltaTime + az * t;
        particle->pos.w += particle->velocity.w * deltaTime + aw * t;

        // integrate acceleration to find new velocity
        // v(t) = a * t + v0
        particle->velocity.x += ax * deltaTime;
        particle->velocity.y += ay * deltaTime;
        particle->velocity.z += az * deltaTime;
        particle->velocity.w += aw * deltaTime;
      }
      else
      {
        // just move using current velocity
        particle->pos.x += particle->velocity.x * deltaTime;
        particle->pos.y += particle->velocity.y * deltaTime;
        particle->pos.z += particle->velocity.z * deltaTime;
        particle->pos.w += particle->velocity.w * deltaTime;
      }

      particle->life -= deltaTime;

      if(particle->life <= 0)
        particle->flags = PARTICLE_DEAD;
      else
        ++particleSystem->numParticles;

      // save the old color
      particle->prevColor.r = particle->color.r;
      particle->prevColor.g = particle->color.g;
      particle->prevColor.b = particle->color.b;
      particle->prevColor.i = particle->color.i;

      // get new color
      particle->color.r += particle->deltaColor.r * deltaTime;
      particle->color.g += particle->deltaColor.g * deltaTime;
      particle->color.b += particle->deltaColor.b * deltaTime;
      particle->color.i += particle->deltaColor.i * deltaTime;
    }

    if( (particleSystem->flags & REGENERATE_BIT) && particle->flags == PARTICLE_DEAD)
    {
      // set particle starting position to origin of particle system
      particle->prevPos.x = particle->pos.x = particleSystem->pos.x + (particleSystem->posVar.x * RND() );
      particle->prevPos.y = particle->pos.y = particleSystem->pos.y + (particleSystem->posVar.y * RND() );
      particle->prevPos.z = particle->pos.z = particleSystem->pos.z + (particleSystem->posVar.z * RND() );
      particle->prevPos.w = particle->pos.w = particleSystem->pos.w + (particleSystem->posVar.w * RND() );

      // set particle starting velocity vector
      yaw = particleSystem->yaw + (particleSystem->yawVar * RND() );

      pitch = particleSystem->pitch + (particleSystem->pitchVar * RND() );

      ROTATE(pitch, yaw, particle->velocity);

      speed = particleSystem->speed + (particleSystem->speedVar * RND() );

      particle->velocity.x *= speed;
      particle->velocity.y *= speed * speed_y_factor;
      particle->velocity.z *= speed;

      // set particle flags
      particle->flags = PARTICLE_UNBORN;

      // calculate lifetime of particle
      particle->life = particleSystem->life + (particleSystem->lifeVar * RND() );

      // calculate colors
      start.r = particleSystem->startColor.r + (particleSystem->startColorVar.r * RND() );
      start.g = particleSystem->startColor.g + (particleSystem->startColorVar.g * RND() );
      start.b = particleSystem->startColor.b + (particleSystem->startColorVar.b * RND() );
      start.i = particleSystem->startColor.i + (particleSystem->startColorVar.i * RND() );

      end.r = particleSystem->endColor.r + (particleSystem->endColorVar.r * RND() );
      end.g = particleSystem->endColor.g + (particleSystem->endColorVar.g * RND() );
      end.b = particleSystem->endColor.b + (particleSystem->endColorVar.b * RND() );
      end.i = particleSystem->endColor.i + (particleSystem->endColorVar.i * RND() );

      particle->prevColor.r = particle->color.r = start.r;
      particle->prevColor.g = particle->color.g = start.g;
      particle->prevColor.b = particle->color.b = start.b;
      particle->prevColor.i = particle->color.i = start.i;

      // color change per second
      particle->deltaColor.r = (end.r - start.r) / particle->life;
      particle->deltaColor.g = (end.g - start.g) / particle->life;
      particle->deltaColor.b = (end.b - start.b) / particle->life;
      particle->deltaColor.i = (end.i - start.i) / particle->life;
    }

    ++particle;

  }while( --totalParticles);

  particle = particleSystem->particles;

  totalParticles = (uint32_t)particleSystem->totalParticles;

  if(emitsPerFrame > 0)
  {
    do
    {
      if(particle->flags == PARTICLE_UNBORN)
      {
        --emitsPerFrame;

        ++particleSystem->numParticles;

        particle->flags = PARTICLE_ACTIVE;
      }

      ++particle;

    }while(emitsPerFrame > 0 && --totalParticles);
  }

label_num:

label_return:
  return;
}

static uint8_t LFbitDepth = 32;
static uint8_t** LFbackBufferArray = 0;
static uint16_t LFwidth = 0;
static uint16_t LFheight = 0;

static uint8_t** (*_backBufferFunction)();

void __LinearFrameBufferOSSetBackBuffer(uint8_t** (*__backBufferFunction)(), uint16_t BackBufferViewPortWidth, uint16_t BackBufferViewPortHeight)
{
  _backBufferFunction = (uint8_t** (*)() )__backBufferFunction;

  LFbackBufferArray = _backBufferFunction();

  LFwidth = BackBufferViewPortWidth;
  LFheight = BackBufferViewPortHeight;
}

static uint8_t __LinearFrameBufferGetBitDepth() { return LFbitDepth; }
extern uint16_t __LinearFrameBufferGetWidth() { return LFwidth; }
extern uint16_t __LinearFrameBufferGetHeight() { return LFheight; }

static uint8_t** __LinearFrameBufferGetBackBufferArray() { return LFbackBufferArray; }

// draws the particles of a particle system, does not update them
//
// does not check if the particle system has died
void DrawParticleSystem
(
  // previously created particle system
  EMITTER** _particleSystem,

  // 4x4 world to camera transformation matrix
  float* m
)
{
  uint32_t totalParticles = 0;
  EMITTER* particleSystem = 0;
  PARTICLE* particle = 0;

  // for backbuffer info
  uint8_t antiAlias = 0;
  uint8_t bitDepth = 0;
  uint8_t** bb = 0;
  uint16_t width = 0;
  uint16_t height = 0;
  //

  // for pixel drawing
  float z = 0;

  uint16_t x = 0;
  uint16_t y = 0;

  uint32_t red = 0;
  uint32_t green = 0;
  uint32_t blue = 0;
  //

  // for anti_alias
  float dx;
  float dxstep;
  float dxabs;
  //
  float dy;
  float dystep;
  float dyabs;
  //
  float xi;
  float yi;
  //
  float ri;
  float gi;
  float bi;

  float x0;
  float y0;
  float z0;
  //
  float x1;
  float y1;
  float z1;
  //
  float r0;
  float g0;
  float b0;
  //
  float r1;
  float g1;
  float b1;

  float t;

  uint32_t count;
  //

  LFbackBufferArray = _backBufferFunction();

  if( !_particleSystem || !_particleSystem[0] || !_particleSystem[0]->particles || !LFbackBufferArray || !LFbackBufferArray[0] )
    goto label_return;

  particleSystem = *_particleSystem;

  particle = particleSystem->particles;

  totalParticles = (uint32_t)particleSystem->totalParticles;

  antiAlias = (uint8_t)( (particleSystem->flags & ANTI_ALIAS_BIT) == ANTI_ALIAS_BIT);

  width = __LinearFrameBufferGetWidth();
  height = __LinearFrameBufferGetHeight();

  bitDepth = __LinearFrameBufferGetBitDepth();

  bb = __LinearFrameBufferGetBackBufferArray();

  do
  {
    if(particle->flags == PARTICLE_ACTIVE)
    {
      if(antiAlias)
      {
        x0 = particle->prevPos.x;
        y0 = particle->prevPos.y;
        z0 = particle->prevPos.z;
        //
        r0 = particle->prevColor.r;
        g0 = particle->prevColor.g;
        b0 = particle->prevColor.b;

        x1 = particle->pos.x;
        y1 = particle->pos.y;
        z1 = particle->pos.z;
        //
        r1 = particle->color.r;
        g1 = particle->color.g;
        b1 = particle->color.b;

        if(m)
        {
          float tx = 0;
          float ty = 0;

          tx = (float)(m[0] * x0 + m[1] * y0 + m[2] * z0 + m[3] );
          ty = (float)(m[4] * x0 + m[5] * y0 + m[6] * z0 + m[7] );
          z0 = (float)(m[8] * x0 + m[9] * y0 + m[10] * z0 + m[11] );

          x0 = tx;
          y0 = ty;

          tx = (float)(m[0] * x1 + m[1] * y1 + m[2] * z1 + m[3] );
          ty = (float)(m[4] * x1 + m[5] * y1 + m[6] * z1 + m[7] );
          z1 = (float)(m[8] * x1 + m[9] * y1 + m[10] * z1 + m[11] );

          x1 = tx;
          y1 = ty;
        }

#define xmin -1
#define xmax  1
#define ymin -1
#define ymax  1
#define zmin  0
#define zmax  1

        if( !( (x0 < xmin && x1 < xmin) ||
          (y0 < ymin && y1 < ymin) ||
          (z0 < zmin && z1 < zmin) ||
          (x0 > xmax && x1 > xmax) ||
          (y0 > ymax && y1 > ymax) ||
          (z0 > zmax && z1 > zmax) ) )
        {
          if(x0 >= xmin && x0 <= xmax && x1 >= xmin && x1 <= xmax &&
            y0 >= ymin && y0 <= ymax && y1 >= ymin && y1 <= ymax &&
            z0 >= zmin && z0 <= zmax && z1 >= zmin && z1 <= zmax)
          {
            if(z0 == 0)
              z = .000001f;
            else
              z = z0;

            // coordinates go from [ -1, 1] to [0, width - 1]
            x0 = (float)( (x0 / z + 1.0) * ( ( (float)width - 1.0) / 2.0) );

            // coordinates go from [ -1, 1] to [0, height - 1]
            y0 = (float)( ( -y0 / z + 1.0) * ( ( (float)height - 1.0) / 2.0) );

            if(z1 == 0)
              z = .000001f;
            else
              z = z1;

            // coordinates go from [ -1, 1] to [0, width - 1]
            x1 = (float)( (x1 / z + 1.0) * ( ( (float)width - 1.0) / 2.0) );

            // coordinates go from [ -1, 1] to [0, height - 1]
            y1 = (float)( ( -y1 / z + 1.0) * ( ( (float)height - 1.0) / 2.0) );

            if(r0 <= 0)
              r0 = 0;
            else if(r0 >= 1)
              r0 = 255;
            else
              r0 = (uint8_t)(r0 * 255.0);

            if(g0 <= 0)
              g0 = 0;
            else if(g0 >= 1)
              g0 = 255;
            else
              g0 = (uint8_t)(g0 * 255.0);

            if(b0 <= 0)
              b0 = 0;
            else if(b0 >= 1)
              b0 = 255;
            else
              b0 = (uint8_t)(b0 * 255.0);

            if(r1 <= 0)
              r1 = 0;
            else if(r1 >= 1)
              r1 = 255;
            else
              r1 = (uint8_t)(r1 * 255.0);

            if(g1 <= 0)
              g1 = 0;
            else if(g1 >= 1)
              g1 = 255;
            else
              g1 = (uint8_t)(g1 * 255.0);

            if(b1 <= 0)
              b1 = 0;
            else if(b1 >= 1)
              b1 = 255;
            else
              b1 = (uint8_t)(b1 * 255.0);

            if(x0 >= 0 && (double)x0 <= (width - 1) && y0 >= 0 && (double)y0 <= (height - 1) && z0 >= .000001 && z0 <= 1 &&
              x1 >= 0 && (double)x1 <= (width - 1) && y1 >= 0 && (double)y1 <= (height - 1) && z1 >= .000001 && z1 <= 1)
              goto drawline;
            else
            {
              ++particle;

              continue;
            }
          }

          // front - in to out
          if(z0 >= zmin && z1 < zmin)
          {
            t = z0 - z1;

            if(t == 0)
              t = (zmin - z1) / .000001f;
            else
              t = (zmin - z1) / t;

            x1 += (x0 - x1) * t;
            y1 += (y0 - y1) * t;
            z1  = zmin;

            r1 += (r0 - r1) * t;
            g1 += (g0 - g1) * t;
            b1 += (b0 - b1) * t;
          }
          // front - out to in
          else if(z0 < zmin && z1 >= zmin)
          {
            t = z1 - z0;

            if(t == 0)
              t = (zmin - z0) / .000001f;
            else
              t = (zmin - z0) / t;

            x0 += (x1 - x0) * t;
            y0 += (y1 - y0) * t;
            z0  = zmin;

            r0 += (r1 - r0) * t;
            g0 += (g1 - g0) * t;
            b0 += (b1 - b0) * t;
          }

          // back - in to out
          if(z0 <= zmax && z1 > zmax)
          {
            t = z1 - z0;

            if(t == 0)
              t = (z1 - zmax) / .000001f;
            else
              t = (z1 - zmax) / t;

            x1 += (x1 - x0) * t;
            y1 += (y1 - y0) * t;
            z1  = zmax;

            r1 += (r1 - r0) * t;
            g1 += (g1 - g0) * t;
            b1 += (b1 - b0) * t;
          }
          // back - out to in
          else if(z0 > zmax && z1 <= zmax)
          {
            t = z0 - z1;

            if(t == 0)
              t = (z0 - zmax) / .000001f;
            else
              t = (z0 - zmax) / t;

            x0 += (x0 - x1) * t;
            y0 += (y0 - y1) * t;
            z0  = zmax;

            r0 += (r0 - r1) * t;
            g0 += (g0 - g1) * t;
            b0 += (b0 - b1) * t;
          }

          if(z0 == 0)
            z = .000001f;
          else
            z = z0;

          // coordinates go from [ -1, 1] to [0, width - 1]
          x0 = (float)( (x0 / z + 1.0) * ( ( (float)width - 1.0) / 2.0) );

          // coordinates go from [ -1, 1] to [0, height - 1]
          y0 = (float)( ( -y0 / z + 1.0) * ( ( (float)height - 1.0) / 2.0) );

          if(z1 == 0)
            z = .000001f;
          else
            z = z1;

          // coordinates go from [ -1, 1] to [0, width - 1]
          x1 = (float)( (x1 / z + 1.0) * ( ( (float)width - 1.0) / 2.0) );

          // coordinates go from [ -1, 1] to [0, height - 1]
          y1 = (float)( ( -y1 / z + 1.0) * ( ( (float)height - 1.0) / 2.0) );

#undef xmin
#undef xmax
#undef ymin
#undef ymax

#define xmin 0
#define xmax ( (float)(width - 1) )
#define ymin 0
#define ymax ( (float)(height - 1) )

          // left - in to out
          if(x0 >= xmin && x1 < xmin)
          {
            t = x0 - x1;

            if(t == 0)
              t = (xmin - x1) / .000001f;
            else
              t = (xmin - x1) / t;

            x1  = xmin;
            y1 += (y0 - y1) * t;
            z1 += (z0 - z1) * t;

            r1 += (r0 - r1) * t;
            g1 += (g0 - g1) * t;
            b1 += (b0 - b1) * t;
          }
          // left - out to in
          else if(x0 < xmin && x1 >= xmin)
          {
            t = x1 - x0;

            if(t == 0)
              t = (xmin - x0) / .000001f;
            else
              t = (xmin - x0) / t;

            x0  = xmin;
            y0 += (y1 - y0) * t;
            z0 += (z1 - z0) * t;

            r0 += (r1 - r0) * t;
            g0 += (g1 - g0) * t;
            b0 += (b1 - b0) * t;
          }

          // right - in to out
          if(x0 <= xmax && x1 > xmax)
          {
            t = x1 - x0;

            if(t == 0)
              t = (x1 - xmax) / .000001f;
            else
              t = (x1 - xmax) / t;

            x1  = xmax;
            y1 += (y1 - y0) * t;
            z1 += (z1 - z0) * t;

            r1 += (r1 - r0) * t;
            g1 += (g1 - g0) * t;
            b1 += (b1 - b0) * t;
          }
          // right - out to in
          else if(x0 > xmax && x1 <= xmax)
          {
            t = x0 - x1;

            if(t == 0)
              t = (x0 - xmax) / .000001f;
            else
              t = (x0 - xmax) / t;

            x0  = xmax;
            y0 += (y0 - y1) * t;
            z0 += (z0 - z1) * t;

            r0 += (r0 - r1) * t;
            g0 += (g0 - g1) * t;
            b0 += (b0 - b1) * t;
          }

          // top - in to out
          if(y0 >= ymin && y1 < ymin)
          {
            t = y0 - y1;

            if(t == 0)
              t = (ymin - y1) / .000001f;
            else
              t = (ymin - y1) / t;

            x1 += (x0 - x1) * t;
            y1  = ymin;
            z1 += (z0 - z1) * t;

            r1 += (r0 - r1) * t;
            g1 += (g0 - g1) * t;
            b1 += (b0 - b1) * t;
          }
          // top - out to in
          else if(y0 < ymin && y1 >= ymin)
          {
            t = y1 - y0;

            if(t == 0)
              t = (ymin - y0) / .000001f;
            else
              t = (ymin - y0) / t;

            x0 += (x1 - x0) * t;
            y0  = ymin;
            z0 += (z1 - z0) * t;

            r0 += (r1 - r0) * t;
            g0 += (g1 - g0) * t;
            b0 += (b1 - b0) * t;
          }

          // bottom - in to out
          if(y0 <= ymax && y1 > ymax)
          {
            t = y1 - y0;

            if(t == 0)
              t = (y1 - ymax) / .000001f;
            else
              t = (y1 - ymax) / t;

            x1 += (x1 - x0) * t;
            y1  = ymax;
            z1 += (z1 - z0) * t;

            r1 += (r1 - r0) * t;
            g1 += (g1 - g0) * t;
            b1 += (b1 - b0) * t;
          }
          // bottom - out to in
          else if(y0 > ymax && y1 <= ymax)
          {
            t = y0 - y1;

            if(t == 0)
              t = (y0 - ymax) / .000001f;
            else
              t = (y0 - ymax) / t;

            x0 += (x0 - x1) * t;
            y0  = ymax;
            z0 += (z0 - z1) * t;

            r0 += (r0 - r1) * t;
            g0 += (g0 - g1) * t;
            b0 += (b0 - b1) * t;
          }

          if( !(x0 >= 0 && (double)x0 <= (width - 1) && y0 >= 0 && (double)y0 <= (height - 1) && z0 >= .000001 && z0 <= 1 &&
            x1 >= 0 && (double)x1 <= (width - 1) && y1 >= 0 && (double)y1 <= (height - 1) && z1 >= .000001 && z1 <= 1) )
          {
            ++particle;

            continue;
          }

drawline:

#define i(x)( (uint32_t)x)

#define copy_x_8() *(bb[i(y0) ] + i(x0) ) = (uint8_t)( (i(r0) + i(g0) + i(b0) ) / 3), r0 += ri, g0 += gi, b0 += bi
#define copy_y_8() *(bb[i(y0) ] + i(x0) ) = (uint8_t)( (i(r0) + i(g0) + i(b0) ) / 3), r0 += ri, g0 += gi, b0 += bi

#define copy_x_15() *( ( (uint16_t*)bb[i(y0) ] ) + i(x0) ) = (uint16_t)( ( (i(r0) >> 3) << 10) | ( (i(g0) >> 3) << 5) | i(b0) ), r0 += ri, g0 += gi, b0 += bi
#define copy_y_15() *( ( (uint16_t*)bb[i(y0) ] ) + i(x0) ) = (uint16_t)( ( (i(r0) >> 3) << 10) | ( (i(g0) >> 3) << 5) | i(b0) ), r0 += ri, g0 += gi, b0 += bi

#define copy_x_16() *( ( (uint16_t*)bb[i(y0) ] ) + i(x0) ) = (uint16_t)( ( (i(r0) >> 3) << 11) | ( (i(g0) >> 2) << 5) | i(b0) ), r0 += ri, g0 += gi, b0 += bi
#define copy_y_16() *( ( (uint16_t*)bb[i(y0) ] ) + i(x0) ) = (uint16_t)( ( (i(r0) >> 3) << 11) | ( (i(g0) >> 2) << 5) | i(b0) ), r0 += ri, g0 += gi, b0 += bi

// 24 bit macro is very unoptimized, I suggest not using line drawing in 24 bit mode
#define copy_x_24() *(bb[i(y0) ] + i(x0) * 3) = (uint8_t)i(b0), \
          *(bb[i(y0) ] + i(x0) * 3 + 1) = (uint8_t)i(g0), \
          *(bb[i(y0) ] + i(x0) * 3 + 2) = (uint8_t)i(r0), \
          r0 += ri, g0 += gi, b0 += bi

// 24 bit macro is very unoptimized, I suggest not using line drawing in 24 bit mode
#define copy_y_24() *(bb[i(y0) ] + i(x0) * 3) = (uint8_t)i(b0), \
          *(bb[i(y0) ] + i(x0) * 3 + 1) = (uint8_t)i(g0), \
          *(bb[i(y0) ] + i(x0) * 3 + 2) = (uint8_t)i(r0), \
          r0 += ri, g0 += gi, b0 += bi

#define copy_x_32() *( ( (uint32_t*)bb[i(y0) ] ) + i(x0) ) = ( (i(r0) << 16) | (i(g0) << 8) | i(b0) ), r0 += ri, g0 += gi, b0 += bi
#define copy_y_32() *( ( (uint32_t*)bb[i(y0) ] ) + i(x0) ) = ( (i(r0) << 16) | (i(g0) << 8) | i(b0) ), r0 += ri, g0 += gi, b0 += bi

          dx = x1 - x0;

          (dx >= 0) ?
            (dxstep = 1, dxabs = dx) :
            (dxstep = -1, dxabs = -dx);

          dy = y1 - y0;

          (dy >=0) ?
            (dystep = 1, dyabs = dy) :
            (dystep = -1, dyabs = -dy);

          if(dxabs >= dyabs)
          {
            count = i(dxabs);

            (count == 0) ?
              (yi = 0, ri = 0, gi = 0, bi = 0) :
              (yi = (y1 - y0) / dxabs,
              ri = (r1 - r0) / dxabs,
              gi = (g1 - g0) / dxabs,
              bi = (b1 - b0) / dxabs);

            x0 = (float)floor(x0);
            x1 = (float)floor(x1);
            dxabs = x1 - x0;

            if(dxabs < 0)
              dxabs =- dxabs;

            // comment to use top-left fill rule
            ++count;

            do
            {
              switch(bitDepth)
              {

              case 8: copy_x_8(); break;

              case 15: copy_x_15(); break;

              case 16: copy_x_16(); break;

              case 24: copy_x_24(); break;

              case 32: copy_x_32(); break;

              default:
                assert("DrawParticleSystem - unsupported bit depth" && 0);
              break;

              }

              x0 += dxstep;
              y0 += yi;

            }while( --count);
          }
          else
          {
            count = i(dyabs);

            (count == 0) ?
              (xi = 0, ri = 0, gi = 0, bi = 0) :
              (xi = (x1 - x0) / dyabs,
              ri = (r1 - r0) / dyabs,
              gi = (g1 - g0) / dyabs,
              bi = (b1 - b0) / dyabs);

            y0 = (float)floor(y0);
            y1 = (float)floor(y1);
            dyabs = y1 - y0;

            if(dyabs < 0)
              dyabs =- dyabs;

            // comment to use top-left fill rule
            ++count;

            do
            {
              switch(bitDepth)
              {

              case 8: copy_y_8(); break;

              case 15: copy_y_15(); break;

              case 16: copy_y_16(); break;

              case 24: copy_y_24(); break;

              case 32: copy_y_32(); break;

              default:
                assert("DrawParticleSystem - unsupported bit depth" && 0);
              break;

              }

              y0 += dystep;
              x0 += xi;

            }while( --count != 0);
          }
        }
      }
      else
      {
        z = particle->pos.z;

        if(m)
        {
          float tx = particle->pos.x;
          float ty = particle->pos.y;

          particle->pos.x = (float)(m[0] * tx + m[1] * ty + m[2] * z + m[3] );
          particle->pos.y = (float)(m[4] * tx + m[5] * ty + m[6] * z + m[7] );

          z = (float)(m[8] * tx + m[9] * ty + m[10] * z + m[11] );
        }

        if(z == 0)
          z = .000001f;

        // coordinates go from [ -1, 1] to [0, width - 1]
        x = (uint16_t)( (particle->pos.x / z + 1.0) * ( ( (float)width - 1.0) / 2.0) );

        // coordinates go from [ -1, 1] to [0, height - 1]
        y = (uint16_t)( ( -particle->pos.y / z + 1.0) * ( ( (float)height - 1.0) / 2.0) );

        if(x >= 0 && x < width && y >= 0 && y < height && z >= .000001f && z <= 1)
        {
          if(particle->color.r <= 0)
            red = 0;
          else if(particle->color.r >= 1)
            red = 255;
          else
            red = (uint8_t)(particle->color.r * 255.0);

          if(particle->color.g <= 0)
            green = 0;
          else if(particle->color.g >= 1)
            green = 255;
          else
            green = (uint8_t)(particle->color.g * 255.0);

          if(particle->color.b <= 0)
            blue = 0;
          else if(particle->color.b >= 1)
            blue = 255;
          else
            blue = (uint8_t)(particle->color.b * 255.0);

          switch(__LinearFrameBufferGetBitDepth() )
          {

          case 8:
            *(bb[y] + x) = (uint8_t)( ( ( (uint16_t)red) + ( (uint16_t)green) + ( (uint16_t)blue) ) / 3);
          break;

          case 15:
            *( ( (uint16_t*)bb[y] ) + x) = (uint16_t)( ( ( ( (uint16_t)red) >> 3) << 10) | ( ( ( (uint16_t)green) >> 3) << 5) | ( ( (uint16_t)blue) >> 3) );
          break;

          case 16:
            *( ( (uint16_t*)bb[y] ) + x) = (uint16_t)( ( ( ( (uint16_t)red) >> 3) << 11) | ( ( ( (uint16_t)green) >> 2) << 5) | ( ( (uint16_t)blue) >> 3) );
          break;

          case 24:
            *(bb[y] + x * 3) = (uint8_t)blue;
            *(bb[y] + x * 3 + 1) = (uint8_t)green;
            *(bb[y] + x * 3 + 2) = (uint8_t)red;
          break;

          case 32:
            *( ( (uint32_t*)bb[y] ) + x) = ( ( ( (uint32_t)red) << 16) | ( ( (uint32_t)green) << 8) | ( (uint32_t)blue) );
          break;

          default:
            assert("DrawParticleSystem - unsupported bit depth" && 0);
          break;

          }
        }
      }
    }

    ++particle;

  }while( --totalParticles);

label_return:
  return;
}

// destroys the particle system and nulls it out
//
// emitter** _particlesystem previously created particle system
void TerminateParticleSystem(EMITTER** _particleSystem)
{
  if( !_particleSystem || !_particleSystem[0] || !_particleSystem[0]->particles)
    goto label_return;

  memset(_particleSystem[0]->particles, 0, sizeof(PARTICLE) * _particleSystem[0]->totalParticles);

  free(_particleSystem[0]->particles);

  memset(_particleSystem[0], 0, sizeof(EMITTER) );

  free(_particleSystem[0] );

  _particleSystem[0] = 0;

label_return:
  return;
}
