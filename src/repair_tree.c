void repair_tree(double *tree,int tree_size,unsigned int *leonardo_number)
{
    int i;
    double tmp;

    if(tree_size < 3) {
        return;
    }
    i=1;
    while(leonardo_number[i] < tree_size) i++;
    if(tree[leonardo_number[i-1]-1] < tree[tree_size-2]) {
        if(tree[tree_size-1] < tree[tree_size-2]) {
            tmp = tree[tree_size-2];
            tree[tree_size-2] = tree[tree_size-1];
            tree[tree_size-1] = tmp;
            repair_tree(tree + leonardo_number[i-1],leonardo_number[i-2],leonardo_number);
        }
    } else {
        if(tree[tree_size-1] < tree[leonardo_number[i-1]-1]) {
            tmp = tree[leonardo_number[i-1]-1];
            tree[leonardo_number[i-1]-1] = tree[tree_size-1];
            tree[tree_size-1] =tmp;
            repair_tree(tree,leonardo_number[i-1],leonardo_number);
        }
    }

    return;
}

int smooth_sort(double *data,int size)
{
    int i,j,k,ret_code;
    unsigned int *leonardo_number;
    int *tree_size,*tree_offset;
    double tmp;
    ret_code = 0;

    if(size < 1) {
        ret_code = -1;
        goto error01;
    }
    if((leonardo_number=(unsigned int *)malloc(3*64*sizeof(unsigned int)))==NULL) {
        ret_code = -1;
        goto error01;
    }
    tree_size = (int *)(leonardo_number + 64);
    tree_offset = tree_size + 64;
    leonardo_number[0] = 1;
    leonardo_number[1] = 1;
    i=2;
    while(i<45) {
        leonardo_number[i] = leonardo_number[i-1] + leonardo_number[i-2] + 1;
        i++;
    }
    while(i<3*64) {
        leonardo_number[i++] = 0;
    }

    tree_offset[0] = 0;
    for(i=0;i<size;i++) {
        j = 0;
        while(tree_size[j]) j++;
        tree_size[j]++;
        k=0;
        while(j>=2) {
            while(leonardo_number[k] < tree_size[j] + tree_size[j-1] + tree_size[j-2]) k++;
            if(leonardo_number[k] == tree_size[j] + tree_size[j-1] + tree_size[j-2]) {
                tree_size[j] = 0;
                tree_size[j-1] = 0;
                tree_size[j-2] = leonardo_number[k];
                j-=2;
            } else {
                j--;
            }
        }
        j=0;
        while(tree_size[j]) {
            tree_offset[j+1] = tree_offset[j] + tree_size[j];
            j++;
        }
        if(j >= 1) {
            repair_tree(data+tree_offset[j-1],tree_size[j-1],leonardo_number);
        }
    }
    j=1;
    k=0;
    while(tree_size[j]) {
        if(data[tree_offset[j+1]-1] > data[tree_offset[k+1]-1]) {
            k = j;
        }
        j++;
    }
    if(j != k+1) {
        tmp = data[tree_offset[j]-1];
        data[tree_offset[j]-1] = data[tree_offset[k+1]-1];
        data[tree_offset[k+1]-1] = tmp;
        repair_tree(data+tree_offset[j-1],tree_size[j-1],leonardo_number);
    }

    while(1) {
        j = 0;
        i = 0;
        while(tree_size[j]) {
            i += tree_size[j];
            j++;
        }
        if(i <= 1) break; 
        j--;
        i = 0;
        while(leonardo_number[i] < tree_size[j]) i++;
        if(i >= 2) {
            tree_size[j] = leonardo_number[i-1];
            tree_size[j+1] = leonardo_number[i-2];
        } else {
            tree_size[j]--;
        }
        j=0;
        k=0;
        while(tree_size[j]) {
            tree_offset[j+1] = tree_offset[j] + tree_size[j];
            if(data[tree_offset[j+1]-1] > data[tree_offset[k+1]-1]) {
                k = j;
            }
            j++;
        }
        if(j != k+1) {
            tmp = data[tree_offset[j]-1];
            data[tree_offset[j]-1] = data[tree_offset[k+1]-1];
            data[tree_offset[k+1]-1] = tmp;
        }
        j=0;
        while(tree_size[j]) {
            repair_tree(data+tree_offset[j],tree_size[j],leonardo_number);
            j++;
        }
    }

    free(leonardo_number);
    error01:
    return ret_code;
}
