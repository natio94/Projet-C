// Creator: Natio & Wek
#include "structure.h"


int main(){
    //printf("test");
    COLUMN test=*create_column("test");
    printf("%d\n",insert_values(&test,5));
    printf("%d\n",insert_values(&test,8));
    print_col(&test);
    delete_column(&test);
    print_col(&test);


        // Create a dataframe
        CDataframe* df = create_dataframe();

        // Add a column
        char* title = "Test Column";
        add_column_dataframe(df, title);

        // Print number of columns
        printf("Number of columns: %d\n", get_number_columns(df));

        // Add a row
        int row_values[] = {5};
        add_row_dataframe(df, row_values);

        // Print number of rows
        printf("Number of rows: %d\n", get_number_rows(df));

        // Print value
        printf("Value at (0,0): %d\n", get_value_from_dataframe(df, 0, 0));

        // Set value
        set_value_in_dataframe(df, 0, 0, 10);
        printf("New value at (0,0): %d\n", get_value_from_dataframe(df, 0, 0));

        // Check if value exists
        printf("Does 10 exist in dataframe: %d\n", value_exists_in_dataframe(df, 10));

        // Count cells equal to, greater than, and less than a value
        printf("Number of cells equal to 10: %d\n", count_cells_equal(df, 10));
        printf("Number of cells greater than 5: %d\n", count_cells_greater(df, 5));
        printf("Number of cells less than 15: %d\n", count_cells_less(df, 15));

        // Delete a row
        delete_row_dataframe(df, 0);
        printf("Number of rows after deletion: %d\n", get_number_rows(df));

        // Delete a column
        delete_column_dataframe(df, 0);
        printf("Number of columns after deletion: %d\n", get_number_columns(df));

        printf("All operations completed!\n");

        return 0;
    }

