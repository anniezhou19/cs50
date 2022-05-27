#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;
bool isjpg(BYTE block[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }
    
    // open memory card
    FILE *inptr = fopen(argv[1], "r");
    
    if (inptr == NULL)
    {
        printf("Could not open\n");
        return 1;
    }
    
    FILE *JPG;
    BYTE block[512];
    bool jpg_found = false;
    int image_count = 0;
    
    // repeat until end of card
    while (fread(block, sizeof(block), 1, inptr))
    {
        // if start of new JPEG
        if (isjpg(block))
        {
            // If first JPEG
            if (jpg_found == true)
            {
                fclose(JPG);
            }
            else
            {
                jpg_found = true;
            }
            
            char filename[8];
            sprintf(filename, "%03i.jpg", image_count);
            printf("%s\n", filename);
            JPG = fopen(filename, "w");
            image_count++;
        }
        if (jpg_found == true)
        {
            fwrite(block, sizeof(block), 1, JPG);
        }
    }
    
    if (JPG == NULL)
    {
        fclose(JPG);
    }
    if (inptr == NULL)
    {
        fclose(inptr);
    }
    return 0;

}

bool isjpg(BYTE block[])
{
    
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}
