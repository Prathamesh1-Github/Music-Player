#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>

struct node
{
    char songName[1000];
    char artistName[1000];
    char genreName[1000];
    char path[1000];
    struct node *left;
    struct node *right;
};

struct node *createNode(char songName[], char artistName[], char genreName[], char path[])
{
    struct node *n;
    n = (struct node *)malloc(sizeof(struct node));
    strcpy(n->songName, songName);
    strcpy(n->artistName, artistName);
    strcpy(n->genreName, genreName);
    strcpy(n->path, path);
    n->left = NULL;
    n->right = NULL;
    return n;
}

struct node *insertNode(struct node *root, char songName[], char artistName[], char genreName[], char path[])
{
    if (root == NULL)
    {
        root = createNode(songName, artistName, genreName, path);
        return root;
    }
    int result = strcmp(artistName, root->artistName);
    // printf("\n");
    // printf("%d\n", result);
    // printf("artistName: %s  and  root->artistName: %s   and  result: %d\n", artistName, root->artistName, result);
    // printf("%s and %s result is %d: \n", name, root->name, result);
    if (result <= 0)
    {
        root->left = insertNode(root->left, songName, artistName, genreName, path);
    }
    else
    {
        root->right = insertNode(root->right, songName, artistName, genreName, path);
    }
    return root;
}

struct node *search(struct node *root, char artistName[])
{
    if (root == NULL)
    {
        return NULL;
    }
    int result = strcmp(artistName, root->artistName);
    if (result == 0)
    {
        return root;
    }
    else if (result < 0)
    {
        return search(root->left, artistName);
    }
    else
    {
        return search(root->right, artistName);
    }
}

void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s ", root->songName);
        printf("%s ", root->artistName);
        printf("%s ", root->genreName);
        printf("%s ", root->path);
        printf("\n");
        inorder(root->right);
    }
}

void showArtistSongs(struct node *root, char artistName[])
{
    if (root != NULL)
    {
        showArtistSongs(root->left, artistName);
        int result = strcmp(artistName, root->artistName);
        if (result == 0)
        {
            printf("%s ", root->songName);
            printf("%s ", root->artistName);
            printf("%s ", root->genreName);
            printf("\n");
        }
        showArtistSongs(root->right, artistName);
    }
}

void playSong(struct node *root, char songName[], char* songPath)
{
    // char *songPath[1000];
    if (root != NULL)
    {
        playSong(root->left, songName, songPath);
        int result = strcmp(songName, root->songName);
        // printf("\nStringOne = %s and StringTwo = %s and result = %d\n", songName, root->songName, result);
        // printf("\n%d ", result);
        if (result == 0)
        {
            printf("%s ", root->songName);
            printf("%s ", root->artistName);
            printf("%s ", root->genreName);
            printf("%s ", root->path);
            printf("\n");
            strcpy(songPath, root->path);
            // songPath = root->path;
        }
        playSong(root->right, songName, songPath);
    }
    // return "songPath";
}

int main()
{
    struct node *root;
    root = NULL;
    // char songName[1000]; char artistName[1000]; char genreName[1000];
    // printf("Enter the song name:\n");
    // // scanf("%s", &name);
    // scanf("%c", (char *) stdin);
    // fgets(songName,1000,stdin);
    // printf("Enter the artist name:\n");
    // // scanf("%s", &name);
    // scanf("%c", (char *) stdin);
    // fgets(artistName,1000,stdin);
    // printf("Enter the genre name:\n");
    // // scanf("%s", &name);
    // scanf("%c", (char *) stdin);
    // fgets(genreName,1000,stdin);
    root = insertNode(root, "Jeet", "Ritviz", "Electronic", "path");
    root = insertNode(root, "Kesariya", "Arijit Singh", "Romantic", "Kesariyapath");
    root = insertNode(root, "Khali Salam Dua", "Himensh rashamiya", "Romantic", "path");
    root = insertNode(root, "Tere Liye", "Atif Aslam", "Romantic", "path");
    root = insertNode(root, "Baaraat", "Ritviz", "Electronic", "path");
    root = insertNode(root, "Tere Pyar Mein", "Arijit Singh", "Romantic", "path");

    inorder(root);

    char artistName[1000];
    printf("Enter arist name: \n");
    scanf("%[^\n]%*c", &artistName);
    printf("%s \n", artistName);
    printf("\n");
    showArtistSongs(root, artistName);

    printf("\n");
    char songToPlay[1000];
    printf("Enter the song to be played: \n");
    scanf("%[^\n]%*c", &songToPlay);

    printf("%s", songToPlay);

    char *songPath;
    playSong(root, songToPlay, songPath);
    // char songPath[1000] = playSong(root, songToPlay);
    // strcpy(songPath, playSong(root, songToPlay));
    printf("\n Song Path = %s", songPath);
}