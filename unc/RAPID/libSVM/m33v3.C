#include "m33.H"
#include "v3.H"
#include "m33v3.H"
#include <string.h>
#include <strings.h>
#include <stdlib.h>

v3
operator*(const m33 &ma, const v3 &va)
{
  v3 vb;
  
  vb.v[0] = ma.m[0][0] * va.v[0] + ma.m[0][1] * va.v[1] + ma.m[0][2] * va.v[2];
  vb.v[1] = ma.m[1][0] * va.v[0] + ma.m[1][1] * va.v[1] + ma.m[1][2] * va.v[2];
  vb.v[2] = ma.m[2][0] * va.v[0] + ma.m[2][1] * va.v[1] + ma.m[2][2] * va.v[2];
  
  return vb;
}

v3 
solve_system(const m33 &A, const v3 &b)
{
  // basic application of Kramer's rule.  This is probably unstable or 
  // something, but I need a inverter now! 

  v3 x;
  
  double det = A.m[0][0]*A.m[1][1]*A.m[2][2] +
               A.m[0][1]*A.m[1][2]*A.m[2][0] +
               A.m[0][2]*A.m[1][0]*A.m[2][1] -
               A.m[0][2]*A.m[1][1]*A.m[2][0] -
               A.m[0][1]*A.m[1][0]*A.m[2][2] -
  	       A.m[0][0]*A.m[1][2]*A.m[2][1];
  
  x.v[0] = b.v[0]   *A.m[1][1]*A.m[2][2] +
           A.m[0][1]*A.m[1][2]*b.v[2]    +
	   A.m[0][2]*b.v[1]   *A.m[2][1] -
	   A.m[0][2]*A.m[1][1]*b.v[2]    -
  	   A.m[0][1]*b.v[1]   *A.m[2][2] -
	   b.v[0]   *A.m[1][2]*A.m[2][1];

  
  x.v[1] = A.m[0][0]*b.v[1]   *A.m[2][2] +
           b.v[0]   *A.m[1][2]*A.m[2][0] +
           A.m[0][2]*A.m[1][0]*b.v[2]    -
           A.m[0][2]*b.v[1]   *A.m[2][0] -
           b.v[0]   *A.m[1][0]*A.m[2][2] -
  	   A.m[0][0]*A.m[1][2]*b.v[2]   ;
  
  
  x.v[2] = A.m[0][0]*A.m[1][1]*b.v[2]    +
           A.m[0][1]*b.v[1]   *A.m[2][0] +
           b.v[0]   *A.m[1][0]*A.m[2][1] -
           b.v[0]   *A.m[1][1]*A.m[2][0] -
           A.m[0][1]*A.m[1][0]*b.v[2]    -
  	   A.m[0][0]*b.v[1]   *A.m[2][1];
  
  x.v[0] /= det;
  x.v[1] /= det;
  x.v[2] /= det;

  return x;
}


void
ptx(m33 *M, v3 *V, double t)
{
  M = M;  // shut unused var warning
  V->v[0] += t;
}

void
pty(m33 *M, v3 *V, double t)
{
  M = M;  // shut unused var warning
  V->v[1] += t;
}

void
ptz(m33 *M, v3 *V, double t)
{
  M = M;  // shut unused var warning
  V->v[2] += t;
}

void
ltx(m33 *M, v3 *V, double t)
{
  M = M;  // shut unused var warning
  V->v[0] += t*M->m[0][0];
  V->v[1] += t*M->m[1][0];
  V->v[2] += t*M->m[2][0];
}

void
lty(m33 *M, v3 *V, double t)
{
  M = M;  // shut unused var warning
  V->v[0] += t*M->m[0][1];
  V->v[1] += t*M->m[1][1];
  V->v[2] += t*M->m[2][1];
}

void
ltz(m33 *M, v3 *V, double t)
{
  M = M;  // shut unused var warning
  V->v[0] += t*M->m[0][2];
  V->v[1] += t*M->m[1][2];
  V->v[2] += t*M->m[2][2];
}

void
prx(m33 *M, v3 *V, double t)
{
  m33 Rot = Rx((degrees) t);
  *V = Rot * *V;
  *M = Rot * *M;
}

void
pry(m33 *M, v3 *V, double t)
{
  m33 Rot = Ry((degrees) t);
  *V = Rot * *V;
  *M = Rot * *M;
}

void
prz(m33 *M, v3 *V, double t)
{
  m33 Rot = Rz((degrees) t);
  *V = Rot * *V;
  *M = Rot * *M;
}

void
lrx(m33 *M, v3 *V, double t)
{
  V = V; // shut up unused var warnings
  m33 Rot = R(M->m[0][0], M->m[1][0], M->m[2][0], (degrees) t);
  *M = Rot * *M;
}

