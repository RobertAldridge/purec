Ok, so here it is, my de Boor algorithm implementation!

I put in at least 80hrs on this one, I actually kept a log!

I reimplemented the iterator ( after listening to your comments during the demo ) to allow the user to change the amount of iterations per frame using + and -. It now defaults to showing all the shells every frame for at least cubics, plus more of the curve is generated on the first frame and every frame.

It features a variation of the subdivision algorithm, as well as 2D transformations using 3D homogeneous matrix math ( actually, I don't use any matrices, since I pre-computed the matrices for translation, scaling, and rotation, I just hard-coded them in ).

Run archive.exe, it is a self-extracting archive, containing all the related code and all files needed to rebuild and run the program de_Boor.exe.

There is no README text file for help on how to run the program ( just this README ), but there is a help menu in the program that will show you how it works.  The help menus currently don't let you edit the curve while viewing them, but the *Box.exe programs can be run cuncurrently with the de Boor program instead.  I fixed this problem, but I lost the code that I wrote that did it, and could not reproduce it in time for the last version of the program.

Everything of relevance is in deBoor.cpp.  It contains lots of comments, but still looks like gobbledy-gook.

The files
         asciiWhite.bmp,
         deBoorAboutBox.exe,
         deBoorHelpBox.exe,
         and deBoorExtraBox.exe
         need to be in the same folder as the executable when running it outside of Microsoft Visual C++.

To re-build the project, open up the existing de_Boor.dsw workspace, or to do it yourself, you need the files:

listObject.h
font.h
list.h
resource.h
particle.h
deBoor.cpp
winmain.cpp
aboutBox.rc

and you will need to link to ddraw.lib and my 3 libraries:

font_small.lib
list_adt.lib
particle_adt.lib
