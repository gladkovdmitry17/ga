

/*running this program for GA_FIll and _Fill_patch*/

#include<stdio.h>
#include<stdlib.h>

#include"mpi.h"
#include"ga.h"
#include"macdecls.h"

main(int argv, char **argc)
{
  int i, j, dims1[3]={4,5,5}, dims2[2]={5,5}, lo[3]={1,1,1}, hi[3]={2,4,4};
  int lo2[2]={1,1}, hi2[2]={3,3};
  int g_A, g_B, value=5, val_patch=1;

  MPI_Init(&argv, &argc);
  MA_init(C_INT, 1000, 1000);
  GA_Initialize();

  g_A=NGA_Create(C_INT, 3, dims1, "array_A", NULL);
  g_B=NGA_Create(C_INT, 2, dims2, "array_B", NULL);                          

  NGA_Fill_patch(g_A, lo, hi, &val_patch);
  GA_Sync();
  GA_Print(g_A);

  GA_Fill(g_B, &value);
  NGA_Fill_patch(g_B, lo2, hi2, &val_patch);
  GA_Sync();
  GA_Print(g_B);
  GA_Print_distribution(g_B);


  GA_Terminate();
  MPI_Finalize();
  return 0;
}
