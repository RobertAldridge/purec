/*************************************************************************\

  Copyright 2000 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify OR distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE
  LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
  CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE
  USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY
  OF NORTH CAROLINA HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGES.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY
  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
  PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
  NORTH CAROLINA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
  UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

  The authors may be contacted via:

  US Mail:             S. Ehmann, M. Lin
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:               (919) 962-1749

  EMail:               geom@cs.unc.edu
                       ehmann@cs.unc.edu
                       lin@cs.unc.edu

\**************************************************************************/


//////////////////////////////////////////////////////////////////////////////
//
// scene.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include <iostream.h>


#include <SWIFT.h>
#include <SWIFT_config.h>
#include <SWIFT_common.h>
#include <SWIFT_linalg.h>
#include <SWIFT_array.h>
#include <SWIFT_mesh.h>
#include <SWIFT_mesh_utils.h>
#include <SWIFT_boxnode.h>
#include <SWIFT_object.h>
#include <SWIFT_pair.h>
#include <SWIFT_fileio.h>


///////////////////////////////////////////////////////////////////////////////
// File Reading Objects
///////////////////////////////////////////////////////////////////////////////

SWIFT_File_Read_Dispatcher file_dispatcher;
SWIFT_Basic_File_Reader basic_file_reader;
SWIFT_Obj_File_Reader obj_file_reader;


///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

// Segment size for the object array which is grown dynamically.  This should
// be a power of 2.
static const int OBJECT_SEGMENT_SIZE = 4;

// How big to create the reporting lists and how much to grow them by
static const int REPORTING_LIST_CREATION_SIZE = 100;
static const int REPORTING_LIST_GROW_SIZE = 100;


///////////////////////////////////////////////////////////////////////////////
// Static functions
///////////////////////////////////////////////////////////////////////////////
static bool Use_Cube( SWIFT_Tri_Mesh* m, bool fixed, int box_setting,
                      SWIFT_Real cube_aspect_ratio_threshold )
{
    if( fixed ) {
        return false;
    } else {
        if( box_setting == BOX_SETTING_CUBE ) {
            return true;
        } else if( box_setting == BOX_SETTING_DYNAMIC ) {
            return false;
        } else {
            // Choose the box setting based on aspect ratio
            SWIFT_Real min_spread, max_spread;
            Compute_Min_And_Max_Spread( m, min_spread, max_spread );
            return max_spread / min_spread < cube_aspect_ratio_threshold;
        }
    }
}

