#include <assert.h>
#include <stdio.h>
#include "control_logic.h"

int main(void) {
    const control_config_t c = {2100, 4095, 70, 0};
    /* Valores representativos de las capturas, NO nuevas mediciones. */
    assert(moisture_percent(4095, 2100, 4095) == 0);
    assert(moisture_percent(2100, 2100, 4095) == 100);
    assert(moisture_percent(2077, 2100, 4095) == 100);
    assert(moisture_percent(2671, 2100, 4095) == 71); /* otra captura usa 73% */
    assert(moisture_percent(2449, 2100, 4095) == 83); /* otra captura usa 84% */
    assert(moisture_percent(2500, 4095, 2100) == -1);
    assert(desired_servo_state(0, true, SERVO_CERRADO, &c) == SERVO_ABIERTO);
    assert(desired_servo_state(70, true, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(100, true, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(40, true, SERVO_CERRADO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(40, true, SERVO_ABIERTO, &c) == SERVO_ABIERTO);
    assert(desired_servo_state(-1, false, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    moving_average_t f;
    moving_average_init(&f);
    assert(moving_average_add(&f, 4000) == 4000); /* sin ceros al inicio */
    assert(moving_average_add(&f, 2000) == 3000);
    for (int i=0;i<8;i++) moving_average_add(&f, 1000);
    assert(moving_average_add(&f, 1000) == 1000);
    puts("OK: 15 verificaciones de logica y filtrado en host (NO prueba hardware)");
    return 0;
}
