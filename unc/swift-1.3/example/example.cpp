//////////////////////////////////////////////////////////////////////////////
//
// example.C
//
//////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <SWIFT.h>

// Object filenames
static const char* object1_filename = "cube.poly";
static const char* object3_filename = "sphere.tri";

// Object data
static const SWIFT_Real vs[] =
{
    -3.0,  0.0,  2.0,
    -1.0,  2.0,  0.0,
    -5.0,  2.0,  0.0,
    -5.0, -2.0,  0.0,
    -1.0, -2.0,  0.0,
    -3.0,  0.0, -2.0 
};

static const int fs[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 3, 4,
    1, 0, 4,
    2, 1, 5,
    3, 2, 5,
    4, 3, 5,
    1, 4, 5
};

static const int vn = 6;
static const int fn = 8;

// Command line options
int nsteps = 1;
SWIFT_Real avel = 1.0;
bool print = false;

// Transformations for the objects
SWIFT_Real R[9];
SWIFT_Real T[3];
SWIFT_Real Q[4];    // Quaternion for the second object's rotation

int id1, id2, id3, id4;

// SWIFT scene
SWIFT_Scene* scene;

void Initialize_Scene( )
{
    // Create a swift scene with local bounding box sorting
    scene = new SWIFT_Scene( true, false );
    cerr << "Created a SWIFT_Scene" << endl;

    // Add some objects to the scene.

    // A fixed cube scaled by 0.1 with a bounding box enlarged by 0.5
    if( !scene->Add_Object( object1_filename, id1, true,
                            DEFAULT_ORIENTATION, DEFAULT_TRANSLATION, 0.1,
                            DEFAULT_BOX_SETTING, DEFAULT_BOX_ENLARGE_REL, 0.5 )
    ) {
        cerr << "Adding object1 failed -- Exiting..." << endl;
        exit( -1 );
    } else {
        cerr << "Added object1 to scene" << endl;
    }

    // A moving object scaled by 0.05 with a bounding box enlarged by 0.5
    if( !scene->Add_Object( vs, fs, vn, fn, id2, false,
                            DEFAULT_ORIENTATION, DEFAULT_TRANSLATION, 0.05,
                            DEFAULT_BOX_SETTING, DEFAULT_BOX_ENLARGE_REL, 0.5 )
    ) {
        cerr << "Adding object2 failed -- Exiting..." << endl;
        exit( -1 );
    } else {
        cerr << "Added object2 to scene" << endl;
    }

    // A moving sphere
    if( !scene->Add_Object( object3_filename, id3, false, DEFAULT_ORIENTATION,
                            DEFAULT_TRANSLATION, DEFAULT_SCALE,
                            DEFAULT_BOX_SETTING, DEFAULT_BOX_ENLARGE_REL, 1.0 )
    ) {
        cerr << "Adding object3 failed -- Exiting..." << endl;
        exit( -1 );
    } else {
        cerr << "Added object3 to scene" << endl;
    }

    // Copy object2 to create object4
    if( !scene->Add_Object( NULL, NULL, 0, 0, id4, false,
                            DEFAULT_ORIENTATION, DEFAULT_TRANSLATION,
                            DEFAULT_SCALE, DEFAULT_BOX_SETTING,
                            DEFAULT_BOX_ENLARGE_REL, 0.5,
                            DEFAULT_FACE_VALENCES, id2, 0 )
    ) {
        cerr << "Copying object2 failed -- Exiting..." << endl;
        exit( -1 );
    } else {
        cerr << "Copied object2 to object4" << endl;
    }

    cerr << "Deleting object2" << endl;
    scene->Delete_Object( id2 );

    // We wish to query the distance from object1 to all other objects.

    // Deactivate all pairs
    scene->Deactivate();

    // Activate only pairs of object1
    scene->Activate( id1 );

    // Set the initial transformations for object1.  I do not bother
    // setting it for the other objects since I never move them.  They have
    // identity transformations by default.

    // Object 1 orbits about the origin
    R[0] = 1.0; R[1] = 0.0; R[2] = 0.0;
    R[3] = 0.0; R[4] = 1.0; R[5] = 0.0;
    R[6] = 0.0; R[7] = 0.0; R[8] = 1.0;

    T[0] = 1.0; T[1] = 0.0; T[2] = 1.0;
    Q[0] = 0.0; Q[1] = 0.0; Q[2] = 0.0; Q[3] = 1.0;
    scene->Set_Object_Transformation( id1, R, T );
    cerr << "Set initial transformation for object 1" << endl;
}

