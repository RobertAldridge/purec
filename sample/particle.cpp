
// particle.cpp
//
// particle system interface
//
// Robert Aldridge
//
// if in a multithreaded environment,
// cannot handle multiple simultaneous
// calls to particle functions
// ...
// because of static global variables currentTime and matrix

//#include <cassert>
//#include <cmath>
//#include <cstdlib>
//#include <cstdio>
//#include <cstring>
//#include <cstdint>

#include "listObject.h"
#include "list.h"

#include "video.h"

#include "emitter.h"

#include "particle.h"

static float currentTime;
static float* matrix;

static int32_t Dead(CLIENT_POTYPE /*Obj1*/, CLIENT_POTYPE Obj2)
{
  int32_t result = 0;

  if( !Obj2.particleSystem)
    result = 1;

  return result;
}

static int32_t Equal(CLIENT_POTYPE Obj1, CLIENT_POTYPE Obj2)
{
  return !strcmp(Obj1.name, Obj2.name);
}

static int32_t Activate(CLIENT_POTYPE* Obj)
{
  if(Obj->particleSystem)
    ActivateParticleSystem( (EMITTER**) &Obj->particleSystem, currentTime, Obj->arg1, Obj->arg2, Obj->arg3);

  return 0;
}

static int32_t Update(CLIENT_POTYPE* Obj)
{
  if(Obj->particleSystem)
    UPDATE_PARTICLE_SYSTEM( (EMITTER**) &Obj->particleSystem, currentTime);

  return 0;
}

static int32_t Draw(CLIENT_POTYPE* Obj)
{
  if(Obj->particleSystem)
    DrawParticleSystem( (EMITTER**) &Obj->particleSystem, matrix);

  return 0;
}

static int32_t Terminate(CLIENT_POTYPE* Obj)
{
  if(Obj->particleSystem)
    TerminateParticleSystem( (EMITTER**) &Obj->particleSystem);

  return 0;
}

