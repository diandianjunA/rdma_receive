#include <iostream>
#include <stdlib.h>

#include <doca_log.h>
#include <doca_argp.h>

#include "rdma_common.h"

DOCA_LOG_REGISTER(RDMA_RECEIVE::MAIN);

/* Sample's Logic */
doca_error_t rdma_receive(struct rdma_config *cfg);

/*
 * Sample main function
 *
 * @argc [in]: command line arguments size
 * @argv [in]: array of command line arguments
 * @return: EXIT_SUCCESS on success and EXIT_FAILURE otherwise
 */
int main(int argc, char **argv)
{
    struct rdma_config cfg;
    doca_error_t result;
    struct doca_log_backend *sdk_log;
    int exit_status = EXIT_FAILURE;

    /* Set the default configuration values (Example values) */
    strcpy(cfg.local_connection_desc_path, DEFAULT_LOCAL_CONNECTION_DESC_PATH);
    strcpy(cfg.remote_connection_desc_path, DEFAULT_REMOTE_CONNECTION_DESC_PATH);
    cfg.is_gid_index_set = false;

    /* No need for send_string in the receiver side */
    cfg.send_string[0] = '\0';

    /* Register a logger backend */
    result = doca_log_backend_create_standard();
    if (result != DOCA_SUCCESS)
        goto sample_exit;

    /* Register a logger backend for internal SDK errors and warnings */
    result = doca_log_backend_create_with_file_sdk(stderr, &sdk_log);
    if (result != DOCA_SUCCESS)
        goto sample_exit;
    result = doca_log_backend_set_sdk_level(sdk_log, DOCA_LOG_LEVEL_WARNING);
    if (result != DOCA_SUCCESS)
        goto sample_exit;

    DOCA_LOG_INFO("Starting the sample");

    /* Start sample */
    result = rdma_receive(&cfg);
    if (result != DOCA_SUCCESS) {
        DOCA_LOG_ERR("rdma_receive() failed: %s", doca_error_get_descr(result));
        goto argp_cleanup;
    }

    exit_status = EXIT_SUCCESS;

    argp_cleanup:
    sample_exit:
    if (exit_status == EXIT_SUCCESS)
        DOCA_LOG_INFO("Sample finished successfully");
    else
        DOCA_LOG_INFO("Sample finished with errors");
    return exit_status;
}
