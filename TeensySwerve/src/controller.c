// This program is intended to ingest human input and publish a message usable by other nodes.

// Initialization
// ==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==
#include <rclc_lifecycle/rclc_lifecycle.h>

 // "\" lets me use multiple lines for readability
#define RCCHECK(fn) { \
    rcl_ret_t tempRC = fn; \
    \
    if (tempRC != RCL_RET_OK) { \
        printf("Failed status on line %d: %d. Aborting\n", __LINE__, (int)tempRC); \
        return 1; \
    } \
}
// Same as RCCheck but doesn't return anything
#define RCSOFTCHECK(fn) {rcl_ret_t tempRC = fn; if (tempRC != RCL_RET_OK) {printf("Failed status on line %d: %d. Continuing\n", __LINE__, (int)tempRC);}}

// Callbacks for state changes
rcl_ret_t myOnConfigure(){
    printf("    >>> lifecycleNode: on_configure() callback called.\n"); return RCL_RET_OK;
}
rcl_ret_t myOnActivate(){
    printf("    >>> lifecycleNode: on_activate() callback called.\n"); return RCL_RET_OK;
}
rcl_ret_t myOnDeactivate(){
    printf("    >>> lifecycleNode: on_deactivate() callback called.\n"); return RCL_RET_OK;
}
rcl_ret_t myOnCleanup(){
    printf("    >>> lifecycleNode: on_cleanup() callback called.\n"); return RCL_RET_OK;
}

int main(int argc, const char * argv[]){
    rcl_allocator_t allocator = rcl_get_default_allocator();
    rclc_support_t support;
    rcl_ret_t rc; //Retrun Code

    // create rcl node
    rc = rclc_support_init(&support, argc, argv, &allocator);
    if (rc != RCL_RET_OK){printf("Error rclc_support_init.\n"); return -1;}
    rcl_node_t myNode;
    rc = rclc_node_init_default(&myNode, "myLifecycle", "rclc", &support);
    if (rc != RCL_RET_OK){printf("Error rclc_node_init_default.\n"); return -1;}

    // rcl state machine
    rcl_lifecycle_state_machine_t stateMachine = rcl_lifecycle_get_zero_initialized_state_machine();
    rclc_lifecycle_node_t lifecycleNode;

    // make it a lifecycle node
    rclc_lifecycle_node_t lifecycleNode;
    rc = rclc_make_node_a_lifecycle_node(
        &lifecycleNode,
        &myNode,
        &stateMachine,
        &allocator,
        true
    );
    if (rc != RCL_RET_OK){printf("Error in creating lifecycle node.\n"); return -1;}

    // Executor time
    // there's a default number of pubs/subs but idk what it is.
    // see documentation in the executor.h at the fuction rclc_executor_init() for more details.
    // (don't forget to configure the micro-ROS middleware too to change from the default number)
    rclc_executor_t executor;
    RCCHECK(rc = rclc_executor_init(
        &executor,
        &support.context,
        4, // 1 for the node + 1 for each lifecycle service
        &allocator
    ));

    // Register lifecycle services
    RCCHECK(rclc_lifecycle_add_get_state_service(&lifecycleNode, &executor));
    RCCHECK(rclc_lifecycle_add_get_available_states_services(&lifecycleNode, &executor));
    RCCHECK(rclc_lifecycle_add_change_state_service(&lifecycleNode, &executor));

    // Register lifecycle service callbacks
    rclc_lifecycle_register_on_configure(&lifecycleNode, &myOnConfigure);
    rclc_lifecycle_register_on_activate(&lifecycleNode, &myOnActivate);
    rclc_lifecycle_register_on_deactivate(&lifecycleNode, &myOnDeactivate);
    rclc_lifecycle_register_on_cleanup(&lifecycleNode, &myOnCleanup);

    // Run time
    // ==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==
    RCSOFTCHECK(rclc_executor_spin(&executor));

    // Cleanup time
    // ==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==
    rc = rclc_lifecycle_node_fini(&lifecycleNode, &allocator);
    rc += rclc_node_fini(&myNode);
    rc += rclc_executor_fini(&executor);
    rc += rclc_support_fini(&support);

    if (rc != RCL_RET_OK){printf("Error while cleaning up!\n"); return -1;}

    return 0;
}

