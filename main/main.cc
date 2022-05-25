/* pthread/std::thread example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

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

#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "protocol_examples_common.h"

#include "thread.hh"

extern "C" {
#include "mqtt.h"    
}


static char *TAG = (char *)"OGESP";

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());

    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("MQTT_CLIENT", ESP_LOG_VERBOSE);
    esp_log_level_set("MQTT_EXAMPLE", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT_BASE", ESP_LOG_VERBOSE);
    esp_log_level_set("esp-tls", ESP_LOG_VERBOSE);
    esp_log_level_set("TRANSPORT", ESP_LOG_VERBOSE);
    esp_log_level_set("OUTBOX", ESP_LOG_VERBOSE);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    /*
     * This helper function configures Wi-Fi or Ethernet, as selected
     * in menuconfig. Read "Establishing Wi-Fi or Ethernet
     * Connection" section in examples/protocols/README.md for more
     * information about this function.
     */
    ESP_ERROR_CHECK(example_connect());

    // Create a thread using deafult values that can run on any core
    auto cfg = esp_pthread_get_default_config();
    esp_pthread_set_cfg(&cfg);
    std::thread any_core(thread_func_any_core);

    // Create a thread on core 0 that spawns another thread, they will
    // both have the same name etc.  
    cfg = create_config("Core 0", 0, 3 * 1024, 5);
    cfg.inherit_cfg = true;
    esp_pthread_set_cfg(&cfg);
    std::thread thread_1(spawn_another_thread);

    // Create a thread on core 1.
    cfg = create_config("Core 1", 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&cfg);
    std::thread thread_2(thread_func);

    // Create a thread using deafult values that can run on any core
    cfg = create_config("MQTT Listener", 1, 3 * 1024, 5);
    esp_pthread_set_cfg(&cfg);
    std::thread mqtt_thread(mqtt_app_start);


    // Let the main task do something too
    while (true) {
#ifdef NOTNOW
        std::stringstream ss;
        ss << "core id: " << xPortGetCoreID()
           << ", prio: " << uxTaskPriorityGet(nullptr)
           << ", minimum free stack: "
           << uxTaskGetStackHighWaterMark(nullptr)
           << " bytes.";
        ESP_LOGI(pcTaskGetName(nullptr), "%s", ss.str().c_str());
#endif
        std::this_thread::sleep_for(sleep_time);
    }
}
