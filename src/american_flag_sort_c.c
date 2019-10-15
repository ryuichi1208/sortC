void american_flag_sort_c(double *data,int size,int **a,int l)
{
    int i,j;
    unsigned char *b;
    double tmp;
    if(l==0|| size < 1) {
        return;
    }
    l--;
    for(i=0;i<257;i++) {
        a[l][i] = 0;
    }
    for(i=0;i<size;i++) {
        b = (unsigned char *)(data + i);
        a[l][1+b[l]]++;
    }
    for(i=0;i<256;i++) {
        a[l][i+1] += a[l][i];
        a[sizeof(double)][i] = a[l][i+1];
    }
    b = (unsigned char *)&tmp;
    for(i=0;i<256;i++) {
        for(j=a[l][i];j<a[sizeof(double)][i];) {
            tmp = data[j];
            if(b[l] != i) {
                data[j] = data[a[l][b[l]]];
                data[a[l][b[l]]] = tmp;
            } else {
                j++;
            }
            a[l][b[l]]++;
        }
    }
    a[l][0] = 0;
    for(i=0;i<256;i++) {
        a[l][i+1] = a[sizeof(double)][i];
    }
    for(i=0;i<256;i++) {
        american_flag_sort_c(data+a[l][i],a[l][i+1]-a[l][i],a,l);
    }

    return;
}

int american_flag_sort(double *data,int size)
{
    int i,j,ret_code;
    int *a[1+sizeof(double)];
    unsigned char *b;
    ret_code = 0;

    if((a[0]=(int *)malloc(1024*(1+sizeof(double))*sizeof(int)))==NULL) {
        ret_code = -1;
        goto error01;
    }
    for(i=1;i<=sizeof(double);i++) {
        a[i] = a[i-1] + 1024;
    }
    for(i=0;i<size;i++) {
        b = (unsigned char *)(data + i);
        if(0x80 & b[sizeof(double)-1]) {
            for(j=0;j<sizeof(double);j++) {
                b[j] = ~b[j];
            }
        } else {
            b[sizeof(double)-1] ^= 0x80;
        }
    }

    american_flag_sort_c(data,size,a,sizeof(double));

    for(i=0;i<size;i++) {
        b = (unsigned char *)(data + i);
        if(0x80 & b[sizeof(double)-1]) {
            b[sizeof(double)-1] ^= 0x80;
        } else {
            for(j=0;j<sizeof(double);j++) {
                b[j] = ~b[j];
            }
        }
    }

    free(a[0]);
    error01:
    return ret_code;
}
