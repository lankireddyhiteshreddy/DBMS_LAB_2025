#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define MAX 10

typedef struct
{
    char left[10];
    char right[10];
} FD;

char attributes[MAX];
FD fds[MAX];
int nAttr, nFD;

// Compute closure of a set
void closure(char *subset, char *result)
{
    strcpy(result, subset); // start with same set
    bool changed = true;

    while (changed)
    {
        changed = false;
        for (int i = 0; i < nFD; i++)
        {
            // check if LHS of FD is inside result
            bool ok = true;
            for (int k = 0; fds[i].left[k]; k++)
            {
                if (strchr(result, fds[i].left[k]) == NULL)
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
            {
                int before = strlen(result);
                // add RHS into result if not present
                for (int k = 0; fds[i].right[k]; k++)
                {
                    if (strchr(result, fds[i].right[k]) == NULL)
                    {
                        int len = strlen(result);
                        result[len] = fds[i].right[k];
                        result[len + 1] = '\0';
                        changed = true;
                    }
                }
                if (strlen(result) > before)
                    changed = true;
            }
        }
    }
}

// Check if a set is superkey
bool isSuperKey(char *subset)
{
    char res[20] = "";
    closure(subset, res);
    for (int i = 0; i < nAttr; i++)
    {
        if (strchr(res, attributes[i]) == NULL)
            return false;
    }
    return true;
}

void findKeys()
{
    int total = (int)pow(2, nAttr);
    char superKeys[100][20];
    int skCount = 0;

    printf("\nSuper Keys:\n");
    for (int mask = 1; mask < total; mask++)
    {
        char subset[20] = "";
        for (int j = 0; j < nAttr; j++)
        {
            if (mask & (1 << j))
            {
                int len = strlen(subset);
                subset[len] = attributes[j];
                subset[len + 1] = '\0';
            }
        }

        if (isSuperKey(subset))
        {
            printf("%s ", subset);
            strcpy(superKeys[skCount++], subset);
        }
    }

    printf("\n\nCandidate Keys:\n");
    for (int i = 0; i < skCount; i++)
    {
        bool minimal = true;
        for (int j = 0; j < skCount; j++)
        {
            if (i != j && strlen(superKeys[j]) < strlen(superKeys[i]))
            {
                // check if smaller key is subset of bigger one
                bool allIn = true;
                for (int k = 0; superKeys[j][k]; k++)
                {
                    if (strchr(superKeys[i], superKeys[j][k]) == NULL)
                    {
                        allIn = false;
                        break;
                    }
                }
                if (allIn)
                {
                    minimal = false;
                    break;
                }
            }
        }
        if (minimal)
            printf("%s ", superKeys[i]);
    }
    printf("\n");
}

int main()
{
    // ---------- Example 1 ----------
    printf("Example 1:\n");
    strcpy(attributes, "XYZW");
    nAttr = strlen(attributes);
    nFD = 3;
    strcpy(fds[0].left, "XYZ");
    strcpy(fds[0].right, "W");
    strcpy(fds[1].left, "XY");
    strcpy(fds[1].right, "ZW");
    strcpy(fds[2].left, "X");
    strcpy(fds[2].right, "YZW");
    findKeys();

    // ---------- Example 2 ----------
    printf("\nExample 2:\n");
    strcpy(attributes, "XYZW");
    nAttr = strlen(attributes);
    nFD = 3;
    strcpy(fds[0].left, "X");
    strcpy(fds[0].right, "Y");
    strcpy(fds[1].left, "Y");
    strcpy(fds[1].right, "Z");
    strcpy(fds[2].left, "Z");
    strcpy(fds[2].right, "X");
    findKeys();

    return 0;
}
