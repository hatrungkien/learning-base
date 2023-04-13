//#include <iostream>
//#include <thread>
//#include <mqtt/async_client.h>
//
//class MqttCallback : public virtual mqtt::callback {
//public:
//    void connection_lost(const std::string& cause) {
//        std::cout << "Connection lost: " << cause << std::endl;
//    }
//
//    void message_arrived(mqtt::const_message_ptr msg) {
//        std::cout << "Message received: " << msg->to_string() << std::endl;
//    }
//
//    void delivery_complete(mqtt::delivery_token_ptr token) {
//        std::cout << "Delivery complete" << std::endl;
//    }
//};
//
//void mqtt_thread_func(mqtt::async_client* client) {
//    try {
//        client->start_consuming();
//    } catch (const mqtt::exception& exc) {
//        std::cerr << "Error: " << exc.what() << std::endl;
//    }
//}
//
//int main(int argc, char* argv[]) {
//    std::string address = "tcp://localhost:1883";
//    std::string client_id = "abc123";
//    std::string topic = "test/mqtt";
//    int qos = 0;
//
//    mqtt::async_client client(address, client_id);
//    MqttCallback cb;
//    client.set_callback(cb);
//    mqtt::connect_options conn_opts;
//    conn_opts.set_keep_alive_interval(20);
//
//    mqtt::token_ptr conn = client.connect(conn_opts);
//    conn->wait();
//
//    mqtt::token_ptr sub = client.subscribe(topic, qos);
//    sub->wait();
//
//    std::thread mqtt_thread(mqtt_thread_func, &client);
//    while (true) {
//        std::cout << "main thread running" << std::endl;
//        std::this_thread::sleep_for(std::chrono::seconds(1));
//    }
//
//    client.stop_consuming();
//    mqtt_thread.join();
//
//    return 0;
//}

#include <iostream>
#include <mqtt/async_client.h>
#include "mqtt/client.h"

class MqttCallback : public virtual mqtt::callback {
public:
    virtual void connected(const std::string& cause) {
        std::cout << "Connected: " << cause << std::endl;
    }
    virtual void connection_lost(const std::string& cause) {
        std::cout << "Connection lost: " << cause << std::endl;
    }

    virtual void message_arrived(mqtt::const_message_ptr msg) {
        std::cout << "Message received: " << msg->to_string() << std::endl;
    }

    virtual void delivery_complete(mqtt::delivery_token_ptr token) {
        std::cout << "Delivery complete" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    std::string address = "tcp://localhost:1883";
    std::string client_id = "abc123";
    std::string topic = "test/mqtt";
    int qos = 1;

    mqtt::async_client client(address, client_id);
    mqtt::connect_options conn_opts;
    MqttCallback cb;
    client.set_callback(cb);
    conn_opts.set_keep_alive_interval(1);
    mqtt::token_ptr conn = client.connect(conn_opts);
    conn->wait();
    mqtt::token_ptr sub = client.subscribe(topic, qos);
    sub->wait();

    while (true) {
        try {
            client.start_consuming();
        } catch (const mqtt::exception& exc) {
            std::cerr << "Error: " << exc.what() << std::endl;
        }
    }

    return 0;
}