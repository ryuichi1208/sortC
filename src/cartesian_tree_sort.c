int cartesian_tree_sort(double *data,int size)
{
    int i,j,k,l,ret_code;
    double *a;
    int *b,*c;
    ret_code = 0;

    i = ((3 * size * sizeof(int) + sizeof(int) -1)/sizeof(double))*sizeof(double);
    j = (i + sizeof(int) - 1)/sizeof(int);
    if((a=(double *)malloc((j + size) * sizeof(int)))==NULL) {
        ret_code = -1;
        goto error01;
    }
    b = (int *)a;
    c = b + j;
        for(i=0;i<4*size;i++) {
        b[i] = -1;
    }
    k=0;
    for(i=1;i<size;i++) {
        j = i-1;
        while(b[3*j] != -1 && data[j] > data[i]) j=b[3*j];
        if(data[j] > data[i]) {
            k=i;
            b[3*j] = i;
            b[3*i+1] = j;
        } else if(b[3*j+2] == -1) {
            b[3*j+2] = i;
            b[3*i] = j;
        } else {
            b[3*i] = j;
            b[3*i+1] = b[3*j+2];
            b[3*b[3*j+2]] = i;
            b[3*j+2] = i;
        }
    }
    i=0;
    j=1;
        c[i] = k;
    while(i < size && c[i] != -1) {
        k = b[3*c[i]+1];
        if(k != -1) {
            for(l=j;data[k] < data[c[l-1]];l--) {
                c[l] = c[l-1];
            }
            c[l] = k;
            j++;
        }
        k = b[3*c[i]+2];
        if(k != -1) {
            for(l=j;data[k] < data[c[l-1]];l--) {
                c[l] = c[l-1];
            }
            c[l] = k;
            j++;
        }
        i++;
    }
    for(i=0;i<size;i++) {
        a[i] = data[i];
    }
    for(i=0;i<size;i++) {
        data[i] = a[c[i]];
    }

    free(a);
    error01:
    return ret_code;
}
