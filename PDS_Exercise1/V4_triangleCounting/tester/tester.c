#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <assert.h>
#include "mmio.h"

uint32_t *vertexWiseTriangleCounts(uint32_t *coo_row, uint32_t *coo_col, uint32_t n, uint32_t nz);

int main(int argc, char *argv[]){

    int ret_code;
    MM_typecode matcode;
    FILE *f;
    int M, N, nnz;
    int i,temp,l;
    int col_start,col_end;// *I, *J;
    int col_start2,col_end2;// *I, *J;
    double *val;
    int col,col2;
    int triang_num = 0;
    int num=0;

    uint32_t isOneBased = 0;
    uint32_t *I,*J;
    uint32_t *csc_row;
    uint32_t *csc_col;
    uint32_t *rowI;
    uint32_t *rowJ;
    uint32_t *rowK;
    int *c3;

    uint32_t *vector;
    /* variables to hold execution time */
    struct timeval startwtime, endwtime;
    double seq_time;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s [martix-market-filename]\n", argv[0]);
        exit(1);
    }
    else
    {
        if ((f = fopen(argv[1], "r")) == NULL){
            printf("Could not process Matrix Market banner.\n");
            exit(1);
        }
    }

    if (mm_read_banner(f, &matcode) != 0)
    {
        printf("Could not process Matrix Market banner.\n");
        exit(1);
    }


    /*  This is how one can screen matrix types if their application */
    /*  only supports a subset of the Matrix Market data types.      */

    if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
            mm_is_sparse(matcode) )
    {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        exit(1);
    }

    /* find out size of sparse matrix .... */

    if ((ret_code = mm_read_mtx_crd_size(f, &M, &N, &nnz)) !=0)
        exit(1);

    printf("nnz = %d\nM   = %d\n",nnz,M);


    /* reseve memory for matrices */

    I = (uint32_t *) malloc(nnz * sizeof(int));
    J = (uint32_t *) malloc(nnz * sizeof(int));
    val = (double *) malloc(nnz * sizeof(double));
    vector = (int *) malloc(M * sizeof(int));


    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

    /* Replace missing val column with 1s and change the fscanf to match patter matrices*/

    if (!mm_is_pattern(matcode))
    {
        for (i=0; i<nnz; i++)
        {
            fscanf(f, "%d %d %lg\n", &I[i], &J[i], &val[i]);
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }
    }
    else
    {
        for (i=0; i<nnz; i++)
        {
            fscanf(f, "%d %d\n", &I[i], &J[i]);
            val[i]=1;
            I[i]--;  /* adjust from 1-based to 0-based */
            J[i]--;
        }
    }
    //for(int l = 0; l < nnz; l++)
    //printf("coo_col[%d] = %d     csc_row[%d] = %d\n",l,I[l],l,J[l]);

    vector = vertexWiseTriangleCounts(I, J, M, nnz);

    for(int k = 0; k < M; k++)
        printf("vector[%d] = %d\n",k,vector[k]);

    free(I);
    free(J);
    free(val);
    free(vector);


}

uint32_t *vertexWiseTriangleCounts(uint32_t *coo_row, uint32_t *coo_col, uint32_t n, uint32_t nz){

    uint32_t * vector,count=0;
    uint32_t k=0,t=0,temp1=0;
    uint32_t col_start;
    uint32_t col_end; 
    uint32_t col_start2;
    uint32_t col_end2;
    int triang_num = 0;
    vector = (uint32_t *)malloc(n   * sizeof(uint32_t));
    for (uint32_t l = 0; l < n; l++) vector[l] = 0;

    uint32_t *csc_row = (uint32_t *)malloc(nz   * sizeof(uint32_t));
    uint32_t *csc_col = (uint32_t *)malloc((n+1) * sizeof(uint32_t));
    uint32_t *rowI = (uint32_t *)malloc(nz   * sizeof(uint32_t));
    uint32_t *rowJ = (uint32_t *)malloc(nz   * sizeof(uint32_t));

    // ----- cannot assume that input is already 0!
    for (uint32_t l = 0; l < n+1; l++) csc_col[l] = 0;

    // ----- find the correct column sizes
    for (uint32_t l = 0; l < nz; l++)
        csc_col[coo_col[l]]++;

    // ----- cumulative sum
    for (uint32_t i = 0, cumsum = 0; i < n; i++) {
        uint32_t temp = csc_col[i];
        csc_col[i] = cumsum;
        cumsum += temp;
    }
    csc_col[n] = nz;
    // ----- copy the row indices to the correct place
    for (uint32_t l = 0; l < nz; l++) {
        uint32_t col_l;
        col_l = coo_col[l];

        uint32_t dst = csc_col[col_l];
        csc_row[dst] = coo_row[l];

        csc_col[col_l]++;
    }
    // ----- revert the column pointers
    for (uint32_t i = 0, last = 0; i < n; i++) {
        uint32_t temp = csc_col[i];
        csc_col[i] = last;
        last = temp;
    }                                


    // for every column
    for(int col = 0; col < n; col++){
        col_start = csc_col[col];
        col_end   = csc_col[col+1];
        //rowI = (uint32_t *)realloc(rowI,(col_end-col_start)   * sizeof(uint32_t));
        temp1 = col_start;
        // take the row indexes
        for(int l = 0; l < (col_end-col_start); l++){
            rowI[l] =  csc_row[temp1];
            temp1++;
        }
        //Go through only nodes that have an edge with node-col
        /* Go and check how many common nodes node-col has with node-rowI[col2] 
           which is the number of triangles that node-col participates*/
        /* Use only low part of the symmetric matrix because we iterate only
           nodes that already have an edge between them*/

        for(int col2 = 0; col2 < (col_end-col_start); col2++){
            col_start2 = csc_col[rowI[col2]];
            col_end2   = csc_col[rowI[col2]+1];
            //rowJ = (uint32_t *)realloc(rowJ,(col_end2-col_start2)   * sizeof(uint32_t));
            temp1 = col_start2;
            for(int l = 0; l < (col_end2-col_start2); l++){
                rowJ[l] =  csc_row[temp1];
                temp1++;
            }
            //num = count_Common(rowI,(col_end-col_start),rowJ,(col_end2-col_start2));
            k=0,t=0;
            count=0;
            while((col_end-col_start) > k && (col_end2-col_start2)> t){
                if (rowI[k] < rowJ[t]) {
                    k++;
                }else if(rowJ[t] < rowI[k]){
                    t++;
                } else {
                    vector[rowI[col2]]++;
                    vector[rowJ[t]]++;
                    count++;
                    k++;
                    t++;
                }
            }
            triang_num += count;
            vector[col] += count;
        }
    }

    //printf("triangle number = %d\n",triang_num);
    /* cleanup variables */
    free(rowJ);

    free(rowI);
    free( csc_row );
    free( csc_col );


    return vector;

}

