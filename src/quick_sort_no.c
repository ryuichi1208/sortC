int quick_sort(double *a,int size)
{
    int i,j,k;
    double p,q;
    int *stack;

    if((stack = (int *)malloc(16*sizeof(int)*sizeof(int))) == NULL) {
        return 0;
    }
    stack[0] = 0;
    stack[1] = size;
    i = 0;
    while(i>=0) {
        if(stack[i*2+1] - stack[i*2+0] >= 3) {
            k = (stack[i*2+1] + stack[i*2+0])/2;
            if(a[stack[i*2+0]] < a[k]) {
                if(a[k] < a[stack[i*2+1]-1]) {
                    p = a[k];
                } else if(a[stack[i*2+0]] < a[stack[i*2+1]-1]) {
                    p = a[stack[i*2+1]-1];
                } else {
                    p = a[stack[i*2+0]];
                }
            } else {
                if(a[k] > a[stack[i*2+1]-1]) {
                    p = a[k];
                } else if(a[stack[i*2+0]] < a[stack[i*2+1]-1]) {
                    p = a[stack[i*2+0]];
                } else {
                    p = a[stack[i*2+1]-1];
                }
            }
        } else if(stack[i*2+1] - stack[i*2+0] == 2) {
            p = a[stack[i*2+0]];
        } else {
            i--;
            continue;
        }
        j = stack[i*2+0];
        k = stack[i*2+1] -1;
        while(1) {
            while(a[j] < p) j++;
            while(a[k] > p) k--;
            if(j>=k) break;
            q = a[j];
            a[j] = a[k];
            a[k] = q;
            j++;
            k--;
        }
        if(j - stack[i*2+0] < stack[i*2+1] - k - 1) {
            stack[i*2+2] = stack[i*2+0];
            stack[i*2+3] = j;
            stack[i*2+0] = k+1;
        } else {
            stack[i*2+2] = k+1;
            stack[i*2+3] = stack[i*2+1];
            stack[i*2+1] = j;
        }
        i++;
    }
    free(stack);
    return 0;
}
