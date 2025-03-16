#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Pixel structure
typedef struct {
    int x, y;
    unsigned short rgb_565;
} Pixel;

// Define the Row structure
typedef struct {
    Pixel *pixels; // Dynamically allocated array of pixels
} Row;

// Define the Image structure
typedef struct {
    Row *data_array; // Dynamically allocated array of rows
    int width;
    int height;
} Image;

// Function to convert 8-bit RGB to 5-6-5 format
unsigned short rgb_to_565(unsigned char r, unsigned char g, unsigned char b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

// Function to remove the .ppm extension from the filename
void remove_extension(char *filename) {
    char *dot = strrchr(filename, '.');
    if (dot && strcmp(dot, ".ppm") == 0) {
        *dot = '\0'; // Remove the .ppm extension
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input.ppm>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    char format[3];
    int width, height, max_val;

    // Read the PPM header
    if (fscanf(file, "%2s", format) != 1 || format[0] != 'P' || format[1] != '3') {
        fprintf(stderr, "Invalid PPM format. Expected P3.\n");
        fclose(file);
        return 1;
    }

    // Read image dimensions
    if (fscanf(file, "%d %d", &width, &height) != 2) {
        fprintf(stderr, "Failed to read image dimensions.\n");
        fclose(file);
        return 1;
    }

    // Read maximum color value
    if (fscanf(file, "%d", &max_val) != 1) {
        fprintf(stderr, "Failed to read maximum color value.\n");
        fclose(file);
        return 1;
    }

    // Dynamically allocate memory for the image
    Image img;
    img.width = width;
    img.height = height;

    img.data_array = malloc(height * sizeof(Row));
    if (!img.data_array) {
        perror("Failed to allocate memory for image rows");
        fclose(file);
        return 1;
    }

    for (int y = 0; y < height; y++) {
        img.data_array[y].pixels = malloc(width * sizeof(Pixel));
        if (!img.data_array[y].pixels) {
            perror("Failed to allocate memory for image pixels");
            // Free previously allocated memory
            for (int i = 0; i < y; i++) {
                free(img.data_array[i].pixels);
            }
            free(img.data_array);
            fclose(file);
            return 1;
        }
    }

    // Read pixel data
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r, g, b;
            if (fscanf(file, "%hhu %hhu %hhu", &r, &g, &b) != 3) {
                fprintf(stderr, "Failed to read pixel data at (%d, %d).\n", x, y);
                // Free allocated memory
                for (int i = 0; i < height; i++) {
                    free(img.data_array[i].pixels);
                }
                free(img.data_array);
                fclose(file);
                return 1;
            }
            img.data_array[y].pixels[x].x = x;
            img.data_array[y].pixels[x].y = y;
            img.data_array[y].pixels[x].rgb_565 = rgb_to_565(r, g, b);
        }
    }
    fclose(file);

    // Remove the .ppm extension from the filename
    char filename[256];
    strncpy(filename, argv[1], sizeof(filename) - 1);
    filename[sizeof(filename) - 1] = '\0'; // Ensure null-termination
    remove_extension(filename);

    // Print the output in the specified format
    printf("Image %s = {\n", filename);
    printf("    .data_array = {\n");
    for (int y = 0; y < height; y++) {
        printf("        {   // Row %d\n", y);
        for (int x = 0; x < width; x++) {
            printf("            { .x = %d, .y = %d, .rgb_565 = 0x%04X }", img.data_array[y].pixels[x].x, img.data_array[y].pixels[x].y, img.data_array[y].pixels[x].rgb_565);
            if (x < width - 1) {
                printf(",");
            }
            printf("  // Pixel (%d,%d)\n", x, y);
        }
        printf("        }");
        if (y < height - 1) {
            printf(",");
        }
        printf("\n");
    }
    printf("    },\n");
    printf("    .width = %d,\n", img.width);
    printf("    .height = %d\n", img.height);
    printf("};\n");

    // Free allocated memory
    for (int y = 0; y < height; y++) {
        free(img.data_array[y].pixels);
    }
    free(img.data_array);

    return 0;
}