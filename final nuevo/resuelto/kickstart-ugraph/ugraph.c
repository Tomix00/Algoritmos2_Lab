#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>            /* Definition of bool      */
#include <assert.h>


#include "ugraph.h"

struct s_node {
    vertex elem;
    struct s_node *next;
    struct s_node *succ;

};

typedef struct s_node *node_t;

struct s_ugraph {
    unsigned int size;
    node_t first;
};


static bool invrep1(ugraph g){
	//about main structre consistency
	return g!=NULL;
}

static bool invrep2(ugraph g){
	//about graph size consistency
	node_t node = g->first;
	unsigned int n = 0;
    while (node!=NULL) {
        node = node->next;
        n++;
    }
    return n == g->size;
}

static bool invrep3(ugraph g){
	//about uniqueness of vertexes
	bool b;
	b = true;
	if(!ugraph_is_empty(g)){
		node_t aux1 = NULL;
		node_t aux2 = NULL;

		aux1 = g->first;
		aux2 = aux1->next;
		
		while(aux1->next != NULL && b){
			if(aux2 != NULL){
				while(aux2->next != NULL && b){
					if(aux1->elem == aux2->elem){
						b = false;
					}else{
						aux2 = aux2->next;
					}
				}
				aux1 = aux1->next;
				aux2 = aux1->next;
			}else{
				aux1 = aux1->next;
			}
		}
	}

	return b;
}

static bool invrep(ugraph g){
	return invrep1(g) && invrep2(g) && invrep3(g);
}


static node_t create_node(vertex v){
	node_t new_node = NULL;
	new_node = malloc(sizeof(struct s_node));

	new_node->elem = v;
	new_node->next = NULL;
	new_node->succ = NULL;

	return new_node;
}


static node_t destroy_node(struct s_node *node){
	
	if(node != NULL){
		free(node);
		node = NULL;
	}
	
	return node;
}

static node_t ugraph_get_node(ugraph g,vertex v){
	/*Returns the node of the vertex v*/
	assert(invrep(g) && ugraph_member(g,v));
	node_t node = g->first;
	while (node!=NULL && node->elem != v) {
		node = node->next;
	}
	assert(invrep(g));
	return node;
}


/****************** CONSTRUCTORS ******************/
ugraph ugraph_empty(void) {
	ugraph new_ugraph = NULL;
	new_ugraph = malloc(sizeof(struct s_ugraph));

	new_ugraph->size = 0;
	new_ugraph->first = NULL;

	assert(new_ugraph != NULL);
	return new_ugraph;
}

ugraph ugraph_add_vertex(ugraph g, vertex v) {
	assert(invrep(g));

	node_t new_node = NULL;
	new_node = create_node(v);


	if(ugraph_is_empty(g)){
		g->first = new_node;
		g->size++;
	}else{
		if(!ugraph_member(g,v)){
			node_t aux = NULL;
			aux = g->first;
			new_node->next = aux;
			g->first = new_node;


			g->size++;
		}
	}


	assert(invrep(g));
	return g;
}


ugraph ugraph_add_edge(ugraph g, vertex v1, vertex v2){
	assert(invrep(g));

	if(ugraph_member(g,v1) && ugraph_member(g,v2)){
		node_t v1_node = ugraph_get_node(g,v1);
		node_t new_succ = NULL;
		new_succ = ugraph_get_node(g,v2);
		v1_node->succ = new_succ;
	}

	assert(invrep(g));
	return g;
}


/******************* OPERATIONS   *******************/
unsigned int ugraph_size(ugraph g){
	assert(invrep(g));
    return g->size;
}

bool ugraph_is_empty(ugraph g){
    return g->size==0;
}

bool ugraph_member(ugraph g, vertex v) {
	assert(invrep(g));

	bool has_it;
	has_it = false;

	if(!ugraph_is_empty(g)){
		node_t nodo = NULL;
		nodo = g->first;

		while(nodo->next != NULL && !has_it){
			if(nodo->elem == v){
				has_it = true;
			}else{
				nodo = nodo->next;
			}
		}
	}
	
	return has_it;
}


vertex ugraph_succ(ugraph g, vertex v){
	assert(invrep(g) && ugraph_get_node(g,v)->succ !=NULL);
	node_t node_v = ugraph_get_node(g,v);
	assert(invrep(g));
	return node_v->succ->elem;
}