static int ParticleSystemsInternalLoad(LIST_HEAD* particleSystems, FILE* file)
{
  float fbuffer[64] = {0};
  int32_t ibuffer[16] = {0};
  CLIENT_POTYPE Obj = {0};

  int result = 0;

  // name
  result += fscanf(file, "%s\n", Obj.name);

  // emitterLife
  result += fscanf(file, "%f\n", &fbuffer[0] );

  // posX posY posZ
  result += fscanf(file, "%f %f %f\n", &fbuffer[1], &fbuffer[2], &fbuffer[3] );

  // posVarX posVarY posVarZ
  result += fscanf(file, "%f %f %f\n", &fbuffer[4], &fbuffer[5], &fbuffer[6] );

  // yaw yawVar
  result += fscanf(file, "%f %f\n", &fbuffer[7], &fbuffer[8] );

  // pitch pitchVar
  result += fscanf(file, "%f %f\n", &fbuffer[9], &fbuffer[10] );

  // speed speedVar
  result += fscanf(file, "%f %f\n", &fbuffer[11], &fbuffer[12] );

  // numParticles
  result += fscanf(file, "%i\n", &ibuffer[0] );

  // emitsPerFrame emitVar
  result += fscanf(file, "%i %i\n", &ibuffer[1], &ibuffer[2] );

  // life lifeVar
  result += fscanf(file, "%f %f\n", &fbuffer[13], &fbuffer[14] );

  // startColorR startColorG startColorB
  result += fscanf(file, "%f %f %f\n", &fbuffer[15], &fbuffer[16], &fbuffer[17] );

  // startColorVarR startColorVarG startColorVarB
  result += fscanf(file, "%f %f %f\n", &fbuffer[18], &fbuffer[19], &fbuffer[20] );

  // endColorR endColorG endColorB
  result += fscanf(file, "%f %f %f\n", &fbuffer[21], &fbuffer[22], &fbuffer[23] );

  // endColorVarR endColorVarG endColorVarB
  result += fscanf(file, "%f %f %f\n", &fbuffer[24], &fbuffer[25], &fbuffer[26] );

  // gForceX gForceY gForceZ
  result += fscanf(file, "%f %f %f\n", &fbuffer[27], &fbuffer[28], &fbuffer[29] );

  // gForceVarX gForceVarY gForceVarZ
  result += fscanf(file, "%f %f %f\n", &fbuffer[30], &fbuffer[31], &fbuffer[32] );

  // antiAlias physics regeneration
  result += fscanf(file, "%i %i %i", &ibuffer[3],  &ibuffer[4],  &ibuffer[5] );

  // if first two characters are "os", then normalize the input
  if(Obj.name && Obj.name[0] && Obj.name[1] && Obj.name[0] == 'O' && Obj.name[1] == 'S')
  {
    float halfWidth = (float)__LinearFrameBufferGetWidth() * 0.5f;
    float halfHeight = (float)__LinearFrameBufferGetHeight() * 0.5f;

    float invHalfWidth  = 1.0f / halfWidth;
    float invHalfHeight = 1.0f / halfHeight;

    float pi2rad = 0.01745329f; // pi / 180

    float colorConv = 0.00392156f; // 1 / 255

    fbuffer[1] = (fbuffer[1] - halfWidth) * invHalfWidth;
    fbuffer[2] = -(fbuffer[2] - halfHeight) * invHalfHeight;

    fbuffer[4] *= invHalfWidth;
    fbuffer[5] *= invHalfHeight;

    fbuffer[7] *= pi2rad;
    fbuffer[8] *= pi2rad;

    fbuffer[9] *= pi2rad;
    fbuffer[10] *= pi2rad;

    fbuffer[11] *= invHalfWidth;
    fbuffer[12] *= invHalfWidth;

    fbuffer[15] *= colorConv;
    fbuffer[16] *= colorConv;
    fbuffer[17] *= colorConv;

    fbuffer[18] *= colorConv;
    fbuffer[19] *= colorConv;
    fbuffer[20] *= colorConv;

    fbuffer[21] *= colorConv;
    fbuffer[22] *= colorConv;
    fbuffer[23] *= colorConv;

    fbuffer[24] *= colorConv;
    fbuffer[25] *= colorConv;
    fbuffer[26] *= colorConv;

    fbuffer[27] *= invHalfWidth;
    fbuffer[28] *= invHalfHeight;

    fbuffer[30] *= invHalfWidth;
    fbuffer[31] *= invHalfHeight;
  }

  Obj.particleSystem = (void*)CreateParticleSystem
  (
    Obj.name,
    currentTime,

    fbuffer[0],

    fbuffer[1], fbuffer[2], fbuffer[3],
    fbuffer[4], fbuffer[5], fbuffer[6],

    fbuffer[7], fbuffer[8],
    fbuffer[9], fbuffer[10],
    fbuffer[11], fbuffer[12],

    ibuffer[0],

    ibuffer[1], ibuffer[2],
    fbuffer[13], fbuffer[14],

    fbuffer[15], fbuffer[16], fbuffer[17],
    fbuffer[18], fbuffer[19], fbuffer[20],

    fbuffer[21], fbuffer[22], fbuffer[23],
    fbuffer[24], fbuffer[25], fbuffer[26],

    fbuffer[27], fbuffer[28], fbuffer[29],
    fbuffer[30], fbuffer[31], fbuffer[32]
  );

  ActivateParticleSystem( (EMITTER**) &Obj.particleSystem, currentTime, (uint8_t)ibuffer[3], (uint8_t)ibuffer[4], (uint8_t)ibuffer[5] );

  Obj.arg1 = (uint8_t)ibuffer[3];
  Obj.arg2 = (uint8_t)ibuffer[4];
  Obj.arg3 = (uint8_t)ibuffer[5];

  ListInsert(particleSystems, Obj, 0);

  result += fscanf(file, "\n\n");

  return result;
}

// loads the particle systems specified in the file
// destroys existing particle system if not 0
// return new particle system
// does nothing else if filename is 0
PARTICLE_SYSTEMS_HEAD* ParticleSystemsLoadFileAndActivate
(
  PARTICLE_SYSTEMS_HEAD** _particleSystems,
  char* filename,

  float _currentTime
)
{
  int32_t Num = 0;
  FILE* file = 0;
  LIST_HEAD* particleSystems = 0;

  int result = 0;

  currentTime = _currentTime;

  ParticleSystemsTerminate(_particleSystems, 0); // ? terminate before verify function parameters ? todo

  if( !filename)
    goto label_return;

  file = fopen(filename, "rb");

  if( !file)
    goto label_return;

  result += fscanf(file, "%i\n\n", &Num);  // NUMBER OF PARTICLE SYSTEMS

  if(Num <= 0)
  {
    fclose(file);

    goto label_return;
  }

  if(Num < 16)
    particleSystems = ListInit(0, 16);
  else
    particleSystems = ListInit(0, Num);

  if( !particleSystems)
  {
    fclose(file);

    goto label_return;
  }

  do
  {
    ParticleSystemsInternalLoad(particleSystems, file);

  }while( --Num);

  fclose(file);

label_return:
  return (PARTICLE_SYSTEMS_HEAD*)particleSystems;
}

