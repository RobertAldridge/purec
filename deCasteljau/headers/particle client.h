// particle client.h
//
// menu particle system interface
//
// Robert Aldridge
//
// if in a multithreaded environment,
// cannot handle multiple simultaneous
// calls to particle functions
// ...
// because of a local static global variable used in the engine
//
// Many thanks to the Jeff Lander article:
// The Ocean Spray in Your Face (July 1998 Game Developer)

#ifdef __cplusplus
	extern "C" {
#endif

// ALWAYS CALL ParticleSystemsInitGraphics AT START OF PROGRAM
// AND WHEN RELOADING BETWEEN SCREEN MODES
//
// Call it every program loop if necessary!
      
void
	ParticleSystemsInitGraphics( void * backBufferPixelPointer,
								 int    backBufferViewPortWidth,
								 int    backBufferViewPortHeight,
								 int    backBufferBitDepth,
								 int    backBufferPitch
							   );

typedef struct __PARTICLE_SYSTEMS_HEAD * PPARTICLE_SYSTEMS_HEAD;

////////////////////////////////////////////////////////////////////////////////////////////////////

// loads the particle systems specified in the file
// destroys existing particle system if not NULL
// return new particle system
// does nothing else if filename is NULL
PPARTICLE_SYSTEMS_HEAD
	ParticleSystemsLoadFileAndActivate( PPARTICLE_SYSTEMS_HEAD *particleSystems,
									    char                   *filename,
									    float                  currentTime
                                      );

////////////////////////////////////////////////////////////////////////////////////////////////////

// adds a particle system specified in the
// file, does nothing if filename is NULL
void
	ParticleSystemsAddFileAndActivate( PPARTICLE_SYSTEMS_HEAD *particleSystems,
									   char                   *filename,
								       float                  currentTime
                                     );

////////////////////////////////////////////////////////////////////////////////////////////////////

// adds a particle system to the list
// input is assumed to be normalized between -1 and 1 for x,y,z
// and between 0 and 1 for r,g,b
// clipping is x:[-1,1] y:[-1,1] z:[0,1]
// angles are specified in radians
// speed and force are normalized
//
// if input is not normalized, set first two characters
// of name to "OS" to have variables normalized
// from x:[0,BackBufferViewPortWidth -1]
//      y:[0,BackBufferViewPortHeight-1]
//      z:[-1,1]
//      r:[0,255] g:[0,255] b:[0,255]
// converts angles from degrees to radians
// speed is normalized based on BackBufferViewPortWidth
// force is normalized based on BackBufferViewPortWidth and BackBufferViewPortHeight
void
	ParticleSystemsAddAndActivate
	(
		PPARTICLE_SYSTEMS_HEAD *particleSystems,

		char          *name,													  // EMITTER NAME
		float         currentTime,												  // CURRENT TIME IN SECONDS
		float         emitterLife,												  // HOW LONG WILL THE PARTICLE SYSTEM LAST - IN SECONDS
		// TRANSFORMATION INFO
		float         posX,           float posY,           float posZ,			  // XYZ POSITION OF PARTICLE SYSTEM ORIGIN AND VARIATION
		float         posVarX,        float posVarY,        float posVarZ,
		float         yaw,            float yawVar,								  // YAW AND VARIATION FOR VELOCITY
		float         pitch,          float pitchVar,							  // PITCH AND VARIATION FOR VELOCITY
		float         speed,          float speedVar,							  // VELOCITY MAGNITUDE AND VARIATION
		// PARTICLE
		int           numParticles,												  // TOTAL EMITTED AT ANY TIME
		int           emitsPerFrame,  int   emitVar,							  // EMITS PER FRAME AND VARIATION
		float         life,           float lifeVar,							  // LIFETIME OF PARTICLES AND VARIATION

		float         startColorR,    float startColorG,    float startColorB,    // START COLOR OF PARTICLES AND VARIATION
		float         startColorVarR, float startColorVarG, float startColorVarB,
		float         endColorR,      float endColorG,      float endColorB,      // END COLOR OF PARTICLES AND VARIATION
		float		  endColorVarR,   float endColorVarG,   float endColorVarB,
		// PHYSICS
		float         gForceX,        float gForceY,        float gForceZ,        // GLOBAL GRAVITY, WIND, ETC. AND VARIATION
		float         gForceVarX,     float gForceVarY,     float gForceVarZ,

		unsigned char antiAlias,												  // IF NOT SET TO 0, PARTICLES WILL BE SHADED LINES
																				      // IF SET TO 0, PARTICLES WILL BE COLORED POINTS

		unsigned char physics,													  // IF NOT SET TO 0, ACCELERATION WILL BE INTEGRATED
																				      // INTO PARTICLES
																				      // IF SET TO 0, ONLY VELOCITY WILL BE TAKEN
																			          // INTO ACCOUNT

		unsigned char regeneration												  // IF NOT SET TO 0, DEAD PARTICLES WILL BE
																				      // REGENERATED
																				      // IF SET TO 0, DEAD PARTICLES WILL NOT BE
																				      // REGENERATED
     );

////////////////////////////////////////////////////////////////////////////////////////////////////

// reactivates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are reactivated
void
	ParticleSystemsReActivate( PPARTICLE_SYSTEMS_HEAD *particleSystems,
						       char                   *particleSystemName,
							   float                  currentTime
							 );

////////////////////////////////////////////////////////////////////////////////////////////////////

// updates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are updated
void
	ParticleSystemsUpdate( PPARTICLE_SYSTEMS_HEAD *particleSystems,
						   char                   *particleSystemName,
						   float                  currentTime
						 );

////////////////////////////////////////////////////////////////////////////////////////////////////

// draws the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are drawn
void
	ParticleSystemsDraw( PPARTICLE_SYSTEMS_HEAD *particleSystems,
						 char                   *particleSystemName
					   );

////////////////////////////////////////////////////////////////////////////////////////////////////

// updates and draws the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are updated and drawn
void
	ParticleSystemsUpdateAndDraw( PPARTICLE_SYSTEMS_HEAD *particleSystems,
						          char                   *particleSystemName,
						          float                  currentTime
						        );

////////////////////////////////////////////////////////////////////////////////////////////////////

// terminates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are terminated
void
	ParticleSystemsTerminate( PPARTICLE_SYSTEMS_HEAD *particleSystems,
						      char                   *particleSystemName
							);

#ifdef __cplusplus
	}
#endif