void
lry(m33 *M, v3 *V, double t)
{
  V = V; // shut up unused var warnings
  m33 Rot = R(M->m[0][1], M->m[1][1], M->m[2][1], (degrees) t);
  *M = Rot * *M;
}

void
lrz(m33 *M, v3 *V, double t)
{
  V = V; // shut up unused var warnings
  m33 Rot = R(M->m[0][2], M->m[1][2], M->m[2][2], (degrees) t);
  *M = Rot * *M;
}



void
make_xform(m33 *mp, v3 *vp, const char *str)
{
  char *s = new char[strlen(str)+1];
  strcpy(s, str);
  char *sp;

  m33 M;
  v3 V;
  
  M.m[0][0] = M.m[1][1] = M.m[2][2] = 1.0;
  M.m[1][0] = M.m[0][1] = 0.0;
  M.m[2][0] = M.m[0][2] = 0.0;
  M.m[1][2] = M.m[2][1] = 0.0;
  
  V.v[0] = V.v[1] = V.v[2] = 0.0;
  
  // loop through the string

  sp = strtok(s, " ");
  while(1)
    {
      if (!sp) break;
      
      if (!strcmp(sp, "ptx"))
	{
	  sp = strtok(0, " ");
	  double v = atof(sp);
	  ptx(&M, &V, v);
	}
      else if (!strcmp(sp, "pty"))
	{
	  sp = strtok(0, " ");
	  double v = atof(sp);
	  pty(&M, &V, v);
	}
      else if (!strcmp(sp, "ptz"))
	{
	  sp = strtok(0, " ");
	  double v = atof(sp);
	  V.v[2] += v;
	  ptz(&M, &V, v);
	}
      else if (!strcmp(sp, "ltx"))
	{
	  sp = strtok(0, " ");
	  double v = atof(sp);
	  ltx(&M, &V, v);
	}
      else if (!strcmp(sp, "lty"))
	{
	  sp = strtok(0, " ");
	  double v = atof(sp);
	  lty(&M, &V, v);
	}
      else if (!strcmp(sp, "ltz"))
	{
	  sp = strtok(0, " ");
	  double v = atof(sp);
	  ltz(&M, &V, v);
	}
      else if (!strcmp(sp, "prx"))
	{
	  sp = strtok(0, " ");
	  double t = atof(sp);
	  prx(&M, &V, t);
	}
      else if (!strcmp(sp, "pry"))
	{
	  sp = strtok(0, " ");
	  double t = atof(sp);
	  pry(&M, &V, t);
	}
      else if (!strcmp(sp, "prz"))
	{
	  sp = strtok(0, " ");
	  double t = atof(sp);
	  prz(&M, &V, t);
	}
      else if (!strcmp(sp, "lrx"))
	{
	  sp = strtok(0, " ");
	  double t = atof(sp);
	  lrx(&M, &V, t);
	}
      else if (!strcmp(sp, "lry"))
	{
	  sp = strtok(0, " ");
	  double t = atof(sp);
	  lry(&M, &V, t);
	}
      else if (!strcmp(sp, "lrz"))
	{
	  sp = strtok(0, " ");
	  double t = atof(sp);
	  lrz(&M, &V, t);
	}
      else if (!strcmp(sp, "trans"))
	{
	  sp = strtok(0, " ");
	  V.v[0] = atof(sp);
	  sp = strtok(0, " ");
	  V.v[1] = atof(sp);
	  sp = strtok(0, " ");
	  V.v[2] = atof(sp);
	}
      else if (!strcmp(sp, "rot"))
	{
	  sp = strtok(0, " ");
	  M.m[0][0] = atof(sp);
	  sp = strtok(0, " ");
	  M.m[1][0] = atof(sp);
	  sp = strtok(0, " ");
	  M.m[2][0] = atof(sp);
	  sp = strtok(0, " ");
	  M.m[0][1] = atof(sp);
	  sp = strtok(0, " ");
	  M.m[1][1] = atof(sp);
	  sp = strtok(0, " ");
	  M.m[2][1] = atof(sp);
	  sp = strtok(0, " ");
	  M.m[0][2] = atof(sp);
	  sp = strtok(0, " ");
	  M.m[1][2] = atof(sp);
	  sp = strtok(0, " ");
	  M.m[2][2] = atof(sp);
	}
      else
	{
	  printf("unrecognized command: '%s'!\n", sp);
	}
    
      sp = strtok(0, " ");
    }
  
  *mp = M;
  *vp = V;
}



v3
col(m33 M, int c)
{
  v3 V;
  V.v[0] = M.m[0][c];
  V.v[1] = M.m[1][c];
  V.v[2] = M.m[2][c];
  return V;
}

