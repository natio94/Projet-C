
#include "structure.h"


int main(){
    //printf("test");
    COLUMN test=*create_column("test");
    printf("%d\n",insert_values(&test,5));
    printf("%d\n",insert_values(&test,8));
    print_col(&test);
    delete_column(&test);
    print_col(&test);
    return 0;
}