// adds a particle system specified in the
// file, does nothing if filename is 0
void ParticleSystemsAddFileAndActivate
(
  PARTICLE_SYSTEMS_HEAD** particleSystemsRef,
  char* filename,

  float _currentTime
)
{
  int32_t Num = 0;
  FILE* file = 0;

  LIST_HEAD** particleSystems = 0;

  int result = 0;

  currentTime = _currentTime;

  if( !particleSystemsRef || !filename)
    goto label_return;

  particleSystems = (LIST_HEAD**)particleSystemsRef;

  file = fopen(filename, "rb");

  if( !file)
    goto label_return;

  result += fscanf(file, "%i\n\n", &Num);  // NUMBER OF PARTICLE SYSTEMS

  if(Num <= 0)
  {
    fclose(file);

    goto label_return;
  }

  if( !particleSystems[0] )
    particleSystems[0] = ListInit(0, 16);

  if( !particleSystems[0] )
  {
    fclose(file);

    goto label_return;
  }

  do
  {
    ParticleSystemsInternalLoad(particleSystems[0], file);

  }while( --Num);

  fclose(file);

label_return:
  return;
}

// adds a particle system to the list
// input is assumed to be normalized between -1 and 1 for x, y, z
// and between 0 and 1 for r, g, b
// clipping is x:[ -1, 1] y:[ -1, 1] z:[0, 1]
//
// angles are specified in radians
// speed and force are normalized
//
// if input is not normalized, set first two characters
// of name to "OS" to have variables normalized
// from x:[0, BackBufferViewPortWidth - 1] y:[0, BackBufferViewPortHeight - 1] z:[ -1, 1]
// r:[0, 255] g:[0, 255] b:[0, 255]
//
// converts angles from degrees to radians
// speed is normalized based on BackBufferViewPortWidth
// force is normalized based on BackBufferViewPortWidth and BackBufferViewPortHeight
void ParticleSystemsAddAndActivate
(
  PARTICLE_SYSTEMS_HEAD** particleSystemsRef,

  // emitter name
  char* name,

  // current time in seconds
  float _currentTime,

  // how long will the particle system last - in seconds
  float emitterLife,

  // transformation info

  // xyz position of particle system origin and variation
  float posX, float posY, float posZ,
  float posVarX, float posVarY, float posVarZ,

  // yaw and variation for velocity
  float yaw, float yawVar,

  // pitch and variation for velocity
  float pitch, float pitchVar,

  // velocity magnitude and variation
  float speed, float speedVar,

  // particle

  // total emitted at any time
  int numParticles,

  // emits per frame and variation
  int emitsPerFrame, int emitVar,

  // lifetime of particles and variation
  float life, float lifeVar,

  // start color of particles and variation
  float startColorR, float startColorG, float startColorB,
  float startColorVarR, float startColorVarG, float startColorVarB,

  // end color of particles and variation
  float endColorR, float endColorG, float endColorB,
  float endColorVarR, float endColorVarG, float endColorVarB,

  // physics

  // global gravity, wind, etc. and variation
  float gForceX, float gForceY, float gForceZ,
  float gForceVarX, float gForceVarY, float gForceVarZ,

  // if not set to 0, particles will be shaded lines
  //
  // if set to 0, particles will be colored points
  unsigned char antiAlias,

  // if not set to 0, acceleration will be integrated
  // into particles
  //
  // if set to 0, only velocity will be taken
  // into account
  unsigned char physics,

  // if not set to 0, dead particles will be
  // regenerated
  //
  // if set to 0, dead particles will not be
  // regenerated
  unsigned char regeneration
)
{
  CLIENT_POTYPE Obj = {0};

  LIST_HEAD** particleSystems = 0;

  if( !particleSystemsRef)
    goto label_return;

  particleSystems = (LIST_HEAD**)particleSystemsRef;

  if( !particleSystems[0] )
    particleSystems[0] = ListInit(0, 16);

  if( !particleSystems[0] )
    goto label_return;

  strcpy(Obj.name, name);

  // if first two characters are "os", then normalize the input
  if(name && name[0] && name[1] && name[0] == 'O' && name[1] == 'S')
  {
    float halfWidth = (float)__LinearFrameBufferGetWidth() * 0.5f;
    float halfHeight = (float)__LinearFrameBufferGetHeight() * 0.5f;

    float invHalfWidth = 1.0f / halfWidth;
    float invHalfHeight = 1.0f / halfHeight;

    float pi2rad = 0.01745329f; // pi / 180

    float colorConv  = 0.00392156f; // 1 / 255

    posX = (posX - halfWidth) * invHalfWidth;
    posY = -(posY - halfHeight) * invHalfHeight;

    posVarX *= invHalfWidth;
    posVarY *= invHalfHeight;

    yaw *= pi2rad;
    yawVar *= pi2rad;

    pitch *= pi2rad;
    pitchVar *= pi2rad;

    speed *= invHalfWidth;
    speedVar *= invHalfWidth;

    startColorR *= colorConv;
    startColorG *= colorConv;
    startColorB *= colorConv;

    startColorVarR *= colorConv;
    startColorVarG *= colorConv;
    startColorVarB *= colorConv;

    endColorR *= colorConv;
    endColorG *= colorConv;
    endColorB *= colorConv;

    endColorVarR *= colorConv;
    endColorVarG *= colorConv;
    endColorVarB *= colorConv;

    gForceX *= invHalfWidth;
    gForceY *= invHalfHeight;

    gForceVarX *= invHalfWidth;
    gForceVarY *= invHalfHeight;
  }

  Obj.particleSystem = (void*)CreateParticleSystem
  (
    Obj.name,
    _currentTime,

    emitterLife,

    posX, posY, posZ,
    posVarX, posVarY, posVarZ,

    yaw, yawVar,
    pitch, pitchVar,
    speed, speedVar,

    numParticles,

    emitsPerFrame, emitVar,
    life, lifeVar,

    startColorR, startColorG, startColorB,
    startColorVarR, startColorVarG, startColorVarB,

    endColorR, endColorG, endColorB,
    endColorVarR, endColorVarG, endColorVarB,

    gForceX, gForceY, gForceZ,
    gForceVarX, gForceVarY, gForceVarZ
  );

  ActivateParticleSystem( (EMITTER**) &Obj.particleSystem, _currentTime, antiAlias, physics, regeneration);

  Obj.arg1 = antiAlias;
  Obj.arg2 = physics;
  Obj.arg3 = regeneration;

  ListInsert(particleSystems[0], Obj, 0);

label_return:
  return;
}

