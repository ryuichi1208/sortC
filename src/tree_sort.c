int tree_sort(double *data,int size)
{
    int i,j,k,l,ret_code;
    double *a;
    int *b;
    ret_code = 0;
    if((a = (double *)malloc(size*sizeof(double))) == NULL) {
        ret_code = -1;
        goto error01;
    }
    if((b = (int *)malloc(3*size*sizeof(int))) == NULL) {
        ret_code = -1;
        goto error02;
    }

    for(i=0;i<3*size;i++) {
        b[i] = -1;
    }

    a[0] = data[0];
    for(i=1;i<size;i++) {
        j = 0;
        while(j >= 0) {
            if(a[j] > data[i]) {
                l = 1;
            } else {
                l = 2;
            }
            k = j;
            j = b[j*3 + l];
        }
        b[k*3 + l] = i;
        b[i*3 + 0] = k;
        a[i] = data[i];
    }

    i = 0;
    j = -1;
    k = 0;
    while(i != -1) {
        if(b[i*3 + 1] != -1 && j == b[i*3 + 0]) {
            j = i;
            i = b[i*3 + 1];
        } else if(b[i*3 + 2] != -1 && j != b[i*3 + 2]) {
            data[k++] = a[i];
            j = i;
            i = b[i*3 + 2];
        } else {
            if(j != b[i*3 + 2] || (b[i*3+1] == -1 && b[i*3+2] == -1)) {
                data[k++] = a[i];
            }
            j = i;
            i = b[i*3 + 0];
        }
    }

    free(b);
    error02:
    free(a);
    error01:
    return ret_code;
}
