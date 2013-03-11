/*
 *  translator.h
 *
 *  Ian Shearin
 *  CS480
 */
#ifndef TRANSLATOR_H
#define TRANSLATOR_H




#include "token.h"
#include "tree.h"

#include <stdlib.h>




/* Data types. */




/* Prototypes. */
void translator_translate(tree_t *tree);
void translator_postorder(tree_node_t *node);




#endif /* TRANSLATOR_H */
