
MPFUN2015: A thread-safe arbitrary precision package
MPFUN-Fort version

Revision date: 27 Sep 2021

AUTHOR:
David H. Bailey
Lawrence Berkeley National Lab (retired) and University of California, Davis
Email: dhbailey@lbl.gov
 
COPYRIGHT AND DISCLAIMER:
All software in this package (c) 2021 David H. Bailey. By downloading or using this software you agree to the copyright, disclaimer and license agreement in the accompanying file DISCLAIMER.txt.

*** NOTE: This package is being phased out, in favor of the more recent MPFUN2020 package from the same author and website. It will continue to be supported for the time being, however.


I. PURPOSE OF PACKAGE:

This system permits one to perform floating-point computations (real and complex) to arbitrarily high numeric precision, by making only relatively minor changes to existing Fortran-90 programs. All basic arithmetic operations and transcendental functions are supported, together with numerous special functions.

One key feature of this package is a 100% THREAD-SAFE design, which means that user-level applications can be easily converted for parallel execution, say by using a threaded parallel environment such as OpenMP. There are no global shared variables (except static compile-time data), and no initialization is necessary unless extremely high precision is required.

This is an all-Fortran version based on floating-point arithmetic. It compiles in just a few seconds on any system with a Fortran-2003 compliant compiler (examples include the GNU gfortran compiler and the Intel ifort compiler).

The newer MPFUN20-Fort and the MPFUN-MPFR versions are now included in the MPFUN2020 package, available from the same site as MPFUN-Fort.


II. DOCUMENTATION:

A detailed description of this software, with instructions for writing Fortran code to use the package, is available in this technical paper:
 
David H. Bailey, "MPFUN2015: A thread-safe arbitrary precision package," 
http://www.davidhbailey.com/dhbpapers/mpfun2015.pdf


III. INSTALLING COMPILERS:

Installation, compilation and linking is relatively straightforward, provided that one has a Unix-based system, such as Linux or Apple OSX, and a Fortran-2003 or higher compiler.

For Apple OSX systems (highly recommended for MPFUN-Fort), first install the latest supported version of XCode, which is available for free from the App Store or from the Apple Developer website:
      https://developer.apple.com/
Here click on Account, then enter your Apple ID and password, then go to 
      https://developer.apple.com/download/more/
On this list, find and download the most recent version of Xcode that is NOT listed as "beta" or "Release Candidate". Install the downloaded package on your system, and place the resulting Xcode app in the Applications folder. Double-click to run Xcode, allowing it install some "additional components", then quit Xcode. Then open a terminal window, using the Terminal application in the Utilities folder, and you should be ready to continue with the installation.

The gfortran compiler (highly recommended for MPFUN-Fort) is available for a variety of systems at this website:
      https://gcc.gnu.org/wiki/GFortranBinaries
A download file for Apple OSX systems is here:
      https://github.com/fxcoudert/gfortran-for-macOS/releases
On an Apple OSX system, when one attempts to install gfortran, one will likely see the message "gfortran.pkg can't be opened because it is from an unidentified developer". If so, open the "System Preferences" on the Mac, then click on "Security & Privacy", and then click "Open anyway".

The gfortran compiler is normally placed in /usr/local/lib and /usr/local/bin. Thus before one uses gfortran, one must insert a line in one's shell initialization file (if the Z shell is used, as on most Apple OS X systems, the shell initialization file is ~/.zshrc). The line to be included is:

PATH=/usr/local/lib:/usr/local/bin:$PATH

The following line is also recommended for gfortran compiler users:

GFORTRAN_UNBUFFERED_ALL=yes; export GFORTRAN_UNBUFFERED_ALL

The following line is recommended for inclusion in the shell initialization file, no matter what compiler is used (it prevents stack overflow system errors):

ulimit -s unlimited

On most Unix systems (including Apple OS X systems), the shell initialization file must be manually executed upon initiating a shell or after any edits, typically by typing "source .zshrc" or the like.

The MPFUN-Fort software has been tested on:

1. gfortran compiler, version 10.2.0, on a Mac OS X system, version 11.3.1 and an Intel Core i5 processor.
2. Intel ifort compiler, version 2021.2.0, on a Debian Linux system, version 4.19.152-1 and an Intel processor.


IV. DOWNLOADING MPFUN-Fort:

From the website http://www.davidhbailey.com/dhbsoftware, download the file "mpfun-fort-vnn.tar.gz" (replace "vnn" by whatever is the current version number on the website, such as "v22"). If the file is not decompressed by your browser, use gunzip at the shell level to do this. Some browsers (such as the Apple OSX Safari browser) do not drop the ".gz" suffix after decompression; if so, remove this suffix manually at the shell level. Then type
  tar xfv mpfun-fort-vnn.tar
(where again "vnn" is replaced by whatever is the current version number, such as "v22"). This should create the directory and unpack all files.


V. INSTALLING MPFUN-MPFR (not needed for MPFUN-Fort)

VI. COMPILING MPFUN-Fort:

The MPFUN-Fort software comes in four variants::

Variant 1: This is recommended for basic applications that do not dynamically change the precision level (or do so only rarely).

Variant 2: This is recommended for more sophisticated applications that dynamically change the precision level.

Variant Q1: This is the same as Variant 1, except that it includes limited support for the real(16) "quad" datatype (provided it is supported by the compiler).

Variant Q2: This is the same as Variant 2, except that it includes limited support for the real(16) "quad" datatype (provided it is supported by the compiler).

See documentation for additional details on the differences between these four variants.

Compile/link scripts are available in the fortran directory for the gfortran and Intel ifort compilers. These scripts automatically select the proper variant files from the package for compilation. For example, to compile Variant 1 of the MPFUN-Fort library using the GNU gfortran compiler, go to the fortran directory and type
  ./gnu-complib1.scr

