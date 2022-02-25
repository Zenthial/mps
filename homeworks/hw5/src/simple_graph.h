// file: simple_graph.h
// description: 
// definitions, structures and interface for an adjacency list graph
// author: bksteele, bks@cs.rit.edu
// date: 9/24/2017
// updated: 2/21/2022

#ifndef SIMPLE_GRAPH_
#define SIMPLE_GRAPH_

#include <stdio.h>                      // FILE
#include <object_list.h>                // linked list utility module

#define MAX_NAME  100                   /// maximum length of a node name

#define MAX_FILE_LINE_LENGTH 2000       ///< maximum file line length

/// GraphNode represents a single, simple graph node using 
/// an adjacency list with a variable number of neighbors.
/// The simple graph uses ObjectList, an unordered, dynamic list module,
/// to store both the list of nodes in a graph and the list of 
/// adjacent, neighboring nodes for a given node in the graph.
/// @see ObjectList

typedef struct GraphNode_S {
    char name[MAX_NAME];                ///< name of the node instance
    ObjectList * neighbors;             ///< neighbors of instance
} GraphNode;

/// grh_create_node creates a graph node in dynamic storage.
/// The new node instance will have a copy of the name passed in.
/// @param name a C string name for the note to create
/// @return pointer to the new node instance
/// @pre-condition name is not NULL

GraphNode * grh_create_node( char * name );

/// grh_delete_node deletes the given node.
/// Note: due to potential cycles, the deletion cannot follow the neighbors.
/// To ensure destruction of all dynamic memory, it is necessary for
/// applications using this module to maintain a comprehensive list of
/// all nodes created.
/// @param node pointer to the node to delete
/// @pre-condition node is not NULL and is a pointer to a GraphNode instance

void grh_delete_node( GraphNode * node );

/// grh_delete_graph will delete the entire list of graph nodes.
/// @param graph pointer to an ObjectList of GraphNode(s)
/// @pre-condition graph is not NULL and is a pointer to an ObjectList

void grh_delete_graph( ObjectList * graph );

/// grh_find_node_by_name searches the graph (a list of GraphNode) for
/// the node whose name matches the input name.
/// @param graph pointer to the list of graph nodes
/// @param name C string of the name of the node to find
/// @return pointer to the GraphNode instance or NULL if not found
/// @pre-condition graph is not NULL and name is not NULL

GraphNode * grh_find_node_by_name( ObjectList * graph, char * name );

/// grh_print_graph
/// @param graph pointer to the list of nodes in the graph
/// @pre-condition graph is not NULL and list is NULL terminated

void grh_print_graph( ObjectList * graph );

/// grh_load_file loads data from the input stream and creates 
/// zero or more graph nodes, which it adds to the graph.
/// @param graph pointer to a list of nodes in the graph
/// @param input pointer to a stream of node information to put into the graph
/// @pre-condition graph is not NULL and is a pointer to an ObjectList
/// @pre-condition input has been opened for reading

void grh_load_file( ObjectList * graph, FILE * input );

#endif // SIMPLE_GRAPH_
