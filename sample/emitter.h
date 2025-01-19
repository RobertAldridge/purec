
// emitter.h
//
// particle system from Jeff Lander article
// The Ocean Spray in Your Face July 1998 Game Developer
//
// editor Robert Aldridge

// creates dynamic memory for a particle system structure
// creates dynamic memory for the particles of that system
//
// if emitterLife <= 0 then the lifetime of the particle system is infinite
//
// initializes and returns the dynamically allocated particle system
extern EMITTER* CreateParticleSystem
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
  float gForceVarX, float gForceVarY, float gForceVarZ
);

// initializes the particles of a particle system
//
// if the particles have already been activated, they are reset
//
// if the particle system has died, it will be destroyed and nulled out
extern void ActivateParticleSystem
(
  // previously created particle system
  EMITTER** particleSystem,

  // current time in seconds
  float currentTime,

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

// updates the particles of a particle system
//
// if the particle system has died, it will be destroyed and nulled out
extern void UpdateParticleSystem
(
  // previously created particle system
  EMITTER** particleSystem,

  // current time in seconds
  float currentTime,

  // if not set to 0, the new gforce vector will be
  // permanently applied to the particle system
  // if set to 0, new gforce is ignored
  unsigned char gForce,

  // global gravity, wind, etc. and variation
  float gForceX, float gForceY, float gForceZ,
  float gForceVarX, float gForceVarY, float gForceVarZ
);

#define UPDATE_PARTICLE_SYSTEM(PARTICLE_SYSTEM,CURRENT_TIME) \
  UpdateParticleSystem(PARTICLE_SYSTEM, CURRENT_TIME, 0, 0, 0, 0, 0, 0, 0)

// draws the particles of a particle system, does not update them
//
// if the particle system has died, it will be destroyed and nulled out
void DrawParticleSystem
(
  // previously created particle system
  EMITTER** particleSystem,

  // 4x4 world to camera transformation matrix
  float* matrix
);

// destroys the particle system and nulls it out
void TerminateParticleSystem
(
  // previously created particle system
  EMITTER** particleSystem
);
