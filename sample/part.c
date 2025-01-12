// part.c
//
// particle system from Jeff Lander article
// The Ocean Spray in Your Face July 1998 Game Developer
//
// editor Robert Aldridge

#pragma warning ( push, 3 )

#include <ddraw.h>

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stdtypes.h"

#include "part_pub.h"
#include "part_priv.h"

#include "video.h"

// calculates float between -1 and 1
#define RND() ( ( (f32) rand() ) / ( (f32) ( RAND_MAX >> 1 ) ) -1 )

#define ROTATE(PITCH,YAW,DIRECTION)                    \
do{				                                       \
	(DIRECTION).x = (f32) ( -sin(YAW)  * cos(PITCH) ); \
	(DIRECTION).y = (f32) ( sin(PITCH)              ); \
	(DIRECTION).z = (f32) ( cos(PITCH) * cos(YAW)   ); \
	(DIRECTION).w = 0;                                 \
  }while(0)

#define ANTI_ALIAS_BIT    1
#define INFINITE_LIFE_BIT 2
#define PHYSICS_BIT       4
#define REGENERATE_BIT    8

static s32 id;

static __forceinline const u8    __LinearFrameBufferGetBitDepth();

static __forceinline u8 ** const __LinearFrameBufferGetBackBufferArray();

// creates dynamic memory for a particle system structure
// creates dynamic memory for the particles of that system
//
// if emitterLife <= 0 then the lifetime of the particle system is infinite
//
// initializes and returns the dynamically allocated particle system
PEMITTER
CreateParticleSystem
(
	s8        *name,												  // EMITTER NAME
	f32       currentTime,											  // CURRENT TIME IN SECONDS
	f32       emitterLife,											  // HOW LONG WILL THE PARTICLE SYSTEM LAST - IN SECONDS
	// TRANSFORMATION INFO
	f32       posX,           f32 posY,           f32 posZ,			  // XYZ POSITION OF PARTICLE SYSTEM ORIGIN AND VARIATION
	f32       posVarX,        f32 posVarY,        f32 posVarZ,
	f32       yaw,            f32 yawVar,							  // YAW AND VARIATION FOR VELOCITY
	f32       pitch,          f32 pitchVar,							  // PITCH AND VARIATION FOR VELOCITY
	f32       speed,          f32 speedVar,							  // VELOCITY MAGNITUDE AND VARIATION
	// PARTICLE
	s32       numParticles,											  // TOTAL EMITTED AT ANY TIME
	s32       emitsPerFrame,  s32 emitVar,							  // EMITS PER FRAME AND VARIATION
	f32       life,           f32 lifeVar,							  // LIFETIME OF PARTICLES AND VARIATION

	f32       startColorR,    f32 startColorG,    f32 startColorB,    // START COLOR OF PARTICLES AND VARIATION
	f32       startColorVarR, f32 startColorVarG, f32 startColorVarB,
	f32       endColorR,      f32 endColorG,      f32 endColorB,      // END COLOR OF PARTICLES AND VARIATION
	f32		  endColorVarR,   f32 endColorVarG,   f32 endColorVarB,
	// PHYSICS
	f32       gForceX,        f32 gForceY,        f32 gForceZ,        // GLOBAL GRAVITY, WIND, ETC. AND VARIATION
	f32       gForceVarX,     f32 gForceVarY,     f32 gForceVarZ
)
{
	PEMITTER particleSystem = calloc( 1, sizeof(EMITTER) );

	if( particleSystem )
	{
		particleSystem->particles = calloc( 1, sizeof(PARTICLE) * numParticles );

		if( !particleSystem->particles )
		{
			free( particleSystem );
			return 0;
		}

		particleSystem->id = id++;
		strcpy( particleSystem->name, name );

		if( emitterLife <= 0 )
			particleSystem->flags      |= INFINITE_LIFE_BIT;
		else
			particleSystem->emitterLife = emitterLife;

		assert( emitsPerFrame > 0 && life > 0 && numParticles > 0 );

		particleSystem->startTime	    = currentTime;
		particleSystem->prevTime	    = currentTime;
		particleSystem->pos.x		    = posX;
		particleSystem->pos.y		    = posY;
		particleSystem->pos.z		    = posZ;
		particleSystem->pos.w			= 1;
		particleSystem->posVar.x		= posVarX;
		particleSystem->posVar.y		= posVarY;
		particleSystem->posVar.z		= posVarZ;
		particleSystem->posVar.w		= 0;
		particleSystem->yaw		        = yaw;
		particleSystem->yawVar		    = yawVar;
		particleSystem->pitch		    = pitch;
		particleSystem->pitchVar	    = pitchVar;
		particleSystem->speed		    = speed;
		particleSystem->speedVar	    = speedVar;
		particleSystem->totalParticles  = numParticles;
		particleSystem->numParticles    = 0;
		particleSystem->emitsPerFrame   = emitsPerFrame;
		particleSystem->emitVar		    = emitVar;
		particleSystem->life		    = life;
		particleSystem->lifeVar		    = lifeVar;
		particleSystem->startColor.r    = startColorR;
		particleSystem->startColor.g    = startColorG;
		particleSystem->startColor.b    = startColorB;
		particleSystem->startColor.i    = 1;
		particleSystem->startColorVar.r = startColorVarR;
		particleSystem->startColorVar.g = startColorVarG;
		particleSystem->startColorVar.b = startColorVarB;
		particleSystem->startColorVar.i = 0;
		particleSystem->endColor.r	    = endColorR;
		particleSystem->endColor.g	    = endColorG;
		particleSystem->endColor.b	    = endColorB;
		particleSystem->endColor.i	    = 1;
		particleSystem->endColorVar.r   = endColorVarR;
		particleSystem->endColorVar.g   = endColorVarG;
		particleSystem->endColorVar.b   = endColorVarB;
		particleSystem->endColorVar.i   = 0;
		particleSystem->gForce.x	    = gForceX;
		particleSystem->gForce.y	    = gForceY;
		particleSystem->gForce.z	    = gForceZ;
		particleSystem->gForce.w	    = 0;
		particleSystem->gForceVar.x	    = gForceVarX;
		particleSystem->gForceVar.y	    = gForceVarY;
		particleSystem->gForceVar.z	    = gForceVarZ;
		particleSystem->gForceVar.w	    = 0;

		return particleSystem;
	}

	return 0;
}

