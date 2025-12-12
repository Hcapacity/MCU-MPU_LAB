/*
 * button.c
 *
 * Created on: Nov 21, 2025
 * Author: Admin
 */

#include "button.h" // Giả định button.h có chứa các định nghĩa: BUTTON_COUNT, NOR_STATE, PRESSED_STATE, BUTTONx_GPIO_Port, BUTTONx_Pin, và hàm HAL_GPIO_ReadPin.

// Định nghĩa các hằng số thời gian dựa trên chu kỳ 10ms
#define LONG_PRESS_TIME_COUNT       100  // 100 * 10ms = 1000ms (1 giây)
#define DOUBLE_PRESS_TIMEOUT_COUNT  30   // 30 * 10ms = 300ms
#define AUTO_INCREASE_TIME_COUNT    50   // 50 * 10ms = 500ms

// --- CÁC THANH GHI VÀ BIẾN TOÀN CỤC ---

// Thanh ghi chống dội (Debounce)
int KeyReg0[BUTTON_COUNT] = {NOR_STATE, NOR_STATE, NOR_STATE};
int KeyReg1[BUTTON_COUNT] = {NOR_STATE, NOR_STATE, NOR_STATE};
int KeyReg2[BUTTON_COUNT] = {NOR_STATE, NOR_STATE, NOR_STATE};
int KeyReg3[BUTTON_COUNT] = {NOR_STATE, NOR_STATE, NOR_STATE};

// Biến cho phát hiện Nhấn Giữ Lâu (Long Press)
int TimeOutForKeyPress[BUTTON_COUNT] = {LONG_PRESS_TIME_COUNT, LONG_PRESS_TIME_COUNT, LONG_PRESS_TIME_COUNT};
int button_long_pressed[BUTTON_COUNT] = {0, 0, 0}; // Cờ báo Long Press (chỉ kích hoạt 1 lần sau 1s)

// Biến cho phát hiện Nhấn Đơn (Single Press)
int button_flag[BUTTON_COUNT] = {0, 0, 0};

// Biến cho phát hiện Nhấn Đúp (Double Press)
int button_double_pressed[BUTTON_COUNT] = {0, 0, 0};
static int press_count[BUTTON_COUNT] = {0, 0, 0};
static int double_press_timeout[BUTTON_COUNT] = {0, 0, 0};

// Biến cho Tự Động Tăng (Auto-Increase)
int button_auto_increase[BUTTON_COUNT] = {0, 0, 0}; // Cờ báo Auto Increase (kích hoạt mỗi 500ms)
static int auto_increase_counter[BUTTON_COUNT] = {0, 0, 0};
static int button_is_holding[BUTTON_COUNT] = {0, 0, 0}; // Cờ báo đã giữ nút đủ 1s (đã vào trạng thái Long Press)

// Cấu hình GPIO (giữ nguyên)
static GPIO_TypeDef* BUTTON_PORTS[BUTTON_COUNT] = {
    BUTTON1_GPIO_Port,
    BUTTON2_GPIO_Port,
    BUTTON3_GPIO_Port
};

static uint16_t BUTTON_PINS[BUTTON_COUNT] = {
    BUTTON1_Pin,
    BUTTON2_Pin,
    BUTTON3_Pin
};

// --- CÁC HÀM GET FLAG ---

int is_button_pressed(int i){
    if(i < 0 || i >= BUTTON_COUNT) return 0;
    if(button_flag[i] == 1){
        button_flag[i] = 0;
        return 1;
    }
    return 0;
}

int is_button_pressed_1s(int i){
    if(i < 0 || i >= BUTTON_COUNT) return 0;
    if(button_long_pressed[i] == 1){
        button_long_pressed[i] = 0;
        return 1;
    }
    return 0;
}

int is_button_double_pressed(int i){
    if(i < 0 || i >= BUTTON_COUNT) return 0;
    if(button_double_pressed[i] == 1){
        button_double_pressed[i] = 0;
        return 1;
    }
    return 0;
}

int is_button_auto_increase(int i){
    if(i < 0 || i >= BUTTON_COUNT) return 0;
    if(button_auto_increase[i] == 1){
        button_auto_increase[i] = 0;
        return 1;
    }
    return 0;
}

// Optional: Function to check current button state (not edge-triggered)
int is_button_held(int i){
    if(i < 0 || i >= BUTTON_COUNT) return 0;
    return (KeyReg3[i] == PRESSED_STATE);
}

// --- HÀM XỬ LÝ NHẤN ---

