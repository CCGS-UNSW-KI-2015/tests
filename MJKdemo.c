
typedge struct _game {
    struct vertex *vertices;
} * game;







game myGame = malloc(sizeof(struct _game));




alloc:

myGame->vertices = malloc(20 * sizeof(struct vertex));
