
// particle.h
//
// menu particle system interface
//
// robert aldridge
//
// if in a multithreaded environment,
// cannot handle multiple simultaneous
// calls to particle functions
// ...
// because of globals
//
// many thanks to the jeff lander article:
// the ocean spray in your face (july 1998 game developer)

// always call particlesystemsinitgraphics at start of program
// and when reloading between screen modes
//
// call it every program loop if necessary!

extern void
ParticleSystemsInitGraphics
(
  void* backBufferPixelPointer,
  int backBufferViewPortWidth,
  int backBufferViewPortHeight,
  int backBufferBitDepth,
  int backBufferPitch
);

////////////////////////////////////////////////////////////////////////////////////////////////////

// loads the particle systems specified in the file
// destroys existing particle system if not 0
// return new particle system
// does nothing else if filename is 0
extern PARTICLE_SYSTEMS_HEAD*
ParticleSystemsLoadFileAndActivate
(
  PARTICLE_SYSTEMS_HEAD** particleSystems,
  char* filename,

  float currentTime
);

////////////////////////////////////////////////////////////////////////////////////////////////////

// adds a particle system specified in the
// file, does nothing if filename is 0
extern void
ParticleSystemsAddFileAndActivate
(
  PARTICLE_SYSTEMS_HEAD** particleSystems,
  char* filename,

  float currentTime
);

////////////////////////////////////////////////////////////////////////////////////////////////////

// adds a particle system to the list
// input is assumed to be normalized between -1 and 1 for x, y, z
// and between 0 and 1 for r, g, b
// clipping is x:[-1, 1] y:[-1, 1] z:[0, 1]
//
// angles are specified in radians
// speed and force are normalized
//
// if input is not normalized, set first two characters
// of name to "OS" to have variables normalized
// from x:[0, BackBufferViewPortWidth - 1] y:[0, BackBufferViewPortHeight - 1] z:[-1, 1]
// r:[0, 255] g:[0, 255] b:[0, 255]
//
// converts angles from degrees to radians
// speed is normalized based on BackBufferViewPortWidth
// force is normalized based on BackBufferViewPortWidth and BackBufferViewPortHeight
extern void
ParticleSystemsAddAndActivate
(
  PARTICLE_SYSTEMS_HEAD** particleSystems,

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
);

////////////////////////////////////////////////////////////////////////////////////////////////////

// reactivates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are reactivated
extern void
ParticleSystemsReActivate
(
  PARTICLE_SYSTEMS_HEAD** particleSystems,
  char* particleSystemName,

  float currentTime
);

////////////////////////////////////////////////////////////////////////////////////////////////////

// updates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are updated
extern void
ParticleSystemsUpdate
(
  PARTICLE_SYSTEMS_HEAD** particleSystems,
  char* particleSystemName,

  float currentTime
);

////////////////////////////////////////////////////////////////////////////////////////////////////

// draws the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are drawn
extern void
ParticleSystemsDraw
(
  PARTICLE_SYSTEMS_HEAD** particleSystems,
  char* particleSystemName,

  // 4x4 world to camera transformation matrix
  float* matrix
);

////////////////////////////////////////////////////////////////////////////////////////////////////

// updates and draws the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are updated and drawn
extern void
ParticleSystemsUpdateAndDraw
(
  PARTICLE_SYSTEMS_HEAD** particleSystems,
  char* particleSystemName,

  // 4x4 world to camera transformation matrix
  float* matrix,

  float currentTime
);

////////////////////////////////////////////////////////////////////////////////////////////////////

// terminates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is 0, all particle
// systems are terminated
extern void
ParticleSystemsTerminate
(
  PARTICLE_SYSTEMS_HEAD** particleSystems,
  char* particleSystemName
);
