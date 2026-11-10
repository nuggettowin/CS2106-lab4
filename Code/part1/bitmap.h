/* Bitmap management 
 
   The bitmap should be an array of unsigned char.
 
 */

// Utility function to print out an array of char as bits
// Print the entire bitmap.
// Each bit of the bitmap represents 1 byte of memory. 0 = free, 1 = allocated.
void print_map(unsigned char *, int);

// Search the bitmap for the required number of zeroes (representing free bytes of memory).
// Returns index of first stretch of 0s that meet the criteria.
int search_map(unsigned char *, int, int);

// Set a sequence of consecutive bits to 0 or 1.
void setmap(unsigned char *, int, int, int);

// Marks a stretch of bits as "1", representing allocated memory
void allocate_map(unsigned char *, int, int);

// Marks a stretch of bits as "0", representing allocated memory
void free_map(unsigned char *, int, int);
