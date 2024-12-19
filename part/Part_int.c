// part_int.c
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

#pragma warning ( push, 3 )

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stdtypes.h"

#include "part_pub.h"

#include "client.h"

#include "listpub.h"

#include "partpub.h"

#include "video.h"


static f32 currentTime;
static f32 *matrix;

static s32 Dead(CLIENT_POTYPE Obj1,
                CLIENT_POTYPE Obj2
               )
{
	if( !Obj2.particleSystem )
		return 1;

	return 0;
}

static s32 Equal(CLIENT_POTYPE Obj1,
                 CLIENT_POTYPE Obj2
                )
{
	return( strcmp( Obj1.name, Obj2.name ) == 0 );
}

static s32 Activate(CLIENT_PPOTYPE Obj
                   )
{
	if( Obj->particleSystem )
		ActivateParticleSystem( (PEMITTER*) (&Obj->particleSystem), currentTime, Obj->arg1, Obj->arg2, Obj->arg3 );

	return 0;
}

static s32 Update(CLIENT_PPOTYPE Obj
                 )
{
	if( Obj->particleSystem )
		UPDATE_PARTICLE_SYSTEM( (PEMITTER*) (&Obj->particleSystem), currentTime );

	return 0;
}

static s32 Draw(CLIENT_PPOTYPE Obj
               )
{
	if( Obj->particleSystem )
		DrawParticleSystem( (PEMITTER*) (&Obj->particleSystem), matrix );

	return 0;
}

static s32 Terminate(CLIENT_PPOTYPE Obj
                    )
{
	if( Obj->particleSystem )
		TerminateParticleSystem( (PEMITTER*) (&Obj->particleSystem) );

	return 0;
}

