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
    assert(moisture_percent(-1, 2100, 4095) == -1);
    assert(moisture_percent(4096, 2100, 4095) == -1);
    assert(moisture_percent(2500, -1, 4095) == -1);
    assert(moisture_percent(2500, 2100, 4096) == -1);
    assert(moisture_percent(2500, 2100, 2100) == -1);
    assert(moisture_percent(3097, 2100, 4095) == 50);
    assert(desired_servo_state(0, true, SERVO_CERRADO, &c) == SERVO_ABIERTO);
    assert(desired_servo_state(70, true, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(100, true, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(40, true, SERVO_CERRADO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(40, true, SERVO_ABIERTO, &c) == SERVO_ABIERTO);
    assert(desired_servo_state(-1, false, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(0, false, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(-1, true, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(101, true, SERVO_ABIERTO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(0, true, SERVO_ABIERTO, NULL) == SERVO_CERRADO);
    assert(desired_servo_state(1, true, SERVO_ABIERTO, &c) == SERVO_ABIERTO);
    assert(desired_servo_state(69, true, SERVO_CERRADO, &c) == SERVO_CERRADO);
    assert(desired_servo_state(40, true, (servo_state_t)2, &c) == SERVO_CERRADO);
    control_config_t invalid = c;
    invalid.umbral_apertura_pct = -1;
    assert(desired_servo_state(40, true, SERVO_ABIERTO, &invalid) == SERVO_CERRADO);
    invalid = c;
    invalid.umbral_cierre_pct = 101;
    assert(desired_servo_state(40, true, SERVO_ABIERTO, &invalid) == SERVO_CERRADO);
    invalid.umbral_cierre_pct = 0;
    assert(desired_servo_state(0, true, SERVO_ABIERTO, &invalid) == SERVO_CERRADO);
    moving_average_t f;
    moving_average_init(&f);
    assert(moving_average_add(&f, 4000) == 4000); /* sin ceros al inicio */
    assert(moving_average_add(&f, 2000) == 3000);
    assert(moving_average_add(&f, -1) == -1);
    assert(moving_average_add(&f, 4096) == -1);
    assert(f.count == 2 && f.total == 6000 && f.next == 2);
    assert(moving_average_add(NULL, 1000) == -1);
    for (int i=0;i<8;i++) moving_average_add(&f, 1000);
    assert(moving_average_add(&f, 1000) == 1000);
    moving_average_init(&f);
    assert(moving_average_add(&f, 4095) == 4095);
    for (int i = 0; i < 7; i++) moving_average_add(&f, 0);
    assert(f.count == 8 && f.next == 0 && f.total == 4095);
    assert(moving_average_add(&f, 0) == 0); /* reemplaza la muestra más antigua */
    moving_average_init(&f);
    assert(moving_average_add(&f, 0) == 0); /* recuperación sin historia previa */
    assert(moving_average_add(&f, 1) == 1); /* redondeo de 0,5 */
    puts("OK: calibracion, control y media movil en PC (NO prueba hardware)");
    return 0;
}
