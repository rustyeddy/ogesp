#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <string>
#include <sstream>
#include <esp_pthread.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

extern void thread_func_any_core();
extern esp_pthread_cfg_t create_config(const char *name, int core_id,
                                       int stack, int prio);

extern void spawn_another_thread();
extern void thread_func();
extern void thread_init();

using namespace std::chrono;
const auto sleep_time = seconds
{
    5
};