void Do_Steps( )
{
    int scount;
    int np, i;
    int* oids;
    SWIFT_Real* dists;
    SWIFT_Real ang = 0.0;

    cerr << "Doing " << nsteps << " steps with angular velocity " << avel
         << endl;

    for( scount = 0; scount < nsteps; scount++ ) {
        // Adjust the quaternion
        Q[0] = sin( ang * 0.5 );
        Q[3] = cos( ang * 0.5 );

        // Convert the quaternion to a matrix
        R[0] = 1.0 - 2.0 * Q[1] * Q[1] - 2.0 * Q[2] * Q[2];
        R[1] = 2.0 * Q[0] * Q[1] - 2.0 * Q[3] * Q[2];
        R[2] = 2.0 * Q[0] * Q[2] + 2.0 * Q[3] * Q[1];
        R[3] = 2.0 * Q[0] * Q[1] + 2.0 * Q[3] * Q[2];
        R[4] = 1.0 - 2.0 * Q[0] * Q[0] - 2.0 * Q[2] * Q[2];
        R[5] = 2.0 * Q[1] * Q[2] - 2.0 * Q[3] * Q[0];
        R[6] = 2.0 * Q[0] * Q[2] - 2.0 * Q[3] * Q[1];
        R[7] = 2.0 * Q[1] * Q[2] + 2.0 * Q[3] * Q[0];
        R[8] = 1.0 - 2.0 * Q[0] * Q[0] - 2.0 * Q[1] * Q[1];

        // The translation is tied to the rotation
        T[0] = cos( ang );
        T[1] = sin( ang );
        T[2] = cos( ang );

        // Move the second object to its new position
        scene->Set_Object_Transformation( id1, R, T );

        // Query distance
        scene->Query_Exact_Distance( false, SWIFT_INFINITY, np, &oids, &dists );

        if( print ) { 
            cerr << "Distances at step " << scount+1 << ":" << endl;
            for( i = 0; i < np; i++ ) {
                cerr << "    Object " << oids[i<<1] << " vs. Object "
                     << oids[(i<<1)+1] << " = " << dists[i] << endl;
            }
        }

        // Increment the angle of rotation
        ang += avel * PI / 180.0;
    }
}

void Print_Usage( )
{
    cerr << "Usage: " << endl;
    cerr << "  example [options]" << endl;
    cerr << "Options:" << endl;
    cerr << "  -h        : Print this help" << endl;
    cerr << "  -p        : Print the distances for each step" << endl;
    cerr << "  -n <int>  : Number of steps to run for" << endl;
    cerr << "  -a <real> : Angular velocity in degrees/step" << endl;
    cerr << "Default values: " << endl;
    cerr << "  n = 1"  << endl;
    cerr << "  a = 1.0"  << endl;
    cerr << "  print is false" << endl;
    exit( -1 );
}

int main( int argc, char **argv )
{
    int i;

    // Process command line options
    i = 1;
    while( i != argc ) {
        if( !strcmp( argv[i], "-h" ) ) {
            // Help
            Print_Usage();
        } else if( !strcmp( argv[i], "-p" ) ) {
            // Print results
            print = true;
        } else if( !strcmp( argv[i], "-n" ) ) {
            // Number of steps
            i++;
            nsteps = atoi( argv[i] );
            nsteps = nsteps <= 0 ? 1 : nsteps;
        } else if( !strcmp( argv[i], "-a" ) ) {
            // Angular velocity
            i++;
            avel = atof( argv[i] );
            avel = avel <= 0.0 ? 1.0 : avel;
        } else {
            break;
        }
        i++;
    }

    // Initialize the scenario
    Initialize_Scene();

    // Run the steps
    Do_Steps();

    // Delete the scene
    delete scene;

    return 0;
}

