// part_priv.h
//
// particle system from Jeff Lander article
// The Ocean Spray in Your Face July 1998 Game Developer
//
// editor Robert Aldridge

#ifdef __cplusplus
extern "C" {
#endif

// Vectors in homogeneous space...
typedef struct __VECTOR
{
	union
	{
		struct
		{
			f32 x,y,z,w; // currently w always 1 or 0
		};

		f32 vector[4];
	};

}VECTOR,*PVECTOR;

typedef struct __COLOR
{
	union
	{
		struct
		{
			f32 red,green,blue,intensity; // red, green and blue colors ( 0 to 1 f32 ~ 0 to 255 i32 )
										  // currently intensity always 1 or 0
		};

		struct
		{
			f32 r,g,b,i;
		};

		f32 color[4];
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
	f32    life;       // HOW LONG WILL THE PARTICLE LAST AFTER IT IS BORN - IN SECONDS
	COLOR  color;      // CURRENT COLOR OF PARTICLE
	COLOR  prevColor;  // PREVIOUS COLOR OF PARTICLE
	COLOR  deltaColor; // CHANGE OF COLOR OVER TIME

}PARTICLE,*PPARTICLE;

typedef struct __EMITTER // STRUCT FOR PARTICLE SYSTEM
{
	s32       id;							 // EMITTER ID
	s8        name[82];						 // EMITTER NAME
	u32       flags;						 // EMITTER FLAGS
	f32       startTime;					 // PARTICLE SYSTEM MOMENT OF CREATION - IN SECONDS
	f32       prevTime;					     // LAST TIME PARTICLE SYSTEM FUNCTION WAS CALLED
	f32       emitterLife;                   // HOW LONG WILL THE PARTICLE SYSTEM LAST - IN SECONDS
	// TRANSFORMATION INFO
	VECTOR    pos,   posVar;				 // XYZ POSITION OF PARTICLE SYSTEM ORIGIN
	f32       yaw,   yawVar;				 // YAW AND VARIATION FOR VELOCITY
	f32       pitch, pitchVar;				 // PITCH AND VARIATION FOR VELOCITY
	f32       speed, speedVar;				 // VELOCITY MAGNITUDE AND VARIATION
	// PARTICLE
	PPARTICLE particles;					 // PARTICLE POOL - ARRAY OF PARTICLES
	s32       totalParticles;                // NUMBER OF PARTICLES IN POOL
	s32       numParticles;                  // NUMBER OF PARTICLES CURRENTLY ACTIVE
	s32       emitsPerFrame,  emitVar;       // EMITS PER FRAME AND VARIATION
	f32       life,           lifeVar;       // LIFETIME OF PARTICLES AND VARIATION
	COLOR     startColor,     startColorVar; // START COLOR OF PARTICLES AND VARIATION
	COLOR     endColor,       endColorVar;   // END COLOR OF PARTICLES AND VARIATION
	// PHYSICS
	VECTOR    gForce,gForceVar;				 // GLOBAL GRAVITY, WIND, ETC. AND VARIATION

}EMITTER,*PEMITTER;

#ifdef __cplusplus
}
#endif