static void ParticleSystemsInternalLoad(PLIST_HEAD particleSystems,
										FILE       *file
									   )
{
	f32           fbuffer[64] = {0};
	s32           ibuffer[16] = {0};
	CLIENT_POTYPE Obj         = {0};

	fscanf( file, "%s\n", Obj.name );    // name

	fscanf( file, "%f\n", &fbuffer[0] ); // emitterLife

	fscanf( file, "%f %f %f\n", &fbuffer[1],  &fbuffer[2], &fbuffer[3] ); // posX posY posZ

	fscanf( file, "%f %f %f\n", &fbuffer[4],  &fbuffer[5], &fbuffer[6] ); // posVarX posVarY posVarZ

	fscanf( file, "%f %f\n", &fbuffer[7],  &fbuffer[8]  );  // yaw yawVar
	fscanf( file, "%f %f\n", &fbuffer[9],  &fbuffer[10] );  // pitch pitchVar
	fscanf( file, "%f %f\n", &fbuffer[11], &fbuffer[12] );  // speed speedVar

	fscanf( file, "%i\n", &ibuffer[0] );                   // numParticles

	fscanf( file, "%i %i\n", &ibuffer[1], &ibuffer[2] );   // emitsPerFrame emitVar

	fscanf( file, "%f %f\n", &fbuffer[13], &fbuffer[14] ); // life lifeVar

	fscanf( file, "%f %f %f\n", &fbuffer[15], &fbuffer[16], &fbuffer[17] ); // startColorR startColorG startColorB
	fscanf( file, "%f %f %f\n", &fbuffer[18], &fbuffer[19], &fbuffer[20] ); // startColorVarR startColorVarG startColorVarB
	fscanf( file, "%f %f %f\n", &fbuffer[21], &fbuffer[22], &fbuffer[23] ); // endColorR endColorG endColorB
	fscanf( file, "%f %f %f\n", &fbuffer[24], &fbuffer[25], &fbuffer[26] ); // endColorVarR endColorVarG endColorVarB

	fscanf( file, "%f %f %f\n", &fbuffer[27], &fbuffer[28], &fbuffer[29] ); // gForceX gForceY gForceZ
	fscanf( file, "%f %f %f\n", &fbuffer[30], &fbuffer[31], &fbuffer[32] ); // gForceVarX gForceVarY gForceVarZ

	fscanf( file, "%i %i %i", &ibuffer[3],  &ibuffer[4],  &ibuffer[5] );  // antiAlias physics regeneration

	// IF FIRST TWO CHARACTERS ARE "OS", THEN NORMALIZE THE INPUT
	if( Obj.name && Obj.name[0] && Obj.name[1] && Obj.name[0]=='O' && Obj.name[1]=='S' )
	{
		f32 halfWidth     = ( (f32) __LinearFrameBufferGetWidth()  ) * 0.5f;
		f32 halfHeight    = ( (f32) __LinearFrameBufferGetHeight() ) * 0.5f;

		f32 invHalfWidth  = 1.0f / halfWidth;
		f32 invHalfHeight = 1.0f / halfHeight;

		f32 pi2rad     = 0.01745329f; // pi / 180

		f32 colorConv  = 0.00392156f; // 1 / 255

		fbuffer[1]   =   ( fbuffer[1] - halfWidth  ) * invHalfWidth;
		fbuffer[2]   = - ( fbuffer[2] - halfHeight ) * invHalfHeight;

		fbuffer[4]  *= invHalfWidth;
		fbuffer[5]  *= invHalfHeight;

		fbuffer[7]  *= pi2rad;
		fbuffer[8]  *= pi2rad;

		fbuffer[9]  *= pi2rad;
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

	Obj.particleSystem = (void*)
		CreateParticleSystem
		(
			Obj.name,
			currentTime,
			fbuffer[0],
			fbuffer[1],  fbuffer[2], fbuffer[3],
			fbuffer[4],  fbuffer[5], fbuffer[6],
			fbuffer[7],  fbuffer[8],
			fbuffer[9],  fbuffer[10],
			fbuffer[11], fbuffer[12],
			ibuffer[0],
			ibuffer[1],  ibuffer[2],
			fbuffer[13], fbuffer[14],
			fbuffer[15], fbuffer[16], fbuffer[17],
			fbuffer[18], fbuffer[19], fbuffer[20],
			fbuffer[21], fbuffer[22], fbuffer[23],
			fbuffer[24], fbuffer[25], fbuffer[26],
			fbuffer[27], fbuffer[28], fbuffer[29],
			fbuffer[30], fbuffer[31], fbuffer[32]
		);

	ActivateParticleSystem( (PEMITTER*) (&Obj.particleSystem), currentTime, (u8) ibuffer[3], (u8) ibuffer[4], (u8) ibuffer[5] );

	Obj.arg1 = (u8) ibuffer[3];
	Obj.arg2 = (u8) ibuffer[4];
	Obj.arg3 = (u8) ibuffer[5];

	ListInsert( particleSystems, Obj, 0 );

	fscanf( file, "\n\n" );
}

// loads the particle systems specified in the file
// destroys existing particle system if not NULL
// return new particle system
// does nothing else if filename is NULL
PPARTICLE_SYSTEMS_HEAD
	ParticleSystemsLoadFileAndActivate(PPARTICLE_SYSTEMS_HEAD *_particleSystems,
                                       s8                     *filename,
									   f32                    _currentTime
                                      )
{
	s32        Num = 0;
	FILE       *file;
	PLIST_HEAD particleSystems;

	currentTime = _currentTime;

	ParticleSystemsTerminate( _particleSystems, 0 );

	if( !filename )
		return 0;

	file = fopen( filename, "rb" );

	if( !file )
		return 0;

	fscanf( file, "%i\n\n", &Num );  // NUMBER OF PARTICLE SYSTEMS

	if( Num <= 0 )
	{
		fclose ( file );

		return 0;
	}

	if( Num < 16 )
		particleSystems = ListInit( 0, 16  );
	else
		particleSystems = ListInit( 0, Num );

	if( !particleSystems )
	{
		fclose ( file );

		return 0;
	}

	do
	{
		ParticleSystemsInternalLoad( particleSystems, file );

	}while( --Num );

	fclose ( file );

	return (PPARTICLE_SYSTEMS_HEAD) particleSystems;
}

// adds a particle system specified in the
// file, does nothing if filename is NULL
void
	ParticleSystemsAddFileAndActivate(PPARTICLE_SYSTEMS_HEAD *particleSystems,
									  s8                     *filename,
								      f32                    _currentTime
                                     )
{
	s32  Num = 0;
	FILE *file;

	currentTime = _currentTime;

	if( !particleSystems || !filename )
		return;

	#define particleSystems ( (PLIST_HEAD) (*particleSystems) )

	file = fopen( filename, "rb" );

	if( !file )
		return;

	fscanf( file, "%i\n\n", &Num );  // NUMBER OF PARTICLE SYSTEMS

	if( Num <= 0 )
	{
		fclose ( file );

		return;
	}

	if( !particleSystems )
		particleSystems = ListInit( 0, 16 );

	if( !particleSystems )
	{
		fclose ( file );

		return;
	}

	do
	{
		ParticleSystemsInternalLoad( particleSystems, file );

	}while( --Num );

	fclose ( file );

	#undef particleSystems
}

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

		s8        *name,												  // EMITTER NAME
		f32       _currentTime,											  // CURRENT TIME IN SECONDS
		f32       emitterLife,											  // HOW LONG WILL THE PARTICLE SYSTEM LAST - IN SECONDS
		// TRANSFORMATION INFO
		f32       posX,           f32 posY,           f32 posZ,		      // XYZ POSITION OF PARTICLE SYSTEM ORIGIN AND VARIATION
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
		f32       gForceVarX,     f32 gForceVarY,     f32 gForceVarZ,

		u8        antiAlias,											  // IF NOT SET TO 0, PARTICLES WILL BE SHADED LINES
																		      // IF SET TO 0, PARTICLES WILL BE COLORED POINTS

		u8        physics,												  // IF NOT SET TO 0, ACCELERATION WILL BE INTEGRATED
																		      // INTO PARTICLES
																		      // IF SET TO 0, ONLY VELOCITY WILL BE TAKEN
																			  // INTO ACCOUNT

		u8        regeneration											  // IF NOT SET TO 0, DEAD PARTICLES WILL BE
																			  // REGENERATED
																		      // IF SET TO 0, DEAD PARTICLES WILL NOT BE
																			  // REGENERATED
	)
{
	CLIENT_POTYPE Obj = {0};

	if( !particleSystems )
		return;

	#define particleSystems ( (PLIST_HEAD) (*particleSystems) )

	if( !particleSystems )
		particleSystems = ListInit( 0, 16 );

	if( !particleSystems )
		return;

	strcpy( Obj.name, name );

	// IF FIRST TWO CHARACTERS ARE "OS", THEN NORMALIZE THE INPUT
	if( name && name[0] && name[1] && name[0]=='O' && name[1]=='S' )
	{
		f32 halfWidth     = ( (f32) __LinearFrameBufferGetWidth()  ) * 0.5f;
		f32 halfHeight    = ( (f32) __LinearFrameBufferGetHeight() ) * 0.5f;

		f32 invHalfWidth  = 1.0f / halfWidth;
		f32 invHalfHeight = 1.0f / halfHeight;

		f32 pi2rad     = 0.01745329f; // pi / 180

		f32 colorConv  = 0.00392156f; // 1 / 255

		posX =   ( posX - halfWidth  ) * invHalfWidth;
		posY = - ( posY - halfHeight ) * invHalfHeight;

		posVarX        *= invHalfWidth;
		posVarY        *= invHalfHeight;

		yaw            *= pi2rad;
		yawVar         *= pi2rad;

		pitch          *= pi2rad;
		pitchVar       *= pi2rad;

		speed          *= invHalfWidth;
		speedVar       *= invHalfWidth;

		startColorR    *= colorConv;
		startColorG    *= colorConv;
		startColorB    *= colorConv;

		startColorVarR *= colorConv;
		startColorVarG *= colorConv;
		startColorVarB *= colorConv;

		endColorR      *= colorConv;
		endColorG      *= colorConv;
		endColorB      *= colorConv;

		endColorVarR   *= colorConv;
		endColorVarG   *= colorConv;
		endColorVarB   *= colorConv;

		gForceX        *= invHalfWidth;
		gForceY        *= invHalfHeight;

		gForceVarX     *= invHalfWidth;
		gForceVarY     *= invHalfHeight;
	}

	Obj.particleSystem = (void*)
		CreateParticleSystem
		(
			Obj.name,
			_currentTime,
			emitterLife,
			posX,           posY,           posZ,
			posVarX,        posVarY,        posVarZ,
			yaw,            yawVar,
			pitch,          pitchVar,
			speed,          speedVar,
			numParticles,
			emitsPerFrame,  emitVar,
			life,           lifeVar,
			startColorR,    startColorG,    startColorB,
			startColorVarR, startColorVarG, startColorVarB,
			endColorR,      endColorG,      endColorB,
			endColorVarR,   endColorVarG,   endColorVarB,
			gForceX,        gForceY,        gForceZ,
			gForceVarX,     gForceVarY,     gForceVarZ
		);

	ActivateParticleSystem( (PEMITTER*) (&Obj.particleSystem), _currentTime, antiAlias, physics, regeneration );

	Obj.arg1 = antiAlias;
	Obj.arg2 = physics;
	Obj.arg3 = regeneration;

	ListInsert( particleSystems, Obj, 0 );

	#undef particleSystems
}

