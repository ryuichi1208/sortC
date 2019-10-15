unsigned int mapkey(double a)
{
    uint64_t *b = (uint64_t *)&a;
    *b = *b >> 52;
    if((*b)&0x800) {
        *b ^= 0xfff;
    } else {
        *b ^= 0x800;
    }
    return (unsigned int)*b;
}

int proxmap_sort(double *data,int size)
{
    int i,j,k,ret_code;
    double *a;
    unsigned int *b,*c;
    ret_code = 0;
    k = (key_length > size)? key_length : size;
    i = (((size + k)*sizeof(unsigned int) + sizeof(double) - 1)/sizeof(double))*sizeof(double);
    j = i/sizeof(unsigned int);
    i += size * sizeof(double);
    if((b=(unsigned int *)malloc(i))==NULL) {
        ret_code = -1;
        goto error01;
    }
    c = b + k;
    a = (double *)(b + j);

    for(i=0;i<key_length;i++) {
        b[i] = 0;
    }
    for(i=0;i<size;i++) {
        ci] = mapkey(data[i]);
        b[c[i]]++;
    }
    j = 0;
    for(i=0;i<key_length;i++) {
        k = b[i];
        b[i] = j;
        j += k;
    }
    for(i=0;i<size;i++) {
        c[i] = b[c[i]];
    }
    for(i=0;i<size;i++) {
        b[i] = 0;
    }
    for(i=0;i<size;i++) {
        j = c[i];
        while(b[j] && data[i] >= a[j]) j++;
        if(!b[j]) {
            b[j] = -1;
            a[j] = data[i];
        } else {
            k = j + 1;
            while(b[k]) k++;
            b[k] = -1;
            while(k > j) {
                a[k] = a[k-1];
                k--;
            }
            a[j] = data[i];
        }
    }
    for(i=0;i<size;i++) {
        data[i] = a[i];
    }

    free(b);
    error01:
    return ret_code;
}