// reactivates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are reactivated
void ParticleSystemsReActivate
(
  PARTICLE_SYSTEMS_HEAD** particleSystemsRef,
  char* particleSystemName,

  float _currentTime
)
{
  CLIENT_POTYPE Obj = {0};

  LIST_HEAD** particleSystems = 0;

  currentTime = _currentTime;

  if( !particleSystemsRef)
    goto label_return;

  particleSystems = (LIST_HEAD**)particleSystemsRef;

  if( !particleSystems[0] )
    goto label_return;

  if(ListIsEmpty(particleSystems[0], 0) )
  {
    ListTerminate(particleSystems[0] );

    particleSystems[0] = 0;

    goto label_num;
  }

  if(particleSystemName)
  {
    strcpy(Obj.name, particleSystemName);

    if( !ListFind(particleSystems[0], Equal, &Obj) )
    {
      Activate( &Obj);

      if( !Obj.particleSystem)
        ListRemove(particleSystems[0], Equal, &Obj);
    }
  }
  else
  {
    ListDump(particleSystems[0], Activate, 0);

    while( !ListRemove(particleSystems[0], Dead, &Obj) )
    {
      /* nop */
    }
  }

label_num:

label_return:
  return;
}

// updates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are updated
void ParticleSystemsUpdate
(
  PARTICLE_SYSTEMS_HEAD** particleSystemsRef,
  char* particleSystemName,

  float _currentTime
)
{
  CLIENT_POTYPE Obj = {0};

  LIST_HEAD** particleSystems = 0;

  currentTime = _currentTime;

  if( !particleSystemsRef)
    goto label_return;

  particleSystems = (LIST_HEAD**)particleSystemsRef;

  if( !particleSystems[0] )
    goto label_return;

  if(ListIsEmpty(particleSystems[0], 0) )
  {
    ListTerminate(particleSystems[0] );
    particleSystems[0] = 0;

    goto label_num;
  }

  if(particleSystemName)
  {
    strcpy(Obj.name, particleSystemName);

    if( !ListFind(particleSystems[0], Equal, &Obj) )
    {
      Update( &Obj);

      if( !Obj.particleSystem)
        ListRemove(particleSystems[0], Equal, &Obj);
    }
  }
  else
  {
    ListDump(particleSystems[0], Update, 0);

    while( !ListRemove(particleSystems[0], Dead, &Obj) )
    {
      /* nop */
    }
  }

label_num:

label_return:
  return;
}

