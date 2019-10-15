int radix_sort(double *data,int size)
{
    int i,j,k,ret_code;
    double **a;
    int **b;
    unsigned char *c;
    ret_code = 0;

    if(size <= 1) {
        ret_code = -1;
        goto error;
    }
    i = 2*sizeof(double *);
    i = ((i + sizeof(int *) - 1)/sizeof(int *));
    i = (i +sizeof(double))*sizeof(int *);
    i = ((i + sizeof(int) - 1)/sizeof(int));
    i = (i + 257*sizeof(double))* sizeof(int);
    i = ((i + sizeof(double) - 1)/sizeof(double));
    i = (i+size) * sizeof(double);
    if((a=(double **)malloc(i))==NULL) {
        ret_code = -1;
        goto error;
    }
    i    = 2*sizeof(double *);
    i    = ((i + sizeof(int *) - 1)/sizeof(int *));
    b    = ((int **)a) + i;
    i    = (i +sizeof(double))*sizeof(int *);
    i    = (( + sizeof(int) - 1)/sizeof(int));
    b[0] = ((int *)a) + i;
    i    = (i + 257*sizeof(double))* sizeof(int);
    i    = ((i + sizeof(double) - 1)/sizeof(double));
    a[1] = ((double *)a) + i;
    a[0] = data;
    for(i=1;i<sizeof(double);i++) {
        b[i] = b[i-1] + 257;
    }

    for(i=0;i<257*sizeof(double);i++) {
        b[0][i] = 0;
    }
    for(i=0;i<size;i++) {
        c = (unsigned char *)(data + i);
        if(c[sizeof(double)-1]&0x80) {
            for(j=0;j<sizeof(double);j++) {
                c[j] = ~c[j];
            }
        } else {
            c[sizeof(double)-1] ^= 0x80;
        }
        for(j=0;j<sizeof(double);j++) {
            b[j][1+c[j]]++;
        }
    }

    k = 0x00;
    for(i=0;i<sizeof(double);i++) {
        for(j=0;j<256;j++) {
            b[i][j+1] += b[i][j];
        }
        for(j=0;j<size;j++) {
            c = (unsigned char *)(a[k] + j);
            a[k^0x01][b[i][c[i]]] = a[k][j];
            b[i][c[i]]++;
        }
        k ^= 0x01;
    }
    if(k==0x01) {
        for(i=0;i<size;i++) {
            data[i] = a[1][i];
        }
    }

    for(i=0;i<size;i++) {
        c = (unsigned char *)(data + i);
        if(c[sizeof(double)-1]&0x80) {
            c[sizeof(double)-1] ^= 0x80;
        } else {
            for(j=0;j<sizeof(double);j++) {
                c[j] = ~c[j];
            }
        }
    }

    free(a);
    error:
    return ret_code;
}