ugraph ugraph_delete_incoming_edge(ugraph g, vertex v){
	assert(invrep(g));
	if (ugraph_member(g,v)){
		node_t node_v = ugraph_get_node(g,v);
		node_t node = g->first;
		while (node!=NULL){
			if (node->succ == node_v){
				node->succ = NULL;
			}
			node = node->next;
		}
	}
	assert(invrep(g));
	return g;		
}

ugraph ugraph_delete_outcoming_edge(ugraph g, vertex v){
	assert(invrep(g) && ugraph_member(g,v));
	node_t node_v = ugraph_get_node(g,v);
	node_v->succ = NULL;
	assert(invrep(g) && ugraph_get_node(g,v)->succ == NULL);
	return g;		
}


ugraph ugraph_delete_vertex(ugraph g, vertex v){
	assert(invrep(g));

	if(ugraph_member(g,v)){
		g = ugraph_delete_incoming_edge(g,v);
		g = ugraph_delete_outcoming_edge(g,v);
		g->size--;

		node_t aux = NULL;
		node_t aux2 = NULL;
		bool found = false;

		aux = g->first;

		while(aux->next != NULL && !found){
			aux2 = aux->next;
			if(aux->elem != v){
				
				aux->next = aux2->next;
				aux2 = destroy_node(aux2);
				aux2 = NULL;

				found = true;
			}else{
				aux = aux->next;	
			}
		}

	}

	return g;
}



bool ugraph_path(ugraph g, vertex v1, vertex v2){
	bool has_path;
	has_path = false;

	if(!ugraph_is_empty(g)){
		if(ugraph_member(g,v1) && ugraph_member(g,v2)){
			node_t v1_node = ugraph_get_node(g,v1);
			node_t aux = NULL;
			aux = v1_node->succ;
			while(aux != NULL && !has_path){
				if(aux->elem == v2){
					has_path = true;
				}else{
					aux = aux->succ;
				}
			}
		}

	}
	return has_path;
}



ugraph ugraph_destroy(ugraph g){
	assert(invrep(g));

	if(!ugraph_is_empty(g)){
		node_t aux = NULL;
		node_t kill_me = NULL;
		aux = g->first;

		while(aux->next != NULL){
			kill_me = aux;
			aux = aux->next;
			g = ugraph_delete_vertex(g,kill_me->elem);
		}
	}
	free(g);
	g = NULL;
	
	return g;
}



void ugraph_dump(ugraph g){
	assert(invrep(g));
    // prints the set of vertexes of the unary graph g
    node_t node = g->first;
    printf("Vertexes: ");
    while (node!=NULL ) {
	   printf("%d ", node->elem);
        node = node->next;
    }
    printf("\n");
    // prints the list of edges of the unary graph g
    printf("Edges: \n");
    node = g->first;
    while (node!=NULL ) {
    	if (node->succ != NULL) {
        	printf("\t%d --> %d\n", node->elem, node->succ->elem);
        }
        node = node->next;
    }
   	assert(invrep(g));
}


ugraph ugraph_from_file(const char *filepath){
    FILE *file = NULL;
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

	//read ugraph size
	int size;
    int res = fscanf(file,"%d", &size);
    if (res != 1) {
    	fprintf(stderr, "Invalid unary graph.\n");
        exit(EXIT_FAILURE);
    }
        
	//load ugraph vertexes
    ugraph g=ugraph_empty();
    int i = 1;
    while (i<=size){
        int elem;
        int res = fscanf(file,"%d", &elem);
        if (res != 1) {
            fprintf(stderr, "1-Invalid unary graph.\n");
            exit(EXIT_FAILURE);
        }
        g = ugraph_add_vertex(g, elem);
        i++;
		
	}
	//load ugraph edges
	int v1;
	int v2;

    while (!feof(file)){
        	int res = fscanf(file,"%d --> %d",&v1,&v2);
			if(res != 2){
				fprintf(stderr, "1-Invalid edge format.\n");
            	exit(EXIT_FAILURE);
			}
			g = ugraph_add_edge(g,v1,v2);
    }
    fclose(file);
   	assert(invrep(g));
    return g;
}


/*SOLO PARA ALUMNOS LIBRES!!!*/
	/*bool ugraph_cycle(ugraph g){
       	COMPLETAR!!! 
	}*/




