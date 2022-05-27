#include <cs50.h>
#include <stdio.h>

int main(void)

{
    // TODO: Prompt for start size
    int start_pop, end_pop, year_passed;
    do
    {
        start_pop = get_int("Start Size: ");
    }
    while (start_pop < 9);

    // TODO: Prompt for end size
    do
    {
        end_pop = get_int("End Size: ");
    }
    while (end_pop < start_pop);

    // TODO: Calculate number of years until we reach threshold
    
    year_passed = 0;
    while (start_pop < end_pop)
    {
        start_pop = start_pop + (start_pop / 3) - (start_pop / 4);
        year_passed++;
    }
    
    // TODO: Print number of years
    printf("Years: %i\n", year_passed);
}
