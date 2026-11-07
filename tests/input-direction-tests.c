/*
 * This file is part of the OpenSupaplex distribution (https://github.com/sergiou87/open-supaplex).
 * Copyright (c) 2026 Sergio Padrino
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#define main opensupaplex_main
#include "../src/supaplex.c"
#undef main

static UserInput parseExpectedInput(const char *name, int *ok)
{
    *ok = 1;
    if (strcmp(name, "none") == 0) return UserInputNone;
    if (strcmp(name, "up") == 0) return UserInputUp;
    if (strcmp(name, "down") == 0) return UserInputDown;
    if (strcmp(name, "left") == 0) return UserInputLeft;
    if (strcmp(name, "right") == 0) return UserInputRight;
    *ok = 0;
    return UserInputNone;
}

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-u") != 0)
    {
        fprintf(stderr, "Usage: input-direction-tests -u <input-case.csv>\n");
        return 2;
    }
    FILE *file = fopen(argv[2], "r");
    if (file == NULL)
    {
        perror(argv[2]);
        return 2;
    }

    char line[256];
    if (fgets(line, sizeof(line), file) == NULL
        || strcmp(line, "frame,up,down,left,right,expected\n") != 0)
    {
        fprintf(stderr, "Invalid input case header\n");
        fclose(file);
        return 2;
    }

    int result = 0;
    unsigned row = 0;
    while (result == 0 && fgets(line, sizeof(line), file))
    {
        unsigned frame, up, down, left, right;
        char expectedName[16];
        int ok = 0;
        UserInput expected = UserInputNone;
        if (sscanf(line, "%u,%u,%u,%u,%u,%15s", &frame, &up, &down, &left, &right, expectedName) == 6
            && up <= 1 && down <= 1 && left <= 1 && right <= 1)
        {
            expected = parseExpectedInput(expectedName, &ok);
        }
        if (ok == 0)
        {
            fprintf(stderr, "Invalid input case row %u\n", row + 1);
            result = 2;
            break;
        }

        gIsUpKeyPressed = up;
        gIsDownKeyPressed = down;
        gIsLeftKeyPressed = left;
        gIsRightKeyPressed = right;
        updateUserInput();
        if (gCurrentUserInput != expected)
        {
            fprintf(stderr, "Frame %u: expected %s, got input %u\n", frame, expectedName, gCurrentUserInput);
            result = 1;
        }
        ++row;
    }
    fclose(file);

    if (result == 0)
    {
        printf("Direction input matched: %s\n", argv[2]);
    }
    return result;
}
