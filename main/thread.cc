#include "thread.hh"

void print_thread_info(const char *extra = nullptr)
{
    std::stringstream ss;
    if (extra) {
        ss << extra;
    }
    ss << "Core id: " << xPortGetCoreID()
       << ", prio: " << uxTaskPriorityGet(nullptr)
       << ", minimum free stack: " << uxTaskGetStackHighWaterMark(nullptr) << " bytes.";
    ESP_LOGI(pcTaskGetName(nullptr), "%s", ss.str().c_str());
}

void thread_func_inherited()
{
    while (true) {
        print_thread_info("This is the INHERITING thread with the same parameters as our parent, including name. ");
        std::this_thread::sleep_for(sleep_time);
    }
}

void spawn_another_thread()
{
    // Create a new thread, it will inherit our configuration
    std::thread inherits(thread_func_inherited);

    while (true) {
        print_thread_info();
        std::this_thread::sleep_for(sleep_time);
    }
}

void thread_func_any_core()
{
    while (true) {
        print_thread_info("This thread (with the default name) may run on any core.");
        std::this_thread::sleep_for(sleep_time);
    }
}

void thread_func()
{
    while (true) {
        print_thread_info();
        std::this_thread::sleep_for(sleep_time);
    }
}

esp_pthread_cfg_t create_config(const char *name, int core_id, int stack, int prio)
{
    auto cfg = esp_pthread_get_default_config();
    cfg.thread_name = name;
    cfg.pin_to_core = core_id;
    cfg.stack_size = stack;
    cfg.prio = prio;
    return cfg;
}

void thread_init()
{

}
