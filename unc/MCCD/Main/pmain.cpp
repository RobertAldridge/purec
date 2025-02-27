/*************************************************************************\

  Copyright 2012 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
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

  US Mail:       GAMMA Research Group at UNC
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of N. Carolina
                       Chapel Hill, NC 27599-3175

  Phone:            (919)962-1749

  EMail:              geom@cs.unc.edu; tang_m@zju.edu.cn


\**************************************************************************/

// Author: Tang, Min tang_m@zju.edu.cn

#include "logger.h"
Logger *logger;

char DATA_PATH[512];
int NUM_FRAME;

float MODEL_SCALE = 1.f;
float DISP_SCALE = 1.f;
int SLICES = 5;
int START_FRAME=0;//320;
bool CCD = true;

bool initParams(int argc, char **argv)
{
	FILE *fp = NULL;

	if (argc == 2)
		fp = fopen(argv[1], "rt");
	else
		fp = fopen("params.txt", "rt");

	if (fp == NULL) {
		fp = fopen("../params.txt", "rt");
		if (fp == NULL) // try upper directory
			return false;
	}

	char buffer[512];
	do {
	if (!fgets(buffer, 512, fp)) return false;
	} while (strlen(buffer) == 1 || buffer[0] == '#');

	strncpy(DATA_PATH, buffer, 512);
	DATA_PATH[strlen(DATA_PATH)-1] = 0; // skip the ending '\n'

	do {
	if (!fgets(buffer, 512, fp)) return false;
	} while (strlen(buffer) == 1 || buffer[0] == '#');

	int num = sscanf(buffer, "%d %f %f %d", &NUM_FRAME, &MODEL_SCALE, &DISP_SCALE, &SLICES);
	if (num < 1) {
		return false;
	}

	fclose(fp);
	return true;
}

static int s_count = 0;
extern void dynamicModel(int t, int start, int circle, bool refit, bool ccd, bool obb);
extern void initModel(char *, int, float, bool ccd);

void endCapture()
{
	NULL;
}

int main(int argc, char **argv)
{
	if (!initParams(argc, argv)) {
		printf("Usage: %s param_file\n", argv[0]);
		exit(0);
	}
	
	initModel(DATA_PATH, NUM_FRAME, MODEL_SCALE, CCD);

	while (1) {
		dynamicModel(s_count++, START_FRAME, SLICES, true, CCD, false);
	}

	return 0;
}