// reactivates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are reactivated
void
	ParticleSystemsReActivate(PPARTICLE_SYSTEMS_HEAD *particleSystems,
							  s8                     *particleSystemName,
							  f32                    _currentTime
							 )
{
	CLIENT_POTYPE Obj = {0};

	currentTime = _currentTime;

	if( !particleSystems )
		return;

	#define particleSystems ( (PLIST_HEAD) (*particleSystems) )

	if( !particleSystems )
		return;

	if( ListIsEmpty( particleSystems, 0 ) )
	{
		ListTerminate( particleSystems );

		particleSystems = 0;

		return;
	}

	if( particleSystemName )
	{
		strcpy( Obj.name, particleSystemName );

		if( ListFind( particleSystems, Equal, &Obj ) == 0 )
		{
			Activate( &Obj );

			if( !Obj.particleSystem )
				ListRemove( particleSystems, Equal, &Obj );
		}
	}
	else
	{
		ListDump( particleSystems, Activate, 0 );

		while( ListRemove( particleSystems, Dead, &Obj ) == 0 )
			1;
	}

	#undef particleSystems
}

// updates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are updated
void
	ParticleSystemsUpdate(PPARTICLE_SYSTEMS_HEAD *particleSystems,
						  s8                     *particleSystemName,
						  f32                    _currentTime
						 )
{
	CLIENT_POTYPE Obj = {0};

	currentTime = _currentTime;

	if( !particleSystems )
		return;

	#define particleSystems ( (PLIST_HEAD) (*particleSystems) )

	if( !particleSystems )
		return;

	if( ListIsEmpty( particleSystems, 0 ) )
	{
		ListTerminate( particleSystems );

		particleSystems = 0;

		return;
	}

	if( particleSystemName )
	{
		strcpy( Obj.name, particleSystemName );

		if( ListFind( particleSystems, Equal, &Obj ) == 0 )
		{
			Update( &Obj );

			if( !Obj.particleSystem )
				ListRemove( particleSystems, Equal, &Obj );
		}
	}
	else
	{
		ListDump( particleSystems, Update, 0 );

		while( ListRemove( particleSystems, Dead, &Obj ) == 0 )
			1;
	}

	#undef particleSystems
}

