#include <stdio.h>
#include <string.h>

/// @param side the length of the square's side
/// @param indent the number of spaces from the left edge to ident the square
/// @param ch the character to use for the square
void draw_square(int side, int indent, char ch) {
    for (int i = 0; i < side; i++) {
        for (int k = 0; k < indent; k++) {
            printf(" ");
        }

        for (int j = 0; j < side; j++) {
            printf("%c", ch);
        }
        printf("\n");
    }

    printf("\n");
}

int main( void ) {
    draw_square(3, 2, '#');
    draw_square(5, 4, '*');
    draw_square(8, 3, '+');

    return 0;
}
