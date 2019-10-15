int merge_sort(double *data,int size)
{
    int i,j,k,l,m,n,m_max,n_max,ret_code;
    double *tmp[2];
    ret_code = 0;

    tmp[0] = data;
    if((tmp[1] = (double *)malloc(size*sizeof(double))) == NULL) {
        ret_code = -1;
        goto error01;
    }

    l = 0x00;
    for(i=1;i<size;i*=2) {
        for(j=0;j<size;j+=i*2) {
            k = j;
            m = j;
            n = j + i;
            m_max = (m+i < size)? m+i : size;
            n_max = (n+i < size)? n+i : size;
            while(m<m_max && n<n_max) {
                if(tmp[l][m] <= tmp[l][n]) {
                    tmp[l^0x01][k++] = tmp[l][m++];
                } else {
                    tmp[l^0x01][k++] = tmp[l][n++];
                }
            }
            while(m<m_max) {
                tmp[l^0x01][k++] = tmp[l][m++];
            }
            while(n<n_max) {
                tmp[l^0x01][k++] = tmp[l][n++];
            }
        }
        l ^= 0x01;
    }

    if(l == 0x01) {
        for(i=0;i<size;i++) {
            tmp[0][i] = tmp[1][i];
        }
    }

    free(tmp[1]);
    error01:
    return ret_code;
}