void subKeyProcess(int button_index){
    // Xử lý nhấn đơn (Single Press)
    button_flag[button_index] = 1;

    // Xử lý nhấn đúp (Double Press)
    if (double_press_timeout[button_index] > 0) {
        // Nhấn lần thứ 2 trong thời gian 300ms
        press_count[button_index]++;
        if (press_count[button_index] == 2) {
            button_double_pressed[button_index] = 1;
            button_flag[button_index] = 0; // Hủy cờ nhấn đơn nếu là nhấn đúp
            press_count[button_index] = 0;
            double_press_timeout[button_index] = 0;
        }
    } else {
        // Nhấn lần đầu - bắt đầu đếm timeout 300ms
        press_count[button_index] = 1;
        double_press_timeout[button_index] = DOUBLE_PRESS_TIMEOUT_COUNT;
    }
}

// --- HÀM XỬ LÝ CHÍNH ---

void getKeyInput(){
    for(int i = 0; i < BUTTON_COUNT; i++){

        // 1. Cập nhật Double Press Timeout
        if (double_press_timeout[i] > 0) {
            double_press_timeout[i]--;
            // Nếu timeout hết, press_count sẽ tự reset khi có lần nhấn tiếp theo.
            // Không cần reset press_count ở đây để giữ lại cờ nhấn đơn (button_flag) nếu không có nhấn đúp.
        }

        // 2. Lấy dữ liệu 3 thanh ghi chống dội
        KeyReg2[i] = KeyReg1[i];
        KeyReg1[i] = KeyReg0[i];
        KeyReg0[i] = HAL_GPIO_ReadPin(BUTTON_PORTS[i], BUTTON_PINS[i]);

        // 3. Xử lý trạng thái nút (Khi KeyReg0/1/2 giống nhau -> trạng thái ổn định)
        if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])){

            // a) Phát hiện chuyển đổi trạng thái (Cạnh lên hoặc Cạnh xuống)
            if (KeyReg2[i] != KeyReg3[i]){
                KeyReg3[i] = KeyReg2[i]; // Ghi nhận trạng thái ổn định mới

                if (KeyReg3[i] == PRESSED_STATE){
                    // Nút được NHẤN XUỐNG
                    TimeOutForKeyPress[i] = LONG_PRESS_TIME_COUNT; // Bắt đầu đếm 1s
                    subKeyProcess(i);  // Xử lý nhấn đơn/nhấn đúp

                    // Reset cờ trạng thái giữ nút khi nhấn xuống
                    button_is_holding[i] = 0;
                    auto_increase_counter[i] = 0;

                } else {
                    // Nút được NHẢ RA
                    // Reset tất cả cờ liên quan đến trạng thái giữ
                    button_long_pressed[i] = 0;
                    button_is_holding[i] = 0;
                    auto_increase_counter[i] = 0;
                    button_auto_increase[i] = 0;
                }
            }
            // b) Trạng thái ổn định không đổi (Giữ hoặc Nhả)
            else {
                // Chỉ xử lý khi nút đang được GIỮ (PRESSED_STATE)
                if (KeyReg3[i] == PRESSED_STATE) {

                    // i) Logic phát hiện Nhấn Giữ 1s (Long Press)
                    if (button_is_holding[i] == 0) {
                        TimeOutForKeyPress[i]--;
                        if (TimeOutForKeyPress[i] == 0){
                            // Đã đủ 1s (100 * 10ms)
                            button_long_pressed[i] = 1; // Kích hoạt cờ Long Press 1 lần
                            button_is_holding[i] = 1;   // Đặt cờ đã vào trạng thái giữ

                            // Reset double press/single press khi Long Press được phát hiện
                            double_press_timeout[i] = 0;
                            press_count[i] = 0;
                            button_flag[i] = 0; // Hủy cờ single press

                            // Khởi tạo bộ đếm cho Auto-Increase: Lần tăng đầu tiên sẽ xảy ra sau 500ms
                            auto_increase_counter[i] = AUTO_INCREASE_TIME_COUNT;
                        }
                    }

                    // ii) Logic Tự động tăng (Auto-Increase)
                    // Chỉ chạy khi nút đã được giữ đủ 1s (button_is_holding == 1)
                    if (button_is_holding[i] == 1) {
                        auto_increase_counter[i]--;
                        if (auto_increase_counter[i] <= 0) {
                            auto_increase_counter[i] = AUTO_INCREASE_TIME_COUNT; // Reset 500ms
                            button_auto_increase[i] = 1; // Kích hoạt cờ Auto-Increase
                        }
                    }
                }
            }
        }
    }
}
