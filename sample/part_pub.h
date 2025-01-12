// part_pub.h
//
// particle system from Jeff Lander article
// The Ocean Spray in Your Face July 1998 Game Developer
//
// editor Robert Aldridge

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __EMITTER *PEMITTER;

// creates dynamic memory for a particle system structure
// creates dynamic memory for the particles of that system
//
// if emitterLife <= 0 then the lifetime of the particle system is infinite
//
// initializes and returns the dynamically allocated particle system
PEMITTER
CreateParticleSystem
(
	char        *name,														// EMITTER NAME
	float       currentTime,												// CURRENT TIME IN SECONDS
	float       emitterLife,												// HOW LONG WILL THE PARTICLE SYSTEM LAST - IN SECONDS
	// TRANSFORMATION INFO
	float       posX,           float posY,           float posZ,			// XYZ POSITION OF PARTICLE SYSTEM ORIGIN AND VARIATION
	float       posVarX,        float posVarY,        float posVarZ,
	float       yaw,            float yawVar,								// YAW AND VARIATION FOR VELOCITY
	float       pitch,          float pitchVar,								// PITCH AND VARIATION FOR VELOCITY
	float       speed,          float speedVar,								// VELOCITY MAGNITUDE AND VARIATION
	// PARTICLE
	int         numParticles,												// TOTAL EMITTED AT ANY TIME
	int         emitsPerFrame,  int   emitVar,								// EMITS PER FRAME AND VARIATION
	float       life,           float lifeVar,								// LIFETIME OF PARTICLES AND VARIATION

	float       startColorR,    float startColorG,    float startColorB,    // START COLOR OF PARTICLES AND VARIATION
	float       startColorVarR, float startColorVarG, float startColorVarB,
	float       endColorR,      float endColorG,      float endColorB,      // END COLOR OF PARTICLES AND VARIATION
	float		endColorVarR,   float endColorVarG,   float endColorVarB,
	// PHYSICS
	float       gForceX,        float gForceY,        float gForceZ,        // GLOBAL GRAVITY, WIND, ETC. AND VARIATION
	float       gForceVarX,     float gForceVarY,     float gForceVarZ
);

// initializes the particles of a particle system
//
// if the particles have already been activated, they are reset
//
// if the particle system has died, it will be destroyed and nulled out
void
ActivateParticleSystem(PEMITTER     *particleSystem, // PREVIOUSLY CREATED PARTICLE SYSTEM

					   float         currentTime,    // CURRENT TIME IN SECONDS

					   unsigned char antiAlias,      // IF NOT SET TO 0, PARTICLES WILL BE SHADED LINES
													 // IF SET TO 0, PARTICLES WILL BE COLORED POINTS

					   unsigned char physics,        // IF NOT SET TO 0, ACCELERATION WILL BE INTEGRATED
													     // INTO PARTICLES
											             // IF SET TO 0, ONLY VELOCITY WILL BE TAKEN
												         // INTO ACCOUNT

					   unsigned char regeneration    // IF NOT SET TO 0, DEAD PARTICLES WILL BE
													     // REGENERATED
													     // IF SET TO 0, DEAD PARTICLES WILL NOT BE
												         // REGENERATED
                      );

// updates the particles of a particle system
//
// if the particle system has died, it will be destroyed and nulled out
void
UpdateParticleSystem
(
	PEMITTER      *particleSystem,								 // PREVIOUSLY CREATED PARTICLE SYSTEM
	float         currentTime,									 // CURRENT TIME IN SECONDS

	unsigned char gForce,										 // IF NOT SET TO 0, THE NEW GFORCE VECTOR WILL BE
																 // PERMANENTLY APPLIED TO THE PARTICLE SYSTEM
																 // IF SET TO 0, NEW GFORCE IS IGNORED

	float         gForceX,    float gForceY,    float gForceZ,   // GLOBAL GRAVITY, WIND, ETC. AND VARIATION
	float         gForceVarX, float gForceVarY, float gForceVarZ
);

#define UPDATE_PARTICLE_SYSTEM(PARTICLE_SYSTEM,CURRENT_TIME) \
	UpdateParticleSystem(PARTICLE_SYSTEM,CURRENT_TIME,0,0,0,0,0,0,0)

// draws the particles of a particle system, does not update them
//
// if the particle system has died, it will be destroyed and nulled out
void
DrawParticleSystem(PEMITTER *particleSystem,     // PREVIOUSLY CREATED PARTICLE SYSTEM
				   float    *matrix              // 4x4 world to camera transformation matrix
                  );

// destroys the particle system and nulls it out
void
TerminateParticleSystem(PEMITTER *particleSystem // PREVIOUSLY CREATED PARTICLE SYSTEM
                       );

#ifdef __cplusplus
}
#endif