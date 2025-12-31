#ifndef AHT_SENSOR_MANAGER_H  // Header Guard: Ngăn việc nạp file này 2 lần gây lỗi biên dịch
#define AHT_SENSOR_MANAGER_H

#include <Wire.h> // Thư viện hỗ trợ giao tiếp I2C
#include <Adafruit_AHTX0.h> // Thư viện điều khiển cảm biến AHT10/AHT20

enum SensorState {
  INIT, // Khởi tạo cảm biến
  IDLE, // Trạng thái nghỉ, chờ đến lần đo tiếp theo
  TRIGGER,  // Ra lệnh cho cảm biến bắt đầu đo
  WAITING,  // Chờ cảm biến xử lý dữ liệu
  READ_DATA,  // Đọc dữ liệu từ cảm biến và lưu vào biến
  ERROR // Xử lý khi có lỗi (ví dụ: mất kết nối I2C)
};

class AHTSensorManager {
private:
  Adafruit_AHTX0 aht; // Đối tượng cảm biến từ thư viện Adafruit
  SensorState currentState; // Lưu trạng thái hiện tại
  unsigned long lastTimestamp;  // Lưu mốc thời gian để tính toán delay non-blocking
  float temp;
  float humi;

public: 
  AHTSensorManager(); // Hàm khởi tạo
  void begin(); // Hàm thiết lập ban đầu
  void update();  // Hàm cập nhật 
  float getTemp();  // Hàm lấy giá trị nhiệt độ
  float getHumi();  // Hàm lấy giá trị độ ẩm
};

#endif