// initializes the particles of a particle system
//
// if the particles have already been activated, they are reset
//
// if the particle system has died, it will be destroyed and nulled out
void
ActivateParticleSystem(PEMITTER      *_particleSystem, // PREVIOUSLY CREATED PARTICLE SYSTEM

					   f32           currentTime,      // CURRENT TIME IN SECONDS

					   u8            antiAlias,        // IF NOT SET TO 0, PARTICLES WILL BE SHADED LINES
													   // IF SET TO 0, PARTICLES WILL BE COLORED POINTS

					   u8            physics,          // IF NOT SET TO 0, ACCELERATION WILL BE INTEGRATED
													       // INTO PARTICLES
											           // IF SET TO 0, ONLY VELOCITY WILL BE TAKEN
												           // INTO ACCOUNT

					   u8            regeneration      // IF NOT SET TO 0, DEAD PARTICLES WILL BE
													       // REGENERATED
													   // IF SET TO 0, DEAD PARTICLES WILL NOT BE
												           // REGENERATED
                      )
{
	f32       deltaTime;
	f32       pitch,yaw;
	f32       speed,speed_y_factor;
	u32       totalParticles;
	COLOR     start,end;
	PEMITTER  particleSystem;
	PPARTICLE particle;

	if( ! ( _particleSystem && *_particleSystem && (*_particleSystem)->particles ) )
		return;

	particleSystem = *_particleSystem;
	
	deltaTime = currentTime - particleSystem->prevTime;

	particleSystem->prevTime = currentTime;

	if( ! ( particleSystem->flags & INFINITE_LIFE_BIT ) )
	{
		particleSystem->emitterLife -= deltaTime;

		if( particleSystem->emitterLife <= 0 )
		{
			TerminateParticleSystem( _particleSystem );
			return;
		}
	}

	if( antiAlias )
		particleSystem->flags |=  ANTI_ALIAS_BIT;
	else
		particleSystem->flags &= ~ANTI_ALIAS_BIT;

	if( physics )
		particleSystem->flags |=  PHYSICS_BIT;
	else
		particleSystem->flags &= ~PHYSICS_BIT;

	if( regeneration )
		particleSystem->flags |=  REGENERATE_BIT;
	else
		particleSystem->flags &= ~REGENERATE_BIT;

	particle       = particleSystem->particles;
	totalParticles = particleSystem->totalParticles;

	speed_y_factor = ( (f32) __LinearFrameBufferGetHeight() ) / ( (f32) __LinearFrameBufferGetWidth() );

	do
	{
		// SET PARTICLE STARTING POSITION TO ORIGIN OF PARTICLE SYSTEM
		particle->prevPos.x = particle->pos.x = particleSystem->pos.x + ( particleSystem->posVar.x * RND() );
		particle->prevPos.y = particle->pos.y = particleSystem->pos.y + ( particleSystem->posVar.y * RND() );
		particle->prevPos.z = particle->pos.z = particleSystem->pos.z + ( particleSystem->posVar.z * RND() );
		particle->prevPos.w = particle->pos.w = particleSystem->pos.w + ( particleSystem->posVar.w * RND() );

		// SET PARTICLE STARTING VELOCITY VECTOR
		yaw   = particleSystem->yaw   + ( particleSystem->yawVar   * RND() );

		pitch = particleSystem->pitch + ( particleSystem->pitchVar * RND() );

		ROTATE( pitch, yaw, particle->velocity );

		speed = particleSystem->speed + ( particleSystem->speedVar * RND() );

		particle->velocity.x *= speed;
		particle->velocity.y *= speed * speed_y_factor;
		particle->velocity.z *= speed;

		// SET PARTICLE FLAGS
		particle->flags = PARTICLE_UNBORN;

		// CALCULATE LIFETIME OF PARTICLE
		particle->life = particleSystem->life + ( particleSystem->lifeVar * RND() );

		// CALCULATE COLORS
		start.r = particleSystem->startColor.r + ( particleSystem->startColorVar.r * RND() );
		start.g = particleSystem->startColor.g + ( particleSystem->startColorVar.g * RND() );
		start.b = particleSystem->startColor.b + ( particleSystem->startColorVar.b * RND() );
		start.i = particleSystem->startColor.i + ( particleSystem->startColorVar.i * RND() );
		
		end.r   = particleSystem->endColor.r   + ( particleSystem->endColorVar.r   * RND() );
		end.g   = particleSystem->endColor.g   + ( particleSystem->endColorVar.g   * RND() );
		end.b   = particleSystem->endColor.b   + ( particleSystem->endColorVar.b   * RND() );
		end.i   = particleSystem->endColor.i   + ( particleSystem->endColorVar.i   * RND() );

		particle->prevColor.r = particle->color.r = start.r;
		particle->prevColor.g = particle->color.g = start.g;
		particle->prevColor.b = particle->color.b = start.b;
		particle->prevColor.i = particle->color.i = start.i;

		// COLOR CHANGE PER SECOND
		particle->deltaColor.r = ( end.r - start.r ) / particle->life;
		particle->deltaColor.g = ( end.g - start.g ) / particle->life;
		particle->deltaColor.b = ( end.b - start.b ) / particle->life;
		particle->deltaColor.i = ( end.i - start.i ) / particle->life;

		++particle;

	}while( --totalParticles );
}

