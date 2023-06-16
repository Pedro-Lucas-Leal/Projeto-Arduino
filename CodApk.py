import wifi_module
import lamp_module
import oven_module

def connect_to_wifi(ssid, password):
    wifi_module.connect(ssid, password)

def toggle_lamp():
    if lamp_module.is_on():
        lamp_module.turn_off()
    else:
        lamp_module.turn_on()

def toggle_oven():
    if oven_module.is_on():
        oven_module.turn_off()
    else:
        oven_module.turn_on()

def toggle_all():
    if lamp_module.is_on() and oven_module.is_on():
        lamp_module.turn_off()
        oven_module.turn_off()
    else:
        lamp_module.turn_on()
        oven_module.turn_on()

def main():
    ssid = "nome_da_rede"
    password = "senha_da_rede"
    connect_to_wifi(ssid, password)

    button1 = Button("Lâmpadas")
    button1.on_press = toggle_lamp

    button2 = Button("Forno")
    button2.on_press = toggle_oven

    button3 = Button("Tudo")
    button3.on_press = toggle_all

    while True:
        button1.check_state()
        button2.check_state()
        button3.check_state()

if __name__ == "__main__":
    main()
