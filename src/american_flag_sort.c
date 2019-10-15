int american_flag_sort(double *data,int size)
{
    int i,j,k,ret_code;
    int **a,*b;
    double **c;
    unsigned char *d;
    double tmp;
    ret_code = 0;

    i  = (1+sizeof(double))*sizeof(int *);
    i  = ((i + sizeof(double *) - 1)/sizeof(double *))*sizeof(double *);
    i += sizeof(double)*sizeof(double *);
    i  = ((i + sizeof(int) -1)/sizeof(int))*sizeof(int);
    i += 257*(1+sizeof(double))*sizeof(int);
    i += 2*sizeof(double)*sizeof(int);
    if((a=(int **)malloc(i))==NULL) {
        ret_code = -1;
        goto error01;
    }
    i  = (1+sizeof(double))*sizeof(int *);
    j  = (i + sizeof(double *) - 1)/sizeof(double *);
    i  = j * sizeof(double *);
    c  = ((double **)a) + j;
    i += sizeof(double)*sizeof(double *);
    j  = (i + sizeof(int) -1)/sizeof(int);
    a[0]  = ((int *)c) + j;
    for(i=1;i<=sizeof(double);i++) {
        a[i] = a[i-1] + 257;
    }
    b = a[sizeof(double)] + 257;

    for(i=0;i<size;i++) {
        d = (unsigned char *)(data + i);
        if(0x80 & d[sizeof(double)-1]) {
            for(j=0;j<sizeof(double);j++) {
                d[j] = ~d[j];
            }
        } else {
            d[sizeof(double)-1] ^= 0x80;
        }
    }
    b[sizeof(double)-1] = size;
    b[2*sizeof(double)-1] = 0;
    c[sizeof(double)-1] = data;
    i=sizeof(double)-1;
    while(1) {
        for(j=0;j<257;j++) {
            a[i][j] = 0;
        }
        for(j=0;j<b[i];j++) {
            d = (unsigned char *)(c[i] + j);
            a[i][1+d[i]]++;
        }
        for(j=0;j<256;j++) {
            a[i][j+1] += a[i][j];
            a[sizeof(double)][j] = a[i][j+1];
        }
        d = (unsigned char *)(&tmp);
        for(j=0;j<256;j++) {
            for(k=a[i][j];k<a[sizeof(double)][j];) {
                tmp = c[i][k];
                if(j != d[i]) {
                    c[i][k] = c[i][a[i][d[i]]];
                    c[i][a[i][d[i]]] = tmp;
                } else {
                    k++;
                }
                a[i][d[i]]++;
            }
        }
        a[i][0] = 0;
        for(j=0;j<256;j++) {
            a[i][j+1] = a[sizeof(double)][j];
        }
        k = 0;
        if(i != 0 && b[i]>1) {
            k = 0;
            while(a[i][1+k] - a[i][k] == 0 && k < 256) k++;
            if(k < 256) {
                c[i-1] = c[i] + a[i][k];
                b[i-1] = a[i][1+k] - a[i][k];
                b[sizeof(double)+i] = k+1;
                k=0;
                i--;
            } else {
                k=1;
            }
        } else {
            k = 1;
        }
        if(k) {
            j = i+1;
            while(j<sizeof(double)) {
                k = b[sizeof(double)+j];
                while(a[j][1+k] - a[j][k] == 0 && k < 256) {
                    k++;
                }
                if(k == 256) {
                    b[sizeof(double)+j] = 256;
                    j++;
                } else {
                    break;
                }
            }
            if(j==sizeof(double)) {
                goto end;
            }
            c[j-1] = c[j] + a[j][k];
            b[j-1] = a[j][1+k] - a[j][k];
            b[sizeof(double)+j] = k + 1;
            i=j-1;
        }
    }
    end:

    for(i=0;i<size;i++) {
        d = (unsigned char *)(data + i);
        if(0x80 & d[sizeof(double)-1]) {
            d[sizeof(double)-1] ^= 0x80;
        } else {
            for(j=0;j<sizeof(double);j++) {
                d[j] = ~d[j];
            }
        }
    }

    free(a);
    error01:
    return ret_code;
}