// updates the particles of a particle system
//
// if the particle system has died, it will be destroyed and nulled out
void
UpdateParticleSystem
(
	PEMITTER *_particleSystem,                          // PREVIOUSLY CREATED PARTICLE SYSTEM
	f32      currentTime,                               // CURRENT TIME IN SECONDS

	u8       gForce,                                    // IF NOT SET TO 0, THE NEW GFORCE VECTOR WILL BE
													        // PERMANENTLY APPLIED TO THE PARTICLE SYSTEM
													        // IF SET TO 0, NEW GFORCE IS IGNORED

	f32      gForceX,    f32 gForceY,    f32 gForceZ,   // GLOBAL GRAVITY, WIND, ETC. AND VARIATION
	f32      gForceVarX, f32 gForceVarY, f32 gForceVarZ
)
{
	f32       deltaTime;
	f32       pitch,yaw;
	f32       speed,speed_y_factor,ax,ay,az,aw,t;
	u32       totalParticles;
	s32       emitsPerFrame;
	COLOR     start,end;
	PEMITTER  particleSystem;
	PPARTICLE particle;

	if( ! ( _particleSystem && *_particleSystem && (*_particleSystem)->particles ) )
		return;

	particleSystem = *_particleSystem;
	
	deltaTime = currentTime - particleSystem->prevTime;

	particleSystem->prevTime = currentTime;

	if( ! ( particleSystem->flags & INFINITE_LIFE_BIT ) )
	{
		particleSystem->emitterLife -= deltaTime;

		if( particleSystem->emitterLife <= 0 )
		{
			TerminateParticleSystem( _particleSystem );
			return;
		}
	}

	if( gForce )
	{
		particleSystem->gForce.x    = gForceX;
		particleSystem->gForce.y    = gForceY;
		particleSystem->gForce.z    = gForceZ;

		particleSystem->gForceVar.x = gForceVarX;
		particleSystem->gForceVar.y = gForceVarY;
		particleSystem->gForceVar.z = gForceVarZ;
	}

	particle       = particleSystem->particles;
	totalParticles = particleSystem->totalParticles;

	emitsPerFrame  = (s32) ( ( (f32) particleSystem->emitsPerFrame ) + ( ( (f32) particleSystem->emitVar ) * RND() ) );

	speed_y_factor = ( (f32) __LinearFrameBufferGetHeight() ) / ( (f32) __LinearFrameBufferGetWidth() );

	ax = particleSystem->gForce.x + ( particleSystem->gForceVar.x * RND() );
	ay = particleSystem->gForce.y + ( particleSystem->gForceVar.y * RND() );
	az = particleSystem->gForce.z + ( particleSystem->gForceVar.z * RND() );
	aw = particleSystem->gForce.w + ( particleSystem->gForceVar.w * RND() );

	particleSystem->numParticles = 0;

	do
	{
		if( particle->flags == PARTICLE_ACTIVE )
		{
			// SAVE OLD POSITION FOR ANTI_ALIASING
			particle->prevPos.x = particle->pos.x;
			particle->prevPos.y = particle->pos.y;
			particle->prevPos.z = particle->pos.z;
			particle->prevPos.w = particle->pos.w;

			// CALCULATE NEW POSITION
			if( particleSystem->flags & PHYSICS_BIT )
			{
				// INTEGRATE ACCELERATION AND VELOCITY TO FIND NEW POSITION
				// r(t) = a * t^2 / 2 + v0 * t + r0
				t  = (f32) ( ( deltaTime * deltaTime ) * 0.5 );

				particle->pos.x += particle->velocity.x * deltaTime + ax * t;
				particle->pos.y += particle->velocity.y * deltaTime + ay * t;
				particle->pos.z += particle->velocity.z * deltaTime + az * t;
				particle->pos.w += particle->velocity.w * deltaTime + aw * t;

				// INTEGRATE ACCELERATION TO FIND NEW VELOCITY
				// v(t) = a * t + v0
				particle->velocity.x += ax * deltaTime;
				particle->velocity.y += ay * deltaTime;
				particle->velocity.z += az * deltaTime;
				particle->velocity.w += aw * deltaTime;
			}
			else
			{
				// JUST MOVE USING CURRENT VELOCITY
				particle->pos.x += particle->velocity.x * deltaTime;
				particle->pos.y += particle->velocity.y * deltaTime;
				particle->pos.z += particle->velocity.z * deltaTime;
				particle->pos.w += particle->velocity.w * deltaTime;
			}

			particle->life -= deltaTime;

			if( particle->life <= 0 )
				particle->flags = PARTICLE_DEAD;
			else
				++particleSystem->numParticles;

			// SAVE THE OLD COLOR
			particle->prevColor.r = particle->color.r;
			particle->prevColor.g = particle->color.g;
			particle->prevColor.b = particle->color.b;
			particle->prevColor.i = particle->color.i;

			// GET NEW COLOR
			particle->color.r += particle->deltaColor.r * deltaTime;
			particle->color.g += particle->deltaColor.g * deltaTime;
			particle->color.b += particle->deltaColor.b * deltaTime;
			particle->color.i += particle->deltaColor.i * deltaTime;
		}

		if( ( particleSystem->flags & REGENERATE_BIT ) && particle->flags == PARTICLE_DEAD )
		{
			// SET PARTICLE STARTING POSITION TO ORIGIN OF PARTICLE SYSTEM
			particle->prevPos.x = particle->pos.x = particleSystem->pos.x + ( particleSystem->posVar.x * RND() );
			particle->prevPos.y = particle->pos.y = particleSystem->pos.y + ( particleSystem->posVar.y * RND() );
			particle->prevPos.z = particle->pos.z = particleSystem->pos.z + ( particleSystem->posVar.z * RND() );
			particle->prevPos.w = particle->pos.w = particleSystem->pos.w + ( particleSystem->posVar.w * RND() );

			// SET PARTICLE STARTING VELOCITY VECTOR
			yaw   = particleSystem->yaw   + ( particleSystem->yawVar   * RND() );

			pitch = particleSystem->pitch + ( particleSystem->pitchVar * RND() );

			ROTATE( pitch, yaw, particle->velocity );

			speed = particleSystem->speed + ( particleSystem->speedVar * RND() );

			particle->velocity.x *= speed;
			particle->velocity.y *= speed * speed_y_factor;
			particle->velocity.z *= speed;

			// SET PARTICLE FLAGS
			particle->flags = PARTICLE_UNBORN;

			// CALCULATE LIFETIME OF PARTICLE
			particle->life = particleSystem->life + ( particleSystem->lifeVar * RND() );

			// CALCULATE COLORS
			start.r = particleSystem->startColor.r + ( particleSystem->startColorVar.r * RND() );
			start.g = particleSystem->startColor.g + ( particleSystem->startColorVar.g * RND() );
			start.b = particleSystem->startColor.b + ( particleSystem->startColorVar.b * RND() );
			start.i = particleSystem->startColor.i + ( particleSystem->startColorVar.i * RND() );
			
			end.r   = particleSystem->endColor.r   + ( particleSystem->endColorVar.r   * RND() );
			end.g   = particleSystem->endColor.g   + ( particleSystem->endColorVar.g   * RND() );
			end.b   = particleSystem->endColor.b   + ( particleSystem->endColorVar.b   * RND() );
			end.i   = particleSystem->endColor.i   + ( particleSystem->endColorVar.i   * RND() );

			particle->prevColor.r = particle->color.r = start.r;
			particle->prevColor.g = particle->color.g = start.g;
			particle->prevColor.b = particle->color.b = start.b;
			particle->prevColor.i = particle->color.i = start.i;

			// COLOR CHANGE PER SECOND
			particle->deltaColor.r = ( end.r - start.r ) / particle->life;
			particle->deltaColor.g = ( end.g - start.g ) / particle->life;
			particle->deltaColor.b = ( end.b - start.b ) / particle->life;
			particle->deltaColor.i = ( end.i - start.i ) / particle->life;
		}

		++particle;

	}while( --totalParticles );

	particle       = particleSystem->particles;
	totalParticles = particleSystem->totalParticles;

	if( emitsPerFrame > 0 )
		do
		{
			if( particle->flags == PARTICLE_UNBORN )
			{
				--emitsPerFrame;

				++particleSystem->numParticles;

				particle->flags = PARTICLE_ACTIVE;
			}

			++particle;

		}while( emitsPerFrame > 0 && --totalParticles );
}