v3
row(m33 M, int r)
{
  v3 V;
  V.v[0] = M.m[r][0];
  V.v[1] = M.m[r][1];
  V.v[2] = M.m[r][2];
  return V;
}

m33
skew(v3 s)
{
  m33 M;
  
  M.m[0][0] = M.m[1][1] = M.m[2][2] = 0.0;
  M.m[1][0] = s.v[2];
  M.m[0][1] = -s.v[2];
  M.m[0][2] = s.v[1];
  M.m[2][0] = -s.v[1];
  M.m[1][2] = -s.v[0];
  M.m[2][1] = s.v[0];
  
  return M;
}

m33 
orthonormalize(m33 m)
{
  v3 c0(m.m[0][0], m.m[1][0], m.m[2][0]);
  v3 c1(m.m[0][1], m.m[1][1], m.m[2][1]);
  v3 c2(m.m[0][2], m.m[1][2], m.m[2][2]);
  
  c0 = c0 * (1.0 / sqrt(c0 * c0));
  
  c1 = c1 - (c0 * c1) * c0;
  c1 = c1 * (1.0 / sqrt(c1 * c1));
  
  c2 = c2 - (c0 * c2) * c0;
  c2 = c2 - (c1 * c2) * c1;
  c2 = c2 * (1.0 / sqrt(c2 * c2));

  m.m[0][0] = c0.v[0];
  m.m[1][0] = c0.v[1];
  m.m[2][0] = c0.v[2];
  
  m.m[0][1] = c1.v[0];
  m.m[1][1] = c1.v[1];
  m.m[2][1] = c1.v[2];
  
  m.m[0][2] = c2.v[0];
  m.m[1][2] = c2.v[1];
  m.m[2][2] = c2.v[2];
  
  return m;
}



#define ROTATE(a,i,j,k,l) g=a.m[i][j]; h=a.m[k][l]; a.m[i][j]=g-s*(h+g*tau); a.m[k][l]=h+s*(g-h*tau);

void
eigen(m33 *vout, v3 *dout, m33 a)
{
  int n = 3;
  int j,iq,ip,i;
  double tresh,theta,tau,t,sm,s,h,g,c;
  int nrot;
  v3 b;
  v3 z;
  m33 v;
  v3 d;
  
  v = Identity();
  for(ip=0; ip<n; ip++) 
    {
      b.v[ip] = a.m[ip][ip];
      d.v[ip] = a.m[ip][ip];
      z.v[ip] = 0.0;
    }
  
  nrot = 0;
  
  for(i=0; i<50; i++)
    {

      sm=0.0;
      for(ip=0;ip<n;ip++) for(iq=ip+1;iq<n;iq++) sm+=fabs(a.m[ip][iq]);
      if (sm == 0.0)
	{
	  *vout = v;
	  *dout = d;
	  return;
	}
      
      
      if (i < 3) tresh=0.2*sm/(n*n);
      else tresh=0.0;
      
      for(ip=0; ip<n; ip++) for(iq=ip+1; iq<n; iq++)
	{
	  g = 100.0*fabs(a.m[ip][iq]);
	  if (i>3 && 
	      fabs(d.v[ip])+g==fabs(d.v[ip]) && 
	      fabs(d.v[iq])+g==fabs(d.v[iq]))
	    a.m[ip][iq]=0.0;
	  else if (fabs(a.m[ip][iq])>tresh)
	    {
	      h = d.v[iq]-d.v[ip];
	      if (fabs(h)+g == fabs(h)) t=(a.m[ip][iq])/h;
	      else
		{
		  theta=0.5*h/(a.m[ip][iq]);
		  t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
		  if (theta < 0.0) t = -t;
		}
	      c=1.0/sqrt(1+t*t);
	      s=t*c;
	      tau=s/(1.0+c);
	      h=t*a.m[ip][iq];
	      z.v[ip] -= h;
	      z.v[iq] += h;
	      d.v[ip] -= h;
	      d.v[iq] += h;
	      a.m[ip][iq]=0.0;
	      for(j=0;j<ip;j++) { ROTATE(a,j,ip,j,iq); } 
	      for(j=ip+1;j<iq;j++) { ROTATE(a,ip,j,j,iq); } 
	      for(j=iq+1;j<n;j++) { ROTATE(a,ip,j,iq,j); } 
	      for(j=0;j<n;j++) { ROTATE(v,j,ip,j,iq); } 
	      nrot++;
	    }
	}
      for(ip=0;ip<n;ip++)
	{
	  b.v[ip] += z.v[ip];
	  d.v[ip] = b.v[ip];
	  z.v[ip] = 0.0;
	}
    }

  fprintf(stderr, "eigen: too many iterations in Jacobi transform.\n");

  return;
}







