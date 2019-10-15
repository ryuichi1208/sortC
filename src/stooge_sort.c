void stooge_sort(double *data,int size)
{
    int i;
    double tmp;
    if(size > 1 && data[0] > data[size-1]) {
        tmp = data[0];
        data[0] = data[size-1];
        data[size-1] = tmp;
    }
    if(size >= 3) {
        i = (2*size + 2)/3;
        stooge_sort(data,i);
        stooge_sort(data + size - i,i);
        stooge_sort(data,i);
    }
    return;
}
