//
// Created by bolnykh on 12/7/15.
//

#ifndef MIMICCOMMLIB_MESSAGESERVICE_H
#define MIMICCOMMLIB_MESSAGESERVICE_H


/**
 * External API of the library
 * NOTE! ALL API CALLS ARE BLOCKING!!!
 */

/**
 * Customizable init function. Uses arbitrary delimeter char
 *
 * \param paths local paths of all clients (needed for addresses sharing)
 * \param delimeter character which is used to extract individual paths
 */
extern "C"
int MCL_init_server(char *paths, char delimeter);

/**
 * Initialize client endpoint
 *
 * \param path string containing the path in the file system to this client
 */
extern "C"
void MCL_init_client(char *path);

/**
 * Send data to specified client
 *
 * \param data pointer to the buffer with data
 * \param count number of entities to send
 * \param data_type type of data to send
 * \param destination id of the client to receive data
 */
extern "C"
void MCL_send(void *data, int count, int data_type, int destination);

/**
 * Receive data from a specified client
 *
 * \param buffer buffer to store data
 * \param count number of entities to receive
 * \param data_type type of data to send
 * \param source id of the client which is sending data
 */
extern "C"
void MCL_receive(void *buffer, int count, int data_type, int source);

/**
 * Destroy the endpoint
 */
extern "C"
void MCL_destroy();


#endif //MIMICCOMMLIB_MESSAGESERVICE_H