// draws the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are drawn
void
	ParticleSystemsDraw(PPARTICLE_SYSTEMS_HEAD *particleSystems,
						s8                     *particleSystemName,
                        f32                    *_matrix
					   )
{
	CLIENT_POTYPE Obj = {0};

	matrix = _matrix;

	if( !particleSystems )
		return;

	#define particleSystems ( (PLIST_HEAD) (*particleSystems) )

	if( !particleSystems )
		return;

	if( ListIsEmpty( particleSystems, 0 ) )
	{
		ListTerminate( particleSystems );

		particleSystems = 0;

		return;
	}

	if( particleSystemName )
	{
		strcpy( Obj.name, particleSystemName );

		if( ListFind( particleSystems, Equal, &Obj ) == 0 )
			Draw( &Obj );
	}
	else
		ListDump( particleSystems, Draw, 0 );

	#undef particleSystems
}

// updates and draws the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are updated and drawn
void
	ParticleSystemsUpdateAndDraw(PPARTICLE_SYSTEMS_HEAD *particleSystems,
								 s8                     *particleSystemName,
							     f32                    *_matrix,
						         f32                    _currentTime
						        )
{
	CLIENT_POTYPE Obj = {0};

	matrix      = _matrix;

	currentTime = _currentTime;

	if( !particleSystems )
		return;

	#define particleSystems ( (PLIST_HEAD) (*particleSystems) )

	if( !particleSystems )
		return;

	if( ListIsEmpty( particleSystems, 0 ) )
	{
		ListTerminate( particleSystems );

		particleSystems = 0;

		return;
	}

	if( particleSystemName )
	{
		strcpy( Obj.name, particleSystemName );

		if( ListFind( particleSystems, Equal, &Obj ) == 0 )
		{
			Update( &Obj );
			Draw  ( &Obj );

			if( !Obj.particleSystem )
				ListRemove( particleSystems, Equal, &Obj );
		}
	}
	else
	{
		ListDump( particleSystems, Update, 0 );
		ListDump( particleSystems, Draw,   0 );

		while( ListRemove( particleSystems, Dead, &Obj ) == 0 )
			1;
	}

	#undef particleSystems
}

// terminates the particle system which has the name
// specified in particleSystemName
//
// if particleSystemName is NULL, all particle
// systems are terminated
void
	ParticleSystemsTerminate(PPARTICLE_SYSTEMS_HEAD *particleSystems,
							 s8                     *particleSystemName
							)
{
	CLIENT_POTYPE Obj = {0};

	if( !particleSystems )
		return;

	#define particleSystems ( (PLIST_HEAD) (*particleSystems) )

	if( !particleSystems )
		return;

	if( ListIsEmpty( particleSystems, 0 ) )
	{
		ListTerminate( particleSystems );

		particleSystems = 0;

		return;
	}

	if( particleSystemName )
	{
		strcpy( Obj.name, particleSystemName );

		if( ListRemove( particleSystems, Equal, &Obj ) == 0 )
			Terminate( &Obj );
	}
	else
	{
		ListDump( particleSystems, Terminate, 0 );

		ListTerminate( particleSystems );

		particleSystems = 0;
	}

	#undef particleSystems
}