void quick_sort(double *a,int size)
{
    int i,j;
    double p,q;
    if(size >= 3) {
        if(a[0] < a[size/2]) {
            if(a[size/2] < a[size-1]) {
                p = a[size/2];
            } else if (a[size-1] < a[0]){
                p = a[0];
            } else {
                p = a[size-1];
            }
        } else {
            if(a[size/2] > a[size-1]) {
                p = a[size/2];
            } else if (a[size-1] > a[0]){
                p = a[0];
            } else {
                p = a[size-1];
            }
        }
    } else if(size == 2) {
        p = a[0];
    } else {
        return;
    }
    i = 0;
    j = size -1;
    while(1) {
        while(a[i] < p) i++;
        while(a[j] > p) j--;
        if(i>=j) break;
        q = a[i];
        a[i] = a[j];
        a[j] = q;
        i++;
        j--;
    }
    quick_sort(a,i);
    j++;
    i = size - j;
    quick_sort(a+j,i);
    return;
}
