import utime
from machine import Pin

left_sensor_pin = Pin(16, Pin.IN)
right_sensor_pin = Pin(17, Pin.IN)

motor_a1 = Pin(0, Pin.OUT)
motor_a2 = Pin(1, Pin.OUT)
motor_b1 = Pin(2, Pin.OUT)
motor_b2 = Pin(3, Pin.OUT)


def forward():
    motor_a1.low()
    motor_a2.high()
    motor_b1.low()
    motor_b2.high()


def right():
    motor_a1.low()
    motor_a2.high()
    motor_b1.high()
    motor_b2.low()


def left():
    motor_a1.high()
    motor_a2.low()
    motor_b1.low()
    motor_b2.high()


def stop():
    motor_a1.low()
    motor_a2.low()
    motor_b1.low()
    motor_b2.low()


while True:
    left_sensor_state = left_sensor_pin()
    right_sensor_state = right_sensor_pin()

    print("left: ", str(left_sensor_state) + " -- right: " + str(right_sensor_state))

    if right_sensor_state == 0 and left_sensor_state == 1:
        print("turning right")
        right()

    if right_sensor_state == 1 and left_sensor_state == 0:
        print("turning left")
        left()

    if right_sensor_state == 1 and left_sensor_state == 1:
        print("stop..")
        stop()

    if right_sensor_state == 0 and left_sensor_state == 0:
        print("forward")
        forward()
    utime.sleep(0.01)
