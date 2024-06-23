//
// Created by 熊嘉晟 on 2024/6/23.
//

#ifndef RDMA_RECEIVE_RDMA_RECEIVE_DEP_H
#define RDMA_RECEIVE_RDMA_RECEIVE_DEP_H

#include <doca_error.h>
#include <doca_log.h>
#include <doca_buf_inventory.h>
#include <doca_buf.h>
#include <doca_ctx.h>
#include <doca_argp.h>
#include <chrono>
#include <iostream>

#include "rdma_common.h"

#define MAX_BUFF_SIZE (256) /* Maximum DOCA buffer size */

/*
 * Write the connection details for the sender to read, and read the connection details of the sender
 *
 * @cfg [in]: Configuration parameters
 * @resources [in/out]: RDMA resources
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t write_read_connection(struct rdma_config *cfg, struct rdma_resources *resources);

/*
 * RDMA receive task completed callback
 *
 * @rdma_receive_task [in]: Completed task
 * @task_user_data [in]: doca_data from the task
 * @ctx_user_data [in]: doca_data from the context
 */
void rdma_receive_completed_callback(struct doca_rdma_task_receive *rdma_receive_task,
                                            union doca_data task_user_data,
                                            union doca_data ctx_user_data);

/*
 * RDMA receive task error callback
 *
 * @rdma_receive_task [in]: failed task
 * @task_user_data [in]: doca_data from the task
 * @ctx_user_data [in]: doca_data from the context
 */
void rdma_receive_error_callback(struct doca_rdma_task_receive *rdma_receive_task,
                                        union doca_data task_user_data,
                                        union doca_data ctx_user_data);

/*
 * Export and receive connection details, and connect to the remote RDMA
 *
 * @resources [in]: RDMA resources
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t rdma_receive_export_and_connect(struct rdma_resources *resources);

/*
 * Prepare and submit RDMA receive task
 *
 * @resources [in]: RDMA resources
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t rdma_receive_prepare_and_submit_task(struct rdma_resources *resources);

/*
 * RDMA receive state change callback
 * This function represents the state machine for this RDMA program
 *
 * @user_data [in]: doca_data from the context
 * @ctx [in]: DOCA context
 * @prev_state [in]: Previous DOCA context state
 * @next_state [in]: Next DOCA context state
 */
void rdma_receive_state_change_callback(const union doca_data user_data,
                                               struct doca_ctx *ctx,
                                               enum doca_ctx_states prev_state,
                                               enum doca_ctx_states next_state);

/*
 * Receive a message from the sender
 *
 * @cfg [in]: Configuration parameters
 * @return: DOCA_SUCCESS on success and DOCA_ERROR otherwise
 */
doca_error_t rdma_receive(struct rdma_config *cfg);

#endif //RDMA_RECEIVE_RDMA_RECEIVE_DEP_H