static u8  LFbitDepth = 32, **LFbackBufferArray;
static u16 LFwidth,LFheight;

static u8** ( *_backBufferFunction ) ( );

extern void __LinearFrameBufferOSSetBackBuffer(s8** ( *__backBufferFunction ) ( ),
											   u16     BackBufferViewPortWidth,
											   u16     BackBufferViewPortHeight
											  )
{
	_backBufferFunction = ( u8** (*) ( ) ) __backBufferFunction;

	LFbackBufferArray = _backBufferFunction();

	LFwidth        = BackBufferViewPortWidth;
	LFheight       = BackBufferViewPortHeight;
}

static __forceinline const u8    __LinearFrameBufferGetBitDepth()        { return LFbitDepth;        }
extern __forceinline const u16   __LinearFrameBufferGetWidth()           { return LFwidth;           }
extern __forceinline const u16   __LinearFrameBufferGetHeight()          { return LFheight;          }

static __forceinline u8 ** const __LinearFrameBufferGetBackBufferArray() { return LFbackBufferArray; }

// draws the particles of a particle system, does not update them
//
// does not check if the particle system has died
void
DrawParticleSystem(PEMITTER *_particleSystem, // PREVIOUSLY CREATED PARTICLE SYSTEM
                   f32      *m                // 4x4 world to camera transformation matrix
                  )
{
	u32       totalParticles;
	PEMITTER  particleSystem;
	PPARTICLE particle;

	// FOR BACKBUFFER INFO
	u8        antiAlias;
	u8        bitDepth;
	u8        **bb;
	u16       width,height;
	//

	// FOR PIXEL DRAWING
	f32       z;

	u16       x,y;

	u32       red,green,blue;
	//

	// FOR ANIT_ALIAS
	f32       dx,dxstep,dxabs,
		      dy,dystep,dyabs,
		      xi,yi,
		      ri,gi,bi;

	f32       x0,y0,z0,x1,y1,z1;
	f32       r0,g0,b0,r1,g1,b1;

	f32       t;

	u32       count;
	//

	LFbackBufferArray = _backBufferFunction();

	if( ! (   _particleSystem               &&
             *_particleSystem               && 
            (*_particleSystem)->particles ) &&
		     LFbackBufferArray              && 
            *LFbackBufferArray
          )
        return;

	particleSystem = *_particleSystem;

	particle       = particleSystem->particles;
	totalParticles = particleSystem->totalParticles;

	antiAlias      = (u8) ( ( particleSystem->flags & ANTI_ALIAS_BIT ) == ANTI_ALIAS_BIT );

	width          = __LinearFrameBufferGetWidth();
	height         = __LinearFrameBufferGetHeight();


	bitDepth = __LinearFrameBufferGetBitDepth();

	bb       = __LinearFrameBufferGetBackBufferArray();

	do
	{
		if( particle->flags == PARTICLE_ACTIVE )
		{
			if( antiAlias )
			{
				x0 = particle->prevPos.x;   y0 = particle->prevPos.y;   z0 = particle->prevPos.z;
				r0 = particle->prevColor.r; g0 = particle->prevColor.g; b0 = particle->prevColor.b;

				x1 = particle->pos.x;       y1 = particle->pos.y;       z1 = particle->pos.z;
				r1 = particle->color.r;     g1 = particle->color.g;     b1 = particle->color.b;

				if( m )
				{
					f32 tx, ty;

					tx = (f32) ( m[0] * x0 + m[1] * y0 + m[2]  * z0 + m[3]  );
					ty = (f32) ( m[4] * x0 + m[5] * y0 + m[6]  * z0 + m[7]  );
					z0 = (f32) ( m[8] * x0 + m[9] * y0 + m[10] * z0 + m[11] );

					x0 = tx; y0 = ty;

					tx = (f32) ( m[0] * x1 + m[1] * y1 + m[2]  * z1 + m[3]  );
					ty = (f32) ( m[4] * x1 + m[5] * y1 + m[6]  * z1 + m[7]  );
					z1 = (f32) ( m[8] * x1 + m[9] * y1 + m[10] * z1 + m[11] );

					x1 = tx; y1 = ty;
				}

				#define xmin -1
				#define xmax  1
				#define ymin -1
				#define ymax  1
				#define zmin  0
				#define zmax  1

				if( ! ( ( x0 < xmin && x1 < xmin ) ||
						( y0 < ymin && y1 < ymin ) ||
						( z0 < zmin && z1 < zmin ) ||
						( x0 > xmax && x1 > xmax ) ||
						( y0 > ymax && y1 > ymax ) ||
						( z0 > zmax && z1 > zmax ) )
                  )
				{
					if( x0 >= xmin && x0 <= xmax &&
                        x1 >= xmin && x1 <= xmax &&
						y0 >= ymin && y0 <= ymax &&
                        y1 >= ymin && y1 <= ymax &&
						z0 >= zmin && z0 <= zmax &&
                        z1 >= zmin && z1 <= zmax
					  )
					{
						if( z0 == 0 )
							z = .000001f;
						else
							z = z0;

						// COORDINATES go from [ -1, 1 ] to [ 0, width-1 ]
						x0 = (f32) ( (    ( x0 / z )   + 1.0 ) * ( ( ( (f32) width  ) - 1.0 ) / 2.0 ) );

						// COORDINATES go from [ -1, 1 ] to [ 0, height-1 ]
						y0 = (f32) ( ( ( -( y0 / z ) ) + 1.0 ) * ( ( ( (f32) height ) - 1.0 ) / 2.0 ) );

						if( z1 == 0 )
							z = .000001f;
						else
							z = z1;

						// COORDINATES go from [ -1, 1 ] to [ 0, width-1 ]
						x1 = (f32) ( (    ( x1 / z )   + 1.0 ) * ( ( ( (f32) width  ) - 1.0 ) / 2.0 ) );

						// COORDINATES go from [ -1, 1 ] to [ 0, height-1 ]
						y1 = (f32) ( ( ( -( y1 / z ) ) + 1.0 ) * ( ( ( (f32) height ) - 1.0 ) / 2.0 ) );

						if( r0 <= 0 )
							r0 = 0;
						else if( r0 >= 1 )
							r0 = 255;
						else
							r0 = (u8) ( r0 * 255.0 );

						if( g0 <= 0 )
							g0 = 0;
						else if( g0 >= 1 )
							g0 = 255;
						else
							g0 = (u8) ( g0 * 255.0 );

						if( b0 <= 0 )
							b0 = 0;
						else if( b0 >= 1 )
							b0 = 255;
						else
							b0 = (u8) ( b0 * 255.0 );

						if( r1 <= 0 )
							r1 = 0;
						else if( r1 >= 1 )
							r1 = 255;
						else
							r1 = (u8) ( r1 * 255.0 );

						if( g1 <= 0 )
							g1 = 0;
						else if( g1 >= 1 )
							g1 = 255;
						else
							g1 = (u8) ( g1 * 255.0 );

						if( b1 <= 0 )
							b1 = 0;
						else if( b1 >= 1 )
							b1 = 255;
						else
							b1 = (u8) ( b1 * 255.0 );

						if( x0 >= 0 && x0 <= ( width - 1 ) && y0 >= 0 && y0 <= ( height - 1 ) && z0 >= .000001f && z0 <= 1 &&
							x1 >= 0 && x1 <= ( width - 1 ) && y1 >= 0 && y1 <= ( height - 1 ) && z1 >= .000001f && z1 <= 1
                          )
							goto drawline;
						else
						{
							++particle;

							continue;
						}	
					}

					// FRONT - IN TO OUT
					if( z0 >= zmin && z1 < zmin )
					{
						t = z0 - z1;

						if( t == 0 )
							t = ( zmin - z1 ) / .000001f;
						else
							t = ( zmin - z1 ) / t;

						x1 += ( x0 - x1 ) * t;
						y1 += ( y0 - y1 ) * t;
						z1  = zmin;

						r1 += ( r0 - r1 ) * t;
						g1 += ( g0 - g1 ) * t;
						b1 += ( b0 - b1 ) * t;
					}
					// FRONT - OUT TO IN
					else if( z0 < zmin && z1 >= zmin )
					{
						t = z1 - z0;

						if( t == 0 )
							t = ( zmin - z0 ) / .000001f;
						else
							t = ( zmin - z0 ) / t;

						x0 += ( x1 - x0 ) * t;
						y0 += ( y1 - y0 ) * t;
						z0  = zmin;

						r0 += ( r1 - r0 ) * t;
						g0 += ( g1 - g0 ) * t;
						b0 += ( b1 - b0 ) * t;
					}

					// BACK - IN TO OUT
					if( z0 <= zmax && z1 > zmax )
					{
						t = z1 - z0;

						if( t == 0 )
							t = ( z1 - zmax ) / .000001f;
						else
							t = ( z1 - zmax ) / t;

						x1 += ( x1 - x0 ) * t;
						y1 += ( y1 - y0 ) * t;
						z1  = zmax;

						r1 += ( r1 - r0 ) * t;
						g1 += ( g1 - g0 ) * t;
						b1 += ( b1 - b0 ) * t;
					}
					// BACK - OUT TO IN
					else if( z0 > zmax && z1 <= zmax )
					{
						t = z0 - z1;

						if( t == 0 )
							t = ( z0 - zmax ) / .000001f;
						else
							t = ( z0 - zmax ) / t;

						x0 += ( x0 - x1 ) * t;
						y0 += ( y0 - y1 ) * t;
						z0  = zmax;

						r0 += ( r0 - r1 ) * t;
						g0 += ( g0 - g1 ) * t;
						b0 += ( b0 - b1 ) * t;
					}

					if( z0 == 0 )
						z = .000001f;
					else
						z = z0;

					// COORDINATES go from [ -1, 1 ] to [ 0, width-1 ]
					x0 = (f32) ( (    ( x0 / z )   + 1.0 ) * ( ( ( (f32) width  ) - 1.0 ) / 2.0 ) );

					// COORDINATES go from [ -1, 1 ] to [ 0, height-1 ]
					y0 = (f32) ( ( ( -( y0 / z ) ) + 1.0 ) * ( ( ( (f32) height ) - 1.0 ) / 2.0 ) );

					if( z1 == 0 )
						z = .000001f;
					else
						z = z1;

					// COORDINATES go from [ -1, 1 ] to [ 0, width-1 ]
					x1 = (f32) ( (    ( x1 / z )   + 1.0 ) * ( ( ( (f32) width  ) - 1.0 ) / 2.0 ) );

					// COORDINATES go from [ -1, 1 ] to [ 0, height-1 ]
					y1 = (f32) ( ( ( -( y1 / z ) ) + 1.0 ) * ( ( ( (f32) height ) - 1.0 ) / 2.0 ) );

					#undef xmin
					#undef xmax
					#undef ymin
					#undef ymax

					#define xmin 0
					#define xmax ( (f32) ( width  - 1 ) )
					#define ymin 0
					#define ymax ( (f32) ( height - 1 ) )

					// LEFT - IN TO OUT
					if( x0 >= xmin && x1 < xmin )
					{
						t = x0 - x1;

						if( t == 0 )
							t = ( xmin - x1 ) / .000001f;
						else
							t = ( xmin - x1 ) / t;

						x1  = xmin;
						y1 += ( y0 - y1 ) * t;
						z1 += ( z0 - z1 ) * t;

						r1 += ( r0 - r1 ) * t;
						g1 += ( g0 - g1 ) * t;
						b1 += ( b0 - b1 ) * t;
					}
					// LEFT - OUT TO IN
					else if( x0 < xmin && x1 >= xmin )
					{
						t = x1 - x0;

						if( t == 0 )
							t = ( xmin - x0 ) / .000001f;
						else
							t = ( xmin - x0 ) / t;

						x0  = xmin;
						y0 += ( y1 - y0 ) * t;
						z0 += ( z1 - z0 ) * t;

						r0 += ( r1 - r0 ) * t;
						g0 += ( g1 - g0 ) * t;
						b0 += ( b1 - b0 ) * t;
					}

					// RIGHT - IN TO OUT
					if( x0 <= xmax && x1 > xmax )
					{
						t = x1 - x0;

						if( t == 0 )
							t = ( x1 - xmax ) / .000001f;
						else
							t = ( x1 - xmax ) / t;

						x1  = xmax;
						y1 += ( y1 - y0 ) * t;
						z1 += ( z1 - z0 ) * t;

						r1 += ( r1 - r0 ) * t;
						g1 += ( g1 - g0 ) * t;
						b1 += ( b1 - b0 ) * t;
					}
					// RIGHT - OUT TO IN
					else if( x0 > xmax && x1 <= xmax )
					{
						t = x0 - x1;

						if( t == 0 )
							t = ( x0 - xmax ) / .000001f;
						else
							t = ( x0 - xmax ) / t;

						x0  = xmax;
						y0 += ( y0 - y1 ) * t;
						z0 += ( z0 - z1 ) * t;

						r0 += ( r0 - r1 ) * t;
						g0 += ( g0 - g1 ) * t;
						b0 += ( b0 - b1 ) * t;
					}

					// TOP - IN TO OUT
					if( y0 >= ymin && y1 < ymin )
					{
						t = y0 - y1;

						if( t == 0 )
							t = ( ymin - y1 ) / .000001f;
						else
							t = ( ymin - y1 ) / t;

						x1 += ( x0 - x1 ) * t;
						y1  = ymin;
						z1 += ( z0 - z1 ) * t;

						r1 += ( r0 - r1 ) * t;
						g1 += ( g0 - g1 ) * t;
						b1 += ( b0 - b1 ) * t;
					}
					// TOP - OUT TO IN
					else if( y0 < ymin && y1 >= ymin )
					{
						t = y1 - y0;

						if( t == 0 )
							t = ( ymin - y0 ) / .000001f;
						else
							t = ( ymin - y0 ) / t;

						x0 += ( x1 - x0 ) * t;
						y0  = ymin;
						z0 += ( z1 - z0 ) * t;

						r0 += ( r1 - r0 ) * t;
						g0 += ( g1 - g0 ) * t;
						b0 += ( b1 - b0 ) * t;
					}

					// BOTTOM - IN TO OUT
					if( y0 <= ymax && y1 > ymax )
					{
						t = y1 - y0;

						if( t == 0 )
							t = ( y1 - ymax ) / .000001f;
						else
							t = ( y1 - ymax ) / t;

						x1 += ( x1 - x0 ) * t;
						y1  = ymax;
						z1 += ( z1 - z0 ) * t;

						r1 += ( r1 - r0 ) * t;
						g1 += ( g1 - g0 ) * t;
						b1 += ( b1 - b0 ) * t;
					}
					// BOTTOM - OUT TO IN
					else if( y0 > ymax && y1 <= ymax )
					{
						t = y0 - y1;

						if( t == 0 )
							t = ( y0 - ymax ) / .000001f;
						else
							t = ( y0 - ymax ) / t;

						x0 += ( x0 - x1 ) * t;
						y0  = ymax;
						z0 += ( z0 - z1 ) * t;

						r0 += ( r0 - r1 ) * t;
						g0 += ( g0 - g1 ) * t;
						b0 += ( b0 - b1 ) * t;
					}

					if( ! ( x0 >= 0 && x0 <= ( width - 1 ) && y0 >= 0 && y0 <= ( height - 1 ) && z0 >= .000001f && z0 <= 1 &&
							x1 >= 0 && x1 <= ( width - 1 ) && y1 >= 0 && y1 <= ( height - 1 ) && z1 >= .000001f && z1 <= 1 )
                      )
					{
						++particle;

						continue;
					}	

					drawline:

					#define i(x) ( (u32) x )

					#define copy_x_8()  *(bb[i(y0)]+i(x0))=(u8)((i(r0)+i(g0)+i(b0))/3),r0+=ri,g0+=gi,b0+=bi
					#define copy_y_8()  *(bb[i(y0)]+i(x0))=(u8)((i(r0)+i(g0)+i(b0))/3),r0+=ri,g0+=gi,b0+=bi

					#define copy_x_15() *(((u16*)bb[i(y0)])+i(x0))=(u16)(((i(r0)>>3)<<10)|((i(g0)>>3)<<5)|i(b0)),r0+=ri,g0+=gi,b0+=bi
					#define copy_y_15() *(((u16*)bb[i(y0)])+i(x0))=(u16)(((i(r0)>>3)<<10)|((i(g0)>>3)<<5)|i(b0)),r0+=ri,g0+=gi,b0+=bi

					#define copy_x_16() *(((u16*)bb[i(y0)])+i(x0))=(u16)(((i(r0)>>3)<<11)|((i(g0)>>2)<<5)|i(b0)),r0+=ri,g0+=gi,b0+=bi
					#define copy_y_16() *(((u16*)bb[i(y0)])+i(x0))=(u16)(((i(r0)>>3)<<11)|((i(g0)>>2)<<5)|i(b0)),r0+=ri,g0+=gi,b0+=bi

					// 24 bit macro is very unoptimized, I suggest not using line drawing in 24 bit mode
					#define copy_x_24() *(bb[i(y0)]+i(x0)*3  )=(u8)i(b0),\
										*(bb[i(y0)]+i(x0)*3+1)=(u8)i(g0),\
										*(bb[i(y0)]+i(x0)*3+2)=(u8)i(r0),\
										r0+=ri,g0+=gi,b0+=bi

					// 24 bit macro is very unoptimized, I suggest not using line drawing in 24 bit mode
					#define copy_y_24() *(bb[i(y0)]+i(x0)*3  )=(u8)i(b0),\
										*(bb[i(y0)]+i(x0)*3+1)=(u8)i(g0),\
										*(bb[i(y0)]+i(x0)*3+2)=(u8)i(r0),\
										r0+=ri,g0+=gi,b0+=bi

					#define copy_x_32() *(((u32*)bb[i(y0)])+i(x0))=((i(r0)<<16)|(i(g0)<<8)|i(b0)),r0+=ri,g0+=gi,b0+=bi
					#define copy_y_32() *(((u32*)bb[i(y0)])+i(x0))=((i(r0)<<16)|(i(g0)<<8)|i(b0)),r0+=ri,g0+=gi,b0+=bi

					dx = x1 - x0;
					( dx >= 0 )?
						( dxstep =  1, dxabs =  dx ):
						( dxstep = -1, dxabs = -dx );

					dy = y1 - y0;
					( dy >=0 )?
						( dystep =  1, dyabs =  dy ):
						( dystep = -1, dyabs = -dy );

					if( dxabs >= dyabs )
					{
						count = i( dxabs );

						( count == 0 )?
							( yi = 0, ri = 0, gi = 0, bi = 0 ):
							( yi = ( y1 - y0 ) / dxabs,
							  ri = ( r1 - r0 ) / dxabs,
							  gi = ( g1 - g0 ) / dxabs,
							  bi = ( b1 - b0 ) / dxabs
							);

						x0    = (f32) floor( x0 );
						x1    = (f32) floor( x1 );
						dxabs = x1 - x0;

						if( dxabs < 0 )
							dxabs =- dxabs;

						++count; // comment to use top-left fill rule

						do
						{
							switch( bitDepth )
							{
								case 8:  copy_x_8();  break;
								case 15: copy_x_15(); break;
								case 16: copy_x_16(); break;
								case 24: copy_x_24(); break;
								case 32: copy_x_32(); break;
								default:
									assert( "DrawParticleSystem - unsupported bit depth" && 0 );
									break;
							}

							x0 += dxstep;
							y0 += yi;
						
						}while( --count != 0 );
					}
					else
					{
						count = i( dyabs );

						( count == 0 )?
							( xi = 0, ri = 0, gi = 0, bi = 0 ):
							( xi = ( x1 - x0 ) / dyabs,
                              ri = ( r1 - r0 ) / dyabs,
                              gi = ( g1 - g0 ) / dyabs,
                              bi = ( b1 - b0 ) / dyabs
                            );

						y0    = (f32) floor( y0 );
						y1    = (f32) floor( y1 );
						dyabs = y1 - y0;

						if( dyabs < 0 )
							dyabs =- dyabs;

						++count; // comment to use top-left fill rule

						do
						{
							switch( bitDepth )
							{
								case 8:  copy_y_8();  break;
								case 15: copy_y_15(); break;
								case 16: copy_y_16(); break;
								case 24: copy_y_24(); break;
								case 32: copy_y_32(); break;
								default:
									assert( "DrawParticleSystem - unsupported bit depth" && 0 );
									break;
							}

							y0 += dystep;
							x0 += xi;

						}while( --count != 0 );
					}
				}
			}
			else
			{
				z = particle->pos.z;

				if( m )
				{
					f32 tx = particle->pos.x, ty = particle->pos.y;

					particle->pos.x = (f32) ( m[0] * tx + m[1] * ty + m[2]  * z + m[3]  );
					particle->pos.y = (f32) ( m[4] * tx + m[5] * ty + m[6]  * z + m[7]  );
					z               = (f32) ( m[8] * tx + m[9] * ty + m[10] * z + m[11] );
				}

				if( z == 0 )
					z = .000001f;

				// COORDINATES go from [ -1, 1 ] to [ 0, width-1 ]
				x = (u16) ( (    ( particle->pos.x / z )   + 1.0 ) * ( ( ( (f32) width  ) - 1.0 ) / 2.0 ) );

				// COORDINATES go from [ -1, 1 ] to [ 0, height-1 ]
				y = (u16) ( ( ( -( particle->pos.y / z ) ) + 1.0 ) * ( ( ( (f32) height ) - 1.0 ) / 2.0 ) );

				if( x >= 0 && x < width && y >= 0 && y < height && z >= .000001f && z <= 1 )
				{
					if( particle->color.r <= 0 )
						red = 0;
					else if( particle->color.r >= 1 )
						red = 255;
					else
						red = (u8) ( particle->color.r * 255.0 );

					if( particle->color.g <= 0 )
						green = 0;
					else if( particle->color.g >= 1 )
						green = 255;
					else
						green = (u8) ( particle->color.g * 255.0 );

					if( particle->color.b <= 0 )
						blue = 0;
					else if( particle->color.b >= 1 )
						blue = 255;
					else
						blue = (u8) ( particle->color.b * 255.0 );

					switch( __LinearFrameBufferGetBitDepth() )
					{
						case 8:
							*( bb[ y ] + x ) =
								(u8) ( ( ( (u16) red ) + ( (u16) green ) + ( (u16) blue ) ) / 3 );
							break;
						case 15:
							*( ( (u16*) bb[ y ] ) + x ) =
								(u16) ( ( ( ( (u16) red ) >> 3 )  << 10 ) | ( ( ( (u16) green ) >> 3 ) << 5 ) | ( ( (u16) blue ) >> 3 ) );
							break;
						case 16:
							*( ( (u16*) bb[ y ] ) + x ) =
								(u16) ( ( ( ( (u16) red ) >> 3 )  << 11 ) | ( ( ( (u16) green ) >> 2 ) << 5 ) | ( ( (u16) blue ) >> 3 ) );
							break;
						case 24:
							*( bb[ y ] + x * 3     ) = (u8) blue;
							*( bb[ y ] + x * 3 + 1 ) = (u8) green;
							*( bb[ y ] + x * 3 + 2 ) = (u8) red;
							break;
						case 32:
							*( ( (u32*) bb[ y ] ) + x ) =
								( ( ( (u32) red ) << 16 ) | ( ( (u32) green ) << 8 ) | ( (u32) blue ) );
							break;
						default:
							assert( "DrawParticleSystem - unsupported bit depth" && 0 );
							break;
					}
				}
			}
		}

		++particle;

	}while( --totalParticles );

}

// destroys the particle system and nulls it out
void
TerminateParticleSystem(PEMITTER *_particleSystem // PREVIOUSLY CREATED PARTICLE SYSTEM
                       )
{
	if( ! ( _particleSystem && *_particleSystem && (*_particleSystem)->particles ) )
		return;

	memset( (*_particleSystem)->particles, 0, sizeof(PARTICLE) * (*_particleSystem)->totalParticles );

	free( (*_particleSystem)->particles );

	memset( (*_particleSystem), 0, sizeof(EMITTER) );

	free( (*_particleSystem) );

	*_particleSystem=0;
}