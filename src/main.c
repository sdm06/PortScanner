#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "scanner.h"

// Initialize the Mutex
pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <IP>\n", argv[0]);
        return 1;
    }

    char *target_ip = argv[1];
    int num_threads = 4;
    pthread_t threads[num_threads];
    scan_range_t ranges[num_threads];

    int ports_per_thread = 1024 / num_threads;

    for (int i = 0; i < num_threads; i++) {
        // Define the chunk of work for this specific thread
        ranges[i].ip = target_ip;
        ranges[i].start_port = (i * ports_per_thread) + 1;
        ranges[i].end_port = (i + 1) * ports_per_thread;

        // pthread_create(id_ptr, attributes, function_to_run, argument)
        if (pthread_create(&threads[i], NULL, scan_ports, &ranges[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    // Join threads (wait for them to finish) before exiting main()
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Scan complete.\n");
    pthread_mutex_destroy(&log_mutex);
    return 0;
}
