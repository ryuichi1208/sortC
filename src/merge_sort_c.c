void merge_sort_c(double *a,double *b,int n,int m) {
    int i,j,k,l;
    double *c;
    k = n >> 1;
    if(n > 2) {
        j = n - k;
        merge_sort_c(a,b,k,m^0x01);
        merge_sort_c(a+k,b+k,j,m^0x01);
    } else if(m == 0) {
        for(i=0;i<n;i++) {
            b[i] = a[i];
        }
    }
    if(m != 0) {
        c = a;
        a = b;
        b = c;
    }
    i = 0;
    j = k;
    l = 0;
    while(i<k && j<n) {
        if(b[i] <= b[j]) {
            a[l++] = b[i++];
        } else {
            a[l++] = b[j++];
        }
    }
    while(i<k) {
        a[l++] = b[i++];
    }
    while(j<n) {
        a[l++] = b[j++];
    }
}

int merge_sort(double *data,int size) {
    double *tmp;
    if((tmp = (double *)malloc(size*sizeof(double))) == NUL) {
        return -1;
    }
    merge_sort_c(data,tmp,size,0);
    free(tmp);
    return 0;
}