// draws the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are drawn
void ParticleSystemsDraw
(
  PARTICLE_SYSTEMS_HEAD** particleSystemsRef,
  char* particleSystemName,

  // 4x4 world to camera transformation matrix
  float* _matrix
)
{
  CLIENT_POTYPE Obj = {0};

  LIST_HEAD** particleSystems = 0;

  matrix = _matrix;

  if( !particleSystemsRef)
    goto label_return;

  particleSystems = (LIST_HEAD**)particleSystemsRef;

  if( !particleSystems[0] )
    goto label_return;

  if(ListIsEmpty(particleSystems[0], 0) )
  {
    ListTerminate(particleSystems[0] );
    particleSystems[0] = 0;

    goto label_num;
  }

  if(particleSystemName)
  {
    strcpy(Obj.name, particleSystemName);

    if( !ListFind(particleSystems[0], Equal, &Obj) )
      Draw( &Obj);
  }
  else
  {
    ListDump(particleSystems[0], Draw, 0);
  }

label_num:

label_return:
  return;
}

// updates and draws the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are updated and drawn
void ParticleSystemsUpdateAndDraw
(
  PARTICLE_SYSTEMS_HEAD** particleSystemsRef,
  char* particleSystemName,

  // 4x4 world to camera transformation matrix
  float* _matrix,

  float _currentTime
)
{
  CLIENT_POTYPE Obj = {0};

  LIST_HEAD** particleSystems = 0;

  matrix = _matrix;

  currentTime = _currentTime;

  if( !particleSystemsRef)
    goto label_return;

  particleSystems = (LIST_HEAD**)particleSystemsRef;

  if( !particleSystems[0] )
    goto label_return;

  if(ListIsEmpty(particleSystems[0], 0) )
  {
    ListTerminate(particleSystems[0] );
    particleSystems[0] = 0;

    goto label_num;
  }

  if(particleSystemName)
  {
    strcpy(Obj.name, particleSystemName);

    if( !ListFind(particleSystems[0], Equal, &Obj) )
    {
      Update( &Obj);
      Draw( &Obj);

      if( !Obj.particleSystem)
        ListRemove(particleSystems[0], Equal, &Obj);
    }
  }
  else
  {
    ListDump(particleSystems[0], Update, 0);
    ListDump(particleSystems[0], Draw, 0);

    while( !ListRemove(particleSystems[0], Dead, &Obj) )
    {
      /* nop */
    }
  }

label_num:

label_return:
  return;
}

// terminates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are terminated
void ParticleSystemsTerminate
(
  PARTICLE_SYSTEMS_HEAD** particleSystemsRef,
  char* particleSystemName
)
{
  CLIENT_POTYPE Obj = {0};

  LIST_HEAD** particleSystems = 0;

  if( !particleSystemsRef)
    goto label_return;

  particleSystems = (LIST_HEAD**)particleSystemsRef;

  if( !particleSystems[0] )
    goto label_return;

  if(ListIsEmpty(particleSystems[0], 0) )
  {
    ListTerminate(particleSystems[0] );
    particleSystems[0] = 0;

    goto label_num;
  }

  if(particleSystemName)
  {
    strcpy(Obj.name, particleSystemName);

    if( !ListRemove(particleSystems[0], Equal, &Obj) )
      Terminate( &Obj);
  }
  else
  {
    ListDump(particleSystems[0], Terminate, 0);

    ListTerminate(particleSystems[0] );

    particleSystems[0] = 0;
  }

label_num:

label_return:
  return;
}
