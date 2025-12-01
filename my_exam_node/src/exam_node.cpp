#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
// INCLUDE CRITICO: Verifica che corrisponda al nome della cartella in src!
#include "sysmonitor_interfaces/msg/sysmon.hpp"

using std::placeholders::_1;

class ExamNode : public rclcpp::Node
{
public:
  ExamNode()
  : Node("exam_node_cpp")
  {
    // Publisher: topic /test, tipo Float64 (richiesto dall'esercizio)
    publisher_ = this->create_publisher<std_msgs::msg::Float64>("/test", 10);

    // Subscriber: topic /system_info
    // Tipo messaggio: sysmonitor_interfaces::msg::Sysmon (preso dai metadati della bag)
    subscription_ = this->create_subscription<sysmonitor_interfaces::msg::Sysmon>(
      "/system_info",
      10,
      std::bind(&ExamNode::topic_callback, this, _1));

    RCLCPP_INFO(this->get_logger(), "Nodo C++ avviato! Attendo dati su /system_info...");
  }

private:
  void topic_callback(const sysmonitor_interfaces::msg::Sysmon::SharedPtr msg) const
  {
    // L'esercizio chiede di pubblicare "an example 0 or 1"
    auto message = std_msgs::msg::Float64();
    message.data = 1.0; 

    // (Opzionale) Stampiamo un dato del messaggio ricevuto per debug
    // Nota: msg->data o msg->cpu_load dipendono dalla definizione interna di Sysmon.
    // Per sicurezza stampiamo solo che abbiamo ricevuto qualcosa.
    RCLCPP_INFO(this->get_logger(), "Dati ricevuti da System. Pubblico 1.0 su /test");
    
    publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
  rclcpp::Subscription<sysmonitor_interfaces::msg::Sysmon>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ExamNode>());
  rclcpp::shutdown();
  return 0;
}

