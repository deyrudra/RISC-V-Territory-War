#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// Global Variable
int count = 0;

// Define the Pixel structure
typedef struct {
    int x, y;
    unsigned short rgb_565;
} Pixel;

// Define the Row structure
typedef struct {
    Pixel *pixels; // Dynamically allocated array of pixels
} Row;

// Define the Asset structure
typedef struct {
    Row *data_array; // Dynamically allocated array of rows
    int width;
    int height;
} Asset;

// Function to convert 8-bit RGB to 5-6-5 format
unsigned short rgb_to_565(unsigned char r, unsigned char g, unsigned char b) {
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

// Function to remove the directory path and .ppm extension from the filename
void get_base_filename(const char *filepath, char *base_filename) {
    const char *filename_start = strrchr(filepath, '/');
    if (filename_start) {
        filename_start++; // Move past the '/'
    } else {
        filename_start = filepath; // No directory path
    }

    // Copy the filename without the directory path
    strncpy(base_filename, filename_start, 256);
    base_filename[255] = '\0'; // Ensure null-termination

    // Remove the .ppm extension
    char *dot = strrchr(base_filename, '.');
    if (dot && strcmp(dot, ".ppm") == 0) {
        *dot = '\0'; // Remove the .ppm extension
    }
}

// Function to process a single PPM file and write output to a file
void process_ppm_file(const char *filepath, FILE *output_file) {
    FILE *file = fopen(filepath, "r");

    char format[3];
    int width, height, max_val;

    // Read the PPM header
    fscanf(file, "%2s", format);
    fscanf(file, "%d %d", &width, &height);
    fscanf(file, "%d", &max_val);

    // Dynamically allocate memory for the Asset
    Asset img;
    img.width = width;
    img.height = height;

    img.data_array = malloc(height * sizeof(Row));
    for (int y = 0; y < height; y++) {
        img.data_array[y].pixels = malloc(width * sizeof(Pixel));
    }

    // Read pixel data
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r, g, b;
            fscanf(file, "%hhu %hhu %hhu", &r, &g, &b);
            img.data_array[y].pixels[x].x = x;
            img.data_array[y].pixels[x].y = y;
            img.data_array[y].pixels[x].rgb_565 = rgb_to_565(r, g, b);
        }
    }
    fclose(file);

    // Get the base filename (without directory path and .ppm extension)
    char base_filename[256];
    get_base_filename(filepath, base_filename);

    // Write the output to the specified file
    fprintf(output_file, "Asset %s = {\n", base_filename);
    fprintf(output_file, "    .data_array = {\n");
    for (int y = 0; y < height; y++) {
        fprintf(output_file, "        {   // Row %d\n", y);
        for (int x = 0; x < width; x++) {
            fprintf(output_file, "            { .x = %d, .y = %d, .rgb_565 = 0x%04X }", img.data_array[y].pixels[x].x, img.data_array[y].pixels[x].y, img.data_array[y].pixels[x].rgb_565);
            if (x < width - 1) {
                fprintf(output_file, ",");
            }
            fprintf(output_file, "  // Pixel (%d,%d)\n", x, y);
        }
        fprintf(output_file, "        }");
        if (y < height - 1) {
            fprintf(output_file, ",");
        }
        fprintf(output_file, "\n");
    }
    fprintf(output_file, "    },\n");
    fprintf(output_file, "    .width = %d,\n", img.width);
    fprintf(output_file, "    .height = %d\n", img.height);
    fprintf(output_file, "};\n\n");
    // fprintf(output_file, "%s = asset%d;", base_filename, count);

    // Free allocated memory
    for (int y = 0; y < height; y++) {
        free(img.data_array[y].pixels);
    }
    free(img.data_array);
}

int main() {
    const char *directory = "../assets"; // Directory containing .ppm files
    const char *output_filepath1 = "../game/assets.txt"; // Output file path

    // Open the output file for writing
    FILE *output_file = fopen(output_filepath1, "w");
    if (!output_file) {
        fprintf(stderr, "Failed to open output file: %s\n", output_filepath1);
        return 1;
    }

    DIR *dir = opendir(directory);
    if (!dir) {
        fprintf(stderr, "Failed to open directory: %s\n", directory);
        fclose(output_file);
        return 1;
    }
    
    // Creating assets.c
    struct dirent *entry;
    
    // while ((entry = readdir(dir)) != NULL) {
    //     // Check if the file has a .ppm extension
    //     const char *extension = strrchr(entry->d_name, '.');
    //     if (extension && strcmp(extension, ".ppm") == 0) {
    //         // Construct the full file path
    //         char filepath[1024];
    //         snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);
            
    //         char base_filename[256];
    //         get_base_filename(filepath, base_filename);
            
    //         // Write the output to the specified file
    //         fprintf(output_file, "Asset %s;\n", base_filename);
    //     }
    // }
    
    dir = opendir(directory);

    while ((entry = readdir(dir)) != NULL) {
        // Check if the file has a .ppm extension
        const char *extension = strrchr(entry->d_name, '.');
        if (extension && strcmp(extension, ".ppm") == 0) {
            // Construct the full file path
            char filepath[1024];
            snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);

            // Process the PPM file and write output to the file
            process_ppm_file(filepath, output_file);
            count++;
            
        }
    }

    fclose(output_file);
    closedir(dir);

    printf("Output written to %s\n", output_filepath1);
    return 0;
}