static bool Is_Identity( const SWIFT_Orientation& orient,
                         const SWIFT_Translation& trans, SWIFT_Real scale )
{
    if( scale == 1.0 ) {
        if( trans == NULL ||
            (trans[0] == 0.0 && trans[1] == 0.0 && trans[2] == 0.0)
        ) {
            return orient == NULL ||
                   (orient[0] == 1.0 && orient[1] == 0.0 && orient[2] == 0.0 &&
                    orient[3] == 0.0 && orient[4] == 1.0 && orient[5] == 0.0 &&
                    orient[6] == 0.0 && orient[7] == 0.0 && orient[8] == 1.0);
        } else {
            return false;
        }
    } else {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////
// Scene Creation methods
///////////////////////////////////////////////////////////////////////////////

SWIFT_Scene::SWIFT_Scene( bool broad_phase, bool global_sort )
{
    // Create the lists
    objects.Create( OBJECT_SEGMENT_SIZE );
    object_ids.Create( OBJECT_SEGMENT_SIZE );
    user_object_ids.Create( OBJECT_SEGMENT_SIZE );
    objects.Set_Length( 0 );
    object_ids.Set_Length( 0 );
    user_object_ids.Set_Length( 0 );
    piece_ids.Create( OBJECT_SEGMENT_SIZE );
    piece_ids.Set_Length( 0 );

    total_pairs = 0;
    overlapping_pairs = NULL;

    // Register the file readers
    basic_file_reader.Register_Yourself( file_dispatcher );
    obj_file_reader.Register_Yourself( file_dispatcher );

    bp = broad_phase;
    gs = global_sort;

    if( bp ) {
        sorted[0].Create( OBJECT_SEGMENT_SIZE<<1 );
        sorted[1].Create( OBJECT_SEGMENT_SIZE<<1 );
        sorted[2].Create( OBJECT_SEGMENT_SIZE<<1 );
        sorted[0].Set_Length( 0 );
        sorted[1].Set_Length( 0 );
        sorted[2].Set_Length( 0 );
    }

    // Create the initial reporting lists
    ds.Create( REPORTING_LIST_CREATION_SIZE );
    ds.Set_Length( 0 );
    nps.Create( REPORTING_LIST_CREATION_SIZE*6 );
    nps.Set_Length( 0 );
    cns.Create( REPORTING_LIST_CREATION_SIZE*3 );
    cns.Set_Length( 0 );
    es.Create( REPORTING_LIST_CREATION_SIZE );
    es.Set_Length( 0 );
    pis.Create( REPORTING_LIST_CREATION_SIZE<<1 );
    pis.Set_Length( 0 );
    fts.Create( REPORTING_LIST_CREATION_SIZE<<1 );
    fts.Set_Length( 0 );
    fis.Create( REPORTING_LIST_CREATION_SIZE<<2 );
    fis.Set_Length( 0 );

    // Initialize non-object modules
    Mesh_Utils_Initialize();
}


///////////////////////////////////////////////////////////////////////////////
// Scene Deletion methods
///////////////////////////////////////////////////////////////////////////////

SWIFT_Scene::~SWIFT_Scene( )
{
    int i;

    for( i = 0; i < objects.Length(); i++ ) {
        // Just delete the objects.  The boxes and the geometry are included
        // in the objects.
        delete objects[i];
    }
}


//////////////////////////////////////////////////////////////////////////////
// Object Creation methods
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Adds single piece object from arrays
bool SWIFT_Scene::Add_Object(
    const SWIFT_Real* vs, const int* fs, int vn, int fn, int& id, bool fixed,
    const SWIFT_Orientation& orient, const SWIFT_Translation& trans,
    SWIFT_Real scale, int box_setting, SWIFT_Real box_enl_rel,
    SWIFT_Real box_enl_abs, const int* fv, int copy_oid, int copy_pid,
    int min_tcount, SWIFT_Real qslim_tratio, SWIFT_Real cube_aspect_ratio )
{
    SWIFT_Tri_Mesh* stm;
    bool copy = copy_oid >= 0;
    bool use_cube;

    if( copy ) {
        copy_pid = (copy_pid < 0 ? 0 : copy_pid);

#ifdef SWIFT_DEBUG
        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        if( copy_oid >= object_ids.Length() ) {
            cerr << "Error (Add_Object'1 obj " << new_obj_id
                 << "): Invalid object id given to copy a piece: "
                 << copy_oid << endl;
            return false;
        }

        if( object_ids[copy_oid] == -1 ) {
            cerr << "Error (Add_Object'1 obj " << new_obj_id
                 << "): Object to be copied is deleted: " << copy_oid << endl;
            return false;
        }

        if( copy_pid >= objects[object_ids[copy_oid]]->Number_Of_Pieces() ) {
            cerr << "Error (Add_Object'1 obj " << new_obj_id
                 << "): Invalid piece id given to copy a piece: "
                 << copy_pid << endl;
            return false;
        }
#endif
        if( Is_Identity( orient, trans, scale ) ) {
            // Non-replication copy
            stm = objects[object_ids[copy_oid]]->Mesh( copy_pid );
            stm->Increment_Ref();
        } else {
            // Replication copy
            stm = objects[object_ids[copy_oid]]->Mesh( copy_pid )->Clone(
                                                        orient, trans, scale );
        }

        box_setting = (box_setting == BOX_SETTING_DEFAULT
                    ? (objects[object_ids[copy_oid]]->Fixed()
                        ? (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE)
                        : (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_COPY))
                    : box_setting);
        if( box_setting == BOX_SETTING_COPY ) {
            box_setting = (objects[object_ids[copy_oid]]->Use_Cube( copy_pid )
                          ? BOX_SETTING_CUBE : BOX_SETTING_DYNAMIC);
        }
        use_cube = Use_Cube( stm, fixed, box_setting, cube_aspect_ratio );
    } else {
        // Creating this piece
        stm = new SWIFT_Tri_Mesh;

        if( box_setting == BOX_SETTING_COPY ) {
            const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                          : free_oids.Last();
            cerr << "Error (Add_Object'1 obj " << new_obj_id
                 << "): Cannot set box type to COPY when copy is "
                 << "not done" << endl;
            return false;
        } else if( box_setting == BOX_SETTING_DEFAULT ) {
            box_setting = fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE;
        }

        if( !stm->Create( vs, fs, vn, fn, orient, trans, scale, fv
#ifdef SWIFT_HIERARCHY
                          , min_tcount
#ifdef SWIFT_QSLIM_HIER
                          , qslim_tratio
#endif
#endif
        ) ) {
            // Delete everything
            delete stm;
            return false;
        }

        use_cube = Use_Cube( stm, fixed, box_setting, cube_aspect_ratio );
    }

    SWIFT_Object* cobj = new SWIFT_Object;

    cobj->Initialize( stm, fixed, use_cube, box_enl_rel, box_enl_abs, copy );

    Initialize_Object_In_Scene( cobj, id );

    return true;
}

//////////////////////////////////////////////////////////////////////////////
// Adds single piece object from file
bool SWIFT_Scene::Add_Object(
    const char* f, int& id, bool fixed, const SWIFT_Orientation& orient,
    const SWIFT_Translation& trans, SWIFT_Real scale,
    int box_setting, SWIFT_Real box_enl_rel, SWIFT_Real box_enl_abs,
    int min_tcount, SWIFT_Real qslim_tratio, SWIFT_Real cube_aspect_ratio )
{
    SWIFT_Tri_Mesh* stm;
    bool use_cube;


    SWIFT_Real* vs = NULL;
    int* fs = NULL;
    int vn, fn;
    int* fv = NULL;

    if( !file_dispatcher.Read( f, vs, fs, vn, fn, fv ) ) {
        // Delete everything
        delete vs; delete fs; delete fv;

        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        cerr << "Error (Add_Object'2 obj " << new_obj_id
             << "): File read failed" << endl;
        return false;
    }

    stm = new SWIFT_Tri_Mesh;

    if( !stm->Create( vs, fs, vn, fn, orient, trans, scale, fv
#ifdef SWIFT_HIERARCHY
                      , min_tcount
#ifdef SWIFT_QSLIM_HIER
                      , qslim_tratio
#endif
#endif
    ) ) {
        // Delete everything
        delete stm; delete vs; delete fs; delete fv;

        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        cerr << "Error (Add_Object'2 obj " << new_obj_id
             << "): Mesh creation failed" << endl;
        return false;
    }

    if( box_setting == BOX_SETTING_COPY ) {
        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        cerr << "Error (Add_Object'2 obj " << new_obj_id
             << "): Cannot set box type to COPY when copy is "
             << "not done" << endl;
        return false;
    } else if( box_setting == BOX_SETTING_DEFAULT ) {
        box_setting = fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE;
    }

    delete vs; delete fs; delete fv;

    use_cube = Use_Cube( stm, fixed, box_setting, cube_aspect_ratio );

    SWIFT_Object* cobj = new SWIFT_Object;

    cobj->Initialize( stm, fixed, use_cube, box_enl_rel, box_enl_abs, false );

    Initialize_Object_In_Scene( cobj, id );

    return true;
}

//////////////////////////////////////////////////////////////////////////////
// Adds multiple pieced object from arrays
bool SWIFT_Scene::Add_Pieced_Object(
    const SWIFT_Real* const* vs, const int* const* fs,
    const int* vn, const int* fn, int pn, int& id, bool fixed,
    const SWIFT_Orientation* orient, const SWIFT_Translation* trans,
    const SWIFT_Real* scales, const int* box_settings,
    const SWIFT_Real* box_enl_rel, const SWIFT_Real* box_enl_abs,
    const int* const* fv, const int* copy_oids, const int* copy_pids,
    const int* min_tcounts, const SWIFT_Real* qslim_tratios,
    const SWIFT_Real* cube_aspect_ratios )
{
    int i, j;
    SWIFT_Tri_Mesh** stms = new SWIFT_Tri_Mesh*[pn];
    bool* copy = new bool[pn];
    bool* use_cube = new bool[pn];

    for( i = 0; i < pn; i++ ) {
        const SWIFT_Orientation* orient_elem =
                        (orient == NULL ? &DEFAULT_ORIENTATION : &(orient[i]));
        const SWIFT_Translation* trans_elem =
                        (trans == NULL ? &DEFAULT_TRANSLATION : &(trans[i]));
        const SWIFT_Real scales_elem = (scales == NULL ? 1.0 : scales[i]);
        const int* fv_elem = (fv == NULL ? NULL : fv[i]);
        const SWIFT_Real cube_aspect_ratio = (cube_aspect_ratios == NULL ?
                             DEFAULT_CUBE_ASPECT_RATIO : cube_aspect_ratios[i]);
        int box_setting = (box_settings == NULL
                          ? BOX_SETTING_DEFAULT : box_settings[i]);

        copy[i] = copy_oids != NULL && copy_oids[i] >= 0;
        if( copy[i] ) {
            const int copy_pid = ((copy_pids == NULL || copy_pids[i] < 0)
                             ? 0 : copy_pids[i]);

#ifdef SWIFT_DEBUG
            const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                          : free_oids.Last();
            if( copy_oids[i] >= object_ids.Length() ) {
                cerr << "Error (Add_Pieced_Object'1 obj " << new_obj_id
                     << "): Invalid object id given to copy a piece: "
                     << copy_oids[i] << endl;
                break;
            }

            if( object_ids[copy_oids[i]] == -1 ) {
                cerr << "Error (Add_Pieced_Object'1 obj " << new_obj_id
                     << "): Object to be copied is deleted: "
                     << copy_oids[i] << endl;
                break;
            }

            if( copy_pid >= objects[object_ids[copy_oids[i]]]->
                                                        Number_Of_Pieces()
            ) {
                cerr << "Error (Add_Pieced_Object'1 obj " << new_obj_id
                     << " piece " << i
                     << "): Invalid piece id given to copy a piece: "
                     << copy_pid << endl;
                break;
            }
#endif
            if( Is_Identity( *orient_elem, *trans_elem, scales_elem ) ) {
                // Non-replication copy
                stms[i] = objects[object_ids[copy_oids[i]]]->Mesh( copy_pid );
                stms[i]->Increment_Ref();
            } else {
                // Replication copy
                stms[i] = objects[object_ids[copy_oids[i]]]->Mesh( copy_pid )->
                            Clone( *orient_elem, *trans_elem, scales_elem );
            }

            box_setting = (box_setting == BOX_SETTING_DEFAULT
                        ? (objects[object_ids[copy_oids[i]]]->Fixed()
                            ? (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE)
                            : (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_COPY))
                        : box_settings[i]);
            if( box_setting == BOX_SETTING_COPY ) {
                box_setting = (objects[object_ids[copy_oids[i]]]->Use_Cube(
                        copy_pid ) ? BOX_SETTING_CUBE : BOX_SETTING_DYNAMIC);
            }
            use_cube[i] = Use_Cube( stms[i], fixed, box_setting,
                                             cube_aspect_ratio );
        } else {
            stms[i] = new SWIFT_Tri_Mesh;

            if( box_setting == BOX_SETTING_COPY ) {
                cerr << "Error (Add_Pieced_Object'1 obj " << objects.Length()
                     << " piece " << i << "): Cannot set box type to COPY "
                     << "when copy is not done" << endl;
                break;
            } else if( box_setting == BOX_SETTING_DEFAULT ) {
                box_setting = fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE;
            }

#ifdef SWIFT_HIERARCHY
            const int min_tcount = (min_tcounts == NULL ?
                                    DEFAULT_MIN_TCOUNT : min_tcounts[i]);
#ifdef SWIFT_QSLIM_HIER
            const SWIFT_Real qslim_tratio = (qslim_tratios == NULL ?
                                    DEFAULT_QSLIM_TRATIO : qslim_tratios[i]);
#endif
#endif
            if( !stms[i]->Create( vs[i], fs[i], vn[i], fn[i],
                                  *orient_elem, *trans_elem, scales_elem,
                                  fv_elem
#ifdef SWIFT_HIERARCHY
                                  , min_tcount
#ifdef SWIFT_QSLIM_HIER
                                  , qslim_tratio
#endif
#endif
            ) ) {
                delete stms[i];
                cerr << "Error (Add_Pieced_Object'1 obj " << objects.Length()
                     << " piece " << i << "): Mesh creation failed" << endl;
                break;
            }

            use_cube[i] = Use_Cube( stms[i], fixed, box_setting,
                                                    cube_aspect_ratio );
        }
    }

    if( i != pn ) {
        // Failure along the way.  Delete everything
        for( j = 0; j < i; j++ ) {
            if( stms[j]->Ref() == 0 ) {
                delete stms[j];
            } else {
                stms[j]->Decrement_Ref();
            }
        }
        delete stms; delete use_cube; delete copy;
        return false;
    }

    SWIFT_Object* cobj = new SWIFT_Object( pn );

    cobj->Initialize( stms, fixed, use_cube, box_enl_rel, box_enl_abs, copy );

    delete stms; delete use_cube; delete copy;

    Initialize_Object_In_Scene( cobj, id );

    return true;
}

//////////////////////////////////////////////////////////////////////////////
// Adds multiple pieced object from files
bool SWIFT_Scene::Add_Pieced_Object(
    const char* const* f, int pn, int& id, bool fixed,
    const SWIFT_Orientation* orient, const SWIFT_Translation* trans,
    const SWIFT_Real* scales, const int* box_settings,
    const SWIFT_Real* box_enl_rel, const SWIFT_Real* box_enl_abs,
    const int* copy_oids, const int* copy_pids, const int* min_tcounts,
    const SWIFT_Real* qslim_tratios, const SWIFT_Real* cube_aspect_ratios )
{
    int i, j;
    SWIFT_Tri_Mesh** stms = new SWIFT_Tri_Mesh*[pn];
    bool* copy = new bool[pn];
    bool* use_cube = new bool[pn];

    for( i = 0; i < pn; i++ ) {
        const SWIFT_Orientation* orient_elem =
                        (orient == NULL ? &DEFAULT_ORIENTATION : &(orient[i]));
        const SWIFT_Translation* trans_elem =
                        (trans == NULL ? &DEFAULT_TRANSLATION : &(trans[i]));
        const SWIFT_Real scales_elem = (scales == NULL ? 1.0 : scales[i]);
        const SWIFT_Real cube_aspect_ratio = (cube_aspect_ratios == NULL ?
                             DEFAULT_CUBE_ASPECT_RATIO : cube_aspect_ratios[i]);
        int box_setting = (box_settings == NULL
                          ? BOX_SETTING_DEFAULT : box_settings[i]);

        copy[i] = copy_oids != NULL && copy_oids[i] >= 0;
        if( copy[i] ) {
            const int copy_pid = ((copy_pids == NULL || copy_pids[i] < 0)
                             ? 0 : copy_pids[i]);

#ifdef SWIFT_DEBUG
            const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                          : free_oids.Last();
            if( copy_oids[i] >= object_ids.Length() ) {
                cerr << "Error (Add_Pieced_Object'2 obj " << new_obj_id
                     << "): Invalid object id given to copy a piece: "
                     << copy_oids[i] << endl;
                break;
            }

            if( object_ids[copy_oids[i]] == -1 ) {
                cerr << "Error (Add_Pieced_Object'2 obj " << new_obj_id
                     << "): Object to be copied is deleted: "
                     << copy_oids[i] << endl;
                break;
            }

            if( copy_pid >= objects[object_ids[copy_oids[i]]]->
                                                        Number_Of_Pieces()
            ) {
                cerr << "Error (Add_Pieced_Object'2 obj " << new_obj_id
                     << " piece " << i
                     << "): Invalid piece id given to copy a piece: "
                     << copy_pid << endl;
                break;
            }
#endif
            if( Is_Identity( *orient_elem, *trans_elem, scales_elem ) ) {
                // Non-replication copy
                stms[i] = objects[object_ids[copy_oids[i]]]->Mesh( copy_pid );
                stms[i]->Increment_Ref();
            } else {
                // Replication copy
                stms[i] = objects[object_ids[copy_oids[i]]]->Mesh( copy_pid )->
                            Clone( *orient_elem, *trans_elem, scales_elem );
            }

            box_setting = (box_setting == BOX_SETTING_DEFAULT
                        ? (objects[object_ids[copy_oids[i]]]->Fixed()
                            ? (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE)
                            : (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_COPY))
                        : box_settings[i]);
            if( box_setting == BOX_SETTING_COPY ) {
                box_setting = (objects[object_ids[copy_oids[i]]]->Use_Cube(
                        copy_pid ) ? BOX_SETTING_CUBE : BOX_SETTING_DYNAMIC);
            }
            use_cube[i] = Use_Cube( stms[i], fixed, box_setting,
                                                    cube_aspect_ratio );
        } else {
            SWIFT_Real* vs = NULL;
            int* fs = NULL;
            int vn, fn;
            int* fv = NULL;

            if( box_setting == BOX_SETTING_COPY ) {
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Pieced_Object'2 obj " << new_obj_id
                     << " piece " << i << "): Cannot set box type to COPY "
                     << "when copy is not done" << endl;
                break;
            } else if( box_setting == BOX_SETTING_DEFAULT ) {
                box_setting = fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE;
            }

            if( !file_dispatcher.Read( f[i], vs, fs, vn, fn, fv ) ) {
                delete vs; delete fs; delete fv;
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Pieced_Object'2 obj " << new_obj_id
                     << " piece " << i << "): File read failed" << endl;
                break;
            }

            stms[i] = new SWIFT_Tri_Mesh;

#ifdef SWIFT_HIERARCHY
            const int min_tcount = (min_tcounts == NULL ?
                                    DEFAULT_MIN_TCOUNT : min_tcounts[i]);
#ifdef SWIFT_QSLIM_HIER
            const SWIFT_Real qslim_tratio = (qslim_tratios == NULL ?
                                    DEFAULT_QSLIM_TRATIO : qslim_tratios[i]);
#endif
#endif
            if( !stms[i]->Create( vs, fs, vn, fn,
                                  *orient_elem, *trans_elem, scales_elem, fv
#ifdef SWIFT_HIERARCHY
                                  , min_tcount
#ifdef SWIFT_QSLIM_HIER
                                  , qslim_tratio
#endif
#endif
            ) ) {
                delete stms[i];
                delete vs; delete fs; delete fv;
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Pieced_Object'2 obj " << new_obj_id
                     << " piece " << i << "): Mesh creation failed" << endl;
                break;
            }

            delete vs; delete fs; delete fv;

            use_cube[i] = Use_Cube( stms[i], fixed, box_setting,
                                                    cube_aspect_ratio );
        }
    }

    if( i != pn ) {
        // Failure along the way.  Delete everything
        for( j = 0; j < i; j++ ) {
            if( stms[j]->Ref() == 0 ) {
                delete stms[j];
            } else {
                stms[j]->Decrement_Ref();
            }
        }
        delete stms; delete use_cube; delete copy;
        return false;
    }

    SWIFT_Object* cobj = new SWIFT_Object( pn );

    cobj->Initialize( stms, fixed, use_cube, box_enl_rel, box_enl_abs, copy );

    delete stms; delete use_cube; delete copy;

    Initialize_Object_In_Scene( cobj, id );

    return true;
}

//////////////////////////////////////////////////////////////////////////////
// Adds single pieced object along with its hierarchy from arrays.
bool SWIFT_Scene::Add_Hierarchical_Object(
    const SWIFT_Real* const* vs, const int* const* fs,
    const int* vn, const int* fn, int ln, int& id, bool fixed,
    const SWIFT_Orientation* orient, const SWIFT_Translation* trans,
    const SWIFT_Real* scales, int box_setting, SWIFT_Real box_enl_rel,
    SWIFT_Real box_enl_abs, const int* const* fv, SWIFT_Real cube_aspect_ratio )
{
#ifdef SWIFT_HIERARCHY
#ifdef SWIFT_DEBUG
    if( ln < 0 ) {
        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        cerr << "Error (Add_Hierarchical_Object'1 obj " << new_obj_id
             << " piece 0): Invalid number of levels given (must be positive): "
             << ln << endl;
        return false;
    } else if( ln > MAX_LEVELS ) {
        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        cerr << "Error (Add_Hierarchical_Object'1 obj " << new_obj_id
             << " piece 0): Invalid number of levels given (must be less than "
             << "or equal to " << MAX_LEVELS << "): " << ln << endl;
        return false;
    }
#endif

    SWIFT_Tri_Mesh* stm = new SWIFT_Tri_Mesh;

    if( !stm->Create( vs, fs, vn, fn, ln,
#ifdef SWIFT_QSLIM_HIER
                      false, NULL,
#endif
                      orient, trans, scales, fv )
    ) {
        // Delete everything
        delete stm;

        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        cerr << "Error (Add_Hierarchical_Object'1 obj " << new_obj_id
             << " piece 0): Mesh creation failed" << endl;
        return false;
    }

    bool use_cube = Use_Cube( stm, fixed, box_setting, cube_aspect_ratio );
    SWIFT_Object* cobj = new SWIFT_Object;

    cobj->Initialize( stm, fixed, use_cube, box_enl_rel, box_enl_abs, false );

    Initialize_Object_In_Scene( cobj, id );

    return true;
#else
    cerr << "Error: SWIFT must be compiled with SWIFT_HIERARCHY defined for "
         << endl << "       the Add_Hierarchical_Object function to be used.  "
         << "See SWIFT_config.h." << endl;
    return false;
#endif
}

//////////////////////////////////////////////////////////////////////////////
// Adds single pieced object along with its hierarchy from files.
bool SWIFT_Scene::Add_Hierarchical_Object(
    const char* const* f, int ln, int& id, bool fixed,
    const SWIFT_Orientation* orient, const SWIFT_Translation* trans,
    const SWIFT_Real* scales, int box_setting,
    SWIFT_Real box_enl_rel, SWIFT_Real box_enl_abs,
    SWIFT_Real cube_aspect_ratio )
{
#ifdef SWIFT_HIERARCHY
    int i, j;
    SWIFT_Tri_Mesh* stm;

#ifdef SWIFT_DEBUG
    if( ln < 0 ) {
        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        cerr << "Error (Add_Hierarchical_Object'2 obj " << new_obj_id
             << " piece 0): Invalid number of levels given (must be positive): "
             << ln << endl;
        return false;
    } else if( ln > MAX_LEVELS ) {
        const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                      : free_oids.Last();
        cerr << "Error (Add_Hierarchical_Object'2 obj " << new_obj_id
             << " piece 0): Invalid number of levels given (must be less than "
             << "or equal to " << MAX_LEVELS << "): " << ln << endl;
        return false;
    }
#endif
    SWIFT_Real** vs = new SWIFT_Real*[ln];
    int** fs = new int*[ln];
    int* vn = new int[ln];
    int* fn = new int[ln];
    int** fv = new int*[ln];

    // Read the files
    for( i = 0; i < ln; i++ ) {
        vs[i] = NULL; fs[i] = NULL; fv[i] = NULL;
        if( !file_dispatcher.Read( f[i], vs[i], fs[i], vn[i], fn[i], fv[i] ) ) {
            const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                          : free_oids.Last();
            cerr << "Error (Add_Hierarchical_Object'2 obj " << new_obj_id
                 << " piece 0 level " << i << "): File read failed" << endl;
            j = i;
            break;
        }
    }

    if( i == ln ) {
        stm = new SWIFT_Tri_Mesh;

        if( !stm->Create( vs, fs, vn, fn, ln,
#ifdef SWIFT_QSLIM_HIER
                          false, NULL,
#endif
                          orient, trans, scales, fv )
        ) {
            // Delete everything
            delete stm;
            j = ln-1;   // Set j to the index of the highest level read.
            i = -1;     // Set i not equal to ln so that failure is detected.
            const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                          : free_oids.Last();
            cerr << "Error (Add_Hierarchical_Object'2 obj " << new_obj_id
                 << " piece 0): Mesh creation failed" << endl;
        }
    }

    // Delete everything
    for( ; j >= 0; j-- ) {
        delete vs[j]; delete fs[j]; delete fv[j];
    }
    delete vs; delete fs; delete vn; delete fn; delete fv;

    if( i != ln ) {
        // Failure
        return false;
    }

    bool use_cube = Use_Cube( stm, fixed, box_setting, cube_aspect_ratio );
    SWIFT_Object* cobj = new SWIFT_Object;

    cobj->Initialize( stm, fixed, use_cube, box_enl_rel, box_enl_abs, false );

    Initialize_Object_In_Scene( cobj, id );

    return true;
#else
    cerr << "Error: SWIFT must be compiled with SWIFT_HIERARCHY defined for "
         << endl << "       the Add_Hierarchical_Object function to be used.  "
         << "See SWIFT_config.h." << endl;
    return false;
#endif
}

//////////////////////////////////////////////////////////////////////////////
// Adds multiple pieced object along with its hierarchy from arrays.
bool SWIFT_Scene::Add_Hierarchical_Pieced_Object(
    const SWIFT_Real* const* const* vs, const int* const* const* fs,
    const int* const* vn, const int* const* fn, const int* ln, int pn, int& id,
    bool fixed, const SWIFT_Orientation* const* orient,
    const SWIFT_Translation* const* trans,
    const SWIFT_Real* const* scales, const int* box_settings,
    const SWIFT_Real* box_enl_rel, const SWIFT_Real* box_enl_abs,
    const int* const* const* fv, const int* copy_oids, const int* copy_pids,
    const int* min_tcounts, const SWIFT_Real* qslim_tratios,
    const SWIFT_Real* cube_aspect_ratios )
{
#ifdef SWIFT_HIERARCHY
    int i, j;
    SWIFT_Tri_Mesh** stms = new SWIFT_Tri_Mesh*[pn];
    bool* copy = new bool[pn];
    bool* use_cube = new bool[pn];

    for( i = 0; i < pn; i++ ) {
        const SWIFT_Real cube_aspect_ratio = (cube_aspect_ratios == NULL ?
                            DEFAULT_CUBE_ASPECT_RATIO : cube_aspect_ratios[i]);
        int box_setting = (box_settings == NULL
                          ? BOX_SETTING_DEFAULT : box_settings[i]);

        copy[i] = copy_oids != NULL && copy_oids[i] >= 0;
        if( copy[i] ) {
            const int copy_pid = ((copy_pids == NULL || copy_pids[i] < 0)
                             ? 0 : copy_pids[i]);
            const SWIFT_Orientation* orient_elem =
                (orient == NULL ? &DEFAULT_ORIENTATION :
                (orient[i] == NULL ? &DEFAULT_ORIENTATION : &(orient[i][0])));
            const SWIFT_Translation* trans_elem =
                (trans == NULL ? &DEFAULT_TRANSLATION :
                (trans[i] == NULL ? &DEFAULT_TRANSLATION : &(trans[i][0])));
            const SWIFT_Real scales_elem = (scales == NULL ? 1.0 :
                                    (scales[i] == NULL ? 1.0 : scales[i][0]));

#ifdef SWIFT_DEBUG
            const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                          : free_oids.Last();
            if( copy_oids[i] >= object_ids.Length() ) {
                cerr << "Error (Add_Hierarchical_Pieced_Object'1 obj "
                     << new_obj_id << " piece " << i
                     << "): Invalid object id given to copy a piece: "
                     << copy_oids[i] << endl;
                break;
            }

            if( object_ids[copy_oids[i]] == -1 ) {
                cerr << "Error (Add_Hierarchical_Pieced_Object'1 obj "
                     << new_obj_id << " piece " << i
                     << "): Object to be copied is deleted: "
                     << copy_oids[i] << endl;
                break;
            }

            if( copy_pid >= objects[object_ids[copy_oids[i]]]->
                                                        Number_Of_Pieces()
            ) {
                cerr << "Error (Add_Hierarchical_Pieced_Object'1 obj "
                     << new_obj_id << " piece " << i
                     << "): Invalid piece id given to copy a piece: "
                     << copy_pid << endl;
                break;
            }
#endif
            if( Is_Identity( *orient_elem, *trans_elem, scales_elem ) ) {
                // Non-replication copy
                stms[i] = objects[object_ids[copy_oids[i]]]->Mesh( copy_pid );
                stms[i]->Increment_Ref();
            } else {
                // Replication copy
                stms[i] = objects[object_ids[copy_oids[i]]]->Mesh( copy_pid )->
                            Clone( *orient_elem, *trans_elem, scales_elem );
            }

            box_setting = (box_setting == BOX_SETTING_DEFAULT
                        ? (objects[object_ids[copy_oids[i]]]->Fixed()
                            ? (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE)
                            : (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_COPY))
                        : box_settings[i]);
            if( box_setting == BOX_SETTING_COPY ) {
                box_setting = (objects[object_ids[copy_oids[i]]]->Use_Cube(
                        copy_pid ) ? BOX_SETTING_CUBE : BOX_SETTING_DYNAMIC);
            }
            use_cube[i] = Use_Cube( stms[i], fixed, box_setting,
                                                    cube_aspect_ratio );
        } else {
            if( box_setting == BOX_SETTING_COPY ) {
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Hierarchical_Pieced_Object'1 obj "
                     << new_obj_id << " piece " << i
                     << "): Cannot set box type to COPY when copy is not done"
                     << endl;
                break;
            } else if( box_setting == BOX_SETTING_DEFAULT ) {
                box_setting = fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE;
            }

            if( ln[i] < 0 ) {
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Hierarchical_Pieced_Object'1 obj "
                     << new_obj_id << " piece " << i
                     << "): Invalid number of levels given (must be positive): "
                     << ln[i] << endl;
                break;
            } else if( ln[i] > MAX_LEVELS ) {
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Hierarchical_Pieced_Object'1 obj "
                     << new_obj_id << " piece " << i
                     << "): Invalid number of levels given (must be less than "
                     << "or equal to " << MAX_LEVELS << "): " << ln[i] << endl;
                break;
            }

            stms[i] = new SWIFT_Tri_Mesh;

            if( ln[i] == 0 ) {
                // SWIFT is to build the hierarchy
                const SWIFT_Orientation* orient_elem =
                    (orient == NULL ? &DEFAULT_ORIENTATION :
                    (orient[i] == NULL ? &DEFAULT_ORIENTATION :
                                         &(orient[i][0])));
                const SWIFT_Translation* trans_elem =
                    (trans == NULL ? &DEFAULT_TRANSLATION :
                    (trans[i] == NULL ? &DEFAULT_TRANSLATION :
                                        &(trans[i][0])));
                const SWIFT_Real scales_elem = (scales == NULL ? 1.0 :
                                (scales[i] == NULL ? 1.0 : scales[i][0]));
#ifdef SWIFT_HIERARCHY
                const int min_tcount = (min_tcounts == NULL ?
                                        DEFAULT_MIN_TCOUNT : min_tcounts[i]);
#ifdef SWIFT_QSLIM_HIER
                const SWIFT_Real qslim_tratio = (qslim_tratios == NULL ?
                                    DEFAULT_QSLIM_TRATIO : qslim_tratios[i]);
#endif
#endif
                if( !stms[i]->Create( vs[i][0], fs[i][0], vn[i][0], fn[i][0],
                                      *orient_elem, *trans_elem, scales_elem,
                                      (fv == NULL ? NULL
                                        : (fv[i] == NULL ? NULL : fv[i][0]))
#ifdef SWIFT_HIERARCHY
                                      , min_tcount
#ifdef SWIFT_QSLIM_HIER
                                      , qslim_tratio
#endif
#endif
                ) ) {
                    // SWIFT building hierarchy mesh creation failed
                    delete stms[i];
                    const int new_obj_id = free_oids.Length() == 0
                                        ? objects.Length() : free_oids.Last();
                    cerr << "Error (Add_Hierarchical_Pieced_Object'1 obj "
                         << new_obj_id << " piece " << i
                         << "): Mesh creation failed -- SWIFT "
                         << "hierarchy" << endl;
                    break;
                }
            } else {
                // Hierarchy is given
                const SWIFT_Orientation* orient_elem =
                                (orient == NULL ? NULL : orient[i]);
                const SWIFT_Translation* trans_elem =
                                (trans == NULL ? NULL : trans[i]);
                const SWIFT_Real* scales_elem =
                                (scales == NULL ? NULL : scales[i]);
                if( !stms[i]->Create( vs[i], fs[i], vn[i], fn[i], ln[i],
#ifdef SWIFT_QSLIM_HIER
                                      false, NULL,
#endif
                                      orient_elem, trans_elem, scales_elem,
                                      (fv == NULL ? NULL : fv[i]) )
                ) {
                    // Hierarchy given mesh creation failed
                    delete stms[i];
                    const int new_obj_id = free_oids.Length() == 0
                                        ? objects.Length() : free_oids.Last();
                    cerr << "Error (Add_Hierarchical_Pieced_Object'1 obj "
                         << new_obj_id << " piece " << i
                         << "): Mesh creation failed -- application "
                         << "hierarchy" << endl;
                    break;
                }
            }

            use_cube[i] = Use_Cube( stms[i], fixed, box_setting,
                                                    cube_aspect_ratio );
        }
    }

    if( i != pn ) {
        // Failure along the way.  Delete everything
        for( j = 0; j < i; j++ ) {
            if( stms[j]->Ref() == 0 ) {
                delete stms[j];
            } else {
                stms[j]->Decrement_Ref();
            }
        }
        delete stms; delete use_cube; delete copy;
        return false;
    }

    SWIFT_Object* cobj = new SWIFT_Object( pn );

    cobj->Initialize( stms, fixed, use_cube, box_enl_rel, box_enl_abs, copy );

    delete stms; delete use_cube; delete copy;

    Initialize_Object_In_Scene( cobj, id );

    return true;
#else
    cerr << "Error: SWIFT must be compiled with SWIFT_HIERARCHY defined for "
         << endl << "       the Add_Hierarchical_Pieced_Object function to be "
         << "used.  See SWIFT_config.h." << endl;
    return false;
#endif
}

//////////////////////////////////////////////////////////////////////////////
// Adds multiple pieced object along with its hierarchy from files.
bool SWIFT_Scene::Add_Hierarchical_Pieced_Object(
    const char* const* const* f, const int* ln, int pn, int& id,
    bool fixed, const SWIFT_Orientation* const* orient,
    const SWIFT_Translation* const* trans,
    const SWIFT_Real* const* scales, const int* box_settings,
    const SWIFT_Real* box_enl_rel, const SWIFT_Real* box_enl_abs,
    const int* copy_oids, const int* copy_pids, const int* min_tcounts, 
    const SWIFT_Real* qslim_tratios, const SWIFT_Real* cube_aspect_ratios )
{
#ifdef SWIFT_HIERARCHY
    int i, j, k;
    SWIFT_Tri_Mesh** stms = new SWIFT_Tri_Mesh*[pn];
    bool* copy = new bool[pn];
    bool* use_cube = new bool[pn];

    for( i = 0; i < pn; i++ ) {
        const SWIFT_Real cube_aspect_ratio = (cube_aspect_ratios == NULL ?
                            DEFAULT_CUBE_ASPECT_RATIO : cube_aspect_ratios[i]);
        int box_setting = (box_settings == NULL
                          ? BOX_SETTING_DEFAULT : box_settings[i]);

        copy[i] = copy_oids != NULL && copy_oids[i] >= 0;
        if( copy[i] ) {
            const int copy_pid = ((copy_pids == NULL || copy_pids[i] < 0)
                             ? 0 : copy_pids[i]);
            const SWIFT_Orientation* orient_elem =
                (orient == NULL ? &DEFAULT_ORIENTATION :
                (orient[i] == NULL ? &DEFAULT_ORIENTATION : &(orient[i][0])));
            const SWIFT_Translation* trans_elem =
                (trans == NULL ? &DEFAULT_TRANSLATION :
                (trans[i] == NULL ? &DEFAULT_TRANSLATION : &(trans[i][0])));
            const SWIFT_Real scales_elem = (scales == NULL ? 1.0 :
                                    (scales[i] == NULL ? 1.0 : scales[i][0]));

#ifdef SWIFT_DEBUG
            const int new_obj_id = free_oids.Length() == 0 ? objects.Length()
                                                          : free_oids.Last();
            if( copy_oids[i] >= object_ids.Length() ) {
                cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                     << new_obj_id << " piece " << i
                     << "): Invalid object id given to copy a piece: "
                     << copy_oids[i] << endl;
                break;
            }

            if( object_ids[copy_oids[i]] == -1 ) {
                cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                     << new_obj_id << " piece " << i
                     << "): Object to be copied is deleted: "
                     << copy_oids[i] << endl;
                break;
            }

            if( copy_pid >= objects[object_ids[copy_oids[i]]]->
                                                        Number_Of_Pieces()
            ) {
                cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                     << new_obj_id << " piece " << i
                     << "): Invalid piece id given to copy a piece: "
                     << copy_pid << endl;
                break;
            }
#endif
            if( Is_Identity( *orient_elem, *trans_elem, scales_elem ) ) {
                // Non-replication copy
                stms[i] = objects[object_ids[copy_oids[i]]]->Mesh( copy_pid );
                stms[i]->Increment_Ref();
            } else {
                // Replication copy
                stms[i] = objects[object_ids[copy_oids[i]]]->Mesh( copy_pid )->
                            Clone( *orient_elem, *trans_elem, scales_elem );
            }

            box_setting = (box_setting == BOX_SETTING_DEFAULT
                        ? (objects[object_ids[copy_oids[i]]]->Fixed()
                            ? (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE)
                            : (fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_COPY))
                        : box_settings[i]);
            if( box_setting == BOX_SETTING_COPY ) {
                box_setting = (objects[object_ids[copy_oids[i]]]->Use_Cube(
                        copy_pid ) ? BOX_SETTING_CUBE : BOX_SETTING_DYNAMIC);
            }
            use_cube[i] = Use_Cube( stms[i], fixed, box_setting,
                                                    cube_aspect_ratio );
        } else {
            if( box_setting == BOX_SETTING_COPY ) {
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                     << new_obj_id << " piece " << i
                     << "): Cannot set box type to COPY when copy is not done"
                     << endl;
                break;
            } else if( box_setting == BOX_SETTING_DEFAULT ) {
                box_setting = fixed ? BOX_SETTING_DYNAMIC : BOX_SETTING_CUBE;
            }

            if( ln[i] < 0 ) {
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                     << new_obj_id << " piece " << i
                     << "): Invalid number of levels given (must be positive): "
                     << ln[i] << endl;
                break;
            } else if( ln[i] > MAX_LEVELS ) {
                const int new_obj_id = free_oids.Length() == 0 ?
                                        objects.Length() : free_oids.Last();
                cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                     << new_obj_id << " piece " << i
                     << "): Invalid number of levels given (must be less than "
                     << "or equal to " << MAX_LEVELS << "): " << ln[i] << endl;
                break;
            }

            const int num_levels = max(ln[i],1);
            SWIFT_Real** vs = new SWIFT_Real*[num_levels];
            int** fs = new int*[num_levels];
            int* vn = new int[num_levels];
            int* fn = new int[num_levels];
            int** fv = new int*[num_levels];

            // Read the files
            for( j = 0, k = -1; j < num_levels; j++, k++ ) {
                vs[j] = NULL; fs[j] = NULL; fv[j] = NULL;
                if( !file_dispatcher.Read( f[i][j], vs[j], fs[j], 
                                           vn[j], fn[j], fv[j] )
                ) {
                    const int new_obj_id = free_oids.Length() == 0
                                        ? objects.Length() : free_oids.Last();
                    cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                         << new_obj_id << " piece " << i
                         << " level " << j << "): File read failed" << endl;
                    break;
                }
            }

            if( j == num_levels ) {
                // All the reading succeeded
                stms[i] = new SWIFT_Tri_Mesh;

                if( ln[i] == 0 ) {
                    // SWIFT is to build the hierarchy
                    const SWIFT_Orientation* orient_elem =
                        (orient == NULL ? &DEFAULT_ORIENTATION :
                        (orient[i] == NULL ? &DEFAULT_ORIENTATION :
                                             &(orient[i][0])));
                    const SWIFT_Translation* trans_elem =
                        (trans == NULL ? &DEFAULT_TRANSLATION :
                        (trans[i] == NULL ? &DEFAULT_TRANSLATION :
                                            &(trans[i][0])));
                    const SWIFT_Real scales_elem = (scales == NULL ? 1.0 :
                                    (scales[i] == NULL ? 1.0 : scales[i][0]));
#ifdef SWIFT_HIERARCHY
                    const int min_tcount = (min_tcounts == NULL ?
                                        DEFAULT_MIN_TCOUNT : min_tcounts[i]);
#ifdef SWIFT_QSLIM_HIER
                    const SWIFT_Real qslim_tratio = (qslim_tratios == NULL ?
                                    DEFAULT_QSLIM_TRATIO : qslim_tratios[i]);
#endif
#endif
                    if( !stms[i]->Create( vs[0], fs[0], vn[0], fn[0],
                                          *orient_elem, *trans_elem,
                                          scales_elem, fv[0]
#ifdef SWIFT_HIERARCHY
                                          , min_tcount
#ifdef SWIFT_QSLIM_HIER
                                          , qslim_tratio
#endif
#endif
                    ) ) {
                        // SWIFT building hierarchy mesh creation failed
                        delete stms[i];
                        j = -1; // Set failure indicator

                        const int new_obj_id = free_oids.Length() == 0
                                        ? objects.Length() : free_oids.Last();
                        cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                             << new_obj_id << " piece " << i
                             << "): Mesh creation failed -- SWIFT "
                             << "hierarchy" << endl;
                    }
                } else {
                    // Hierarchy is given
                    const SWIFT_Orientation* orient_elem =
                                    (orient == NULL ? NULL : orient[i]);
                    const SWIFT_Translation* trans_elem =
                                    (trans == NULL ? NULL : trans[i]);
                    const SWIFT_Real* scales_elem =
                                    (scales == NULL ? NULL : scales[i]);
                    if( !stms[i]->Create( vs, fs, vn, fn, ln[i],
#ifdef SWIFT_QSLIM_HIER
                                      false, NULL,
#endif
                                      orient_elem, trans_elem, scales_elem, fv )
                    ) {
                        // Hierarchy given mesh creation failed
                        delete stms[i];
                        j = -1; // Set failure indicator

                        const int new_obj_id = free_oids.Length() == 0
                                        ? objects.Length() : free_oids.Last();
                        cerr << "Error (Add_Hierarchical_Pieced_Object'2 obj "
                             << new_obj_id << " piece " << i
                             << "): Mesh creation failed -- application "
                             << "hierarchy" << endl;
                    }
                }
            }

            // Delete the temp arrays
            for( ; k >= 0; k-- ) {
                delete vs[k]; delete fs[k]; delete fv[k];
            }
            delete vs; delete fs; delete vn; delete fn; delete fv;

            if( j != num_levels ) {
                // Failure
                break;
            }

            use_cube[i] = Use_Cube( stms[i], fixed, box_setting,
                                                    cube_aspect_ratio );
        }
    }

    if( i != pn ) {
        // Failure along the way.  Delete everything
        for( j = 0; j < i; j++ ) {
            if( stms[j]->Ref() == 0 ) {
                delete stms[j];
            } else {
                stms[j]->Decrement_Ref();
            }
        }
        delete stms; delete use_cube; delete copy;
        return false;
    }

    SWIFT_Object* cobj = new SWIFT_Object( pn );

    cobj->Initialize( stms, fixed, use_cube, box_enl_rel, box_enl_abs, copy );

    delete stms; delete use_cube; delete copy;

    Initialize_Object_In_Scene( cobj, id );

    return true;
#else
    cerr << "Error: SWIFT must be compiled with SWIFT_HIERARCHY defined for "
         << endl << "       the Add_Hierarchical_Pieced_Object function to be "
         << "used.  See SWIFT_config.h." << endl;
    return false;
#endif
}



///////////////////////////////////////////////////////////////////////////////
// Object Deletion methods
///////////////////////////////////////////////////////////////////////////////

void SWIFT_Scene::Delete_Object( int id )
{
#ifdef SWIFT_DEBUG
    // Check the validity of the id
    if( id < 0 || id >= object_ids.Length() ) {
        cerr << "Error: Object id out of range given to Delete_Object("
             << id << "): " << id << endl;
    } else if( object_ids[id] == -1 ) {
        cerr << "Error: Object with id given to Delete_Object("
             << id << "): already deleted" << endl;
    }
#endif

    int i, j;
    SWIFT_Object* free_obj = objects[object_ids[id]];
    const int np = free_obj->Number_Of_Pieces();

    if( bp ) {
        // Remove the boxes from the sorted lists and compress the lists
        int k;
        SWIFT_Array<SWIFT_Box_Node*> bns[3];
        bns[0].Create( free_obj->Number_Of_Pieces()<<1 );
        bns[1].Create( free_obj->Number_Of_Pieces()<<1 );
        bns[2].Create( free_obj->Number_Of_Pieces()<<1 );
        for( i = 0, j = 0; i < free_obj->Number_Of_Pieces(); i++, j += 2 ) {
            bns[0][j] = free_obj->Min_Box_Node( 0, i );
            bns[0][j+1] = free_obj->Max_Box_Node( 0, i );
            bns[1][j] = free_obj->Min_Box_Node( 1, i );
            bns[1][j+1] = free_obj->Max_Box_Node( 1, i );
            bns[2][j] = free_obj->Min_Box_Node( 2, i );
            bns[2][j+1] = free_obj->Max_Box_Node( 2, i );
        }
        Quicksort( bns[0], 0, bns[0].Length()-1 );
        Quicksort( bns[1], 0, bns[1].Length()-1 );
        Quicksort( bns[2], 0, bns[2].Length()-1 );

        // Remove the boxes from the sorted lists and compress the lists
        for( j = 0; j < 3; j++ ) {
            // Fix the boxes before the first deleted index
            for( i = 0; i < bns[j][0]->Idx(); i++ ) {
                if( sorted[j][i]->Id() > free_obj->Id() ) {
                    sorted[j][i]->Set_Id( sorted[j][i]->Id()-np );
                }
            }
            // Fix the boxes between the deleted indices
            for( k = 1; k < bns[j].Length(); k++ ) {
                for( ; i < bns[j][k]->Idx()-k; i++ ) {
                    sorted[j][i] = sorted[j][i+k];
                    sorted[j][i]->Set_Idx( i );
                    if( sorted[j][i]->Id() > free_obj->Id() ) {
                        sorted[j][i]->Set_Id( sorted[j][i]->Id()-np );
                    }
                }
            }
            // Fix the boxes after the second deleted index
            for( ; i < sorted[j].Length()-k; i++ ) {
                sorted[j][i] = sorted[j][i+k];
                sorted[j][i]->Set_Idx( i );
                if( sorted[j][i]->Id() > free_obj->Id() ) {
                    sorted[j][i]->Set_Id( sorted[j][i]->Id()-np );
                }
            }
            sorted[j].Set_Length( sorted[j].Length() - k );
        }
    }
    
    // Delete from the overlapping pairs list
    Deactivate( id );

    // Decrement the number of pairs in the scene
    total_pairs -= free_obj->Num_Pairs();

    // Compress all the object stuff and renumber internal oids
    for( i = object_ids[id]+1; i < objects.Length(); i++ ) {
        objects[i-1] = objects[i];
        user_object_ids[i-1] = user_object_ids[i];
        object_ids[user_object_ids[i]] = i-1;

        // Find the pair to delete.
        for( j = 0; j < objects[i]->Num_Pairs(); j++ ) {
            if( !objects[i]->Pairs()[j].Deleted() ) {
                // Renumber the pair
                objects[i]->Pairs()[j].Set_Id1(
                                            objects[i]->Pairs()[j].Id1()-np );
                if( objects[i]->Pairs()[j].Id0() == free_obj->Id() ) {
                    objects[i]->Pairs()[j].Delete();
                    j++;
                    break;
                } else if( objects[i]->Pairs()[j].Id0() > free_obj->Id() ) {
                    // Did not find it.  Must have been a pair of fixed objects.
                    break;
                }
            }
        }

        // Renumber the remaining pairs
        for( ; j < objects[i]->Num_Pairs(); j++ ) {
            if( !objects[i]->Pairs()[j].Deleted() ) {
                objects[i]->Pairs()[j].Set_Id0(
                                            objects[i]->Pairs()[j].Id0()-np );
                objects[i]->Pairs()[j].Set_Id1(
                                            objects[i]->Pairs()[j].Id1()-np );
            }
        }

        // Shuffle the piece_ids
        objects[i]->Set_Id( objects[i]->Id() - np );
        for( j = 0; j < objects[i]->Number_Of_Pieces(); j++ ) {
            piece_ids[objects[i]->Id()+j] = piece_ids[objects[i]->Id()+np+j]-1;
        }
    }
    objects.Decrement_Length();
    user_object_ids.Decrement_Length();
    piece_ids.Set_Length( piece_ids.Length() - np );

    // Put the index on the reuse list
    free_oids.Add_Grow( id, 10 );

    // Set the index to invalid
    object_ids[id] = -1;

    // Free up the memory
    delete free_obj;
}

///////////////////////////////////////////////////////////////////////////////
// Object Transformation methods
///////////////////////////////////////////////////////////////////////////////

void SWIFT_Scene::Set_Object_Transformation( int id, const SWIFT_Real* R,
                                                     const SWIFT_Real* T )
{
#ifdef SWIFT_DEBUG
    // Check the validity of the id
    if( id < 0 || id >= object_ids.Length() ) {
        cerr << "Error: Object id out of range given to "
             << "Set_Object_Transformation(" << id << ")" << endl;
    } else if( object_ids[id] == -1 ) {
        cerr << "Error: Object given to Set_Object_Transformation("
             << id << "): already deleted" << endl;
    }
#endif
    if( bp ) {
        objects[object_ids[id]]->Set_Transformation( R, T );
        if( !gs ) {
            int j;
            for( j = 0; j < objects[object_ids[id]]->Number_Of_Pieces(); j++ ) {
                Sort_Local( object_ids[id], j );
            }
        }
    } else {
        objects[object_ids[id]]->Set_Transformation_No_Boxes( R, T );
    }
}

void SWIFT_Scene::Set_Object_Transformation( int id, const SWIFT_Real* R )
{
#ifdef SWIFT_DEBUG
    // Check the validity of the id
    if( id < 0 || id >= object_ids.Length() ) {
        cerr << "Error: Object id out of range given to "
             << "Set_Object_Transformation(" << id << ")" << endl;
    } else if( object_ids[id] == -1 ) {
        cerr << "Error: Object given to Set_Object_Transformation("
             << id << "): already deleted" << endl;
    }
#endif
    if( bp ) {
        objects[object_ids[id]]->Set_Transformation( R );
        if( !gs ) {
            int j;
            for( j = 0; j < objects[object_ids[id]]->Number_Of_Pieces(); j++ ) {
                Sort_Local( object_ids[id], j );
            }
        }
    } else {
        objects[object_ids[id]]->Set_Transformation_No_Boxes( R );
    }
}

void SWIFT_Scene::Set_All_Object_Transformations( const SWIFT_Real* R,
                                                  const SWIFT_Real* T )
{
    int i;
    const SWIFT_Real* Rp = R;
    const SWIFT_Real* Tp = T;

    if( bp ) {
        for( i = 0; i < objects.Length(); i++ ) {
            if( !objects[i]->Fixed() ) {
                objects[i]->Set_Transformation( Rp, Tp );
                Rp += 9; Tp += 3;
            }
        }
        Sort_Global();
    } else {
        for( i = 0; i < objects.Length(); i++ ) {
            if( !objects[i]->Fixed() ) {
                objects[i]->Set_Transformation_No_Boxes( Rp, Tp );
                Rp += 9; Tp += 3;
            }
        }
    }
}

void SWIFT_Scene::Set_All_Object_Transformations( const SWIFT_Real* R )
{
    int i;
    const SWIFT_Real* Rp = R;

    if( bp ) {
        for( i = 0; i < objects.Length(); i++ ) {
            if( !objects[i]->Fixed() ) {
                objects[i]->Set_Transformation( Rp );
                Rp += 12;
            }
        }
        Sort_Global();
    } else {
        for( i = 0; i < objects.Length(); i++ ) {
            if( !objects[i]->Fixed() ) {
                objects[i]->Set_Transformation_No_Boxes( Rp );
                Rp += 12;
            }
        }
    }
}


///////////////////////////////////////////////////////////////////////////////
// Pair Activation methods
///////////////////////////////////////////////////////////////////////////////

void SWIFT_Scene::Activate( int id1, int id2 )
{
#ifdef SWIFT_DEBUG
    if( id1 < 0 || id1 >= object_ids.Length() ) {
        cerr << "Error: out of range object id given to Activate(" << id1
             << "," << id2 << "): " << id1 << endl;
        return;
    } else if( object_ids[id1] == -1 ) {
        cerr << "Error: deleted object id given to Activate(" << id1
             << "," << id2 << "): " << id1 << endl;
        return;
    }
    if( id2 < 0 || id2 >= object_ids.Length() ) {
        cerr << "Error: out of range object id given to Activate(" << id1
             << "," << id2 << "): " << id2 << endl;
        return;
    } else if( object_ids[id2] == -1 ) {
        cerr << "Error: deleted object id given to Activate(" << id1
             << "," << id2 << "): " << id2 << endl;
        return;
    }
    if( id1 == id2 ) {
        cerr << "Warning: object ids equal given to Activate(" << id1
             << "," << id2 << "): Has no effect" << endl;
        return;
    }
#endif

    int j;

    id1 = object_ids[id1];
    id2 = object_ids[id2];

    if( !objects[id1]->Fixed() || !objects[id2]->Fixed() ) {
        if( id1 > id2 ) {
            for( j = 0;
                 objects[id1]->Pairs()[j].Id0() < objects[id2]->Id(); j++ );

            for( ; j < objects[id1]->Num_Pairs() &&
                   //objects[id1]->Pairs()[j].Id0() < objects[id2+1]->Id(); j++
                   objects[id1]->Pairs()[j].Id0() <
                     objects[id2]->Id()+objects[id2]->Number_Of_Pieces(); j++
            ) {
                if( !objects[id1]->Pairs()[j].Deleted() &&
                    objects[id1]->Pairs()[j].Inactive() &&
                    objects[id1]->Pairs()[j].Overlapping()
                ) {
                    // Add it to the overlapping list.
                    objects[id1]->Pairs()[j].Set_Next( overlapping_pairs );
                    objects[id1]->Pairs()[j].Set_Prev( NULL );
                    if( overlapping_pairs != NULL ) {
                        overlapping_pairs->Set_Prev( objects[id1]->Pairs()(j) );
                    }
                    overlapping_pairs = objects[id1]->Pairs()(j);
                }
                objects[id1]->Pairs()[j].Set_Active();
            }
        } else if( id1 < id2 ) {
            for( j = 0;
                 objects[id2]->Pairs()[j].Id0() < objects[id1]->Id(); j++ );

            for( ; j < objects[id2]->Num_Pairs() &&
                   //objects[id2]->Pairs()[j].Id0() < objects[id1+1]->Id(); j++
                   objects[id2]->Pairs()[j].Id0() <
                     objects[id1]->Id()+objects[id1]->Number_Of_Pieces(); j++
            ) {
                if( !objects[id2]->Pairs()[j].Deleted() &&
                    objects[id2]->Pairs()[j].Inactive() &&
                    objects[id2]->Pairs()[j].Overlapping()
                ) {
                    // Add it to the overlapping list.
                    objects[id2]->Pairs()[j].Set_Next( overlapping_pairs );
                    objects[id2]->Pairs()[j].Set_Prev( NULL );
                    if( overlapping_pairs != NULL ) {
                        overlapping_pairs->Set_Prev( objects[id2]->Pairs()(j) );
                    }
                    overlapping_pairs = objects[id2]->Pairs()(j);
                }
                objects[id2]->Pairs()[j].Set_Active();
            }
        }
    }
}

void SWIFT_Scene::Activate( int id )
{
#ifdef SWIFT_DEBUG
    if( id < 0 || id >= object_ids.Length() ) {
        cerr << "Error: out of range object id given to Activate(" << id << ")"
             << endl;
        return;
    } else if( object_ids[id] == -1 ) {
        cerr << "Error: deleted object id given to Activate(" << id << ")"
             << endl;
        return;
    }
#endif

    int j, k;

    id = object_ids[id];

    // Take care of the object's pairs
    for( j = 0; j < objects[id]->Num_Pairs(); j++ ) {
        if( !objects[id]->Pairs()[j].Deleted() &&
            objects[id]->Pairs()[j].Inactive() &&
            objects[id]->Pairs()[j].Overlapping()
        ) {
            // Add it to the overlapping list.
            objects[id]->Pairs()[j].Set_Next( overlapping_pairs );
            objects[id]->Pairs()[j].Set_Prev( NULL );
            if( overlapping_pairs != NULL ) {
                overlapping_pairs->Set_Prev( objects[id]->Pairs()(j) );
            }
            overlapping_pairs = objects[id]->Pairs()(j);
        }
        objects[id]->Pairs()[j].Set_Active();
    }

    // Take care of the pairs of all subsequent objects
    for( k = id+1; k < objects.Length(); k++ ) {
        if( !objects[id]->Fixed() || !objects[k]->Fixed() ) {
            for( j = 0; objects[k]->Pairs()[j].Id0() < objects[id]->Id(); j++ );

            for( ; j < objects[k]->Num_Pairs() &&
                   //objects[k]->Pairs()[j].Id0() < objects[i+1]->Id(); j++
                   objects[k]->Pairs()[j].Id0() <
                     objects[id]->Id()+objects[id]->Number_Of_Pieces(); j++
            ) {
                if( !objects[k]->Pairs()[j].Deleted() &&
                    objects[k]->Pairs()[j].Inactive() &&
                    objects[k]->Pairs()[j].Overlapping()
                ) {
                    // Add it to the overlapping list.
                    objects[k]->Pairs()[j].Set_Next( overlapping_pairs );
                    objects[k]->Pairs()[j].Set_Prev( NULL );
                    if( overlapping_pairs != NULL ) {
                        overlapping_pairs->Set_Prev( objects[k]->Pairs()(j) );
                    }
                    overlapping_pairs = objects[k]->Pairs()(j);
                }
                objects[k]->Pairs()[j].Set_Active();
            }
        }
    }
}

void SWIFT_Scene::Activate( )
{
    int i, j;

    // Start off with an empty overlap list
    overlapping_pairs = NULL;

    for( i = 0; i < objects.Length(); i++ ) {
        for( j = 0; j < objects[i]->Num_Pairs(); j++ ) {
            if( !objects[i]->Pairs()[j].Deleted() ) {
                objects[i]->Pairs()[j].Set_Active();
                if( objects[i]->Pairs()[j].Overlapping() ) {
                    // Add it to the overlapping list.
                    objects[i]->Pairs()[j].Set_Next( overlapping_pairs );
                    objects[i]->Pairs()[j].Set_Prev( NULL );
                    if( overlapping_pairs != NULL ) {
                        overlapping_pairs->Set_Prev( objects[i]->Pairs()(j) );
                    }
                    overlapping_pairs = objects[i]->Pairs()(j);
                }
            }
        }
    }
}

void SWIFT_Scene::Deactivate( int id1, int id2 )
{
#ifdef SWIFT_DEBUG
    if( id1 < 0 || id1 >= object_ids.Length() ) {
        cerr << "Error: out of range object id given to Deactivate(" << id1
             << "," << id2 << "): " << id1 << endl;
        return;
    } else if( object_ids[id1] == -1 ) {
        cerr << "Error: deleted object id given to Deactivate(" << id1
             << "," << id2 << "): " << id1 << endl;
        return;
    }
    if( id2 < 0 || id2 >= object_ids.Length() ) {
        cerr << "Error: out of range object id given to Deactivate(" << id1
             << "," << id2 << "): " << id2 << endl;
        return;
    } else if( object_ids[id2] == -1 ) {
        cerr << "Error: deleted object id given to Deactivate(" << id1
             << "," << id2 << "): " << id2 << endl;
        return;
    }
    if( id1 == id2 ) {
        cerr << "Warning: object ids equal given to Deactivate(" << id1
             << "," << id2 << "): Has no effect" << endl;
        return;
    }
#endif

    int j;

    id1 = object_ids[id1];
    id2 = object_ids[id2];

    if( !objects[id1]->Fixed() || !objects[id2]->Fixed() ) {
        if( id1 > id2 ) {
            for( j = 0;
                 objects[id1]->Pairs()[j].Id0() < objects[id2]->Id(); j++ );

            for( ; j < objects[id1]->Num_Pairs() &&
                   //objects[id1]->Pairs()[j].Id0() < objects[id2+1]->Id(); j++
                   objects[id1]->Pairs()[j].Id0() <
                     objects[id2]->Id()+objects[id2]->Number_Of_Pieces(); j++
            ) {
                objects[id1]->Pairs()[j].Set_Inactive();
            }
        } else if( id1 < id2 ) {
            for( j = 0;
                 objects[id2]->Pairs()[j].Id0() < objects[id1]->Id(); j++ );

            for( ; j < objects[id2]->Num_Pairs() &&
                   //objects[id2]->Pairs()[j].Id0() < objects[id1+1]->Id(); j++
                   objects[id2]->Pairs()[j].Id0() <
                     objects[id1]->Id()+objects[id1]->Number_Of_Pieces(); j++
            ) {
                objects[id2]->Pairs()[j].Set_Inactive();
            }
        }
    }

    // Remove pairs from the overlapping list
    while( overlapping_pairs != NULL &&
           ( (piece_ids[overlapping_pairs->Id0()] == id1 &&
              piece_ids[overlapping_pairs->Id1()] == id2) ||
             (piece_ids[overlapping_pairs->Id0()] == id2 &&
              piece_ids[overlapping_pairs->Id1()] == id1) )
    ) {
        overlapping_pairs = overlapping_pairs->Next();
    }

    if( overlapping_pairs != NULL ) {
        SWIFT_Pair* pair = overlapping_pairs->Next();
        overlapping_pairs->Set_Prev( NULL );
        while( pair != NULL ) {
            if( (piece_ids[pair->Id0()]==id1 && piece_ids[pair->Id1()]==id2) ||
                (piece_ids[pair->Id0()]==id2 && piece_ids[pair->Id1()]==id1)
            ) {
                pair->Prev()->Set_Next( pair->Next() );
                if( pair->Next() != NULL ) {
                    pair->Next()->Set_Prev( pair->Prev() );
                }
            }
            pair = pair->Next();
        }
    }
}

void SWIFT_Scene::Deactivate( int id )
{
#ifdef SWIFT_DEBUG
    if( id < 0 || id >= object_ids.Length() ) {
        cerr << "Error: out of range object id given to Deactivate(" << id
             << ")" << endl;
        return;
    } else if( object_ids[id] == -1 ) {
        cerr << "Error: deleted object id given to Deactivate(" << id << ")"
             << endl;
        return;
    }
#endif

    int j, k;

    id = object_ids[id];

    // Take care of the object's pairs
    for( j = 0; j < objects[id]->Num_Pairs(); j++ ) {
        objects[id]->Pairs()[j].Set_Inactive();
    }

    // Take care of the pairs of all subsequent objects
    for( k = id+1; k < objects.Length(); k++ ) {
        if( !objects[id]->Fixed() || !objects[k]->Fixed() ) {
            for( j = 0; objects[k]->Pairs()[j].Id0() < objects[id]->Id(); j++ );

            for( ; j < objects[k]->Num_Pairs() &&
                   //objects[k]->Pairs()[j].Id0() < objects[id+1]->Id(); j++
                   objects[k]->Pairs()[j].Id0() <
                     objects[id]->Id()+objects[id]->Number_Of_Pieces(); j++
            ) {
                objects[k]->Pairs()[j].Set_Inactive();
            }
        }
    }

    // Remove pairs from the overlapping list
    while( overlapping_pairs != NULL &&
           (piece_ids[overlapping_pairs->Id0()] == id ||
            piece_ids[overlapping_pairs->Id1()] == id)
    ) {
        overlapping_pairs = overlapping_pairs->Next();
    }

    if( overlapping_pairs != NULL ) {
        SWIFT_Pair* pair = overlapping_pairs->Next();
        overlapping_pairs->Set_Prev( NULL );
        while( pair != NULL ) {
            if( piece_ids[pair->Id0()] == id || piece_ids[pair->Id1()] == id ) {
                pair->Prev()->Set_Next( pair->Next() );
                if( pair->Next() != NULL ) {
                    pair->Next()->Set_Prev( pair->Prev() );
                }
            }
            pair = pair->Next();
        }
    }
}

void SWIFT_Scene::Deactivate( )
{
    int i, j;

    for( i = 0; i < objects.Length(); i++ ) {
        for( j = 0; j < objects[i]->Num_Pairs(); j++ ) {
            objects[i]->Pairs()[j].Set_Inactive();
        }
    }

    // No pairs are overlapping
    overlapping_pairs = NULL;
}


///////////////////////////////////////////////////////////////////////////////
// Query methods
///////////////////////////////////////////////////////////////////////////////


bool SWIFT_Scene::Query_Intersection(
                                bool early_exit, int& num_pairs, int** oids )
{
    int i, j, k;
    int o1, o2;
    int p1, p2;

    ois.Ensure_Length( total_pairs<<1 );
    *oids = ois.Data();

    num_pairs = 0;


    if( bp ) {
        if( gs ) {
            // Do global bounding box sort
            Sort_Global();
        }

        SWIFT_Pair* pair = overlapping_pairs;

        k = 0;
        while( pair != NULL ) {
            o1 = piece_ids[ pair->Id0() ];
            p1 = pair->Id0() - objects[o1]->Id();
            o2 = piece_ids[ pair->Id1() ];
            p2 = pair->Id1() - objects[o2]->Id();
            if( pair->Tolerance( objects[o1], objects[o2],
                                 p1, p2,
                                 0.0 )
            ) {
                if( early_exit ) {
                    num_pairs = 0;
                    return true;
                }
                ois[k] = user_object_ids[o1];
                ois[k+1] = user_object_ids[o2];
                k += 2;
            }
            pair = pair->Next();
        }
    } else {
        // Do an all pairs test
        for( i = 1, k = 0; i < objects.Length(); i++ ) {
            // Objects are compressed on deletion so this object valid
            for( j = 0; j < objects[i]->Num_Pairs(); j++ ) {
                if( objects[i]->Pairs()[j].Inactive() ||
                    objects[i]->Pairs()[j].Deleted()
                ) {
                    continue;
                }
                o1 = piece_ids[ objects[i]->Pairs()[j].Id0() ];
                p1 = objects[i]->Pairs()[j].Id0() - objects[o1]->Id();
                o2 = piece_ids[ objects[i]->Pairs()[j].Id1() ];
                p2 = objects[i]->Pairs()[j].Id1() - objects[o2]->Id();
                if( objects[i]->Pairs()[j].Tolerance( objects[o1], objects[o2],
                                                      p1, p2,
                                                      0.0 )
                ) {
                    if( early_exit ) {
                        num_pairs = 0;
                        return true;
                    }
                    ois[k] = user_object_ids[o1];
                    ois[k+1] = user_object_ids[o2];
                    k += 2;
                }
            }
        }
    }


    num_pairs = k>>1;
    return num_pairs != 0;
}




bool SWIFT_Scene::Query_Approximate_Distance(
                    bool early_exit, SWIFT_Real distance_tolerance,
                    SWIFT_Real error_tolerance, int& num_pairs,
                    int** oids, SWIFT_Real** distances, SWIFT_Real** errors )
{
    int i, j, k;
    int o1, o2;
    int p1, p2;
    SWIFT_Real dist, err;
    bool intersection = false;

    ois.Ensure_Length( total_pairs<<1 );
    *oids = ois.Data();

    num_pairs = 0;

    distance_tolerance = distance_tolerance < 0.0 ? 0.0 : distance_tolerance;
    error_tolerance = error_tolerance < 0.0 ? 0.0 : error_tolerance;

    if( bp ) {
        if( gs ) {
            // Do global bounding box sort
            Sort_Global();
        }

        SWIFT_Pair* pair = overlapping_pairs;

        j = 0; k = 0;
        while( pair != NULL ) {
            o1 = piece_ids[ pair->Id0() ];
            p1 = pair->Id0() - objects[o1]->Id();
            o2 = piece_ids[ pair->Id1() ];
            p2 = pair->Id1() - objects[o2]->Id();
            if( pair->Approximate_Distance( objects[o1], objects[o2],
                                            p1, p2, distance_tolerance,
                                            error_tolerance, dist, err )
            ) {
                // There is intersection
                intersection = true;
                if( early_exit ) {
                    // Force the number of reported pairs to be 0
                    k = 0;
                    break;
                }
            }

            if( dist <= distance_tolerance ) {
                // Process all the pairs that met the tolerance.
                // This works even if they are intersecting
                ois[k] = user_object_ids[o1];
                ois[k+1] = user_object_ids[o2];
                ds.Add_Grow( dist, REPORTING_LIST_GROW_SIZE );
                es.Add_Grow( err, REPORTING_LIST_GROW_SIZE );
                k += 2;
            }

            pair = pair->Next();
        }
    } else {
        // Do an all pairs test
        for( i = 1, k = 0; i < objects.Length(); i++ ) {
            // Objects are compressed on deletion so this object valid
            for( j = 0; j < objects[i]->Num_Pairs(); j++ ) {
                if( objects[i]->Pairs()[j].Inactive() ||
                    objects[i]->Pairs()[j].Deleted()
                ) {
                    continue;
                }
                o1 = piece_ids[ objects[i]->Pairs()[j].Id0() ];
                p1 = objects[i]->Pairs()[j].Id0() - objects[o1]->Id();
                o2 = piece_ids[ objects[i]->Pairs()[j].Id1() ];
                p2 = objects[i]->Pairs()[j].Id1() - objects[o2]->Id();
                if( objects[i]->Pairs()[j].Approximate_Distance(
                            objects[o1], objects[o2], p1, p2,
                            distance_tolerance, error_tolerance, dist, err )
                ) {
                    // There is intersection
                    intersection = true;
                    if( early_exit ) {
                        // Force the number of reported pairs to be 0
                        k = 0;
                        break;
                    }
                }

                if( dist <= distance_tolerance ) {
                    // Process all the pairs that met the tolerance.
                    // This works even if they are intersecting
                    ois[k] = user_object_ids[o1];
                    ois[k+1] = user_object_ids[o2];
                    ds.Add_Grow( dist, REPORTING_LIST_GROW_SIZE );
                    es.Add_Grow( err, REPORTING_LIST_GROW_SIZE );
                    k += 2;
                }
            }
            if( intersection && early_exit ) {
                break;
            }
        }
    }

    *distances = ds.Data();
    ds.Set_Length( 0 );
    *errors = es.Data();
    es.Set_Length( 0 );

    num_pairs = k>>1;
    return intersection;
}


bool SWIFT_Scene::Query_Exact_Distance(
                        bool early_exit, SWIFT_Real tolerance, int& num_pairs,
                        int** oids, SWIFT_Real** distances )
{
    int i, j, k;
    int o1, o2;
    int p1, p2;
    SWIFT_Real dist;
    bool intersection = false;

    ois.Ensure_Length( total_pairs<<1 );
    *oids = ois.Data();

    num_pairs = 0;

    tolerance = tolerance < 0.0 ? 0.0 : tolerance;

    if( bp ) {
        if( gs ) {
            // Do global bounding box sort
            Sort_Global();
        }

        SWIFT_Pair* pair = overlapping_pairs;

        j = 0; k = 0;
        while( pair != NULL ) {
            o1 = piece_ids[ pair->Id0() ];
            p1 = pair->Id0() - objects[o1]->Id();
            o2 = piece_ids[ pair->Id1() ];
            p2 = pair->Id1() - objects[o2]->Id();
            if( pair->Distance( objects[o1], objects[o2],
                                p1, p2,
                                tolerance,
                                dist )
            ) {
                // There is intersection
                intersection = true;
                if( early_exit ) {
                    // Force the number of reported pairs to be 0
                    k = 0;
                    break;
                }
            }

            if( dist <= tolerance ) {
                // Process all the pairs that met the tolerance.
                // This works even if they are intersecting
                ois[k] = user_object_ids[o1];
                ois[k+1] = user_object_ids[o2];
                ds.Add_Grow( dist, REPORTING_LIST_GROW_SIZE );
                k += 2;
            }

            pair = pair->Next();
        }
    } else {
        // Do an all pairs test
        for( i = 1, k = 0; i < objects.Length(); i++ ) {
            // Objects are compressed on deletion so this object valid
            for( j = 0; j < objects[i]->Num_Pairs(); j++ ) {
                if( objects[i]->Pairs()[j].Inactive() ||
                    objects[i]->Pairs()[j].Deleted()
                ) {
                    continue;
                }
                o1 = piece_ids[ objects[i]->Pairs()[j].Id0() ];
                p1 = objects[i]->Pairs()[j].Id0() - objects[o1]->Id();
                o2 = piece_ids[ objects[i]->Pairs()[j].Id1() ];
                p2 = objects[i]->Pairs()[j].Id1() - objects[o2]->Id();
                if( objects[i]->Pairs()[j].Distance( objects[o1], objects[o2],
                        p1, p2,
                        tolerance,
                        dist )
                ) {
                    // There is intersection
                    intersection = true;
                    if( early_exit ) {
                        // Force the number of reported pairs to be 0
                        k = 0;
                        break;
                    }
                }

                if( dist <= tolerance ) {
                    // Process all the pairs that met the tolerance.
                    // This works even if they are intersecting
                    ois[k] = user_object_ids[o1];
                    ois[k+1] = user_object_ids[o2];
                    ds.Add_Grow( dist, REPORTING_LIST_GROW_SIZE );
                    k += 2;
                }
            }
            if( intersection && early_exit ) {
                break;
            }
        }
    }

    *distances = ds.Data();
    ds.Set_Length( 0 );

    num_pairs = k>>1;
    return intersection;
}


bool SWIFT_Scene::Query_Contact_Determination(
        bool early_exit, SWIFT_Real tolerance, int& num_pairs, int** oids,
        SWIFT_Real** distances, SWIFT_Real** nearest_pts, SWIFT_Real** normals,
        int** pids, int** feature_types, int** feature_ids )
{
    int i, j, k;
    int o1, o2;
    int p1, p2;
    int num_cs;
    SWIFT_Real dist;
    bool intersection = false;

    ois.Ensure_Length( total_pairs<<1 );
    *oids = ois.Data();


    num_pairs = 0;

    tolerance = tolerance < 0.0 ? 0.0 : tolerance;

    if( bp ) {
        if( gs ) {
            // Do global bounding box sort
            Sort_Global();
        }

        SWIFT_Pair* pair = overlapping_pairs;

        k = 0;
        while( pair != NULL ) {
            o1 = piece_ids[ pair->Id0() ];
            p1 = pair->Id0() - objects[o1]->Id();
            o2 = piece_ids[ pair->Id1() ];
            p2 = pair->Id1() - objects[o2]->Id();
            if( pair->Contacts( objects[o1], objects[o2],
                                p1, p2,
                                tolerance, dist, num_cs )
            ) {
                // There is intersection
                intersection = true;
                if( early_exit ) {
                    // Force the number of reported pairs to be 0
                    k = 0;
                    break;
                }
            }

            if( dist <= tolerance ) {
                // Process all the contacts that met the tolerance.
                // This works even if they are intersecting
                ois[k] = user_object_ids[o1];
                ois[k+1] = user_object_ids[o2];

                if( distances != NULL ) {
                    ds.Fit_Grow( 1, REPORTING_LIST_GROW_SIZE );
                    ds.Add( dist );
                }
                if( nearest_pts != NULL ) {
                    nps.Fit_Grow( 6, REPORTING_LIST_GROW_SIZE*6 );
                    pair->Contact_Points( nps );
                }
                if( normals != NULL ) {
                    cns.Fit_Grow( 3, REPORTING_LIST_GROW_SIZE*3 );
                    pair->Contact_Normals( cns );
                }
                if( pids != NULL && feature_types != NULL &&
                    feature_ids != NULL
                ) {
                    pis.Fit_Grow( 2, REPORTING_LIST_GROW_SIZE<<1 );
                    fts.Fit_Grow( 2, REPORTING_LIST_GROW_SIZE<<1 );
                    fis.Fit_Grow( 4, REPORTING_LIST_GROW_SIZE<<2 );
                    pair->Contact_Features( pis, fts, fis );
                }
                k += 2;
            }

            pair = pair->Next();
        }
    } else {
        // Do an all pairs test
        for( i = 1, k = 0; i < objects.Length(); i++ ) {
            // Objects are compressed on deletion so this object valid
            for( j = 0; j < objects[i]->Num_Pairs(); j++ ) {
                if( objects[i]->Pairs()[j].Inactive() ||
                    objects[i]->Pairs()[j].Deleted()
                ) {
                    continue;
                }
                o1 = piece_ids[ objects[i]->Pairs()[j].Id0() ];
                p1 = objects[i]->Pairs()[j].Id0() - objects[o1]->Id();
                o2 = piece_ids[ objects[i]->Pairs()[j].Id1() ];
                p2 = objects[i]->Pairs()[j].Id1() - objects[o2]->Id();
                if( objects[i]->Pairs()[j].Contacts( objects[o1], objects[o2],
                                                     p1, p2,
                                                     tolerance, dist, num_cs )
                ) {
                    // There is intersection
                    intersection = true;
                    if( early_exit ) {
                        // Force the number of reported pairs to be 0
                        k = 0;
                        break;
                    }
                }

                if( dist <= tolerance ) { 
                    // Process all the contacts that met the tolerance.
                    // This works even if they are intersecting
                    ois[k] = user_object_ids[o1];
                    ois[k+1] = user_object_ids[o2];

                    if( distances != NULL ) {
                        ds.Fit_Grow( 1, REPORTING_LIST_GROW_SIZE );
                        ds.Add( dist );
                    }
                    if( nearest_pts != NULL ) {
                        nps.Fit_Grow( 6, REPORTING_LIST_GROW_SIZE*6 );
                        objects[i]->Pairs()[j].Contact_Points( nps );
                    }
                    if( normals != NULL ) {
                        cns.Fit_Grow( 3, REPORTING_LIST_GROW_SIZE*3 );
                        objects[i]->Pairs()[j].Contact_Normals( cns );
                    }
                    if( pids != NULL && feature_types != NULL &&
                        feature_ids != NULL
                    ) {
                        pis.Fit_Grow( 2, REPORTING_LIST_GROW_SIZE<<1 );
                        fts.Fit_Grow( 2, REPORTING_LIST_GROW_SIZE<<1 );
                        fis.Fit_Grow( 4, REPORTING_LIST_GROW_SIZE<<2 );
                        objects[i]->Pairs()[j].Contact_Features( pis, fts, fis );
                    }
                    k += 2;
                }
            }
            if( intersection && early_exit ) {
                break;
            }
        }
    }

    if( distances != NULL ) {
        *distances = ds.Data();
        ds.Set_Length( 0 );
    }
    if( nearest_pts != NULL ) {
        *nearest_pts = nps.Data();
        nps.Set_Length( 0 );
    }
    if( normals != NULL ) {
        *normals = cns.Data();
        cns.Set_Length( 0 );
    }
    if( pids != NULL && feature_types != NULL && feature_ids != NULL ) {
        *pids = pis.Data();
        pis.Set_Length( 0 );
        *feature_types = fts.Data();
        *feature_ids = fis.Data();
        fts.Set_Length( 0 );
        fis.Set_Length( 0 );
    }

    num_pairs = k>>1;
    return intersection;
}


///////////////////////////////////////////////////////////////////////////////
// Plug-In Registration methods
///////////////////////////////////////////////////////////////////////////////

bool SWIFT_Scene::Register_File_Reader( const char* magic_number,
                                        SWIFT_File_Reader* file_reader ) const
{
    return file_dispatcher.Register( magic_number, file_reader );
}

//////////////////////////////////////////////////////////////////////////////
// Private functions
//////////////////////////////////////////////////////////////////////////////

void SWIFT_Scene::Initialize_Object_In_Scene( SWIFT_Object* cobj, int& id )
{
    int i, j, k, l;

    if( piece_ids.Max_Length() - piece_ids.Length() < cobj->Number_Of_Pieces()
    ) {
        piece_ids.Grow( max(OBJECT_SEGMENT_SIZE, cobj->Number_Of_Pieces()) );
        if( bp ) {
            sorted[0].Grow(
                (max(OBJECT_SEGMENT_SIZE, cobj->Number_Of_Pieces()))<<1 );
            sorted[1].Grow(
                (max(OBJECT_SEGMENT_SIZE, cobj->Number_Of_Pieces()))<<1 );
            sorted[2].Grow(
                (max(OBJECT_SEGMENT_SIZE, cobj->Number_Of_Pieces()))<<1 );
        }
    }
    cobj->Set_Id( piece_ids.Length() );

    // Assign the piece_ids mapping
    piece_ids.Set_Length( piece_ids.Length() + cobj->Number_Of_Pieces() );
    for( i = piece_ids.Length() - cobj->Number_Of_Pieces();
         i < piece_ids.Length(); i++
    ) {
        piece_ids[i] = objects.Length();
    }

    if( free_oids.Length() == 0 ) {
        // Need a new id
        id = objects.Length();
        if( objects.Max_Length() == objects.Length() ) {
            // Object list is full.  Grow it.
            objects.Grow( OBJECT_SEGMENT_SIZE );
            object_ids.Grow( OBJECT_SEGMENT_SIZE );
            user_object_ids.Grow( OBJECT_SEGMENT_SIZE );
        }
        object_ids.Increment_Length();
    } else {
        // Reuse one of the free ids
        id = free_oids.Last();
        free_oids.Decrement_Length();
    }
    object_ids[id] = objects.Length();
    objects.Increment_Length();
    objects.Last() = cobj;
    user_object_ids.Increment_Length();
    user_object_ids.Last() = id;

    // Count up the pairs
    for( i = 0, j = 0; i < objects.Length()-1; i++ ) {
        if( !cobj->Fixed() || !objects[i]->Fixed() ) {
            j += cobj->Number_Of_Pieces() * objects[i]->Number_Of_Pieces();
        }
    }
    total_pairs += j;
    cobj->Pairs().Create( j );

    // Set up the pairs for this object
    for( i = 0, l = 0; i < objects.Length()-1; i++ ) {
        if( !cobj->Fixed() || !objects[i]->Fixed() ) {
            for( k = 0; k < objects[i]->Number_Of_Pieces(); k++ ) {
                for( j = 0; j < cobj->Number_Of_Pieces(); j++ ) {
                    cobj->Pairs()[l].Set_Id0( objects[i]->Id() + k );
                    cobj->Pairs()[l++].Set_Id1( cobj->Id() + j );
                }
            }
        }
    }

    if( bp ) {
        // Set the box nodes and initialize them in the sorted list
        j = sorted[0].Length();
        k = j+1;
        i = 0;
        for( ; i < cobj->Number_Of_Pieces(); i++, j += 2, k += 2 ) {
            sorted[0].Increment_Length();
            sorted[0].Increment_Length();
            sorted[1].Increment_Length();
            sorted[1].Increment_Length();
            sorted[2].Increment_Length();
            sorted[2].Increment_Length();
            cobj->Get_Box_Nodes( i, &(sorted[0][j]), &(sorted[0][k]),
                                    &(sorted[1][j]), &(sorted[1][k]),
                                    &(sorted[2][j]), &(sorted[2][k]) );
            sorted[0][j]->Set_Idx( j );
            sorted[0][k]->Set_Idx( k );
            sorted[1][j]->Set_Idx( j );
            sorted[1][k]->Set_Idx( k );
            sorted[2][j]->Set_Idx( j );
            sorted[2][k]->Set_Idx( k );
            Sort_Local( objects.Length()-1, i );
        }
    }
}

inline void SWIFT_Scene::Update_Overlap( int axis, int id1, int id2 )
{
    int j;
    SWIFT_Pair* pair;
    bool poverlapping;
    const int oid1 = piece_ids[id1];
    const int oid2 = piece_ids[id2];

    // Check to see if a pair exists for the two ids
    if( oid1 == oid2 || (objects[oid1]->Fixed() && objects[oid2]->Fixed()) ) {
        return;
    }

    // Find the pair
    if( oid1 > oid2 ) {
        for( j = id1 - objects[oid1]->Id();
             objects[oid1]->Pairs()[j].Id0() != id2;
             j += objects[oid1]->Number_Of_Pieces() );

        pair = objects[oid1]->Pairs()( j );
    } else {
        for( j = id2 - objects[oid2]->Id();
             objects[oid2]->Pairs()[j].Id0() != id1;
             j += objects[oid2]->Number_Of_Pieces() );

        pair = objects[oid2]->Pairs()( j );
    }

    poverlapping = pair->Active() && pair->Overlapping();

    // Potentially changes the Overlapping() status of the pair
    pair->Toggle_Overlap( axis );

    if( poverlapping ) {
        // Pair is done overlapping. Remove it from the overlapping pairs list.
        if( pair->Next() != NULL ) {
            pair->Next()->Set_Prev( pair->Prev() );
        }
        if( pair->Prev() != NULL ) {
            pair->Prev()->Set_Next( pair->Next() );
        } else {
            overlapping_pairs = pair->Next();
        }
        // Set it uninitialized
        pair->Set_Uninitialized();
    } else if( pair->Active() && pair->Overlapping() ) {
        // The pair is starting to overlap.  Add it to the overlapping list.
        pair->Set_Next( overlapping_pairs );
        pair->Set_Prev( NULL );
        if( overlapping_pairs != NULL ) {
            overlapping_pairs->Set_Prev( pair );
        }
        overlapping_pairs = pair;
    }
}

inline void SWIFT_Scene::Sort_Global( int axis )
{
    int i, j;
    SWIFT_Box_Node* tempc;

    // Do insertion sort on the list.
    for( i = 1; i < sorted[axis].Length(); i++ ) {
        tempc = sorted[axis][i];
        for( j = i; j > 0 && tempc->Value() < sorted[axis][j-1]->Value(); j--
        ) {
            sorted[axis][j] = sorted[axis][j-1];
            sorted[axis][j]->Set_Idx( j );
            if( tempc->Is_Max() != sorted[axis][j]->Is_Max() ) {
                Update_Overlap( axis, tempc->Id(), sorted[axis][j]->Id() );
            }
        }
        sorted[axis][j] = tempc;
        tempc->Set_Idx( j );
    }
}

void SWIFT_Scene::Sort_Global( )
{
    int i;
    for( i = 0; i < 3; i++ ) {
        Sort_Global( i );
    }
}

inline void SWIFT_Scene::Sort_Local( int oid, int pid, int axis )
{
    SWIFT_Box_Node* bn;
    int i;

    // Try to move the min to the left
    bn = objects[oid]->Min_Box_Node( axis, pid );
    i = bn->Idx();
    for( ; i != 0 && sorted[axis][i-1]->Value() > bn->Value(); i-- ) {
        sorted[axis][i] = sorted[axis][i-1];
        sorted[axis][i]->Set_Idx( i );
        if( sorted[axis][i]->Is_Max() ) {
            Update_Overlap( axis, bn->Id(), sorted[axis][i]->Id() );
        }
    }

    sorted[axis][i] = bn;
    bn->Set_Idx( i );

    // Try to move the max to the right
    bn = objects[oid]->Max_Box_Node( axis, pid );
    i = bn->Idx();
    for( ; i != sorted[axis].Length()-1 &&
           sorted[axis][i+1]->Value() < bn->Value(); i++
    ) {
        sorted[axis][i] = sorted[axis][i+1];
        sorted[axis][i]->Set_Idx( i );
        if( !sorted[axis][i]->Is_Max() ) {
            Update_Overlap( axis, bn->Id(), sorted[axis][i]->Id() );
        }
    }

    sorted[axis][i] = bn;
    bn->Set_Idx( i );

    // Try to move the min to the right
    bn = objects[oid]->Min_Box_Node( axis, pid );
    i = bn->Idx();
    for( ; sorted[axis][i+1]->Value() < bn->Value(); i++ ) {
        sorted[axis][i] = sorted[axis][i+1];
        sorted[axis][i]->Set_Idx( i );
        if( sorted[axis][i]->Is_Max() ) {
            Update_Overlap( axis, bn->Id(), sorted[axis][i]->Id() );
        }
    }

    sorted[axis][i] = bn;
    bn->Set_Idx( i );

    // Try to move the max to the left
    bn = objects[oid]->Max_Box_Node( axis, pid );
    i = bn->Idx();
    for( ; sorted[axis][i-1]->Value() > bn->Value(); i-- ) {
        sorted[axis][i] = sorted[axis][i-1];
        sorted[axis][i]->Set_Idx( i );
        if( !sorted[axis][i]->Is_Max() ) {
            Update_Overlap( axis, bn->Id(), sorted[axis][i]->Id() );
        }
    }

    sorted[axis][i] = bn;
    bn->Set_Idx( i );
}

void SWIFT_Scene::Sort_Local( int oid, int pid )
{
    int i;
    for( i = 0; i < 3; i++ ) {
        Sort_Local( oid, pid, i );
    }
}

void SWIFT_Scene::Quicksort( SWIFT_Array<SWIFT_Box_Node*>& bs, int p, int r )
{
    if( p < r ) {
        // Compute a random element to use as the pivot
        int rn = (int) ((SWIFT_Real)(r-p+1) * drand48()) + p;
        int i = p-1;
        int j = r+1;
        SWIFT_Box_Node* x = bs[rn];
        SWIFT_Box_Node* tb;

        // Swap the random element into the first position
        bs[rn] = bs[p];
        bs[p] = x;

        while( true ) {
            j--;
            while( bs[j]->Idx() > x->Idx() ) {
                j--;
            }
            i++;
            while( bs[i]->Idx() < x->Idx() ) {
                i++;
            }
            if( i < j ) {
                tb = bs[i];
                bs[i] = bs[j];
                bs[j] = tb;
            } else {
                break;
            }
        }

        Quicksort( bs, p, j );
        Quicksort( bs, j+1, r );
    }
}