NOTE: The first time you compile the library, you may see numerous error messages. This is normal -- just repeat the library compile script. The compile script actually invokes the compiler twice for this reason.

Then to compile and link the application program tpslq1.f90 for variant 1, using the GNU gfortran compiler, producing the executable file tpslq1, type
  ./gnu-complink1.scr tpslq1

To execute the program, with output to tpslq1.txt, type
  ./tpslq1 > tpslq1.txt

These scripts assume that the user program is in the same directory as the library files; this can easily be changed by editing the script files.

Several sample test programs are included in the fortran directory of the packages, together with output files -- see Section VIII below.


VII. BRIEF SUMMARY OF CODING INSTRUCTIONS AND USAGE:

What follows is a brief summary of Fortran coding instructions. For full details, see:

David H. Bailey, "MPFUN2015: A thread-safe arbitrary precision package," 
http://www.davidhbailey.com/dhbpapers/mpfun2015.pdf

First set the parameter mpipl, the default standard precision level in digits, which is the maximum precision level to be used for subsequent computation, and is used to specify the amount of storage required for multiprecision data. mpipl is set in a parameter statement in file mpfunf.f90 in the fortran directory of the software. In the code as distributed, mpipl is set to 2500 digits (sufficient to run each of the test programs), but it can be set to any level greater than 50 digits. mpipl is automatically converted to mantissa words by the formula 
  mpwds = int (mpipl / mpdpw + 2)
where mpdpw is a system parameter set in file mpfuna.f90. The resulting parameter mpwds is the internal default precision level, in words. All subsequent computations are performed to mpwds precision unless the user, within an application code, specifies a lower precision.

After setting the value of mpipl, compile the library, using one of the scripts mentioned above (e.g., gnu-complib1.scr if using the GNU gfortran compiler or intel-complib1.scr if using the Intel compiler).

Next, place the following line in every subprogram of the user's application code that contains a multiprecision variable or array, at the beginning of the declaration section, before any implicit or type statements:

  use mpmodule

To designate a variable or array as multiprecision real (MPR) in an application code, use the Fortran-90 type statement with the type "mp_real", as in this example:

  type (mp_real) a, b(m), c(m,n)

Similarly, to designate a variable or array as multiprecision complex (MPC), use a type statement with "mp_complex".

Thereafter when one of these variables or arrays appears in code, e.g.,

  d = a + b(i) * sqrt(3.d0 - c(i,j))

the proper multiprecision routines are automatically called by the Fortran compiler.

Most common mixed-mode combinations (arithmetic operations, comparisons and assignments) involving MPR, MPC, double precision (DP) and integer arguments are supported, although restrictions apply if one uses Variant 2 of the MPFUN-Fort software. A complete list of supported mixed-mode operations is given in the documentation paper.

Users should be aware, however, that there are some hazards in this type of programming, inherent in conventions adopted by all Fortran compilers. For example, the code

  r1 = 3.14159d0

where r1 is MPR, does NOT produce the true multiprecision equivalent of 3.14159. In fact, the software will flag such usage with a run-time error. To obtain the full MPR converted value, write this as

r1 = "3.14159d0"

instead. Similarly, the code

  r2 = r1 + 3.d0 * sqrt (2.d0)

where r1 and r2 are MPR, does NOT produce the true multiprecision value one might expect, since the expression 3.d0 * sqrt (2.d0) will be performed in double precision, according to Fortran-90 precedence rules. In fact, the above line of code will result in a run-time error. To obtain the fully accurate result, write this as

  r2 = r1 + 3.d0 * sqrt (mpreal (2.q0))

See documentation for details.

Input and output of MPR and MPC data are performed using the subroutines mpread and mpwrite. For example, to output the variable r2 to Fortran unit 6 (standard output), to 100-digit accuracy, in a field of width 120 characters, use the line of code

  call mpwrite (6, 120, 100, r2)

For mpwrite, the second argument (120 in the above example) must be at least 20 larger than the third argument (100 in the above example). See documentation for details.

Most Fortran-2008 intrinsic functions are supported with MPR and MPC arguments, as appropriate. A complete list of supported functions and subroutines is given in the documentation paper. 


VIII. SAMPLE APPLICATION PROGRAMS:

The current release of the software includes a set of sample application programs in the fortran directory:

testmpfun.f90    Tests most arithmetic and transcendental functions.

tpslq1.f90       Performs the standard 1-level PSLQ integer relation algorithm.

tpslqm1.f90      Performs the 1-level multipair PSLQ integer relation algorithm.

tpslqm2.f90      Performs the 2-level multipair PSLQ integer relation algorithm.

tpslqm3.f90      Performs the 3-level multipair PSLQ integer relation algorithm.

tpphix3.f90      Performs a Poisson polynomial application, using 3-level multipair PSLQ.

tquad.f90        Evaluates a set of definite integrals, using tanh-sinh, exp-sinh and sinh-sinh algorithms.

tquadgs.f90      Evaluates a set of definite integrals, using Gaussian quadrature.

In addition, the fortran directory includes test scripts that compile the library and run each of the above sample programs above (except tquadgs.f90, which takes considerably more run time). The test scripts are gnu-mpfun-tests1.scr and intel-mpfun-tests1.scr. For each test program, the script outputs either "TEST PASSED" or "TEST FAILED". If all tests pass, then one can be fairly confident that the MPFUN2015 software and underlying compilers are working properly. Full descriptions of these application programs are included in the documentation paper:

David H. Bailey, "MPFUN2015: A thread-safe arbitrary precision package," 
http://www.davidhbailey.com/dhbpapers/mpfun2015.pdf




