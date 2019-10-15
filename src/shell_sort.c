int shell_sort(double *data,int size)
{
    int i,j,k;
    int *a,ret_code;
    double tmp;

    ret_code = 0;
    if(size <= 0) {
        ret_code = -1;
        goto error;
    }
    i=0;
    j=1;
    while(j<size) {
        k = j;
        while(k<size) {
            i++;
            k *= 3;
        }
        j *= 2;
    }
    if((a=(int *)malloc((i+2)*sizeof(int)))==NULL) {
        ret_code = -1;
        goto error;
    }
    a+=2;
    i=0;
    j=1;
    while(j<size) {
        k = j;
        while(k<size) {
            a[i++] = k;
            k *= 3;
        }
        j *= 2;
    }
    a[-2]=i;
    for(i=1;i<a[-2];i++) {
        j=i;
        while(j>0) {
            k=(j-1)>>1;
            if(a[j] > a[k]) {
                a[-1] = a[j];
                a[j] = a[k];
                a[k] = a[-1];
            } else {
                break;
            }
        }
    }
    for(i=a[-2]-1;i>0;i--) {
        a[-1] = a[i];
        a[i] = a[0];
        a[0] = a[-1];
        j=0;
        while(j*2+1<i) {
            k=j*2+1;
            if(k+1 < i && a[k] < a[k+1]) {
                k++;
            }
            if(a[j] < a[k]) {
                a[-1]=a[k];
                a[k] = a[j];
                a[j] = a[-1];
                j=k;
            } else {
                break;
            }
        }
    }
    for(i=a[-2]-1;i>=0;i--) {
        for(j=1;j<size;j++) {
            tmp = data[j];
            for(k=j;k-a[i]>=0 && data[k-a[i]]>tmp;k-=a[i]) {
                data[k] = data[k-a[i]];
            }
            data[k] = tmp;
        }
    }

    free(a-2);
    error:
    return ret_code;
}
