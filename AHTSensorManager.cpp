#include "AHTSensorManager.h"

// Khởi tạo các giá trị mặc định cho đối tượng
AHTSensorManager::AHTSensorManager() {
    currentState = INIT;
    lastTimestamp = 0;
}

// Kiểm tra kết nối với cảm biến qua I2C
void AHTSensorManager::begin() {
    if (!aht.begin()) {
        currentState = ERROR; // Nếu không tìm thấy cảm biến, chuyển sang lỗi
    } else {
        currentState = IDLE;  // Sẵn sàng hoạt động
    }
}

void AHTSensorManager::update() {
  switch (currentState) {
    case INIT:
      begin();
      break;

    case IDLE:
      if (millis() - lastTimestamp >= 2000) { // Sau 2 giây nghỉ thì mới bắt đầu chu kỳ đo mới
        currentState = TRIGGER;
      }
      break;

    case TRIGGER:
      currentState = WAITING; // Chuẩn bị chuyển sang bước chờ cảm biến xử lý
      lastTimestamp = millis();
      break;

    case WAITING:
    // Đợi ít nhất 80ms theo datasheet của AHT20 để dữ liệu sẵn sàng
      if (millis() - lastTimestamp >= 80) { // Wait for measurement
        currentState = READ_DATA;
      }
      break;

    case READ_DATA:
      sensors_event_t hum_event, temp_event; 
      aht.getEvent(&hum_event, &temp_event);
  
      this->temp = temp_event.temperature;   // Lấy dữ liệu từ thư viện
      this->humi = hum_event.relative_humidity; // Cập nhật độ ẩm vào biến class

  currentState = IDLE;
  lastTimestamp = millis();
  break;

      currentState = IDLE; // Quay lại trạng thái nghỉ
      lastTimestamp = millis();
      break;

      case ERROR: 
        break;
  }
}

// Trả về giá trị nhiệt độ đã lưu
float AHTSensorManager::getTemp() {return temp; }
// Trả về giá trị độ ẩm đã lưu
float AHTSensorManager::getHumi() {return humi; }