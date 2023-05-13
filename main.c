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
    int height;
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
    n->height = 1;
    return n;
}

int max(int a, int b){
    if(a >= b){
        return a;
    }
    else{
        return b;
    }
}

int getHeight(struct node *n){
    if(n == NULL){
        return 0;
    }
    return n->height;
}

int getBalanceFactor(struct node *n){
    if(n == NULL){
        return 0;
    }
    return getHeight(n->left) - getHeight(n->right);
}

struct node *rightRotate(struct node *y){
    struct node *x = y->left;
    struct node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
}

struct node *leftRotate(struct node *x) {
    struct node *y = x->right;
    struct node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

struct node *insertNodeArtist(struct node *root, char songName[], char artistName[], char genreName[], char path[])
{
    if (root == NULL)
    {
        root = createNode(songName, artistName, genreName, path);
        return root;
    }

    int result = strcmp(artistName, root->artistName);
    if (result <= 0)
    {
        root->left = insertNodeArtist(root->left, songName, artistName, genreName, path);
    }
    else
    {
        root->right = insertNodeArtist(root->right, songName, artistName, genreName, path);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    int result1 = (root->left != NULL) ? strcmp(artistName, root->left->artistName) : -1;
    int result2 = (root->right != NULL) ? strcmp(artistName, root->right->artistName) : 1;

    // Left Left Case
    if (bf > 1 && result1 < 0)
    {
        return rightRotate(root);
    }
    // Right Right Case
    if (bf < -1 && result2 > 0)
    {
        return leftRotate(root);
    }
    // Left Right Case
    if (bf > 1 && result1 > 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Left Case
    if (bf < -1 && result2 < 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}


struct node *insertNodeSong(struct node *root, char songName[], char artistName[], char genreName[], char path[])
{
    if (root == NULL)
    {
        root = createNode(songName, artistName, genreName, path);
        return root;
    }
    int result = strcmp(songName, root->songName);
    if (result <= 0)
    {
        root->left = insertNodeSong(root->left, songName, artistName, genreName, path);
    }
    else
    {
        root->right = insertNodeSong(root->right, songName, artistName, genreName, path);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    int result1 = (root->left != NULL) ? strcmp(songName, root->left->songName) : -1;
    int result2 = (root->right != NULL) ? strcmp(songName, root->right->songName) : 1;

    // Left Left Case
    if (bf > 1 && result1 < 0)
    {
        return rightRotate(root);
    }
    // Right Right Case
    if (bf < -1 && result2 > 0)
    {
        return leftRotate(root);
    }
    // Left Right Case
    if (bf > 1 && result1 > 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Left Case
    if (bf < -1 && result2 < 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct node *insertNodeGenre(struct node *root, char songName[], char artistName[], char genreName[], char path[])
{
    if (root == NULL)
    {
        root = createNode(songName, artistName, genreName, path);
        return root;
    }
    int result = strcmp(genreName, root->genreName);
    if (result <= 0)
    {
        root->left = insertNodeSong(root->left, songName, artistName, genreName, path);
    }
    else
    {
        root->right = insertNodeSong(root->right, songName, artistName, genreName, path);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    int result1 = (root->left != NULL) ? strcmp(genreName, root->left->genreName) : -1;
    int result2 = (root->right != NULL) ? strcmp(genreName, root->right->genreName) : 1;

    // Left Left Case
    if (bf > 1 && result1 < 0)
    {
        return rightRotate(root);
    }
    // Right Right Case
    if (bf < -1 && result2 > 0)
    {
        return leftRotate(root);
    }
    // Left Right Case
    if (bf > 1 && result1 > 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Left Case
    if (bf < -1 && result2 < 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct node *searchArtist(struct node *root, char artistName[])
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
        return searchArtist(root->left, artistName);
    }
    else
    {
        return searchArtist(root->right, artistName);
    }
}

struct node *searchSong(struct node *root, char songName[])
{
    if (root == NULL)
    {
        return NULL;
    }
    int result = strcmp(songName, root->songName);
    if (result == 0)
    {
        return root;
    }
    else if (result < 0)
    {
        return searchSong(root->left, songName);
    }
    else
    {
        return searchSong(root->right, songName);
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

void showGenreSongs(struct node *root, char genreName[])
{
    if (root != NULL)
    {
        showGenreSongs(root->left, genreName);
        int result = strcmp(genreName, root->genreName);
        if (result == 0)
        {
            printf("%s ", root->songName);
            printf("%s ", root->artistName);
            printf("%s ", root->genreName);
            printf("\n");
        }
        showGenreSongs(root->right, genreName);
    }
}

void playSong(struct node *root, char songName[], char* songPath)
{
    if (root != NULL)
    {
        playSong(root->left, songName, songPath);
        int result = strcmp(songName, root->songName);
        if (result == 0)
        {
            printf("Function %s \n", root->songName);
            printf("\n");
            strcpy(songPath, root->path);
            return;
        }
        playSong(root->right, songName, songPath);
    }
}

void inorderSong(struct node *root){
    if(root != NULL){
        inorderSong(root->left);
        printf("%s ", root->songName);
        inorderSong(root->right);
    }
}

void inorderArtist(struct node *root){
    if(root != NULL){
        inorderArtist(root->left);
        printf("%s ", root->artistName);
        inorderArtist(root->right);
    }
}
void inorderGenre(struct node *root){
    if(root != NULL){
        inorderGenre(root->left);
        printf("%s ", root->genreName);
        inorderGenre(root->right);
    }
}

int main()
{
    struct node *rootSong = NULL;
    struct node *rootArtist = NULL;
    struct node *rootGenre = NULL;

    rootArtist = insertNodeArtist(rootArtist, "Jeet", "Ritviz", "Electronic", "Jeetpath");
    rootArtist = insertNodeArtist(rootArtist, "Kesariya", "Arijit Singh", "Romantic", "Kesariyapath");
    rootArtist = insertNodeArtist(rootArtist, "Khali Salam Dua", "Himensh rashamiya", "Romantic", "KhaliSalampath");
    rootArtist = insertNodeArtist(rootArtist, "Tere Liye", "Atif Aslam", "Romantic", "TereLiyepath");
    rootArtist = insertNodeArtist(rootArtist, "Baaraat", "Ritviz", "Electronic", "Baaratpath");
    rootArtist = insertNodeArtist(rootArtist, "Tere Pyar Mein", "Arijit Singh", "Romantic", "TerePyarMenepath");


    rootGenre = insertNodeGenre(rootGenre, "Jeet", "Ritviz", "Electronic", "Jeetpath");
    rootGenre = insertNodeGenre(rootGenre, "Kesariya", "Arijit Singh", "Romantic", "Kesariyapath");
    rootGenre = insertNodeGenre(rootGenre, "Khali Salam Dua", "Himensh rashamiya", "Romantic", "KhaliSalampath");
    rootGenre = insertNodeGenre(rootGenre, "Tere Liye", "Atif Aslam", "Romantic", "TereLiyepath");
    rootGenre = insertNodeGenre(rootGenre, "Baaraat", "Ritviz", "Electronic", "Baaratpath");
    rootGenre = insertNodeGenre(rootGenre, "Tere Pyar Mein", "Arijit Singh", "Romantic", "TerePyarMenepath");


    rootSong = insertNodeSong(rootSong, "Jeet", "Ritviz", "Electronic", "Jeetpath");
    rootSong = insertNodeSong(rootSong, "Kesariya", "Arijit Singh", "Romantic", "Kesariyapath");
    rootSong = insertNodeSong(rootSong, "Khali Salam Dua", "Himensh rashamiya", "Romantic", "KhaliSalampath");
    rootSong = insertNodeSong(rootSong, "Tere Liye", "Atif Aslam", "Romantic", "TereLiyepath");
    rootSong = insertNodeSong(rootSong, "Baaraat", "Ritviz", "Electronic", "Baaratpath");
    rootSong = insertNodeSong(rootSong, "Tere Pyar Mein", "Arijit Singh", "Romantic", "TerePyarMenepath");

    printf("***** Artist Tree *****\n");
    inorderArtist(rootArtist);
    printf("\n");

    printf("***** Genre Tree *****\n");
    inorderGenre(rootGenre);
    printf("\n");

    printf("***** Song Tree *****\n");
    inorderSong(rootSong);
    printf("\n");

    printf("\n");
    printf("\n");
    printf("\n");


    printf("Press 1 : to play via song name\nPress 2 : to play via aritst name\nPress 3 : to play via genre name\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("\n");
    if(choice == 1){
        printf("\n");
        char songToPlay[1000];
        printf("Enter the song to be played: \n");
        scanf(" %[^\n]%*c", songToPlay);  // Remove the & operator before songToPlay

        printf("%s\n", songToPlay);

        char songPath[1000];
        playSong(rootArtist, songToPlay, songPath);
        printf("\n Song Path = %s", songPath);
    }
    else if (choice == 2) {
        char artistName[1000];
        printf("Enter artist name: \n");
        scanf(" %[^\n]%*c", artistName);  // Remove the & operator before artistName
        printf("%s \n", artistName);
        printf("\n");
        showArtistSongs(rootArtist, artistName);

        printf("\n");
        char songToPlay[1000];
        printf("Enter the song to be played: \n");
        scanf(" %[^\n]%*c", songToPlay);  // Remove the & operator before songToPlay

        printf("%s\n", songToPlay);

        char songPath[1000];
        playSong(rootArtist, songToPlay, songPath);
        printf("\n Song Path = %s", songPath);
    }
    else if(choice == 3){
        char genreName[1000];
        printf("Enter genre name: \n");
        scanf(" %[^\n]%*c", genreName);  // Remove the & operator before artistName
        printf("%s \n", genreName);
        printf("\n");
        showGenreSongs(rootArtist, genreName);

        printf("\n");
        char songToPlay[1000];
        printf("Enter the song to be played: \n");
        scanf(" %[^\n]%*c", songToPlay);  // Remove the & operator before songToPlay

        printf("%s\n", songToPlay);

        char songPath[1000];
        playSong(rootArtist, songToPlay, songPath);
        printf("\n Song Path = %s", songPath);
    }

}
